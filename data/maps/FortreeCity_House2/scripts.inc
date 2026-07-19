FortreeCity_House2_MapScripts::
	.byte 0

FortreeCity_House2_EventScript_HiddenPowerGiver::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_HIDDEN_POWER, FortreeCity_House2_EventScript_ExplainHiddenPower
	call_if_unset FLAG_MET_HIDDEN_POWER_GIVER, FortreeCity_House2_EventScript_Greeting
	msgbox FortreeCity_House2_Text_CoinInWhichHand, MSGBOX_DEFAULT
	multichoice 21, 8, MULTI_RIGHTLEFT, TRUE
	switch VAR_RESULT
	case 1, FortreeCity_House2_EventScript_WrongGuess
	msgbox FortreeCity_House2_Text_CorrectTryAgainWhichHand, MSGBOX_DEFAULT
	multichoice 21, 8, MULTI_RIGHTLEFT, TRUE
	switch VAR_RESULT
	case 1, FortreeCity_House2_EventScript_WrongGuess
	msgbox FortreeCity_House2_Text_CorrectTryAgainWhichHand2, MSGBOX_DEFAULT
	multichoice 21, 8, MULTI_RIGHTLEFT, TRUE
	switch VAR_RESULT
	case 0, FortreeCity_House2_EventScript_WrongGuess
	msgbox FortreeCity_House2_Text_YourHiddenPowerHasAwoken, MSGBOX_DEFAULT
	giveitem ITEM_TM_HIDDEN_POWER
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_HIDDEN_POWER
	msgbox FortreeCity_House2_Text_ExplainHiddenPower, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_EventScript_Greeting::
	msgbox FortreeCity_House2_Text_HiddenPowersArousedByNature, MSGBOX_DEFAULT
	setflag FLAG_MET_HIDDEN_POWER_GIVER
	return

FortreeCity_House2_EventScript_ExplainHiddenPower::
	msgbox FortreeCity_House2_Text_ExplainHiddenPower, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_EventScript_WrongGuess::
	msgbox FortreeCity_House2_Text_YouGuessedWrong, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_Text_HiddenPowersArousedByNature:
	.string "{CHN}人类……宝可梦……\p"
	.string "他们的隐藏力量被\n"
	.string "自然环境所唤醒……$"

FortreeCity_House2_Text_CoinInWhichHand:
	.string "{CHN}让老婆婆我看看你的隐藏\n"
	.string "力量有没有觉醒……\p"
	.string "我手里握着一枚硬币。\p"
	.string "现在，告诉我，我把它\n"
	.string "握在右手了？还是左手？$"

FortreeCity_House2_Text_CorrectTryAgainWhichHand:
	.string "{CHN}哦！答对了！\p"
	.string "我们再来一次。\p"
	.string "我把硬币握在哪只手了？\n"
	.string "右手还是左手？$"

FortreeCity_House2_Text_CorrectTryAgainWhichHand2:
	.string "{CHN}哦！答对了！\p"
	.string "我们再来一次。\p"
	.string "我把硬币握在哪只手了？\n"
	.string "右手还是左手？$"

FortreeCity_House2_Text_YourHiddenPowerHasAwoken:
	.string "{CHN}哦！太棒了！\n"
	.string "你的隐藏力量觉醒了！\p"
	.string "来，拿着这个，\n"
	.string "唤醒你宝可梦的隐藏力量吧。$"

FortreeCity_House2_Text_ExplainHiddenPower:
	.string "{CHN}觉醒力量是\n"
	.string "根据宝可梦而变化的招式。$"

FortreeCity_House2_Text_YouGuessedWrong:
	.string "{CHN}不对，太可惜了。\n"
	.string "你猜错了。$"
