SootopolisCity_House4_MapScripts::
	.byte 0

SootopolisCity_House4_EventScript_Man::
	msgbox SootopolisCity_House4_Text_AncientTreasuresWaitingInSea, MSGBOX_NPC
	end

SootopolisCity_House4_EventScript_Woman::
	msgbox SootopolisCity_House4_Text_StrollUnderwaterWithPokemon, MSGBOX_NPC
	end

SootopolisCity_House4_EventScript_Azumarill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZUMARILL, CRY_MODE_NORMAL
	msgbox SootopolisCity_House4_Text_Azumarill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SootopolisCity_House4_Text_AncientTreasuresWaitingInSea:
	.string "{CHN}听好了，告诉你一件\n"
	.string "好事。\p"
	.string "据说这片海域里有一座\n"
	.string "古代遗迹。\p"
	.string "说不定有什么宝藏\n"
	.string "正等着被人发现呢。$"

SootopolisCity_House4_Text_StrollUnderwaterWithPokemon:
	.string "{CHN}古代宝藏……\p"
	.string "要是真有就好了，不过\n"
	.string "就算没有，能和我的\l"
	.string "宝可梦一起在水下\l"
	.string "漫步也很美。$"

SootopolisCity_House4_Text_Azumarill:
	.string "{CHN}玛力露丽：玛力露丽。$"

