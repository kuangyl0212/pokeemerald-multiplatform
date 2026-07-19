Route114_FossilManiacsHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_FossilManiacsHouse_OnTransition
	.byte 0

Route114_FossilManiacsHouse_OnTransition:
	setflag FLAG_LANDMARK_FOSSIL_MANIACS_HOUSE
	end

Route114_FossilManiacsHouse_EventScript_FossilManiacsBrother::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_DIG, Route114_FossilManiacsHouse_EventScript_ReceivedDig
	msgbox Route114_FossilManiacsHouse_Text_HaveThisToDigLikeMyBrother, MSGBOX_DEFAULT
	giveitem ITEM_TM_DIG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_DIG
	release
	end

Route114_FossilManiacsHouse_EventScript_ReceivedDig::
	msgbox Route114_FossilManiacsHouse_Text_DigReturnsYouToEntrance, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsHouse_EventScript_RockDisplay::
	msgbox Route114_FossilManiacsHouse_Text_RocksFillDisplayCase, MSGBOX_SIGN
	end

Route114_FossilManiacsHouse_EventScript_Bookshelf::
	msgbox Route114_FossilManiacsHouse_Text_CrammedWithBooks, MSGBOX_SIGN
	end

Route114_FossilManiacsHouse_Text_HaveThisToDigLikeMyBrother:
	.string "{CHN}我大哥是化石狂人……\n"
	.string "他是个喜欢化石的好人……\p"
	.string "他也喜欢挖洞……\n"
	.string "这个洞就是他自己挖的……\p"
	.string "这个给你，这样你也能像我大哥\n"
	.string "一样挖洞……$"

Route114_FossilManiacsHouse_Text_DigReturnsYouToEntrance:
	.string "{CHN}如果你让宝可梦在洞窟里使用挖洞，\n"
	.string "你就会被送回入口……$"

Route114_FossilManiacsHouse_Text_RocksFillDisplayCase:
	.string "{CHN}展示柜里装满了\n"
	.string "形状奇特的岩石……$"

Route114_FossilManiacsHouse_Text_CrammedWithBooks:
	.string "{CHN}地层的构成……\n"
	.string "雨水如何塑造大地……\l"
	.string "石头、土壤和岩石……\p"
	.string "塞满了各种书籍。$"

