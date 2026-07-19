LavaridgeTown_House_MapScripts::
	.byte 0

LavaridgeTown_House_EventScript_OldMan::
	msgbox LavaridgeTown_House_Text_WifeWarmingEggInHotSprings, MSGBOX_NPC
	end

LavaridgeTown_House_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox LavaridgeTown_House_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

LavaridgeTown_House_Text_WifeWarmingEggInHotSprings:
	.string "{CHN}我妻子在温泉里温蛋。\n"
	.string "她是这么跟我说的。\p"
	.string "她在寄放屋放了两只宝可梦。\n"
	.string "然后它们发现了那颗蛋！$"

LavaridgeTown_House_Text_Zigzagoon:
	.string "{CHN}蛇纹熊：噗咻！$"
