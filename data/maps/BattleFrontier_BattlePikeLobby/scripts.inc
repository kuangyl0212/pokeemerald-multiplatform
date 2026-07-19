BattleFrontier_BattlePikeLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePikeLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePikeLobby_OnWarp
	.byte 0

BattleFrontier_BattlePikeLobby_OnFrame:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattlePikeLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePikeLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattlePikeLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattlePikeLobby_EventScript_LostChallenge
	.short 0

BattleFrontier_BattlePikeLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePikeLobby_EventScript_TurnPlayerNorth
	.short 0

BattleFrontier_BattlePikeLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePikeLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattlePikeLobby_EventScript_QuitWithoutSaving::
	special HealPlayerParty
	pike_resethelditems
	lockall
	msgbox BattleFrontier_BattlePikeLobby_Text_FailedToSaveBeforeQuitting, MSGBOX_DEFAULT
	closemessage
	pike_set PIKE_DATA_WIN_STREAK, 0
	pike_set PIKE_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePikeLobby_EventScript_DefeatedQueen
	msgbox BattleFrontier_BattlePikeLobby_Text_PossessLuckInAbundance, MSGBOX_DEFAULT
	waitmessage
	goto BattleFrontier_BattlePikeLobby_EventScript_GiveBattlePoints

BattleFrontier_BattlePikeLobby_EventScript_DefeatedQueen::
	msgbox BattleFrontier_BattlePikeLobby_Text_SnatchedVictoryFromQueen, MSGBOX_DEFAULT
	waitmessage
BattleFrontier_BattlePikeLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattlePikeLobby_Text_AwardYouTheseBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	frontier_checkairshow
	pike_get PIKE_DATA_TOTAL_STREAKS
	addvar VAR_RESULT, 1
	pike_set PIKE_DATA_TOTAL_STREAKS, VAR_RESULT
	special LoadPlayerParty
	special HealPlayerParty
	pike_resethelditems
	message BattleFrontier_BattlePikeLobby_Text_ShallRecordResults
	waitmessage
	pike_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_LostChallenge::
	lockall
	message BattleFrontier_BattlePikeLobby_Text_ChallengeEndedRecordResults
	waitmessage
	frontier_checkairshow
	frontier_set FRONTIER_DATA_BATTLE_NUM, 0
	pike_set PIKE_DATA_WIN_STREAK_ACTIVE, FALSE
	special LoadPlayerParty
	special HealPlayerParty
	pike_resethelditems
	pike_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_Attendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PIKE
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattlePikeLobby_Text_WelcomeToBattlePike, MSGBOX_DEFAULT
BattleFrontier_BattlePikeLobby_EventScript_AskTakeChallenge::
	message BattleFrontier_BattlePikeLobby_Text_TakeChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePikeLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattlePikeLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattlePikeLobby_Text_WhichChallengeMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattlePikeLobby_Text_PleaseChooseThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattlePikeLobby_Text_SaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattlePikeLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_1, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	pike_init
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	pike_set PIKE_DATA_WIN_STREAK_ACTIVE, TRUE
	pike_savehelditems
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	pike_savehelditems
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePikeLobby_EventScript_CancelChallengeSaveFailed
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattlePikeLobby_Text_StepThisWay, MSGBOX_DEFAULT
	closemessage
	frontier_settrainers
	call BattleFrontier_BattlePikeLobby_EventScript_WalkToCorridor
	special HealPlayerParty
	call BattleFrontier_BattlePike_EventScript_CloseCurtain
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PIKE_CORRIDOR, 6, 7
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattlePikeLobby_EventScript_ExplainChallenge::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainBattlePike, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_AskTakeChallenge

BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou, MSGBOX_DEFAULT
BattleFrontier_BattlePikeLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattlePikeLobby_EventScript_ShowResults::
	lockall
	frontier_results FRONTIER_FACILITY_PIKE
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_WalkToCorridor::
	applymovement LOCALID_PIKE_LOBBY_ATTENDANT, BattleFrontier_BattlePikeLobby_Movement_AttendantWalkToCorridor
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePikeLobby_Movement_PlayerWalkToCorridor
	waitmovement 0
	return

BattleFrontier_BattlePikeLobby_Movement_PlayerWalkToCorridor:
	walk_up
BattleFrontier_BattlePikeLobby_Movement_AttendantWalkToCorridor:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattlePikeLobby_EventScript_Hiker::
	msgbox BattleFrontier_BattlePikeLobby_Text_OneRoomAwayFromGoal, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_Twin::
	msgbox BattleFrontier_BattlePikeLobby_Text_NeverHadToBattleTrainer, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_Beauty::
	msgbox BattleFrontier_BattlePikeLobby_Text_ThinkAbilitiesUsefulHere, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattlePikeLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattlePikeLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 16, 4, MULTI_BATTLE_PIKE_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePikeLobby_EventScript_RulesPokenavBag
	case 1, BattleFrontier_BattlePikeLobby_EventScript_RulesHeldItems
	case 2, BattleFrontier_BattlePikeLobby_EventScript_RulesMonOrder
	case 3, BattleFrontier_BattlePikeLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_ExitRules
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesPokenavBag::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainPokenavBagRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesHeldItems::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainHeldItemRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesMonOrder::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainMonOrderRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePikeLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattlePike_EventScript_CloseCurtain::
	playse SE_PIKE_CURTAIN_CLOSE
	special CloseBattlePikeCurtain
	waitstate
	waitse
	return

BattleFrontier_BattlePikeLobby_Text_WelcomeToBattlePike:
	.string "{CHN}这里是考验训练家\n"
	.string "运气之处……\p"
	.string "欢迎来到对战管道……\p"
	.string "我是你对战管道的向导……$"

BattleFrontier_BattlePikeLobby_Text_TakeChallenge:
	.string "{CHN}你想接受\n"
	.string "对战选择挑战吗？$"

BattleFrontier_BattlePikeLobby_Text_ExplainBattlePike:
	.string "{CHN}这里举办的活动\n"
	.string "叫做对战选择。\p"
	.string "对战选择的规则\n"
	.string "非常简单……\p"
	.string "从三条路径中选择一条，\n"
	.string "走到对战管道尽头\l"
	.string "的目标房间即可。就这么简单。\p"
	.string "不过，所选路径上会发生什么，\n"
	.string "完全取决于挑战者\l"
	.string "的运气……\p"
	.string "若你能到达终点，\n"
	.string "将获得对战点数作为奖励。\p"
	.string "若想中断挑战，\n"
	.string "请与沿途大房间里的\l"
	.string "工作人员交谈。\p"
	.string "若中断前未保存，\n"
	.string "你将被取消资格。$"

BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou:
	.string "{CHN}期待下次\n"
	.string "再见到你……$"

BattleFrontier_BattlePikeLobby_Text_WhichChallengeMode:
	.string "{CHN}你有两个课程可选，\n"
	.string "50级和自由级别。\l"
	.string "你要挑战哪一个？$"

BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLv50:
	.string "{CHN}不好意思……\p"
	.string "你没有三只\n"
	.string "符合对战选择资格的宝可梦。\p"
	.string "参赛需要三只不同种类\n"
	.string "且等级在50级以下的宝可梦。\p"
	.string "它们也不能携带\n"
	.string "相同种类的道具。\p"
	.string "蛋{STR_VAR_1}不符合资格。\p"
	.string "请准备好后\n"
	.string "再来找我……$"

BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLvOpen:
	.string "{CHN}不好意思……\p"
	.string "你没有三只\n"
	.string "符合对战选择资格的宝可梦。\p"
	.string "参赛需要三只\n"
	.string "不同的宝可梦。\p"
	.string "它们也不能携带\n"
	.string "相同种类的道具。\p"
	.string "蛋{STR_VAR_1}不符合资格。\p"
	.string "请准备好后\n"
	.string "再来找我……$"

BattleFrontier_BattlePikeLobby_Text_PleaseChooseThreeMons:
	.string "{CHN}请选择你想参加\n"
	.string "挑战的三只宝可梦……$"

BattleFrontier_BattlePikeLobby_Text_SaveBeforeChallenge:
	.string "{CHN}开始对战选择\n"
	.string "挑战之前，必须保存游戏。\l"
	.string "可以吗？$"

BattleFrontier_BattlePikeLobby_Text_StepThisWay:
	.string "{CHN}请这边走……$"

BattleFrontier_BattlePikeLobby_Text_ChallengeEndedRecordResults:
	.string "{CHN}你的挑战结束了……\p"
	.string "我将记录你的成绩。\n"
	.string "请稍候……$"

BattleFrontier_BattlePikeLobby_Text_PossessLuckInAbundance:
	.string "{CHN}你完成了挑战……\p"
	.string "我得说……你似乎\n"
	.string "拥有极好的运气……$"

BattleFrontier_BattlePikeLobby_Text_ShallRecordResults:
	.string "{CHN}我将记录你的成绩。\n"
	.string "请稍候……$"

/* Unused*/
BattleFrontier_BattlePikeLobby_Text_AwardYouTheseBattlePoints2:
	.string "{CHN}为纪念你完成\n"
	.string "对战选择挑战，我们赠予\l"
	.string "你这些对战点数……$"

/* Unused*/
BattleFrontier_BattlePikeLobby_Text_ReachedBattlePointLimit:
	.string "{CHN}你似乎已达到\n"
	.string "对战点数的上限……\p"
	.string "请先兑换一些对战点数\n"
	.string "为奖品，再来……$"

BattleFrontier_BattlePikeLobby_Text_FailedToSaveBeforeQuitting:
	.string "{CHN}不好意思……\p"
	.string "上次你退出挑战前\n"
	.string "未保存进度。\p"
	.string "因此，你的挑战进度\n"
	.string "已被取消资格。非常抱歉……$"

BattleFrontier_BattlePikeLobby_Text_SnatchedVictoryFromQueen:
	.string "{CHN}恭喜……\p"
	.string "你从管道女王手中\n"
	.string "夺走了胜利，通过了挑战……$"

BattleFrontier_BattlePikeLobby_Text_AwardYouTheseBattlePoints:
	.string "{CHN}为表彰你惊人的运气，\n"
	.string "我们赠予你这些对战点数……$"

BattleFrontier_BattlePikeLobby_Text_OneRoomAwayFromGoal:
	.string "{CHN}啊！我错失了机会！\n"
	.string "我只差一个房间就到终点了！\p"
	.string "在这个地方，你最好小心\n"
	.string "中毒、冰冻等异常状态。$"

BattleFrontier_BattlePikeLobby_Text_NeverHadToBattleTrainer:
	.string "{CHN}我已经完成了10次挑战，\n"
	.string "但从未与训练家\l"
	.string "对战过一次。$"

BattleFrontier_BattlePikeLobby_Text_ThinkAbilitiesUsefulHere:
	.string "{CHN}听我说！听我说！\p"
	.string "你不觉得宝可梦的\n"
	.string "特性在这里\l"
	.string "会很有用吗？$"

/* Unused*/
BattleFrontier_BattlePikeLobby_Text_TrainersWhicheverPathIChoose:
	.string "{CHN}这是什么奇怪的地方？\n"
	.string "我完全搞不懂！\p"
	.string "我已经挑战了好多次，\n"
	.string "但无论选哪条路，\l"
	.string "都会遇到训练家。$"

BattleFrontier_BattlePikeLobby_Text_RulesAreListed:
	.string "{CHN}这里列出了对战选择的规则。$"

BattleFrontier_BattlePikeLobby_Text_ReadWhichHeading:
	.string "{CHN}你想阅读哪个标题？$"

BattleFrontier_BattlePikeLobby_Text_ExplainPokenavBagRules:
	.string "{CHN}在对战选择挑战期间，\n"
	.string "不得使用背包和宝可梦导航器。$"

BattleFrontier_BattlePikeLobby_Text_ExplainHeldItemRules:
	.string "{CHN}在对战选择挑战期间，\n"
	.string "宝可梦携带的任何树果或草药\l"
	.string "只会生效一次。$"

BattleFrontier_BattlePikeLobby_Text_ExplainMonOrderRules:
	.string "{CHN}在对战选择挑战期间，\n"
	.string "宝可梦的顺序\l"
	.string "无法更改。\p"
	.string "顺序必须在开始挑战前\n"
	.string "设定好。$"

