MauvilleCity_House2_MapScripts::
	.byte 0

MauvilleCity_House2_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_COIN_CASE, MauvilleCity_House2_EventScript_ReceivedCoinCase
	msgbox MauvilleCity_House2_Text_BuyHarborMailAtSlateport, MSGBOX_DEFAULT
	checkitem ITEM_HARBOR_MAIL
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_House2_EventScript_AskToTradeForHarborMail
	release
	end

MauvilleCity_House2_EventScript_AskToTradeForHarborMail::
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox MauvilleCity_House2_Text_TradeHarborMailForCoinCase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_House2_EventScript_AcceptTrade
	goto_if_eq VAR_RESULT, NO, MauvilleCity_House2_EventScript_DeclineTrade
	end

MauvilleCity_House2_EventScript_AcceptTrade::
	msgbox MauvilleCity_House2_Text_IllTradeYouCoinCase, MSGBOX_DEFAULT
	removeitem ITEM_HARBOR_MAIL
	giveitem ITEM_COIN_CASE
	setflag FLAG_RECEIVED_COIN_CASE
	goto MauvilleCity_House2_EventScript_ReceivedCoinCase
	end

MauvilleCity_House2_EventScript_ReceivedCoinCase::
	msgbox MauvilleCity_House2_Text_UseCoinCaseAtGameCorner, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House2_EventScript_DeclineTrade::
	msgbox MauvilleCity_House2_Text_ThatsDisappointing, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House2_Text_BuyHarborMailAtSlateport:
	.string "{CHN}如果我有一辆自行车，骑车去\n"
	.string "凯那市购物就方便了。\p"
	.string "我就能在凯那市的\n"
	.string "宝可梦商店买到港湾邮件了……$"

MauvilleCity_House2_Text_TradeHarborMailForCoinCase:
	.string "{CHN}哦！你有港湾邮件？\n"
	.string "你愿意用它换一个代币盒吗？$"

MauvilleCity_House2_Text_IllTradeYouCoinCase:
	.string "{CHN}哦，我太高兴了！\n"
	.string "好，我跟你换一个代币盒！$"

MauvilleCity_House2_Text_UseCoinCaseAtGameCorner:
	.string "{CHN}那个代币盒可以在\n"
	.string "游戏中心使用。$"

MauvilleCity_House2_Text_ThatsDisappointing:
	.string "{CHN}哦，真让人失望。\p"
	.string "游戏中心需要\n"
	.string "一个代币盒。$"
