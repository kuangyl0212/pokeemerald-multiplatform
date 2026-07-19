#!/usr/bin/env python3
"""Find scripts.inc files that still have English .string content (no {CHN})."""
import os
import re

root = r'w:\workspace\pokeemerald-multiplatform-master\data\maps'
untranslated = []

for dirpath, dirnames, filenames in os.walk(root):
    for filename in filenames:
        if filename == 'scripts.inc':
            path = os.path.join(dirpath, filename)
            try:
                with open(path, 'r', encoding='utf-8') as f:
                    content = f.read()
                # Count .string lines
                string_count = len(re.findall(r'\.string', content))
                if string_count == 0:
                    continue
                chn_count = content.count('{CHN}')
                if chn_count == 0:
                    # Check if there are actual English text strings
                    # Look for .string "..." patterns with ASCII letters
                    english_strings = re.findall(r'\.string\s+"[^"]*[A-Za-z][^"]*"', content)
                    if english_strings:
                        rel_path = os.path.relpath(path, r'w:\workspace\pokeemerald-multiplatform-master')
                        untranslated.append((rel_path, string_count, len(english_strings)))
            except Exception as e:
                print(f"Error: {path}: {e}")

print(f"Found {len(untranslated)} files with untranslated English strings:")
for path, total, english in untranslated:
    print(f"  {path}: {total} .string lines, {english} with English text")
