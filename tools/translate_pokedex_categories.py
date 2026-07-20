"""Translate pokedex_entries.h categoryName fields from English to Chinese.

This script uses NATIONAL_DEX_ identifiers as keys (not line numbers) so it is
robust to line number shifts.

Replaces each .categoryName = _("XXXX") with .categoryName = _("{CHN}中文").
"""
import sys
import re
from pathlib import Path

# Mapping: NATIONAL_DEX identifier -> Chinese translation (without {CHN} prefix)
# Based on official 52poke Chinese category names.
TRANSLATIONS = {
    "NONE": "不明",
    "BULBASAUR": "种子",
    "IVYSAUR": "草",
    "VENUSAUR": "花",
    "CHARMANDER": "蜥蜴",
    "CHARMELEON": "火焰",
    "CHARIZARD": "火焰",
    "SQUIRTLE": "小龟",
    "WARTORTLE": "龟",
    "BLASTOISE": "龟甲",
    "CATERPIE": "虫",
    "METAPOD": "蛹",
    "BUTTERFREE": "蝴蝶",
    "WEEDLE": "毛虫",
    "KAKUNA": "蛹",
    "BEEDRILL": "毒蜂",
    "PIDGEY": "小鸟",
    "PIDGEOTTO": "鸟",
    "PIDGEOT": "鸟",
    "RATTATA": "鼠",
    "RATICATE": "鼠",
    "SPEAROW": "小鸟",
    "FEAROW": "鸟嘴",
    "EKANS": "蛇",
    "ARBOK": "眼镜蛇",
    "PIKACHU": "鼠",
    "RAICHU": "鼠",
    "SANDSHREW": "鼠",
    "SANDSLASH": "鼠",
    "NIDORAN_F": "毒针",
    "NIDORINA": "毒针",
    "NIDOQUEEN": "钻头",
    "NIDORAN_M": "毒针",
    "NIDORINO": "毒针",
    "NIDOKING": "钻头",
    "CLEFAIRY": "妖精",
    "CLEFABLE": "妖精",
    "VULPIX": "狐狸",
    "NINETALES": "狐狸",
    "JIGGLYPUFF": "气球",
    "WIGGLYTUFF": "气球",
    "ZUBAT": "蝙蝠",
    "GOLBAT": "蝙蝠",
    "ODDISH": "杂草",
    "GLOOM": "杂草",
    "VILEPLUME": "花",
    "PARAS": "蘑菇",
    "PARASECT": "蘑菇",
    "VENONAT": "虫",
    "VENOMOTH": "毒蛾",
    "DIGLETT": "鼹鼠",
    "DUGTRIO": "鼹鼠",
    "MEOWTH": "小猫",
    "PERSIAN": "猫",
    "PSYDUCK": "鸭",
    "GOLDUCK": "鸭",
    "MANKEY": "猪猴",
    "PRIMEAPE": "猪猴",
    "GROWLITHE": "小狗",
    "ARCANINE": "传说",
    "POLIWAG": "蝌蚪",
    "POLIWHIRL": "蝌蚪",
    "POLIWRATH": "蝌蚪",
    "ABRA": "念力",
    "KADABRA": "念力",
    "ALAKAZAM": "念力",
    "MACHOP": "怪力",
    "MACHOKE": "怪力",
    "MACHAMP": "怪力",
    "BELLSPROUT": "花",
    "WEEPINBELL": "捕蝇草",
    "VICTREEBEL": "捕蝇草",
    "TENTACOOL": "水母",
    "TENTACRUEL": "水母",
    "GEODUDE": "岩石",
    "GRAVELER": "岩石",
    "GOLEM": "巨石",
    "PONYTA": "火马",
    "RAPIDASH": "火马",
    "SLOWPOKE": "呆呆",
    "SLOWBRO": "寄居蟹",
    "MAGNEMITE": "磁铁",
    "MAGNETON": "磁铁",
    "FARFETCHD": "野鸭",
    "DODUO": "双鸟",
    "DODRIO": "三鸟",
    "SEEL": "海狮",
    "DEWGONG": "海狮",
    "GRIMER": "污泥",
    "MUK": "污泥",
    "SHELLDER": "双壳贝",
    "CLOYSTER": "双壳贝",
    "GASTLY": "气体",
    "HAUNTER": "气体",
    "GENGAR": "影",
    "ONIX": "岩蛇",
    "DROWZEE": "催眠",
    "HYPNO": "催眠",
    "KRABBY": "河蟹",
    "KINGLER": "钳",
    "VOLTORB": "球",
    "ELECTRODE": "球",
    "EXEGGCUTE": "蛋",
    "EXEGGUTOR": "椰子",
    "CUBONE": "孤独",
    "MAROWAK": "骨",
    "HITMONLEE": "踢",
    "HITMONCHAN": "拳",
    "LICKITUNG": "舔",
    "KOFFING": "毒气",
    "WEEZING": "毒气",
    "RHYHORN": "尖刺",
    "RHYDON": "钻头",
    "CHANSEY": "蛋",
    "TANGELA": "藤",
    "KANGASKHAN": "母子",
    "HORSEA": "龙",
    "SEADRA": "龙",
    "GOLDEEN": "金鱼",
    "SEAKING": "金鱼",
    "STARYU": "星形",
    "STARMIE": "神秘",
    "MR_MIME": "屏障",
    "SCYTHER": "螳螂",
    "JYNX": "人形",
    "ELECTABUZZ": "电",
    "MAGMAR": "喷火",
    "PINSIR": "锹形",
    "TAUROS": "野牛",
    "MAGIKARP": "鱼",
    "GYARADOS": "凶恶",
    "LAPRAS": "渡船",
    "DITTO": "变身",
    "EEVEE": "进化",
    "VAPOREON": "泡沫",
    "JOLTEON": "闪电",
    "FLAREON": "火焰",
    "PORYGON": "虚拟",
    "OMANYTE": "螺旋",
    "OMASTAR": "螺旋",
    "KABUTO": "甲壳",
    "KABUTOPS": "甲壳",
    "AERODACTYL": "化石",
    "SNORLAX": "贪睡",
    "ARTICUNO": "冰冻",
    "ZAPDOS": "电",
    "MOLTRES": "火焰",
    "DRATINI": "龙",
    "DRAGONAIR": "龙",
    "DRAGONITE": "龙",
    "MEWTWO": "基因",
    "MEW": "新种",
    "CHIKORITA": "叶",
    "BAYLEEF": "叶",
    "MEGANIUM": "香草",
    "CYNDAQUIL": "火鼠",
    "QUILAVA": "火山",
    "TYPHLOSION": "火山",
    "TOTODILE": "大颚",
    "CROCONAW": "大颚",
    "FERALIGATR": "大颚",
    "SENTRET": "侦察",
    "FURRET": "长身",
    "HOOTHOOT": "猫头鹰",
    "NOCTOWL": "猫头鹰",
    "LEDYBA": "五星",
    "LEDIAN": "五星",
    "SPINARAK": "吐丝",
    "ARIADOS": "长脚",
    "CROBAT": "蝙蝠",
    "CHINCHOU": "灯笼",
    "LANTURN": "灯",
    "PICHU": "小鼠",
    "CLEFFA": "星形",
    "IGGLYBUFF": "气球",
    "TOGEPI": "刺球",
    "TOGETIC": "幸福",
    "NATU": "小鸟",
    "XATU": "神秘",
    "MAREEP": "羊毛",
    "FLAAFFY": "羊毛",
    "AMPHAROS": "灯",
    "BELLOSSOM": "花",
    "MARILL": "水鼠",
    "AZUMARILL": "水兔",
    "SUDOWOODO": "模仿",
    "POLITOED": "青蛙",
    "HOPPIP": "棉絮",
    "SKIPLOOM": "棉絮",
    "JUMPLUFF": "棉絮",
    "AIPOM": "长尾",
    "SUNKERN": "种子",
    "SUNFLORA": "太阳",
    "YANMA": "透翅",
    "WOOPER": "水鱼",
    "QUAGSIRE": "水鱼",
    "ESPEON": "太阳",
    "UMBREON": "月光",
    "MURKROW": "黑暗",
    "SLOWKING": "王者",
    "MISDREAVUS": "尖叫",
    "UNOWN": "符号",
    "WOBBUFFET": "忍耐",
    "GIRAFARIG": "长颈",
    "PINECO": "蓑虫",
    "FORRETRESS": "蓑虫",
    "DUNSPARCE": "陆蛇",
    "GLIGAR": "飞蝎",
    "STEELIX": "铁蛇",
    "SNUBBULL": "妖精",
    "GRANBULL": "妖精",
    "QWILFISH": "气球",
    "SCIZOR": "钳",
    "SHUCKLE": "霉",
    "HERACROSS": "独角",
    "SNEASEL": "利爪",
    "TEDDIURSA": "小熊",
    "URSARING": "冬眠",
    "SLUGMA": "熔岩",
    "MAGCARGO": "熔岩",
    "SWINUB": "猪",
    "PILOSWINE": "野猪",
    "CORSOLA": "珊瑚",
    "REMORAID": "喷射",
    "OCTILLERY": "喷射",
    "DELIBIRD": "派送",
    "MANTINE": "风筝",
    "SKARMORY": "铠鸟",
    "HOUNDOUR": "暗",
    "HOUNDOOM": "暗",
    "KINGDRA": "龙",
    "PHANPY": "长鼻",
    "DONPHAN": "铠甲",
    "PORYGON2": "虚拟",
    "STANTLER": "大角",
    "SMEARGLE": "画家",
    "TYROGUE": "角斗",
    "HITMONTOP": "倒立",
    "SMOOCHUM": "亲吻",
    "ELEKID": "电",
    "MAGBY": "炭火",
    "MILTANK": "奶牛",
    "BLISSEY": "幸福",
    "RAIKOU": "雷电",
    "ENTEI": "火山",
    "SUICUNE": "极光",
    "LARVITAR": "岩皮",
    "PUPITAR": "硬壳",
    "TYRANITAR": "铠甲",
    "LUGIA": "潜水",
    "HO_OH": "彩虹",
    "CELEBI": "时空",
    "TREECKO": "林蜥",
    "GROVYLE": "林蜥",
    "SCEPTILE": "森林",
    "TORCHIC": "小鸡",
    "COMBUSKEN": "幼鸟",
    "BLAZIKEN": "烈焰",
    "MUDKIP": "泥鱼",
    "MARSHTOMP": "泥鱼",
    "SWAMPERT": "泥鱼",
    "POOCHYENA": "咬",
    "MIGHTYENA": "咬",
    "ZIGZAGOON": "小浣熊",
    "LINOONE": "奔走",
    "WURMPLE": "虫",
    "SILCOON": "蛹",
    "BEAUTIFLY": "蝴蝶",
    "CASCOON": "蛹",
    "DUSTOX": "毒蛾",
    "LOTAD": "水草",
    "LOMBRE": "欢乐",
    "LUDICOLO": "悠闲",
    "SEEDOT": "橡果",
    "NUZLEAF": "狡猾",
    "SHIFTRY": "邪恶",
    "TAILLOW": "小燕",
    "SWELLOW": "燕子",
    "WINGULL": "海鸥",
    "PELIPPER": "水鸟",
    "RALTS": "感受",
    "KIRLIA": "情感",
    "GARDEVOIR": "拥抱",
    "SURSKIT": "水黾",
    "MASQUERAIN": "眼球",
    "SHROOMISH": "蘑菇",
    "BRELOOM": "蘑菇",
    "SLAKOTH": "懒散",
    "VIGOROTH": "野猴",
    "SLAKING": "懒惰",
    "NINCADA": "见习",
    "NINJASK": "忍者",
    "SHEDINJA": "蜕壳",
    "WHISMUR": "低语",
    "LOUDRED": "大声",
    "EXPLOUD": "巨响",
    "MAKUHITA": "毅力",
    "HARIYAMA": "推掌",
    "AZURILL": "圆点",
    "NOSEPASS": "罗盘",
    "SKITTY": "小猫",
    "DELCATTY": "优雅",
    "SABLEYE": "黑暗",
    "MAWILE": "欺诈",
    "ARON": "铁铠",
    "LAIRON": "铁铠",
    "AGGRON": "铁铠",
    "MEDITITE": "冥想",
    "MEDICHAM": "冥想",
    "ELECTRIKE": "闪电",
    "MANECTRIC": "放电",
    "PLUSLE": "欢呼",
    "MINUN": "欢呼",
    "VOLBEAT": "萤火虫",
    "ILLUMISE": "萤火虫",
    "ROSELIA": "荆棘",
    "GULPIN": "毒袋",
    "SWALOT": "胃袋",
    "CARVANHA": "凶猛",
    "SHARPEDO": "残暴",
    "WAILMER": "球鲸",
    "WAILORD": "浮鲸",
    "NUMEL": "麻木",
    "CAMERUPT": "喷火",
    "TORKOAL": "煤炭",
    "SPOINK": "弹跳",
    "GRUMPIG": "操纵",
    "SPINDA": "斑点",
    "TRAPINCH": "蚁穴",
    "VIBRAVA": "振动",
    "FLYGON": "神秘",
    "CACNEA": "仙人掌",
    "CACTURNE": "稻草人",
    "SWABLU": "棉鸟",
    "ALTARIA": "嗡鸣",
    "ZANGOOSE": "猫鼬",
    "SEVIPER": "牙蛇",
    "LUNATONE": "陨石",
    "SOLROCK": "陨石",
    "BARBOACH": "胡须",
    "WHISCASH": "胡须",
    "CORPHISH": "恶霸",
    "CRAWDAUNT": "流氓",
    "BALTOY": "泥偶",
    "CLAYDOL": "泥偶",
    "LILEEP": "海百合",
    "CRADILY": "藤壶",
    "ANORITH": "古虾",
    "ARMALDO": "铠甲",
    "FEEBAS": "鱼",
    "MILOTIC": "温柔",
    "CASTFORM": "天气",
    "KECLEON": "变色",
    "SHUPPET": "玩偶",
    "BANETTE": "提线",
    "DUSKULL": "安魂",
    "DUSCLOPS": "招手",
    "TROPIUS": "水果",
    "CHIMECHO": "风铃",
    "ABSOL": "灾厄",
    "WYNAUT": "明亮",
    "SNORUNT": "雪帽",
    "GLALIE": "脸",
    "SPHEAL": "拍手",
    "SEALEO": "滚球",
    "WALREIN": "破冰",
    "CLAMPERL": "双壳贝",
    "HUNTAIL": "深海",
    "GOREBYSS": "南海",
    "RELICANTH": "长寿",
    "LUVDISC": "相会",
    "BAGON": "岩头",
    "SHELGON": "忍耐",
    "SALAMENCE": "龙",
    "BELDUM": "铁球",
    "METANG": "铁爪",
    "METAGROSS": "铁腿",
    "REGIROCK": "岩峰",
    "REGICE": "冰山",
    "REGISTEEL": "铁",
    "LATIAS": "无限",
    "LATIOS": "无限",
    "KYOGRE": "海渊",
    "GROUDON": "大陆",
    "RAYQUAZA": "天空",
    "JIRACHI": "祈愿",
    "DEOXYS": "基因",
}


def is_gb2312(ch: str) -> bool:
    """Check if a Chinese character is in GB2312 charset."""
    try:
        ch.encode('gb2312')
        return True
    except UnicodeEncodeError:
        return False


def verify_translations():
    """Verify all translation characters are in GB2312."""
    bad = []
    all_chars = set()
    for name, chn in TRANSLATIONS.items():
        for ch in chn:
            all_chars.add(ch)
            if not is_gb2312(ch):
                bad.append((name, chn, ch, hex(ord(ch))))

    if bad:
        print("ERROR: Non-GB2312 characters found:")
        for name, chn, ch, cp in bad:
            print(f"  {name}: '{chn}' has char '{ch}' (U+{cp})")
        return False

    print(f"All {len(all_chars)} unique Chinese characters are GB2312 compliant.")
    return True


def translate_file(filepath: Path) -> None:
    """Translate the file in-place using NATIONAL_DEX identifiers as keys."""
    content = filepath.read_text(encoding='utf-8', newline='')
    lines = content.split('\n')

    # Pattern to match [NATIONAL_DEX_XXX] =
    dex_pattern = re.compile(r'^\s*\[NATIONAL_DEX_(\w+)\]\s*=\s*$')
    # Pattern to match .categoryName = _("...")
    # Allow either _("XXXX") (uppercase English) or _("{CHN}...") (already translated)
    cat_pattern_eng = re.compile(r'^(\s*\.categoryName = _\(")([A-Z ][A-Z ]*)("\),)\s*$')
    cat_pattern_chn = re.compile(r'^\s*\.categoryName = _\("\{CHN\}.*"\),\s*$')

    current_dex = None
    replaced = 0
    skipped_already_translated = 0
    missing_translations = []
    not_matched = []

    for i, line in enumerate(lines, start=1):
        m = dex_pattern.match(line)
        if m:
            current_dex = m.group(1)
            continue

        # Check if this is a categoryName line
        m_eng = cat_pattern_eng.match(line)
        m_chn = cat_pattern_chn.match(line)
        if m_chn:
            skipped_already_translated += 1
            current_dex = None
            continue
        if m_eng:
            if current_dex is None:
                not_matched.append((i, line, "no preceding NATIONAL_DEX"))
                continue
            if current_dex not in TRANSLATIONS:
                missing_translations.append((i, current_dex, line))
                current_dex = None
                continue
            chn = TRANSLATIONS[current_dex]
            new_line = f'{m_eng.group(1)}{{CHN}}{chn}{m_eng.group(3)}'
            lines[i - 1] = new_line
            replaced += 1
            current_dex = None

    print(f"Replaced {replaced} entries")
    print(f"Skipped {skipped_already_translated} already-translated entries")
    if missing_translations:
        print(f"WARNING: {len(missing_translations)} entries have no translation:")
        for i, dex, line in missing_translations[:20]:
            print(f"  Line {i} [{dex}]: {line!r}")
    if not_matched:
        print(f"WARNING: {len(not_matched)} categoryName lines had no preceding NATIONAL_DEX:")
        for i, line, why in not_matched[:20]:
            print(f"  Line {i}: {line!r} ({why})")

    new_content = '\n'.join(lines)
    filepath.write_text(new_content, encoding='utf-8', newline='')


def verify_replacements(filepath: Path) -> None:
    """Verify all categoryName entries now have {CHN} prefix."""
    content = filepath.read_text(encoding='utf-8', newline='')
    lines = content.split('\n')

    pattern_chn = re.compile(r'^\s*\.categoryName = _\("\{CHN\}.*"\),\s*$')
    pattern_any = re.compile(r'^\s*\.categoryName = _\(.*"\),\s*$')

    chn_count = 0
    non_chn_count = 0
    for i, line in enumerate(lines, start=1):
        if pattern_any.match(line):
            if pattern_chn.match(line):
                chn_count += 1
            else:
                non_chn_count += 1
                print(f"  Line {i} NOT translated: {line!r}")

    print(f"Verified: {chn_count} translated, {non_chn_count} not translated")


def main():
    filepath = Path(__file__).parent.parent / 'src' / 'data' / 'pokemon' / 'pokedex_entries.h'
    print(f"Target file: {filepath}")
    print(f"Translations in dict: {len(TRANSLATIONS)}")

    if not verify_translations():
        sys.exit(1)

    translate_file(filepath)
    verify_replacements(filepath)


if __name__ == '__main__':
    main()
