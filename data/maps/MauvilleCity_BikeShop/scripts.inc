MauvilleCity_BikeShop_MapScripts::
	.byte 0

MauvilleCity_BikeShop_EventScript_Rydel::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_BIKE, MauvilleCity_BikeShop_EventScript_AskSwitchBikes
	goto_if_set FLAG_DECLINED_BIKE, MauvilleCity_BikeShop_EventScript_SkipGreeting
	msgbox MauvilleCity_BikeShop_Text_RydelGreeting, MSGBOX_DEFAULT
	msgbox MauvilleCity_BikeShop_Text_DidYouComeFromFarAway, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_YesFar
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_NotFar
	end

MauvilleCity_BikeShop_EventScript_SkipGreeting::
	msgbox MauvilleCity_BikeShop_Text_DidYouComeFromFarAway, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_YesFar
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_NotFar
	end

MauvilleCity_BikeShop_EventScript_ChooseBike::
	message MauvilleCity_BikeShop_Text_ExplainBikesChooseWhichOne
	waitmessage
	multichoice 21, 8, MULTI_BIKE, TRUE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_GetMachBike
	case 1, MauvilleCity_BikeShop_EventScript_GetAcroBike
	end

MauvilleCity_BikeShop_EventScript_NotFar::
	setflag FLAG_DECLINED_BIKE
	msgbox MauvilleCity_BikeShop_Text_GuessYouDontNeedBike, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_YesFar::
	setflag FLAG_RECEIVED_BIKE
	goto MauvilleCity_BikeShop_EventScript_ChooseBike
	end

MauvilleCity_BikeShop_EventScript_GetMachBike::
	msgbox MauvilleCity_BikeShop_Text_ChoseMachBike, MSGBOX_DEFAULT
	giveitem ITEM_MACH_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_GetAcroBike::
	msgbox MauvilleCity_BikeShop_Text_ChoseAcroBike, MSGBOX_DEFAULT
	giveitem ITEM_ACRO_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_ComeBackToSwitchBikes, MSGBOX_DEFAULT
	special SwapRegisteredBike
	release
	end

MauvilleCity_BikeShop_EventScript_AskSwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_WantToSwitchBikes, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_SwitchBikes
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_KeepBike
	end

/* If the player does not have a bike on them Rydel assumes its stored in the PC*/
MauvilleCity_BikeShop_EventScript_SwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_IllSwitchBikes, MSGBOX_DEFAULT
	checkitem ITEM_ACRO_BIKE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_BikeShop_EventScript_SwitchAcroForMach
	checkitem ITEM_MACH_BIKE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_BikeShop_EventScript_SwitchMachForAcro
	msgbox MauvilleCity_BikeShop_Text_OhYourBikeIsInPC, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_KeepBike::
	msgbox MauvilleCity_BikeShop_Text_HappyYouLikeIt, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_SwitchAcroForMach::
	incrementgamestat GAME_STAT_TRADED_BIKES
	msgbox MauvilleCity_BikeShop_Text_ExchangedAcroForMach, MSGBOX_DEFAULT
	removeitem ITEM_ACRO_BIKE
	giveitem ITEM_MACH_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_SwitchMachForAcro::
	incrementgamestat GAME_STAT_TRADED_BIKES
	msgbox MauvilleCity_BikeShop_Text_ExchangedMachForAcro, MSGBOX_DEFAULT
	removeitem ITEM_MACH_BIKE
	giveitem ITEM_ACRO_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_Assistant::
	msgbox MauvilleCity_BikeShop_Text_HandbooksAreInBack, MSGBOX_NPC
	end

MauvilleCity_BikeShop_EventScript_MachBikeHandbook::
	message MauvilleCity_BikeShop_Text_MachHandbookWhichPage
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage::
	multichoice 0, 0, MULTI_MACH_BIKE_INFO, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_HowToRide
	case 1, MauvilleCity_BikeShop_EventScript_HowToTurn
	case 2, MauvilleCity_BikeShop_EventScript_SandySlopes
	case 3, MauvilleCity_BikeShop_EventScript_ExitMachHandbook
	case MULTI_B_PRESSED, MauvilleCity_BikeShop_EventScript_ExitMachHandbook
	end

MauvilleCity_BikeShop_EventScript_HowToRide::
	message MauvilleCity_BikeShop_Text_HowToRideMachBike
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_HowToTurn::
	message MauvilleCity_BikeShop_Text_HowToTurnMachBike
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_SandySlopes::
	message MauvilleCity_BikeShop_Text_SandySlopes
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ExitMachHandbook::
	release
	end

MauvilleCity_BikeShop_EventScript_AcroBikeHandbook::
	message MauvilleCity_BikeShop_Text_AcroHandbookWhichPage
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage::
	multichoice 0, 0, MULTI_ACRO_BIKE_INFO, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_Wheelies
	case 1, MauvilleCity_BikeShop_EventScript_BunnyHops
	case 2, MauvilleCity_BikeShop_EventScript_Jumps
	case 3, MauvilleCity_BikeShop_EventScript_ExitAcroHandbook
	case MULTI_B_PRESSED, MauvilleCity_BikeShop_EventScript_ExitAcroHandbook
	end

MauvilleCity_BikeShop_EventScript_Wheelies::
	message MauvilleCity_BikeShop_Text_Wheelies
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_BunnyHops::
	message MauvilleCity_BikeShop_Text_BunnyHops
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_Jumps::
	message MauvilleCity_BikeShop_Text_Jumps
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ExitAcroHandbook::
	release
	end

MauvilleCity_BikeShop_Text_RydelGreeting:
	.string "{CHN}哦哦，这位客人，\n"
	.string "您真有精神！\p"
	.string "我？你可以叫我利川。\n"
	.string "我是这家自行车店的老板。$"

MauvilleCity_BikeShop_Text_DidYouComeFromFarAway:
	.string "{CHN}利川：你的跑步鞋……\n"
	.string "脏得厉害。\p"
	.string "你是从很远的地方来的吗？$"

MauvilleCity_BikeShop_Text_GuessYouDontNeedBike:
	.string "{CHN}利川：是吗？\p"
	.string "那么，我想你不需要\n"
	.string "我的任何一辆自行车了。$"

MauvilleCity_BikeShop_Text_ExplainBikesChooseWhichOne:
	.string "{CHN}利川：嗯，嗯…… ……\p"
	.string "你是说你从\n"
	.string "未白镇一路走过来的？\p"
	.string "我的天！\n"
	.string "那可远得离谱！\p"
	.string "如果你有我的一辆自行车，\n"
	.string "你就能轻松地去任何地方，\l"
	.string "感受微风的轻抚！\p"
	.string "这么办吧！\n"
	.string "我送你一辆自行车！\p"
	.string "哦，等等！\p"
	.string "我忘了告诉你，\n"
	.string "自行车有两种！\p"
	.string "它们是竞速自行车\n"
	.string "和跳跃自行车！\p"
	.string "竞速自行车适合那些想用身体\n"
	.string "感受风的骑车人！\p"
	.string "跳跃自行车则适合那些\n"
	.string "喜欢技巧骑乘的人！\p"
	.string "我是个大好人，所以\n"
	.string "你想要哪一辆都可以！\p"
	.string "你要选哪一辆？$"

MauvilleCity_BikeShop_Text_ChoseMachBike:
	.string "{CHN}{PLAYER}选择了竞速自行车。$"

MauvilleCity_BikeShop_Text_ChoseAcroBike:
	.string "{CHN}{PLAYER}选择了跳跃自行车。$"

MauvilleCity_BikeShop_Text_ComeBackToSwitchBikes:
	.string "{CHN}利川：如果你想换\n"
	.string "自行车，就来找我吧！$"

MauvilleCity_BikeShop_Text_WantToSwitchBikes:
	.string "{CHN}利川：哦？你想\n"
	.string "换自行车吗？$"

MauvilleCity_BikeShop_Text_IllSwitchBikes:
	.string "{CHN}利川：好的，没问题！\n"
	.string "我给你换自行车！$"

MauvilleCity_BikeShop_Text_ExchangedMachForAcro:
	.string "{CHN}{PLAYER}把竞速自行车\n"
	.string "换成了一辆跳跃自行车。$"

MauvilleCity_BikeShop_Text_ExchangedAcroForMach:
	.string "{CHN}{PLAYER}把跳跃自行车\n"
	.string "换成了一辆竞速自行车。$"

MauvilleCity_BikeShop_Text_HappyYouLikeIt:
	.string "{CHN}利川：好，好！\n"
	.string "你喜欢它我真高兴！$"

MauvilleCity_BikeShop_Text_OhYourBikeIsInPC:
	.string "{CHN}哦？我给你的那辆自行车\n"
	.string "怎么了？\p"
	.string "哦，我明白了，你把它存到电脑里了。\p"
	.string "那么，把它从电脑里取出来，\n"
	.string "我很乐意给你换！\p"
	.string "愿你的冒险之路上\n"
	.string "永远有顺风相伴！$"

MauvilleCity_BikeShop_Text_HandbooksAreInBack:
	.string "{CHN}我在这里工作的同时\n"
	.string "也在学习关于自行车的知识。\p"
	.string "如果你需要关于如何骑自行车的建议，\n"
	.string "后面有几本手册\l"
	.string "可以看。$"

MauvilleCity_BikeShop_Text_MachHandbookWhichPage:
	.string "{CHN}这是一本关于竞速自行车的手册。\p"
	.string "你想看哪一页？$"

MauvilleCity_BikeShop_Text_HowToRideMachBike:
	.string "{CHN}自行车会朝着\n"
	.string "+控制键按下的方向移动。\p"
	.string "一旦开始滚动，它就会加速。\p"
	.string "要停下来，松开+控制键。\n"
	.string "自行车会慢慢停下。\p"
	.string "想看其他页吗？$"

MauvilleCity_BikeShop_Text_HowToTurnMachBike:
	.string "{CHN}竞速自行车速度很快，\n"
	.string "但不能很快停下来。\p"
	.string "转弯的时候会有点\n"
	.string "棘手。\p"
	.string "在转弯前稍微提前松开\n"
	.string "+控制键减速。\p"
	.string "想看其他页吗？$"

MauvilleCity_BikeShop_Text_SandySlopes:
	.string "{CHN}丰缘地区各处\n"
	.string "都有沙地斜坡。\p"
	.string "松软的沙子使得\n"
	.string "正常攀爬不可能。\p"
	.string "但如果你有竞速自行车，\n"
	.string "你就能冲上沙地斜坡。\p"
	.string "想看其他页吗？$"

MauvilleCity_BikeShop_Text_AcroHandbookWhichPage:
	.string "{CHN}这是一本关于跳跃自行车的手册。\p"
	.string "你想看哪一页？$"

MauvilleCity_BikeShop_Text_Wheelies:
	.string "{CHN}骑行时按下B键，\n"
	.string "前轮就会抬起。\p"
	.string "你可以用+控制键在前轮抬起的\n"
	.string "状态下四处移动。\p"
	.string "这个技巧叫做后轮骑。\p"
	.string "想看其他页吗？$"

MauvilleCity_BikeShop_Text_BunnyHops:
	.string "{CHN}按住B键，\n"
	.string "你的自行车可以在原地跳跃。\p"
	.string "这个技巧叫做兔子跳。\p"
	.string "你也可以一边跳一边骑。\p"
	.string "想看其他页吗？$"

MauvilleCity_BikeShop_Text_Jumps:
	.string "{CHN}同时按下B键和+控制键\n"
	.string "可以跳跃。\p"
	.string "将+控制键按向侧方\n"
	.string "可以侧向跳跃。\p"
	.string "向后按可以让自行车\n"
	.string "在跳跃时改变方向。\p"
	.string "想看其他页吗？$"
