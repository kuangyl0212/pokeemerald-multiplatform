MagmaHideout_4F_MapScripts::
	.byte 0

MagmaHideout_4F_EventScript_Maxie::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	msgbox MagmaHideout_4F_Text_MaxieAwakenGroudon, MSGBOX_DEFAULT
	closemessage
	delay 20
	setvar VAR_RESULT, 1
	playse SE_M_DETECT
	dofieldeffectsparkle 18, 42, 0
	waitfieldeffect FLDEFF_SPARKLE
	setvar VAR_RESULT, 1
	playfanfare MUS_AWAKEN_LEGEND
	playse SE_ORB
	special DoOrbEffect
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 150
	removeobject LOCALID_MAGMA_HIDEOUT_4F_GROUDON_SLEEPING
	addobject LOCALID_MAGMA_HIDEOUT_4F_GROUDON
	waitstate
	delay 60
	applymovement LOCALID_MAGMA_HIDEOUT_4F_GROUDON, MagmaHideout_4F_Movement_GroudonApproach
	waitmovement 0
	special FadeOutOrbEffect
	waitstate
	setvar VAR_0x8004, 1  /* vertical pan*/
	setvar VAR_0x8005, 1  /* horizontal pan*/
	setvar VAR_0x8006, 8  /* num shakes*/
	setvar VAR_0x8007, 5  /* shake delay*/
	special ShakeCamera
	waitstate
	applymovement LOCALID_MAGMA_HIDEOUT_4F_GROUDON, MagmaHideout_4F_Movement_GroudonExit
	waitmovement 0
	removeobject LOCALID_MAGMA_HIDEOUT_4F_GROUDON
	delay 4
	setvar VAR_0x8004, 2  /* vertical pan*/
	setvar VAR_0x8005, 2  /* horizontal pan*/
	setvar VAR_0x8006, 8  /* num shakes*/
	setvar VAR_0x8007, 5  /* shake delay*/
	special ShakeCamera
	waitstate
	delay 30
	applymovement LOCALID_MAGMA_HIDEOUT_4F_MAXIE, MagmaHideout_4F_Movement_MaxieLookAround
	waitmovement 0
	msgbox MagmaHideout_4F_Text_MaxieGroudonWhatsWrong, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_MAGMA_HIDEOUT_4F_MAXIE, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MagmaHideout_4F_Text_MaxieOhItWasYou, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_MAXIE_MAGMA_HIDEOUT, MagmaHideout_4F_Text_MaxieDefeat
	msgbox MagmaHideout_4F_Text_MaxieImGoingAfterGroudon, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_SLATEPORT_CITY_CAPTAIN_STERN
	clearflag FLAG_HIDE_SLATEPORT_CITY_GABBY_AND_TY
	setvar VAR_SLATEPORT_CITY_STATE, 1
	setflag FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT
	setvar VAR_SLATEPORT_HARBOR_STATE, 1
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_MAGMA_HIDEOUT_4F_MAXIE
	removeobject LOCALID_MAGMA_HIDEOUT_4F_GRUNT_1
	removeobject LOCALID_MAGMA_HIDEOUT_4F_GRUNT_2
	removeobject LOCALID_MAGMA_HIDEOUT_4F_GRUNT_3
	removeobject LOCALID_MAGMA_HIDEOUT_4F_TABITHA
	setflag FLAG_HIDE_MAGMA_HIDEOUT_GRUNTS
	fadescreen FADE_FROM_BLACK
	releaseall
	end

MagmaHideout_4F_Movement_GroudonApproach:
	delay_16
	delay_16
	walk_slow_down
	delay_16
	delay_16
	delay_16
	walk_slow_down
	delay_16
	delay_16
	delay_16
	step_end

MagmaHideout_4F_Movement_GroudonExit:
	slide_up
	slide_up
	step_end

MagmaHideout_4F_Movement_MaxieLookAround:
	face_left
	delay_16
	face_right
	delay_16
	face_left
	delay_16
	face_right
	delay_16
	face_up
	delay_16
	delay_16
	step_end

MagmaHideout_4F_EventScript_Grunt11::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_11, MagmaHideout_4F_Text_Grunt11Intro, MagmaHideout_4F_Text_Grunt11Defeat
	msgbox MagmaHideout_4F_Text_Grunt11PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Grunt12::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_12, MagmaHideout_4F_Text_Grunt12Intro, MagmaHideout_4F_Text_Grunt12Defeat
	msgbox MagmaHideout_4F_Text_Grunt12PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Grunt13::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_13, MagmaHideout_4F_Text_Grunt13Intro, MagmaHideout_4F_Text_Grunt13Defeat
	msgbox MagmaHideout_4F_Text_Grunt13PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Tabitha::
	trainerbattle_single TRAINER_TABITHA_MAGMA_HIDEOUT, MagmaHideout_4F_Text_TabithaIntro, MagmaHideout_4F_Text_TabithaDefeat
	msgbox MagmaHideout_4F_Text_TabithaPostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_Text_Grunt11Intro:
	.string "{CHN}我也想看固拉多，但他们\n"
	.string "连它的尾巴都不让我看…\p"
	.string "让我觉得好郁闷。\p"
	.string "哦，不！\n"
	.string "我把固拉多说出来了！$"

MagmaHideout_4F_Text_Grunt11Defeat:
	.string "{CHN}看来心不静\n"
	.string "就赢不了…$"

MagmaHideout_4F_Text_Grunt11PostBattle:
	.string "{CHN}固拉多到底有没有尾巴呢？$"

MagmaHideout_4F_Text_Grunt12Intro:
	.string "{CHN}呼哈哈哈！\n"
	.string "快了！很快！\l"
	.string "我们的宏伟目标就要实现了！$"

MagmaHideout_4F_Text_Grunt12Defeat:
	.string "{CHN}呃呃…\n"
	.string "我都走到这一步了，结果这样？$"

MagmaHideout_4F_Text_Grunt12PostBattle:
	.string "{CHN}赤焰松大人！\n"
	.string "有个入侵者朝您那边去了！$"

MagmaHideout_4F_Text_Grunt13Intro:
	.string "{CHN}你还没完呢！\n"
	.string "别想轻易从我这里过去！$"

MagmaHideout_4F_Text_Grunt13Defeat:
	.string "{CHN}我就这么容易被打倒吗？$"

MagmaHideout_4F_Text_Grunt13PostBattle:
	.string "{CHN}再…再来一场吧…$"

MagmaHideout_4F_Text_TabithaIntro:
	.string "{CHN}嘿嘿嘿！\n"
	.string "你都到这里了，我就告诉你！\p"
	.string "没错！\n"
	.string "前面，固拉多正在沉睡！\p"
	.string "赤焰松几秒钟前\n"
	.string "刚去找固拉多了！\p"
	.string "它马上就要醒了！\n"
	.string "嘿嘿！嘿嘿嘿！$"

MagmaHideout_4F_Text_TabithaDefeat:
	.string "{CHN}又被打倒了…\n"
	.string "嘿嘿…$"

MagmaHideout_4F_Text_TabithaPostBattle:
	.string "{CHN}…在你跟我浪费时间的时候，\n"
	.string "赤焰松应该已经唤醒固拉多了…$"

MagmaHideout_4F_Text_MaxieAwakenGroudon:
	.string "{CHN}赤焰松：固拉多…\p"
	.string "没什么能把你从\n"
	.string "岩浆中的沉睡唤醒…\p"
	.string "这颗蓝色宝珠就是你寻求的。\n"
	.string "不是吗？\p"
	.string "我把蓝色宝珠带来了。\n"
	.string "让它的光芒唤醒你吧！\p"
	.string "并向我展示…\n"
	.string "向我展示你全部的力量！$"

MagmaHideout_4F_Text_MaxieGroudonWhatsWrong:
	.string "{CHN}赤焰松：固拉多！\n"
	.string "你怎么了？\p"
	.string "蓝色宝珠不是关键吗？\p"
	.string "固拉多！\n"
	.string "你去哪了…$"

MagmaHideout_4F_Text_MaxieOhItWasYou:
	.string "{CHN}赤焰松：哦，是你？\p"
	.string "我看到你在这那\n"
	.string "不请自来地乱转…\p"
	.string "我明白了！\n"
	.string "你一定耍了什么花招！$"

MagmaHideout_4F_Text_MaxieDefeat:
	.string "{CHN}你怎么这么擅长\n"
	.string "操控宝可梦？$"

MagmaHideout_4F_Text_MaxieImGoingAfterGroudon:
	.string "{CHN}赤焰松：固拉多逃跑\n"
	.string "一定有什么原因…\p"
	.string "这就是你想说的，\n"
	.string "对吧？\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "哼…\n"
	.string "你以为我不知道吗？\p"
	.string "固拉多既然走了，这破火山\n"
	.string "也就没必要待了。\p"
	.string "我要去追固拉多，\n"
	.string "我们就到此为止！$"
