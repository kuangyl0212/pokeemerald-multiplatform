SootopolisCity_LotadAndSeedotHouse_MapScripts::
	.byte 0

SootopolisCity_LotadAndSeedotHouse_EventScript_SeedotBrother::
	special GetSeedotSizeRecordInfo
	lock
	faceplayer
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigSeedot, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	copyvar VAR_RESULT, VAR_0x8004
	goto_if_eq VAR_RESULT, PARTY_NOTHING_CHOSEN, SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowSeedot
	special CompareSeedotSize
	goto_if_eq VAR_RESULT, 1, SootopolisCity_LotadAndSeedotHouse_EventScript_NotSeedot
	goto_if_eq VAR_RESULT, 2, SootopolisCity_LotadAndSeedotHouse_EventScript_SmallSeedot
	goto_if_eq VAR_RESULT, 3, SootopolisCity_LotadAndSeedotHouse_EventScript_BigSeedot
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowSeedot::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigSeedot, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NotSeedot::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotSeedot, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_SmallSeedot::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerSeedot, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_BigSeedot::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_GoshMightBeBiggerThanLotad, MSGBOX_DEFAULT
	giveitem ITEM_ELIXIR
	goto_if_eq VAR_RESULT, FALSE, SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir1
	closemessage
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir1::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull1, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_LotadBrother::
	special GetLotadSizeRecordInfo
	lock
	faceplayer
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigLotad, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	copyvar VAR_RESULT, VAR_0x8004
	goto_if_eq VAR_RESULT, PARTY_NOTHING_CHOSEN, SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowLotad
	special CompareLotadSize
	goto_if_eq VAR_RESULT, 1, SootopolisCity_LotadAndSeedotHouse_EventScript_NotLotad
	goto_if_eq VAR_RESULT, 2, SootopolisCity_LotadAndSeedotHouse_EventScript_SmallLotad
	goto_if_eq VAR_RESULT, 3, SootopolisCity_LotadAndSeedotHouse_EventScript_BigLotad
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowLotad::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigLotad, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NotLotad::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotLotad, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_SmallLotad::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerLotad, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_BigLotad::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_WowMightBeBiggerThanSeedot, MSGBOX_DEFAULT
	giveitem ITEM_ELIXIR
	goto_if_eq VAR_RESULT, FALSE, SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir2
	closemessage
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir2::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull2, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_SeedotSizeRecord::
	special GetSeedotSizeRecordInfo
	lockall
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BiggestSeedotInHistory, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_LotadSizeRecord::
	special GetLotadSizeRecordInfo
	lockall
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BiggestLotadInHistory, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigSeedot:
	.string "{CHN}你知道橡实果这种宝可梦吗？\n"
	.string "在琉璃市很少见到。\p"
	.string "总之，我喜欢大号的橡实果。\n"
	.string "越大越好。\p"
	.string "但是我弟弟说\n"
	.string "莲叶童子更大。\p"
	.string "那太傻了。\n"
	.string "橡实果肯定比那个大！\p"
	.string "咦？你带着橡实果吗？\n"
	.string "请、请让我看看！$"

SootopolisCity_LotadAndSeedotHouse_Text_GoshMightBeBiggerThanLotad:
	.string "{CHN}{STR_VAR_2}英寸！\n"
	.string "哦，天哪，这个真大！\p"
	.string "说不定比我弟弟见过的\n"
	.string "大莲叶童子还要大！\p"
	.string "谢谢你让我看。\n"
	.string "这是谢礼！$"

/* Unused*/
SootopolisCity_LotadAndSeedotHouse_Text_ReceivedPotion1:
	.string "{CHN}{PLAYER}得到了伤药。$"

SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull1:
	.string "{CHN}咦？\n"
	.string "你的背包已经满了。$"

SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerSeedot:
	.string "{CHN}{STR_VAR_2}英寸是吧？\p"
	.string "嗯……我见过\n"
	.string "比这更大的橡实果。$"

SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotSeedot:
	.string "{CHN}哦，这倒是挺稀奇的……\n"
	.string "但这不是橡实果啊！$"

SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigSeedot:
	.string "{CHN}你没有大号的橡实果吗？\n"
	.string "那太可惜了……\p"
	.string "如果你得到了大号橡实果，\n"
	.string "请来给我看看。$"

SootopolisCity_LotadAndSeedotHouse_Text_BiggestSeedotInHistory:
	.string "{CHN}史上最大的橡实果！\n"
	.string "{STR_VAR_2}的{STR_VAR_3}英寸巨物！\p"
	.string "一直想要一只\n"
	.string "比莲叶童子还大的橡实果！$"

SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigLotad:
	.string "{CHN}你知道莲叶童子这种宝可梦吗？\n"
	.string "在琉璃市很少见。\p"
	.string "我、我真的很喜欢大号的莲叶童子！\p"
	.string "我哥哥说\n"
	.string "橡实果更大。\p"
	.string "但那不对！谁都知道\n"
	.string "莲叶童子大得多。\p"
	.string "咦？你有莲叶童子吗？\n"
	.string "请、请让我看看！$"

SootopolisCity_LotadAndSeedotHouse_Text_WowMightBeBiggerThanSeedot:
	.string "{CHN}{STR_VAR_2}英寸！\n"
	.string "哇，真大！\p"
	.string "说不定比我哥哥见过的\n"
	.string "巨型橡实果还要大。\p"
	.string "谢谢你让我看！\n"
	.string "这是谢礼！$"

/* Unused*/
SootopolisCity_LotadAndSeedotHouse_Text_ReceivedPotion2:
	.string "{CHN}{PLAYER}得到了伤药。$"

SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull2:
	.string "{CHN}咦？\n"
	.string "你的背包已经满了。$"

SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerLotad:
	.string "{CHN}{STR_VAR_2}英寸？\p"
	.string "嗯……我见过\n"
	.string "比这只更大的莲叶童子。$"

SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotLotad:
	.string "{CHN}哎呀，这可真是稀奇！\n"
	.string "但这不是莲叶童子！$"

SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigLotad:
	.string "{CHN}你没有大号的莲叶童子吗？\n"
	.string "真令人失望……\p"
	.string "如果你得到了大号莲叶童子，\n"
	.string "请来给我看看！$"

SootopolisCity_LotadAndSeedotHouse_Text_BiggestLotadInHistory:
	.string "{CHN}史上最大的莲叶童子！\n"
	.string "{STR_VAR_2}的{STR_VAR_3}英寸巨无霸！\p"
	.string "一直想要一只\n"
	.string "比橡实果还大的莲叶童子！$"

