FortreeCity_House4_MapScripts::
	.byte 0

FortreeCity_House4_EventScript_Woman::
	msgbox FortreeCity_House4_Text_BringsWorldCloserTogether, MSGBOX_NPC
	end

FortreeCity_House4_EventScript_Boy::
	lockall
	goto_if_set FLAG_RECEIVED_MENTAL_HERB, FortreeCity_House4_EventScript_ReceivedMentalHerb
	goto_if_set FLAG_WINGULL_DELIVERED_MAIL, FortreeCity_House4_EventScript_WingullReturned
	goto_if_set FLAG_WINGULL_SENT_ON_ERRAND, FortreeCity_House4_EventScript_WingullOnErrand
	msgbox FortreeCity_House4_Text_GoBirdPokemon, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_WINGULL_SENT_ON_ERRAND
	clearflag FLAG_HIDE_MOSSDEEP_CITY_HOUSE_2_WINGULL
	applymovement LOCALID_FORTREE_HOUSE_WINGULL, FortreeCity_House4_Movement_WingullExit
	waitmovement 0
	removeobject LOCALID_FORTREE_HOUSE_WINGULL
	releaseall
	end

FortreeCity_House4_EventScript_WingullOnErrand::
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FortreeCity_House4_Text_AskedWingullToRunErrand, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_House4_EventScript_WingullReturned::
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FortreeCity_House4_Text_WelcomeWingullTakeMentalHerb, MSGBOX_DEFAULT
	giveitem ITEM_MENTAL_HERB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MENTAL_HERB
	releaseall
	end

FortreeCity_House4_EventScript_ReceivedMentalHerb::
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FortreeCity_House4_Text_FriendsFarAwayThanksToWingull, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_House4_Movement_WingullExit:
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_in_place_faster_down
	delay_8
	step_end

FortreeCity_House4_EventScript_Wingull::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
	msgbox FortreeCity_House4_Text_Wingull, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House4_Text_BringsWorldCloserTogether:
	.string "{CHN}通过与宝可梦相伴，\n"
	.string "人们结交了越来越多的朋友。\p"
	.string "这让世界\n"
	.string "更加紧密地联系在一起。我觉得这真是太棒了！$"

FortreeCity_House4_Text_GoBirdPokemon:
	.string "{CHN}去吧！\n"
	.string "去吧，鸟宝可梦！$"

FortreeCity_House4_Text_AskedWingullToRunErrand:
	.string "{CHN}嘿嘿，我让我的长翅鸥\n"
	.string "帮我跑腿去了。$"

FortreeCity_House4_Text_WelcomeWingullTakeMentalHerb:
	.string "{CHN}太好了！\n"
	.string "欢迎回来，长翅鸥！\p"
	.string "咦？这是什么？\n"
	.string "它嘴里叼着什么？\p"
	.string "精神香草？\n"
	.string "一定是在哪儿捡到的。\p"
	.string "但我不是训练家，\n"
	.string "所以这个就给你吧。$"

FortreeCity_House4_Text_FriendsFarAwayThanksToWingull:
	.string "{CHN}多亏了我的长翅鸥，\n"
	.string "我才有远方的朋友。$"

FortreeCity_House4_Text_Wingull:
	.string "{CHN}长翅鸥：皮哟！$"
