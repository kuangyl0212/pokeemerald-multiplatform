SlateportCity_NameRatersHouse_MapScripts::
	.byte 0

SlateportCity_NameRatersHouse_EventScript_NameRater::
	lock
	faceplayer
	msgbox SlateportCity_NameRatersHouse_Text_PleasedToRateMonNickname, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_NameRatersHouse_EventScript_ChooseMonToRate
	goto_if_eq VAR_RESULT, NO, SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_ChooseMonToRate::
	msgbox SlateportCity_NameRatersHouse_Text_CritiqueWhichMonNickname, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_ne VAR_0x8004, PARTY_NOTHING_CHOSEN, SlateportCity_NameRatersHouse_EventScript_RateMonNickname
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_DeclineNameRate::
	msgbox SlateportCity_NameRatersHouse_Text_DoVisitAgain, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_RateMonNickname::
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, SlateportCity_NameRatersHouse_EventScript_CantRateEgg
	special BufferMonNickname
	special IsMonOTIDNotPlayers
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	specialvar VAR_RESULT, MonOTNameNotPlayer
	special BufferMonNickname
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	msgbox SlateportCity_NameRatersHouse_Text_FineNameSuggestBetterOne, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_NameRatersHouse_EventScript_ChangeNickname
	goto_if_eq VAR_RESULT, NO, SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_CantRateEgg::
	msgbox SlateportCity_NameRatersHouse_Text_ThatIsMerelyAnEgg, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT::
	msgbox SlateportCity_NameRatersHouse_Text_MagnificentName, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_ChangeNickname::
	msgbox SlateportCity_NameRatersHouse_Text_WhatShallNewNameBe, MSGBOX_DEFAULT
	call Common_EventScript_NameReceivedPartyMon
	specialvar VAR_RESULT, TryPutNameRaterShowOnTheAir
	special BufferMonNickname
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_NameRatersHouse_EventScript_NewNameDifferent
	msgbox SlateportCity_NameRatersHouse_Text_NameNoDifferentYetSuperior, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_NewNameDifferent::
	msgbox SlateportCity_NameRatersHouse_Text_MonShallBeKnownAsName, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_Text_PleasedToRateMonNickname:
	.string "{CHN}嗨，嗨！我是命名师！\n"
	.string "我是名字的算命师！\p"
	.string "我很乐意评价你的\n"
	.string "宝可梦的昵称。$"

SlateportCity_NameRatersHouse_Text_CritiqueWhichMonNickname:
	.string "{CHN}我应该点评\n"
	.string "哪只宝可梦的昵称呢？$"

SlateportCity_NameRatersHouse_Text_FineNameSuggestBetterOne:
	.string "{CHN}嗯…{STR_VAR_1}，是吗？那是个\n"
	.string "很好的名字。\p"
	.string "但是！要是我建议\n"
	.string "一个更好的名字呢？$"

SlateportCity_NameRatersHouse_Text_WhatShallNewNameBe:
	.string "{CHN}啊，好的。那么，新的\n"
	.string "昵称叫什么呢？$"

SlateportCity_NameRatersHouse_Text_MonShallBeKnownAsName:
	.string "{CHN}好了！从现在起，这只宝可梦\n"
	.string "就叫{STR_VAR_1}了！\p"
	.string "这个名字比以前更好了！\n"
	.string "你真幸运！$"

SlateportCity_NameRatersHouse_Text_DoVisitAgain:
	.string "{CHN}我明白了。\n"
	.string "请下次再来。$"

SlateportCity_NameRatersHouse_Text_NameNoDifferentYetSuperior:
	.string "{CHN}好了！从现在起，这只宝可梦\n"
	.string "就叫{STR_VAR_1}了！\p"
	.string "看起来和以前没什么不同，\n"
	.string "但是，这名字好多了！\p"
	.string "你真幸运！$"

SlateportCity_NameRatersHouse_Text_MagnificentName:
	.string "{CHN}嗯…是{STR_VAR_1}啊！\p"
	.string "这是个了不起的昵称！\n"
	.string "简直无可挑剔！\p"
	.string "你要好好珍惜你的\n"
	.string "{STR_VAR_1}，从今往后。$"

SlateportCity_NameRatersHouse_Text_ThatIsMerelyAnEgg:
	.string "{CHN}哎呀哎呀。\n"
	.string "那只不过是一个蛋而已！$"

