SootopolisCity_House6_MapScripts::
	.byte 0

SootopolisCity_House6_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_WAILMER_DOLL, SootopolisCity_House6_EventScript_ReceivedWailmerDoll
	msgbox SootopolisCity_House6_Text_FirstGuestInWhileTakeDoll, MSGBOX_YESNO
	call_if_eq VAR_RESULT, NO, SootopolisCity_House6_EventScript_DeclineWailmerDoll
	msgbox SootopolisCity_House6_Text_TakeGoodCareOfIt, MSGBOX_DEFAULT
	givedecoration DECOR_WAILMER_DOLL
	goto_if_eq VAR_RESULT, FALSE, SootopolisCity_House6_EventScript_NoRoomForWailmerDoll
	setflag FLAG_RECEIVED_WAILMER_DOLL
	release
	end

SootopolisCity_House6_EventScript_DeclineWailmerDoll::
	msgbox SootopolisCity_House6_Text_DontWantThisDoll, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House6_EventScript_ReceivedWailmerDoll::
	msgbox SootopolisCity_House6_Text_LovePlushDolls, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House6_EventScript_NoRoomForWailmerDoll::
	bufferdecorationname STR_VAR_2, DECOR_WAILMER_DOLL
	msgbox gText_NoRoomLeftForAnother, MSGBOX_DEFAULT
	msgbox SootopolisCity_House6_Text_IllHoldItForYou, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House6_Text_FirstGuestInWhileTakeDoll:
	.string "{CHN}你好！你是我们好久以来\n"
	.string "的第一位客人。\p"
	.string "你让我今天心情大好，\n"
	.string "所以我要送你一个吼鲸王布偶。$"

SootopolisCity_House6_Text_TakeGoodCareOfIt:
	.string "{CHN}要好好照顾它哦！$"

SootopolisCity_House6_Text_IllHoldItForYou:
	.string "{CHN}哦，你想要，但不是现在？\n"
	.string "好吧，那我就先替你保管。$"

SootopolisCity_House6_Text_DontWantThisDoll:
	.string "{CHN}你确定吗？\n"
	.string "你不想要这个布偶吗？$"

SootopolisCity_House6_Text_LovePlushDolls:
	.string "{CHN}我喜欢毛绒布偶！$"

