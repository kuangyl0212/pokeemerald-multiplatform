BattleFrontier_BattlePyramidLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePyramidLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleDomeLobby_OnWarp
	.byte 0

/* Unused. Pyramid uses Dome's OnWarp (presumably by mistake). Their effects are identical*/
BattleFrontier_BattlePyramidLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePyramidLobby_EventScript_TurnPlayerNorth
	.short 0

BattleFrontier_BattlePyramidLobby_EventScript_TurnPlayerNorth:
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePyramidLobby_OnFrame:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattlePyramidLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePyramidLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePyramidLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattlePyramidLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattlePyramidLobby_EventScript_LostChallenge
	.short 0

BattleFrontier_BattlePyramidLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattlePyramidLobby_EventScript_QuitWithoutSaving::
	lockall
	message BattleFrontier_BattlePyramidLobby_Text_DidntSaveBeforeQuittingTakeBag
	waitmessage
	playse SE_EXP_MAX
	waitse
	closemessage
	pyramid_set PYRAMID_DATA_WIN_STREAK, 0
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_DefeatedKing
	msgbox BattleFrontier_BattlePyramidLobby_Text_YouveConqueredPyramid, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_GiveBattlePoints

BattleFrontier_BattlePyramidLobby_EventScript_DefeatedKing::
	msgbox BattleFrontier_BattlePyramidLobby_Text_YouveDefeatedPyramidKing, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_GiveBattlePoints::
	special DoBattlePyramidMonsHaveHeldItem
	call_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_StoreHeldItemsInPyramidBag
	clearflag FLAG_STORING_ITEMS_IN_PYRAMID_BAG
	frontier_checkairshow
	special LoadPlayerParty
	pyramid_clearhelditems
	special HealPlayerParty
	message BattleFrontier_BattlePyramidLobby_Text_UsedBattleBagWillBeKept
	waitmessage
	playse SE_EXP_MAX
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_GiveYouTheseBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait
	waitmessage
	pyramid_setprize
	pyramid_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_LostChallenge::
	frontier_checkairshow
	special LoadPlayerParty
	pyramid_clearhelditems
	special HealPlayerParty
	lockall
	message BattleFrontier_BattlePyramidLobby_Text_DisappointingHereIsBag
	waitmessage
	playse SE_EXP_MAX
	waitse
	message BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait
	waitmessage
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, FALSE
	pyramid_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_ResumeChallenge::
	goto BattleFrontier_BattlePyramidLobby_EventScript_EnterChallenge

BattleFrontier_BattlePyramidLobby_EventScript_Attendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PYRAMID
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattlePyramidLobby_Text_WelcomeToBattlePyramid, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_AskTakeChallenge::
	message BattleFrontier_BattlePyramidLobby_Text_EmbarkOnChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattlePyramidLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattlePyramidLobby_Text_SelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattlePyramidLobby_Text_OkayToSaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattlePyramidLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	pyramid_init
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	pyramid_seedfloor
	pyramid_settrainers
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallengeSaveFailed
BattleFrontier_BattlePyramidLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattlePyramidLobby_Text_ShowYouIntoPyramid, MSGBOX_DEFAULT
	closemessage
	call BattleFrontier_BattlePyramidLobby_EventScript_WalkToPanelAndReceiveBag
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_RESULT, 0
	special HealPlayerParty
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR, 1, 1
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattlePyramidLobby_EventScript_ExplainChallenge::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainBattlePyramid, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_AskTakeChallenge

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattlePyramidLobby_Text_AwaitFutureChallenge, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattlePyramidLobby_EventScript_HintGiver::
	lockall
	applymovement LOCALID_PYRAMID_LOBBY_HINT_GIVER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidLobby_Text_TellYouWhatMisfortunesAwait, MSGBOX_DEFAULT
	call BattleFrontier_BattlePyramidLobby_EventScript_GiveHint
	msgbox BattleFrontier_BattlePyramidLobby_Text_BelieveMyFortunesOrNot, MSGBOX_DEFAULT
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_GiveHint::
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLvOpen
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePyramidLobby_EventScript_NoHint
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_NoHint
	return

/* Shouldnt occur*/
BattleFrontier_BattlePyramidLobby_EventScript_NoHint::
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLv50::
	msgbox BattleFrontier_BattlePyramidLobby_Text_Aah, MSGBOX_DEFAULT
	pyramid_get PYRAMID_DATA_WIN_STREAK_ACTIVE_50
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLv50Streak
	setvar VAR_RESULT, 0
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLv50Streak::
	pyramid_get PYRAMID_DATA_WIN_STREAK_50
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLvOpen::
	msgbox BattleFrontier_BattlePyramidLobby_Text_Aah, MSGBOX_DEFAULT
	pyramid_get PYRAMID_DATA_WIN_STREAK_ACTIVE_OPEN
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLvOpenStreak
	setvar VAR_RESULT, 0
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLvOpenStreak::
	pyramid_get PYRAMID_DATA_WIN_STREAK_OPEN
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment::
	copyvar VAR_0x8004, VAR_RESULT
	special GetBattlePyramidHint
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_HintParalysis
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_HintPoison
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_HintBurn
	case 3, BattleFrontier_BattlePyramidLobby_EventScript_HintPPWaste
	case 4, BattleFrontier_BattlePyramidLobby_EventScript_HintLevitate
	case 5, BattleFrontier_BattlePyramidLobby_EventScript_HintTrapAbility
	case 6, BattleFrontier_BattlePyramidLobby_EventScript_HintIce
	case 7, BattleFrontier_BattlePyramidLobby_EventScript_HintExplosion
	case 8, BattleFrontier_BattlePyramidLobby_EventScript_HintPsychic
	case 9, BattleFrontier_BattlePyramidLobby_EventScript_HintRock
	case 10, BattleFrontier_BattlePyramidLobby_EventScript_HintFighting
	case 11, BattleFrontier_BattlePyramidLobby_EventScript_HintWeather
	case 12, BattleFrontier_BattlePyramidLobby_EventScript_HintBug
	case 13, BattleFrontier_BattlePyramidLobby_EventScript_HintDark
	case 14, BattleFrontier_BattlePyramidLobby_EventScript_HintWater
	case 15, BattleFrontier_BattlePyramidLobby_EventScript_HintGhost
	case 16, BattleFrontier_BattlePyramidLobby_EventScript_HintSteel
	case 17, BattleFrontier_BattlePyramidLobby_EventScript_HintFlyingDragon
	case 18, BattleFrontier_BattlePyramidLobby_EventScript_HintStoneEvolve
	case 19, BattleFrontier_BattlePyramidLobby_EventScript_HintNormal
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintParalysis::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintParalysis, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintPoison::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPoison, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintBurn::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintBurn, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintPPWaste::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPPWaste, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintLevitate::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintLevitate, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintTrapAbility::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintTrapAbility, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintIce::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintIce, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintExplosion::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintExplosion, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintPsychic::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPsychic, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintRock::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintRock, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintFighting::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintFighting, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintWeather::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintWeather, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintBug::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintBug, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintDark::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintDark, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintWater::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintWater, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintGhost::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintGhost, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintSteel::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintSteel, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintFlyingDragon::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintFlyingDragon, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintStoneEvolve::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintStoneEvolve, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintNormal::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintNormal, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_ShowResults::
	lockall
	frontier_results FRONTIER_FACILITY_PYRAMID
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_WalkToPanelAndReceiveBag::
	applymovement LOCALID_PYRAMID_LOBBY_ATTENDANT, BattleFrontier_BattlePyramidLobby_Movement_AttendantWalkToPanel
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePyramidLobby_Movement_PlayerWalkToPanel
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidLobby_Text_WeWillHoldBagForSafekeeping, MSGBOX_DEFAULT
	pyramid_get PYRAMID_DATA_WIN_STREAK
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_ReceiveNewBattleBag
	msgbox BattleFrontier_BattlePyramidLobby_Text_PleaseTakePreviousBattleBag, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReceiveBattleBag

BattleFrontier_BattlePyramidLobby_EventScript_ReceiveNewBattleBag::
	msgbox BattleFrontier_BattlePyramidLobby_Text_PleaseTakeThisBattleBag, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_ReceiveBattleBag::
	message BattleFrontier_BattlePyramidLobby_Text_ExchangedBagForBattleBag
	waitmessage
	playse SE_EXP_MAX
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_StepOnFloorPanel, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PYRAMID_LOBBY_ATTENDANT, BattleFrontier_BattlePyramidLobby_Movement_AttendantMoveAside
	waitmovement 0
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePyramidLobby_Movement_PlayerStepOnPanel
	waitmovement 0
	return

BattleFrontier_BattlePyramidLobby_Movement_AttendantWalkToPanel:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_down
	step_end

BattleFrontier_BattlePyramidLobby_Movement_PlayerWalkToPanel:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePyramidLobby_Movement_AttendantMoveAside:
	walk_right
	face_left
	step_end

BattleFrontier_BattlePyramidLobby_Movement_PlayerStepOnPanel:
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePyramidLobby_EventScript_StoreHeldItemsInPyramidBag::
	msgbox BattleFrontier_BattlePyramidLobby_Text_MonHoldingItemCannotTake, MSGBOX_DEFAULT
	setflag FLAG_STORING_ITEMS_IN_PYRAMID_BAG
	special TryStoreHeldItemsInPyramidBag
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_HeldItemsStoredInPyramidBag
	message BattleFrontier_BattlePyramidLobby_Text_BagCannotHoldPickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_HeldItemsStoredInPyramidBag::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HeldItemsMovedToBag, MSGBOX_DEFAULT
	return

/* When exiting Battle Pyramid with a full pyramid bag and held items the player must select to keep/toss party held items and make room for any kept items by tossing from the pyramid bag*/
BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep::
	multichoice 17, 6, MULTI_FRONTIER_ITEM_CHOOSE, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromBag
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromParty
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems
	end

BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromBag::
	special ChooseItemsToTossFromPyramidBag
	waitstate
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromParty::
	special BattlePyramidChooseMonHeldItems
	waitstate
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems::
	special DoBattlePyramidMonsHaveHeldItem
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_PartyStillHasHeldItems
	return

BattleFrontier_BattlePyramidLobby_EventScript_PartyStillHasHeldItems::
	msgbox BattleFrontier_BattlePyramidLobby_Text_LeastOneMonHoldingItem, MSGBOX_DEFAULT
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_Woman::
	msgbox BattleFrontier_BattlePyramidLobby_Text_TrainersNoticeRunning, MSGBOX_NPC
	end

BattleFrontier_BattlePyramidLobby_EventScript_FatMan::
	msgbox BattleFrontier_BattlePyramidLobby_Text_LostLotOfItems, MSGBOX_NPC
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattlePyramidLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattlePyramidLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 15, 2, MULTI_BATTLE_PYRAMID_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_RulesPokemon
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_RulesTrainers
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_RulesMaze
	case 3, BattleFrontier_BattlePyramidLobby_EventScript_RulesBag
	case 4, BattleFrontier_BattlePyramidLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_ExitRules
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesPokemon::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainMonRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesTrainers::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainTrainerRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesMaze::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainMazeRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesBag::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainBagRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattlePyramidLobby_Text_WelcomeToBattlePyramid:
	.string "{CHN}这里是测试训练家勇气之地！\p"
	.string "欢迎来到对战金字塔！\p"
	.string "我是你的向导，\n"
	.string "负责引导你进行战斗探索。$"

BattleFrontier_BattlePyramidLobby_Text_EmbarkOnChallenge:
	.string "{CHN}你有勇气挑战\n"
	.string "战斗探索吗？$"

BattleFrontier_BattlePyramidLobby_Text_AwaitFutureChallenge:
	.string "{CHN}我们期待你日后的挑战！$"

BattleFrontier_BattlePyramidLobby_Text_ExplainBattlePyramid:
	.string "{CHN}战斗探索是一场战斗活动，\n"
	.string "你需要探索金字塔\l"
	.string "并尝试到达顶层。\p"
	.string "金字塔内有七层迷宫，\n"
	.string "里面不仅有技艺高超的训练家，\l"
	.string "还有野生宝可梦。\p"
	.string "你必须带三只宝可梦进入，\n"
	.string "且都不能携带道具。\p"
	.string "在攀登过程中，我们会提供\n"
	.string "一个战斗背包来装道具。\p"
	.string "如果挑战失败，\n"
	.string "战斗背包中的所有道具都会消失。\p"
	.string "如果想要中断挑战，\n"
	.string "必须选择“休息”\l"
	.string "并保存游戏。\p"
	.string "如果中断前没有保存，\n"
	.string "你将被取消资格。$"

BattleFrontier_BattlePyramidLobby_Text_WhichLevelMode:
	.string "{CHN}金字塔提供两种模式，\n"
	.string "50级和开放等级。\l"
	.string "你要进入哪一种？$"

BattleFrontier_BattlePyramidLobby_Text_SelectThreeMons:
	.string "{CHN}很好。那么，请选择\n"
	.string "三只你想带上的宝可梦。$"

BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLvOpen:
	.string "{CHN}有点问题，探险家！\p"
	.string "你似乎没有三只\n"
	.string "符合挑战条件的宝可梦。\p"
	.string "也请记得取下宝可梦\n"
	.string "携带的所有道具。\p"
	.string "蛋{STR_VAR_1}不符合资格。\p"
	.string "准备好后，\n"
	.string "请再来找我。$"

BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLv50:
	.string "{CHN}有点问题，探险家！\p"
	.string "你似乎没有三只\n"
	.string "符合挑战条件的宝可梦。\p"
	.string "三只宝可梦必须各不相同，\n"
	.string "且等级均不超过50级。\p"
	.string "也请记得取下宝可梦\n"
	.string "携带的所有道具。\p"
	.string "蛋{STR_VAR_1}不符合资格。\p"
	.string "准备好后，\n"
	.string "请再来找我。$"

BattleFrontier_BattlePyramidLobby_Text_OkayToSaveBeforeChallenge:
	.string "{CHN}进入对战金字塔前，\n"
	.string "必须保存游戏。可以吗？$"

BattleFrontier_BattlePyramidLobby_Text_ShowYouIntoPyramid:
	.string "{CHN}很好。我现在就带你\n"
	.string "进入对战金字塔。$"

BattleFrontier_BattlePyramidLobby_Text_WeWillHoldBagForSafekeeping:
	.string "{CHN}{PLAYER}，在你探索期间，\n"
	.string "我们会替你保管背包。$"

BattleFrontier_BattlePyramidLobby_Text_PleaseTakePreviousBattleBag:
	.string "{CHN}作为交换，请拿上这个战斗背包，\n"
	.string "就是你上次用过的那个。$"

BattleFrontier_BattlePyramidLobby_Text_PleaseTakeThisBattleBag:
	.string "{CHN}作为交换，\n"
	.string "请拿上这个战斗背包。$"

BattleFrontier_BattlePyramidLobby_Text_ExchangedBagForBattleBag:
	.string "{CHN}{PLAYER}将背包换成了\n"
	.string "战斗背包。$"

BattleFrontier_BattlePyramidLobby_Text_StepOnFloorPanel:
	.string "{CHN}当你踏上这块地板开关时，\n"
	.string "就会被传送到金字塔中\l"
	.string "更高的一层。\p"
	.string "祝你的探索\n"
	.string "一路平安！$"

BattleFrontier_BattlePyramidLobby_Text_DidntSaveBeforeQuittingTakeBag:
	.string "{CHN}出大问题了，探险家！\p"
	.string "你上次结束挑战时\n"
	.string "没有保存游戏。\p"
	.string "因此，很遗憾，\n"
	.string "你的挑战已被取消资格。\p"
	.string "这是为你保管的\n"
	.string "背包。\p"
	.string "{PLAYER}取回了背包。$"

BattleFrontier_BattlePyramidLobby_Text_YouveConqueredPyramid:
	.string "{CHN}欢迎回来！\p"
	.string "你征服了金字塔！\n"
	.string "太棒了！$"

BattleFrontier_BattlePyramidLobby_Text_MonHoldingItemCannotTake:
	.string "{CHN}啊，有个小问题。\p"
	.string "至少有一只宝可梦\n"
	.string "携带了道具。\p"
	.string "很遗憾，在金字塔中\n"
	.string "获得的道具无法带走。$"

BattleFrontier_BattlePyramidLobby_Text_HeldItemsMovedToBag:
	.string "{CHN}{PLAYER}，你的宝可梦携带的所有道具\n"
	.string "都会被移到战斗背包里。$"

BattleFrontier_BattlePyramidLobby_Text_BagCannotHoldPickItemsToKeep:
	.string "{CHN}很遗憾，战斗背包\n"
	.string "装不下你所有的道具。\p"
	.string "请选择要保留在战斗背包里\n"
	.string "和宝可梦身上的道具。$"

BattleFrontier_BattlePyramidLobby_Text_LeastOneMonHoldingItem:
	.string "{CHN}至少还有一只宝可梦\n"
	.string "携带了道具。$"

BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep:
	.string "{CHN}请选择要保留在战斗背包里\n"
	.string "和宝可梦身上的道具。$"

/* Unused*/
BattleFrontier_BattlePyramidLobby_Text_ReturnedEverythingMonsHeld:
	.string "{CHN}{PLAYER}归还了宝可梦\n"
	.string "携带的所有道具。$"

BattleFrontier_BattlePyramidLobby_Text_UsedBattleBagWillBeKept:
	.string "{CHN}你使用过的战斗背包会保留下来，\n"
	.string "以备下次挑战之用。\p"
	.string "{PLAYER}交出了战斗背包，\n"
	.string "换回了自己的背包。$"

BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait:
	.string "{CHN}我需要记录你的成绩。\n"
	.string "请稍候。$"

/* Unused*/
BattleFrontier_BattlePyramidLobby_Text_ForConqueringPyramidTakeThis:
	.string "{CHN}作为征服对战金字塔的纪念，\n"
	.string "请收下这个。$"

/* Unused*/
BattleFrontier_BattlePyramidLobby_Text_ReceivedPrizeItem:
	.string "{CHN}{PLAYER}获得了奖品\n"
	.string "{STR_VAR_1}。$"

/* Unused*/
BattleFrontier_BattlePyramidLobby_Text_BagIsFull:
	.string "{CHN}……啊……\n"
	.string "你的背包好像已经满了。\p"
	.string "请整理好背包内容后\n"
	.string "再来。$"

BattleFrontier_BattlePyramidLobby_Text_DisappointingHereIsBag:
	.string "{CHN}真令人遗憾……\p"
	.string "这是为你保管的\n"
	.string "背包。\p"
	.string "{PLAYER}取回了背包。$"

BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge:
	.string "{CHN}我们期待你的\n"
	.string "下一次挑战！$"

/* Unused*/
BattleFrontier_BattlePyramidLobby_Text_HereIsPrize:
	.string "{CHN}我们一直期盼\n"
	.string "你的到来！\p"
	.string "这是你征服金字塔\n"
	.string "的奖品。$"

BattleFrontier_BattlePyramidLobby_Text_TellYouWhatMisfortunesAwait:
	.string "{CHN}欢迎……\p"
	.string "我很乐意告诉你\n"
	.string "金字塔中有什么不幸在等着你……$"

BattleFrontier_BattlePyramidLobby_Text_Aah:
	.string "{CHN}…… ………… …………\n"
	.string "…… ………… …………\p"
	.string "…… ………… …………\n"
	.string "啊！$"

BattleFrontier_BattlePyramidLobby_Text_HintParalysis:
	.string "{CHN}我看到一阵火花飞溅……\p"
	.string "……其中，我看到你的宝可梦\n"
	.string "正被麻痹所困扰……$"

BattleFrontier_BattlePyramidLobby_Text_HintPoison:
	.string "{CHN}我看到毒……\p"
	.string "……而且，我看到你的宝可梦\n"
	.string "正遭受中毒之苦……$"

BattleFrontier_BattlePyramidLobby_Text_HintBurn:
	.string "{CHN}我看到鲜红的火焰……\p"
	.string "……而且，我看到你的宝可梦\n"
	.string "正遭受灼伤之苦……$"

BattleFrontier_BattlePyramidLobby_Text_HintPPWaste:
	.string "{CHN}我感到一股\n"
	.string "无法发泄的强烈愤怒……\p"
	.string "那是一种诅咒……\p"
	.string "……而且，我看到你的宝可梦\n"
	.string "耗尽了招式点数，\l"
	.string "只能使用挣扎……$"

BattleFrontier_BattlePyramidLobby_Text_HintLevitate:
	.string "{CHN}我看到宝可梦高高飘浮在空中……\p"
	.string "……而且，我看到你的宝可梦\n"
	.string "因地面属性招式无效而感到挫败……$"

BattleFrontier_BattlePyramidLobby_Text_HintTrapAbility:
	.string "{CHN}我感到一股\n"
	.string "从地面升起的强大能量……\p"
	.string "……而且，我看到你的宝可梦\n"
	.string "无法逃脱那股力量的束缚……$"

BattleFrontier_BattlePyramidLobby_Text_HintIce:
	.string "{CHN}我看到冰属性的宝可梦……\p"
	.string "……而且，我看到你的宝可梦\n"
	.string "正与冰冻效果搏斗……$"

BattleFrontier_BattlePyramidLobby_Text_HintExplosion:
	.string "{CHN}我看到一连串\n"
	.string "危及使用者的招式……\p"
	.string "……而且，我看到你的宝可梦\n"
	.string "败在它们手下……$"

BattleFrontier_BattlePyramidLobby_Text_HintPsychic:
	.string "{CHN}我看到超能力属性的宝可梦……\p"
	.string "……而且，我看到你的宝可梦\n"
	.string "正受超能力招式的折磨……$"

BattleFrontier_BattlePyramidLobby_Text_HintRock:
	.string "{CHN}我看到岩石属性的宝可梦……\p"
	.string "……而且，我看到你的宝可梦\n"
	.string "正遭受岩石招式之苦……$"

BattleFrontier_BattlePyramidLobby_Text_HintFighting:
	.string "{CHN}我看到格斗属性的宝可梦……\p"
	.string "……而且，我看到你的宝可梦\n"
	.string "被格斗招式痛击……$"

BattleFrontier_BattlePyramidLobby_Text_HintWeather:
	.string "{CHN}求雨……大晴天……\n"
	.string "沙尘暴……冰雹……\p"
	.string "我看到宝可梦会随天气\n"
	.string "变强……\p"
	.string "……而且，我看到你的宝可梦\n"
	.string "被各种招式搞得手足无措……$"

BattleFrontier_BattlePyramidLobby_Text_HintBug:
	.string "{CHN}我看到虫属性的宝可梦……\p"
	.string "……而且，我看到你的宝可梦\n"
	.string "正遭受各种攻击之苦……$"

BattleFrontier_BattlePyramidLobby_Text_HintDark:
	.string "{CHN}我看到恶属性的宝可梦……\p"
	.string "……而且，我看到你的宝可梦\n"
	.string "正遭受恶属性招式之苦……$"

BattleFrontier_BattlePyramidLobby_Text_HintWater:
	.string "{CHN}我看到水属性的宝可梦……\p"
	.string "……而且，我看到你的宝可梦\n"
	.string "正遭受水属性招式之苦……$"

BattleFrontier_BattlePyramidLobby_Text_HintGhost:
	.string "{CHN}我看到幽灵属性的宝可梦……\p"
	.string "……而且，我看到你的宝可梦\n"
	.string "正遭受幽灵属性招式之苦……$"

BattleFrontier_BattlePyramidLobby_Text_HintSteel:
	.string "{CHN}我看到钢属性的宝可梦……\p"
	.string "……而且，我看到你的宝可梦\n"
	.string "正遭受极其强大的招式之苦……$"

BattleFrontier_BattlePyramidLobby_Text_HintFlyingDragon:
	.string "{CHN}我看到飞翔的宝可梦……\p"
	.string "……而且，我看到你的宝可梦\n"
	.string "正遭受极其强大的招式之苦……$"

BattleFrontier_BattlePyramidLobby_Text_HintStoneEvolve:
	.string "{CHN}我看到那些借助\n"
	.string "石头之力进化的宝可梦……\p"
	.string "我还感受到火、水、\n"
	.string "电的力量……\p"
	.string "……而且，我看到你的宝可梦\n"
	.string "正遭受这三种力量之苦……$"

BattleFrontier_BattlePyramidLobby_Text_HintNormal:
	.string "{CHN}我看到一般属性的宝可梦……\p"
	.string "……而且，我看到你的宝可梦\n"
	.string "正遭受极其强大的招式之苦……$"

BattleFrontier_BattlePyramidLobby_Text_BelieveMyFortunesOrNot:
	.string "{CHN}信不信我的预言，\n"
	.string "由你自己决定……\p"
	.string "未来随时可以改变……\n"
	.string "祝你一路平安……$"

BattleFrontier_BattlePyramidLobby_Text_TrainersNoticeRunning:
	.string "{CHN}你知道吗？\p"
	.string "如果你跑得快，训练家可能会注意到\n"
	.string "并追上来和你对战。\p"
	.string "所以，如果你想避开训练家，\n"
	.string "不要引起他们的注意，\l"
	.string "悄悄地从他们身边溜过去。$"

BattleFrontier_BattlePyramidLobby_Text_LostLotOfItems:
	.string "{CHN}哇啊啊啊啊啊！\p"
	.string "我有好多道具，可是我输了，\n"
	.string "全都丢了！\p"
	.string "哇啊啊啊啊啊！$"

BattleFrontier_BattlePyramidLobby_Text_YouveDefeatedPyramidKing:
	.string "{CHN}欢迎回来！\n"
	.string "你做出了不可思议的事！\p"
	.string "你击败了金字塔之王，\n"
	.string "征服了对战金字塔！$"

BattleFrontier_BattlePyramidLobby_Text_GiveYouTheseBattlePoints:
	.string "{CHN}年轻的探险家！\n"
	.string "为表彰你的勇气，\l"
	.string "我们赠予你这些对战点数！$"

BattleFrontier_BattlePyramidLobby_Text_RulesAreListed:
	.string "{CHN}这里列出了战斗探索的规则。$"

BattleFrontier_BattlePyramidLobby_Text_ReadWhichHeading:
	.string "{CHN}你想阅读哪一项？$"

BattleFrontier_BattlePyramidLobby_Text_ExplainMonRules:
	.string "{CHN}当金字塔被征服后，\n"
	.string "其中出现的野生宝可梦\l"
	.string "会被替换成其他种类。\p"
	.string "探索、观察并了解\n"
	.string "你可能会遇到什么样的野生宝可梦。$"

BattleFrontier_BattlePyramidLobby_Text_ExplainTrainerRules:
	.string "{CHN}金字塔里\n"
	.string "有训练家在等着你。\p"
	.string "每一层最多有\n"
	.string "八名训练家。\p"
	.string "击败训练家后，\n"
	.string "你会获得对探险有用的提示。$"

BattleFrontier_BattlePyramidLobby_Text_ExplainMazeRules:
	.string "{CHN}金字塔里的迷宫\n"
	.string "每次进入都会重新排列。\p"
	.string "迷宫内光线昏暗。\n"
	.string "你必须小心前进。\p"
	.string "每当你击败野生宝可梦或训练家时，\n"
	.string "光线就会变亮一些。$"

BattleFrontier_BattlePyramidLobby_Text_ExplainBagRules:
	.string "{CHN}在金字塔中，战斗背包\n"
	.string "就充当你的背包。\p"
	.string "战斗背包有两种——\n"
	.string "50级和开放等级\l"
	.string "各一种。\p"
	.string "每种都能装下十种道具，\n"
	.string "每种最多99个。\p"
	.string "如果挑战失败，\n"
	.string "战斗背包里的东西就会全部丢失。$"

