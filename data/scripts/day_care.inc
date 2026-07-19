Route117_EventScript_DaycareMan::
	lock
	faceplayer
	special GetDaycareMonNicknames
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_EGG_WAITING, Route117_EventScript_DaycareEggWaiting
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route117_EventScript_CheckOnOneMon
	goto_if_eq VAR_RESULT, DAYCARE_TWO_MONS, Route117_EventScript_CheckOnTwoMons
	msgbox Route117_Text_SeeWifeIfYoudLikeMeToRaiseMon, MSGBOX_DEFAULT
	release
	end

Route117_EventScript_DaycareEggWaiting::
	msgbox Route117_Text_DoYouWantEgg, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route117_EventScript_DaycareAcceptEgg
	msgbox Route117_Text_IWillKeepDoYouWantIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route117_EventScript_DaycareAcceptEgg
	msgbox Route117_Text_IllKeepIt, MSGBOX_DEFAULT
	clearflag FLAG_PENDING_DAYCARE_EGG
	special RejectEggFromDayCare
	release
	end

Route117_EventScript_DaycareAcceptEgg::
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_ne VAR_RESULT, PARTY_SIZE, Route117_EventScript_DaycareReceiveEgg
	msgbox Route117_Text_YouHaveNoRoomForIt, MSGBOX_DEFAULT
	release
	end

Route117_EventScript_DaycareReceiveEgg::
	message Route117_Text_ReceivedEgg
	playfanfare MUS_LEVEL_UP
	waitfanfare
	waitbuttonpress
	msgbox Route117_Text_TakeGoodCareOfIt, MSGBOX_DEFAULT
	special GiveEggFromDaycare
	clearflag FLAG_PENDING_DAYCARE_EGG
	release
	end

Route117_EventScript_CheckMonReceivedMail::
	specialvar VAR_RESULT, CheckDaycareMonReceivedMail
	call_if_eq VAR_RESULT, 1, Route117_EventScript_MonReceivedMail
	return

Route117_EventScript_MonReceivedMail::
	msgbox Route117_Text_FriendlyWithOtherTrainersMon, MSGBOX_DEFAULT
	return

Route117_EventScript_CheckOnOneMon::
	special GetDaycareMonNicknames
	msgbox Route117_Text_YourMonIsDoingFine, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call Route117_EventScript_CheckMonReceivedMail
	release
	end

Route117_EventScript_CheckOnTwoMons::
	special GetDaycareMonNicknames
	msgbox Route117_Text_YourMonsAreDoingFine, MSGBOX_DEFAULT
	special SetDaycareCompatibilityString
	special ShowFieldMessageStringVar4
	waitmessage
	waitbuttonpress
	setvar VAR_0x8004, 0
	call Route117_EventScript_CheckMonReceivedMail
	setvar VAR_0x8004, 1
	call Route117_EventScript_CheckMonReceivedMail
	release
	end

Route117_PokemonDayCare_EventScript_DaycareWoman::
	lock
	faceplayer
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_EGG_WAITING, Route117_PokemonDayCare_EventScript_EggWaiting
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route117_PokemonDayCare_EventScript_OneMonInDaycare
	goto_if_eq VAR_RESULT, DAYCARE_TWO_MONS, Route117_PokemonDayCare_EventScript_TwoMonsInDaycare
	msgbox Route117_PokemonDayCare_Text_WouldYouLikeUsToRaiseAMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route117_PokemonDayCare_EventScript_GiveMonToRaise
	msgbox Route117_PokemonDayCare_Text_FineThenComeAgain, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_GiveMonToRaise::
	specialvar VAR_RESULT, CountPartyNonEggMons
	goto_if_eq VAR_RESULT, 1, Route117_PokemonDayCare_EventScript_OnlyOneMon
	specialvar VAR_RESULT, CountPartyAliveNonEggMons
	goto_if_eq VAR_RESULT, 2, Route117_PokemonDayCare_EventScript_OnlyTwoAliveMons
	msgbox Route117_PokemonDayCare_Text_WhichMonShouldWeRaise, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special ChooseSendDaycareMon
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Route117_PokemonDayCare_EventScript_ComeAgain
	specialvar VAR_RESULT, CountPartyAliveNonEggMons_IgnoreVar0x8004Slot
	goto_if_eq VAR_RESULT, 0, Route117_PokemonDayCare_EventScript_OnlyOneAliveMon
	specialvar VAR_0x8005, GetSelectedMonNicknameAndSpecies
	waitse
	playmoncry VAR_0x8005, CRY_MODE_NORMAL
	msgbox Route117_PokemonDayCare_Text_WellRaiseYourMon, MSGBOX_DEFAULT
	waitmoncry
	special StoreSelectedPokemonInDaycare
	incrementgamestat GAME_STAT_USED_DAYCARE
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route117_PokemonDayCare_EventScript_CanRaiseOneMore
	release
	end

Route117_PokemonDayCare_EventScript_ComeAgain::
	msgbox Route117_PokemonDayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_CanRaiseOneMore::
	msgbox Route117_PokemonDayCare_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route117_PokemonDayCare_EventScript_GiveMonToRaise
	goto Route117_PokemonDayCare_EventScript_ComeAgain
	end

Route117_PokemonDayCare_EventScript_OnlyOneMon::
	msgbox Route117_PokemonDayCare_Text_YouHaveJustOneMon, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_OnlyOneAliveMon::
	msgbox Route117_PokemonDayCare_Text_WhatWillYouBattleWith, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_OnlyTwoAliveMons::
	msgbox Route117_PokemonDayCare_Text_YoullBeLeftWithJustOne, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_EggWaiting::
	msgbox Route117_PokemonDayCare_Text_HusbandWasLookingForYou, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_YourMonHasGrownXLevels::
	msgbox Route117_PokemonDayCare_Text_YourMonHasGrownXLevels, MSGBOX_DEFAULT
	return

Route117_PokemonDayCare_EventScript_DisplayLevelsGained::
	specialvar VAR_RESULT, GetNumLevelsGainedFromDaycare
	call_if_ne VAR_RESULT, 0, Route117_PokemonDayCare_EventScript_YourMonHasGrownXLevels
	return

Route117_PokemonDayCare_EventScript_OneMonInDaycare::
	msgbox Route117_PokemonDayCare_Text_GoodToSeeYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call Route117_PokemonDayCare_EventScript_DisplayLevelsGained
	msgbox Route117_PokemonDayCare_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route117_PokemonDayCare_EventScript_GiveMonToRaise
	msgbox Route117_PokemonDayCare_Text_TakeYourMonBack, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route117_PokemonDayCare_EventScript_TryRetrieveMon
	goto Route117_PokemonDayCare_EventScript_ComeAgain
	end

Route117_PokemonDayCare_EventScript_TryRetrieveMon::
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_eq VAR_RESULT, PARTY_SIZE, Route117_PokemonDayCare_EventScript_NoRoom
	specialvar VAR_RESULT, GetDaycareState
	setvar VAR_0x8004, 0
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route117_PokemonDayCare_EventScript_CostPrompt
	special ShowDaycareLevelMenu
	waitstate
	copyvar VAR_0x8004, VAR_RESULT
	goto_if_eq VAR_RESULT, DAYCARE_EXITED_LEVEL_MENU, Route117_PokemonDayCare_EventScript_ComeAgain
	goto Route117_PokemonDayCare_EventScript_CostPrompt
	end

Route117_PokemonDayCare_EventScript_CostPrompt::
	special GetDaycareCost
	msgbox Route117_PokemonDayCare_Text_ItWillCostX, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route117_PokemonDayCare_EventScript_CheckEnoughMoney
	goto Route117_PokemonDayCare_EventScript_ComeAgain
	end

Route117_PokemonDayCare_EventScript_CheckEnoughMoney::
	specialvar VAR_RESULT, IsEnoughForCostInVar0x8005
	goto_if_eq VAR_RESULT, 1, Route117_PokemonDayCare_EventScript_RetrieveMon
	msgbox Route117_PokemonDayCare_Text_NotEnoughMoney, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_RetrieveMon::
	applymovement LOCALID_DAYCARE_LADY, Route117_PokemonDayCare_Movement_RetrieveDaycareMon
	waitmovement 0
	specialvar VAR_RESULT, TakePokemonFromDaycare
	special SubtractMoneyFromVar0x8005
	playse SE_SHOP
	msgbox Route117_PokemonDayCare_Text_HeresYourMon, MSGBOX_DEFAULT
	waitse
	playmoncry VAR_RESULT, CRY_MODE_NORMAL
	msgbox Route117_PokemonDayCare_Text_TookBackMon, MSGBOX_DEFAULT
	waitmoncry
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route117_PokemonDayCare_EventScript_AskRetrieveOtherMon
	goto Route117_PokemonDayCare_EventScript_ComeAgain
	end

Route117_PokemonDayCare_EventScript_AskRetrieveOtherMon::
	msgbox Route117_PokemonDayCare_Text_TakeOtherOneBackToo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route117_PokemonDayCare_EventScript_TryRetrieveMon
	goto Route117_PokemonDayCare_EventScript_ComeAgain
	end

Route117_PokemonDayCare_EventScript_NoRoom::
	msgbox Route117_PokemonDayCare_Text_YourTeamIsFull, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_Movement_RetrieveDaycareMon:
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	face_right
	delay_16
	delay_16
	face_up
	walk_slow_up
	set_invisible
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	face_down
	set_visible
	walk_slow_down
	step_end

/* Unused. Possibly a commented script, or a typo end added to the above Movement script*/
Route117_PokemonDayCare_EventScript_UnusedEnd::
	end

Route117_PokemonDayCare_EventScript_TwoMonsInDaycare::
	msgbox Route117_PokemonDayCare_Text_GoodToSeeYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call Route117_PokemonDayCare_EventScript_DisplayLevelsGained
	setvar VAR_0x8004, 1
	call Route117_PokemonDayCare_EventScript_DisplayLevelsGained
	msgbox Route117_PokemonDayCare_Text_TakeYourMonBack, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route117_PokemonDayCare_EventScript_TryRetrieveMon
	msgbox Route117_PokemonDayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

/* Unused*/
Route117_PokemonDayCare_EventScript_UnusedRetrieveMon::
	special ShowDaycareLevelMenu
	waitstate
	goto_if_eq VAR_RESULT, 2, Route117_PokemonDayCare_EventScript_ComeAgain
	copyvar VAR_0x8004, VAR_RESULT
	specialvar VAR_RESULT, TakePokemonFromDaycare
	msgbox Route117_PokemonDayCare_Text_HeresYourMon, MSGBOX_DEFAULT
	msgbox Route117_PokemonDayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

EventScript_EggHatch::
	lockall
	msgbox Text_EggHatchHuh, MSGBOX_DEFAULT
	special EggHatch
	waitstate
	releaseall
	end

Route117_Text_SeeWifeIfYoudLikeMeToRaiseMon:
	.string "{CHN}我是寄宿处老爷爷。\p"
	.string "我帮忙照看训练家们\n"
	.string "宝贵的宝可梦。\p"
	.string "如果你想让我培育你的宝可梦，\n"
	.string "请跟我妻子说说。$"

Route117_Text_DoYouWantEgg:
	.string "{CHN}啊，是你啊！\p"
	.string "我们在培育你的宝可梦时，\n"
	.string "天哪，我们大吃一惊！\p"
	.string "你的宝可梦生了一个蛋！\p"
	.string "我们不知道它是怎么来的，\n"
	.string "但是你的宝可梦带着它。\p"
	.string "你想要它，对吧？$"

Route117_Text_YourMonIsDoingFine:
	.string "{CHN}啊，是你啊！很高兴见到你。\n"
	.string "你的{STR_VAR_1}过得很好。$"

Route117_Text_IllKeepIt:
	.string "{CHN}那么，我就收下它了。\n"
	.string "谢谢！$"

Route117_Text_YouHaveNoRoomForIt:
	.string "{CHN}你没有地方放它……\n"
	.string "腾出位置后再来吧。$"

Route117_Text_ReceivedEgg:
	.string "{CHN}{PLAYER}从寄宿处老爷爷那里\n"
	.string "得到了蛋。$"

Route117_Text_TakeGoodCareOfIt:
	.string "{CHN}要好好照顾它哦。$"

Route117_Text_FriendlyWithOtherTrainersMon:
	.string "{CHN}对了，关于你的{STR_VAR_1}，\n"
	.string "它好像和{STR_VAR_2}的{STR_VAR_3}\l"
	.string "相处得很好。\p"
	.string "我甚至看到它收到了\n"
	.string "一封信。$"

/* Unused*/
Route117_Text_SeeWifeIfYouWantToPickUpMon:
	.string "{CHN}如果你想领回你的宝可梦，\n"
	.string "请跟我妻子说说。$"

Route117_Text_YourMonsAreDoingFine:
	.string "{CHN}啊，是你啊！你的{STR_VAR_1}和\n"
	.string "{STR_VAR_2}都过得很好。$"

Route117_Text_IWillKeepDoYouWantIt:
	.string "{CHN}我真的会收下它。\n"
	.string "你想要它，对吧？$"

Route117_PokemonDayCare_Text_WouldYouLikeUsToRaiseAMon:
	.string "{CHN}我是寄宿处老奶奶。\p"
	.string "我们可以帮你培育宝可梦。\p"
	.string "你要让我们培育一只吗？$"

Route117_PokemonDayCare_Text_WhichMonShouldWeRaise:
	.string "{CHN}我们要为你培育\n"
	.string "哪只宝可梦呢？$"

Route117_PokemonDayCare_Text_WellRaiseYourMon:
	.string "{CHN}好的，我们会培育你的{STR_VAR_1}\n"
	.string "一阵子。\p"
	.string "之后再来接它吧。$"

Route117_PokemonDayCare_Text_WeCanRaiseOneMore:
	.string "{CHN}我们可以培育你的两只宝可梦。\n"
	.string "你要让我们再培育一只吗？$"

Route117_PokemonDayCare_Text_HusbandWasLookingForYou:
	.string "{CHN}我丈夫在找你。$"

Route117_PokemonDayCare_Text_FineThenComeAgain:
	.string "{CHN}哦，那好吧。\n"
	.string "下次再来。$"

Route117_PokemonDayCare_Text_NotEnoughMoney:
	.string "{CHN}你的钱不够……$"

Route117_PokemonDayCare_Text_TakeOtherOneBackToo:
	.string "{CHN}你要不要把另一只\n"
	.string "也领回去呢？$"

Route117_PokemonDayCare_Text_ComeAgain:
	.string "{CHN}好的。\n"
	.string "下次再来。$"

Route117_PokemonDayCare_Text_GoodToSeeYou:
	.string "{CHN}啊，是你啊！很高兴见到你。\n"
	.string "你的宝可梦一定过得很好！$"

Route117_PokemonDayCare_Text_YourMonHasGrownXLevels:
	.string "{CHN}等级方面，你的{STR_VAR_1}\n"
	.string "增长了{STR_VAR_2}级。$"

Route117_PokemonDayCare_Text_YourTeamIsFull:
	.string "{CHN}你的宝可梦队伍已满。\n"
	.string "腾出位置后再来找我。$"

/* Unused*/
Route117_PokemonDayCare_Text_TakeBackWhichMon:
	.string "{CHN}你要领回哪只宝可梦呢？$"

Route117_PokemonDayCare_Text_ItWillCostX:
	.string "{CHN}如果你想领回你的{STR_VAR_1}，\n"
	.string "需要花费¥{STR_VAR_2}。$"

Route117_PokemonDayCare_Text_HeresYourMon:
	.string "{CHN}完美！\n"
	.string "这是你的宝可梦。$"

Route117_PokemonDayCare_Text_TookBackMon:
	.string "{CHN}{PLAYER}从寄宿处老奶奶那里\n"
	.string "领回了{STR_VAR_1}。$"

Route117_PokemonDayCare_Text_YouHaveJustOneMon:
	.string "{CHN}哦？可是你只有一只\n"
	.string "宝可梦。\p"
	.string "下次再来吧。$"

Route117_PokemonDayCare_Text_TakeYourMonBack:
	.string "{CHN}你要领回你的宝可梦吗？$"

Route117_PokemonDayCare_Text_WhatWillYouBattleWith:
	.string "{CHN}如果你把那只宝可梦留给我，\n"
	.string "你要用什么来战斗呢？\p"
	.string "下次再来吧。$"

Text_EggHatchHuh:
	.string "{CHN}咦？$"

Route117_PokemonDayCare_Text_YoullBeLeftWithJustOne:
	.string "{CHN}咦？\n"
	.string "好了好了。\p"
	.string "如果你把那只宝可梦留给我，\n"
	.string "你就只剩一只了。\p"
	.string "我敢说，你要是多抓几只\n"
	.string "会更好哦。$"
