MtPyre_1F_MapScripts::
	.byte 0

MtPyre_1F_EventScript_CleanseTagWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CLEANSE_TAG, MtPyre_1F_EventScript_ReceivedCleanseTag
	msgbox MtPyre_1F_Text_TakeThisForYourOwnGood, MSGBOX_DEFAULT
	giveitem ITEM_CLEANSE_TAG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CLEANSE_TAG
	release
	end

MtPyre_1F_EventScript_ReceivedCleanseTag::
	msgbox MtPyre_1F_Text_ExplainCleanseTag, MSGBOX_DEFAULT
	release
	end

MtPyre_1F_EventScript_PokefanF::
	msgbox MtPyre_1F_Text_ComeToPayRespects, MSGBOX_NPC
	end

MtPyre_1F_EventScript_Man::
	msgbox MtPyre_1F_Text_RestingPlaceOfZigzagoon, MSGBOX_NPC
	end

MtPyre_1F_Text_TakeThisForYourOwnGood:
	.string "{CHN}送神山的山坡上\n"
	.string "游荡着各种各样的生物……\p"
	.string "不知道会发生什么事。\n"
	.string "拿着这个。这是为你好。$"

MtPyre_1F_Text_ExplainCleanseTag:
	.string "{CHN}让宝可梦带着那个\n"
	.string "净符吧。\p"
	.string "它可以帮助驱赶野生宝可梦。$"

MtPyre_1F_Text_ComeToPayRespects:
	.string "{CHN}你是来向逝去的宝可梦\n"
	.string "的灵魂致敬的吗？\p"
	.string "你一定很关心你的宝可梦。$"

MtPyre_1F_Text_RestingPlaceOfZigzagoon:
	.string "{CHN}这是我深爱的蛇纹熊\n"
	.string "最终的安息之地。我曾那么珍惜它……$"

