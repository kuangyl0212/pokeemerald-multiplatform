GraniteCave_1F_MapScripts::
	.byte 0

GraniteCave_1F_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_FLASH, GraniteCave_1F_EventScript_ReceivedFlash
	msgbox GraniteCave_1F_Text_GetsDarkAheadHereYouGo, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLASH
	setflag FLAG_RECEIVED_HM_FLASH
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_EventScript_ReceivedFlash::
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_Text_GetsDarkAheadHereYouGo:
	.string "{CHN}嘿，你。\n"
	.string "前面会变得非常暗。\l"
	.string "要探索会很困难。\p"
	.string "之前经过的那个人……\n"
	.string "是大吾吧，我想。\p"
	.string "他会使用闪光，所以他应该\n"
	.string "没问题，但是……\p"
	.string "嗯，对我们登山男来说，帮助\n"
	.string "遇到的人是我们的座右铭。\p"
	.string "给你，我把这个传给你。$"

GraniteCave_1F_Text_ExplainFlash:
	.string "{CHN}把秘传招式闪光教给\n"
	.string "一只宝可梦并使用它。\p"
	.string "它能照亮即使是\n"
	.string "漆黑的洞窟。\p"
	.string "但是，要使用它，你需要武斗镇\n"
	.string "宝可梦道馆的道馆徽章。$"

