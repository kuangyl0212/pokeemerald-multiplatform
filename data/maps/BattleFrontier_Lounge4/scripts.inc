BattleFrontier_Lounge4_MapScripts::
	.byte 0

BattleFrontier_Lounge4_EventScript_Woman::
	msgbox BattleFrontier_Lounge4_Text_WonderIfInterviewsAiring, MSGBOX_NPC
	end

BattleFrontier_Lounge4_EventScript_Cook::
	msgbox BattleFrontier_Lounge4_Text_IfIOpenedRestaurantHere, MSGBOX_NPC
	end

BattleFrontier_Lounge4_EventScript_Man::
	msgbox BattleFrontier_Lounge4_Text_NeedBreatherAfterBattles, MSGBOX_NPC
	end

BattleFrontier_Lounge4_Text_WonderIfInterviewsAiring:
	.string "{CHN}不知道今天会不会播出\n"
	.string "强大训练家的采访呢？$"

BattleFrontier_Lounge4_Text_IfIOpenedRestaurantHere:
	.string "{CHN}如果我在这里开一家餐厅，\n"
	.string "肯定能赚钱。$"

BattleFrontier_Lounge4_Text_NeedBreatherAfterBattles:
	.string "{CHN}呼……\p"
	.string "打了几场激烈的对战后，\n"
	.string "我需要喘口气……\p"
	.string "但即使是现在，我也从不停下\n"
	.string "构思策略和组合的功夫。$"

