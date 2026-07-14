# Chinese (Simplified) Localization Design

## Overview

Add simplified Chinese text rendering support to pokeemerald-multiplatform. This enables both GBA ROM and PC (Windows/Android) builds to display Chinese text.

## Scope

**Phase 1 (this implementation):** Foundational infrastructure + proof of concept
- GB2312 double-byte encoding in charmap.txt
- 12×12 Chinese font generation and integration
- text.c rendering branch for Chinese characters
- Sample string translations to verify end-to-end display
- Build verification on PC platform

**Out of scope (future work):**
- Full translation of all game strings (thousands of strings)
- Complete UI layout adjustments for all screens
- Traditional Chinese support

## Architecture

### 1. Encoding: GB2312 Double-Byte

**Decision:** Use GB2312 encoding for Chinese characters.

**Rationale:**
- GB2312 covers 6763 Chinese characters (sufficient for game text)
- Well-established in GBA modding community
- Double-byte format: first byte 0x81-0xFE, second byte 0x40-0xFE
- Existing single-byte encodings (English/Japanese/control codes) remain unchanged
- GB2312 first byte (≥0x81) does not conflict with existing charmap values (0x00-0xFF control codes are single-byte)

**charmap.txt changes:**
- Append GB2312 character mappings at end of file
- Format: `'汉字' = XX YY` (two-byte sequence)
- Cover GB2312 Level 1 (3755 most common characters) as minimum
- Chinese punctuation (。，！？：；""''《》（）…) mapped explicitly

**Detection logic:** In text.c, when reading a character, if first byte ≥ 0x81, read second byte and combine as GB2312 code. This requires modifying all character-reading loops.

### 2. Font System: 12×12 Bitmap

**Decision:** Generate 12×12 pixel bitmap font from open-source HZK12 font data.

**Font format:** New `.cnfont` format (custom), storing:
- Glyph data: 12×12 = 144 bits = 18 bytes per glyph (1bpp)
- Width table: 1 byte per glyph (fixed 12 for full-width, 6 for half-width punctuation)
- Organized by GB2312 code (94×94 grid, row-major)

**Font storage in ROM:**
- `gFontChineseGlyphs[]`: Array of u16, INCBIN_U16 from `.cnfont` file
- `gFontChineseWidths[]`: Array of u8, width per glyph
- Stored similar to existing `gFontNormalJapaneseGlyphs`

**Font rendering:** New `DecompressGlyph_Chinese()` function in text.c:
- Input: GB2312 two-byte code
- Convert to glyph index: `(byte1 - 0x81) * 94 + (byte2 - 0x40)` (simplified, need to handle 0x40-0x7E and 0x80-0xFE ranges)
- Each glyph: 12×12 pixels, rendered as 2 tiles (8×8 + 4×8 or similar split)
- Fixed width 12 pixels (full-width)

### 3. Text Rendering: Triple-Branch

**Decision:** Extend existing `isJapanese` binary branch to a ternary `textLanguage` state.

**Current state:** `isJapanese` flag (0 or 1), toggled by EXT_CTRL_CODE_JPN (0xFC 0x15) / EXT_CTRL_CODE_ENG (0xFC 0x16)

**New state:** `textLanguage` enum (LANGUAGE_ENGLISH, LANGUAGE_JAPANESE, LANGUAGE_CHINESE)
- New control code: EXT_CTRL_CODE_CHN (0xFC 0x17) to switch to Chinese mode
- Existing ENG/JPN codes remain functional
- In Chinese mode:
  - Character reading: detect GB2312 double-byte sequences
  - Glyph lookup: use `gFontChineseGlyphs` table
  - Width: fixed 12 pixels per Chinese character
  - Decompression: new `DecompressGlyph_Chinese` function

**Files to modify:**
- `src/text.c`: Core rendering functions (~15 functions need Chinese branch)
- `include/text.h`: Add LANGUAGE_CHINESE enum, EXT_CTRL_CODE_CHN
- `include/fonts.h`: Declare Chinese font arrays
- `src/fonts.c`: Define Chinese font INCBIN
- `include/constants/characters.h`: Add Chinese character constants

### 4. String Translation: Sample Set

**Decision:** Translate a representative sample of strings to verify end-to-end functionality.

**Sample set (~20 strings):**
- Title screen: "POKéMON EMERALD" → "宝可梦 绿宝石"
- Menu items: "POKéDEX", "POKéMON", "BAG", "SAVE", "OPTION" → Chinese equivalents
- System messages: "Would you like to save the game?" → "要保存游戏吗？"
- Battle messages: "What will X do?" → "X要怎么做？"

**Translation files:**
- `data/text/chinese.inc`: New file with Chinese string definitions
- `src/strings.c`: Add Chinese string variants (gCNText_*)

### 5. UI Layout Adjustments

**Decision:** Minimal adjustments for proof of concept.

**Key changes:**
- Dialog box line width: accommodate ~18 Chinese characters per line (vs 28 English)
- Text wrapping: ensure Chinese text wraps at character boundaries (not mid-character)
- Menu column widths: adjust for double-width Chinese characters

### 6. Build System

**No changes needed to Makefile or Makefile_pc.** The existing build system will automatically pick up:
- Modified charmap.txt
- New font files in graphics/fonts/
- Modified source files

**Build commands:**
- PC: `make -f Makefile_pc -j4` (primary verification target)
- GBA ROM: `make modern -j4` (secondary, if arm-none-eabi toolchain available)

## Key Risks

1. **Character reading complexity:** All `*currentChar++` patterns need GB2312 detection. Missing one causes garbled text.
2. **Font file generation:** HZK12 font may not be readily available. Fallback: generate from TTF using Python PIL.
3. **Tile rendering alignment:** 12×12 doesn't fit neatly into 8×8 tile grid. Need careful tile splitting.
4. **preproc tool compatibility:** The preproc tool may not handle multi-byte charmap entries. Need to verify or patch.

## Testing Strategy

- **Unit tests:** Character reading functions (GB2312 detection, glyph index calculation)
- **Integration tests:** Render sample Chinese strings, verify pixel output
- **Build tests:** Ensure both PC and GBA builds compile successfully
- **Visual verification:** Run PC build and verify Chinese text displays correctly

## Success Criteria

1. `charmap.txt` contains GB2312 Level 1 character mappings
2. 12×12 Chinese font file generated and integrated
3. `text.c` renders Chinese characters correctly (no crashes, proper glyphs)
4. At least 20 sample strings display in Chinese
5. PC build (`pokeemerald.exe`) compiles and runs with Chinese text visible
