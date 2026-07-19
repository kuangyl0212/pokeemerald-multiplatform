SlateportCity_BattleTentCorridor_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SlateportCity_BattleTentCorridor_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SlateportCity_BattleTentCorridor_OnWarp
	.byte 0

	/* This is Slateport Tent's version of the Battle Factory Pre-Battle Room*/

SlateportCity_BattleTentCorridor_OnWarp:
	map_script_2 VAR_TEMP_1, 0, SlateportCity_BattleTentCorridor_EventScript_SetUpObjects
	.short 0

SlateportCity_BattleTentCorridor_EventScript_SetUpObjects::
	setvar VAR_TEMP_1, 1
	goto_if_ne VAR_0x8006, 1, SlateportCity_BattleTentCorridor_EventScript_TurnPlayerNorth
	setobjectxy LOCALID_SLATEPORT_TENT_CORRIDOR_ATTENDANT, 2, 2
	turnobject LOCALID_SLATEPORT_TENT_CORRIDOR_ATTENDANT, DIR_SOUTH
SlateportCity_BattleTentCorridor_EventScript_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

SlateportCity_BattleTentCorridor_OnFrame:
	map_script_2 VAR_TEMP_0, 0, SlateportCity_BattleTentCorridor_EventScript_EnterCorridor
	.short 0

SlateportCity_BattleTentCorridor_EventScript_EnterCorridor::
	goto_if_eq VAR_0x8006, 1, SlateportCity_BattleTentCorridor_EventScript_ReturnToRoomFromBattle
	setvar VAR_TEMP_0, 1
	applymovement LOCALID_SLATEPORT_TENT_CORRIDOR_ATTENDANT, SlateportCity_BattleTentCorridor_Movement_AttendantEnter
	applymovement LOCALID_PLAYER, SlateportCity_BattleTentCorridor_Movement_PlayerEnter
	waitmovement 0
	goto_if_eq VAR_0x8006, 2, SlateportCity_BattleTentCorridor_EventScript_ResumeChallenge
	slateporttent_generaterentalmons
	slateporttent_generateopponentmons
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_HoldMonsChooseFromSelection, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	slateporttent_rentmons
	waitstate
SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom::
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_RightThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_TENT_CORRIDOR_ATTENDANT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor 2, 1
	waitdooranim
	applymovement LOCALID_SLATEPORT_TENT_CORRIDOR_ATTENDANT, SlateportCity_BattleTentCorridor_Movement_AttendantExit
	applymovement LOCALID_PLAYER, SlateportCity_BattleTentCorridor_Movement_PlayerExit
	waitmovement 0
	closedoor 2, 1
	waitdooranim
	warp MAP_SLATEPORT_CITY_BATTLE_TENT_BATTLE_ROOM, 4, 4
	waitstate
	end

SlateportCity_BattleTentCorridor_EventScript_ReturnToRoomFromBattle::
	factory_setopponentmons
	factory_resethelditems
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_LetUsRestoreMons, MSGBOX_DEFAULT
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent::
	frontier_get FRONTIER_DATA_BATTLE_NUM
	call_if_eq VAR_RESULT, 1, SlateportCity_BattleTentCorridor_EventScript_ReadyFor2ndOpponent
	call_if_eq VAR_RESULT, 2, SlateportCity_BattleTentCorridor_EventScript_ReadyFor3rdOpponent
	multichoice 20, 6, MULTI_GO_ON_REST_RETIRE, TRUE
	switch VAR_RESULT
	case 0, SlateportCity_BattleTentCorridor_EventScript_AskSwapMon
	case 1, SlateportCity_BattleTentCorridor_EventScript_AskPauseChallenge
	case 2, SlateportCity_BattleTentCorridor_EventScript_AskRetireChallenge

SlateportCity_BattleTentCorridor_EventScript_AskPauseChallenge::
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_SaveAndQuitGame, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent
	case YES, SlateportCity_BattleTentCorridor_EventScript_PauseChallenge
	case MULTI_B_PRESSED, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent

SlateportCity_BattleTentCorridor_EventScript_AskRetireChallenge::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_RetireFromChallenge
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent
	case 0, SlateportCity_BattleTent_EventScript_WarpToLobbyLost
	case MULTI_B_PRESSED, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent

SlateportCity_BattleTentCorridor_EventScript_AskSwapMon::
	slateporttent_generateopponentmons
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_LikeToSwapMon, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom
	case YES, SlateportCity_BattleTentCorridor_EventScript_SwapMons
	case MULTI_B_PRESSED, SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom

SlateportCity_BattleTentCorridor_EventScript_SwapMons::
	fadescreen FADE_TO_BLACK
	slateporttent_swapmons
	waitstate
	goto_if_eq VAR_RESULT, 1, SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_YourSwapIsComplete, MSGBOX_DEFAULT
	goto SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom

SlateportCity_BattleTentCorridor_EventScript_ReadyFor2ndOpponent::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor2ndOpponent
	waitmessage
	return

SlateportCity_BattleTentCorridor_EventScript_ReadyFor3rdOpponent::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor3rdOpponent
	waitmessage
	return

SlateportCity_BattleTentCorridor_EventScript_PauseChallenge::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_SavingDataPleaseWait
	waitmessage
	slateporttent_save CHALLENGE_STATUS_PAUSED
	playse SE_SAVE
	waitse
	fadescreen FADE_TO_BLACK
	frontier_reset
	end

SlateportCity_BattleTentCorridor_EventScript_ResumeChallenge::
	special SavePlayerParty
	factory_setparties 0
	goto SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent

SlateportCity_BattleTentCorridor_Movement_PlayerEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SlateportCity_BattleTentCorridor_Movement_PlayerExit:
	walk_up
	walk_up
	set_invisible
	step_end

SlateportCity_BattleTentCorridor_Movement_AttendantEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

SlateportCity_BattleTentCorridor_Movement_AttendantExit:
	walk_up
	set_invisible
	step_end

/* Leftover text from when this was a Contest Hall in R/S*/
/* Unused*/
SlateportCity_ContestHall_Text_AdviceForContests:
	.string "{CHN}想要一点关于\n"
	.string "评选赛的小建议吗？\p"
	.string "在某些招式之后使用特定招式\n"
	.string "有时能让你\l"
	.string "获得额外的关注。\p"
	.string "如果你知道自己在做什么，\n"
	.string "可以在评审中大放异彩。\p"
	.string "当然，你的对手可能会尝试\n"
	.string "干扰你的宝可梦的表现。$"

/* Unused*/
SlateportCity_ContestHall_Text_MyPapaIsContestJudge:
	.string "{CHN}我爸爸是评选赛裁判。\p"
	.string "我不知道长大后应该做什么，\n"
	.string "当裁判还是道馆馆主呢？$"

/* Unused*/
SlateportCity_ContestHall_Text_ImLikeMajorlyCheesed:
	.string "{CHN}嘿，老兄，我真是气炸了，\n"
	.string "你懂的。就是，你懂的，我就是\l"
	.string "想知道为什么我的宝可梦\l"
	.string "从来没赢过，你懂的，嘿？\p"
	.string "所以，我就给裁判提了点\n"
	.string "意见，你懂的，免费的。\p"
	.string "但是他根本不听我说，嘿！\n"
	.string "真是太倒霉了，老兄！\p"
	.string "喂，你！闭嘴好吗？\n"
	.string "拿着这个吧！$"

/* Unused*/
SlateportCity_ContestHall_Text_ExplainTorment:
	.string "{CHN}那个是招式学习器41，知道吗？\n"
	.string "是惩磨难！听到了吗？\p"
	.string "它不会让对方\n"
	.string "连续使用同一个招式，懂吗？\p"
	.string "喂，你听着，\n"
	.string "我不是在折磨你！$"

/* Unused*/
SlateportCity_ContestHall_Text_MCStepUpTakePartInContest:
	.string "{CHN}主持人：哦，天哪！\n"
	.string "那真是一只出色的宝可梦啊！\p"
	.string "请！一定要来参加\n"
	.string "我们精彩的评选赛！\p"
	.string "你会做得很好的！我确信！\n"
	.string "我的眼光从不会出错！$"

/* Unused*/
SlateportCity_ContestHall_Text_JudgeWouldntDoToMissContest:
	.string "{CHN}裁判：哎呀，你好！\n"
	.string "我看出来你是个训练家！\p"
	.string "那么，你绝对不能错过\n"
	.string "宝可梦评选赛！\p"
	.string "去茵郁市拿一张\n"
	.string "评选赛通行证，随时可以参加！$"

/* Unused*/
SlateportCity_ContestHall_Text_ItsAppealTime:
	.string "{CHN}评审时间到了！\n"
	.string "我应该先上谁呢？$"

/* Unused*/
SlateportCity_ContestHall_Text_DidntPayAttentionToAppeal:
	.string "{CHN}他们没怎么关注\n"
	.string "我的宝可梦的评审…\p"
	.string "哼，那个裁判，他根本\n"
	.string "不识货。$"

/* Unused*/
SlateportCity_ContestHall_Text_RewardWithSageAdvice:
	.string "{CHN}哦，嗨！你一定是个铁杆粉丝才能靠\n"
	.string "这么近。\p"
	.string "我会用这个金玉良言\n"
	.string "来奖励你的热情。\p"
	.string "如果一个招式效果特别好，\n"
	.string "观众就会兴奋起来。\p"
	.string "在大家都很兴奋的时候\n"
	.string "进行评审的宝可梦…\p"
	.string "嗯，你肯定觉得会\n"
	.string "发生什么好事！$"

/* Unused*/
SlateportCity_ContestHall_Text_MoreFreakedOutThanMon:
	.string "{CHN}我做不到！我比\n"
	.string "我的宝可梦还紧张。\p"
	.string "我在发抖，心跳得厉害！$"

/* Unused*/
SlateportCity_ContestHall_Text_BattleAndContestAlike:
	.string "{CHN}战斗和评选赛不是\n"
	.string "一回事，但它们也有相似之处。\p"
	.string "你需要努力工作，相信\n"
	.string "你培育的宝可梦。$"

/* Unused*/
SlateportCity_ContestHall_Text_MonLooksOnTopOfGame:
	.string "{CHN}那只宝可梦看起来状态\n"
	.string "正佳啊？\p"
	.string "在第二轮评审中表现好的\n"
	.string "宝可梦在评审时似乎\l"
	.string "更从容。$"

/* Unused*/
SlateportCity_ContestHall_Text_MyMonBetterThanThatLot:
	.string "{CHN}你看看那副惨样？\p"
	.string "嘿，我的宝可梦绝对比\n"
	.string "那群强！$"

/* Unused*/
SlateportCity_ContestHall_Text_GetUrgeToMoveWithMon:
	.string "{CHN}如果宝可梦正在进行\n"
	.string "充满活力的评审，你不会\l"
	.string "想和它们一起动起来吗？$"

/* Unused*/
SlateportCity_ContestHall_Text_HyperRankStage:
	.string "{CHN}宝可梦评选赛\n"
	.string "高级组舞台！$"

