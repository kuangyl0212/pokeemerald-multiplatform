SlateportCity_PokemonFanClub_MapScripts::
	.byte 0

SlateportCity_PokemonFanClub_EventScript_Chairman::
	lock
	faceplayer
	goto_if_unset FLAG_ENTERED_CONTEST, SlateportCity_PokemonFanClub_EventScript_ChairmanNotEnteredContest
	call_if_unset FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN, SlateportCity_PokemonFanClub_EventScript_MeetChairman
	switch VAR_SLATEPORT_FAN_CLUB_STATE
	case 0, SlateportCity_PokemonFanClub_EventScript_ChairmanFirstAssessment
	case 1, SlateportCity_PokemonFanClub_EventScript_ChairmanTryAssessPokemon
	case 2, SlateportCity_PokemonFanClub_EventScript_NoMoreScarves
	release
	end

SlateportCity_PokemonFanClub_EventScript_ChairmanFirstAssessment::
	setvar VAR_SLATEPORT_FAN_CLUB_STATE, 1
	msgbox SlateportCity_PokemonFanClub_Text_AllowMeToExamineYourPokemon, MSGBOX_DEFAULT
	goto SlateportCity_PokemonFanClub_EventScript_ChairmanAssessLeadMon
	end

SlateportCity_PokemonFanClub_EventScript_ChairmanTryAssessPokemon::
	setvar VAR_TEMP_2, 0
	call_if_set FLAG_RECEIVED_YELLOW_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_set FLAG_RECEIVED_GREEN_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_set FLAG_RECEIVED_PINK_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_set FLAG_RECEIVED_BLUE_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_set FLAG_RECEIVED_RED_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_eq VAR_TEMP_2, CONTEST_CATEGORIES_COUNT, SlateportCity_PokemonFanClub_EventScript_ReceivedAllScarves
	goto_if_eq VAR_SLATEPORT_FAN_CLUB_STATE, 2, SlateportCity_PokemonFanClub_EventScript_NoMoreScarves
	msgbox SlateportCity_PokemonFanClub_Text_HowIsYourPokemonGrowing, MSGBOX_DEFAULT
	goto SlateportCity_PokemonFanClub_EventScript_ChairmanAssessLeadMon
	end

SlateportCity_PokemonFanClub_EventScript_NoMoreScarves::
	msgbox SlateportCity_PokemonFanClub_Text_NothingElseToGiveYou, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_ChairmanAssessLeadMon::
	msgbox SlateportCity_PokemonFanClub_Text_HmHmISee, MSGBOX_DEFAULT
	setvar VAR_TEMP_1, 0
	call_if_unset FLAG_RECEIVED_YELLOW_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonTough
	call_if_unset FLAG_RECEIVED_GREEN_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonSmart
	call_if_unset FLAG_RECEIVED_PINK_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonCute
	call_if_unset FLAG_RECEIVED_BLUE_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonBeauty
	call_if_unset FLAG_RECEIVED_RED_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonCool
	bufferleadmonspeciesname STR_VAR_1
	switch VAR_TEMP_1
	case 0, SlateportCity_PokemonFanClub_EventScript_NoHighConditions
	case 1, SlateportCity_PokemonFanClub_EventScript_GiveRedScarf
	case 2, SlateportCity_PokemonFanClub_EventScript_GiveBlueScarf
	case 3, SlateportCity_PokemonFanClub_EventScript_GivePinkScarf
	case 4, SlateportCity_PokemonFanClub_EventScript_GiveGreenScarf
	case 5, SlateportCity_PokemonFanClub_EventScript_GiveYellowScarf
	release
	end

SlateportCity_PokemonFanClub_EventScript_ReceivedAllScarves::
	setvar VAR_SLATEPORT_FAN_CLUB_STATE, 2
	return

SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf::
	addvar VAR_TEMP_2, 1
	return

SlateportCity_PokemonFanClub_EventScript_NoHighConditions::
	msgbox SlateportCity_PokemonFanClub_Text_GiveMonMorePokeblocks, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveRedScarf::
	checkitemspace ITEM_RED_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_RED_SCARF
	giveitem ITEM_RED_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainRedScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveBlueScarf::
	checkitemspace ITEM_BLUE_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_BLUE_SCARF
	giveitem ITEM_BLUE_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainBlueScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GivePinkScarf::
	checkitemspace ITEM_PINK_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_PINK_SCARF
	giveitem ITEM_PINK_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainPinkScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveGreenScarf::
	checkitemspace ITEM_GREEN_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_GREEN_SCARF
	giveitem ITEM_GREEN_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainGreenScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveYellowScarf::
	checkitemspace ITEM_YELLOW_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_YELLOW_SCARF
	giveitem ITEM_YELLOW_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainYellowScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf::
	msgbox SlateportCity_PokemonFanClub_Text_NoSpaceForReward, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_CheckMonCool::
	specialvar VAR_RESULT, CheckLeadMonCool
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonCool
	return

SlateportCity_PokemonFanClub_EventScript_SetMonCool::
	setvar VAR_TEMP_1, 1
	return

SlateportCity_PokemonFanClub_EventScript_CheckMonBeauty::
	specialvar VAR_RESULT, CheckLeadMonBeauty
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonBeauty
	return

SlateportCity_PokemonFanClub_EventScript_SetMonBeauty::
	setvar VAR_TEMP_1, 2
	return

SlateportCity_PokemonFanClub_EventScript_CheckMonCute::
	specialvar VAR_RESULT, CheckLeadMonCute
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonCute
	return

SlateportCity_PokemonFanClub_EventScript_SetMonCute::
	setvar VAR_TEMP_1, 3
	return

SlateportCity_PokemonFanClub_EventScript_CheckMonSmart::
	specialvar VAR_RESULT, CheckLeadMonSmart
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonSmart
	return

SlateportCity_PokemonFanClub_EventScript_SetMonSmart::
	setvar VAR_TEMP_1, 4
	return

SlateportCity_PokemonFanClub_EventScript_CheckMonTough::
	specialvar VAR_RESULT, CheckLeadMonTough
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonTough
	return

SlateportCity_PokemonFanClub_EventScript_SetMonTough::
	setvar VAR_TEMP_1, 5
	return

SlateportCity_PokemonFanClub_EventScript_ChairmanNotEnteredContest::
	goto_if_set FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN, SlateportCity_PokemonFanClub_EventScript_ChairmanEnterContest
	msgbox SlateportCity_PokemonFanClub_Text_MeetChairman, MSGBOX_DEFAULT
	setflag FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN
	release
	end

SlateportCity_PokemonFanClub_EventScript_ChairmanEnterContest::
	msgbox SlateportCity_PokemonFanClub_Text_LikeToSeeEnteredContestPokemon, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_MeetChairman::
	msgbox SlateportCity_PokemonFanClub_Text_MeetChairman, MSGBOX_DEFAULT
	setflag FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN
	return

SlateportCity_PokemonFanClub_EventScript_SootheBellWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SOOTHE_BELL, SlateportCity_PokemonFanClub_EventScript_ReceivedSootheBell
	msgbox SlateportCity_PokemonFanClub_Text_ShowMePokemonThatLoveYou, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	goto_if_ge VAR_RESULT, FRIENDSHIP_150_TO_199, SlateportCity_PokemonFanClub_EventScript_GiveSootheBell
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveSootheBell::
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox SlateportCity_PokemonFanClub_Text_PokemonAdoresYou, MSGBOX_DEFAULT
	giveitem ITEM_SOOTHE_BELL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_SOOTHE_BELL
	release
	end

SlateportCity_PokemonFanClub_EventScript_ReceivedSootheBell::
	msgbox SlateportCity_PokemonFanClub_Text_TreatPokemonWithLove, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_Man::
	msgbox SlateportCity_PokemonFanClub_Text_PokemonDontLikeFainting, MSGBOX_NPC
	end

SlateportCity_PokemonFanClub_EventScript_Twin::
	msgbox SlateportCity_PokemonFanClub_Text_MonEnjoyedProtein, MSGBOX_NPC
	end

SlateportCity_PokemonFanClub_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox SlateportCity_PokemonFanClub_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SlateportCity_PokemonFanClub_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox SlateportCity_PokemonFanClub_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SlateportCity_PokemonFanClub_EventScript_Azumarill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZUMARILL, CRY_MODE_NORMAL
	msgbox SlateportCity_PokemonFanClub_Text_Azumarill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SlateportCity_PokemonFanClub_Text_MeetChairman:
	.string "{CHN}咳咳！我是宝可梦\n"
	.string "俱乐部的会长！\p"
	.string "作为会长，我自然是\n"
	.string "最重要的！\p"
	.string "说到培育宝可梦，没有人能\n"
	.string "比我更厉害。没有人！\p"
	.string "好吧，让我告诉你关于\n"
	.string "宝可梦评选赛的事。\p"
	.string "那是一种可以向世人展示\n"
	.string "宝可梦的活动！\p"
	.string "不过，它们都在很远的城镇举办，\n"
	.string "所以我没法经常参加。\p"
	.string "所以我们在这里聚集，展示\n"
	.string "我们的宝可梦，也让别人\l"
	.string "展示他们的。$"

SlateportCity_PokemonFanClub_Text_LikeToSeeEnteredContestPokemon:
	.string "{CHN}参加过宝可梦评选赛的\n"
	.string "训练家的宝可梦…\l"
	.string "那个，我想看看。$"

SlateportCity_PokemonFanClub_Text_AllowMeToExamineYourPokemon:
	.string "{CHN}咳咳！我看你参加过了\n"
	.string "宝可梦评选赛！\p"
	.string "请！让我检查一下你是如何\n"
	.string "培育你的宝可梦的。\p"
	.string "看到其他训练家培育的宝可梦\n"
	.string "我真是太开心了。\p"
	.string "宝可梦被好好照顾后\n"
	.string "露出的快乐表情…\p"
	.string "培育它的训练家\n"
	.string "那慈祥的眼神…\p"
	.string "光是想想我就\n"
	.string "心花怒放了。\p"
	.string "哦！非常抱歉！\n"
	.string "原谅我喋喋不休！\p"
	.string "请！让我检查一下你的宝可梦\n"
	.string "成长得如何了！$"

SlateportCity_PokemonFanClub_Text_HowIsYourPokemonGrowing:
	.string "{CHN}你的宝可梦成长得如何？\n"
	.string "让我检查一下吧。$"

SlateportCity_PokemonFanClub_Text_HmHmISee:
	.string "{CHN}嗯，嗯…\n"
	.string "我看看…$"

SlateportCity_PokemonFanClub_Text_GiveMonMorePokeblocks:
	.string "{CHN}嗯…说不上差，但也不能说\n"
	.string "好…\p"
	.string "作为训练家，你应该更努力地\n"
	.string "培育这只宝可梦！\p"
	.string "比如，你可以给它吃\n"
	.string "更多的{POKEBLOCK}S如何？$"

SlateportCity_PokemonFanClub_Text_NoSpaceForReward:
	.string "{CHN}哎呀…\p"
	.string "你的宝可梦成长得非常好，\n"
	.string "你应该得到奖励。\p"
	.string "不过很遗憾，你的背包里\n"
	.string "没有空间装这个了。$"

SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis:
	.string "{CHN}你的{STR_VAR_1}成长得\n"
	.string "非常惊人！\l"
	.string "真是个好标本！\p"
	.string "不过！如果你给它这个，\n"
	.string "它会成长得更好！真的！$"

SlateportCity_PokemonFanClub_Text_ExplainRedScarf:
	.string "{CHN}让宝可梦携带那条红色头巾。\p"
	.string "大家都会认可\n"
	.string "那只宝可梦的帅气！$"

SlateportCity_PokemonFanClub_Text_ExplainBlueScarf:
	.string "{CHN}让宝可梦携带那条蓝色头巾。\p"
	.string "它的美丽会比现在\n"
	.string "更加突出！$"

SlateportCity_PokemonFanClub_Text_ExplainPinkScarf:
	.string "{CHN}让宝可梦携带那条粉色头巾。\p"
	.string "它会进一步激发\n"
	.string "宝可梦的可爱！$"

SlateportCity_PokemonFanClub_Text_ExplainGreenScarf:
	.string "{CHN}让宝可梦携带那条绿色头巾。\p"
	.string "这会增强\n"
	.string "宝可梦的聪明！$"

SlateportCity_PokemonFanClub_Text_ExplainYellowScarf:
	.string "{CHN}让宝可梦携带那条黄色头巾。\p"
	.string "它会大幅增强\n"
	.string "你宝可梦的强壮！$"

SlateportCity_PokemonFanClub_Text_NothingElseToGiveYou:
	.string "{CHN}很抱歉，我已经没有别的\n"
	.string "东西可以给你了！什么都没有！\p"
	.string "毕竟，你天生就有\n"
	.string "培育宝可梦的天赋，\l"
	.string "根本不需要任何道具！$"

SlateportCity_PokemonFanClub_Text_ShowMePokemonThatLoveYou:
	.string "{CHN}我喜欢看到爱\n"
	.string "训练家的宝可梦。\p"
	.string "宝可梦对训练家的\n"
	.string "感情非常敏感。\p"
	.string "如果你用爱和关怀对待你的宝可梦，\n"
	.string "它们也会爱你的。\p"
	.string "当你的宝可梦爱上你时，\n"
	.string "请来给我看看。$"

SlateportCity_PokemonFanClub_Text_PokemonAdoresYou:
	.string "{CHN}你的宝可梦真的很爱你。\p"
	.string "给这位最有爱心的\n"
	.string "训练家，来自俱乐部的礼物！$"

SlateportCity_PokemonFanClub_Text_TreatPokemonWithLove:
	.string "{CHN}宝可梦对训练家的\n"
	.string "感情非常敏感。\p"
	.string "如果你用爱和关怀对待你的宝可梦，\n"
	.string "它们也会爱你的。$"

SlateportCity_PokemonFanClub_Text_PokemonDontLikeFainting:
	.string "{CHN}如果你总是让宝可梦\n"
	.string "在战斗中倒下，它会怨恨的。\p"
	.string "很快，它就会变得\n"
	.string "不那么信任训练家。\p"
	.string "换句话说，它肯定\n"
	.string "不会太喜欢你了。$"

SlateportCity_PokemonFanClub_Text_MonEnjoyedProtein:
	.string "{CHN}宝可梦喜欢被\n"
	.string "使用道具吗？\p"
	.string "当我给它吃蛋白质时，\n"
	.string "它看起来非常开心。$"

SlateportCity_PokemonFanClub_Text_Skitty:
	.string "{CHN}向尾喵：喵呜呀啊…$"

SlateportCity_PokemonFanClub_Text_Zigzagoon:
	.string "{CHN}蛇纹熊：咕呜…$"

SlateportCity_PokemonFanClub_Text_Azumarill:
	.string "{CHN}玛力露丽：玛力玛力？$"

