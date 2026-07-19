#!/usr/bin/env python3
"""Fix ASCII double quotes used as content in all .inc files.
Replace them with Chinese quotes (U+201C left, U+201D right).
Also fix literal \\u201c and \\u201d strings that were written incorrectly."""
import os
import re

def fix_file(path):
    try:
        with open(path, 'r', encoding='utf-8') as f:
            content = f.read()
    except Exception as e:
        return 0, 0

    original = content

    # Fix literal \u201c and \u201d strings
    content = content.replace('\\u201c', '\u201c')
    content = content.replace('\\u201d', '\u201d')

    # Now fix lines with .string "..." where ... contains ASCII double quotes
    lines = content.split('\n')
    fixed_lines = 0
    for i, line in enumerate(lines):
        # Match .string "..." where ... contains ASCII double quotes
        # Pattern: .string "content"suffix
        m = re.match(r'^(\s*\.string ")(.*)("[^\n]*)$', line)
        if not m:
            continue
        prefix = m.group(1)
        inner = m.group(2)
        suffix = m.group(3)

        # Skip if no inner ASCII double quote
        if '"' not in inner:
            continue

        # Replace pairs of ASCII double quotes with Chinese quotes
        new_inner = []
        quote_count = 0
        for ch in inner:
            if ch == '"':
                if quote_count % 2 == 0:
                    new_inner.append('\u201c')  # left
                else:
                    new_inner.append('\u201d')  # right
                quote_count += 1
            else:
                new_inner.append(ch)
        new_inner = ''.join(new_inner)
        lines[i] = prefix + new_inner + suffix
        fixed_lines += 1

    content = '\n'.join(lines)

    if content != original:
        try:
            with open(path, 'w', encoding='utf-8', newline='') as f:
                f.write(content)
            return fixed_lines, 1
        except Exception:
            return 0, 0
    return 0, 0

def main():
    root = r'w:\workspace\pokeemerald-multiplatform-master'
    extensions = ('.inc',)
    total_fixed_lines = 0
    total_fixed_files = 0
    for dirpath, dirnames, filenames in os.walk(root):
        dirnames[:] = [d for d in dirnames if not d.startswith('.') and d not in ('build', 'android', '.git', 'SDL2', 'libagbsys', 'tools')]
        for filename in filenames:
            if filename.endswith(extensions):
                path = os.path.join(dirpath, filename)
                fixed_lines, fixed_files = fix_file(path)
                if fixed_lines > 0:
                    print(f"Fixed {fixed_lines} lines in {path}")
                total_fixed_lines += fixed_lines
                total_fixed_files += fixed_files
    print(f"Total: fixed {total_fixed_lines} lines in {total_fixed_files} files")

if __name__ == '__main__':
    main()
