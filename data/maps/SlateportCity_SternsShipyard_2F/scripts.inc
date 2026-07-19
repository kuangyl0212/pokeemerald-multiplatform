SlateportCity_SternsShipyard_2F_MapScripts::
	.byte 0

SlateportCity_SternsShipyard_2F_EventScript_Scientist1::
	msgbox SlateportCity_SternsShipyard_2F_Text_ShipDesignMoreLikeBuilding, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_2F_EventScript_Scientist2::
	msgbox SlateportCity_SternsShipyard_2F_Text_FloatsBecauseBuoyancy, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_2F_Text_ShipDesignMoreLikeBuilding:
	.string "{CHN}设计大船更像是\n"
	.string "建造大楼，而不是\l"
	.string "组装交通工具。$"

SlateportCity_SternsShipyard_2F_Text_FloatsBecauseBuoyancy:
	.string "{CHN}你不觉得奇怪吗？\n"
	.string "铁做的重船能浮在水上？\p"
	.string "它能浮起来是因为一个\n"
	.string "叫做浮力的原理。$"

