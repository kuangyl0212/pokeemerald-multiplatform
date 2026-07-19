Route109_SeashoreHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route109_SeashoreHouse_OnTransition
	.byte 0

Route109_SeashoreHouse_OnTransition:
	setflag FLAG_LANDMARK_SEASHORE_HOUSE
	end

Route109_SeashoreHouse_EventScript_Owner::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_6_SODA_POP, Route109_SeashoreHouse_EventScript_AlreadyReceivedSodaPop
	goto_if_set FLAG_DEFEATED_SEASHORE_HOUSE, Route109_SeashoreHouse_EventScript_DefeatedTrainers
	goto_if_set FLAG_TEMP_2, Route109_SeashoreHouse_EventScript_AlreadyGaveIntroduction
	msgbox Route109_SeashoreHouse_Text_SeashoreHouseIntro, MSGBOX_DEFAULT
	setflag FLAG_TEMP_2
	release
	end

Route109_SeashoreHouse_EventScript_AlreadyGaveIntroduction::
	msgbox Route109_SeashoreHouse_Text_ShowMeSomeHotMatches, MSGBOX_DEFAULT
	release
	end

Route109_SeashoreHouse_EventScript_DefeatedTrainers::
	msgbox Route109_SeashoreHouse_Text_TakeTheseSodaPopBottles, MSGBOX_DEFAULT
	giveitem ITEM_SODA_POP, 6
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_BagFull
	setflag FLAG_RECEIVED_6_SODA_POP
	release
	end

Route109_SeashoreHouse_EventScript_BagFull::
	msgbox Route109_SeashoreHouse_Text_BagFull, MSGBOX_DEFAULT
	release
	end

Route109_SeashoreHouse_EventScript_AlreadyReceivedSodaPop::
	showmoneybox 0, 0
	msgbox Route109_SeashoreHouse_Text_WantToBuySodaPop, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route109_SeashoreHouse_EventScript_BuySodaPop
	msgbox Route109_SeashoreHouse_Text_ThatsTooBad, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_BuySodaPop::
	checkmoney 300
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_NotEnoughMoney
	checkitemspace ITEM_SODA_POP
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_NotEnoughSpace
	msgbox Route109_SeashoreHouse_Text_HereYouGo, MSGBOX_DEFAULT
	removemoney 300
	updatemoneybox
	giveitem ITEM_SODA_POP
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_NotEnoughMoney::
	msgbox Route109_SeashoreHouse_Text_NotEnoughMoney, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_NotEnoughSpace::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_Dwayne::
	trainerbattle_single TRAINER_DWAYNE, Route109_SeashoreHouse_Text_DwayneIntro, Route109_SeashoreHouse_Text_DwayneDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_DwaynePostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_Johanna::
	trainerbattle_single TRAINER_JOHANNA, Route109_SeashoreHouse_Text_JohannaIntro, Route109_SeashoreHouse_Text_JohannaDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_JohannaPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_Simon::
	trainerbattle_single TRAINER_SIMON, Route109_SeashoreHouse_Text_SimonIntro, Route109_SeashoreHouse_Text_SimonDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_SimonPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_CheckTrainersCompletion::
	goto_if_not_defeated TRAINER_DWAYNE, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	goto_if_not_defeated TRAINER_JOHANNA, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	goto_if_not_defeated TRAINER_SIMON, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	setflag FLAG_DEFEATED_SEASHORE_HOUSE
	release
	end

Route109_SeashoreHouse_EventScript_TrainersNotCompleted::
	release
	end

Route109_SeashoreHouse_Text_SeashoreHouseIntro:
	.string "{CHN}我是海边小屋的老板。\n"
	.string "但你可以叫我海先生！\p"
	.string "我最喜欢的就是看到\n"
	.string "激烈的宝可梦对战。\p"
	.string "让我看到你火热的心！\p"
	.string "如果你能打败这里所有的\n"
	.string "训练家，我会奖励你的努力。$"

Route109_SeashoreHouse_Text_ShowMeSomeHotMatches:
	.string "{CHN}给我看些激烈的比赛吧！\p"
	.string "我经营这个海边小屋\n"
	.string "就是为了这个原因！$"

Route109_SeashoreHouse_Text_TakeTheseSodaPopBottles:
	.string "{CHN}你热得发烫！\n"
	.string "那些对战太火爆了！\l"
	.string "我非常满意！\p"
	.string "作为你向我展示\n"
	.string "热情的感谢，我要你收下这些。\p"
	.string "这是半打汽水！$"

Route109_SeashoreHouse_Text_BagFull:
	.string "{CHN}哦，但是嘿，你的包塞满了。\n"
	.string "我先替你保管这些。$"

Route109_SeashoreHouse_Text_WantToBuySodaPop:
	.string "{CHN}想买些汽水吗？\n"
	.string "宝可梦很喜欢它！\p"
	.string "只要300元一瓶！\n"
	.string "买一些吧！$"

Route109_SeashoreHouse_Text_HereYouGo:
	.string "{CHN}给你！$"

Route109_SeashoreHouse_Text_NotEnoughMoney:
	.string "{CHN}你的钱不够。$"

Route109_SeashoreHouse_Text_ThatsTooBad:
	.string "{CHN}不买吗？\n"
	.string "那太可惜了。$"

Route109_SeashoreHouse_Text_DwayneIntro:
	.string "{CHN}如果你在海边小屋\n"
	.string "找人对战，你找不到比我更\l"
	.string "热血的训练家了，老兄！$"

Route109_SeashoreHouse_Text_DwayneDefeated:
	.string "{CHN}那是一场激烈的对战！\n"
	.string "我可以接受那个失败，老兄！$"

Route109_SeashoreHouse_Text_DwaynePostBattle:
	.string "{CHN}每当我在凯那市，我都会享受\n"
	.string "激烈的对战和冰凉的汽水！$"

Route109_SeashoreHouse_Text_JohannaIntro:
	.string "{CHN}无聊的对战不值得费力。\p"
	.string "火热激烈的对战才能让\n"
	.string "训练家和宝可梦变强！$"

Route109_SeashoreHouse_Text_JohannaDefeated:
	.string "{CHN}好火热！$"

Route109_SeashoreHouse_Text_JohannaPostBattle:
	.string "{CHN}呼，我好渴。\n"
	.string "也许我该喝瓶汽水。$"

Route109_SeashoreHouse_Text_SimonIntro:
	.string "{CHN}我要让你看看我的宝可梦\n"
	.string "有多厉害，但别哭哦！$"

Route109_SeashoreHouse_Text_SimonDefeated:
	.string "{CHN}……我输了，但我不会哭……$"

Route109_SeashoreHouse_Text_SimonPostBattle:
	.string "{CHN}如果我的宝可梦中有一只会\n"
	.string "那种能驮着我过水面的\l"
	.string "招式，我就可以丢掉这个游泳圈了。$"

