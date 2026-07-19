#!/usr/bin/env python3
"""Generate 16x16 2bpp Chinese bitmap font for pokeemerald PC port.

Renders GB2312 characters from a TTF font to 16x16 2bpp bitmaps
(12x12 character centered in 16x16 canvas, compatible with DecompressGlyphTile).

Outputs:
  - chinese.latfont (glyph data, 2bpp format, 64 bytes per glyph)
  - chinese_widths.bin (width table, 1 byte per glyph slot)

GB2312 encoding space:
  - First byte: 0x81-0xFE (126 zones)
  - Second byte: 0x40-0xFE, skipping 0x7F (190 positions per zone)
  - Total slots: 126 * 190 = 23940

2bpp format (compatible with GBA DecompressGlyphTile):
  - Each pixel: 2 bits (0=bg, 1=fg, 2=shadow)
  - Each byte: 4 pixels, MSB first (bits 7-6 = pixel 0, bits 5-4 = pixel 1, ...)
  - Each 8x8 tile: 16 bytes, 8 rows x 2 bytes/row
  - Each 16x16 glyph: 4 tiles (top-left, top-right, bottom-left, bottom-right) = 64 bytes
  - Row layout in tile: 2 bytes per row, low byte = first 4 pixels, high byte = next 4 pixels

Usage:
  python generate_chinese_font.py <output_glyphs> <output_widths>
  python generate_chinese_font.py graphics/fonts/chinese.latfont graphics/fonts/chinese_widths.bin
"""

import os
import sys

# Canvas dimensions (character is 12x12 at top-left of 16x16 canvas)
# The renderer (CopyGlyphToWindow) only renders the top-left 12x12 region
# (width=12, height=12), so the character must be placed at offset (0,0),
# NOT centered. Centering at (2,2) would truncate the right and bottom
# 2 pixels of each character.
CANVAS_WIDTH = 16
CANVAS_HEIGHT = 16
CHAR_WIDTH = 12
CHAR_HEIGHT = 12
CHAR_OFFSET_X = 0
# Vertical offset to align Chinese baseline with English font.
# English latin_normal renders glyphs at y=[0,14] (height=15).
# Without offset, Chinese glyphs render at y=[0,11], making text appear
# too high. Pushing down by 3px places Chinese at y=[3,14], aligning
# the baseline with the English font.
CHAR_OFFSET_Y = 3

# 2bpp: 4 pixels per byte, 2 bytes per row (8 pixels), 16 bytes per 8x8 tile
TILE_SIZE = 8
TILE_WIDTH_BYTES = 2  # 8 pixels * 2bpp / 8 = 2 bytes per row
BYTES_PER_TILE = TILE_SIZE * TILE_WIDTH_BYTES  # 8 * 2 = 16 bytes
TILES_PER_GLYPH = 4  # 2x2 tiles for 16x16
BYTES_PER_GLYPH = BYTES_PER_TILE * TILES_PER_GLYPH  # 64 bytes

# GB2312 encoding space
TOTAL_ZONES = 0xFE - 0x81 + 1  # 126
POS_PER_ZONE = (0xFE - 0x40 + 1) - 1  # 190
TOTAL_SLOTS = TOTAL_ZONES * POS_PER_ZONE  # 23940

# Full-width character width
FULL_WIDTH = 12

# Font search paths (project-bundled Ark-Pixel-Font takes priority)
_FONT_DIR = os.path.dirname(os.path.abspath(__file__))
_PROJECT_ROOT = os.path.dirname(_FONT_DIR)
FONT_PATHS = [
    # Project-bundled pixel font (preferred — matches GBA aesthetic)
    os.path.join(_FONT_DIR, 'fonts', 'ark-pixel-12px-monospaced-zh_cn.ttf'),
    # System fallbacks
    '/usr/share/fonts/truetype/wqy/wqy-zenhei.ttc',
    '/usr/share/fonts/truetype/wqy/wqy-microhei.ttc',
    '/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc',
    '/usr/share/fonts/noto-cjk/NotoSansCJK-Regular.ttc',
    'C:/Windows/Fonts/simhei.ttf',
    'C:/Windows/Fonts/simsun.ttc',
    'C:/Windows/Fonts/msyh.ttc',
    'C:/Windows/Fonts/Deng.ttf',
]

# Drop-shadow offset (in pixels). The English latin_normal.png font uses a
# 1px bottom-right shadow; replicate that for Chinese to match the style.
SHADOW_OFFSET_X = 1
SHADOW_OFFSET_Y = 1

# 2bpp pixel values
BG = 0
FG = 1
SHADOW = 2


def gb2312_to_index(b1, b2):
    """Convert GB2312 two-byte encoding to glyph index."""
    zone = b1 - 0x81
    pos = b2 - 0x40
    if b2 > 0x7F:
        pos -= 1
    return zone * POS_PER_ZONE + pos


def find_font():
    """Find an available Chinese TTF font."""
    for path in FONT_PATHS:
        if os.path.exists(path):
            return path
    return None


def _pixel_to_2bpp(pixel):
    """Convert grayscale pixel value to 2bpp.

    Pixel value 0 = BG, any non-zero value is kept as-is (FG=1 or SHADOW=2).
    """
    if pixel == 0:
        return BG
    return pixel if pixel in (FG, SHADOW) else FG


def _pack_4_pixels_to_byte(pixels):
    """Pack 4 pixels into one 2bpp byte.

    Standard GBA 2bpp packing (compatible with DecompressGlyphTile):
    bits 7-6 = pixel 0 (leftmost), bits 5-4 = pixel 1,
    bits 3-2 = pixel 2, bits 1-0 = pixel 3 (rightmost)
    """
    b = 0
    for i, p in enumerate(pixels):
        b |= (p & 0x3) << (6 - i * 2)
    return b


def render_glyph_2bpp(char, font, img, draw):
    """Render a single character to 16x16 2bpp bitmap with drop shadow.

    Returns:
        Tuple of (glyph_bytes, width) where glyph_bytes is 64 bytes
        of packed 2bpp data (4 tiles: TL, TR, BL, BR) and width is 12.
    """
    # Clear canvas
    draw.rectangle([0, 0, CANVAS_WIDTH - 1, CANVAS_HEIGHT - 1], fill=0)

    # Get bounding box for character
    bbox = draw.textbbox((0, 0), char, font=font)
    char_w = bbox[2] - bbox[0] if bbox[2] > bbox[0] else CHAR_WIDTH
    char_h = bbox[3] - bbox[1] if bbox[3] > bbox[1] else CHAR_HEIGHT

    # Center character in 12x12 region (offset 0,0 within 16x16 canvas)
    x_off = CHAR_OFFSET_X + (CHAR_WIDTH - char_w) // 2 - bbox[0]
    y_off = CHAR_OFFSET_Y + (CHAR_HEIGHT - char_h) // 2 - bbox[1]

    # Draw drop shadow first (bottom-right offset), then foreground on top.
    # FG (1) overwrites SHADOW (2) where they overlap, leaving a 1px shadow
    # on the bottom-right edge — matching the english latin_normal.png style.
    draw.text((x_off + SHADOW_OFFSET_X, y_off + SHADOW_OFFSET_Y), char,
              fill=SHADOW, font=font)
    draw.text((x_off, y_off), char, fill=FG, font=font)

    # Extract 16x16 pixel grid
    px = img.load()
    pixels = [[px[x, y] for x in range(CANVAS_WIDTH)] for y in range(CANVAS_HEIGHT)]

    # Convert to 2bpp values
    grid = [[_pixel_to_2bpp(p) for p in row] for row in pixels]

    # Pack into 4 tiles (TL, TR, BL, BR), each 8x8 = 16 bytes
    glyph_bytes = bytearray(BYTES_PER_GLYPH)
    tile_order = [
        (0, 0),   # Top-Left
        (1, 0),   # Top-Right
        (0, 1),   # Bottom-Left
        (1, 1),   # Bottom-Right
    ]

    for tile_idx, (tx, ty) in enumerate(tile_order):
        tile_offset = tile_idx * BYTES_PER_TILE
        base_x = tx * TILE_SIZE
        base_y = ty * TILE_SIZE
        for row in range(TILE_SIZE):
            y = base_y + row
            # 2 bytes per row. DecompressGlyphTile reads u16 as (lo_byte | hi_byte<<8),
            # then outputs u32 = (lookup[lo_byte] << 16) | lookup[hi_byte].
            # GLYPH_COPY reads u32 from low to high, so the high byte's pixels
            # (stored in u32 low 16 bits) are output first. To get correct
            # left-to-right pixel order (p0..p7), the FIRST byte in font data
            # must store the RIGHT half (pixels 4-7) and the SECOND byte must
            # store the LEFT half (pixels 0-3). This matches pret/pokeemerald's
            # convention for Japanese fonts (hwjpnfont/fwjpnfont).
            pixels_lo = grid[y][base_x:base_x + 4]      # left half (pixels 0-3)
            pixels_hi = grid[y][base_x + 4:base_x + 8]  # right half (pixels 4-7)
            byte_offset = tile_offset + row * 2
            glyph_bytes[byte_offset] = _pack_4_pixels_to_byte(pixels_hi)   # right half first
            glyph_bytes[byte_offset + 1] = _pack_4_pixels_to_byte(pixels_lo)  # left half second

    return bytes(glyph_bytes), FULL_WIDTH


def generate_font(glyph_path, width_path, font_path=None):
    """Generate the Chinese font files.

    Args:
        glyph_path: Output path for chinese.latfont
        width_path: Output path for chinese_widths.bin
        font_path: Optional TTF font path. If None, auto-detect.
    """
    if font_path is None:
        font_path = find_font()

    glyph_data = bytearray(TOTAL_SLOTS * BYTES_PER_GLYPH)
    width_data = bytearray(TOTAL_SLOTS)

    if font_path is None:
        print("Warning: No Chinese TTF font found. Generating empty placeholder.",
              file=sys.stderr)
        _write_files(glyph_path, width_path, glyph_data, width_data)
        return

    try:
        from PIL import Image, ImageDraw, ImageFont
    except ImportError:
        print("Error: PIL/Pillow not installed. Install with: pip install Pillow",
              file=sys.stderr)
        sys.exit(1)

    print(f"Loading font: {font_path}")
    # Render at 12px to fit in 12x12 region.
    # Use 'L' (8-bit grayscale) mode to support FG + SHADOW pixel values.
    font = ImageFont.truetype(font_path, CHAR_HEIGHT)
    img = Image.new('L', (CANVAS_WIDTH, CANVAS_HEIGHT), 0)
    draw = ImageDraw.Draw(img)

    count = 0
    for b1 in range(0x81, 0xFF):
        for b2 in range(0x40, 0xFF):
            if b2 == 0x7F:
                continue

            try:
                char = bytes([b1, b2]).decode('gb2312')
            except (UnicodeDecodeError, ValueError):
                continue

            glyph_bytes, width = render_glyph_2bpp(char, font, img, draw)

            idx = gb2312_to_index(b1, b2)
            offset = idx * BYTES_PER_GLYPH
            glyph_data[offset:offset + BYTES_PER_GLYPH] = glyph_bytes
            width_data[idx] = width
            count += 1

    _write_files(glyph_path, width_path, glyph_data, width_data)
    print(f"Generated {count} glyphs ({count * 100 // TOTAL_SLOTS}% of {TOTAL_SLOTS} slots)")


def _write_files(glyph_path, width_path, glyph_data, width_data):
    """Write the font data to files."""
    glyph_dir = os.path.dirname(glyph_path)
    if glyph_dir:
        os.makedirs(glyph_dir, exist_ok=True)
    width_dir = os.path.dirname(width_path)
    if width_dir:
        os.makedirs(width_dir, exist_ok=True)

    with open(glyph_path, 'wb') as f:
        f.write(glyph_data)
    with open(width_path, 'wb') as f:
        f.write(width_data)

    print(f"Glyph data: {len(glyph_data)} bytes -> {glyph_path}")
    print(f"Width data:  {len(width_data)} bytes -> {width_path}")


def main():
    if len(sys.argv) < 3:
        print(f"Usage: {sys.argv[0]} <output_glyphs> <output_widths>",
              file=sys.stderr)
        print(f"  e.g. {sys.argv[0]} graphics/fonts/chinese.latfont graphics/fonts/chinese_widths.bin",
              file=sys.stderr)
        sys.exit(1)

    glyph_path = sys.argv[1]
    width_path = sys.argv[2]
    font_path = sys.argv[3] if len(sys.argv) > 3 else None

    generate_font(glyph_path, width_path, font_path)


if __name__ == '__main__':
    main()
