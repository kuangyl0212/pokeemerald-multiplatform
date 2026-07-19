MagmaHideout_3F_2R_MapScripts::
	.byte 0

MagmaHideout_3F_2R_EventScript_Grunt10::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_10, MagmaHideout_3F_2R_Text_Grunt10Intro, MagmaHideout_3F_2R_Text_Grunt10Defeat
	msgbox MagmaHideout_3F_2R_Text_Grunt10PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_2R_Text_Grunt10Intro:
	.string "{CHN}我明白首领说的每一句话。\n"
	.string "但是你知道吗？\p"
	.string "像挖出超古代\n"
	.string "宝可梦，还有抢走\l"
	.string "别人的陨石之类的事…\p"
	.string "我觉得我们有点过分了。\n"
	.string "你觉得呢？$"

MagmaHideout_3F_2R_Text_Grunt10Defeat:
	.string "{CHN}是啊，我觉得我们\n"
	.string "确实做错了什么。$"

MagmaHideout_3F_2R_Text_Grunt10PostBattle:
	.string "{CHN}你知道吗，输给你让我清醒了。\p"
	.string "下次见到首领，\n"
	.string "我要问问他我们做的事。$"
