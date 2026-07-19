Route116_TunnelersRestHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route116_TunnelersRestHouse_OnTransition
	.byte 0

Route116_TunnelersRestHouse_OnTransition:
	setflag FLAG_LANDMARK_TUNNELERS_REST_HOUSE
	end

Route116_TunnelersRestHouse_EventScript_Tunneler1::
	msgbox Route116_TunnelersRestHouse_Text_WeHadToStopBoring, MSGBOX_NPC
	end

Route116_TunnelersRestHouse_EventScript_Tunneler2::
	msgbox Route116_TunnelersRestHouse_Text_ManDiggingHisWayToVerdanturf, MSGBOX_NPC
	end

Route116_TunnelersRestHouse_EventScript_Tunneler3::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, Route116_TunnelersRestHouse_EventScript_TunnelOpened
	msgbox Route116_TunnelersRestHouse_Text_GetToVerdanturfWithoutTunnel, MSGBOX_DEFAULT
	release
	end

Route116_TunnelersRestHouse_EventScript_TunnelOpened::
	msgbox Route116_TunnelersRestHouse_Text_TunnelHasGoneThrough, MSGBOX_DEFAULT
	release
	end

Route116_TunnelersRestHouse_Text_WeHadToStopBoring:
	.string "{CHN}那边的橙华隧道……\p"
	.string "一开始，我们有一大群工人用最新\n"
	.string "的机械在岩石中钻孔。\l"
	.string "但是，我们不得不停工。\p"
	.string "结果发现我们会对这一带的\n"
	.string "野生宝可梦\l"
	.string "造成负面影响。\p"
	.string "所以，我们无事可做，只能\n"
	.string "在这里闲晃。$"

Route116_TunnelersRestHouse_Text_ManDiggingHisWayToVerdanturf:
	.string "{CHN}有个人正在独自挖通\n"
	.string "到绿荫镇的通道。\l"
	.string "他拼命想要挖通。\p"
	.string "他说如果不用机器，一点一点地挖，\n"
	.string "就不会\l"
	.string "打扰宝可梦，也能避免\l"
	.string "破坏自然环境。\p"
	.string "不知道他挖通了没有。$"

Route116_TunnelersRestHouse_Text_GetToVerdanturfWithoutTunnel:
	.string "{CHN}如果不走这条隧道要到\n"
	.string "绿荫镇，你得先渡海\l"
	.string "去武斗镇，再航行到凯那市，\l"
	.string "然后穿过紫堇市。$"

Route116_TunnelersRestHouse_Text_TunnelHasGoneThrough:
	.string "{CHN}你听说了吗？通往绿荫镇\n"
	.string "的隧道挖通了！\p"
	.string "有时候，如果你足够强烈地期盼，\n"
	.string "梦想真的会实现。$"

