MauvilleCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MauvilleCity_OnTransition
	.byte 0

MauvilleCity_OnTransition:
	setflag FLAG_VISITED_MAUVILLE_CITY
	clearflag FLAG_FORCE_MIRAGE_TOWER_VISIBLE
	clearflag FLAG_HIDE_SLATEPORT_MUSEUM_POPULATION
	setflag FLAG_SYS_TV_START
	clearflag FLAG_MAUVILLE_GYM_BARRIERS_STATE
	setvar VAR_MAUVILLE_GYM_STATE, 0
	call_if_set FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON, MauvilleCity_EventScript_MoveWattsonBackToGym
	end

MauvilleCity_EventScript_MoveWattsonBackToGym::
	clearflag FLAG_HIDE_MAUVILLE_GYM_WATTSON
	setflag FLAG_HIDE_MAUVILLE_CITY_WATTSON
	setflag FLAG_WATTSON_REMATCH_AVAILABLE
	return

MauvilleCity_EventScript_Boy::
	msgbox MauvilleCity_Text_NurseHurtMonBackToHealth, MSGBOX_NPC
	end

MauvilleCity_EventScript_Maniac::
	msgbox MauvilleCity_Text_AllSortsOfPeopleComeThrough, MSGBOX_NPC
	end

MauvilleCity_EventScript_Woman::
	msgbox MauvilleCity_Text_RydelVeryGenerous, MSGBOX_NPC
	end

MauvilleCity_EventScript_RichBoy::
	msgbox MauvilleCity_Text_PokemonCanJumpYouOnBike, MSGBOX_NPC
	end

MauvilleCity_EventScript_CitySign::
	msgbox MauvilleCity_Text_CitySign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GymSign::
	msgbox MauvilleCity_Text_GymSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_BikeShopSign::
	msgbox MauvilleCity_Text_BikeShopSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GameCornerSign::
	msgbox MauvilleCity_Text_GameCornerSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_SchoolKidM::
	lock
	faceplayer
	goto_if_set FLAG_TV_EXPLAINED, MauvilleCity_EventScript_TVExplained
	msgbox MauvilleCity_Text_ExplainTV, MSGBOX_DEFAULT
	setflag FLAG_TV_EXPLAINED
	release
	end

MauvilleCity_EventScript_TVExplained::
	msgbox MauvilleCity_Text_BeenCheckingOutTV, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallysUncle::
	lock
	faceplayer
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_UncleAskPlayerToBattleWally
	msgbox MauvilleCity_Text_UncleHesTooPeppy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_UncleAskPlayerToBattleWally::
	msgbox MauvilleCity_Text_UncleCanYouBattleWally, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_Wally::
	lockall
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_WallyRequestBattleAgain
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWantToChallengeGym, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_UncleYourePushingIt, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_WallyWeCanBeatAnyone, MSGBOX_DEFAULT
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_Delay48
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWillYouBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_EventScript_BattleWallyPrompt::
	call_if_eq VAR_RESULT, YES, MauvilleCity_EventScript_BattleWally
	goto_if_eq VAR_RESULT, NO, MauvilleCity_EventScript_DeclineWallyBattle
	closemessage
	switch VAR_FACING
	case DIR_NORTH, MauvilleCity_EventScript_WallyAndUncleExitNorth
	case DIR_EAST, MauvilleCity_EventScript_WallyAndUncleExitEast
	end

MauvilleCity_EventScript_WallyAndUncleExitNorth::
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitNorth1
	applymovement LOCALID_MAUVILLE_WALLY, MauvilleCity_Movement_WallyExitNorth1
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitNorth1
	waitmovement 0
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerFaceUncleNorth
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleApproachPlayerNorth
	waitmovement 0
	msgbox MauvilleCity_Text_UncleVisitUsSometime, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitNorth2
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitNorth2
	applymovement LOCALID_MAUVILLE_WALLY, MauvilleCity_Movement_WallyExitNorth2
	waitmovement 0
	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_WallyAndUncleExitEast::
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitEast1
	applymovement LOCALID_MAUVILLE_WALLY, MauvilleCity_Movement_WallyExitEast1
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitEast1
	waitmovement 0
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleApproachPlayerEast
	waitmovement 0
	msgbox MauvilleCity_Text_UncleVisitUsSometime, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitEast2
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitEast2
	applymovement LOCALID_MAUVILLE_WALLY, MauvilleCity_Movement_WallyExitEast2
	waitmovement 0
	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_DefeatedWally::
	removeobject LOCALID_MAUVILLE_WALLY
	removeobject LOCALID_MAUVILLE_WALLYS_UNCLE
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLYS_UNCLE
	setflag FLAG_DEFEATED_WALLY_MAUVILLE
	setvar VAR_WALLY_CALL_STEP_COUNTER, 0
	setflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	call_if_eq VAR_FACING, DIR_NORTH, MauvilleCity_EventScript_ScottApproachPlayerNorth
	call_if_eq VAR_FACING, DIR_EAST, MauvilleCity_EventScript_ScottApproachPlayerEast
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox MauvilleCity_Text_ScottYouDidntHoldBack, MSGBOX_DEFAULT
	closemessage
	addvar VAR_SCOTT_STATE, 1
	call_if_eq VAR_FACING, DIR_NORTH, MauvilleCity_EventScript_ScottExitNorth
	call_if_eq VAR_FACING, DIR_EAST, MauvilleCity_EventScript_ScottExitEast
	removeobject LOCALID_MAUVILLE_SCOTT
	releaseall
	end

MauvilleCity_EventScript_ScottApproachPlayerNorth::
	addobject LOCALID_MAUVILLE_SCOTT
	applymovement LOCALID_MAUVILLE_SCOTT, MauvilleCity_Movement_ScottApproachPlayerNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottApproachPlayerEast::
	setobjectxyperm LOCALID_MAUVILLE_SCOTT, 12, 13
	addobject LOCALID_MAUVILLE_SCOTT
	applymovement LOCALID_MAUVILLE_SCOTT, MauvilleCity_Movement_ScottApproachPlayerEast
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitNorth::
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitNorth
	applymovement LOCALID_MAUVILLE_SCOTT, MauvilleCity_Movement_ScottExitNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitEast::
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitEast
	applymovement LOCALID_MAUVILLE_SCOTT, MauvilleCity_Movement_ScottExitEast
	waitmovement 0
	return

MauvilleCity_EventScript_BattleWally::
	msgbox MauvilleCity_Text_WallyHereICome, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_MAUVILLE, MauvilleCity_Text_WallyDefeat
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyIllGoBackToVerdanturf, MSGBOX_DEFAULT
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_ThankYouNotEnoughToBattle, MSGBOX_DEFAULT
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_UncleNoNeedToBeDown, MSGBOX_DEFAULT
	return

MauvilleCity_EventScript_DeclineWallyBattle::
	setflag FLAG_DECLINED_WALLY_BATTLE_MAUVILLE
	msgbox MauvilleCity_Text_WallyMyUncleWontKnowImStrong, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallyRequestBattleAgain::
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_WallyPleaseBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_Movement_WallyExitNorth1:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	step_end

MauvilleCity_Movement_WallyExitEast1:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallyExitNorth2:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_WallyExitEast2:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth2:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast2:
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchScottExitNorth:
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchScottExitEast:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast1:
	delay_16
	walk_in_place_faster_down
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth1:
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_WallysUncleExitNorth1:
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

MauvilleCity_Movement_WallysUncleExitEast1:
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_PlayerFaceUncleNorth:
	delay_16
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerNorth:
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerEast:
	walk_right
	walk_up
	step_end

MauvilleCity_Movement_WallysUncleExitNorth2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallysUncleExitEast2:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_ScottApproachPlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

MauvilleCity_Movement_ScottApproachPlayerEast:
	walk_up
	walk_up
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

MauvilleCity_Movement_ScottExitNorth:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_ScottExitEast:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_EventScript_Wattson::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON, MauvilleCity_EventScript_ReceivedThunderbolt
	goto_if_eq VAR_NEW_MAUVILLE_STATE, 2, MauvilleCity_EventScript_CompletedNewMauville
	goto_if_set FLAG_GOT_BASEMENT_KEY_FROM_WATTSON, MauvilleCity_EventScript_BegunNewMauville
	msgbox MauvilleCity_Text_WattsonNeedFavorTakeKey, MSGBOX_DEFAULT
	giveitem ITEM_BASEMENT_KEY
	setflag FLAG_GOT_BASEMENT_KEY_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_BegunNewMauville::
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_CompletedNewMauville::
	msgbox MauvilleCity_Text_WattsonThanksTakeTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_THUNDERBOLT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_ReceivedThunderbolt::
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_RegisterWallyCall::
	lockall
	pokenavcall MauvilleCity_Text_WallyPokenavCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MauvilleCity_Text_RegisteredWally, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WALLY_MATCH_CALL
	clearflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	releaseall
	end

MauvilleCity_Text_UncleHesTooPeppy:
	.string "{CHN}叔叔：是因为宝可梦\n"
	.string "这孩子才这么有精神吧……\l"
	.string "不过他有点精神过头了……$"

MauvilleCity_Text_WallyWantToChallengeGym:
	.string "{CHN}小光：哎呀，叔叔，求你了\p"
	.string "我想挑战这个道馆，看看\n"
	.string "自己变强了多少。\p"
	.string "求你了？可以吗，求你了？$"

MauvilleCity_Text_UncleYourePushingIt:
	.string "{CHN}叔叔：等等，小光。\p"
	.string "自从你开始和宝可梦一起生活，\n"
	.string "你确实变强了不少。\p"
	.string "但是你不觉得突然去挑战道馆\n"
	.string "有点勉强吗？$"

MauvilleCity_Text_WallyWeCanBeatAnyone:
	.string "{CHN}小光：我没有勉强。\p"
	.string "如果我和拉鲁拉丝齐心协力，\n"
	.string "我们就能战胜任何人！$"

MauvilleCity_Text_WallyWillYouBattleMe:
	.string "{CHN}小光：哦！嗨，{PLAYER}！\p"
	.string "自从我们上次见面以来，\n"
	.string "我变强了很多。\p"
	.string "{PLAYER}，我希望你和我叔叔\n"
	.string "都能明白这一点。\p"
	.string "{PLAYER}，求你了，\n"
	.string "和我对战一场好吗？$"

MauvilleCity_Text_WallyMyUncleWontKnowImStrong:
	.string "{CHN}小光：哦……如果你不对战的话，\n"
	.string "{PLAYER}，我叔叔就不会知道\l"
	.string "我已经变得很强了。$"

MauvilleCity_Text_UncleCanYouBattleWally:
	.string "{CHN}叔叔：{PLAYER}{KUN}，是吧？\n"
	.string "替小光，我能不能请你\l"
	.string "和他对战一次？\p"
	.string "他现在这个样子，\n"
	.string "恐怕听不进任何道理。$"

MauvilleCity_Text_WallyPleaseBattleMe:
	.string "{CHN}小光：{PLAYER}，求你了！\n"
	.string "请和我对战吧。$"

MauvilleCity_Text_WallyHereICome:
	.string "{CHN}小光：{PLAYER}，谢谢你。\p"
	.string "好……我来了！$"

MauvilleCity_Text_WallyDefeat:
	.string "{CHN}小光：…………………\p"
	.string "…………………\p"
	.string "我输了……$"

MauvilleCity_Text_WallyIllGoBackToVerdanturf:
	.string "{CHN}小光：叔叔……\n"
	.string "我回橙华市去……$"

MauvilleCity_Text_ThankYouNotEnoughToBattle:
	.string "{CHN}{PLAYER}，谢谢你。\n"
	.string "做训练家真不容易啊，对吧？\p"
	.string "光是有宝可梦\n"
	.string "并让它们战斗是不够的。\l"
	.string "那不是真正的训练家的做法。$"

MauvilleCity_Text_UncleNoNeedToBeDown:
	.string "{CHN}叔叔：小光，没必要\n"
	.string "这么沮丧。\p"
	.string "哎呀，有什么能阻止你\n"
	.string "变得越来越强呢？\p"
	.string "好了，我们回家吧。\n"
	.string "大家都在等你呢。$"

MauvilleCity_Text_UncleVisitUsSometime:
	.string "{CHN}叔叔：{PLAYER}{KUN}，我刚想起来，\n"
	.string "你一定就是那个在小光抓\l"
	.string "宝可梦时\l"
	.string "照顾他的训练家吧。\p"
	.string "你什么时候来橙华市\n"
	.string "找我们玩吧？\l"
	.string "小光一定会很高兴的。$"


MauvilleCity_Text_WallyPokenavCall:
	.string "{CHN}………………\n"
	.string "………嘟！\p"
	.string "小光：哦，你好，{PLAYER}！\p"
	.string "我就是想告诉你，\n"
	.string "叔叔给我买了宝可梦领航员！\p"
	.string "现在我可以随时\n"
	.string "联系你了，{PLAYER}！\p"
	.string "………………\n"
	.string "………咔嗒！$"

MauvilleCity_Text_RegisteredWally:
	.string "{CHN}已将小光\n"
	.string "登录到宝可梦领航员中。$"

MauvilleCity_Text_ScottYouDidntHoldBack:
	.string "{CHN}斯科特：嘿嘿……\n"
	.string "我看了那场比赛！\p"
	.string "你是那个男孩小光的朋友，\n"
	.string "对吧？\p"
	.string "但是你没有手下留情，\n"
	.string "漂亮地击败了他。\p"
	.string "没错！这才是真正的宝可梦\n"
	.string "对战啊！\p"
	.string "我最崇拜那样的训练家了！\p"
	.string "………………\n"
	.string "我会为你加油的！$"

MauvilleCity_Text_WattsonNeedFavorTakeKey:
	.string "{CHN}铁旋：哦，{PLAYER}{KUN}！\n"
	.string "你看起来真有活力！\l"
	.string "这是好事，哇哈哈哈哈！\p"
	.string "好！我决定了！\n"
	.string "{PLAYER}{KUN}，我要请你帮个忙！\p"
	.string "紫堇市有一个地下区域，\n"
	.string "叫做新紫堇。\p"
	.string "{PLAYER}{KUN}，我希望你去那里\n"
	.string "关掉发电机。\p"
	.string "那台发电机最近\n"
	.string "有点失控。变得不安全了。\p"
	.string "给，这是进入\n"
	.string "新紫堇的钥匙。$"

MauvilleCity_Text_WattsonWontBeChallenge:
	.string "{CHN}铁旋：不用担心。\n"
	.string "这对你来说不算什么挑战。\p"
	.string "新紫堇的入口就在\n"
	.string "110号水路上，冲浪过去不远。\p"
	.string "那就这样，我相信你了！\n"
	.string "哇哈哈哈哈！$"

MauvilleCity_Text_WattsonThanksTakeTM:
	.string "{CHN}铁旋：哇哈哈哈哈！\p"
	.string "我就知道，{PLAYER}{KUN}！\n"
	.string "我就知道找你是正确的！\p"
	.string "这是我的谢礼——一个装有\n"
	.string "十万伏特的招式学习器！\p"
	.string "拿着吧，这是你应得的！$"

MauvilleCity_Text_WattsonYoungTakeCharge:
	.string "{CHN}铁旋：哇哈哈哈哈！\p"
	.string "看到年轻人\n"
	.string "挺身而出承担责任，真是太让我高兴了！$"

MauvilleCity_Text_NurseHurtMonBackToHealth:
	.string "{CHN}你知道吗，搞宝可梦对战\n"
	.string "之类的挺酷的……\p"
	.string "但是如果你的宝可梦受伤了，\n"
	.string "你就要把它治疗康复。$"

MauvilleCity_Text_AllSortsOfPeopleComeThrough:
	.string "{CHN}这个城镇的道路向北\n"
	.string "和向南，向东和向西延伸。\p"
	.string "正因如此，我们有各种各样的人\n"
	.string "从这里经过。$"

MauvilleCity_Text_RydelVeryGenerous:
	.string "{CHN}你去过利川自行车店了吗？\p"
	.string "利川，那位老板，是一个非常大方\n"
	.string "的人。$"

MauvilleCity_Text_PokemonCanJumpYouOnBike:
	.string "{CHN}即使你骑着自行车，\n"
	.string "野生宝可梦也可能会扑向你。$"

MauvilleCity_Text_CitySign:
	.string "{CHN}紫堇市\n"
	.string "“明亮闪耀的欢乐之城！”$"

MauvilleCity_Text_GymSign:
	.string "{CHN}紫堇市宝可梦道馆\n"
	.string "馆主：铁旋\l"
	.string "“开朗令人触电的男人！”$"

MauvilleCity_Text_BikeShopSign:
	.string "{CHN}“在碎石路上骑行，\n"
	.string "震撼你的灵魂！”\l"
	.string "利川自行车店$"

MauvilleCity_Text_GameCornerSign:
	.string "{CHN}“大家的游乐天地！”\n"
	.string "紫堇游戏中心$"

MauvilleCity_Text_ExplainTV:
	.string "{CHN}嗨，你看电视吗？\p"
	.string "他们最近加了很多\n"
	.string "有趣的新节目。\p"
	.string "电视真是太棒了。我曾在电视上\n"
	.string "突然看到我的朋友们。\p"
	.string "而且，有时候他们甚至不告诉你就把\n"
	.string "你放到电视上。\p"
	.string "我希望有一天我也能上电视。\p"
	.string "所以我觉得你应该尽可能\n"
	.string "多看看电视。$"

MauvilleCity_Text_BeenCheckingOutTV:
	.string "{CHN}嗨，你一直在看电视吗？$"
