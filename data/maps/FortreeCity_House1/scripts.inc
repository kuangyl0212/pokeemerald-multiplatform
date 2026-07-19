FortreeCity_House1_MapScripts::
	.byte 0

FortreeCity_House1_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_FORTREE_NPC_TRADE_COMPLETED, FortreeCity_House1_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_PLUSLE
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox FortreeCity_House1_Text_YouWillTradeWontYou, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FortreeCity_House1_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, FortreeCity_House1_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, FortreeCity_House1_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox FortreeCity_House1_Text_MonYouTakeCare, MSGBOX_DEFAULT
	setflag FLAG_FORTREE_NPC_TRADE_COMPLETED
	release
	end

FortreeCity_House1_EventScript_DeclineTrade::
	msgbox FortreeCity_House1_Text_YouWontTradeMe, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox FortreeCity_House1_Text_ThisIsntAMon, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_TradeCompleted::
	msgbox FortreeCity_House1_Text_GoingToMakeVolbeatStrong, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_ExpertF::
	msgbox FortreeCity_House1_Text_TradingMemoriesWithOthers, MSGBOX_NPC
	end

FortreeCity_House1_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox FortreeCity_House1_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House1_Text_YouWillTradeWontYou:
	.string "{CHN}哇啊啊啊！我需要它！\n"
	.string "我必须弄到一只{STR_VAR_1}！\l"
	.string "为了它我什么都愿意做！\p"
	.string "……呃……你听见了吗？\n"
	.string "我发自内心的呐喊？\p"
	.string "既然听见了，\n"
	.string "你就用{STR_VAR_1}换我的{STR_VAR_2}，\l"
	.string "好吗？$"

FortreeCity_House1_Text_MonYouTakeCare:
	.string "{CHN}哦，太棒了！\p"
	.string "{STR_VAR_1}，欢迎你！\n"
	.string "{STR_VAR_2}，你要好好的哦！$"

FortreeCity_House1_Text_ThisIsntAMon:
	.string "{CHN}呃，不，不是这个。\n"
	.string "那不是{STR_VAR_1}。$"

FortreeCity_House1_Text_YouWontTradeMe:
	.string "{CHN}不？你不和我交换吗？\n"
	.string "我都对你敞开心扉了？$"

FortreeCity_House1_Text_GoingToMakeVolbeatStrong:
	.string "{CHN}从现在开始，我要把\n"
	.string "电萤怪培养得超级强！\p"
	.string "希望你对正电拍拍也是一样！$"

FortreeCity_House1_Text_TradingMemoriesWithOthers:
	.string "{CHN}和别人交换宝可梦……\p"
	.string "那就好像在和别人\n"
	.string "交换自己的回忆一样。$"

FortreeCity_House1_Text_Zigzagoon:
	.string "{CHN}蛇纹熊：咕摩摩？$"
