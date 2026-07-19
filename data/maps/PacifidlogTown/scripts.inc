PacifidlogTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PacifidlogTown_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, PacifidlogTown_OnResume
	.byte 0

PacifidlogTown_OnTransition:
	setflag FLAG_VISITED_PACIFIDLOG_TOWN
	end

PacifidlogTown_OnResume:
	setstepcallback STEP_CB_PACIFIDLOG_BRIDGE
	end

PacifidlogTown_EventScript_NinjaBoy::
	msgbox PacifidlogTown_Text_NeatHousesOnWater, MSGBOX_NPC
	end

PacifidlogTown_EventScript_Girl::
	msgbox PacifidlogTown_Text_FastRunningCurrent, MSGBOX_NPC
	end

PacifidlogTown_EventScript_Fisherman::
	msgbox PacifidlogTown_Text_SkyPillarTooScary, MSGBOX_NPC
	end

PacifidlogTown_EventScript_TownSign::
	msgbox PacifidlogTown_Text_TownSign, MSGBOX_SIGN
	end

PacifidlogTown_Text_FastRunningCurrent:
	.string "{CHN}凯那吉镇和\n"
	.string "凯那市之间的海域潮水流动很快。\p"
	.string "如果你决定冲浪，可能会被\n"
	.string "冲到其他地方去哦。$"

PacifidlogTown_Text_NeatHousesOnWater:
	.string "{CHN}看，是不是很棒？\n"
	.string "这些房子都建在水上！\p"
	.string "我就出生在这里！$"

PacifidlogTown_Text_SkyPillarTooScary:
	.string "{CHN}天空之柱？\p"
	.string "……哦，你一定是说再远一点的\n"
	.string "那座高高耸立的塔吧。\p"
	.string "要我说，我可不会爬上去。\n"
	.string "爬到那么高太可怕了。\p"
	.string "在凯那吉镇的海平面上生活，\n"
	.string "那才适合我。$"

PacifidlogTown_Text_TownSign:
	.string "{CHN}凯那吉镇\p"
	.string "“晨曦的阳光\n"
	.string "在水面上微笑。”$"
