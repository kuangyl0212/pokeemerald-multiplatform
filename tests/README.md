# StringCopyPadded PC-side unit tests

## Purpose

Verifies the multibyte-aware fix for `StringCopyPadded` in
`src/string_util.c`. The original implementation treats every byte as a
character, which overflows the destination buffer when copying Chinese
names (each Chinese character is a 3-byte `0x80 + GB2312` sequence).
This causes garbled text and A/B button crashes on the PC move-Pokemon
page.

The fixed version counts characters, not bytes:

- `0x80` + 2 bytes  → 1 Chinese character
- `0xFC` + 1 byte   → 2-byte control code, not counted as a character
- any other byte    → 1 character

## Files

- `test_string_copy_padded.c` — self-contained test program.
  Includes a copy of the buggy implementation (for reference) and the
  fixed implementation under test. Thirteen test cases cover ASCII,
  Chinese, control codes, truncation, padding, and edge cases.
- `Makefile` — builds and runs the test program.

## Running

From WSL (the test program is compiled with gcc on Linux):

```bash
cd /mnt/w/workspace/pokeemerald-multiplatform-master/.worktrees/fix-chinese-localization/tests
make test
```

A successful run prints `passed: 13` / `failed: 0` and exits 0.
