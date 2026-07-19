BattleFrontier_ReceptionGate_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_ReceptionGate_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_ReceptionGate_OnTransition
	.byte 0

BattleFrontier_ReceptionGate_OnTransition:
	setflag FLAG_LANDMARK_BATTLE_FRONTIER
	end

BattleFrontier_ReceptionGate_OnFrame:
	map_script_2 VAR_HAS_ENTERED_BATTLE_FRONTIER, 0, BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering
	.short 0

BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering::
	lockall
	setvar VAR_HAS_ENTERED_BATTLE_FRONTIER, 1
	playse SE_PIN
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_Delay48
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter
	waitmovement 0
	goto BattleFrontier_ReceptionGate_EventScript_ScottScene
	end

BattleFrontier_ReceptionGate_EventScript_ScottScene::
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IssueFrontierPass, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass
	waitfanfare
	waitmessage
	msgbox BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass, MSGBOX_DEFAULT
	setflag FLAG_SYS_FRONTIER_PASS
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_FRONTIER_RECEPTION_GUIDE, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_ExclamationMark
	applymovement LOCALID_FRONTIER_RECEPTION_GUIDE, Common_Movement_ExclamationMark
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, BattleFrontier_ReceptionGate_Movement_GreeterFaceScott
	applymovement LOCALID_FRONTIER_RECEPTION_GUIDE, BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott
	applymovement LOCALID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerFaceScott
	applymovement LOCALID_FRONTIER_RECEPTION_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottEnter
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_RECEPTION_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottExit
	waitmovement 0
	removeobject LOCALID_FRONTIER_RECEPTION_SCOTT
	releaseall
	end

BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter:
	walk_up
	walk_up
	walk_left
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_PlayerFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

/* Unused*/
BattleFrontier_ReceptionGate_Movement_WalkDown:
	walk_down
	walk_down
	step_end

BattleFrontier_ReceptionGate_Movement_ScottEnter:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_ScottExit:
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_ReceptionGate_Movement_GreeterFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

BattleFrontier_ReceptionGate_EventScript_Greeter::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_FacilityGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToFacilities, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich2
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_BF_RECEPTIONIST
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_BattleTower
	case 1, BattleFrontier_ReceptionGate_EventScript_BattleDome
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePalace
	case 3, BattleFrontier_ReceptionGate_EventScript_BattleArena
	case 4, BattleFrontier_ReceptionGate_EventScript_BattleFactory
	case 5, BattleFrontier_ReceptionGate_EventScript_BattlePike
	case 6, BattleFrontier_ReceptionGate_EventScript_BattlePyramid
	case 7, BattleFrontier_ReceptionGate_EventScript_RankingHall
	case 8, BattleFrontier_ReceptionGate_EventScript_ExchangeCorner
	case 9, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide
	end

BattleFrontier_ReceptionGate_EventScript_BattleTower::
	msgbox BattleFrontier_ReceptionGate_Text_BattleTowerInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleDome::
	msgbox BattleFrontier_ReceptionGate_Text_BattleDomeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePalace::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePalaceInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleArena::
	msgbox BattleFrontier_ReceptionGate_Text_BattleArenaInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleFactory::
	msgbox BattleFrontier_ReceptionGate_Text_BattleFactoryInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePike::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePikeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePyramid::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePyramidInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_RankingHall::
	msgbox BattleFrontier_ReceptionGate_Text_RankingHallInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExchangeCorner::
	msgbox BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_RulesGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToRules, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhat
	waitmessage
	multichoice 15, 0, MULTI_FRONTIER_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_LevelMode
	case 1, BattleFrontier_ReceptionGate_EventScript_Level50
	case 2, BattleFrontier_ReceptionGate_EventScript_OpenLevel
	case 3, BattleFrontier_ReceptionGate_EventScript_MonEntry
	case 4, BattleFrontier_ReceptionGate_EventScript_HoldItems
	case 5, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide
	end

BattleFrontier_ReceptionGate_EventScript_LevelMode::
	msgbox BattleFrontier_ReceptionGate_Text_LevelModeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_Level50::
	msgbox BattleFrontier_ReceptionGate_Text_Level50Info, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_OpenLevel::
	msgbox BattleFrontier_ReceptionGate_Text_OpenLevelInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_MonEntry::
	msgbox BattleFrontier_ReceptionGate_Text_MonEntryInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_HoldItems::
	msgbox BattleFrontier_ReceptionGate_Text_HoldItemsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_FrontierPassGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich1
	waitmessage
	multichoice 16, 4, MULTI_FRONTIER_PASS_INFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_Symbols
	case 1, BattleFrontier_ReceptionGate_EventScript_RecordBattle
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePoints
	case 3, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide
	end

BattleFrontier_ReceptionGate_EventScript_Symbols::
	msgbox BattleFrontier_ReceptionGate_Text_SymbolsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_RecordBattle::
	msgbox BattleFrontier_ReceptionGate_Text_RecordedBattleInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePoints::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePointsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay:
	.string "{CHN}你是第一次来吗？\n"
	.string "请这边走！$"

BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier:
	.string "{CHN}宝可梦对战的最前线！\n"
	.string "欢迎来到对战开拓区！$"

BattleFrontier_ReceptionGate_Text_IssueFrontierPass:
	.string "{CHN}对于初次来访的客人，\n"
	.string "我们会发放开拓区通行证。\p"
	.string "它可以在对战开拓区的\n"
	.string "所有设施中使用。\p"
	.string "这个给你！$"

BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass:
	.string "{CHN}{PLAYER}获得了\n"
	.string "开拓区通行证。$"

BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass:
	.string "{CHN}{PLAYER}将训练家卡片\n"
	.string "放入了开拓区通行证。$"

BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier:
	.string "{CHN}希望你能尽情享受\n"
	.string "对战开拓区的一切！$"

BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame:
	.string "{CHN}？？：哎呀，这不是{PLAYER}{KUN}吗！\n"
	.string "你到这里来了！$"

BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay:
	.string "{CHN}引导员：哦！亚希达先生！\n"
	.string "您好，先生！$"

BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere:
	.string "{CHN}亚希达：很高兴在这里见到你，\n"
	.string "真的很高兴！\p"
	.string "希望你能慢慢来，\n"
	.string "到处看看。\p"
	.string "当然，我也希望你能体验到\n"
	.string "对战的纯粹精髓。\p"
	.string "我在这里也有住处，\n"
	.string "有空的话欢迎来坐坐。$"

BattleFrontier_ReceptionGate_Text_YourGuideToFacilities:
	.string "{CHN}我是对战开拓区\n"
	.string "各设施的引导员。$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhich2:
	.string "{CHN}你想了解哪个设施呢？$"

BattleFrontier_ReceptionGate_Text_BattleTowerInfo:
	.string "{CHN}那是对战开拓区象征的\n"
	.string "巨大高塔。\p"
	.string "塔中有四种对战房，\n"
	.string "分别为单打、双打、多人\l"
	.string "和联机多人对战。$"

BattleFrontier_ReceptionGate_Text_BattleDomeInfo:
	.string "{CHN}对战巨蛋是那栋像巨蛋一样\n"
	.string "形状的大型建筑。\p"
	.string "名为对战锦标赛的项目\n"
	.string "在这个设施中举行。\p"
	.string "对战锦标赛分为两个级别——\n"
	.string "单打和双打\l"
	.string "对战。$"

BattleFrontier_ReceptionGate_Text_BattlePalaceInfo:
	.string "{CHN}对战宫殿是对战开拓区\n"
	.string "右侧的红色建筑。\p"
	.string "有两种对战厅，\n"
	.string "分别用于单打和双打对战。$"

BattleFrontier_ReceptionGate_Text_BattleArenaInfo:
	.string "{CHN}对战竞技场是对战开拓区\n"
	.string "中右侧那栋\l"
	.string "类似道场的建筑。\p"
	.string "名为连环淘汰赛的项目\n"
	.string "在对战竞技场举行。$"

BattleFrontier_ReceptionGate_Text_BattleFactoryInfo:
	.string "{CHN}对战工厂是离我们最近的\n"
	.string "那栋大型建筑。\p"
	.string "名为对战交换的项目\n"
	.string "在那里进行。\p"
	.string "对战交换项目分为两个级别，\n"
	.string "分别是单打和双打\l"
	.string "对战。$"

BattleFrontier_ReceptionGate_Text_BattlePikeInfo:
	.string "{CHN}对战管道是对战开拓区\n"
	.string "中左侧那栋\l"
	.string "宝可梦形状的建筑。\p"
	.string "名为对战选择的项目\n"
	.string "在那里进行。$"

BattleFrontier_ReceptionGate_Text_BattlePyramidInfo:
	.string "{CHN}对战金字塔是那座\n"
	.string "巨大的金字塔。\p"
	.string "名为对战探险的项目\n"
	.string "在那里进行。$"

BattleFrontier_ReceptionGate_Text_RankingHallInfo:
	.string "{CHN}名人堂位于\n"
	.string "对战塔附近。\p"
	.string "在那里，你可以看到那些\n"
	.string "接受了对战开拓区诸多挑战的\l"
	.string "训练家们留下的\l"
	.string "最辉煌的记录。$"

BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo:
	.string "{CHN}兑换服务柜台位于\n"
	.string "对战塔附近。\p"
	.string "你在对战开拓区\n"
	.string "获得的对战点数\l"
	.string "可以在那里兑换成丰厚的奖品。$"

BattleFrontier_ReceptionGate_Text_YourGuideToRules:
	.string "{CHN}我是对战开拓区各设施挑战\n"
	.string "通用基本规则的\l"
	.string "引导员。$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhat:
	.string "{CHN}你想了解什么呢？$"

BattleFrontier_ReceptionGate_Text_LevelModeInfo:
	.string "{CHN}对战开拓区各设施的所有挑战\n"
	.string "都分为两个级别——\l"
	.string "50级和自由级别。$"

BattleFrontier_ReceptionGate_Text_Level50Info:
	.string "{CHN}50级课程允许50级及以下\n"
	.string "的宝可梦参加。\p"
	.string "但请注意，\n"
	.string "你面对的任何训练家\l"
	.string "都不会有低于50级的宝可梦。\p"
	.string "这个课程是对战开拓区\n"
	.string "对战的入门级别。\p"
	.string "作为开始，\n"
	.string "我们希望你能挑战这个课程。$"

BattleFrontier_ReceptionGate_Text_OpenLevelInfo:
	.string "{CHN}自由级别课程对参加挑战的\n"
	.string "宝可梦等级\l"
	.string "没有限制。\p"
	.string "你的对手的宝可梦等级\n"
	.string "会根据你的宝可梦等级\l"
	.string "进行调整。\p"
	.string "但是，你面对的任何训练家\n"
	.string "都不会有低于60级的宝可梦。$"

BattleFrontier_ReceptionGate_Text_MonEntryInfo:
	.string "{CHN}几乎所有种类的宝可梦\n"
	.string "都可以参加各设施的挑战。\p"
	.string "但是，蛋和某些特定的宝可梦\n"
	.string "是不允许参加的。\p"
	.string "挑战所需的宝可梦数量\n"
	.string "因设施而异。\p"
	.string "不过，在所有设施中，\n"
	.string "都不允许携带两只以上\l"
	.string "相同种类的宝可梦。$"

BattleFrontier_ReceptionGate_Text_HoldItemsInfo:
	.string "{CHN}在对战开拓区设施参加挑战时，\n"
	.string "宝可梦不能\l"
	.string "携带相同的道具。\p"
	.string "请确保所有参加挑战的宝可梦\n"
	.string "都携带\l"
	.string "不同的道具。$"

BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass:
	.string "{CHN}我是开拓区通行证的引导员。$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhich1:
	.string "{CHN}你想了解哪个呢？$"

BattleFrontier_ReceptionGate_Text_SymbolsInfo:
	.string "{CHN}对战开拓区共有七座设施。\p"
	.string "凭借实力获得认可的训练家\n"
	.string "可能会从各设施\l"
	.string "获得象征。\p"
	.string "要获得象征，训练家可能需要\n"
	.string "连续击败其他训练家，\l"
	.string "并可能需要反复赢得项目。\p"
	.string "获得象征绝非易事。\n"
	.string "祝你好运！$"

BattleFrontier_ReceptionGate_Text_RecordedBattleInfo:
	.string "{CHN}你可以在开拓区通行证上\n"
	.string "记录一场对战。\p"
	.string "你可以记录与朋友\n"
	.string "进行的对战。\p"
	.string "或者你可以记录在对战开拓区\n"
	.string "进行的对战，但不包括\l"
	.string "对战管道或\l"
	.string "对战金字塔的比赛。\p"
	.string "你可以在一场对战结束时\n"
	.string "选择记录这场比赛。$"

BattleFrontier_ReceptionGate_Text_BattlePointsInfo:
	.string "{CHN}对战点数是给予在对战开拓区\n"
	.string "表现出色的\l"
	.string "训练家的奖励。\p"
	.string "你可以在兑换服务柜台\n"
	.string "用对战点数\l"
	.string "兑换奖品。$"

