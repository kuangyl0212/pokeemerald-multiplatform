/*
 * 测试名称：test_pokedex_dex_num_buffer
 *
 * 测试目标：验证图鉴列表页 CreateMonDexNum 的缓冲区大小足够容纳
 *          汉化版 {NO}000 字符串（含 EOS 终止符）
 *
 * 根因：汉化版 {NO} = 80 F9 08（3 字节），_("{NO}000") 编译后为
 *       80 F9 08 30 30 30 FF（7 字节含 EOS）。
 *       原代码 text[6] 缓冲区只能装 6 字节，memcpy 不含 EOS，
 *       导致渲染时 0x80 被识别为中文转义码，读取 0xF9 0x08 组成
 *       currChar=0xF908，GB2312ToGlyphIndex 越界访问字体数据，
 *       产生乱码并可能越界写入 VRAM 破坏 BG tilemap。
 *
 * BDD 场景：
 *   Given: 汉化版 {NO} = 3 字节（80 F9 08）
 *   When:  sText_No000 = _("{NO}000") 编译为字节序列
 *   Then:  字节序列应为 80 F9 08 30 30 30 FF（7 字节含 EOS）
 *   And:   缓冲区大小应 >= 7 才能容纳完整字符串
 *
 *   Given: text[6] 缓冲区（6 字节，原 buggy 代码）
 *   When:  memcpy(text, sText_No000, 6) 复制前 6 字节
 *   Then:  text 中不含 EOS 终止符（text[5] = '0' != EOS）
 *   And:   渲染时会越界读取，产生乱码
 *
 *   Given: text[7] 缓冲区（7 字节，修复后代码）
 *   When:  memcpy(text, sText_No000, 7) 复制 7 字节
 *   Then:  text[6] == EOS (0xFF)
 *   And:   渲染时在 EOS 处正常停止
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

/* 模拟 GBA 字符常量 */
#define EOS 0xFF
#define CHAR_0 0xA1
#define CHAR_EXTRA_SYMBOL 0xF9

/* 汉化版 {NO} = 80 F9 08（3 字节），见 charmap.txt:1023 */
#define NO_BYTE_0 0x80
#define NO_BYTE_1 0xF9
#define NO_BYTE_2 0x08

/*
 * 模拟 sText_No000 = _("{NO}000") 编译后的字节序列
 * {NO} = 80 F9 08, '0' = 0x30, EOS = 0xFF
 * 完整序列：80 F9 08 30 30 30 FF（7 字节）
 */
static const uint8_t sText_No000[] = {
    NO_BYTE_0, NO_BYTE_1, NO_BYTE_2,
    0x30, 0x30, 0x30,
    EOS
};

/* 模拟 CreateMonDexNum 的核心逻辑（不含渲染） */
static void CreateMonDexNum_Simulate(uint8_t *text, size_t text_size, uint16_t dexNum)
{
    /* memcpy(text, sText_No000, ARRAY_COUNT(text)) */
    memcpy(text, sText_No000, text_size);

    /* 填充图鉴号数字（与 src/pokedex.c:2432-2434 一致） */
    text[2] = CHAR_0 + dexNum / 100;
    text[3] = CHAR_0 + (dexNum % 100) / 10;
    text[4] = CHAR_0 + (dexNum % 100) % 10;
}

/* 检查字符串是否以 EOS 终止（在 buffer_size 范围内） */
static int has_eos_terminator(const uint8_t *text, size_t buffer_size)
{
    size_t i;
    for (i = 0; i < buffer_size; i++)
    {
        if (text[i] == EOS)
            return 1;
    }
    return 0;
}

/* 测试 1：sText_No000 字节序列长度应为 7（含 EOS） */
static void test_sText_No000_length_is_7_with_eos(void)
{
    size_t expected = 7;  /* 80 F9 08 30 30 30 FF */
    size_t actual = sizeof(sText_No000);

    printf("RUN  test_sText_No000_length_is_7_with_eos\n");
    assert(actual == expected);
    printf("  ok:   sizeof(sText_No000) == %zu (expected 7: {NO}000 + EOS)\n", actual);

    /* 验证字节序列 */
    assert(sText_No000[0] == 0x80);  /* {NO} byte 0 */
    assert(sText_No000[1] == 0xF9);  /* {NO} byte 1 */
    assert(sText_No000[2] == 0x08);  /* {NO} byte 2 */
    assert(sText_No000[3] == 0x30);  /* '0' */
    assert(sText_No000[4] == 0x30);  /* '0' */
    assert(sText_No000[5] == 0x30);  /* '0' */
    assert(sText_No000[6] == EOS);   /* EOS */
    printf("  ok:   byte sequence == 80 F9 08 30 30 30 FF\n");
    printf("  -> PASS\n\n");
}

/* 测试 2：text[6] 缓冲区（原 buggy 代码）缺少 EOS */
static void test_text6_buffer_missing_eos(void)
{
    uint8_t text[6];
    uint16_t dexNum = 1;  /* No.001 */

    printf("RUN  test_text6_buffer_missing_eos\n");
    CreateMonDexNum_Simulate(text, sizeof(text), dexNum);

    /* text[6] 只能装 6 字节，EOS 未被复制 */
    assert(text[0] == 0x80);  /* {NO} byte 0 */
    assert(text[1] == 0xF9);  /* {NO} byte 1 */
    assert(text[2] == CHAR_0 + 0);  /* dexNum/100 = 0 → CHAR_0 */
    assert(text[3] == CHAR_0 + 0);  /* (dexNum%100)/10 = 0 → CHAR_0 */
    assert(text[4] == CHAR_0 + 1);  /* (dexNum%100)%10 = 1 → CHAR_0+1 */
    assert(text[5] == 0x30);  /* 最后一个 '0'（未被覆盖） */

    /* 关键：没有 EOS 终止符 */
    assert(!has_eos_terminator(text, sizeof(text)));
    printf("  ok:   text[6] 缺少 EOS 终止符（buffer overflow 根因）\n");
    printf("  -> PASS (确认 bug 存在)\n\n");
}

/* 测试 3：text[7] 缓冲区（修复后代码）包含 EOS */
static void test_text7_buffer_has_eos(void)
{
    uint8_t text[7];
    uint16_t dexNum = 1;  /* No.001 */

    printf("RUN  test_text7_buffer_has_eos\n");
    CreateMonDexNum_Simulate(text, sizeof(text), dexNum);

    /* text[7] 装 7 字节，EOS 被正确复制 */
    assert(text[0] == 0x80);  /* {NO} byte 0 */
    assert(text[1] == 0xF9);  /* {NO} byte 1 */
    assert(text[2] == CHAR_0 + 0);  /* dexNum/100 = 0 → CHAR_0 */
    assert(text[3] == CHAR_0 + 0);  /* (dexNum%100)/10 = 0 → CHAR_0 */
    assert(text[4] == CHAR_0 + 1);  /* (dexNum%100)%10 = 1 → CHAR_0+1 */
    assert(text[5] == 0x30);  /* 最后一个 '0'（未被覆盖） */
    assert(text[6] == EOS);   /* EOS 终止符 */

    /* 关键：有 EOS 终止符 */
    assert(has_eos_terminator(text, sizeof(text)));
    printf("  ok:   text[7] 包含 EOS 终止符（修复后正常）\n");
    printf("  -> PASS\n\n");
}

/* 测试 4：图鉴号边界 - No.000 */
static void test_dex_num_000(void)
{
    uint8_t text[7];
    uint16_t dexNum = 0;

    printf("RUN  test_dex_num_000\n");
    CreateMonDexNum_Simulate(text, sizeof(text), dexNum);

    assert(text[2] == CHAR_0 + 0);
    assert(text[3] == CHAR_0 + 0);
    assert(text[4] == CHAR_0 + 0);
    assert(text[6] == EOS);
    printf("  ok:   No.000: text[2..4] = CHAR_0 CHAR_0 CHAR_0, EOS present\n");
    printf("  -> PASS\n\n");
}

/* 测试 5：图鉴号边界 - No.100 */
static void test_dex_num_100(void)
{
    uint8_t text[7];
    uint16_t dexNum = 100;

    printf("RUN  test_dex_num_100\n");
    CreateMonDexNum_Simulate(text, sizeof(text), dexNum);

    assert(text[2] == CHAR_0 + 1);  /* 百位 = 1 */
    assert(text[3] == CHAR_0 + 0);  /* 十位 = 0 */
    assert(text[4] == CHAR_0 + 0);  /* 个位 = 0 */
    assert(text[6] == EOS);
    printf("  ok:   No.100: text[2..4] = CHAR_0+1 CHAR_0 CHAR_0, EOS present\n");
    printf("  -> PASS\n\n");
}

/* 测试 6：图鉴号边界 - No.386（丰缘图鉴最大值） */
static void test_dex_num_386(void)
{
    uint8_t text[7];
    uint16_t dexNum = 386;

    printf("RUN  test_dex_num_386\n");
    CreateMonDexNum_Simulate(text, sizeof(text), dexNum);

    assert(text[2] == CHAR_0 + 3);  /* 百位 = 3 */
    assert(text[3] == CHAR_0 + 8);  /* 十位 = 8 */
    assert(text[4] == CHAR_0 + 6);  /* 个位 = 6 */
    assert(text[6] == EOS);
    printf("  ok:   No.386: text[2..4] = CHAR_0+3 CHAR_0+8 CHAR_0+6, EOS present\n");
    printf("  -> PASS\n\n");
}

/* 测试 7：图鉴号边界 - No.999（最大 3 位数） */
static void test_dex_num_999(void)
{
    uint8_t text[7];
    uint16_t dexNum = 999;

    printf("RUN  test_dex_num_999\n");
    CreateMonDexNum_Simulate(text, sizeof(text), dexNum);

    assert(text[2] == CHAR_0 + 9);
    assert(text[3] == CHAR_0 + 9);
    assert(text[4] == CHAR_0 + 9);
    assert(text[6] == EOS);
    printf("  ok:   No.999: text[2..4] = CHAR_0+9 CHAR_0+9 CHAR_0+9, EOS present\n");
    printf("  -> PASS\n\n");
}

/* 测试 8：0x80 中文转义码不与图鉴号数字冲突 */
static void test_no_conflict_between_0x80_and_dex_num(void)
{
    uint8_t text[7];
    uint16_t dexNum = 1;

    printf("RUN  test_no_conflict_between_0x80_and_dex_num\n");
    CreateMonDexNum_Simulate(text, sizeof(text), dexNum);

    /* text[0] 仍然是 0x80（中文转义码），不会被图鉴号覆盖 */
    assert(text[0] == 0x80);
    /* text[1] 仍然是 0xF9（{NO} 的第二字节） */
    assert(text[1] == 0xF9);
    /* text[2..4] 被图鉴号数字覆盖 */
    assert(text[2] == CHAR_0 + 0);
    assert(text[3] == CHAR_0 + 0);
    assert(text[4] == CHAR_0 + 1);
    printf("  ok:   0x80 转义码保留在 text[0]，图鉴号数字在 text[2..4]\n");
    printf("  -> PASS\n\n");
}

int main(void)
{
    int passed = 0, failed = 0;

    printf("=== CreateMonDexNum 缓冲区边界测试 ===\n\n");

    /* RED 阶段：先验证 buggy 行为 */
    /* test_text6_buffer_missing_eos 确认 bug 存在 */

    /* GREEN 阶段：验证修复后行为 */
    /* test_text7_buffer_has_eos 确认修复有效 */

    /* 运行所有测试 */
    #define RUN_TEST(t) do { \
        int before = failed; \
        t(); \
        if (failed == before) passed++; \
        else failed++; \
    } while (0)

    RUN_TEST(test_sText_No000_length_is_7_with_eos);
    RUN_TEST(test_text6_buffer_missing_eos);
    RUN_TEST(test_text7_buffer_has_eos);
    RUN_TEST(test_dex_num_000);
    RUN_TEST(test_dex_num_100);
    RUN_TEST(test_dex_num_386);
    RUN_TEST(test_dex_num_999);
    RUN_TEST(test_no_conflict_between_0x80_and_dex_num);

    #undef RUN_TEST

    printf("=== Summary ===\n");
    printf("passed: %d\n", passed);
    printf("failed: %d\n", failed);

    return failed > 0 ? 1 : 0;
}
