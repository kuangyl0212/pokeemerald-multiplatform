RustboroCity_CuttersHouse_MapScripts::
	.byte 0

RustboroCity_CuttersHouse_EventScript_Cutter::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_CUT, RustboroCity_CuttersHouse_EventScript_ExplainCut
	msgbox RustboroCity_CuttersHouse_Text_YouCanPutThisHMToGoodUse, MSGBOX_DEFAULT
	giveitem ITEM_HM_CUT
	setflag FLAG_RECEIVED_HM_CUT
	msgbox RustboroCity_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
	release
	end

RustboroCity_CuttersHouse_EventScript_ExplainCut::
	msgbox RustboroCity_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
	release
	end

RustboroCity_CuttersHouse_EventScript_Lass::
	msgbox RustboroCity_CuttersHouse_Text_DadHelpedClearLandOfTrees, MSGBOX_NPC
	end

RustboroCity_CuttersHouse_Text_YouCanPutThisHMToGoodUse:
	.string "{CHN}那坚毅的表情…\n"
	.string "那敏捷的动作…\l"
	.string "还有你训练有素的宝可梦…\p"
	.string "你显然是个熟练的训练家！\p"
	.string "不，等等，什么都别说.\n"
	.string "我一看就知道.\p"
	.string "我相信你一定能好好利用\n"
	.string "这台秘传学习器.\p"
	.string "不用客气或害羞.\n"
	.string "来，拿着吧！$"

RustboroCity_CuttersHouse_Text_ExplainCut:
	.string "{CHN}那台秘传学习器，简称HM，\n"
	.string "装的是居合劈.\p"
	.string "秘传学习器招式是宝可梦可以在\n"
	.string "对战之外使用的招式.\p"
	.string "任何学会居合劈的宝可梦，\n"
	.string "只要训练家获得了\l"
	.string "岩石徽章，就能砍倒细小的树木.\p"
	.string "而且，与招式学习器不同，\n"
	.string "秘传学习器可以多次使用.$"

RustboroCity_CuttersHouse_Text_DadHelpedClearLandOfTrees:
	.string "{CHN}当他们扩建卡那兹市时，\n"
	.string "我爸爸也帮了忙.\p"
	.string "他让宝可梦使用居合劈清除\n"
	.string "了地上的树木.$"

