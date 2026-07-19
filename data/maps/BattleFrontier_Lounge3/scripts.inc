BattleFrontier_Lounge3_MapScripts::
	.byte 0

	.set BET_AMOUNT_5,  5
	.set BET_AMOUNT_10, 10
	.set BET_AMOUNT_15, 15

BattleFrontier_Lounge3_EventScript_Gambler::
	lock
	faceplayer
	goto_if_set FLAG_MET_BATTLE_FRONTIER_GAMBLER, BattleFrontier_Lounge3_EventScript_AlreadyMetGambler
	call BattleFrontier_Lounge3_EventScript_CountSilverSymbols
	goto_if_le VAR_0x8004, 2, BattleFrontier_Lounge3_EventScript_NotEnoughSilverSymbols
	setflag FLAG_MET_BATTLE_FRONTIER_GAMBLER
	msgbox BattleFrontier_Lounge3_Text_YouLookToughExplainGambling, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_AskToEnterChallenge
	end

BattleFrontier_Lounge3_EventScript_AskToEnterChallenge::
	special ShowFrontierGamblerLookingMessage
	waitmessage
	waitbuttonpress
	msgbox BattleFrontier_Lounge3_Text_HowAboutEnteringEventForMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge3_EventScript_DeclineChallenge
	msgbox BattleFrontier_Lounge3_Text_SpotMeSomeBattlePoints, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge3_EventScript_DeclineChallenge
	message BattleFrontier_Lounge3_Text_HowMuchCanYouSpot
	waitmessage
	special ShowBattlePointsWindow
	goto BattleFrontier_Lounge3_EventScript_ChooseBetAmount
	end

BattleFrontier_Lounge3_EventScript_ChooseBetAmount::
	multichoice 20, 4, MULTI_FRONTIER_GAMBLER_BET, FALSE
	copyvar VAR_FRONTIER_GAMBLER_AMOUNT_BET, VAR_RESULT
	switch VAR_RESULT
	case FRONTIER_GAMBLER_BET_5, BattleFrontier_Lounge3_EventScript_Bet5
	case FRONTIER_GAMBLER_BET_10, BattleFrontier_Lounge3_EventScript_Bet10
	case FRONTIER_GAMBLER_BET_15, BattleFrontier_Lounge3_EventScript_Bet15
	case FRONTIER_GAMBLER_BET_CANCEL, BattleFrontier_Lounge3_EventScript_CancelBet
	case MULTI_B_PRESSED, BattleFrontier_Lounge3_EventScript_CancelBet
	end

BattleFrontier_Lounge3_EventScript_Bet5::
	setvar VAR_0x8008, BET_AMOUNT_5
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_Bet10::
	setvar VAR_0x8008, BET_AMOUNT_10
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_Bet15::
	setvar VAR_0x8008, BET_AMOUNT_15
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_TryPlaceBet::
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	goto_if_ge VAR_TEMP_1, VAR_0x8008, BattleFrontier_Lounge3_EventScript_PlaceBet
	msgbox BattleFrontier_Lounge3_Text_YouDontHaveEnoughPoints, MSGBOX_DEFAULT
	message BattleFrontier_Lounge3_Text_HowMuchCanYouSpot
	waitmessage
	goto BattleFrontier_Lounge3_EventScript_ChooseBetAmount
	end

BattleFrontier_Lounge3_EventScript_PlaceBet::
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET
	special UpdateBattlePointsWindow
	playse SE_SHOP
	msgbox BattleFrontier_Lounge3_Text_ThanksOffYouGo, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FinishBet
	end

BattleFrontier_Lounge3_EventScript_FinishBet::
	special ShowFrontierGamblerGoMessage
	waitmessage
	waitbuttonpress
	special CloseBattlePointsWindow
	release
	end

BattleFrontier_Lounge3_EventScript_CountSilverSymbols::
	setvar VAR_0x8004, 0
	call_if_set FLAG_SYS_TOWER_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_DOME_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PALACE_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_ARENA_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_FACTORY_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PIKE_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PYRAMID_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	return

BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount::
	addvar VAR_0x8004, 1
	return

BattleFrontier_Lounge3_EventScript_NotEnoughSilverSymbols::
	msgbox BattleFrontier_Lounge3_Text_CantYouSeeWereBusyHere, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_AlreadyMetGambler::
	msgbox BattleFrontier_Lounge3_Text_Oh, MSGBOX_DEFAULT
	goto_if_ge VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET, BattleFrontier_Lounge3_EventScript_CheckBetResults
	goto BattleFrontier_Lounge3_EventScript_AskToEnterChallenge
	end

BattleFrontier_Lounge3_EventScript_CheckBetResults::
	goto_if_eq VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET, BattleFrontier_Lounge3_EventScript_ChallengeNotAttempted
	goto_if_eq VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WON, BattleFrontier_Lounge3_EventScript_WonChallenge
	goto BattleFrontier_Lounge3_EventScript_LostChallenge
	end

BattleFrontier_Lounge3_EventScript_WonChallenge::
	msgbox BattleFrontier_Lounge3_Text_HelloChampHeresYourPoints, MSGBOX_DEFAULT
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_5, BattleFrontier_Lounge3_EventScript_RewardBet5
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_10, BattleFrontier_Lounge3_EventScript_RewardBet10
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_15, BattleFrontier_Lounge3_EventScript_RewardBet15
	msgbox BattleFrontier_Lounge3_Text_ObtainedBattlePoints, MSGBOX_GETPOINTS
	special GiveFrontierBattlePoints
	msgbox BattleFrontier_Lounge3_Text_ThinkOfMeForAnotherChallenge, MSGBOX_DEFAULT
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WAITING
	release
	end

BattleFrontier_Lounge3_EventScript_LostChallenge::
	msgbox BattleFrontier_Lounge3_Text_NiceTryCantReturnPoints, MSGBOX_DEFAULT
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WAITING
	release
	end

BattleFrontier_Lounge3_EventScript_RewardBet5::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_5 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_5 * 2)
	return

BattleFrontier_Lounge3_EventScript_RewardBet10::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_10 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_10 * 2)
	return

BattleFrontier_Lounge3_EventScript_RewardBet15::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_15 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_15 * 2)
	return

BattleFrontier_Lounge3_EventScript_ChallengeNotAttempted::
	special ShowFrontierGamblerGoMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge3_EventScript_DeclineChallenge::
	msgbox BattleFrontier_Lounge3_Text_NotInterested, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge3_EventScript_CancelBet::
	special CloseBattlePointsWindow
	goto BattleFrontier_Lounge3_EventScript_DeclineChallenge
	end

BattleFrontier_Lounge3_EventScript_Man::
	msgbox BattleFrontier_Lounge3_Text_ShouldBeTakingChallenges, MSGBOX_NPC
	end

BattleFrontier_Lounge3_EventScript_Woman::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_BackedWrongTrainer, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_PokefanF::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_KnowWinnerWhenISeeOne, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_FatMan::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_TrainerGoodButRattled, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_FaceOriginalDirection::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleFrontier_Lounge3_Text_CantYouSeeWereBusyHere::
	.string "{CHN}……你有什么事？\p"
	.string "没看到我们正忙着吗？\n"
	.string "你的事不能等会儿再说吗？$"

BattleFrontier_Lounge3_Text_YouLookToughExplainGambling::
	.string "{CHN}……嗯？\n"
	.string "你看上去像个厉害的训练家。\p"
	.string "嘿嘿……\n"
	.string "听着，我有个提议。\p"
	.string "我们这里有个小团体，\n"
	.string "我们会就对战开拓区\l"
	.string "里发生的事情玩个小游戏。\p"
	.string "规则非常简单。\p"
	.string "首先，我们在对战开拓区\n"
	.string "的设施中选一个。\p"
	.string "然后，我们各自选一个\n"
	.string "正在挑战那个设施的训练家，\l"
	.string "用我们的对战点数下注。\p"
	.string "押在成绩最好的训练家身上的人\n"
	.string "就能赢走池子里所有的\l"
	.string "对战点数。\p"
	.string "听起来很简单吧？\n"
	.string "那么，话说回来……$"

BattleFrontier_Lounge3_Text_ChallengeBattleTowerSingle::
	.string "{CHN}我要找的是一个\n"
	.string "即将挑战对战\l"
	.string "塔单打对战房的训练家。\p"
	.string "但到目前为止，我还没看到\n"
	.string "有那种必胜气质的训练家。$"

BattleFrontier_Lounge3_Text_ChallengeBattleTowerDouble::
	.string "{CHN}我要找的是一个\n"
	.string "即将挑战对战\l"
	.string "塔双打对战房的训练家。\p"
	.string "但到目前为止，我还没看到\n"
	.string "有那种必胜气质的训练家。$"

BattleFrontier_Lounge3_Text_ChallengeBattleTowerMulti::
	.string "{CHN}我要找的是一个\n"
	.string "即将挑战对战\l"
	.string "塔多人对战房的训练家。\p"
	.string "但到目前为止，我还没看到\n"
	.string "有那种必胜气质的训练家。$"

BattleFrontier_Lounge3_Text_ChallengeBattleDomeSingle::
	.string "{CHN}我要找的是一个\n"
	.string "即将参加对战\l"
	.string "巨蛋单打锦标赛的训练家。\p"
	.string "但到目前为止，我还没看到\n"
	.string "有那种必胜气质的训练家。$"

BattleFrontier_Lounge3_Text_ChallengeBattleDomeDouble::
	.string "{CHN}我要找的是一个\n"
	.string "即将参加对战\l"
	.string "巨蛋双打锦标赛的训练家。\p"
	.string "但到目前为止，我还没看到\n"
	.string "有那种必胜气质的训练家。$"

BattleFrontier_Lounge3_Text_ChallengeBattleFactorySingle::
	.string "{CHN}我要找的是一个\n"
	.string "即将参加对战\l"
	.string "工厂单打交换锦标赛的训练家。\p"
	.string "但到目前为止，我还没看到\n"
	.string "有那种必胜气质的训练家。$"

BattleFrontier_Lounge3_Text_ChallengeBattleFactoryDouble::
	.string "{CHN}我要找的是一个\n"
	.string "即将参加对战\l"
	.string "工厂双打交换锦标赛的训练家。\p"
	.string "但到目前为止，我还没看到\n"
	.string "有那种必胜气质的训练家。$"

BattleFrontier_Lounge3_Text_ChallengeBattlePalaceSingle::
	.string "{CHN}我要找的是一个\n"
	.string "即将挑战对战\l"
	.string "宫殿单打对战厅的训练家。\p"
	.string "但到目前为止，我还没看到\n"
	.string "有那种必胜气质的训练家。$"

BattleFrontier_Lounge3_Text_ChallengeBattlePalaceDouble::
	.string "{CHN}我要找的是一个\n"
	.string "即将挑战对战\l"
	.string "宫殿双打对战厅的训练家。\p"
	.string "但到目前为止，我还没看到\n"
	.string "有那种必胜气质的训练家。$"

BattleFrontier_Lounge3_Text_ChallengeBattleArena::
	.string "{CHN}我要找的是一个\n"
	.string "即将参加对战\l"
	.string "竞技场连环淘汰赛的训练家。\p"
	.string "但到目前为止，我还没看到\n"
	.string "有那种必胜气质的训练家。$"

BattleFrontier_Lounge3_Text_ChallengeBattlePike::
	.string "{CHN}我要找的是一个\n"
	.string "即将参加对战管道\l"
	.string "对战选择的训练家。\p"
	.string "但到目前为止，我还没看到\n"
	.string "有那种必胜气质的训练家。$"

BattleFrontier_Lounge3_Text_ChallengeBattlePyramid::
	.string "{CHN}我要找的是一个\n"
	.string "即将参加对战\l"
	.string "金字塔对战探险的训练家。\p"
	.string "但到目前为止，我还没看到\n"
	.string "有那种必胜气质的训练家。$"

BattleFrontier_Lounge3_Text_HowAboutEnteringEventForMe::
	.string "{CHN}我会让你也受益的。\n"
	.string "那么怎么样？\l"
	.string "你替我参加那个项目如何？$"

BattleFrontier_Lounge3_Text_SpotMeSomeBattlePoints::
	.string "{CHN}好，太完美了。\n"
	.string "那么，呃……你能借我一些\l"
	.string "对战点数吗？\p"
	.string "相信我，事后我会\n"
	.string "好好感谢你的。$"

BattleFrontier_Lounge3_Text_HowMuchCanYouSpot::
	.string "{CHN}好，好！\n"
	.string "那么，你能借我多少？$"

BattleFrontier_Lounge3_Text_YouDontHaveEnoughPoints::
	.string "{CHN}哦，不，不，不！\n"
	.string "你的对战点数不够！\p"
	.string "希望你别再胡闹\n"
	.string "浪费大家的时间了！$"

BattleFrontier_Lounge3_Text_ThanksOffYouGo::
	.string "{CHN}嘿嘿！多谢了！\n"
	.string "那么，出发吧！$"

BattleFrontier_Lounge3_Text_GetToBattleTowerSingle::
	.string "{CHN}赶紧去对战塔的\n"
	.string "单打对战房！\p"
	.string "这是必须获胜的局面！\n"
	.string "别错失良机！\l"
	.string "我们两人的未来都靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattleTowerDouble::
	.string "{CHN}赶紧去对战塔的\n"
	.string "双打对战房！\p"
	.string "这是必须获胜的局面！\n"
	.string "别错失良机！\l"
	.string "我们两人的未来都靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattleTowerMulti::
	.string "{CHN}赶紧去对战塔的\n"
	.string "多人对战房！\p"
	.string "这是必须获胜的局面！\n"
	.string "别错失良机！\l"
	.string "我们两人的未来都靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattleDomeSingle::
	.string "{CHN}赶紧去对战巨蛋的\n"
	.string "单打锦标赛！\p"
	.string "这是必须获胜的局面！\n"
	.string "别错失良机！\l"
	.string "我们两人的未来都靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattleDomeDouble::
	.string "{CHN}赶紧去对战巨蛋的\n"
	.string "双打锦标赛！\p"
	.string "这是必须获胜的局面！\n"
	.string "别错失良机！\l"
	.string "我们两人的未来都靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattleFactorySingle::
	.string "{CHN}赶紧去对战工厂的\n"
	.string "单打交换锦标赛！\p"
	.string "这是必须获胜的局面！\n"
	.string "别错失良机！\l"
	.string "我们两人的未来都靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattleFactoryDouble::
	.string "{CHN}赶紧去对战工厂的\n"
	.string "双打交换锦标赛！\p"
	.string "这是必须获胜的局面！\n"
	.string "别错失良机！\l"
	.string "我们两人的未来都靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattlePalaceSingle::
	.string "{CHN}赶紧去对战宫殿的\n"
	.string "单打对战厅！\p"
	.string "这是必须获胜的局面！\n"
	.string "别错失良机！\l"
	.string "我们两人的未来都靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattlePalaceDouble::
	.string "{CHN}赶紧去对战宫殿的\n"
	.string "双打对战厅！\p"
	.string "这是必须获胜的局面！\n"
	.string "别错失良机！\l"
	.string "我们两人的未来都靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattleArena::
	.string "{CHN}赶紧去对战竞技场的\n"
	.string "连环淘汰赛！\p"
	.string "这是必须获胜的局面！\n"
	.string "别错失良机！\l"
	.string "我们两人的未来都靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattlePike::
	.string "{CHN}赶紧去对战管道的\n"
	.string "对战选择！\p"
	.string "这是必须获胜的局面！\n"
	.string "别错失良机！\l"
	.string "我们两人的未来都靠你了！$"

BattleFrontier_Lounge3_Text_GetToBattlePyramid::
	.string "{CHN}赶紧去对战金字塔的\n"
	.string "对战探险！\p"
	.string "这是必须获胜的局面！\n"
	.string "别错失良机！\l"
	.string "我们两人的未来都靠你了！$"

BattleFrontier_Lounge3_Text_NiceTryCantReturnPoints::
	.string "{CHN}哦，是你啊……\n"
	.string "不错的尝试……\p"
	.string "虽然不想告诉你，但我不能\n"
	.string "退还你的对战点数……\p"
	.string "我想这会激励我们\n"
	.string "下次更加努力！$"

BattleFrontier_Lounge3_Text_HelloChampHeresYourPoints::
	.string "{CHN}哦，好！\n"
	.string "你好啊，冠军！\p"
	.string "我就知道你能行！\n"
	.string "我就知道你会赢！\l"
	.string "我们都是大赢家！\p"
	.string "我会还你对战点数，\n"
	.string "当然，还有我的一点额外心意！$"

BattleFrontier_Lounge3_Text_ObtainedBattlePoints::
	.string "{CHN}{PLAYER}获得了\n"
	.string "{STR_VAR_1}个对战点数。$"

BattleFrontier_Lounge3_Text_ThinkOfMeForAnotherChallenge::
	.string "{CHN}如果你还想再挑战一次，\n"
	.string "请务必想到我！$"

BattleFrontier_Lounge3_Text_NotInterested::
	.string "{CHN}不感兴趣？！你不应该\n"
	.string "这么害怕冒险！$"

BattleFrontier_Lounge3_Text_Oh::
	.string "{CHN}哦……$"

BattleFrontier_Lounge3_Text_BackedWrongTrainer::
	.string "{CHN}我又押错训练家了！\p"
	.string "也许我应该像其他人一样\n"
	.string "正常对战……$"

BattleFrontier_Lounge3_Text_TrainerGoodButRattled::
	.string "{CHN}那个训练家……\p"
	.string "他不错，但他太容易慌张，\n"
	.string "无法在对战巨蛋中生存……$"

BattleFrontier_Lounge3_Text_KnowWinnerWhenISeeOne::
	.string "{CHN}嘻嘻！\n"
	.string "我一眼就能看出谁是赢家！$"

BattleFrontier_Lounge3_Text_ShouldBeTakingChallenges::
	.string "{CHN}那些训练家……\n"
	.string "他们在干什么？\l"
	.string "他们应该去参加挑战才对。$"
