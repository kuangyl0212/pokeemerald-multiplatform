#!/usr/bin/env python3
"""Translate region_map_entries.h sMapName_* strings to Chinese.

Uses ORAS official Chinese translations for Hoenn region, and
commonly-used fan translation names for Kanto and Sevii Islands.
Each translated string is prefixed with {CHN} control code to
switch to Chinese rendering mode.
"""

import re
import sys

# English name -> Chinese name mapping
# Based on ORAS official Chinese translations for Hoenn,
# and widely-accepted fan translations for Kanto/Sevii.
TRANSLATIONS = {
    # === Hoenn Towns ===
    'LITTLEROOT TOWN': '未白镇',
    'OLDALE TOWN': '古辰镇',
    'DEWFORD TOWN': '武斗镇',
    'LAVARIDGE TOWN': '焕燃镇',
    'FALLARBOR TOWN': '秋叶镇',
    'VERDANTURF TOWN': '茵郁镇',
    'PACIFIDLOG TOWN': '紫堇镇',

    # === Hoenn Cities ===
    'PETALBURG CITY': '橙华市',
    'SLATEPORT CITY': '凯那市',
    'MAUVILLE CITY': '紫堇市',
    'RUSTBORO CITY': '卡那兹市',
    'FORTREE CITY': '茵郁市',
    'LILYCOVE CITY': '水静市',
    'MOSSDEEP CITY': '绿岭市',
    'SOOTOPOLIS CITY': '琉璃市',
    'EVER GRANDE CITY': '彩幽市',

    # === Hoenn Routes (101-134) ===
    'ROUTE 101': '101号道路',
    'ROUTE 102': '102号道路',
    'ROUTE 103': '103号道路',
    'ROUTE 104': '104号道路',
    'ROUTE 105': '105号道路',
    'ROUTE 106': '106号道路',
    'ROUTE 107': '107号道路',
    'ROUTE 108': '108号道路',
    'ROUTE 109': '109号道路',
    'ROUTE 110': '110号道路',
    'ROUTE 111': '111号道路',
    'ROUTE 112': '112号道路',
    'ROUTE 113': '113号道路',
    'ROUTE 114': '114号道路',
    'ROUTE 115': '115号道路',
    'ROUTE 116': '116号道路',
    'ROUTE 117': '117号道路',
    'ROUTE 118': '118号道路',
    'ROUTE 119': '119号道路',
    'ROUTE 120': '120号道路',
    'ROUTE 121': '121号道路',
    'ROUTE 122': '122号道路',
    'ROUTE 123': '123号道路',
    'ROUTE 124': '124号道路',
    'ROUTE 125': '125号道路',
    'ROUTE 126': '126号道路',
    'ROUTE 127': '127号道路',
    'ROUTE 128': '128号道路',
    'ROUTE 129': '129号道路',
    'ROUTE 130': '130号道路',
    'ROUTE 131': '131号道路',
    'ROUTE 132': '132号道路',
    'ROUTE 133': '133号道路',
    'ROUTE 134': '134号道路',

    # === Hoenn Landmarks ===
    'UNDERWATER': '水下',
    'GRANITE CAVE': '石之洞窟',
    'MT. CHIMNEY': '烟突山',
    'SAFARI ZONE': '野生原野区',
    'BATTLE FRONTIER': '对战开拓区',
    'PETALBURG WOODS': '橙华森林',
    'RUSTURF TUNNEL': '卡绿隧道',
    'ABANDONED SHIP': '弃船',
    'NEW MAUVILLE': '新紫堇',
    'METEOR FALLS': '流星瀑布',
    'MT. PYRE': '送火山',
    'SHOAL CAVE': '浅滩洞穴',
    'SEAFLOOR CAVERN': '海底洞窟',
    'VICTORY ROAD': '冠军之路',
    'MIRAGE ISLAND': '幻影岛屿',
    'CAVE OF ORIGIN': '起源洞窟',
    'SOUTHERN ISLAND': '南方岛屿',
    'FIERY PATH': '火焰近道',
    'JAGGED PASS': '崎岖山道',
    'SEALED CHAMBER': '封印之间',
    'SCORCHED SLAB': '焦热石室',
    'ISLAND CAVE': '岛屿洞窟',
    'DESERT RUINS': '沙漠遗迹',
    'ANCIENT TOMB': '古代之墓',
    'INSIDE OF TRUCK': '卡车内',
    'SKY PILLAR': '天空之柱',
    'SECRET BASE': '秘密基地',
    'AQUA HIDEOUT': '水舰队藏身处',
    'MAGMA HIDEOUT': '熔岩队藏身处',
    'MIRAGE TOWER': '幻影塔',
    'FARAWAY ISLAND': '遥远岛屿',
    'ARTISAN CAVE': '匠之洞窟',
    'MARINE CAVE': '海之洞窟',
    'TERRA CAVE': '陆之洞窟',
    'DESERT UNDERPASS': '沙漠地道',
    'TRAINER HILL': '训练家之丘',
    'ALTERING CAVE': '变化洞窟',
    'NAVEL ROCK': '肚脐岩',
    'BIRTH ISLAND': '诞生岛屿',
    'EMBER SPA': '火炎温泉',
    'SPECIAL AREA': '特别区域',

    # === Kanto Towns/Cities ===
    'PALLET TOWN': '真新镇',
    'VIRIDIAN CITY': '常青市',
    'PEWTER CITY': '尼比市',
    'CERULEAN CITY': '华蓝市',
    'LAVENDER TOWN': '紫苑镇',
    'VERMILION CITY': '枯叶市',
    'CELADON CITY': '玉虹市',
    'FUCHSIA CITY': '浅红市',
    'CINNABAR ISLAND': '红莲岛',
    'INDIGO PLATEAU': '石英高原',
    'SAFFRON CITY': '金黄市',

    # === Kanto Routes (1-25) ===
    'ROUTE 1': '1号道路',
    'ROUTE 2': '2号道路',
    'ROUTE 3': '3号道路',
    'ROUTE 4': '4号道路',
    'ROUTE 5': '5号道路',
    'ROUTE 6': '6号道路',
    'ROUTE 7': '7号道路',
    'ROUTE 8': '8号道路',
    'ROUTE 9': '9号道路',
    'ROUTE 10': '10号道路',
    'ROUTE 11': '11号道路',
    'ROUTE 12': '12号道路',
    'ROUTE 13': '13号道路',
    'ROUTE 14': '14号道路',
    'ROUTE 15': '15号道路',
    'ROUTE 16': '16号道路',
    'ROUTE 17': '17号道路',
    'ROUTE 18': '18号道路',
    'ROUTE 19': '19号道路',
    'ROUTE 20': '20号道路',
    'ROUTE 21': '21号道路',
    'ROUTE 22': '22号道路',
    'ROUTE 23': '23号道路',
    'ROUTE 24': '24号道路',
    'ROUTE 25': '25号道路',

    # === Kanto Landmarks ===
    'VIRIDIAN FOREST': '常青森林',
    'MT. MOON': '月见山',
    'S.S. ANNE': '圣特安努号',
    'UNDERGROUND PATH': '地下通道',
    "DIGLETT'S CAVE": '地鼠洞',
    'ROCKET HIDEOUT': '火箭队藏身处',
    'SILPH CO.': '西尔佛公司',
    'POKéMON MANSION': '宝可梦公馆',
    'POKéMON LEAGUE': '宝可梦联盟',
    'ROCK TUNNEL': '岩石隧道',
    'SEAFOAM ISLANDS': '双子岛',
    'POKéMON TOWER': '宝可梦塔',
    'CERULEAN CAVE': '华蓝洞窟',
    'POWER PLANT': '无人发电厂',

    # === Sevii Islands ===
    'ONE ISLAND': '一岛',
    'TWO ISLAND': '二岛',
    'THREE ISLAND': '三岛',
    'FOUR ISLAND': '四岛',
    'FIVE ISLAND': '五岛',
    'SIX ISLAND': '六岛',
    'SEVEN ISLAND': '七岛',
    'KINDLE ROAD': '点燃之路',
    'TREASURE BEACH': '宝藏海滩',
    'CAPE BRINK': '望缘角',
    'BOND BRIDGE': '羁绊桥',
    'THREE ISLE PORT': '三岛港',
    'SEVII ISLE 6': '六之岛',
    'SEVII ISLE 7': '七之岛',
    'SEVII ISLE 8': '八之岛',
    'SEVII ISLE 9': '九之岛',
    'RESORT GORGEOUS': '华丽度假地',
    'WATER LABYRINTH': '水之迷宫',
    'FIVE ISLE MEADOW': '五岛草原',
    'MEMORIAL PILLAR': '纪念之柱',
    'OUTCAST ISLAND': '孤岛',
    'GREEN PATH': '绿之小径',
    'WATER PATH': '水之小径',
    'RUIN VALLEY': '遗迹山谷',
    'TRAINER TOWER': '训练家塔',
    'CANYON ENTRANCE': '峡谷入口',
    'SEVAULT CANYON': '荒野峡谷',
    'TANOBY RUINS': '塔诺比遗迹',
    'SEVII ISLE 22': '22号岛',
    'SEVII ISLE 23': '23号岛',
    'SEVII ISLE 24': '24号岛',
    'MT. EMBER': '火炎山',
    'BERRY FOREST': '树果森林',
    'ICEFALL CAVE': '冰瀑洞窟',
    'ROCKET WAREHOUSE': '火箭队仓库',
    'DOTTED HOLE': '点点洞',
    'LOST CAVE': '迷失洞窟',
    'PATTERN BUSH': '花纹灌木丛',
    'TANOBY CHAMBERS': '塔诺比房间',
    'THREE ISLE PATH': '三岛小径',
    'TANOBY KEY': '塔诺比钥匙',
    'MONEAN CHAMBER': '莫尼安房间',
    'LIPTOO CHAMBER': '利普图房间',
    'WEEPTH CHAMBER': '威普斯房间',
    'DILFORD CHAMBER': '迪尔福德房间',
    'SCUFIB CHAMBER': '斯库菲布房间',
    'RIXY CHAMBER': '里克斯房间',
    'VIAPOIS CHAMBER': '维亚波斯房间',
}


def translate_file(path):
    with open(path, 'r', encoding='utf-8') as f:
        content = f.read()

    # Pattern: static const u8 sMapName_XXX[] = _("YYY");
    # YYY may contain control codes like {AQUA}
    pattern = re.compile(
        r'(static const u8 sMapName_\w+\[\] = _\(")(.*?)("\);)'
    )

    translated_count = 0
    skipped = []

    def replace_match(m):
        nonlocal translated_count, skipped
        prefix, english_name, suffix = m.group(1), m.group(2), m.group(3)
        # Handle empty string (sMapName_[] = _(""))
        if english_name == '':
            return m.group(0)
        # Handle control code prefixed strings like "{AQUA} HIDEOUT"
        # Extract leading control codes
        ctrl_match = re.match(r'^(\{[^}]+\}\s*)', english_name)
        if ctrl_match:
            ctrl_prefix = ctrl_match.group(1)
            rest = english_name[len(ctrl_prefix):]
            # Look up the rest in translations
            if rest in TRANSLATIONS:
                chinese = TRANSLATIONS[rest]
                translated_count += 1
                return f'{prefix}{{CHN}}{ctrl_prefix}{chinese}{suffix}'
            else:
                skipped.append(f'{english_name} (with control code)')
                return m.group(0)
        # Direct lookup
        if english_name in TRANSLATIONS:
            chinese = TRANSLATIONS[english_name]
            translated_count += 1
            return f'{prefix}{{CHN}}{chinese}{suffix}'
        else:
            skipped.append(english_name)
            return m.group(0)

    new_content = pattern.sub(replace_match, content)

    with open(path, 'w', encoding='utf-8') as f:
        f.write(new_content)

    print(f"Translated: {translated_count}")
    print(f"Skipped: {len(skipped)}")
    if skipped:
        print("Skipped items:")
        for s in skipped:
            print(f"  {s}")


if __name__ == '__main__':
    path = 'src/data/region_map/region_map_entries.h'
    translate_file(path)
    print(f"Done: {path}")
