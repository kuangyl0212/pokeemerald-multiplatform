AbandonedShip_Corridors_1F_MapScripts::
	.byte 0

AbandonedShip_Corridors_1F_EventScript_Youngster::
	msgbox AbandonedShip_Corridors_1F_Text_IsntItFunHere, MSGBOX_NPC
	end

AbandonedShip_Corridors_1F_EventScript_Charlie::
	trainerbattle_single TRAINER_CHARLIE, AbandonedShip_Corridors_1F_Text_CharlieIntro, AbandonedShip_Corridors_1F_Text_CharlieDefeat
	msgbox AbandonedShip_Corridors_1F_Text_CharliePostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Corridors_1F_Text_CharlieIntro:
	.string "{CHN}我把游泳圈带上船\n"
	.string "有什么好笑的？$"

AbandonedShip_Corridors_1F_Text_CharlieDefeat:
	.string "{CHN}哇，你把我压倒了！$"

AbandonedShip_Corridors_1F_Text_CharliePostBattle:
	.string "{CHN}抓着游泳圈的同时\n"
	.string "扔精灵球可不容易！$"

AbandonedShip_Corridors_1F_Text_IsntItFunHere:
	.string "{CHN}这里不是很有趣吗？\n"
	.string "光是待在这里我就很兴奋了！$"
