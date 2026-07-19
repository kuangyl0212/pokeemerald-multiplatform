AquaHideout_B2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AquaHideout_B2F_OnTransition
	.byte 0

AquaHideout_B2F_OnTransition:
	call_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, AquaHideout_B2F_EventScript_PreventMattNoticing
	end

AquaHideout_B2F_EventScript_PreventMattNoticing::
	setvar VAR_TEMP_1, 1
	return

AquaHideout_B2F_EventScript_MattNoticePlayer::
	lockall
	setvar VAR_0x8008, LOCALID_AQUA_HIDEOUT_MATT
	playse SE_PIN
	applymovement VAR_0x8008, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	setvar VAR_TEMP_1, 1
	releaseall
	end

AquaHideout_B2F_EventScript_Matt::
	trainerbattle_single TRAINER_MATT, AquaHideout_B2F_Text_MattIntro, AquaHideout_B2F_Text_MattDefeat, AquaHideout_B2F_EventScript_SubmarineEscape
	msgbox AquaHideout_B2F_Text_MattPostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_B2F_EventScript_SubmarineEscape::
	setvar VAR_0x8008, LOCALID_AQUA_HIDEOUT_MATT
	setvar VAR_0x8009, LOCALID_AQUA_HIDEOUT_SUBMARINE
	applymovement VAR_0x8008, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 20
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	msgbox AquaHideout_B2F_Text_OurBossGotThroughHisPreparations, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_0x8008, Common_Movement_WalkInPlaceFasterLeft
	applymovement VAR_0x8009, AquaHideout_B2F_Movement_SumbarineDepartLeft
	waitmovement 0
	removeobject VAR_0x8009
	delay 20
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	msgbox AquaHideout_B2F_Text_MattPostBattle, MSGBOX_DEFAULT
	setflag FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE
	setflag FLAG_HIDE_LILYCOVE_CITY_AQUA_GRUNTS
	release
	end

AquaHideout_B2F_Movement_SumbarineDepartLeft:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

/* Unused*/
AquaHideout_B2F_Movement_SumbarineDepartRight:
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

AquaHideout_B2F_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_4, AquaHideout_B2F_Text_Grunt4Intro, AquaHideout_B2F_Text_Grunt4Defeat, AquaHideout_B2F_EventScript_Grunt4Defeated
	msgbox AquaHideout_B2F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_EventScript_Grunt4Defeated::
	msgbox AquaHideout_B2F_Text_Grunt4PostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_B2F_EventScript_Grunt6::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_6, AquaHideout_B2F_Text_Grunt6Intro, AquaHideout_B2F_Text_Grunt6Defeat
	msgbox AquaHideout_B2F_Text_Grunt6PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_EventScript_Grunt8::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_8, AquaHideout_B2F_Text_Grunt8Intro, AquaHideout_B2F_Text_Grunt8Defeat
	msgbox AquaHideout_B2F_Text_Grunt8PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_Text_MattIntro:
	.string "{CHN}嘿嘿嘿…\p"
	.string "已经到这里了？\n"
	.string "我们小看你了！\p"
	.string "但到此为止了！\p"
	.string "我比你见过的队员\n"
	.string "要厉害一些。\p"
	.string "我不是在拖延时间。\n"
	.string "我要把你粉碎！$"

AquaHideout_B2F_Text_MattDefeat:
	.string "{CHN}嘿嘿嘿…\n"
	.string "我也输了…$"

AquaHideout_B2F_Text_OurBossGotThroughHisPreparations:
	.string "{CHN}嘿嘿嘿！\p"
	.string "在我跟你周旋的时候，我们老大\n"
	.string "已经完成了准备！$"

AquaHideout_B2F_Text_MattPostBattle:
	.string "{CHN}嘿嘿嘿！\p"
	.string "我们老大已经前往\n"
	.string "海底的某个洞窟了！\p"
	.string "如果你要追的话，最好\n"
	.string "去水静市外面那片广阔的\l"
	.string "大海找找。\p"
	.string "但你能找到吗？\n"
	.string "嘿嘿嘿！$"

AquaHideout_B2F_Text_Grunt4Intro:
	.string "{CHN}哇哈哈，我等得不耐烦了！\n"
	.string "你也得跟我打一场！$"

AquaHideout_B2F_Text_Grunt4Defeat:
	.string "{CHN}等得不耐烦…\n"
	.string "输得晕头转向…$"

AquaHideout_B2F_Text_Grunt4PostBattle:
	.string "{CHN}老大…\n"
	.string "这样够了吗？$"

AquaHideout_B2F_Text_Grunt6Intro:
	.string "{CHN}传送板，基地引以为豪的\n"
	.string "玩意儿！\p"
	.string "你根本不知道自己在哪，\n"
	.string "对吧？\p"
	.string "让敌人慌张疲劳，然后\n"
	.string "给予痛击！这就是我们的计划！$"

AquaHideout_B2F_Text_Grunt6Defeat:
	.string "{CHN}你怎么回事？\n"
	.string "一点都不累！$"

AquaHideout_B2F_Text_Grunt6PostBattle:
	.string "{CHN}说起来… 我不记得\n"
	.string "把大师球放在哪里了。\p"
	.string "如果我守不好，我们老大\n"
	.string "会骂死我…$"

AquaHideout_B2F_Text_Grunt8Intro:
	.string "{CHN}我加入水舰队时，第一件\n"
	.string "要学的事就是这些\l"
	.string "传送板是怎么连接的。$"

AquaHideout_B2F_Text_Grunt8Defeat:
	.string "{CHN}我太专注于想传送板\n"
	.string "的事了…$"

AquaHideout_B2F_Text_Grunt8PostBattle:
	.string "{CHN}我得学学怎样才能\n"
	.string "战斗得更有效率…$"
