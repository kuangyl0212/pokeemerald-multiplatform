MagmaHideout_2F_2R_MapScripts::
	.byte 0

MagmaHideout_2F_2R_EventScript_Grunt15::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_15, MagmaHideout_2F_2R_Text_Grunt15Intro, MagmaHideout_2F_2R_Text_Grunt15Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt15PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt6::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_6, MagmaHideout_2F_2R_Text_Grunt6Intro, MagmaHideout_2F_2R_Text_Grunt6Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt6PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt7::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_7, MagmaHideout_2F_2R_Text_Grunt7Intro, MagmaHideout_2F_2R_Text_Grunt7Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt7PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt8::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_8, MagmaHideout_2F_2R_Text_Grunt8Intro, MagmaHideout_2F_2R_Text_Grunt8Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt8PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_Text_Grunt15Intro:
	.string "{CHN}我跟你无冤无仇。\n"
	.string "我只是在服从命令！$"

MagmaHideout_2F_2R_Text_Grunt15Defeat:
	.string "{CHN}我可能输了，但是…$"

MagmaHideout_2F_2R_Text_Grunt15PostBattle:
	.string "{CHN}我们挖到了难以置信的东西！\n"
	.string "而且，我们拿到了蓝色宝珠！\p"
	.string "现在只剩首领…\n"
	.string "呼呼呼… 哇哈哈哈！$"

MagmaHideout_2F_2R_Text_Grunt6Intro:
	.string "{CHN}我受不了热。也许我\n"
	.string "该加入水舰队才对…$"

MagmaHideout_2F_2R_Text_Grunt6Defeat:
	.string "{CHN}是啊，我可能真的\n"
	.string "不适合火焰队…$"

MagmaHideout_2F_2R_Text_Grunt6PostBattle:
	.string "{CHN}在这种地方待着，\n"
	.string "你不会想念大海吗？$"

MagmaHideout_2F_2R_Text_Grunt7Intro:
	.string "{CHN}这里有时能听到震动。\p"
	.string "是火山在震动吗？\n"
	.string "还是固拉…\p"
	.string "哎呀！\n"
	.string "不，不，当我没说！$"

MagmaHideout_2F_2R_Text_Grunt7Defeat:
	.string "{CHN}你是个火热的对手。\n"
	.string "就像火山一样！$"

MagmaHideout_2F_2R_Text_Grunt7PostBattle:
	.string "{CHN}你这次只是碰巧赢了，\n"
	.string "但那不重要。\p"
	.string "火焰队的目标即将\n"
	.string "实现了！$"

MagmaHideout_2F_2R_Text_Grunt8Intro:
	.string "{CHN}我们有个家伙慌了神，说\n"
	.string "他的火焰队徽章丢了…\p"
	.string "等等！\n"
	.string "是你找到的吗？$"

MagmaHideout_2F_2R_Text_Grunt8Defeat:
	.string "{CHN}我真不敢相信…$"

MagmaHideout_2F_2R_Text_Grunt8PostBattle:
	.string "{CHN}我有一种感觉，我们的计划\n"
	.string "要以失败告终了…$"
