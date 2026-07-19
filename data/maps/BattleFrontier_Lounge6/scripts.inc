BattleFrontier_Lounge6_MapScripts::
	.byte 0

BattleFrontier_Lounge6_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_BATTLE_FRONTIER_TRADE_DONE, BattleFrontier_Lounge6_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_MEOWTH
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox BattleFrontier_Lounge6_Text_WouldYouLikeToTrade, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge6_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge6_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, BattleFrontier_Lounge6_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox BattleFrontier_Lounge6_Text_PromiseIllBeGoodToIt, MSGBOX_DEFAULT
	setflag FLAG_BATTLE_FRONTIER_TRADE_DONE
	release
	end

BattleFrontier_Lounge6_EventScript_DeclineTrade::
	msgbox BattleFrontier_Lounge6_Text_WellThatsFineToo, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_TradeCompleted::
	msgbox BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_Text_WouldYouLikeToTrade:
	.string "{CHN}我的宝可梦是{STR_VAR_2}。\n"
	.string "你知道吗？\l"
	.string "它又可爱又乖巧。\p"
	.string "这只小家伙，我可以\n"
	.string "自豪地拿来交换！\p"
	.string "你想用{STR_VAR_1}\n"
	.string "换我的{STR_VAR_2}吗？$"

BattleFrontier_Lounge6_Text_PromiseIllBeGoodToIt:
	.string "{CHN}哦，太可爱了！\n"
	.string "谢谢你！\l"
	.string "我保证会好好待它的！\p"
	.string "哦！希望你也好好\n"
	.string "对待我的{STR_VAR_2}哦！$"

BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon:
	.string "{CHN}哦，对不起！\n"
	.string "除了{STR_VAR_1}以外，\l"
	.string "我不想交换其他宝可梦。$"

BattleFrontier_Lounge6_Text_WellThatsFineToo:
	.string "{CHN}哦，你不愿意吗？\n"
	.string "那也没关系。\l"
	.string "请再来看我们哦。$"

BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined:
	.string "{CHN}嘻嘻！\n"
	.string "向尾喵比我想象的\l"
	.string "还要可爱得多。我太开心了！$"
