MagmaHideout_3F_1R_MapScripts::
	.byte 0

MagmaHideout_3F_1R_EventScript_Grunt9::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_9, MagmaHideout_3F_1R_Text_Grunt9Intro, MagmaHideout_3F_1R_Text_Grunt9Defeat
	msgbox MagmaHideout_3F_1R_Text_Grunt9PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_1R_EventScript_Grunt16::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_16, MagmaHideout_3F_1R_Text_Grunt16Intro, MagmaHideout_3F_1R_Text_Grunt16Defeat
	msgbox MagmaHideout_3F_1R_Text_Grunt16PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_1R_Text_Grunt9Intro:
	.string "{CHN}我做了什么要被派来\n"
	.string "守这里？\p"
	.string "我左耳朵都烫了！$"

MagmaHideout_3F_1R_Text_Grunt9Defeat:
	.string "{CHN}我中暑了…$"

MagmaHideout_3F_1R_Text_Grunt9PostBattle:
	.string "{CHN}你不觉得在这岩浆满布的火山里\n"
	.string "还戴着兜帽很奇怪吗？$"

MagmaHideout_3F_1R_Text_Grunt16Intro:
	.string "{CHN}我们加入是为了帮首领\n"
	.string "实现他宏大的愿景。\p"
	.string "不管你是水舰队的人\n"
	.string "还是路过的孩子。\p"
	.string "没人能妨碍我们\n"
	.string "还能全身而退！$"

MagmaHideout_3F_1R_Text_Grunt16Defeat:
	.string "{CHN}哦，不！\n"
	.string "你简直不可信！$"

MagmaHideout_3F_1R_Text_Grunt16PostBattle:
	.string "{CHN}听我说。\n"
	.string "火焰队是对的！\p"
	.string "别听水舰队的。\n"
	.string "别相信他们的谎言！$"
