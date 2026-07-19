PacifidlogTown_House3_MapScripts::
	.byte 0

PacifidlogTown_House3_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_PACIFIDLOG_NPC_TRADE_COMPLETED, PacifidlogTown_House3_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_HORSEA
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox PacifidlogTown_House3_Text_WillingToTradeIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PacifidlogTown_House3_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, PacifidlogTown_House3_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, PacifidlogTown_House3_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox PacifidlogTown_House3_Text_ItsSubtlyDifferentThankYou, MSGBOX_DEFAULT
	setflag FLAG_PACIFIDLOG_NPC_TRADE_COMPLETED
	release
	end

PacifidlogTown_House3_EventScript_DeclineTrade::
	msgbox PacifidlogTown_House3_Text_NotDesperateOrAnything, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox PacifidlogTown_House3_Text_WontAcceptAnyLessThanRealMon, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_TradeCompleted::
	msgbox PacifidlogTown_House3_Text_ReallyWantedToGetBagon, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_Girl::
	msgbox PacifidlogTown_House3_Text_IsThatAPokedex, MSGBOX_NPC
	end

PacifidlogTown_House3_Text_WillingToTradeIt:
	.string "{CHN}看看这只{STR_VAR_2}！\p"
	.string "这是我昨天为了庆祝生日\n"
	.string "抓到的{STR_VAR_2}！\p"
	.string "哦，我看得出你想要它！\n"
	.string "毕竟，它是无价之宝！\p"
	.string "这样吧，我也许愿意\n"
	.string "用它换一只{STR_VAR_1}。$"

PacifidlogTown_House3_Text_ItsSubtlyDifferentThankYou:
	.string "{CHN}哦，这就是{STR_VAR_1}？\p"
	.string "它有点像{STR_VAR_2}，\n"
	.string "但又有些微妙的不同。\p"
	.string "谢谢你！$"

PacifidlogTown_House3_Text_WontAcceptAnyLessThanRealMon:
	.string "{CHN}不，不，不！我只接受\n"
	.string "真正的{STR_VAR_1}！$"

PacifidlogTown_House3_Text_NotDesperateOrAnything:
	.string "{CHN}哦，你不想\n"
	.string "交易了吗？\p"
	.string "没关系。我也不是\n"
	.string "非交易不可。$"

PacifidlogTown_House3_Text_ReallyWantedToGetBagon:
	.string "{CHN}我知道我可以自己去\n"
	.string "找一只，但是……\p"
	.string "但我真的很想要一只\n"
	.string "其他训练家抓到的甲壳龙……$"

PacifidlogTown_House3_Text_IsThatAPokedex:
	.string "{CHN}那是宝可梦图鉴吗？\p"
	.string "你遇到了很多不同的\n"
	.string "宝可梦吗？\p"
	.string "我真想像你一样。$"
