SlateportCity_House_MapScripts::
	.byte 0

SlateportCity_House_EventScript_PokefanM::
	msgbox SlateportCity_House_Text_NatureToDoWithStatGains, MSGBOX_NPC
	end

SlateportCity_House_EventScript_Girl::
	msgbox SlateportCity_House_Text_MustBeGoingToBattleTent, MSGBOX_NPC
	end

SlateportCity_House_Text_NatureToDoWithStatGains:
	.string "{CHN}我的宝可梦是急躁性格。\p"
	.string "它的速度比我\n"
	.string "其他宝可梦高。\p"
	.string "也许它们的性格和\n"
	.string "宝可梦的能力成长有关。$"

SlateportCity_House_Text_MustBeGoingToBattleTent:
	.string "{CHN}你是训练家，对吧？\p"
	.string "既然你来了凯那市，\n"
	.string "那你一定是去对战帐篷吧。$"

