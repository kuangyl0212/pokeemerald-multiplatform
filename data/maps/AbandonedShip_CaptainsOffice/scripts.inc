AbandonedShip_CaptainsOffice_MapScripts:: /* 82387E1*/
	.byte 0

AbandonedShip_CaptainsOffice_EventScript_CaptSternAide:: /* 82387E2*/
	lock
	faceplayer
	goto_if_set FLAG_EXCHANGED_SCANNER, AbandonedShip_CaptainsOffice_EventScript_ThisIsSSCactus
	checkitem ITEM_SCANNER
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_CaptainsOffice_EventScript_CanYouDeliverScanner
	goto_if_set FLAG_ITEM_ABANDONED_SHIP_HIDDEN_FLOOR_ROOM_2_SCANNER, AbandonedShip_CaptainsOffice_EventScript_ThisIsSSCactus
	msgbox AbandonedShip_CaptainsOffice_Text_NoSuccessFindingScanner, MSGBOX_DEFAULT
	release
	end

AbandonedShip_CaptainsOffice_EventScript_CanYouDeliverScanner::
	msgbox AbandonedShip_CaptainsOffice_Text_OhCanYouDeliverScanner, MSGBOX_DEFAULT
	release
	end

AbandonedShip_CaptainsOffice_EventScript_ThisIsSSCactus::
	msgbox AbandonedShip_CaptainsOffice_Text_ThisIsSSCactus, MSGBOX_DEFAULT
	release
	end

AbandonedShip_CaptainsOffice_Text_NoSuccessFindingScanner:
	.string "{CHN}我代表史铁伦船长\n"
	.string "调查这艘船。\p"
	.string "他还让我找扫描仪，\n"
	.string "但我一直没有找到……$"

AbandonedShip_CaptainsOffice_Text_OhCanYouDeliverScanner:
	.string "{CHN}哦！那是扫描仪！\p"
	.string "听我说，你能把这个\n"
	.string "交给史铁伦船长吗？\p"
	.string "我想再多调查一下\n"
	.string "这艘船。$"

AbandonedShip_CaptainsOffice_Text_ThisIsSSCactus:
	.string "{CHN}这艘船叫做S.S. CACTUS号。\n"
	.string "看起来是以前时代的船。$"
