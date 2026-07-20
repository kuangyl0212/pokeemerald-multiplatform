"""Count translated and untranslated categoryName entries."""
import re
from pathlib import Path

filepath = Path(__file__).parent.parent / 'src' / 'data' / 'pokemon' / 'pokedex_entries.h'
content = filepath.read_text(encoding='utf-8', newline='')

chn_pattern = re.compile(r'\.categoryName = _\("\{CHN\}')
total_pattern = re.compile(r'\.categoryName = _\(')

chn_count = len(chn_pattern.findall(content))
total_count = len(total_pattern.findall(content))

print(f"Translated (with CHN): {chn_count}")
print(f"Total categoryName: {total_count}")
print(f"Remaining: {total_count - chn_count}")

# Show first 20 untranslated entries
lines = content.split('\n')
current_dex = None
dex_pattern = re.compile(r'^\s*\[NATIONAL_DEX_(\w+)\]\s*=\s*$')
cat_eng = re.compile(r'^\s*\.categoryName = _\("[^{}]"\),\s*$')
cat_eng2 = re.compile(r'^\s*\.categoryName = _\("[A-Z][A-Z ]*"\),\s*$')

untranslated = []
for i, line in enumerate(lines, start=1):
    m = dex_pattern.match(line)
    if m:
        current_dex = m.group(1)
        continue
    if cat_eng2.match(line):
        untranslated.append((i, current_dex, line.strip()))

print(f"\nFirst 30 untranslated entries:")
for i, dex, line in untranslated[:30]:
    print(f"  Line {i} [{dex}]: {line}")
print(f"\nTotal untranslated: {len(untranslated)}")
