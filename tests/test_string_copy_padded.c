/*
 * test_string_copy_padded.c
 *
 * PC-side unit tests for the StringCopyPadded multi-byte fix.
 *
 * Background:
 *   Pokemon Emerald Chinese localization encodes Chinese characters as
 *   a 3-byte sequence: 0x80 + 2 bytes GB2312. The original
 *   StringCopyPadded treats every byte as one character, which causes
 *   buffer overflows on the PC move-Pokemon page (garbled text and
 *   A/B button crashes).
 *
 *   These tests verify the fixed version correctly:
 *     - treats 0x80 + 2 bytes as ONE character
 *     - treats 0xFC + variable params as a control code (not counted as char)
 *     - uses GetExtCtrlCodeLength to handle 1-4 byte control codes
 *     - treats CHAR_EXTRA_SYMBOL (0xF9) + 1 byte as ONE character
 *     - truncates by character count, not byte count
 *     - pads to n characters
 *     - handles incomplete 0x80 sequences safely
 *     - handles truncated control codes safely
 *
 * Build:  make test     (see Makefile)
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* Constants matching include/constants/characters.h */
#define EOS                    0xFF
#define CHAR_EXTRA_SYMBOL      0xF9
#define EXT_CTRL_CODE_BEGIN    0xFC

/* EXT_CTRL_CODE_* constants matching include/constants/characters.h */
#define EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW 0x04
#define EXT_CTRL_CODE_RESET_FONT             0x07
#define EXT_CTRL_CODE_PLAY_BGM               0x0B
#define EXT_CTRL_CODE_CHN                    0x19

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef u8       bool8;

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE  1
#endif

/* Buffer size large enough for every test case. */
#define TEST_BUF_SIZE 64

#define PAD_CHAR ' '

/*
 * ============================================================
 * WARNING: SYNCHRONIZATION CONSTRAINT
 * ============================================================
 * The function `StringCopyPadded_Fixed` below is a CODE COPY of
 * `StringCopyPadded` in `../src/string_util.c`. It is duplicated
 * here because the original file depends on GBA-specific headers
 * (global.h, EWRAM_DATA macro, etc.) that cannot be compiled on PC.
 *
 * ANY CHANGE to `StringCopyPadded` in `src/string_util.c` MUST be
 * mirrored in `StringCopyPadded_Fixed` below, and vice versa.
 *
 * The test cases in this file validate the behavior of
 * StringCopyPadded_Fixed. If the two implementations diverge,
 * the tests may pass while the real code is broken.
 *
 * Last synchronized with: src/string_util.c (this commit; see git log for hash)
 * ============================================================
 */

static int tests_passed = 0;
static int tests_failed = 0;

/* =============================================================
 * Buggy implementation (current src/string_util.c:567-587)
 * Kept here for reference / comparison; NOT what we test.
 * Wrapped in #if 0 to avoid -Wunused-function under -Wall -Wextra.
 * ============================================================= */
#if 0
static u8 *StringCopyPadded_Buggy(u8 *dest, const u8 *src, u8 c, u16 n)
{
    while (*src != EOS)
    {
        *dest++ = *src++;
        if (n)
            n--;
    }

    n--;

    while (n != (u16)-1)
    {
        *dest++ = c;
        n--;
    }

    *dest = EOS;
    return dest;
}
#endif

/* =============================================================
 * Test-only copy of GetExtCtrlCodeLength.
 *
 * This is a CODE COPY of `GetExtCtrlCodeLength` in
 * `../src/string_util.c` (lines 737-772). The original is `static`
 * and therefore not visible outside string_util.c, so we duplicate
 * it here for StringCopyPadded_Fixed to call.
 *
 * Returns the number of bytes AFTER the 0xFC header consumed by the
 * control code's parameters (NOT including the 0xFC byte itself).
 * Returns 0 for unknown control codes (e.g. EXT_CTRL_CODE_CHN),
 * which by convention are treated as 2-byte sequences.
 *
 * MUST be kept in sync with GetExtCtrlCodeLength in src/string_util.c.
 * ============================================================= */
static u8 GetExtCtrlCodeLength_Test(u8 code)
{
    static const u8 lengths[] =
    {
        [0]                                    = 1,
        [0x01]                                 = 2, /* EXT_CTRL_CODE_COLOR */
        [0x02]                                 = 2, /* EXT_CTRL_CODE_HIGHLIGHT */
        [0x03]                                 = 2, /* EXT_CTRL_CODE_SHADOW */
        [EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW] = 4,
        [0x05]                                 = 2, /* EXT_CTRL_CODE_PALETTE */
        [0x06]                                 = 2, /* EXT_CTRL_CODE_FONT */
        [EXT_CTRL_CODE_RESET_FONT]             = 1,
        [0x08]                                 = 2, /* EXT_CTRL_CODE_PAUSE */
        [0x09]                                 = 1, /* EXT_CTRL_CODE_PAUSE_UNTIL_PRESS */
        [0x0A]                                 = 1, /* EXT_CTRL_CODE_WAIT_SE */
        [EXT_CTRL_CODE_PLAY_BGM]               = 3,
        [0x0C]                                 = 2, /* EXT_CTRL_CODE_ESCAPE */
        [0x0D]                                 = 2, /* EXT_CTRL_CODE_SHIFT_RIGHT */
        [0x0E]                                 = 2, /* EXT_CTRL_CODE_SHIFT_DOWN */
        [0x0F]                                 = 1, /* EXT_CTRL_CODE_FILL_WINDOW */
        [0x10]                                 = 3, /* EXT_CTRL_CODE_PLAY_SE */
        [0x11]                                 = 2, /* EXT_CTRL_CODE_CLEAR */
        [0x12]                                 = 2, /* EXT_CTRL_CODE_SKIP */
        [0x13]                                 = 2, /* EXT_CTRL_CODE_CLEAR_TO */
        [0x14]                                 = 2, /* EXT_CTRL_CODE_MIN_LETTER_SPACING */
        [0x15]                                 = 1, /* EXT_CTRL_CODE_JPN */
        [0x16]                                 = 1, /* EXT_CTRL_CODE_ENG */
        [0x17]                                 = 1, /* EXT_CTRL_CODE_PAUSE_MUSIC */
        [0x18]                                 = 1, /* EXT_CTRL_CODE_RESUME_MUSIC */
    };

    u8 length = 0;
    if (code < sizeof(lengths) / sizeof(lengths[0]))
        length = lengths[code];
    return length;
}

/* =============================================================
 * Fixed implementation.
 *
 * Counts characters, not bytes:
 *   0x80 + 2 bytes       -> 1 Chinese character
 *   0xFC + variable      -> control code (GetExtCtrlCodeLength params, 0 chars)
 *   0xF9 + 1 byte        -> 1 extra symbol character
 *   any other byte       -> 1 character
 *
 * Writes at most n characters from src into dest, then pads with c
 * up to n characters, then writes EOS. If src ends early, the rest
 * is padding. If src is longer than n, it is truncated at n chars.
 * Truncated multi-byte sequences (incomplete 0x80, truncated 0xFC
 * control code, incomplete 0xF9) cause copy to stop immediately
 * without writing a partial character.
 * ============================================================= */
/* MUST be kept in sync with StringCopyPadded in src/string_util.c */
static u8 *StringCopyPadded_Fixed(u8 *dest, const u8 *src, u8 c, u16 n)
{
    u16 charsWritten = 0;
    bool8 truncated = FALSE;

    /* Order matters: 0xFC (EXT_CTRL_CODE_BEGIN) is a valid GB2312 byte,
     * so 0x80 (Chinese escape) must be checked first. See SkipExtCtrlCode. */
    while (*src != EOS && charsWritten < n && !truncated)
    {
        if (*src == 0x80) /* Chinese escape: 3 bytes = 1 char */
        {
            if (src[1] == EOS || src[2] == EOS)
            {
                truncated = TRUE;
                break;
            }
            *dest++ = *src++;
            *dest++ = *src++;
            *dest++ = *src++;
            charsWritten++;
        }
        else if (*src == EXT_CTRL_CODE_BEGIN) /* Control code: variable length, 0 chars */
        {
            u8 ctrlCode = src[1];
            u8 ctrlLen = GetExtCtrlCodeLength_Test(ctrlCode);
            u16 totalLen;
            u16 k;

            if (ctrlLen == 0)
                totalLen = 2; /* Unknown control code (e.g. EXT_CTRL_CODE_CHN), treat as 2 bytes */
            else
                totalLen = 1 + ctrlLen; /* 0xFC + params */

            /* Defensive: ensure we don't read past EOS */
            for (k = 1; k < totalLen; k++)
            {
                if (src[k] == EOS)
                {
                    truncated = TRUE;
                    break;
                }
            }
            if (truncated)
                break;

            for (k = 0; k < totalLen; k++)
                *dest++ = *src++;
        }
        else if (*src == CHAR_EXTRA_SYMBOL) /* Extra symbol: 2 bytes = 1 char */
        {
            if (src[1] == EOS)
            {
                truncated = TRUE;
                break;
            }
            *dest++ = *src++;
            *dest++ = *src++;
            charsWritten++;
        }
        else /* Single-byte character */
        {
            *dest++ = *src++;
            charsWritten++;
        }
    }

    while (charsWritten < n)
    {
        *dest++ = c;
        charsWritten++;
    }

    *dest = EOS;
    return dest;
}

/* =============================================================
 * Test helpers
 * ============================================================= */

static void print_hex(const u8 *buf, int len, const char *label)
{
    printf("    %s: ", label);
    for (int i = 0; i < len; i++)
        printf("%02X ", buf[i]);
    printf("\n");
}

static int bytes_equal(const u8 *actual, const u8 *expected, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (actual[i] != expected[i])
            return 0;
    }
    return 1;
}

/* Length of a string up to and including EOS. */
static int buf_total_len(const u8 *buf)
{
    int len = 0;
    while (buf[len] != EOS)
        len++;
    return len + 1;
}

#define TEST(name) static int name(void)

#define ASSERT(cond, msg) do { \
    if (!(cond)) { \
        printf("  FAIL: %s\n", msg); \
        return 0; \
    } \
    printf("  ok:   %s\n", msg); \
} while(0)

#define ASSERT_BYTES(actual, expected, len, msg) do { \
    if (!bytes_equal(actual, expected, len)) { \
        printf("  FAIL: %s\n", msg); \
        print_hex(actual,   len, "actual  "); \
        print_hex(expected, len, "expected"); \
        return 0; \
    } \
    printf("  ok:   %s\n", msg); \
} while(0)

#define RUN_TEST(name) do { \
    printf("RUN  %s\n", #name); \
    if (name()) { \
        printf("  -> PASS\n\n"); \
        tests_passed++; \
    } else { \
        printf("  -> FAIL\n\n"); \
        tests_failed++; \
    } \
} while(0)

/* =============================================================
 * Test data
 * ============================================================= */

/* GB2312 sequences used by the test cases (values from the spec). */
static const u8 STR_AB[]        = { 'A','B', EOS };
static const u8 STR_ABCDE[]     = { 'A','B','C','D','E', EOS };
static const u8 STR_ABCDEF[]    = { 'A','B','C','D','E','F', EOS };
static const u8 STR_ZHONG[]     = { 0x80,0xD6,0xD0, EOS };                      /* 中 */
static const u8 STR_MIAOWA[]    = { 0x80,0xC3,0xEE, 0x80,0xCD,0xBD, EOS };      /* 妙蛙 */
static const u8 STR_MWZZ[]      = { 0x80,0xC3,0xEE, 0x80,0xCD,0xBD,
                                    0x80,0xD6,0xD6, 0x80,0xD7,0xD3, EOS };      /* 妙蛙种子 */
static const u8 STR_MWZZM[]     = { 0x80,0xC3,0xEE, 0x80,0xCD,0xBD,
                                    0x80,0xD6,0xD6, 0x80,0xD7,0xD3,
                                    0x80,0xC3,0xEE, EOS };                       /* 妙蛙种子妙 (5 chars) */
static const u8 STR_EGG[]       = { 0xFC,0x19, 0x80,0xB5,0x02, EOS };           /* {CHN}蛋 */
static const u8 STR_CHN_YIDONG[]= { 0xFC,0x19, 0x80,0xD2,0xC6, 0x80,0xB4,0xB6, EOS }; /* {CHN}移动 */
static const u8 STR_A_BROKEN_80[]= { 'A', 0x80, EOS };                          /* A + incomplete 0x80 */
static const u8 STR_EMPTY[]     = { EOS };

/* Variable-length control code test data (see GetExtCtrlCodeLength). */
/* 4-byte ctrl code: COLOR_HIGHLIGHT_SHADOW (0x04) returns 4 -> totalLen=5 (0xFC + ctrl + 3 params) */
static const u8 STR_CTRL_CHS[]      = { 0xFC, EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW,
                                        0x01, 0x02, 0x03, EOS };
/* 3-byte ctrl code: PLAY_BGM (0x0B) returns 3 -> totalLen=4 (0xFC + ctrl + 2 params) */
static const u8 STR_CTRL_BGM[]      = { 0xFC, EXT_CTRL_CODE_PLAY_BGM,
                                        0x01, 0x02, EOS };
/* 1-byte ctrl code: RESET_FONT (0x07) returns 1 -> totalLen=2 (0xFC + ctrl, no params) */
static const u8 STR_CTRL_RESET[]    = { 0xFC, EXT_CTRL_CODE_RESET_FONT, EOS };
/* Standalone CHN control code (unknown to GetExtCtrlCodeLength -> default 2 bytes) */
static const u8 STR_CTRL_CHN_ONLY[] = { 0xFC, EXT_CTRL_CODE_CHN, EOS };
/* 0xFC immediately followed by EOS: cannot read ctrl code -> truncated */
static const u8 STR_CTRL_TRUNC_HEAD[]= { 0xFC, EOS };
/* 4-byte ctrl code truncated mid-params: ctrl=0x04 needs 3 params but only 1 present */
static const u8 STR_CTRL_TRUNC_MID[]= { 0xFC, EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW,
                                        0x01, EOS };
/* CHAR_EXTRA_SYMBOL (0xF9) + 1 byte -> 1 char (2 bytes total) */
static const u8 STR_EXTRA[]         = { 0xF9, 'X', EOS };
/* CHAR_EXTRA_SYMBOL at EOS: incomplete, should not be copied */
static const u8 STR_EXTRA_TRUNC[]  = { 'A', 0xF9, EOS };
/* Mixed: {CHN}妙蛙 = control(2) + Chinese(3) + Chinese(3) = 8 bytes, 2 chars */
static const u8 STR_MIXED_CHN_ZH[]  = { 0xFC, EXT_CTRL_CODE_CHN,
                                        0x80,0xC3,0xEE, 0x80,0xCD,0xBD, EOS };

/* =============================================================
 * Test cases
 * ============================================================= */

/* 1. Pure ASCII short name: "AB" (2 chars), n=5 -> "AB   " + EOS */
TEST(test_ascii_short)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { 'A','B',' ',' ',' ', EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_AB, PAD_CHAR, 5);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 6, "buffer == 'AB   ' + EOS");
    ASSERT(ret == &buf[5], "return points to EOS position");
    return 1;
}

/* 2. Pure ASCII exact: "ABCDE" (5 chars), n=5 -> "ABCDE" + EOS */
TEST(test_ascii_exact)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { 'A','B','C','D','E', EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_ABCDE, PAD_CHAR, 5);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 6, "buffer == 'ABCDE' + EOS, no padding");
    return 1;
}

/* 3. Pure ASCII long: "ABCDEF" (6 chars), n=5 -> truncated to "ABCDE" + EOS */
TEST(test_ascii_long)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { 'A','B','C','D','E', EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_ABCDEF, PAD_CHAR, 5);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 6, "buffer == 'ABCDE' + EOS (truncated)");
    ASSERT(buf_total_len(buf) == 6, "total length == 6 (5 chars + EOS)");
    return 1;
}

/* 4. One Chinese char: "中" (3 bytes, 1 char), n=5 -> 3 bytes + 4 pad + EOS */
TEST(test_chinese_1char)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { 0x80,0xD6,0xD0, ' ',' ',' ',' ', EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_ZHONG, PAD_CHAR, 5);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 8, "buffer == '中' + 4 spaces + EOS");
    ASSERT(buf_total_len(buf) == 8, "total length == 8 (3+4+EOS)");
    return 1;
}

/* 5. Two Chinese chars: "妙蛙" (6 bytes, 2 chars), n=5 -> 6 bytes + 3 pad + EOS */
TEST(test_chinese_2char)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { 0x80,0xC3,0xEE, 0x80,0xCD,0xBD, ' ',' ',' ', EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_MIAOWA, PAD_CHAR, 5);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 10, "buffer == '妙蛙' + 3 spaces + EOS");
    ASSERT(buf_total_len(buf) == 10, "total length == 10 (6+3+EOS)");
    return 1;
}

/* 6. Four Chinese chars: "妙蛙种子" (12 bytes, 4 chars), n=5 -> 12 bytes + 1 pad + EOS */
TEST(test_chinese_4char)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { 0x80,0xC3,0xEE, 0x80,0xCD,0xBD,
                      0x80,0xD6,0xD6, 0x80,0xD7,0xD3,
                      ' ', EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_MWZZ, PAD_CHAR, 5);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 14, "buffer == '妙蛙种子' + 1 space + EOS");
    ASSERT(buf_total_len(buf) == 14, "total length == 14 (12+1+EOS)");
    return 1;
}

/* 7. Truncate Chinese: "妙蛙种子妙" (5 chars, 15 bytes), n=3 -> 3 chars (9 bytes) + EOS */
TEST(test_chinese_truncate)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { 0x80,0xC3,0xEE, 0x80,0xCD,0xBD, 0x80,0xD6,0xD6, EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_MWZZM, PAD_CHAR, 3);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 10, "buffer == '妙蛙种' + EOS (truncated to 3 chars)");
    ASSERT(buf_total_len(buf) == 10, "total length == 10 (9+EOS), no padding");
    return 1;
}

/* 8. Egg name: "{CHN}蛋" = FC 19 + 0x80 B5 02, n=8
 *    Control code (2 bytes, 0 chars) + 1 Chinese char (3 bytes, 1 char)
 *    -> 2 + 3 + 7 pad = 12 bytes + EOS */
TEST(test_egg_name)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { 0xFC,0x19, 0x80,0xB5,0x02,
                      ' ',' ',' ',' ',' ',' ',' ', EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_EGG, PAD_CHAR, 8);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 13, "buffer == '{CHN}蛋' + 7 spaces + EOS");
    ASSERT(buf_total_len(buf) == 13, "total length == 13 (2+3+7+EOS)");
    return 1;
}

/* 9. {CHN}移动 = FC 19 + 0x80 D2 C6 + 0x80 B4 B6, n=5
 *    Control code (2 bytes, 0 chars) + 2 Chinese chars (6 bytes, 2 chars)
 *    -> 2 + 6 + 3 pad = 11 bytes + EOS */
TEST(test_src_with_chn_control)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { 0xFC,0x19,
                      0x80,0xD2,0xC6, 0x80,0xB4,0xB6,
                      ' ',' ',' ', EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_CHN_YIDONG, PAD_CHAR, 5);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 12, "buffer == '{CHN}移动' + 3 spaces + EOS");
    ASSERT(buf_total_len(buf) == 12, "total length == 12 (2+6+3+EOS)");
    return 1;
}

/* 10. Incomplete 0x80: "A\x80" + EOS, n=5 -> 'A' + 4 pad + EOS
 *     The 0x80 must NOT be copied because it is followed by EOS. */
TEST(test_truncated_0x80)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { 'A',' ',' ',' ',' ', EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_A_BROKEN_80, PAD_CHAR, 5);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 6, "buffer == 'A' + 4 spaces + EOS, no 0x80 leaked");
    ASSERT(buf_total_len(buf) == 6, "total length == 6 (1+4+EOS)");
    return 1;
}

/* 11. Empty src: "", n=5 -> 5 pad + EOS */
TEST(test_empty_src)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { ' ',' ',' ',' ',' ', EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_EMPTY, PAD_CHAR, 5);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 6, "buffer == 5 spaces + EOS");
    ASSERT(buf_total_len(buf) == 6, "total length == 6 (5+EOS)");
    return 1;
}

/* 12. n == 0: "AB", n=0 -> just EOS, nothing copied, nothing padded */
TEST(test_n_zero)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_AB, PAD_CHAR, 0);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 1, "buffer == EOS only");
    ASSERT(buf == ret, "return points to buf[0] (EOS position)");
    return 1;
}

/* 13. Chinese overflow: "妙蛙种子" (4 chars, 12 bytes), n=2 -> 2 chars (6 bytes) + EOS
 *     This is the key test for the PC crash bug: the buggy version copies
 *     all 12 bytes into an n=2 buffer, overflowing it. */
TEST(test_chinese_long_overflow)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { 0x80,0xC3,0xEE, 0x80,0xCD,0xBD, EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_MWZZ, PAD_CHAR, 2);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 7, "buffer == '妙蛙' + EOS (truncated to 2 chars, no overflow)");
    ASSERT(buf_total_len(buf) == 7, "total length == 7 (6+EOS)");
    return 1;
}

/* 14. Variable-length 4-byte control code: COLOR_HIGHLIGHT_SHADOW (0x04)
 *     GetExtCtrlCodeLength(0x04) = 4, so totalLen = 1 + 4 = 5 (0xFC + ctrl + 3 params)
 *     src = {0xFC, 0x04, 0x01, 0x02, 0x03, EOS}, n=5
 *     Control code (0 chars) + 5 padding = 5 + 5 + EOS = 11 bytes */
TEST(test_ctrl_code_4byte)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { 0xFC, EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW,
                      0x01, 0x02, 0x03,
                      ' ', ' ', ' ', ' ', ' ', EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_CTRL_CHS, PAD_CHAR, 5);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 11, "buffer == 4-byte ctrl + 5 spaces + EOS");
    ASSERT(buf_total_len(buf) == 11, "total length == 11 (5 ctrl + 5 pad + EOS)");
    return 1;
}

/* 15. Variable-length 3-byte control code: PLAY_BGM (0x0B)
 *     GetExtCtrlCodeLength(0x0B) = 3, so totalLen = 1 + 3 = 4 (0xFC + ctrl + 2 params)
 *     src = {0xFC, 0x0B, 0x01, 0x02, EOS}, n=5
 *     Control code (0 chars) + 5 padding = 4 + 5 + EOS = 10 bytes */
TEST(test_ctrl_code_3byte)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { 0xFC, EXT_CTRL_CODE_PLAY_BGM,
                      0x01, 0x02,
                      ' ', ' ', ' ', ' ', ' ', EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_CTRL_BGM, PAD_CHAR, 5);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 10, "buffer == 3-byte ctrl + 5 spaces + EOS");
    ASSERT(buf_total_len(buf) == 10, "total length == 10 (4 ctrl + 5 pad + EOS)");
    return 1;
}

/* 16. Variable-length 1-byte control code: RESET_FONT (0x07)
 *     GetExtCtrlCodeLength(0x07) = 1, so totalLen = 1 + 1 = 2 (0xFC + ctrl, no params)
 *     src = {0xFC, 0x07, EOS}, n=5
 *     Control code (0 chars) + 5 padding = 2 + 5 + EOS = 8 bytes */
TEST(test_ctrl_code_1byte)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { 0xFC, EXT_CTRL_CODE_RESET_FONT,
                      ' ', ' ', ' ', ' ', ' ', EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_CTRL_RESET, PAD_CHAR, 5);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 8, "buffer == 1-byte ctrl + 5 spaces + EOS");
    ASSERT(buf_total_len(buf) == 8, "total length == 8 (2 ctrl + 5 pad + EOS)");
    return 1;
}

/* 17. Standalone CHN control code: EXT_CTRL_CODE_CHN (0x19) is unknown to
 *     GetExtCtrlCodeLength (returns 0), so we default to totalLen = 2.
 *     src = {0xFC, 0x19, EOS}, n=5
 *     Control code (0 chars) + 5 padding = 2 + 5 + EOS = 8 bytes */
TEST(test_ctrl_code_chn)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { 0xFC, EXT_CTRL_CODE_CHN,
                      ' ', ' ', ' ', ' ', ' ', EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_CTRL_CHN_ONLY, PAD_CHAR, 5);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 8, "buffer == CHN ctrl + 5 spaces + EOS");
    ASSERT(buf_total_len(buf) == 8, "total length == 8 (2 ctrl + 5 pad + EOS)");
    return 1;
}

/* 18. Truncated control code at EOS: {0xFC, EOS}
 *     Cannot read src[1] safely as a ctrl code (it is EOS, which is not a
 *     valid ctrl code). The implementation should treat this as truncated
 *     and copy NOTHING (no partial control code). */
TEST(test_ctrl_code_truncated_at_eos)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { ' ', ' ', ' ', ' ', ' ', EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_CTRL_TRUNC_HEAD, PAD_CHAR, 5);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 6, "buffer == 5 spaces + EOS (truncated ctrl not copied)");
    ASSERT(buf_total_len(buf) == 6, "total length == 6 (5 pad + EOS)");
    return 1;
}

/* 19. Truncated control code mid-params: {0xFC, 0x04, 0x01, EOS}
 *     COLOR_HIGHLIGHT_SHADOW needs 3 params but only 1 present. The
 *     implementation should detect EOS in the params and stop without
 *     writing any partial bytes. */
TEST(test_ctrl_code_truncated_mid_params)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { ' ', ' ', ' ', ' ', ' ', EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_CTRL_TRUNC_MID, PAD_CHAR, 5);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 6, "buffer == 5 spaces + EOS (truncated ctrl mid-params not copied)");
    ASSERT(buf_total_len(buf) == 6, "total length == 6 (5 pad + EOS)");
    return 1;
}

/* 20. CHAR_EXTRA_SYMBOL (0xF9) + 1 byte = 1 character.
 *     src = {0xF9, 'X', EOS}, n=4
 *     1 char (2 bytes) + 3 padding = 2 + 3 + EOS = 6 bytes */
TEST(test_extra_symbol)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { 0xF9, 'X', ' ', ' ', ' ', EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_EXTRA, PAD_CHAR, 4);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 6, "buffer == 0xF9 'X' + 3 spaces + EOS");
    ASSERT(buf_total_len(buf) == 6, "total length == 6 (2 + 3 pad + EOS)");
    return 1;
}

/* 21. CHAR_EXTRA_SYMBOL at EOS (incomplete): {'A', 0xF9, EOS}, n=5
 *     'A' is copied (1 char), 0xF9 has no following byte so it must NOT
 *     be copied. Result: 'A' + 4 padding + EOS. */
TEST(test_extra_symbol_truncated)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { 'A', ' ', ' ', ' ', ' ', EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_EXTRA_TRUNC, PAD_CHAR, 5);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 6, "buffer == 'A' + 4 spaces + EOS, no 0xF9 leaked");
    ASSERT(buf_total_len(buf) == 6, "total length == 6 (1 + 4 pad + EOS)");
    return 1;
}

/* 22. Mixed CHN control code + Chinese chars: "{CHN}妙蛙", n=5
 *     src = {0xFC, 0x19, 0x80, 0xC3, 0xEE, 0x80, 0xCD, 0xBD, EOS}
 *     Control code (2 bytes, 0 chars) + 2 Chinese chars (6 bytes, 2 chars)
 *     -> 2 + 6 + 3 padding = 8 + 3 + EOS = 12 bytes */
TEST(test_mixed_chinese_and_control)
{
    u8 buf[TEST_BUF_SIZE];
    u8 expected[] = { 0xFC, EXT_CTRL_CODE_CHN,
                      0x80, 0xC3, 0xEE, 0x80, 0xCD, 0xBD,
                      ' ', ' ', ' ', EOS };
    u8 *ret = StringCopyPadded_Fixed(buf, STR_MIXED_CHN_ZH, PAD_CHAR, 5);
    ASSERT(ret != NULL, "return value non-NULL");
    ASSERT_BYTES(buf, expected, 12, "buffer == '{CHN}妙蛙' + 3 spaces + EOS");
    ASSERT(buf_total_len(buf) == 12, "total length == 12 (8 + 3 pad + EOS)");
    return 1;
}

/* =============================================================
 * Main
 * ============================================================= */
int main(void)
{
    printf("=== StringCopyPadded Fixed-implementation tests ===\n\n");

    RUN_TEST(test_ascii_short);
    RUN_TEST(test_ascii_exact);
    RUN_TEST(test_ascii_long);
    RUN_TEST(test_chinese_1char);
    RUN_TEST(test_chinese_2char);
    RUN_TEST(test_chinese_4char);
    RUN_TEST(test_chinese_truncate);
    RUN_TEST(test_egg_name);
    RUN_TEST(test_src_with_chn_control);
    RUN_TEST(test_truncated_0x80);
    RUN_TEST(test_empty_src);
    RUN_TEST(test_n_zero);
    RUN_TEST(test_chinese_long_overflow);
    RUN_TEST(test_ctrl_code_4byte);
    RUN_TEST(test_ctrl_code_3byte);
    RUN_TEST(test_ctrl_code_1byte);
    RUN_TEST(test_ctrl_code_chn);
    RUN_TEST(test_ctrl_code_truncated_at_eos);
    RUN_TEST(test_ctrl_code_truncated_mid_params);
    RUN_TEST(test_extra_symbol);
    RUN_TEST(test_extra_symbol_truncated);
    RUN_TEST(test_mixed_chinese_and_control);

    printf("=== Summary ===\n");
    printf("passed: %d\n", tests_passed);
    printf("failed: %d\n", tests_failed);

    return (tests_failed == 0) ? 0 : 1;
}
