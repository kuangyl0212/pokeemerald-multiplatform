BattleFrontier_BattlePalaceLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePalaceLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePalaceLobby_OnWarp
	.byte 0

BattleFrontier_BattlePalaceLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePalaceLobby_EventScript_TurnPlayerNorth
	.short 0

BattleFrontier_BattlePalaceLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePalaceLobby_OnFrame:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattlePalaceLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePalaceLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePalaceLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattlePalaceLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattlePalaceLobby_EventScript_LostChallenge
	.short 0

BattleFrontier_BattlePalaceLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattlePalaceLobby_EventScript_QuitWithoutSaving::
	lockall
	msgbox BattleFrontier_BattlePalaceLobby_Text_FailedToSaveBeforeEndingChallenge, MSGBOX_DEFAULT
	closemessage
	palace_set PALACE_DATA_WIN_STREAK, 0
	palace_set PALACE_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePalaceLobby_EventScript_DefeatedMaven
	msgbox BattleFrontier_BattlePalaceLobby_Text_FirmTrueBondsFor7WinStreak, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_GiveBattlePoints

BattleFrontier_BattlePalaceLobby_EventScript_DefeatedMaven::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ToDefeatMavenAnd7Trainers, MSGBOX_DEFAULT
BattleFrontier_BattlePalaceLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattlePalaceLobby_Text_PresentYouWithBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattlePalaceLobby_Text_FeatWillBeRecorded
	waitmessage
	call BattleFrontier_BattlePalaceLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattlePalaceLobby_Text_ReturnWhenFortified, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_LostChallenge::
	lockall
	message BattleFrontier_BattlePalaceLobby_Text_ResultsWillBeRecorded
	waitmessage
	palace_set PALACE_DATA_WIN_STREAK_ACTIVE, FALSE
	call BattleFrontier_BattlePalaceLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattlePalaceLobby_Text_ReturnWhenFortified, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_SaveAfterChallenge::
	frontier_checkairshow
	special LoadPlayerParty
	special HealPlayerParty
	palace_save 0
	playse SE_SAVE
	waitse
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePalaceLobby_EventScript_EndSaveAfterChallenge
	message BattleFrontier_BattlePalaceLobby_Text_LikeToRecordMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattlePalaceLobby_EventScript_EndSaveAfterChallenge
	case 0, BattleFrontier_BattlePalaceLobby_EventScript_RecordMatch
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_EndSaveAfterChallenge

BattleFrontier_BattlePalaceLobby_EventScript_RecordMatch::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattlePalaceLobby_EventScript_EndSaveAfterChallenge::
	return

BattleFrontier_BattlePalaceLobby_EventScript_ResumeChallenge::
	lockall
	msgbox BattleFrontier_BattlePalaceLobby_Text_WeHaveBeenWaiting, MSGBOX_DEFAULT
	message BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge
	waitmessage
	palace_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto BattleFrontier_BattlePalaceLobby_EventScript_EnterChallenge

BattleFrontier_BattlePalaceLobby_EventScript_SinglesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PALACE
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	goto BattleFrontier_BattlePalaceLobby_EventScript_Attendant
	end

BattleFrontier_BattlePalaceLobby_EventScript_DoublesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PALACE
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	goto BattleFrontier_BattlePalaceLobby_EventScript_Attendant
	end

BattleFrontier_BattlePalaceLobby_EventScript_Attendant::
	palace_get PALACE_DATA_PRIZE
	goto_if_ne VAR_RESULT, ITEM_NONE, BattleFrontier_BattlePalaceLobby_EventScript_WonChallenge
	special SavePlayerParty
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattlePalaceLobby_EventScript_WelcomeForSingleBattle
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_WelcomeForDoubleBattle
BattleFrontier_BattlePalaceLobby_EventScript_AskTakeChallenge::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattlePalaceLobby_EventScript_AskTakeSingleBattleChallenge
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_AskTakeDoubleBattleChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePalaceLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattlePalaceLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge

BattleFrontier_BattlePalaceLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattlePalaceLobby_Text_WhichChallenge
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattlePalaceLobby_Text_NowSelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePalaceLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge2, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattlePalaceLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattlePalaceLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattlePalaceLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	palace_init
	palace_set PALACE_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallengeSaveFailed
BattleFrontier_BattlePalaceLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattlePalaceLobby_Text_FollowMe, MSGBOX_DEFAULT
	closemessage
	call BattleFrontier_BattlePalaceLobby_EventScript_WalkToDoor
	warp MAP_BATTLE_FRONTIER_BATTLE_PALACE_CORRIDOR, 8, 13
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattlePalaceLobby_EventScript_ExplainChallenge::
	goto_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_ExplainDoublesChallenge
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainSingleBattleChallenge, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_AskTakeChallenge

BattleFrontier_BattlePalaceLobby_EventScript_ExplainDoublesChallenge::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainDoubleBattleChallenge, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_AskTakeChallenge

BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePalaceLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge

BattleFrontier_BattlePalaceLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ReturnWhenFortified, MSGBOX_DEFAULT
BattleFrontier_BattlePalaceLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattlePalaceLobby_EventScript_WelcomeForSingleBattle::
	msgbox BattleFrontier_BattlePalaceLobby_Text_WelcomeForSingleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePalaceLobby_EventScript_WelcomeForDoubleBattle::
	msgbox BattleFrontier_BattlePalaceLobby_Text_WelcomeForDoubleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePalaceLobby_EventScript_AskTakeSingleBattleChallenge::
	message BattleFrontier_BattlePalaceLobby_Text_TakeSingleBattleChallenge
	return

BattleFrontier_BattlePalaceLobby_EventScript_AskTakeDoubleBattleChallenge::
	message BattleFrontier_BattlePalaceLobby_Text_TakeDoubleBattleChallenge
	return

BattleFrontier_BattlePalaceLobby_EventScript_WalkToDoor::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattlePalaceLobby_EventScript_TalkedToSinglesAttendant
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_TalkedToDoublesAttendant
	applymovement VAR_LAST_TALKED, BattleFrontier_BattlePalaceLobby_Movement_WalkToDoor
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePalaceLobby_Movement_WalkToDoor
	waitmovement 0
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattlePalaceLobby_EventScript_OpenSinglesHallDoor
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_OpenDoublesHallDoor
	waitdooranim
	applymovement VAR_LAST_TALKED, BattleFrontier_BattlePalaceLobby_Movement_AttendantEnterDoor
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePalaceLobby_Movement_PlayerEnterDoor
	waitmovement 0
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattlePalaceLobby_EventScript_CloseSinglesHallDoor
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_CloseDoublesHallDoor
	waitdooranim
	return

BattleFrontier_BattlePalaceLobby_EventScript_TalkedToSinglesAttendant::
	setvar VAR_LAST_TALKED, LOCALID_PALACE_ATTENDANT_SINGLES
	return

BattleFrontier_BattlePalaceLobby_EventScript_TalkedToDoublesAttendant::
	setvar VAR_LAST_TALKED, LOCALID_PALACE_ATTENDANT_DOUBLES
	return

BattleFrontier_BattlePalaceLobby_EventScript_OpenSinglesHallDoor::
	opendoor 5, 4
	return

BattleFrontier_BattlePalaceLobby_EventScript_OpenDoublesHallDoor::
	opendoor 19, 4
	return

BattleFrontier_BattlePalaceLobby_EventScript_CloseSinglesHallDoor::
	closedoor 5, 4
	return

BattleFrontier_BattlePalaceLobby_EventScript_CloseDoublesHallDoor::
	closedoor 19, 4
	return

BattleFrontier_BattlePalaceLobby_Movement_WalkToDoor:
	walk_up
	step_end

BattleFrontier_BattlePalaceLobby_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattlePalaceLobby_Movement_PlayerEnterDoor:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattlePalaceLobby_EventScript_ShowSinglesResults::
	lockall
	frontier_results FRONTIER_FACILITY_PALACE, FRONTIER_MODE_SINGLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_ShowDoublesResults::
	lockall
	frontier_results FRONTIER_FACILITY_PALACE, FRONTIER_MODE_DOUBLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_BlackBelt::
	msgbox BattleFrontier_BattlePalaceLobby_Text_LadyCanTellWhatMonsThink, MSGBOX_NPC
	end

BattleFrontier_BattlePalaceLobby_EventScript_Man::
	msgbox BattleFrontier_BattlePalaceLobby_Text_NatureAndMovesKeyHere, MSGBOX_NPC
	end

BattleFrontier_BattlePalaceLobby_EventScript_Beauty::
	msgbox BattleFrontier_BattlePalaceLobby_Text_MonDocileButTransforms, MSGBOX_NPC
	end

BattleFrontier_BattlePalaceLobby_EventScript_Maniac::
	msgbox BattleFrontier_BattlePalaceLobby_Text_WhatNatureFavorsChippingAway, MSGBOX_NPC
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattlePalaceLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattlePalaceLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 16, 0, MULTI_BATTLE_PALACE_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePalaceLobby_EventScript_RulesBasics
	case 1, BattleFrontier_BattlePalaceLobby_EventScript_RulesNature
	case 2, BattleFrontier_BattlePalaceLobby_EventScript_RulesMoves
	case 3, BattleFrontier_BattlePalaceLobby_EventScript_RulesUnderpowered
	case 4, BattleFrontier_BattlePalaceLobby_EventScript_RulesWhenInDanger
	case 5, BattleFrontier_BattlePalaceLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_ExitRules
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesBasics::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesBasics, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesNature::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesNature, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesMoves::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesMoves, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesUnderpowered::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesUnderpowered, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesWhenInDanger::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesWhenInDanger, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattlePalaceLobby_Text_WelcomeForSingleBattle:
	.string "{CHN}这里是考验训练家\n"
	.string "心灵之处。\p"
	.string "欢迎来到对战宫殿。\p"
	.string "我受理单人\n"
	.string "对战大厅的挑战。$"

BattleFrontier_BattlePalaceLobby_Text_TakeSingleBattleChallenge:
	.string "{CHN}你想挑战\n"
	.string "单人对战大厅吗？$"

BattleFrontier_BattlePalaceLobby_Text_ExplainSingleBattleChallenge:
	.string "{CHN}在对战宫殿中，\n"
	.string "有几间进行单打对战的\l"
	.string "被称为单人对战大厅的场馆。\p"
	.string "单打对战的进行方式\n"
	.string "与平常相同，但有一条必须\l"
	.string "遵守的重要规则。\p"
	.string "训练家只能切换\n"
	.string "自己的宝可梦。\p"
	.string "训练家不得\n"
	.string "对宝可梦下达指令。\p"
	.string "宝可梦将根据自身的性格\n"
	.string "自主战斗。\p"
	.string "你必须信任你的\n"
	.string "宝可梦并守护它们。\p"
	.string "若你能连续击败\n"
	.string "七名训练家，\l"
	.string "我们将赠予你对战点数。\p"
	.string "若想中断挑战，\n"
	.string "必须保存游戏。\p"
	.string "若中断前未保存，\n"
	.string "你将被取消资格。$"

BattleFrontier_BattlePalaceLobby_Text_ReturnWhenFortified:
	.string "{CHN}当你的心灵和宝可梦\n"
	.string "都变得更强时，再来吧。$"

BattleFrontier_BattlePalaceLobby_Text_WhichChallenge:
	.string "{CHN}这里有两个对战大厅，\n"
	.string "50级和自由级别。\l"
	.string "你要挑战哪一个？$"

BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLv50:
	.string "{CHN}唉……\p"
	.string "你没有挑战所需的\n"
	.string "三只宝可梦。\p"
	.string "参赛需要提供三只\n"
	.string "不同种类的宝可梦。\p"
	.string "这些宝可梦的等级\n"
	.string "都必须在50级以下。\p"
	.string "它们也不能携带\n"
	.string "相同种类的道具。\p"
	.string "蛋{STR_VAR_1}不符合资格。\p"
	.string "等你做好准备后\n"
	.string "再来吧。$"

BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLvOpen:
	.string "{CHN}唉……\p"
	.string "你没有挑战所需的\n"
	.string "三只宝可梦。\p"
	.string "参赛需要提供三只\n"
	.string "不同种类的宝可梦。\p"
	.string "它们也不能携带\n"
	.string "相同种类的道具。\p"
	.string "蛋{STR_VAR_1}不符合资格。\p"
	.string "等你做好准备后\n"
	.string "再来吧。$"

BattleFrontier_BattlePalaceLobby_Text_NowSelectThreeMons:
	.string "{CHN}好的。现在，请选择你的\n"
	.string "三只宝可梦。$"

BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge2:
	.string "{CHN}带你去对战大厅之前\n"
	.string "必须保存游戏。可以吗？$"

BattleFrontier_BattlePalaceLobby_Text_FollowMe:
	.string "{CHN}好的。\n"
	.string "请跟我来。$"

BattleFrontier_BattlePalaceLobby_Text_ResultsWillBeRecorded:
	.string "{CHN}能见到你的宝可梦\n"
	.string "大显身手，我深感荣幸。\p"
	.string "现在记录结果。\n"
	.string "请稍候片刻。$"

BattleFrontier_BattlePalaceLobby_Text_FirmTrueBondsFor7WinStreak:
	.string "{CHN}达成七连胜……\p"
	.string "你与宝可梦之间的\n"
	.string "羁绊看来十分坚固真挚。$"

BattleFrontier_BattlePalaceLobby_Text_FeatWillBeRecorded:
	.string "{CHN}你的功绩将被记录。\n"
	.string "请稍候片刻。$"

/* Unused*/
BattleFrontier_BattlePalaceLobby_Text_BattlePointsFor7WinStreak:
	.string "{CHN}为你的七连胜功绩，\n"
	.string "我们赠予你对战点数。$"

BattleFrontier_BattlePalaceLobby_Text_NoSpaceForPrize:
	.string "{CHN}你似乎没有空间\n"
	.string "放下我们的奖品。\p"
	.string "请整理好你的背包后\n"
	.string "再来吧。$"

BattleFrontier_BattlePalaceLobby_Text_WeHaveBeenWaiting:
	.string "{CHN}我们一直在等你……$"

BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge:
	.string "{CHN}带你去对战大厅之前\n"
	.string "必须保存游戏。可以吗？$"

BattleFrontier_BattlePalaceLobby_Text_FailedToSaveBeforeEndingChallenge:
	.string "{CHN}唉……\p"
	.string "上次你结束时未保存\n"
	.string "挑战进度。\p"
	.string "因此，你的挑战已被\n"
	.string "取消资格。真是遗憾。$"

/* Unused*/
BattleFrontier_BattlePalaceLobby_Text_ReceivedPrize:
	.string "{CHN}{PLAYER}获得了奖品\n"
	.string "{STR_VAR_1}。$"

BattleFrontier_BattlePalaceLobby_Text_LadyCanTellWhatMonsThink:
	.string "{CHN}对于我这样的硬汉来说，\n"
	.string "同样硬朗的宝可梦最棒了。\p"
	.string "进攻就是最好的防御！\n"
	.string "猛攻才是王道！\p"
	.string "但这并不是我想聊的\n"
	.string "话题。\p"
	.string "时不时会有位非常可爱的女士\n"
	.string "来这里。\p"
	.string "她说她能看穿\n"
	.string "宝可梦的心思。\p"
	.string "那部分我倒不清楚，\n"
	.string "但她真的很可爱。\p"
	.string "咦？\n"
	.string "你为什么那样看着我？$"

BattleFrontier_BattlePalaceLobby_Text_NatureAndMovesKeyHere:
	.string "{CHN}嗯……\p"
	.string "看来宝可梦的性格\n"
	.string "和它们所学的招式\l"
	.string "是这里对战的关键。\p"
	.string "更准确地说，是招式\n"
	.string "与宝可梦性格的\l"
	.string "契合程度。\p"
	.string "如果你的宝可梦陷入困境\n"
	.string "无法发挥实力，\l"
	.string "你可能需要检视它的招式\l"
	.string "与性格的契合程度。$"

BattleFrontier_BattlePalaceLobby_Text_MonDocileButTransforms:
	.string "{CHN}我的宝可梦平时很温顺。\p"
	.string "但一进对战大厅，\n"
	.string "它有时会变得\l"
	.string "判若两物！\p"
	.string "变得极具威慑力。\n"
	.string "简直让人震惊。$"

BattleFrontier_BattlePalaceLobby_Text_WhatNatureFavorsChippingAway:
	.string "{CHN}我想知道，偏好削弱对手\n"
	.string "并慢慢消耗对方的宝可梦\l"
	.string "会有什么样的性格。\p"
	.string "如果是乐天性格我会很惊讶。\p"
	.string "不过，那应该不对。$"

BattleFrontier_BattlePalaceLobby_Text_WelcomeForDoubleBattle:
	.string "{CHN}这里是考验训练家\n"
	.string "心灵之处。\p"
	.string "欢迎来到对战宫殿。\p"
	.string "我受理双人\n"
	.string "对战大厅的挑战。$"

BattleFrontier_BattlePalaceLobby_Text_TakeDoubleBattleChallenge:
	.string "{CHN}你想挑战\n"
	.string "双人对战大厅吗？$"

BattleFrontier_BattlePalaceLobby_Text_ExplainDoubleBattleChallenge:
	.string "{CHN}在对战宫殿中，\n"
	.string "有几间进行双打对战的\l"
	.string "被称为双人对战大厅的场馆。\p"
	.string "双打对战的进行方式\n"
	.string "与平常相同，但有一条必须\l"
	.string "遵守的重要规则。\p"
	.string "训练家只能切换\n"
	.string "自己的宝可梦。\p"
	.string "训练家不得\n"
	.string "对宝可梦下达指令。\p"
	.string "宝可梦将根据自身的性格\n"
	.string "自主战斗。\p"
	.string "你必须信任你的\n"
	.string "宝可梦并守护它们。\p"
	.string "若你能连续击败\n"
	.string "七名训练家，\l"
	.string "我们将赠予你对战点数。\p"
	.string "若想中断挑战，\n"
	.string "请保存游戏。\p"
	.string "若中断前未保存，\n"
	.string "你将被取消资格。$"

BattleFrontier_BattlePalaceLobby_Text_ToDefeatMavenAnd7Trainers:
	.string "{CHN}击败宫殿长老\n"
	.string "和七名训练家……$"

BattleFrontier_BattlePalaceLobby_Text_PresentYouWithBattlePoints:
	.string "{CHN}为纪念你与宝可梦的\n"
	.string "羁绊，我们赠予你\l"
	.string "这些对战点数。$"

BattleFrontier_BattlePalaceLobby_Text_LikeToRecordMatch:
	.string "{CHN}你想把上一场对战宫殿的对战\n"
	.string "记录在\l"
	.string "开拓区通行证上吗？$"

BattleFrontier_BattlePalaceLobby_Text_RulesAreListed:
	.string "{CHN}这里列出了对战大厅的规则。$"

BattleFrontier_BattlePalaceLobby_Text_ReadWhichHeading:
	.string "{CHN}你想阅读哪个标题？$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesBasics:
	.string "{CHN}在这里，宝可梦需要\n"
	.string "自主思考和战斗。\p"
	.string "与野外不同，与人类共同生活的宝可梦\n"
	.string "会根据自身性格\l"
	.string "表现出不同的行为。$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesNature:
	.string "{CHN}根据性格不同，\n"
	.string "有的宝可梦可能无论如何都想进攻。\p"
	.string "另一只宝可梦可能更愿意\n"
	.string "保护自己不受伤害。\p"
	.string "还有的可能喜欢\n"
	.string "困扰或迷惑对手。\p"
	.string "由于性格的关系，\n"
	.string "宝可梦会有自己擅长\l"
	.string "使用的招式。\p"
	.string "它也可能不喜欢\n"
	.string "某些难以使用的招式。$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesMoves:
	.string "{CHN}有直接对对手\n"
	.string "造成伤害的攻击招式。\p"
	.string "有用于防备对手攻击，\n"
	.string "或回复HP等的防御招式。\p"
	.string "还有一些稍显古怪的招式，\n"
	.string "能以中毒和麻痹等状态异常\l"
	.string "削弱对手。\p"
	.string "宝可梦会考虑使用\n"
	.string "这三类招式。$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesUnderpowered:
	.string "{CHN}训练家不下达指令时，\n"
	.string "宝可梦可能无法有效地\l"
	.string "使用某些招式。\p"
	.string "宝可梦不擅长\n"
	.string "使用自己不喜欢的招式。\p"
	.string "若宝可梦只会与自身性格\n"
	.string "不符的招式，往往\l"
	.string "无法发挥实力。$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesWhenInDanger:
	.string "{CHN}根据性格不同，宝可梦\n"
	.string "在陷入困境时可能\l"
	.string "会使用与自己性格不符的招式。\p"
	.string "若你的宝可梦在危急时\n"
	.string "行为异常，请仔细观察。$"

