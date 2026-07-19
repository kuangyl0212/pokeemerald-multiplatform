#!/usr/bin/env python3
"""Scan all .inc files for characters not in GB2312."""
import os

def is_valid_gb2312(ch):
    """Check if a character can be encoded in GB2312."""
    if ord(ch) < 0x80:
        return True
    try:
        ch.encode('gb2312')
        return True
    except (UnicodeEncodeError, LookupError):
        return False

def scan_file(path):
    """Scan a file for non-GB2312 characters inside .string content."""
    try:
        with open(path, 'r', encoding='utf-8') as f:
            lines = f.readlines()
    except Exception:
        return []

    issues = []
    in_string = False
    for lineno, line in enumerate(lines, 1):
        # Only check content inside .string "..." lines
        # Look for non-ASCII chars between the first " and last " on .string lines
        stripped = line.lstrip()
        if not stripped.startswith('.string'):
            continue
        # Extract content between first " and last "
        first = line.find('"')
        last = line.rfind('"')
        if first == -1 or last == -1 or first == last:
            continue
        content = line[first+1:last]
        for ch in content:
            if not is_valid_gb2312(ch):
                issues.append((lineno, ch, hex(ord(ch)), line.rstrip()))
    return issues

def main():
    root = r'w:\workspace\pokeemerald-multiplatform-master'
    extensions = ('.inc', '.c', '.h')
    all_issues = {}
    for dirpath, dirnames, filenames in os.walk(root):
        dirnames[:] = [d for d in dirnames if not d.startswith('.') and d not in ('build', 'android', '.git', 'SDL2', 'libagbsys', 'tools')]
        for filename in filenames:
            if filename.endswith(extensions):
                path = os.path.join(dirpath, filename)
                issues = scan_file(path)
                if issues:
                    all_issues[path] = issues

    if not all_issues:
        print("No non-GB2312 characters found!")
        return

    total = 0
    for path, issues in all_issues.items():
        print(f"\n{path}:")
        for lineno, ch, code, line in issues:
            print(f"  Line {lineno}: '{ch}' ({code})")
            print(f"    {line}")
            total += 1
    print(f"\nTotal: {total} non-GB2312 characters in {len(all_issues)} files")

if __name__ == '__main__':
    main()
