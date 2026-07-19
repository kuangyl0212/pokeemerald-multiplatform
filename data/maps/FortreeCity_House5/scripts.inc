FortreeCity_House5_MapScripts::
	.byte 0

FortreeCity_House5_EventScript_PokefanF::
	msgbox FortreeCity_House5_Text_TreeHousesAreGreat, MSGBOX_NPC
	end

FortreeCity_House5_EventScript_Man::
	msgbox FortreeCity_House5_Text_AdaptedToNature, MSGBOX_NPC
	end

FortreeCity_House5_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox FortreeCity_House5_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House5_Text_TreeHousesAreGreat:
	.string "{CHN}茵郁的树屋真棒！\p"
	.string "我觉得这里是\n"
	.string "和宝可梦一起生活的第一城市。$"

FortreeCity_House5_Text_AdaptedToNature:
	.string "{CHN}宝可梦和人类\n"
	.string "为了生存而适应自然。\p"
	.string "没有必要让自然\n"
	.string "屈从于我们想要的生活方式。$"

FortreeCity_House5_Text_Zigzagoon:
	.string "{CHN}蛇纹熊：噗呼！$"
