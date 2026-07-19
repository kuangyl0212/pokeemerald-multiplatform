VictoryRoad_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VictoryRoad_1F_OnTransition
	.byte 0

VictoryRoad_1F_OnTransition:
	call_if_eq VAR_VICTORY_ROAD_1F_STATE, 1, VictoryRoad_1F_EventScript_SetEntranceWallyPos1
	call_if_eq VAR_VICTORY_ROAD_1F_STATE, 2, VictoryRoad_1F_EventScript_SetEntranceWallyPos2
	end

VictoryRoad_1F_EventScript_SetEntranceWallyPos1::
	setobjectxyperm LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, 2, 24
	setobjectmovementtype LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, MOVEMENT_TYPE_FACE_DOWN
	return

VictoryRoad_1F_EventScript_SetEntranceWallyPos2::
	setobjectxyperm LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, 3, 24
	setobjectmovementtype LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, MOVEMENT_TYPE_FACE_DOWN
	return

VictoryRoad_1F_EventScript_WallyBattleTrigger1::
	lockall
	setvar VAR_0x8008, 1
	addobject LOCALID_VICTORY_ROAD_ENTRANCE_WALLY
	applymovement LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, VictoryRoad_1F_Movement_WallyApproachPlayer1
	waitmovement 0
	goto VictoryRoad_1F_EventScript_WallyEntranceBattle
	end

VictoryRoad_1F_EventScript_WallyBattleTrigger2::
	lockall
	setvar VAR_0x8008, 2
	addobject LOCALID_VICTORY_ROAD_ENTRANCE_WALLY
	applymovement LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, VictoryRoad_1F_Movement_WallyApproachPlayer2
	waitmovement 0
	goto VictoryRoad_1F_EventScript_WallyEntranceBattle
	end

VictoryRoad_1F_EventScript_WallyEntranceBattle::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox VictoryRoad_1F_Text_WallyNotGoingToLoseAnymore, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_VR_1, VictoryRoad_1F_Text_WallyEntranceDefeat
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_VICTORY_ROAD_ENTRANCE_WALLY
	copyobjectxytoperm LOCALID_VICTORY_ROAD_ENTRANCE_WALLY
	setflag FLAG_DEFEATED_WALLY_VICTORY_ROAD
	copyvar VAR_VICTORY_ROAD_1F_STATE, VAR_0x8008
	releaseall
	end

VictoryRoad_1F_Movement_WallyApproachPlayer1:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

VictoryRoad_1F_Movement_WallyApproachPlayer2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

/* This Wally appears near the entrance once his battle is triggered and remains there until the Hall of Fame is entered*/
VictoryRoad_1F_EventScript_EntranceWally::
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_NPC
	end

/* This Wally appears and remains at the exit after the Hall of Fame is entered*/
VictoryRoad_1F_EventScript_ExitWally::
	trainerbattle_single TRAINER_WALLY_VR_2, VictoryRoad_1F_Text_WallyIntro, VictoryRoad_1F_Text_WallyDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, VictoryRoad_1F_EventScript_RematchWally
	msgbox VictoryRoad_1F_Text_WallyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_RematchWally::
	trainerbattle_rematch TRAINER_WALLY_VR_2, VictoryRoad_1F_Text_WallyIntro, VictoryRoad_1F_Text_WallyDefeat
	msgbox VictoryRoad_1F_Text_WallyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Edgar::
	trainerbattle_single TRAINER_EDGAR, VictoryRoad_1F_Text_EdgarIntro, VictoryRoad_1F_Text_EdgarDefeat
	msgbox VictoryRoad_1F_Text_EdgarPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Albert::
	trainerbattle_single TRAINER_ALBERT, VictoryRoad_1F_Text_AlbertIntro, VictoryRoad_1F_Text_AlbertDefeat
	msgbox VictoryRoad_1F_Text_AlbertPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Hope::
	trainerbattle_single TRAINER_HOPE, VictoryRoad_1F_Text_HopeIntro, VictoryRoad_1F_Text_HopeDefeat
	msgbox VictoryRoad_1F_Text_HopePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Quincy::
	trainerbattle_single TRAINER_QUINCY, VictoryRoad_1F_Text_QuincyIntro, VictoryRoad_1F_Text_QuincyDefeat
	msgbox VictoryRoad_1F_Text_QuincyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Katelynn::
	trainerbattle_single TRAINER_KATELYNN, VictoryRoad_1F_Text_KatelynnIntro, VictoryRoad_1F_Text_KatelynnDefeat
	msgbox VictoryRoad_1F_Text_KatelynnPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_Text_WallyNotGoingToLoseAnymore:
	.string "{CHN}满充：嗨！{PLAYER}！\p"
	.string "看到我在这里，很惊讶吧！\p"
	.string "我能一路走到这里，\n"
	.string "全都是多亏了你！\p"
	.string "{PLAYER}，那次输给你，\n"
	.string "让我变得更强了！\p"
	.string "但我不会再输了！\p"
	.string "我要赢！为了那些给予我勇气和力量\n"
	.string "的宝可梦！\p"
	.string "好了……我来了！$"

VictoryRoad_1F_Text_WallyEntranceDefeat:
	.string "{CHN}哇！\n"
	.string "{PLAYER}，你果然很强！$"

VictoryRoad_1F_Text_WallyPostEntranceBattle:
	.string "{CHN}满充：今天我没能赢你，\n"
	.string "{PLAYER}，但总有一天，我会\l"
	.string "追上你的！$"

VictoryRoad_1F_Text_WallyIntro:
	.string "{CHN}满充：嗨！{PLAYER}！\p"
	.string "自上次以来，我变得更强了！\n"
	.string "我想让你看看，{PLAYER}！\p"
	.string "好了……我来了！$"

VictoryRoad_1F_Text_WallyDefeat:
	.string "{CHN}哇！\n"
	.string "{PLAYER}，你果然很强！$"

VictoryRoad_1F_Text_WallyPostBattle:
	.string "{CHN}满充：这次我也没能赢你……\n"
	.string "但总有一天，{PLAYER}，\l"
	.string "我会追上你的……\p"
	.string "去挑战宝可梦联盟！$"

VictoryRoad_1F_Text_EdgarIntro:
	.string "{CHN}我已经走到这一步好几次了，\n"
	.string "但最后一段路真是漫长……$"

VictoryRoad_1F_Text_EdgarDefeat:
	.string "{CHN}我的梦想再次在这里破灭……$"

VictoryRoad_1F_Text_EdgarPostBattle:
	.string "{CHN}你已经走到这里了。保持这股势头，\n"
	.string "成为冠军吧！\l"
	.string "如果有人能做到，那就是你！$"

VictoryRoad_1F_Text_AlbertIntro:
	.string "{CHN}我大老远跑到这里，可不是为了现在输掉。\n"
	.string "这种可能性根本不存在！$"

VictoryRoad_1F_Text_AlbertDefeat:
	.string "{CHN}不可能……\n"
	.string "我输了？$"

VictoryRoad_1F_Text_AlbertPostBattle:
	.string "{CHN}我在这里输了……\p"
	.string "这意味着我还没有\n"
	.string "成为冠军的资格……$"

VictoryRoad_1F_Text_HopeIntro:
	.string "{CHN}这条看似无尽而艰险的道路，\n"
	.string "果然无愧于胜利之名。$"

VictoryRoad_1F_Text_HopeDefeat:
	.string "{CHN}你的对战方式真精彩……$"

VictoryRoad_1F_Text_HopePostBattle:
	.string "{CHN}你似乎有着成为\n"
	.string "冠军的潜质。$"

VictoryRoad_1F_Text_QuincyIntro:
	.string "{CHN}冠军之路是什么？\n"
	.string "你赢了我就告诉你！$"

VictoryRoad_1F_Text_QuincyDefeat:
	.string "{CHN}好吧！\n"
	.string "干得漂亮！$"

VictoryRoad_1F_Text_QuincyPostBattle:
	.string "{CHN}能安全通过这里——\n"
	.string "这是对任何志在成为宝可梦冠军的训练家\l"
	.string "都要面对的最后考验。\p"
	.string "所以它才被称为\n"
	.string "冠军之路。$"

VictoryRoad_1F_Text_KatelynnIntro:
	.string "{CHN}我对走到这里的人\n"
	.string "没什么好说的。来吧！$"

VictoryRoad_1F_Text_KatelynnDefeat:
	.string "{CHN}真是耻辱……$"

VictoryRoad_1F_Text_KatelynnPostBattle:
	.string "{CHN}哼，继续走吧。\n"
	.string "我才不在乎呢。$"
