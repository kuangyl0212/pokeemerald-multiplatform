#!/usr/bin/env python3
"""Tests for generate_chinese_font.py

Run with: python -m pytest tools/test_generate_chinese_font.py
Or:       python tools/test_generate_chinese_font.py
"""

import os
import sys
import struct
import tempfile
import unittest

# Add tools dir to path so we can import the module
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from generate_chinese_font import (
    gb2312_to_index,
    TOTAL_ZONES,
    POS_PER_ZONE,
    TOTAL_SLOTS,
    BYTES_PER_GLYPH,
    CHAR_WIDTH,
    CHAR_HEIGHT,
    BG,
    FG,
    SHADOW,
    generate_font,
    render_glyph_2bpp,
    find_font,
)


class TestGB2312ToIndex(unittest.TestCase):
    """Test the GB2312 to glyph index conversion."""

    def test_ah_char_index(self):
        """'啊' encodes to B0 A1 in GB2312."""
        # '啊' = B0 A1
        idx = gb2312_to_index(0xB0, 0xA1)
        # zone = 0xB0 - 0x81 = 0x2F = 47
        # pos = 0xA1 - 0x40 - 1 = 96  (0xA1 > 0x7F so pos--)
        # index = 47 * 190 + 96 = 9026
        self.assertEqual(idx, 47 * 190 + 96)

    def test_first_valid_gb2312_char(self):
        """First valid GB2312 hanzi is at zone 16, pos 1 = A1 A1."""
        # A1 A1 is the first EUC-CN character
        idx = gb2312_to_index(0xA1, 0xA1)
        # zone = 0xA1 - 0x81 = 0x20 = 32
        # pos = 0xA1 - 0x40 - 1 = 96
        # index = 32 * 190 + 96 = 6176
        self.assertEqual(idx, 32 * 190 + 96)

    def test_byte_below_0x7f_no_adjustment(self):
        """Second byte 0x40-0x7E: no position adjustment."""
        # b2 = 0x40 -> pos = 0 (no adjustment since 0x40 <= 0x7F)
        idx = gb2312_to_index(0x81, 0x40)
        self.assertEqual(idx, 0 * 190 + 0)

    def test_byte_above_0x7f_adjustment(self):
        """Second byte 0x80-0xFE: position adjusted by -1."""
        # b2 = 0x80 -> pos = 0x80 - 0x40 - 1 = 63
        idx = gb2312_to_index(0x81, 0x80)
        self.assertEqual(idx, 0 * 190 + 63)

    def test_max_index(self):
        """Maximum index: zone 125, pos 189."""
        idx = gb2312_to_index(0xFE, 0xFE)
        # zone = 0xFE - 0x81 = 125
        # pos = 0xFE - 0x40 - 1 = 189
        self.assertEqual(idx, 125 * 190 + 189)

    def test_total_slots(self):
        """Total slots = 126 zones * 190 positions = 23940."""
        self.assertEqual(TOTAL_SLOTS, 23940)


class TestFontGeneration(unittest.TestCase):
    """Test the font file generation."""

    @classmethod
    def setUpClass(cls):
        """Generate the font files once for all tests."""
        cls.tmpdir = tempfile.mkdtemp()
        cls.glyph_path = os.path.join(cls.tmpdir, "chinese.1bpp")
        cls.width_path = os.path.join(cls.tmpdir, "chinese_widths.bin")
        generate_font(cls.glyph_path, cls.width_path)

    def test_glyph_file_size(self):
        """Font file should be TOTAL_SLOTS * 18 bytes."""
        size = os.path.getsize(self.glyph_path)
        self.assertEqual(size, TOTAL_SLOTS * BYTES_PER_GLYPH)

    def test_width_file_size(self):
        """Width file should be TOTAL_SLOTS bytes."""
        size = os.path.getsize(self.width_path)
        self.assertEqual(size, TOTAL_SLOTS)

    def test_ah_glyph_nonzero(self):
        """'啊' (B0 A1) should have non-zero glyph data."""
        idx = gb2312_to_index(0xB0, 0xA1)
        offset = idx * BYTES_PER_GLYPH
        with open(self.glyph_path, "rb") as f:
            f.seek(offset)
            data = f.read(BYTES_PER_GLYPH)
        self.assertTrue(any(b != 0 for b in data),
                        f"Glyph for '啊' at index {idx} is all zeros")

    def test_ah_width_is_12(self):
        """'啊' should have width 12 (full-width character)."""
        idx = gb2312_to_index(0xB0, 0xA1)
        with open(self.width_path, "rb") as f:
            f.seek(idx)
            width = f.read(1)[0]
        self.assertEqual(width, 12)

    def test_empty_slot_is_zero(self):
        """An invalid GB2312 slot should have zero glyph data."""
        # Zone 0 (byte 0x81) position 0 (byte 0x40) is not a valid
        # EUC-CN character - it should be zero
        idx = gb2312_to_index(0x81, 0x40)
        offset = idx * BYTES_PER_GLYPH
        with open(self.glyph_path, "rb") as f:
            f.seek(offset)
            data = f.read(BYTES_PER_GLYPH)
        self.assertTrue(all(b == 0 for b in data),
                        f"Empty slot at index {idx} should be zero")

    def test_chinese_punctuation_present(self):
        """Chinese full-width comma '，' (A3 AC) should have non-zero data."""
        try:
            b = '，'.encode('gb2312')
        except UnicodeEncodeError:
            self.skipTest("Cannot encode '，' in GB2312")
        idx = gb2312_to_index(b[0], b[1])
        offset = idx * BYTES_PER_GLYPH
        with open(self.glyph_path, "rb") as f:
            f.seek(offset)
            data = f.read(BYTES_PER_GLYPH)
        self.assertTrue(any(b != 0 for b in data),
                        f"Glyph for '，' at index {idx} is all zeros")


class TestShadowRendering(unittest.TestCase):
    """Test that Chinese glyphs are rendered with a drop shadow.

    The English latin_normal.png font uses 2bpp 4-color encoding where
    pixel value 2 = SHADOW (a light-gray drop shadow offset to the
    bottom-right). Chinese glyphs must use the same convention so the
    rendered text matches the English style.
    """

    @classmethod
    def setUpClass(cls):
        """Render a known character once for inspection."""
        cls.font_path = find_font()
        if cls.font_path is None:
            raise unittest.SkipTest("No Chinese TTF font available")
        from PIL import Image, ImageDraw, ImageFont
        cls._PIL = (Image, ImageDraw, ImageFont)

    def _render(self, char):
        Image, ImageDraw, ImageFont = self._PIL
        font = ImageFont.truetype(self.font_path, CHAR_HEIGHT)
        img = Image.new('L', (16, 16), 0)
        draw = ImageDraw.Draw(img)
        return render_glyph_2bpp(char, font, img, draw)

    def _unpack_glyph(self, glyph_bytes):
        """Unpack 64 bytes of 2bpp data into a 16x16 grid of pixel values."""
        from generate_chinese_font import _pack_4_pixels_to_byte, TILE_SIZE
        # Each tile is 8x8 = 16 bytes (8 rows x 2 bytes/row)
        # Tile order: TL, TR, BL, BR
        # Each byte = 4 pixels, MSB first
        # Byte order in font data: right half first, then left half (per
        # DecompressGlyphTile's u16 read + byte swap)
        grid = [[0] * 16 for _ in range(16)]
        tile_order = [(0, 0), (1, 0), (0, 1), (1, 1)]
        for tile_idx, (tx, ty) in enumerate(tile_order):
            tile_offset = tile_idx * 16
            base_x = tx * 8
            base_y = ty * 8
            for row in range(8):
                y = base_y + row
                byte_offset = tile_offset + row * 2
                # First byte = right half (pixels 4-7), second = left half (0-3)
                hi_byte = glyph_bytes[byte_offset]
                lo_byte = glyph_bytes[byte_offset + 1]
                # Right half pixels 4-7
                for i in range(4):
                    px = (hi_byte >> (6 - i * 2)) & 0x3
                    grid[y][base_x + 4 + i] = px
                # Left half pixels 0-3
                for i in range(4):
                    px = (lo_byte >> (6 - i * 2)) & 0x3
                    grid[y][base_x + i] = px
        return grid

    def test_glyph_contains_shadow_pixels(self):
        """A typical Chinese character should produce SHADOW (2) pixels."""
        glyph_bytes, _ = self._render('待')
        grid = self._unpack_glyph(glyph_bytes)
        flat = [v for row in grid for v in row]
        self.assertIn(SHADOW, flat,
                      "Glyph for '待' contains no SHADOW pixels")

    def test_glyph_contains_fg_pixels(self):
        """A typical Chinese character should produce FG (1) pixels."""
        glyph_bytes, _ = self._render('待')
        grid = self._unpack_glyph(glyph_bytes)
        flat = [v for row in grid for v in row]
        self.assertIn(FG, flat,
                      "Glyph for '待' contains no FG pixels")

    def test_shadow_offset_bottom_right(self):
        """Shadow pixels should appear at the bottom-right of FG pixels.

        For any pixel that is FG, the pixel at (x+1, y+1) should be
        SHADOW (unless out of bounds). At minimum, the bottom-right
        region of the glyph should contain SHADOW pixels.
        """
        glyph_bytes, _ = self._render('宝')
        grid = self._unpack_glyph(glyph_bytes)
        # Collect FG and SHADOW coordinates
        fg_coords = [(x, y) for y in range(16) for x in range(16)
                     if grid[y][x] == FG]
        shadow_coords = [(x, y) for y in range(16) for x in range(16)
                         if grid[y][x] == SHADOW]
        self.assertTrue(fg_coords, "No FG pixels found")
        self.assertTrue(shadow_coords, "No SHADOW pixels found")
        # The shadow should be offset to the bottom-right: average shadow
        # position should be greater than average FG position in both x and y.
        avg_fg_x = sum(x for x, _ in fg_coords) / len(fg_coords)
        avg_fg_y = sum(y for _, y in fg_coords) / len(fg_coords)
        avg_sh_x = sum(x for x, _ in shadow_coords) / len(shadow_coords)
        avg_sh_y = sum(y for _, y in shadow_coords) / len(shadow_coords)
        self.assertGreater(avg_sh_x, avg_fg_x,
                           "Shadow is not offset to the right of FG")
        self.assertGreater(avg_sh_y, avg_fg_y,
                           "Shadow is not offset below FG")


if __name__ == "__main__":
    unittest.main()
