Route104_MrBrineysHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route104_MrBrineysHouse_OnTransition
	.byte 0

Route104_MrBrineysHouse_OnTransition:
	setflag FLAG_LANDMARK_MR_BRINEY_HOUSE
	call_if_eq VAR_BRINEY_HOUSE_STATE, 1, Route104_MrBrineysHouse_EventScript_SetBrineyPeekoPos
	call_if_set FLAG_RECEIVED_POKENAV, Route104_MrBrineysHouse_EventScript_HideRustboroRival
	end

Route104_MrBrineysHouse_EventScript_HideRustboroRival::
	setflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	return

Route104_MrBrineysHouse_EventScript_SetBrineyPeekoPos::
	setobjectxyperm LOCALID_BRINEYS_HOUSE_BRINEY, 9, 3
	setobjectmovementtype LOCALID_BRINEYS_HOUSE_BRINEY, MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_UP_RIGHT
	setobjectxyperm LOCALID_BRINEYS_HOUSE_PEEKO, 9, 6
	setobjectmovementtype LOCALID_BRINEYS_HOUSE_PEEKO, MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_RIGHT_DOWN
	return

Route104_MrBrineysHouse_EventScript_Briney::
	lock
	faceplayer
	call_if_unset FLAG_MR_BRINEY_SAILING_INTRO, Route104_MrBrineysHouse_EventScript_SailingIntro
	goto_if_unset FLAG_DELIVERED_STEVEN_LETTER, Route104_MrBrineysHouse_EventScript_SailBothDeliveries
	goto_if_unset FLAG_DELIVERED_DEVON_GOODS, Route104_MrBrineysHouse_EventScript_SailDeliverPackage
	goto Route104_MrBrineysHouse_EventScript_WhereAreWeBound
	end

Route104_MrBrineysHouse_EventScript_SailingIntro::
	setflag FLAG_MR_BRINEY_SAILING_INTRO
	msgbox Route104_MrBrineysHouse_Text_WaitUpPeeko, MSGBOX_DEFAULT
	msgbox Route104_MrBrineysHouse_Text_ItsYouLetsSailToDewford, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing
	goto Route104_MrBrineysHouse_EventScript_SailToDewford
	end

Route104_MrBrineysHouse_EventScript_WhereAreWeBound::
	message Route104_MrBrineysHouse_Text_WhereAreWeBound
	waitmessage
	multichoicedefault 20, 8, MULTI_BRINEY_OFF_DEWFORD, 1, FALSE
	switch VAR_RESULT
	case 0, Route104_MrBrineysHouse_EventScript_SailToDewford
	case 1, Route104_MrBrineysHouse_EventScript_DeclineSailing
	case MULTI_B_PRESSED, Route104_MrBrineysHouse_EventScript_DeclineSailing
	end

Route104_MrBrineysHouse_EventScript_SailBothDeliveries::
	msgbox Route104_MrBrineysHouse_Text_NeedToMakeDeliveriesSailToDewford, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing
	goto Route104_MrBrineysHouse_EventScript_SailToDewford
	end

Route104_MrBrineysHouse_EventScript_SailDeliverPackage::
	msgbox Route104_MrBrineysHouse_Text_NeedToDeliverPackageSailToDewford, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing
	goto Route104_MrBrineysHouse_EventScript_SailToDewford
	end

Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing::
	msgbox Route104_MrBrineysHouse_Text_DeclineDeliverySail, MSGBOX_DEFAULT
	release
	end

Route104_MrBrineysHouse_EventScript_DeclineSailing::
	msgbox Route104_MrBrineysHouse_Text_TellMeWheneverYouWantToSail, MSGBOX_DEFAULT
	release
	end

Route104_MrBrineysHouse_EventScript_SailToDewford::
	msgbox Route104_MrBrineysHouse_Text_SetSailForDewford, MSGBOX_DEFAULT
	call EventScript_BackupMrBrineyLocation
	setvar VAR_BOARD_BRINEY_BOAT_STATE, 1
	clearflag FLAG_HIDE_ROUTE_104_MR_BRINEY
	setflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	setflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	setvar VAR_RUSTBORO_CITY_STATE, 8
	setvar VAR_ROUTE104_STATE, 2
	setflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	setflag FLAG_HIDE_ROUTE_104_RIVAL
	warp MAP_ROUTE104, 13, 51
	waitstate
	releaseall
	end

Route104_MrBrineysHouse_EventScript_Peeko::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
	msgbox Route104_MrBrineysHouse_Text_Peeko, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route104_MrBrineysHouse_Text_WaitUpPeeko:
	.string "{CHN}布里内先生：等等，小姑娘！\n"
	.string "等等，皮皮科！$"

Route104_MrBrineysHouse_Text_ItsYouLetsSailToDewford:
	.string "{CHN}嗯？你是{PLAYER}{KUN}！\n"
	.string "你救了我的宝贝皮皮科！\l"
	.string "我们欠你一份大恩情！\p"
	.string "什么？\n"
	.string "你想和我一起航海？\p"
	.string"嗯嗯……\p"
	.string "你有一封要送到武斗镇的信，\n"
	.string "还有一件要送到凯那市的包裹，是吗？\p"
	.string "看来你过得挺忙碌的啊！\p"
	.string "不过，你说的这件事\n"
	.string "完全没问题。\p"
	.string "你找对人了！\n"
	.string "我们这就起航去武斗镇吧。$"

Route104_MrBrineysHouse_Text_SetSailForDewford:
	.string "{CHN}布里内先生：那就去武斗镇吧！\p"
	.string "起锚！\n"
	.string "皮皮科，我们要起航了，宝贝！$"

Route104_MrBrineysHouse_Text_DeclineDeliverySail:
	.string "{CHN}布里内先生：是吗？\n"
	.string "你的东西不急着送？\p"
	.string "你想什么时候\n"
	.string "起航就告诉我！$"

Route104_MrBrineysHouse_Text_NeedToMakeDeliveriesSailToDewford:
	.string "{CHN}布里内先生：哦吼！\n"
	.string "我完全知道你想说什么！\p"
	.string "你要把一封信送到武斗镇，\n"
	.string "还要把一件包裹送到凯那市。\p"
	.string "你要我做的事\n"
	.string "完全没问题——交给我吧！\p"
	.string "首先，我们起航去武斗镇。$"

Route104_MrBrineysHouse_Text_NeedToDeliverPackageSailToDewford:
	.string "{CHN}布里内先生：哦吼！\n"
	.string "我完全知道你想说什么！\p"
	.string "你要把一件包裹送到\n"
	.string "凯那市的史特龙船长那里。\p"
	.string "你要我做的事\n"
	.string "完全没问题——交给我吧！\p"
	.string "首先，我们起航去武斗镇。$"

Route104_MrBrineysHouse_Text_WhereAreWeBound:
	.string "{CHN}布里内先生：哦吼！\n"
	.string "为了你，我随时都愿意出海！\p"
	.string "那么，朋友，我们要去哪里？$"

Route104_MrBrineysHouse_Text_TellMeWheneverYouWantToSail:
	.string "{CHN}布里内先生：是吗？\n"
	.string "皮皮科的命可是你救的。\p"
	.string "你想什么时候\n"
	.string "起航就告诉我！$"

Route104_MrBrineysHouse_Text_Peeko:
	.string "{CHN}皮皮科：皮皮皮皮咯！$"

