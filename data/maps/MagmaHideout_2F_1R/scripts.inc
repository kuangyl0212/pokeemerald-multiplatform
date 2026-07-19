MagmaHideout_2F_1R_MapScripts::
	.byte 0

MagmaHideout_2F_1R_EventScript_Grunt14::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_14, MagmaHideout_2F_1R_Text_Grunt14Intro, MagmaHideout_2F_1R_Text_Grunt14Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt14PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_3, MagmaHideout_2F_1R_Text_Grunt3Intro, MagmaHideout_2F_1R_Text_Grunt3Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_4, MagmaHideout_2F_1R_Text_Grunt4Intro, MagmaHideout_2F_1R_Text_Grunt4Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_5, MagmaHideout_2F_1R_Text_Grunt5Intro, MagmaHideout_2F_1R_Text_Grunt5Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_Text_Grunt14Intro:
	.string "{CHN}什么，什么，什么？\p"
	.string "只有火焰队队员才能\n"
	.string "在这里！\p"
	.string "但你穿的\n"
	.string "不是火焰队的制服…\p"
	.string "你引起了我的怀疑！\n"
	.string "跟我打一场！$"

MagmaHideout_2F_1R_Text_Grunt14Defeat:
	.string "{CHN}哎呀呀…\n"
	.string "我作为火焰队队员的尊严…$"

MagmaHideout_2F_1R_Text_Grunt14PostBattle:
	.string "{CHN}如果你怕冷，应该\n"
	.string "加入火焰队。$"

MagmaHideout_2F_1R_Text_Grunt3Intro:
	.string "{CHN}站住！\p"
	.string "你不会真以为我会\n"
	.string "闭嘴让你大摇大摆地过去吧？$"

MagmaHideout_2F_1R_Text_Grunt3Defeat:
	.string "{CHN}哇哦！\n"
	.string "我认输！$"

MagmaHideout_2F_1R_Text_Grunt3PostBattle:
	.string "{CHN}也许我不拦你\n"
	.string "让你直接过去更好…$"

MagmaHideout_2F_1R_Text_Grunt4Intro:
	.string "{CHN}啊哈！\n"
	.string "入侵者！$"

MagmaHideout_2F_1R_Text_Grunt4Defeat:
	.string "{CHN}嘎啊啊！$"

MagmaHideout_2F_1R_Text_Grunt4PostBattle:
	.string "{CHN}我已经输了。\p"
	.string "我还需要继续\n"
	.string "兜圈子吗？$"

MagmaHideout_2F_1R_Text_Grunt5Intro:
	.string "{CHN}哦，哦！\n"
	.string "入侵者！$"

MagmaHideout_2F_1R_Text_Grunt5Defeat:
	.string "{CHN}嘟囔…$"

MagmaHideout_2F_1R_Text_Grunt5PostBattle:
	.string "{CHN}其实，我不擅长战斗…$"
