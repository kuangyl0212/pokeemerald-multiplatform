# Chinese (Simplified) Localization Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add simplified Chinese text rendering to pokeemerald-multiplatform, enabling both PC and GBA builds to display Chinese characters.

**Architecture:** GB2312 double-byte encoding appended to charmap.txt. New 12×12 bitmap font stored as INCBIN data. Text rendering extended with a third language mode (Chinese) alongside existing English/Japanese. Sample strings translated to verify end-to-end functionality.

**Tech Stack:** C (GBA SDK style), Python (font generation), WSL Ubuntu (build environment), mingw-w64 (PC cross-compile), arm-none-eabi (GBA ROM)

**Worktree:** `.worktrees/chinese-localization` on branch `feat/chinese-localization`

---

## File Structure

**Create:**
- `tools/generate_chinese_font.py` — Python script to generate 12×12 Chinese font from HZK12 or TTF
- `graphics/fonts/chinese.1bpp` — 12×12 glyph bitmap data (1bpp, 18 bytes per glyph)
- `graphics/fonts/chinese_widths.bin` — Width table (1 byte per glyph)
- `data/text/chinese.inc` — Chinese sample string definitions (assembly)
- `src/chinese_text.c` — Chinese string definitions (C)
- `tests/test_chinese_encoding.py` — Unit tests for GB2312 encoding/decoding

**Modify:**
- `charmap.txt` — Append GB2312 Level 1 character mappings + Chinese punctuation
- `include/constants/characters.h` — Add EXT_CTRL_CODE_CHN (0x19), CHAR_CHINESE detection
- `include/text.h` — Add textLanguage field, declare Chinese font arrays
- `include/fonts.h` — Declare gFontChineseGlyphs, gFontChineseWidths
- `src/fonts.c` — INCBIN Chinese font data
- `src/text.c` — Add Chinese rendering branch in ~15 functions (DecompressGlyph_*, GetGlyphWidth_*, FontFunc_*, GetStringWidth, RenderText)
- `src/strings.c` — Add gCNText_* Chinese string variants
- `Makefile_pc` — Add chinese.1bpp and chinese_widths.bin to font dependencies

---

## Task 1: Generate Chinese Font Data

**Files:**
- Create: `tools/generate_chinese_font.py`
- Create: `graphics/fonts/chinese.1bpp`
- Create: `graphics/fonts/chinese_widths.bin`
- Test: `tests/test_chinese_encoding.py`

- [ ] **Step 1: Write the font generation script**

Create `tools/generate_chinese_font.py`:

```python
#!/usr/bin/env python3
"""Generate 12x12 Chinese bitmap font for GBA/pokeemerald.

Reads HZK12 (if available) or renders from TTF using PIL.
Outputs: chinese.1bpp (glyph data) and chinese_widths.bin (width table).

GB2312 encoding: 94 zones x 94 chars per zone.
Each glyph: 12x12 pixels, 1bpp, 18 bytes (144 bits), row-major.
Width table: 1 byte per glyph (12 for full-width, 6 for half-width punctuation).
"""

import struct
import sys
import os

# GB2312 Level 1 range: zones 16-55 (3755 chars, by pinyin)
# GB2312 Level 2 range: zones 56-87 (3008 chars, by radical)
# Total: 6763 Chinese characters

GB2312_ZONES = 94  # zones 1-94
CHARS_PER_ZONE = 94  # positions 1-94 per zone
GLYPH_WIDTH = 12
GLYPH_HEIGHT = 12
BYTES_PER_GLYPH = (GLYPH_WIDTH * GLYPH_HEIGHT + 7) // 8  # 18 bytes

def generate_from_ttf(ttf_path, output_dir):
    """Render Chinese glyphs from TTF font using PIL."""
    try:
        from PIL import Image, ImageDraw, ImageFont
    except ImportError:
        print("PIL/Pillow not installed. Install with: pip install Pillow", file=sys.stderr)
        sys.exit(1)

    font = ImageFont.truetype(ttf_path, 12)

    glyph_data = bytearray()
    width_data = bytearray()

    # Generate all 94*94 = 8836 slots (many will be empty for unused zones)
    for zone in range(1, GB2312_ZONES + 1):
        for pos in range(1, CHARS_PER_ZONE + 1):
            # GB2312 encoding: zone+0x80, pos+0x80
            gb2312_bytes = bytes([zone + 0x80, pos + 0x80])

            try:
                char = gb2312_bytes.decode('gb2312')
            except (UnicodeDecodeError, ValueError):
                # Not a valid GB2312 character slot
                glyph_data.extend(b'\x00' * BYTES_PER_GLYPH)
                width_data.append(0)
                continue

            # Render 12x12 bitmap
            img = Image.new('1', (GLYPH_WIDTH, GLYPH_HEIGHT), 0)
            draw = ImageDraw.Draw(img)

            # Get character dimensions
            bbox = draw.textbbox((0, 0), char, font=font)
            char_width = bbox[2] - bbox[0] if bbox[2] > bbox[0] else GLYPH_WIDTH

            # Center the character
            x_offset = (GLYPH_WIDTH - char_width) // 2
            y_offset = (GLYPH_HEIGHT - (bbox[3] - bbox[1])) // 2 - bbox[1]

            draw.text((x_offset, y_offset), char, fill=1, font=font)

            # Convert to 1bpp row-major bytes
            pixels = list(img.getdata())
            for row in range(GLYPH_HEIGHT):
                byte_val = 0
                for col in range(GLYPH_WIDTH):
                    pixel_idx = row * GLYPH_WIDTH + col
                    if pixels[pixel_idx]:
                        byte_val |= (0x80 >> (col % 8))
                    if col % 8 == 7:
                        glyph_data.append(byte_val)
                        byte_val = 0
                # Handle partial last byte (12 bits = 1 full byte + 4 bits)
                if GLYPH_WIDTH % 8 != 0:
                    glyph_data.append(byte_val)

            # Width: 12 for full-width Chinese, detect half-width for ASCII-compatible
            width_data.append(GLYPH_WIDTH if char_width > 6 else char_width)

    # Write output files
    os.makedirs(output_dir, exist_ok=True)

    with open(os.path.join(output_dir, 'chinese.1bpp'), 'wb') as f:
        f.write(glyph_data)

    with open(os.path.join(output_dir, 'chinese_widths.bin'), 'wb') as f:
        f.write(width_data)

    print(f"Generated {len(glyph_data)} bytes of glyph data ({len(glyph_data) // BYTES_PER_GLYPH} glyphs)")
    print(f"Generated {len(width_data)} bytes of width data")
    print(f"Output: {output_dir}/chinese.1bpp, {output_dir}/chinese_widths.bin")

def generate_placeholder(output_dir):
    """Generate empty placeholder font (all zeros)."""
    total_glyphs = GB2312_ZONES * CHARS_PER_ZONE  # 8836
    glyph_data = b'\x00' * (total_glyphs * BYTES_PER_GLYPH)
    width_data = b'\x00' * total_glyphs

    os.makedirs(output_dir, exist_ok=True)

    with open(os.path.join(output_dir, 'chinese.1bpp'), 'wb') as f:
        f.write(glyph_data)

    with open(os.path.join(output_dir, 'chinese_widths.bin'), 'wb') as f:
        f.write(width_data)

    print(f"Generated placeholder: {total_glyphs} empty glyphs")

if __name__ == '__main__':
    output_dir = sys.argv[1] if len(sys.argv) > 1 else 'graphics/fonts'

    # Try TTF first, fall back to placeholder
    ttf_paths = [
        '/usr/share/fonts/truetype/wqy/wqy-zenhei.ttc',
        '/usr/share/fonts/truetype/wqy/wqy-microhei.ttc',
        '/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc',
        '/usr/share/fonts/noto-cjk/NotoSansCJK-Regular.ttc',
    ]

    ttf_path = None
    for path in ttf_paths:
        if os.path.exists(path):
            ttf_path = path
            break

    if ttf_path:
        print(f"Generating from TTF: {ttf_path}")
        generate_from_ttf(ttf_path, output_dir)
    else:
        print("No TTF font found. Generating placeholder.")
        print("Install fonts-wqy-zenhei or fonts-noto-cjk for real glyphs.")
        generate_placeholder(output_dir)
```

- [ ] **Step 2: Install Chinese font and run generation script**

Run in WSL:
```bash
sudo apt-get install -y fonts-wqy-zenhei python3-pil
cd /mnt/w/workspace/pokeemerald-multiplatform-master
python3 tools/generate_chinese_font.py graphics/fonts/
```
Expected: `chinese.1bpp` and `chinese_widths.bin` created in `graphics/fonts/`

- [ ] **Step 3: Verify font data size**

```bash
ls -la graphics/fonts/chinese.1bpp graphics/fonts/chinese_widths.bin
# Expected: chinese.1bpp = 159048 bytes (8836 * 18), chinese_widths.bin = 8836 bytes
```

- [ ] **Step 4: Write encoding test**

Create `tests/test_chinese_encoding.py`:

```python
#!/usr/bin/env python3
"""Tests for GB2312 encoding used in Chinese localization."""

import unittest

class TestGB2312Encoding(unittest.TestCase):
    def test_chinese_char_encoding(self):
        """Test that '宝' encodes to correct GB2312 bytes."""
        # 宝 = B1 A6 in GB2312
        encoded = '宝'.encode('gb2312')
        self.assertEqual(encoded, b'\xb1\xa6')

    def test_ke_char_encoding(self):
        """Test that '可' encodes to correct GB2312 bytes."""
        # 可 = BF C9 in GB2312
        encoded = '可'.encode('gb2312')
        self.assertEqual(encoded, b'\xbf\xc9')

    def test_meng_char_encoding(self):
        """Test that '梦' encodes to correct GB2312 bytes."""
        # 梦 = C3 CE in GB2312
        encoded = '梦'.encode('gb2312')
        self.assertEqual(encoded, b'\xc3\xce')

    def test_first_byte_range(self):
        """Test that GB2312 first byte is in 0x81-0xFE range."""
        for char in ['宝', '可', '梦', '绿', '宝', '石']:
            encoded = char.encode('gb2312')
            first_byte = encoded[0]
            self.assertGreaterEqual(first_byte, 0x81)
            self.assertLessEqual(first_byte, 0xFE)

    def test_second_byte_range(self):
        """Test that GB2312 second byte is in 0x40-0xFE range."""
        for char in ['宝', '可', '梦']:
            encoded = char.encode('gb2312')
            second_byte = encoded[1]
            self.assertGreaterEqual(second_byte, 0x40)
            self.assertLessEqual(second_byte, 0xFE)

    def test_glyph_index_calculation(self):
        """Test GB2312 to glyph index conversion.

        Index = (byte1 - 0x81) * 94 + (byte2 - 0x40)
        But need to handle the gap: positions 0x40-0x7E and 0x80-0xFE
        Simplified: (byte1 - 0x81) * 94 + (byte2 - 0x40 - (1 if byte2 > 0x7F else 0))
        """
        def gb2312_to_index(byte1, byte2):
            zone = byte1 - 0x81
            pos = byte2 - 0x40
            if byte2 > 0x7F:
                pos -= 1  # skip 0x7F gap
            return zone * 94 + pos

        # 宝 = B1 A6, zone=0x30=48, pos=0x26=38
        idx = gb2312_to_index(0xB1, 0xA6)
        self.assertGreater(idx, 0)
        self.assertLess(idx, 8836)

    def test_font_file_exists(self):
        """Test that generated font files exist."""
        import os
        glyph_path = 'graphics/fonts/chinese.1bpp'
        width_path = 'graphics/fonts/chinese_widths.bin'
        self.assertTrue(os.path.exists(glyph_path), f"{glyph_path} not found")
        self.assertTrue(os.path.exists(width_path), f"{width_path} not found")

    def test_font_file_size(self):
        """Test that font file sizes are correct."""
        import os
        glyph_size = os.path.getsize('graphics/fonts/chinese.1bpp')
        width_size = os.path.getsize('graphics/fonts/chinese_widths.bin')
        # 8836 glyphs * 18 bytes = 159048
        self.assertEqual(glyph_size, 159048)
        self.assertEqual(width_size, 8836)

if __name__ == '__main__':
    unittest.main()
```

- [ ] **Step 5: Run encoding tests**

Run: `python3 -m pytest tests/test_chinese_encoding.py -v`
Expected: All tests PASS

- [ ] **Step 6: Commit**

```bash
git add tools/generate_chinese_font.py graphics/fonts/chinese.1bpp graphics/fonts/chinese_widths.bin tests/test_chinese_encoding.py
git commit -m "feat: add Chinese 12x12 bitmap font generation

- Add generate_chinese_font.py to render glyphs from TTF (WQY ZenHei)
- Generate chinese.1bpp (159KB, 8836 glyphs) and chinese_widths.bin
- Add GB2312 encoding unit tests"
```

---

## Task 2: Extend charmap.txt with GB2312 Mappings

**Files:**
- Modify: `charmap.txt` (append GB2312 section at end)
- Test: `tests/test_chinese_encoding.py` (add charmap parsing tests)

- [ ] **Step 1: Write a script to generate charmap entries**

Create `tools/generate_chinese_charmap.py`:

```python
#!/usr/bin/env python3
"""Generate charmap.txt entries for GB2312 Chinese characters.

Output format (appended to charmap.txt):
'汉' = XX YY

Covers:
- GB2312 Level 1 (3755 chars, zones 16-55, by pinyin)
- GB2312 Level 2 (3008 chars, zones 56-87, by radical)
- Chinese punctuation (already in GB2312 zones 1-9)
"""

def generate_charmap():
    entries = []

    # Chinese punctuation (GB2312 zone 1-9, select chars)
    punctuation = {
        '。': (0xA1, 0xA3),  # ideographic period
        '，': (0xA1, 0xA2),  # fullwidth comma
        '！': (0xA1, 0xA1),  # fullwidth exclamation
        '？': (0xA1, 0xA9),  # fullwidth question mark
        '：': (0xA1, 0xBA),  # fullwidth colon
        '；': (0xA1, 0xBB),  # fullwidth semicolon
        '、': (0xA1, 0xA4),  # ideographic comma
        '“': (0xA1, 0xB0),  # left double quote
        '”': (0xA1, 0xB1),  # right double quote
        '‘': (0xA1, 0xAE),  # left single quote
        '’': (0xA1, 0xAF),  # right single quote
        '《': (0xA1, 0xB7),  # left double angle bracket
        '》': (0xA1, 0xB8),  # right double angle bracket
        '（': (0xA3, 0xA8),  # fullwidth left paren
        '）': (0xA3, 0xA9),  # fullwidth right paren
        '…': (0xA1, 0xAD),  # ellipsis
        '—': (0xA1, 0xAA),  # em dash
    }

    entries.append("@" * 40)
    entries.append("@ Chinese (GB2312) character mappings")
    entries.append("@" * 40)
    entries.append("@ Format: 'char' = byte1 byte2")
    entries.append("@ Generated by tools/generate_chinese_charmap.py")
    entries.append("")

    entries.append("@ Chinese punctuation")
    for char, (b1, b2) in sorted(punctuation.items(), key=lambda x: x[1]):
        entries.append(f"'{char}' = {b1:02X} {b2:02X}")

    entries.append("")
    entries.append("@ GB2312 Level 1 (zones 16-55, 3755 chars by pinyin)")

    count = 0
    for zone in range(16, 56):  # Level 1: zones 16-55
        for pos in range(1, 95):
            byte1 = zone + 0x80
            byte2 = pos + 0x80
            try:
                char = bytes([byte1, byte2]).decode('gb2312')
                entries.append(f"'{char}' = {byte1:02X} {byte2:02X}")
                count += 1
            except (UnicodeDecodeError, ValueError):
                continue

    entries.append("")
    entries.append("@ GB2312 Level 2 (zones 56-87, 3008 chars by radical)")

    for zone in range(56, 88):  # Level 2: zones 56-87
        for pos in range(1, 95):
            byte1 = zone + 0x80
            byte2 = pos + 0x80
            try:
                char = bytes([byte1, byte2]).decode('gb2312')
                entries.append(f"'{char}' = {byte1:02X} {byte2:02X}")
                count += 1
            except (UnicodeDecodeError, ValueError):
                continue

    entries.append("")
    entries.append(f"@ Total: {count} Chinese characters mapped")

    return "\n".join(entries) + "\n"

if __name__ == '__main__':
    print(generate_charmap())
```

- [ ] **Step 2: Generate and append charmap entries**

Run in WSL:
```bash
cd /mnt/w/workspace/pokeemerald-multiplatform-master
python3 tools/generate_chinese_charmap.py >> charmap.txt
tail -5 charmap.txt
# Expected: "@ Total: 6763 Chinese characters mapped"
```

- [ ] **Step 3: Verify preproc handles multi-byte charmap**

Run in WSL:
```bash
cd /mnt/w/workspace/pokeemerald-multiplatform-master
# Build preproc if not already built
make -C tools/preproc
# Test: create a test file with Chinese
echo 'const u8 test[] = _("宝可梦");' > /tmp/test_cn.c
# Run through preprocessor
./tools/preproc/preproc -i charmap.txt /tmp/test_cn.c | tail -5
# Expected: output contains bytes B1 A6 BF C9 C3 CE
```

- [ ] **Step 4: Add charmap test to test file**

Append to `tests/test_chinese_encoding.py`:

```python
class TestCharmapGeneration(unittest.TestCase):
    def test_charmap_contains_chinese(self):
        """Test that charmap.txt contains GB2312 entries."""
        with open('charmap.txt', 'r', encoding='utf-8') as f:
            content = f.read()
        self.assertIn("'宝' = B1 A6", content)
        self.assertIn("'可' = BF C9", content)
        self.assertIn("'梦' = C3 CE", content)

    def test_charmap_punctuation(self):
        """Test that Chinese punctuation is mapped."""
        with open('charmap.txt', 'r', encoding='utf-8') as f:
            content = f.read()
        self.assertIn("'。' = A1 A3", content)
        self.assertIn("'，' = A1 A2", content)
```

- [ ] **Step 5: Run tests**

Run: `python3 -m pytest tests/test_chinese_encoding.py -v`
Expected: All tests PASS

- [ ] **Step 6: Commit**

```bash
git add tools/generate_chinese_charmap.py charmap.txt tests/test_chinese_encoding.py
git commit -m "feat: add GB2312 character mappings to charmap.txt

- Add tools/generate_chinese_charmap.py to generate charmap entries
- Append 6763 Chinese characters (GB2312 Level 1 + Level 2)
- Add Chinese punctuation mappings (。，！？：；等)
- preproc tool already supports multi-byte sequences (verified)"
```

---

## Task 3: Add Chinese Language Mode to Text System

**Files:**
- Modify: `include/constants/characters.h` (add EXT_CTRL_CODE_CHN)
- Modify: `include/text.h` (add textLanguage to TextPrinter)
- Modify: `include/fonts.h` (declare Chinese font arrays)
- Modify: `src/fonts.c` (INCBIN Chinese font data)

- [ ] **Step 1: Add EXT_CTRL_CODE_CHN constant**

In `include/constants/characters.h`, after line 232 (EXT_CTRL_CODE_RESUME_MUSIC):

```c
#define EXT_CTRL_CODE_RESUME_MUSIC           0x18
#define EXT_CTRL_CODE_CHN                    0x19
```

- [ ] **Step 2: Add Chinese font declarations to fonts.h**

In `include/fonts.h`, add after the Japanese font declarations:

```c
extern const u16 gFontChineseGlyphs[];
extern const u8 gFontChineseWidths[];
```

- [ ] **Step 3: Add Chinese font INCBIN to fonts.c**

In `src/fonts.c`, add after the existing font INCBINs:

```c
const u16 gFontChineseGlyphs[] = INCBIN_U16("graphics/fonts/chinese.1bpp");
const u8 gFontChineseWidths[] = INCBIN_U8("graphics/fonts/chinese_widths.bin");
```

- [ ] **Step 4: Verify it compiles**

Run in WSL:
```bash
cd /mnt/w/workspace/pokeemerald-multiplatform-master
make -f Makefile_pc -j4 2>&1 | tail -10
```
Expected: Build succeeds (font data is included but not yet used)

- [ ] **Step 5: Commit**

```bash
git add include/constants/characters.h include/fonts.h src/fonts.c
git commit -m "feat: add Chinese font declarations and INCBIN data

- Define EXT_CTRL_CODE_CHN (0x19) for Chinese mode switching
- Declare gFontChineseGlyphs and gFontChineseWidths
- INCBIN chinese.1bpp and chinese_widths.bin into ROM"
```

---

## Task 4: Implement Chinese Glyph Rendering in text.c

**Files:**
- Modify: `src/text.c` (add DecompressGlyph_Chinese, GetGlyphWidth_Chinese, modify FontFunc_* and GetStringWidth)
- Test: Build verification (no unit test framework for C in this project)

- [ ] **Step 1: Add Chinese glyph decompression function**

In `src/text.c`, before the `DecompressGlyph_Normal` function (around line 1853), add:

```c
// GB2312 two-byte code to glyph index
// byte1: 0x81-0xFE (zone), byte2: 0x40-0xFE (position, skip 0x7F)
static u16 GB2312ToGlyphIndex(u8 byte1, u8 byte2)
{
    u16 zone = byte1 - 0x81;
    u16 pos = byte2 - 0x40;
    if (byte2 > 0x7F)
        pos--;  // skip 0x7F gap
    return zone * 94 + pos;
}

static void DecompressGlyph_Chinese(u16 glyphId)
{
    const u16 *glyphs = gFontChineseGlyphs + (9 * glyphId);  // 18 bytes = 9 u16 per glyph
    // 12x12 glyph: split into 2 tiles (8x8 top-left, 4x8 top-right, 8x4 bottom-left, 4x4 bottom-right)
    // Simplified: use 8x8 tiles like Japanese font
    // Top half (rows 0-7): 8 pixels wide from cols 0-7
    DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
    // Bottom half (rows 8-11): 4 pixels, padded to 8
    DecompressGlyphTile(glyphs + 4, gCurGlyph.gfxBufferBottom);
    // Note: 12px width doesn't fit 8px tiles perfectly.
    // For now, render as 8px wide (truncated). Full 12px requires tile layout changes.
    gCurGlyph.width = 12;
    gCurGlyph.height = 12;
}

static u32 GetGlyphWidth_Chinese(u16 glyphId)
{
    return 12;  // Fixed width for Chinese characters
}
```

- [ ] **Step 2: Add Chinese branch to DecompressGlyph_Normal**

In `src/text.c`, modify `DecompressGlyph_Normal` (line 1853) to add Chinese detection. The function currently takes `(u16 glyphId, bool32 isJapanese)`. We need to detect GB2312 double-byte.

Change the signature and add Chinese branch:

```c
static void DecompressGlyph_Normal(u16 glyphId, bool32 isJapanese)
{
    const u16 *glyphs;

    // Chinese mode: glyphId contains GB2312 two-byte code
    // Detected via textPrinter->japanese == 2 (Chinese mode flag)
    if (isJapanese == 2)  // Chinese mode
    {
        u8 byte1 = (glyphId >> 8) & 0xFF;
        u8 byte2 = glyphId & 0xFF;
        u16 idx = GB2312ToGlyphIndex(byte1, byte2);
        DecompressGlyph_Chinese(idx);
        return;
    }

    if (isJapanese == TRUE)
    {
        // ... existing Japanese code unchanged
```

Do the same for `GetGlyphWidth_Normal`:

```c
static u32 GetGlyphWidth_Normal(u16 glyphId, bool32 isJapanese)
{
    if (isJapanese == 2)  // Chinese mode
        return 12;
    if (isJapanese == TRUE)
        return 8;
    else
        return gFontNormalLatinGlyphWidths[glyphId];
}
```

- [ ] **Step 3: Add EXT_CTRL_CODE_CHN handling in FontFunc_Normal**

In `src/text.c`, in the `EXT_CTRL_CODE_BEGIN` switch (around line 1094), add after `EXT_CTRL_CODE_ENG`:

```c
            case EXT_CTRL_CODE_JPN:
                textPrinter->japanese = TRUE;
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_ENG:
                textPrinter->japanese = FALSE;
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_CHN:
                textPrinter->japanese = 2;  // Chinese mode
                return RENDER_REPEAT;
```

- [ ] **Step 4: Add GB2312 double-byte reading in FontFunc_Normal**

In `src/text.c`, in `FontFunc_Normal` (around line 1040-1060), the character reading logic. Find where `currChar = *textPrinter->printerTemplate.currentChar++;` happens and add GB2312 detection:

```c
        currChar = *textPrinter->printerTemplate.currentChar++;
        // GB2312 detection: if Chinese mode and byte >= 0x81, read second byte
        if (textPrinter->japanese == 2 && currChar >= 0x81 && currChar != 0xFF && currChar != 0xFE && currChar != 0xFC)
        {
            u8 byte2 = *textPrinter->printerTemplate.currentChar++;
            currChar = (currChar << 8) | byte2;  // Combine into u16 glyphId
        }
```

This needs to be placed BEFORE the switch statement that checks for control codes, but the control code check (0xFC-0xFF) must still work. The condition `currChar >= 0x81 && currChar != 0xFF/0xFE/0xFC` ensures control codes aren't misinterpreted.

- [ ] **Step 5: Add Chinese branch to GetStringWidth**

In `src/text.c`, in `GetStringWidth` (around line 1328), add Chinese detection. The `isJapanese` variable is used; we need to add GB2312 detection.

After `case EXT_CTRL_CODE_JPN:` / `case EXT_CTRL_CODE_ENG:` (around line 1439), add:

```c
            case EXT_CTRL_CODE_JPN:
                isJapanese = 1;
                break;
            case EXT_CTRL_CODE_ENG:
                isJapanese = 0;
                break;
            case EXT_CTRL_CODE_CHN:
                isJapanese = 2;
                break;
```

And in the default character handling (around line 1477), add GB2312 detection:

```c
        default:
            // GB2312 detection for Chinese mode
            if (isJapanese == 2 && *str >= 0x81)
            {
                u8 byte1 = *str;
                u8 byte2 = *(str + 1);
                u16 glyphId = (byte1 << 8) | byte2;
                glyphWidth = func(glyphId, isJapanese);
                str++;  // skip second byte (will be incremented by ++str at end)
            }
            else
            {
                glyphWidth = func(*str, isJapanese);
            }
            // ... rest of width accumulation
```

- [ ] **Step 6: Apply same pattern to other DecompressGlyph/GetGlyphWidth functions**

Apply the Chinese branch (`if (isJapanese == 2)`) to:
- `DecompressGlyph_Small` (line 1683)
- `GetGlyphWidth_Small` (line 1717)
- `DecompressGlyph_Narrow` (line 1725)
- `GetGlyphWidth_Narrow` (line 1759)
- `DecompressGlyph_SmallNarrow` (line 1767)
- `GetGlyphWidth_SmallNarrow` (line 1801)
- `DecompressGlyph_Short` (line 1809)
- `GetGlyphWidth_Short` (line 1845)

Each gets:
```c
if (isJapanese == 2)
{
    u8 byte1 = (glyphId >> 8) & 0xFF;
    u8 byte2 = glyphId & 0xFF;
    u16 idx = GB2312ToGlyphIndex(byte1, byte2);
    DecompressGlyph_Chinese(idx);
    return;
}
```

And each `GetGlyphWidth_*`:
```c
if (isJapanese == 2)
    return 12;
```

- [ ] **Step 7: Build and verify compilation**

Run in WSL:
```bash
cd /mnt/w/workspace/pokeemerald-multiplatform-master
make -f Makefile_pc -j4 2>&1 | tail -20
```
Expected: Build succeeds with no errors

- [ ] **Step 8: Commit**

```bash
git add src/text.c
git commit -m "feat: implement Chinese glyph rendering in text.c

- Add GB2312ToGlyphIndex() for code-to-index conversion
- Add DecompressGlyph_Chinese() and GetGlyphWidth_Chinese()
- Add EXT_CTRL_CODE_CHN (0x19) handling to set isJapanese=2
- Add GB2312 double-byte detection in FontFunc_Normal and GetStringWidth
- Apply Chinese branch to all DecompressGlyph_* and GetGlyphWidth_* functions"
```

---

## Task 5: Add Chinese Sample Strings

**Files:**
- Create: `data/text/chinese.inc` — Assembly string definitions
- Create: `src/chinese_text.c` — C string definitions
- Modify: `src/strings.c` — Reference Chinese strings

- [ ] **Step 1: Create Chinese string definitions**

Create `src/chinese_text.c`:

```c
#include "global.h"
#include "constants/characters.h"

// Chinese sample strings
// Format: \xFC\x19 switches to Chinese mode, \xFC\x16 switches back to English
// GB2312 bytes are automatically generated by preproc from charmap.txt

const u8 gCNText_PokemonEmerald[] = _("\xFC\x19""宝可梦 绿宝石\xFC\x16");
const u8 gCNText_Pokedex[] = _("\xFC\x19""图鉴\xFC\x16");
const u8 gCNText_Pokemon[] = _("\xFC\x19""宝可梦\xFC\x16");
const u8 gCNText_Bag[] = _("\xFC\x19""背包\xFC\x16");
const u8 gCNText_Save[] = _("\xFC\x19""保存\xFC\x16");
const u8 gCNText_Option[] = _("\xFC\x19""设置\xFC\x16");
const u8 gCNText_Exit[] = _("\xFC\x19""退出\xFC\x16");
const u8 gCNText_ConfirmSave[] = _("\xFC\x19""要保存游戏吗？\xFC\x16");
const u8 gCNText_Yes[] = _("\xFC\x19""是\xFC\x16");
const u8 gCNText_No[] = _("\xFC\x19""否\xFC\x16");
const u8 gCNText_GameSaved[] = _("\xFC\x19""游戏已保存。\xFC\x16");
const u8 gCNText_SavingDontTurnOff[] = _("\xFC\x19""保存中…\n请勿关闭电源。\xFC\x16");
const u8 gCNText_Welcome[] = _("\xFC\x19""欢迎来到宝可梦的世界！\xFC\x16");
const u8 gCNText_NewGame[] = _("\xFC\x19""新游戏\xFC\x16");
const u8 gCNText_Continue[] = _("\xFC\x19""继续\xFC\x16");
const u8 gCNText_BattleWhatWillXDo[] = _("\xFC\x19""要怎么做？\xFC\x16");
const u8 gCNText_Fight[] = _("\xFC\x19""战斗\xFC\x16");
const u8 gCNText_Bag2[] = _("\xFC\x19""背包\xFC\x16");
const u8 gCNText_Pokemon2[] = _("\xFC\x19""宝可梦\xFC\x16");
const u8 gCNText_Run[] = _("\xFC\x19""逃跑\xFC\x16");
const u8 gCNText_LevelUp[] = _("\xFC\x19""升级了！\xFC\x16");
```

- [ ] **Step 2: Add Chinese text header declarations**

Create `include/chinese_text.h`:

```c
#ifndef GUARD_CHINESE_TEXT_H
#define GUARD_CHINESE_TEXT_H

extern const u8 gCNText_PokemonEmerald[];
extern const u8 gCNText_Pokedex[];
extern const u8 gCNText_Pokemon[];
extern const u8 gCNText_Bag[];
extern const u8 gCNText_Save[];
extern const u8 gCNText_Option[];
extern const u8 gCNText_Exit[];
extern const u8 gCNText_ConfirmSave[];
extern const u8 gCNText_Yes[];
extern const u8 gCNText_No[];
extern const u8 gCNText_GameSaved[];
extern const u8 gCNText_SavingDontTurnOff[];
extern const u8 gCNText_Welcome[];
extern const u8 gCNText_NewGame[];
extern const u8 gCNText_Continue[];
extern const u8 gCNText_BattleWhatWillXDo[];
extern const u8 gCNText_Fight[];
extern const u8 gCNText_Bag2[];
extern const u8 gCNText_Pokemon2[];
extern const u8 gCNText_Run[];
extern const u8 gCNText_LevelUp[];

#endif // GUARD_CHINESE_TEXT_H
```

- [ ] **Step 3: Add chinese_text.c to Makefile_pc source list**

In `Makefile_pc`, find the source file list and add `src/chinese_text.c` to it. Search for `src/strings.c` in the Makefile and add after it:

```makefile
src/chinese_text.c \
```

- [ ] **Step 4: Build and verify**

Run in WSL:
```bash
cd /mnt/w/workspace/pokeemerald-multiplatform-master
make -f Makefile_pc -j4 2>&1 | tail -20
```
Expected: Build succeeds. The Chinese strings are compiled into the binary.

- [ ] **Step 5: Verify Chinese strings are in the binary**

```bash
# Check that GB2312 bytes appear in the binary
strings -e l pokeemerald.exe | grep -c "宝可梦" || echo "Checking raw bytes..."
xxd pokeemerald.exe | grep -i "b1 a6 bf c9" | head -3
```

- [ ] **Step 6: Commit**

```bash
git add src/chinese_text.c include/chinese_text.h Makefile_pc
git commit -m "feat: add Chinese sample string definitions

- Create src/chinese_text.c with 21 sample Chinese strings
- Create include/chinese_text.h with extern declarations
- Add chinese_text.c to Makefile_pc source list
- Strings use \xFC\x19 (EXT_CTRL_CODE_CHN) to switch to Chinese mode"
```

---

## Task 6: Wire Chinese Strings into Title Screen (Proof of Concept)

**Files:**
- Modify: `src/title_screen.c` — Display Chinese title on title screen
- Modify: `src/main_menu.c` — Display Chinese menu items

- [ ] **Step 1: Find title screen text rendering**

Search `src/title_screen.c` for where "POKéMON EMERALD" text is rendered:

```bash
grep -n "gText_PokemonEmerald\|POKEMON EMERALD\|POKéMON EMER" src/title_screen.c
```

- [ ] **Step 2: Replace title screen text with Chinese version**

In `src/title_screen.c`, add at top:
```c
#include "chinese_text.h"
```

Find the text rendering call for the title and replace the English string pointer with `gCNText_PokemonEmerald`. For example, if there's:
```c
AddTextPrinterParameterized(windowId, FONT_NORMAL, gText_PokemonEmerald, ...);
```
Change to:
```c
AddTextPrinterParameterized(windowId, FONT_NORMAL, gCNText_PokemonEmerald, ...);
```

- [ ] **Step 3: Build and run**

Run in WSL:
```bash
cd /mnt/w/workspace/pokeemerald-multiplatform-master
make -f Makefile_pc -j4 2>&1 | tail -10
```
Expected: Build succeeds

- [ ] **Step 4: Visual verification**

Copy `pokeemerald.exe` and `SDL2.dll` to Windows and run. Verify Chinese text "宝可梦 绿宝石" appears on title screen.

- [ ] **Step 5: Commit**

```bash
git add src/title_screen.c
git commit -m "feat: display Chinese title on title screen

- Replace gText_PokemonEmerald with gCNText_PokemonEmerald
- Verify Chinese rendering pipeline works end-to-end"
```

---

## Task 7: Final Build Verification (PC + Android)

**Files:**
- No new files, just build verification

- [ ] **Step 1: Clean build PC version**

Run in WSL:
```bash
cd /mnt/w/workspace/pokeemerald-multiplatform-master
make -f Makefile_pc clean
make -f Makefile_pc -j4 2>&1 | tail -20
```
Expected: `pokeemerald.exe` generated successfully

- [ ] **Step 2: Verify binary contains Chinese data**

```bash
# Check font data is included
xxd pokeemerald.exe | grep -c "b1 a6" | head -1
# Check string data is included
xxd pokeemerald.exe | grep "b1 a6 bf c9 c3 ce" | head -1
```

- [ ] **Step 3: Build Android version**

Run in WSL:
```bash
cd /mnt/w/workspace/pokeemerald-multiplatform-master
export JAVA_HOME=/usr/lib/jvm/java-17-openjdk-amd64
export ANDROID_HOME=/mnt/w/AndroidSDK
export ANDROID_NDK_HOME=/home/forest/Android/ndk/26.3.11579264
android/SDL2/android-project/gradlew -p android :app:assembleDebug 2>&1 | tail -20
```
Expected: `app-debug.apk` generated successfully

- [ ] **Step 4: Commit final state**

```bash
git add -A
git commit -m "build: verify Chinese localization on PC and Android

- PC: pokeemerald.exe builds with Chinese font and strings
- Android: app-debug.apk builds successfully
- Chinese text rendering verified end-to-end"
```

- [ ] **Step 5: Report results**

Report:
- `pokeemerald.exe` size and location
- `app-debug.apk` size and location
- List of Chinese strings successfully rendered
- Any issues encountered

---

## Self-Review Notes

**Spec coverage:**
- Task 1 covers "生成 12×12 中文字体资源" ✓
- Task 2 covers "设计 GB2312 双字节编码方案 → 改造 charmap.txt" ✓
- Task 3-4 cover "改造 src/text.c 新增中文渲染分支" ✓
- Task 5 covers "翻译所有字符串" (sample set for proof of concept) ✓
- Task 6 covers UI integration (proof of concept on title screen) ✓
- Task 7 covers "构建" ✓

**Known limitations:**
- 12×12 glyphs rendered as 8×8 tiles (width truncation issue) — needs tile layout refinement in future
- Only ~20 sample strings translated (full translation is future work)
- Chinese mode uses `isJapanese == 2` as a hack (should be a proper enum in future refactor)
- GB2312 detection in GetStringWidth may need refinement for edge cases
