TrainerHill_Entrance_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, TrainerHill_Entrance_OnResume
	map_script MAP_SCRIPT_ON_RETURN_TO_FIELD, TrainerHill_Entrance_OnReturn
	map_script MAP_SCRIPT_ON_TRANSITION, TrainerHill_Entrance_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, TrainerHill_Entrance_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrainerHill_Entrance_OnFrame
	.byte 0

TrainerHill_Entrance_OnTransition:
	setflag FLAG_LANDMARK_TRAINER_HILL
	getplayerxy VAR_TEMP_D, VAR_RESULT
	end

/* Unused*/
TrainerHill_Entrance_OnWarp:
	end

TrainerHill_Entrance_OnResume:
	trainerhill_resumetimer
	setvar VAR_TEMP_0, 0
	trainerhill_getusingereader
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_TryFaceAttendant  @ VAR_RESULT always FALSE here
	setobjectxy LOCALID_PLAYER, 9, 6
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	end

TrainerHill_Entrance_EventScript_TryFaceAttendant::
	trainerhill_getwon
	goto_if_eq VAR_RESULT, TRUE, TrainerHill_Entrance_EventScript_PlayerDontFaceAttendant
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	end

TrainerHill_Entrance_EventScript_PlayerDontFaceAttendant::
	end

TrainerHill_Entrance_OnReturn:
	addobject LOCALID_TRAINER_HILL_NURSE
	addobject LOCALID_TRAINER_HILL_ATTENDANT
	addobject LOCALID_TRAINER_HILL_MAN
	addobject LOCALID_TRAINER_HILL_GIRL
	end

TrainerHill_Entrance_OnLoad:
	call_if_eq VAR_TEMP_D, 17, TrainerHill_Entrance_EventScript_OpenCounterDoor
	end

TrainerHill_Entrance_EventScript_OpenCounterDoor::
	setmetatile 17, 10, METATILE_TrainerHill_GreenFloorTile, FALSE
	return

TrainerHill_Entrance_OnFrame:
	map_script_2 VAR_TEMP_0, 0, TrainerHill_Entrance_EventScript_ExitChallenge
	map_script_2 VAR_TEMP_D, 17, TrainerHill_Entrance_EventScript_ExitElevator
	map_script_2 VAR_TEMP_5, 1, TrainerHill_Entrance_EventScript_EntryTrigger
	map_script_2 VAR_TEMP_1, 1, TrainerHill_EventScript_WarpToEntranceCounter
	.short 0

TrainerHill_Entrance_EventScript_ExitElevator::
	lockall
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PlayerExitElevator
	waitmovement 0
	setmetatile 17, 10, METATILE_TrainerHill_CounterDoor, TRUE
	special DrawWholeMapView
	playse SE_CLICK
	waitse
	setvar VAR_TEMP_D, 0
	releaseall
	end

TrainerHill_Entrance_EventScript_ExitChallenge::
	setvar VAR_TEMP_0, 1
	trainerhill_getstatus
	switch VAR_RESULT
	case TRAINER_HILL_PLAYER_STATUS_LOST, TrainerHill_Entrance_EventScript_ExitChallengeLost
	case TRAINER_HILL_PLAYER_STATUS_ECARD_SCANNED, TrainerHill_Entrance_EventScript_ExitChallengeECard
	case TRAINER_HILL_PLAYER_STATUS_NORMAL, TrainerHill_Entrance_EventScript_EndExitChallenge

TrainerHill_Entrance_EventScript_ExitChallengeLost::
	lockall
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	msgbox TrainerHill_Entrance_Text_TooBadTremendousEffort, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_PlayerExitChallenge

TrainerHill_Entrance_EventScript_ExitChallengeECard::
	lockall
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	msgbox TrainerHill_Entrance_Text_MovedReceptionHereForSwitch, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_PlayerExitChallenge::
	closemessage
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	setvar VAR_TRAINER_HILL_IS_ACTIVE, 0
	special HealPlayerParty
	releaseall
TrainerHill_Entrance_EventScript_EndExitChallenge::
	end

TrainerHill_Entrance_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_TRAINER_HILL_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

TrainerHill_Entrance_EventScript_Attendant::
	lock
	faceplayer
	trainerhill_inchallenge
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_ThanksForPlaying
	msgbox TrainerHill_Entrance_Text_HopeYouGiveItYourBest, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AttendantEnd

TrainerHill_Entrance_EventScript_ThanksForPlaying::
	msgbox TrainerHill_Entrance_Text_ThankYouForPlaying, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_AttendantEnd::
	release
	end

TrainerHill_Entrance_EventScript_EntryTrigger::
	lockall
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_Closed
	msgbox TrainerHill_Entrance_Text_WelcomeToTrainerHill, MSGBOX_DEFAULT
	trainerhill_getsaved
	call_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_SaveGame
	trainerhill_allfloorsused
	goto_if_eq VAR_RESULT, TRUE, TrainerHill_Entrance_EventScript_AllFloorsUsed
	msgbox TrainerHill_Entrance_Text_TrainersUpToFloorX, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AskChallengeTrainers

TrainerHill_Entrance_EventScript_AllFloorsUsed::
	msgbox TrainerHill_Entrance_Text_TrainersInEveryRoom, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_AskChallengeTrainers::
	message TrainerHill_Entrance_Text_LikeToChallengeTrainers
	waitmessage
	multichoice 15, 6, MULTI_YESNOINFO, FALSE
	switch VAR_RESULT
	case 0, TrainerHill_Entrance_EventScript_ChooseChallenge
	case 1, TrainerHill_Entrance_EventScript_CancelEntry
	case 2, TrainerHill_Entrance_EventScript_Info
	case MULTI_B_PRESSED, TrainerHill_Entrance_EventScript_CancelEntry
	end

TrainerHill_Entrance_EventScript_Info::
	msgbox TrainerHill_Entrance_Text_ExplainTrainerHill, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AskChallengeTrainers
	end

TrainerHill_Entrance_EventScript_ChooseChallenge::
	multichoice 13, 2, MULTI_TAG_MATCH_TYPE, FALSE
	switch VAR_RESULT
	case 4, TrainerHill_Entrance_EventScript_CancelEntry
	case MULTI_B_PRESSED, TrainerHill_Entrance_EventScript_CancelEntry
	trainerhill_setmode VAR_RESULT
	setvar VAR_TRAINER_HILL_IS_ACTIVE, 1
	setvar VAR_TEMP_5, 0
	special HealPlayerParty
	msgbox TrainerHill_Entrance_Text_TimeProgessGetSetGo, MSGBOX_DEFAULT
	trainerhill_start
	releaseall
	end

TrainerHill_Entrance_EventScript_CancelEntry::
	setvar VAR_TEMP_5, 0
	msgbox TrainerHill_Entrance_Text_PleaseVisitUsAgain, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

TrainerHill_Entrance_EventScript_SaveGame::
	msgbox TrainerHill_Entrance_Text_SaveGameBeforeEnter, MSGBOX_DEFAULT
	trainerhill_setsaved
	setvar VAR_TEMP_5, 1
	call Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_SaveFailed
	trainerhill_setsaved
	return

TrainerHill_Entrance_EventScript_SaveFailed::
	trainerhill_clearsaved
	goto TrainerHill_Entrance_EventScript_CancelEntry
	end

TrainerHill_Entrance_EventScript_Closed::
	msgbox TrainerHill_Entrance_Text_StillGettingReady, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

TrainerHill_Entrance_Movement_PlayerFaceAttendant:
	face_right
	step_end

TrainerHill_Entrance_Movement_PushPlayerBackFromCounter:
	walk_down
	step_end

/* Unused*/
TrainerHill_Entrance_Movement_FaceUp:
	face_up
	step_end

TrainerHill_Entrance_Movement_PlayerExitElevator:
	walk_down
	walk_down
	step_end

TrainerHill_Entrance_EventScript_Records::
	lockall
	fadescreen FADE_TO_BLACK
	special ShowTrainerHillRecords
	waitstate
	releaseall
	end

TrainerHill_Entrance_EventScript_Man::
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_ManTrainerHillClosed
	msgbox TrainerHill_Entrance_Text_WhatSortOfTrainersAreAhead, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_ManTrainerHillClosed::
	msgbox TrainerHill_Entrance_Text_CantWaitToTestTheWaters, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_Girl::
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_GirlTrainerHillClosed
	msgbox TrainerHill_Entrance_Text_FriendsTryingToReachTimeBoardTop, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_GirlTrainerHillClosed::
	msgbox TrainerHill_Entrance_Text_DoYouKnowWhenTheyOpen, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_set FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_ExpandedPokemart
	pokemart TrainerHill_Entrance_Pokemart_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
TrainerHill_Entrance_Pokemart_Basic:
	.short ITEM_SUPER_POTION
	.short ITEM_ANTIDOTE
	.short ITEM_PARALYZE_HEAL
	.short ITEM_AWAKENING
	.short ITEM_X_SPEED
	.short ITEM_X_SPECIAL
	.short ITEM_X_ATTACK
	.short ITEM_X_DEFEND
	.short ITEM_DIRE_HIT
	.short ITEM_GUARD_SPEC
	.short ITEM_X_ACCURACY
	pokemartlistend

TrainerHill_Entrance_EventScript_ExpandedPokemart::
	pokemart TrainerHill_Entrance_Pokemart_Expanded
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
TrainerHill_Entrance_Pokemart_Expanded:
	.short ITEM_HYPER_POTION
	.short ITEM_MAX_POTION
	.short ITEM_FULL_RESTORE
	.short ITEM_FULL_HEAL
	.short ITEM_REVIVE
	.short ITEM_X_SPEED
	.short ITEM_X_SPECIAL
	.short ITEM_X_ATTACK
	.short ITEM_X_DEFEND
	.short ITEM_DIRE_HIT
	.short ITEM_GUARD_SPEC
	.short ITEM_X_ACCURACY
	pokemartlistend

TrainerHill_Entrance_Text_StillGettingReady:
	.string "{CHN}这里是训练家之丘，\n"
	.string "你可以在这里和许多训练家\l"
	.string "进行组队对战。\p"
	.string "很抱歉，我们还在准备中。\n"
	.string "请以后再来！$"

TrainerHill_Entrance_Text_WelcomeToTrainerHill:
	.string "{CHN}欢迎！\p"
	.string "这里是训练家之丘，\n"
	.string "你可以在这里和许多训练家\l"
	.string "进行组队对战！$"

TrainerHill_Entrance_Text_SaveGameBeforeEnter:
	.string "{CHN}这是你第一次来吗？\p"
	.string "在进入之前，请先\n"
	.string "保存游戏。$"

TrainerHill_Entrance_Text_TrainersUpToFloorX:
	.string "{CHN}让我看看……\n"
	.string "现在这里的训练家有……\p"
	.string "到第{STR_VAR_1}层。$"

TrainerHill_Entrance_Text_TrainersInEveryRoom:
	.string "{CHN}让我看看……\n"
	.string "现在这里的训练家有……\p"
	.string "每个房间里似乎都有\n"
	.string "训练家聚集。$"

TrainerHill_Entrance_Text_LikeToChallengeTrainers:
	.string "{CHN}你想挑战\n"
	.string "等待中的训练家们吗？$"

TrainerHill_Entrance_Text_TimeProgessGetSetGo:
	.string "{CHN}我会为你计时。\n"
	.string "祝你好运！\p"
	.string "各就各位……\p"
	.string "预备……\p"
	.string "开始！$"

TrainerHill_Entrance_Text_PleaseVisitUsAgain:
	.string "{CHN}请再次光临！$"

TrainerHill_Entrance_Text_TooBadTremendousEffort:
	.string "{CHN}那太遗憾了。\p"
	.string "我觉得你在对战中\n"
	.string "付出了巨大的努力。\p"
	.string "请再来挑战吧！$"

TrainerHill_Entrance_Text_HopeYouGiveItYourBest:
	.string "{CHN}希望你能全力以赴。$"

TrainerHill_Entrance_Text_MovedReceptionHereForSwitch:
	.string "{CHN}当训练家换班时，\n"
	.string "现场会很混乱。\p"
	.string "为了避免拥挤，我们把接待柜台\n"
	.string "搬到了这里。\p"
	.string "给您带来不便，敬请谅解。$"

TrainerHill_Entrance_Text_ThankYouForPlaying:
	.string "{CHN}感谢您的游玩！$"

TrainerHill_Entrance_Text_ExplainTrainerHill:
	.string "{CHN}在训练家之丘，我们举办\n"
	.string "一项名为时间竞速的活动。\p"
	.string "这是一场计时赛，\n"
	.string "测量你从这个柜台出发，\l"
	.string "到达屋顶找到我们主人所用的时间。\p"
	.string "最快的时间会公布在\n"
	.string "计时板上——试着和\l"
	.string "你的朋友们竞争吧。\p"
	.string "沿途的训练家对战中，\n"
	.string "经验值和金钱都\l"
	.string "不会获得。$"

/* Unused*/
TrainerHill_Entrance_Text_NeedAtLeastTwoPokemon:
	.string "{CHN}哦，很抱歉，你身上似乎\n"
	.string "只有一只宝可梦。\p"
	.string "你需要至少两只宝可梦\n"
	.string "才能参加这项活动。$"

TrainerHill_Roof_Text_YouFinallyCameBravo:
	.string "{CHN}嗯！嗯！\p"
	.string "你终于来了！\n"
	.string "是的，你到了！\p"
	.string "等等！别说！\n"
	.string "我知道你为什么一个人\l"
	.string "千里迢迢来到这里！\p"
	.string "你想见我，训练家之丘的主人，\n"
	.string "是因为……\p"
	.string "你想和我组成搭档！\n"
	.string "哇哈！\p"
	.string "……嗯？\n"
	.string "不是这样？\p"
	.string "总之，我看着你一路上来。\n"
	.string "精彩的对战！真是出色！$"

TrainerHill_Roof_Text_HaveTheMostMarvelousGift:
	.string "{CHN}对于像你这样出色的人，\n"
	.string "我准备了最棒的礼物！$"

TrainerHill_Roof_Text_FullUpBeBackLaterForThis:
	.string "{CHN}哦，不，东西满了！\n"
	.string "你以后再来拿吧！$"

TrainerHill_Roof_Text_GotHereMarvelouslyQuickly:
	.string "{CHN}哦，等等！你是不是以惊人的速度\n"
	.string "到达这里的？\p"
	.string "太棒了！你不必\n"
	.string "这么急着来见我的！\p"
	.string "太令人高兴了。我会让人更新\n"
	.string "接待处的计时板！$"

TrainerHill_Roof_Text_YouWerentVeryQuick:
	.string "{CHN}但是，哦……\n"
	.string "你到这里来不太快呢。$"

TrainerHill_Roof_Text_ArriveZippierNextTime:
	.string "{CHN}也许下次你能来得更麻利些，\n"
	.string "我会更高兴的。\p"
	.string "到时候，我很乐意和你\n"
	.string "组成搭档！\p"
	.string "后会有期，朋友！$"

/* Unused*/
TrainerHill_Roof_Text_BuiltTrainerHillToFindPartner:
	.string "{CHN}我建造训练家之丘，\n"
	.string "只为一个理由！\p"
	.string "为了寻找最合适的搭档，\n"
	.string "与他组成搭档队伍！$"

TrainerHill_Entrance_Text_ChallengeTime:
	.string "{CHN}{STR_VAR_1}分 {STR_VAR_2}.{STR_VAR_3}秒$"

TrainerHill_Entrance_Text_WhatSortOfTrainersAreAhead:
	.string "{CHN}谁知道前面有什么样的训练家\n"
	.string "和宝可梦组合呢？\p"
	.string "我只知道，我会把挡路的\n"
	.string "任何人都打飞！$"

TrainerHill_Entrance_Text_CantWaitToTestTheWaters:
	.string "{CHN}我听说来自各地的厉害训练家\n"
	.string "都会来这个训练家之丘。\p"
	.string "我迫不及待想试试身手！\p"
	.string "我会把挡路的\n"
	.string "任何人都打飞！$"

TrainerHill_Entrance_Text_FriendsTryingToReachTimeBoardTop:
	.string "{CHN}你看到那边的计时板了吗？\p"
	.string "我和朋友们正在比赛，\n"
	.string "看谁能用最短的时间登顶。$"

TrainerHill_Entrance_Text_DoYouKnowWhenTheyOpen:
	.string "{CHN}你知道这个地方\n"
	.string "什么时候开业吗？\p"
	.string "我在这里等着，\n"
	.string "想成为第一个挑战者！$"

TrainerHill_Elevator_Text_ReturnToReception:
	.string "{CHN}你想回到\n"
	.string "接待柜台吗？$"
