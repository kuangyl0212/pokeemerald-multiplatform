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
 *     - treats 0xFC + 1 byte as a 2-byte control code (not counted as char)
 *     - truncates by character count, not byte count
 *     - pads to n characters
 *     - handles incomplete 0x80 sequences safely
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

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;

/* Buffer size large enough for every test case. */
#define TEST_BUF_SIZE 64

#define PAD_CHAR ' '

static int tests_passed = 0;
static int tests_failed = 0;

/* =============================================================
 * Buggy implementation (current src/string_util.c:567-587)
 * Kept here for reference / comparison; NOT what we test.
 * ============================================================= */
u8 *StringCopyPadded_Buggy(u8 *dest, const u8 *src, u8 c, u16 n)
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

/* =============================================================
 * Fixed implementation.
 *
 * Counts characters, not bytes:
 *   0x80 + 2 bytes  -> 1 Chinese character
 *   0xFC + 1 byte   -> 2-byte control code (not counted as a char)
 *   any other byte  -> 1 character
 *
 * Writes at most n characters from src into dest, then pads with c
 * up to n characters, then writes EOS. If src ends early, the rest
 * is padding. If src is longer than n, it is truncated at n chars.
 * ============================================================= */
u8 *StringCopyPadded_Fixed(u8 *dest, const u8 *src, u8 c, u16 n)
{
    u16 charsWritten = 0;

    while (*src != EOS && charsWritten < n)
    {
        if (*src == 0x80) /* Chinese escape: 3 bytes = 1 char */
        {
            if (src[1] == EOS || src[2] == EOS)
                break;
            *dest++ = *src++;
            *dest++ = *src++;
            *dest++ = *src++;
            charsWritten++;
        }
        else if (*src == EXT_CTRL_CODE_BEGIN) /* Control code: 2 bytes, 0 chars */
        {
            if (src[1] == EOS)
                break;
            *dest++ = *src++;
            *dest++ = *src++;
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

    printf("=== Summary ===\n");
    printf("passed: %d\n", tests_passed);
    printf("failed: %d\n", tests_failed);

    return (tests_failed == 0) ? 0 : 1;
}
