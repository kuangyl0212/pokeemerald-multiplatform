RustboroCity_House1_MapScripts::
	.byte 0

RustboroCity_House1_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_RUSTBORO_NPC_TRADE_COMPLETED, RustboroCity_House1_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_SEEDOT
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox RustboroCity_House1_Text_IllTradeIfYouWant, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_House1_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, RustboroCity_House1_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, RustboroCity_House1_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox RustboroCity_House1_Text_PleaseBeGoodToMyPokemon, MSGBOX_DEFAULT
	setflag FLAG_RUSTBORO_NPC_TRADE_COMPLETED
	release
	end

RustboroCity_House1_EventScript_DeclineTrade::
	msgbox RustboroCity_House1_Text_YouDontWantToThatsOkay, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox RustboroCity_House1_Text_DoesntLookLikeMonToMe, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_TradeCompleted::
	msgbox RustboroCity_House1_Text_AnyPokemonCanBeCute, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_Hiker::
	msgbox RustboroCity_House1_Text_AllSortsOfPlaces, MSGBOX_NPC
	end

RustboroCity_House1_Text_IllTradeIfYouWant:
	.string "{CHN}咦？我的宝可梦很可爱？\n"
	.string "当然，这我知道.\p"
	.string "但如果你真的想要，我愿意\n"
	.string "和你交换它.\p"
	.string "如果你想要的话，我就用我的{STR_VAR_2}\n"
	.string "和你换一只{STR_VAR_1}.$"

RustboroCity_House1_Text_PleaseBeGoodToMyPokemon:
	.string "{CHN}嘿嘿…\n"
	.string "请好好对待我的宝可梦.$"

RustboroCity_House1_Text_DoesntLookLikeMonToMe:
	.string "{CHN}咦？那看起来完全不像\n"
	.string "{STR_VAR_1}啊.$"

RustboroCity_House1_Text_YouDontWantToThatsOkay:
	.string "{CHN}哦，如果你不想换，那也没关系.\n"
	.string "不过我的宝可梦很可爱的，你知道…$"

RustboroCity_House1_Text_AnyPokemonCanBeCute:
	.string "{CHN}任何宝可梦只要用心和\n"
	.string "善意来培育，都会变得可爱.$"

RustboroCity_House1_Text_AllSortsOfPlaces:
	.string "{CHN}在各种地方，都有各种\n"
	.string "宝可梦和人在.\p"
	.string "我觉得这很有趣，所以我去了\n"
	.string "各种地方.$"

