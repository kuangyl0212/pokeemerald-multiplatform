Route111_OldLadysRestStop_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route111_OldLadysRestStop_OnTransition
	.byte 0

Route111_OldLadysRestStop_OnTransition:
	setflag FLAG_LANDMARK_OLD_LADY_REST_SHOP
	end

Route111_OldLadysRestStop_EventScript_OldLady::
	lock
	faceplayer
	msgbox Route111_OldLadysRestStop_Text_RestUpHere, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route111_OldLadysRestStop_EventScript_Rest
	goto_if_eq VAR_RESULT, NO, Route111_OldLadysRestStop_EventScript_DeclineRest
	end

Route111_OldLadysRestStop_EventScript_Rest::
	msgbox Route111_OldLadysRestStop_Text_TakeYourTimeRestUp, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox Route111_OldLadysRestStop_Text_StillTiredTakeAnotherRest, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route111_OldLadysRestStop_EventScript_Rest
	goto_if_eq VAR_RESULT, NO, Route111_OldLadysRestStop_EventScript_DeclineRest
	end

Route111_OldLadysRestStop_EventScript_DeclineRest::
	msgbox Route111_OldLadysRestStop_Text_DontNeedToBeShy, MSGBOX_DEFAULT
	release
	end

Route111_OldLadysRestStop_Text_RestUpHere:
	.string "{CHN}哎呀，哎呀。\n"
	.string "你的宝可梦不是累坏了吗？\p"
	.string "如果你想的话，就在这里休息一下吧。\n"
	.string "这是个好主意！你应该这么做。$"

Route111_OldLadysRestStop_Text_TakeYourTimeRestUp:
	.string "{CHN}这就对了。\n"
	.string "慢慢来，好好休息！$"

Route111_OldLadysRestStop_Text_StillTiredTakeAnotherRest:
	.string "{CHN}哎呀，哎呀。\n"
	.string "你的宝可梦还是累吗？\p"
	.string "你应该再在这里休息一次。\n"
	.string "这是个好主意。你应该这么做。$"

Route111_OldLadysRestStop_Text_DontNeedToBeShy:
	.string "{CHN}是这样吗？\n"
	.string "你不用觉得不好意思。$"

