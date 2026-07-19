BattleFrontier_BattleArenaLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleArenaLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleArenaLobby_OnWarp
	.byte 0

BattleFrontier_BattleArenaLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleArenaLobby_EventScript_TurnPlayerNorth
	.short 0

BattleFrontier_BattleArenaLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleArenaLobby_OnFrame:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattleArenaLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattleArenaLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattleArenaLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattleArenaLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattleArenaLobby_EventScript_LostChallenge
	.short 0

BattleFrontier_BattleArenaLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattleArenaLobby_EventScript_QuitWithoutSaving::
	lockall
	msgbox BattleFrontier_BattleArenaLobby_Text_DidntSaveBeforeShuttingDown, MSGBOX_DEFAULT
	closemessage
	arena_set ARENA_DATA_WIN_STREAK, 0
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleArenaLobby_EventScript_DefeatedTycoon
	msgbox BattleFrontier_BattleArenaLobby_Text_CongratsOnSevenWins, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_GiveBattlePoints

BattleFrontier_BattleArenaLobby_EventScript_DefeatedTycoon::
	msgbox BattleFrontier_BattleArenaLobby_Text_CongratsOnDefeatingTycoon, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattleArenaLobby_Text_PleaseAcceptBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattleArenaLobby_Text_RecordAchievement
	waitmessage
	call BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge2, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_LostChallenge::
	lockall
	message BattleFrontier_BattleArenaLobby_Text_ThankYouWaitWhileSave
	waitmessage
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, FALSE
	call BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge2, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge::
	frontier_checkairshow
	special LoadPlayerParty
	special HealPlayerParty
	arena_save 0
	playse SE_SAVE
	waitse
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge
	message BattleFrontier_BattleArenaLobby_Text_RecordLastMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge
	case 0, BattleFrontier_BattleArenaLobby_EventScript_RecordMatch
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge

BattleFrontier_BattleArenaLobby_EventScript_RecordMatch::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge::
	return

BattleFrontier_BattleArenaLobby_EventScript_ResumeChallenge::
	lockall
	message BattleFrontier_BattleArenaLobby_Text_LookingForwardToArrivalSaveGame
	waitmessage
	arena_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto BattleFrontier_BattleArenaLobby_EventScript_EnterChallenge

BattleFrontier_BattleArenaLobby_EventScript_Attendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_ARENA
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattleArenaLobby_Text_WelcomeToBattleArena, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_AskTakeChallenge::
	message BattleFrontier_BattleArenaLobby_Text_WishToTakeChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleArenaLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattleArenaLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattleArenaLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleArenaLobby_Text_SelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattleArenaLobby_Text_OkayToSave, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattleArenaLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	arena_init
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleArenaLobby_EventScript_CancelChallengeSaveFailed
BattleFrontier_BattleArenaLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattleArenaLobby_Text_GuideYouToArena, MSGBOX_DEFAULT
	closemessage
	frontier_get FRONTIER_DATA_LVL_MODE
	call_if_eq VAR_RESULT, FRONTIER_LVL_50, BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLv50
	call_if_eq VAR_RESULT, FRONTIER_LVL_OPEN, BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLvOpen
	warp MAP_BATTLE_FRONTIER_BATTLE_ARENA_CORRIDOR, 9, 13
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattleArenaLobby_EventScript_ExplainChallenge::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainChallenge, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_AskTakeChallenge

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLv50::
	applymovement LOCALID_ARENA_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToLeftDoor
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToLeftDoor
	waitmovement 0
	opendoor 2, 2
	waitdooranim
	applymovement LOCALID_ARENA_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 2, 2
	waitdooranim
	return

BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToLeftDoor:
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToLeftDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLvOpen::
	applymovement LOCALID_ARENA_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToRightDoor
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToRightDoor
	waitmovement 0
	opendoor 11, 2
	waitdooranim
	applymovement LOCALID_ARENA_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 11, 2
	waitdooranim
	return

BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToRightDoor:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToRightDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

BattleFrontier_BattleArenaLobby_EventScript_ShowResults::
	lockall
	frontier_results FRONTIER_FACILITY_ARENA
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_Youngster::
	msgbox BattleFrontier_BattleArenaLobby_Text_BadIdeaToNotAttack, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Man::
	msgbox BattleFrontier_BattleArenaLobby_Text_LandingHitsWorked, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Camper::
	msgbox BattleFrontier_BattleArenaLobby_Text_MatchWasDeclaredDraw, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Woman::
	msgbox BattleFrontier_BattleArenaLobby_Text_OrderOfMonsImportant, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattleArenaLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattleArenaLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 17, 2, MULTI_BATTLE_ARENA_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleArenaLobby_EventScript_BattleRules
	case 1, BattleFrontier_BattleArenaLobby_EventScript_MindRules
	case 2, BattleFrontier_BattleArenaLobby_EventScript_SkillRules
	case 3, BattleFrontier_BattleArenaLobby_EventScript_BodyRules
	case 4, BattleFrontier_BattleArenaLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_ExitRules
	end

BattleFrontier_BattleArenaLobby_EventScript_BattleRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainBattleRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_MindRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainMindRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_SkillRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainSkillRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_BodyRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainBodyRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattleArenaLobby_Text_WelcomeToBattleArena:
	.string "{CHN}这里是考验训练家\n"
	.string "对战精神的地方！\p"
	.string "欢迎来到对战竞技场！\p"
	.string "我是你的淘汰赛向导！$"

BattleFrontier_BattleArenaLobby_Text_WishToTakeChallenge:
	.string "{CHN}那么，你想接受\n"
	.string "对战竞技场的挑战吗？$"

BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge:
	.string "{CHN}我们期待你\n"
	.string "在另一天来挑战！$"

BattleFrontier_BattleArenaLobby_Text_ExplainChallenge:
	.string "{CHN}在对战竞技场，我们要进行\n"
	.string "淘汰赛。\p"
	.string "所有参赛者都要带着由\n"
	.string "三只宝可梦组成的队伍。\p"
	.string "这三只宝可梦必须按照\n"
	.string "出场的顺序排列。\p"
	.string "对战中，宝可梦会按预设顺序\n"
	.string "一只一只地出场。\p"
	.string "一旦宝可梦进入对战，它必须\n"
	.string "留在场上直到比赛决出胜负。\p"
	.string "如果比赛在三回合内\n"
	.string "未分胜负，将交由评判裁决。\p"
	.string "如果你想中断挑战，\n"
	.string "请保存游戏。\p"
	.string "如果不保存，你将无法继续\n"
	.string "你的挑战。\p"
	.string "如果你能连续击败\n"
	.string "七位训练家，\l"
	.string "我们将赠予你对战点数。$"

BattleFrontier_BattleArenaLobby_Text_OkayToSave:
	.string "{CHN}在带你去对战竞技场之前，\n"
	.string "你必须保存游戏。可以吗？$"

BattleFrontier_BattleArenaLobby_Text_WhichLevelMode:
	.string "{CHN}对战竞技场提供两种等级的\n"
	.string "挑战，50级和开放等级。\l"
	.string "你选哪个？$"

BattleFrontier_BattleArenaLobby_Text_SelectThreeMons:
	.string "{CHN}那么，现在请选择你的\n"
	.string "三只宝可梦。$"

BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLvOpen:
	.string "{CHN}亲爱的挑战者！\p"
	.string "你没有参赛所需的\n"
	.string "三只宝可梦。\p"
	.string "要符合资格，你必须带三只\n"
	.string "不同种类的宝可梦。\p"
	.string "它们也不能携带\n"
	.string "相同种类的道具。\p"
	.string "蛋{STR_VAR_1}不符合资格。\p"
	.string "当你做好准备后，\n"
	.string "请再来。$"

BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLv50:
	.string "{CHN}亲爱的挑战者！\p"
	.string "你没有参赛所需的\n"
	.string "三只宝可梦。\p"
	.string "要符合资格，你必须带三只\n"
	.string "不同种类的宝可梦。\p"
	.string "这三只不同的宝可梦\n"
	.string "必须都是50级或以下。\p"
	.string "它们也不能携带\n"
	.string "相同种类的道具。\p"
	.string "蛋{STR_VAR_1}不符合资格。\p"
	.string "当你做好准备后，\n"
	.string "请再来。$"

BattleFrontier_BattleArenaLobby_Text_GuideYouToArena:
	.string "{CHN}我现在带你去\n"
	.string "对战竞技场。$"

BattleFrontier_BattleArenaLobby_Text_DidntSaveBeforeShuttingDown:
	.string "{CHN}亲爱的挑战者！\p"
	.string "你在关机前没有保存游戏，\n"
	.string "对吧？\p"
	.string "很遗憾，这导致了\n"
	.string "你的挑战被取消资格。\l"
	.string "你的挑战已作废。\p"
	.string "当然，你可以\n"
	.string "重新开始新的挑战。$"

BattleFrontier_BattleArenaLobby_Text_CongratsOnSevenWins:
	.string "{CHN}恭喜你连续击败了\n"
	.string "七位训练家，取得了辉煌的连胜！$"

BattleFrontier_BattleArenaLobby_Text_RecordAchievement:
	.string "{CHN}你的成就将被记录。\n"
	.string "请稍等，我正在保存游戏。$"

/* Unused*/
BattleFrontier_BattleArenaLobby_Text_PresentYouWithPrize:
	.string "{CHN}为纪念你的七连胜，\n"
	.string "我们向你颁发此奖品。$"

/* Unused*/
BattleFrontier_BattleArenaLobby_Text_ReceivedPrize:
	.string "{CHN}{PLAYER}获得了奖品\n"
	.string "{STR_VAR_1}。$"

/* Unused*/
BattleFrontier_BattleArenaLobby_Text_BagFullReturnForPrize:
	.string "{CHN}哦？\n"
	.string "你的包包好像满了。\p"
	.string "我建议你腾出空间\n"
	.string "后再来领取奖品。$"

BattleFrontier_BattleArenaLobby_Text_ThankYouWaitWhileSave:
	.string "{CHN}非常感谢你的参与！\p"
	.string "请稍等，我正在保存游戏。$"

BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge2:
	.string "{CHN}我们期待你\n"
	.string "在另一天来挑战！$"

BattleFrontier_BattleArenaLobby_Text_LookingForwardToArrivalSaveGame:
	.string "{CHN}我们一直期待着\n"
	.string "你的到来。\p"
	.string "在我带你去对战竞技场之前，\n"
	.string "我必须保存游戏。\l"
	.string "请稍等。$"

BattleFrontier_BattleArenaLobby_Text_RecordLastMatch:
	.string "{CHN}要我把你上一场对战竞技场的\n"
	.string "对战记录到你的开拓区通行证上吗？$"

BattleFrontier_BattleArenaLobby_Text_BadIdeaToNotAttack:
	.string "{CHN}我因为裁判的判定输了……\p"
	.string "我觉得只使用防御性招式\n"
	.string "而不攻击不是个好主意……$"

BattleFrontier_BattleArenaLobby_Text_LandingHitsWorked:
	.string "{CHN}我通过评判获胜了！\p"
	.string "持续命中对手的\n"
	.string "宝可梦起了作用！$"

BattleFrontier_BattleArenaLobby_Text_MatchWasDeclaredDraw:
	.string "{CHN}我们的比赛被判定为平局。\p"
	.string "时间到的时候，我的宝可梦\n"
	.string "和对手的宝可梦剩余的\l"
	.string "HP差不多。$"

BattleFrontier_BattleArenaLobby_Text_OrderOfMonsImportant:
	.string "{CHN}在对战竞技场，宝可梦的顺序\n"
	.string "非常重要。\p"
	.string "例如，如果你的第一只宝可梦\n"
	.string "有某些属性劣势，\l"
	.string "可以试试让第二只宝可梦\l"
	.string "携带对第一只效果拔群的招式。\p"
	.string "我觉得那是组建\n"
	.string "有效队伍的好方法。$"

BattleFrontier_BattleArenaLobby_Text_RulesAreListed:
	.string "{CHN}这里列出了淘汰赛的规则。$"

BattleFrontier_BattleArenaLobby_Text_ReadWhichHeading:
	.string "{CHN}你想阅读哪个标题？$"

BattleFrontier_BattleArenaLobby_Text_ExplainBattleRules:
	.string "{CHN}淘汰赛有特殊规则，\n"
	.string "与普通对战不同。\p"
	.string "首先，一场对战只持续\n"
	.string "三个回合。\p"
	.string "如果三回合后未决出胜负，\n"
	.string "将交由评判裁决。\p"
	.string "裁判会根据宝可梦的对战表现\n"
	.string "来选择胜者。\p"
	.string "另外，宝可梦在比赛胜负未定前\n"
	.string "不能被替换下场。$"

BattleFrontier_BattleArenaLobby_Text_ExplainMindRules:
	.string "{CHN}第一个评判项目是“心智”。\n"
	.string "这个项目评估对战者的\l"
	.string "攻击积极性。\p"
	.string "评判基于训练家下令使用\n"
	.string "攻击性招式的\l"
	.string "频率。$"

BattleFrontier_BattleArenaLobby_Text_ExplainSkillRules:
	.string "{CHN}第二个评判项目是“技巧”。\n"
	.string "这个项目评估宝可梦招式\l"
	.string "使用的有效性。\p"
	.string "如果招式成功命中，\n"
	.string "技巧评分会上升。\p"
	.string "如果招式失败，技巧评分\n"
	.string "会下降。\p"
	.string "如果是攻击招式，当招式\n"
	.string "“效果拔群”时技巧评分\l"
	.string "上升，当招式\l"
	.string "“效果不理想”时下降。\p"
	.string "对于守住和察觉这类招式，\n"
	.string "技巧评分不会上升。\p"
	.string "如果对手使用了守住或察觉，\n"
	.string "而你的宝可梦没能\l"
	.string "命中招式，它的技巧评分不会\l"
	.string "下降。$"

BattleFrontier_BattleArenaLobby_Text_ExplainBodyRules:
	.string "{CHN}第三个评判项目是“体魄”。\n"
	.string "这个项目基于对战结束时\l"
	.string "剩余的HP量。\p"
	.string "评分会考虑宝可梦在对战开始时\n"
	.string "拥有的HP，\l"
	.string "以及结束时剩余的HP。$"

BattleFrontier_BattleArenaLobby_Text_CongratsOnDefeatingTycoon:
	.string "{CHN}从竞技场首脑手中夺得胜利，\n"
	.string "并横扫七位训练家！\p"
	.string "我们恭喜你完成了\n"
	.string "最精彩的挑战！$"

BattleFrontier_BattleArenaLobby_Text_PleaseAcceptBattlePoints:
	.string "{CHN}亲爱的挑战者，为表彰你\n"
	.string "不屈不挠的精神，请\l"
	.string "收下这些对战点数。$"
