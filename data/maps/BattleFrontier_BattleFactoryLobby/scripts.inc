BattleFrontier_BattleFactoryLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleFactoryLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleFactoryLobby_OnWarp
	.byte 0

BattleFrontier_BattleFactoryLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleFactoryLobby_EventScript_TurnPlayerNorth
	.short 0

BattleFrontier_BattleFactoryLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleFactoryLobby_OnFrame:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattleFactoryLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattleFactoryLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattleFactoryLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattleFactoryLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattleFactoryLobby_EventScript_LostChallenge
	.short 0

BattleFrontier_BattleFactoryLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattleFactoryLobby_EventScript_QuitWithoutSaving::
	lockall
	msgbox BattleFrontier_BattleFactoryLobby_Text_DidntSaveBeforeQuitting, MSGBOX_DEFAULT
	closemessage
	factory_setswapped
	factory_set FACTORY_DATA_WIN_STREAK_SWAPS, 0
	factory_set FACTORY_DATA_WIN_STREAK, 0
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleFactoryLobby_EventScript_DefeatedFactoryHead
	msgbox BattleFrontier_BattleFactoryLobby_Text_CongratsSevenWins, MSGBOX_DEFAULT
	waitmessage
	goto BattleFrontier_BattleFactoryLobby_EventScript_GiveBattlePoints

BattleFrontier_BattleFactoryLobby_EventScript_DefeatedFactoryHead::
	msgbox BattleFrontier_BattleFactoryLobby_Text_CongratsForDefeatingHead, MSGBOX_DEFAULT
	waitmessage
BattleFrontier_BattleFactoryLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattleFactoryLobby_Text_AwardBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattleFactoryLobby_Text_ExchangeMonsAndSave
	waitmessage
	frontier_checkairshow
	special LoadPlayerParty
	factory_save 0
	playse SE_SAVE
	waitse
	goto BattleFrontier_BattleFactoryLobby_EventScript_AskRecordBattle
	end

BattleFrontier_BattleFactoryLobby_EventScript_LostChallenge::
	lockall
	message BattleFrontier_BattleFactoryLobby_Text_ReturnMonsSaveResults
	waitmessage
	frontier_checkairshow
	special LoadPlayerParty
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, FALSE
	factory_save 0
	playse SE_SAVE
	waitse

BattleFrontier_BattleFactoryLobby_EventScript_AskRecordBattle::
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle
	message BattleFrontier_BattleFactoryLobby_Text_RecordLastMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_RecordBattle
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle

BattleFrontier_BattleFactoryLobby_EventScript_RecordBattle::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle::
	msgbox BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_ResumeChallenge::
	lockall
	message BattleFrontier_BattleFactoryLobby_Text_WaitingForYouToResume
	waitmessage
	factory_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	setvar VAR_0x8006, 2
	goto BattleFrontier_BattleFactoryLobby_EventScript_EnterChallenge

BattleFrontier_BattleFactoryLobby_EventScript_SinglesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_FACTORY
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	goto BattleFrontier_BattleFactoryLobby_EventScript_Attendant
	end

BattleFrontier_BattleFactoryLobby_EventScript_DoublesAttendant::
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_FACTORY
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	goto BattleFrontier_BattleFactoryLobby_EventScript_Attendant
	end

BattleFrontier_BattleFactoryLobby_EventScript_Attendant::
	special SavePlayerParty
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForSingleBattle
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForDoubleBattle
BattleFrontier_BattleFactoryLobby_EventScript_AskTakeChallenge::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_TakeSinglesChallenge
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_TakeDoublesChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge

BattleFrontier_BattleFactoryLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattleFactoryLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleFactoryLobby_Text_OkayToSaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattleFactoryLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattleFactoryLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	factory_init
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallengeSaveFailed
	setvar VAR_0x8006, 0
BattleFrontier_BattleFactoryLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	msgbox BattleFrontier_BattleFactoryLobby_Text_StepThisWay, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_TalkedToSinglesAttendant
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_TalkedToDoublesAttendant
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleFactoryLobby_Movement_AttendantEnterDoor
	applymovement LOCALID_PLAYER, BattleFrontier_BattleFactoryLobby_Movement_PlayerEnterDoor
	waitmovement 0
	warp MAP_BATTLE_FRONTIER_BATTLE_FACTORY_PRE_BATTLE_ROOM, 8, 13
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattleFactoryLobby_EventScript_TalkedToSinglesAttendant::
	setvar VAR_LAST_TALKED, LOCALID_FACTORY_ATTENDANT_SINGLES
	return

BattleFrontier_BattleFactoryLobby_EventScript_TalkedToDoublesAttendant::
	setvar VAR_LAST_TALKED, LOCALID_FACTORY_ATTENDANT_DOUBLES
	return

BattleFrontier_BattleFactoryLobby_EventScript_ExplainChallenge::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_ExplainSinglesChallenge
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_ExplainDoublesChallenge
	goto BattleFrontier_BattleFactoryLobby_EventScript_AskTakeChallenge

BattleFrontier_BattleFactoryLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge

BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleFactoryLobby_Movement_AttendantEnterDoor:
	walk_up
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleFactoryLobby_Movement_PlayerEnterDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForSingleBattle::
	msgbox BattleFrontier_BattleFactoryLobby_Text_WelcomeForSingleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForDoubleBattle::
	msgbox BattleFrontier_BattleFactoryLobby_Text_WelcomeForDoubleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_TakeSinglesChallenge::
	message BattleFrontier_BattleFactoryLobby_Text_TakeSinglesChallenge
	return

BattleFrontier_BattleFactoryLobby_EventScript_TakeDoublesChallenge::
	message BattleFrontier_BattleFactoryLobby_Text_TakeDoublesChallenge
	return

BattleFrontier_BattleFactoryLobby_EventScript_ExplainSinglesChallenge::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSinglesChallenge, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_ExplainDoublesChallenge::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainDoublesChallenge, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_ShowSinglesResults::
	lockall
	frontier_results FRONTIER_FACILITY_FACTORY, FRONTIER_MODE_SINGLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_ShowDoublesResults::
	lockall
	frontier_results FRONTIER_FACILITY_FACTORY, FRONTIER_MODE_DOUBLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_Woman::
	msgbox BattleFrontier_BattleFactoryLobby_Text_NeedKnowledgeOfMonsMoves, MSGBOX_NPC
	end

BattleFrontier_BattleFactoryLobby_EventScript_Camper::
	msgbox BattleFrontier_BattleFactoryLobby_Text_SwappedForWeakMon, MSGBOX_NPC
	end

BattleFrontier_BattleFactoryLobby_EventScript_Picnicker::
	lock
	msgbox BattleFrontier_BattleFactoryLobby_Text_NeedToCheckOpponentsMons, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleFactoryLobby_EventScript_FatMan::
	msgbox BattleFrontier_BattleFactoryLobby_Text_CantFigureOutStaffHints, MSGBOX_NPC
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattleFactoryLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattleFactoryLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 17, 0, MULTI_BATTLE_FACTORY_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_RulesBasics
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapPartner
	case 2, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNumber
	case 3, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNotes
	case 4, BattleFrontier_BattleFactoryLobby_EventScript_RulesOpenLv
	case 5, BattleFrontier_BattleFactoryLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_ExitRules
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesBasics::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainBasicRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapPartner::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapPartnerRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNumber::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNumberRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNotes::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNotesRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesOpenLv::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainOpenLvRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattleFactoryLobby_Text_WelcomeForSingleBattle:
	.string "{CHN}这里是测试训练家\n"
	.string "智慧的地方！\p"
	.string "欢迎来到对战工厂！\p"
	.string "我是对战交换\n"
	.string "单打锦标赛的向导。$"

BattleFrontier_BattleFactoryLobby_Text_TakeSinglesChallenge:
	.string "{CHN}你想挑战对战\n"
	.string "交换单打吗？$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSinglesChallenge:
	.string "{CHN}对战交换单打锦标赛\n"
	.string "是只能使用租借宝可梦的\l"
	.string "单打对战比赛。\p"
	.string "首先，我们会借给你三只\n"
	.string "专为本次活动准备的宝可梦。\p"
	.string "使用提供的租借宝可梦，\n"
	.string "你必须进行单打对战。\p"
	.string "如果获胜，你可以交换\n"
	.string "一只你的租借宝可梦。\p"
	.string "重复这种对战和交换的循环——\n"
	.string "如果你连续获胜七次，\l"
	.string "就能获得对战点数。\p"
	.string "如果你想中断挑战，\n"
	.string "请保存游戏。\p"
	.string "如果不保存，你将\n"
	.string "被取消挑战资格。$"

BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit:
	.string "{CHN}期待您下次光临。$"

BattleFrontier_BattleFactoryLobby_Text_WhichLevelMode:
	.string "{CHN}你想挑战哪个等级？\n"
	.string "50级还是开放等级？$"

BattleFrontier_BattleFactoryLobby_Text_OkayToSaveBeforeChallenge:
	.string "{CHN}在你开始挑战之前，\n"
	.string "我需要保存游戏。可以吗？$"

/* Unused*/
BattleFrontier_BattleFactoryLobby_Text_WillHoldMonsForSafekeeping:
	.string "{CHN}好的，在你比赛期间，\n"
	.string "我会替你保管你的宝可梦。$"

BattleFrontier_BattleFactoryLobby_Text_StepThisWay:
	.string "{CHN}请这边走。$"

BattleFrontier_BattleFactoryLobby_Text_ReturnMonsSaveResults:
	.string "{CHN}感谢你的参与！\p"
	.string "我将用我们的租借宝可梦换回\n"
	.string "你的宝可梦。\p"
	.string "我还必须保存活动结果。\n"
	.string "请稍等。$"

/* Unused*/
BattleFrontier_BattleFactoryLobby_Text_ReturnMons:
	.string "{CHN}我将用我们的租借宝可梦换回\n"
	.string "你的宝可梦。$"

BattleFrontier_BattleFactoryLobby_Text_CongratsSevenWins:
	.string "{CHN}恭喜！你已经连续赢得了\n"
	.string "七场对战交换比赛！$"

/* Unused*/
BattleFrontier_BattleFactoryLobby_Text_AwardBattlePointsForStreak:
	.string "{CHN}为表彰你的七连胜，\n"
	.string "我们授予你这些对战点数。$"

/* Unused*/
BattleFrontier_BattleFactoryLobby_Text_MaxBattlePoints:
	.string "{CHN}哦，哦，哦！\p"
	.string "你的对战点数已满。\p"
	.string "请使用一些对战点数后\n"
	.string "再来。$"

BattleFrontier_BattleFactoryLobby_Text_WaitingForYouToResume:
	.string "{CHN}我们一直在等你！\p"
	.string "在恢复你的挑战之前，\n"
	.string "我必须保存游戏。$"

BattleFrontier_BattleFactoryLobby_Text_DidntSaveBeforeQuitting:
	.string "{CHN}很抱歉通知你，但你上次退出前\n"
	.string "没有保存游戏。\p"
	.string "因此，你已被取消\n"
	.string "挑战资格。$"

/* Unused*/
BattleFrontier_BattleFactoryLobby_Text_WellReturnMons:
	.string "{CHN}我们会还你个人的宝可梦。$"

/* Unused*/
BattleFrontier_BattleFactoryLobby_Text_ReceivedPrizeItem:
	.string "{CHN}{PLAYER}获得了奖品\n"
	.string "{STR_VAR_1}。$"

BattleFrontier_BattleFactoryLobby_Text_WelcomeForDoubleBattle:
	.string "{CHN}这里是测试训练家\n"
	.string "智慧的地方！\p"
	.string "欢迎来到对战工厂！\p"
	.string "我是对战交换\n"
	.string "双打锦标赛的向导。$"

BattleFrontier_BattleFactoryLobby_Text_TakeDoublesChallenge:
	.string "{CHN}你想挑战对战\n"
	.string "交换双打吗？$"

BattleFrontier_BattleFactoryLobby_Text_ExplainDoublesChallenge:
	.string "{CHN}对战交换双打锦标赛\n"
	.string "是只能使用租借宝可梦的\l"
	.string "双打对战比赛。\p"
	.string "首先，我们会借给你三只\n"
	.string "专为本次活动准备的宝可梦。\p"
	.string "使用提供的租借宝可梦，\n"
	.string "你必须进行双打对战。\p"
	.string "如果获胜，你可以交换\n"
	.string "一只你的租借宝可梦。\p"
	.string "重复这种对战和交换的循环——\n"
	.string "如果你连续获胜七次，\l"
	.string "就能获得对战点数。\p"
	.string "如果你想中断挑战，\n"
	.string "请保存游戏。\p"
	.string "如果在中断前不保存，\n"
	.string "你将被取消资格。$"

BattleFrontier_BattleFactoryLobby_Text_CongratsForDefeatingHead:
	.string "{CHN}恭喜你击败了\n"
	.string "工厂首脑并连续\l"
	.string "赢得了七场比赛！$"

BattleFrontier_BattleFactoryLobby_Text_AwardBattlePoints:
	.string "{CHN}为表彰你丰富的\n"
	.string "知识和敏锐的智慧，\l"
	.string "我们授予你这些对战点数。$"

BattleFrontier_BattleFactoryLobby_Text_ExchangeMonsAndSave:
	.string "{CHN}让我用我们的租借宝可梦\n"
	.string "换回你的宝可梦。\p"
	.string "我需要保存对战数据，\n"
	.string "请稍等。$"

BattleFrontier_BattleFactoryLobby_Text_RecordLastMatch:
	.string "{CHN}你想把上一场对战工厂\n"
	.string "的比赛记录到你的\l"
	.string "开拓区通行证上吗？$"

BattleFrontier_BattleFactoryLobby_Text_NeedKnowledgeOfMonsMoves:
	.string "{CHN}嗨！\n"
	.string "你啊！\p"
	.string "你是不是觉得这里的比赛很简单，\n"
	.string "因为你不需要培养\l"
	.string "一支宝可梦队伍？\p"
	.string "我可不那么确定你能\n"
	.string "轻松获胜。\p"
	.string "如果你对宝可梦和它们的招式\n"
	.string "没有透彻的了解，\l"
	.string "要连续获胜会很困难。$"

BattleFrontier_BattleFactoryLobby_Text_SwappedForWeakMon:
	.string "{CHN}我换了一只弱的宝可梦……\n"
	.string "我以为它是好的品种……\p"
	.string "他们把我们打得落花流水……$"

BattleFrontier_BattleFactoryLobby_Text_NeedToCheckOpponentsMons:
	.string "{CHN}我最近一直\n"
	.string "不太顺利。\p"
	.string "你需要在战斗中查看对手的\n"
	.string "宝可梦，看看它们\l"
	.string "到底怎么样。$"

BattleFrontier_BattleFactoryLobby_Text_CantFigureOutStaffHints:
	.string "{CHN}你知道这里的员工会给你\n"
	.string "一些关于下一个对手的提示吗？\p"
	.string "唉，我是个成年人，但我\n"
	.string "却搞不懂他们的提示。$"

/* Unused*/
BattleFrontier_BattleFactoryLobby_Text_RentalMonsAreVaried:
	.string "{CHN}那个，我其实很强，但我很容易\n"
	.string "无聊，所以就一直交换\l"
	.string "和战斗个不停。\p"
	.string "总之，当我不断参加\n"
	.string "对战交换活动时，我发现他们\l"
	.string "会变换租借的宝可梦。$"

BattleFrontier_BattleFactoryLobby_Text_RulesAreListed:
	.string "{CHN}这里列出了对战交换的规则。$"

BattleFrontier_BattleFactoryLobby_Text_ReadWhichHeading:
	.string "{CHN}你想阅读哪一项？$"

BattleFrontier_BattleFactoryLobby_Text_ExplainBasicRules:
	.string "{CHN}在对战交换活动中，\n"
	.string "你只能使用三只宝可梦。\p"
	.string "无论是租借还是交换，\n"
	.string "你的队伍中都不能有两只或更多\l"
	.string "相同的宝可梦。$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSwapPartnerRules:
	.string "{CHN}你只能与你刚刚击败的\n"
	.string "训练家交换宝可梦。\p"
	.string "你只能交换被击败的\n"
	.string "训练家所使用的宝可梦。$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNumberRules:
	.string "{CHN}每赢一场比赛后，你可以\n"
	.string "交换一只你击败的\l"
	.string "对手的宝可梦。\p"
	.string "你将无法与活动中的第七位\n"
	.string "训练家交换宝可梦。$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNotesRules:
	.string "{CHN}交换宝可梦时有两点\n"
	.string "需要注意。\p"
	.string "第一，交换时你无法查看\n"
	.string "你即将获得的宝可梦的\n"
	.string "能力值。\p"
	.string "第二，你队伍中的宝可梦\n"
	.string "按照你租借它们的顺序\l"
	.string "依次排列。\p"
	.string "即使进行交换，\n"
	.string "这个顺序也不会改变。$"

BattleFrontier_BattleFactoryLobby_Text_ExplainOpenLvRules:
	.string "{CHN}在开放等级中，租借的宝可梦\n"
	.string "和对手训练家的宝可梦\l"
	.string "全部都是100级。$"
