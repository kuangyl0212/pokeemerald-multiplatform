Roulette_EventScript_Table1::
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 0
	getpokenewsactive POKENEWS_GAME_CORNER
	goto_if_eq VAR_RESULT, FALSE, Roulette_EventScript_Play
	addvar VAR_0x8004, ROULETTE_SPECIAL_RATE
	goto Roulette_EventScript_Play
	end

Roulette_EventScript_Table2::
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 1
	getpokenewsactive POKENEWS_GAME_CORNER
	goto_if_eq VAR_RESULT, FALSE, Roulette_EventScript_Play
	addvar VAR_0x8004, ROULETTE_SPECIAL_RATE
	goto Roulette_EventScript_Play
	end

Roulette_EventScript_Play::
	special PlayRoulette
	waitstate
	end

Roulette_Text_PlayMinimumWagerIsX::
	.string "{CHN}这个桌台的最低下注额\n"
	.string "是{STR_VAR_1}。你要玩吗？$"

Roulette_Text_NotEnoughCoins::
	.string "{CHN}你的代币不够。$"

Roulette_Text_SpecialRateTable::
	.string "{CHN}现在是特别赔率桌台！$"

Roulette_Text_ControlsInstruction::
	.string "{CHN}用+方向键\n"
	.string "下注，然后按A键。$"

Roulette_Text_ItsAHit::
	.string "{CHN}中了！$"

Roulette_Text_Jackpot::
	.string "{CHN}头奖！$"

Roulette_Text_NothingDoing::
	.string "{CHN}没中！$"

Roulette_Text_YouveWonXCoins::
	.string "{CHN}你赢得了{STR_VAR_1}枚代币！$"

Roulette_Text_NoCoinsLeft::
	.string "{CHN}没有代币了……$"

Roulette_Text_KeepPlaying::
	.string "{CHN}继续玩吗？$"

Roulette_Text_BoardWillBeCleared::
	.string "{CHN}轮盘盘面将被清空。$"

/* Unused*/
Roulette_Text_YouDontHaveACoinCase::
	.string "{CHN}你没有代币盒。$"

Roulette_Text_CoinCaseIsFull::
	.string "{CHN}你的代币盒满了！\n"
	.string "代币可以兑换奖品。$"
