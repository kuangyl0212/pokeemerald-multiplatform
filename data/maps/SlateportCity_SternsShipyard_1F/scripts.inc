SlateportCity_SternsShipyard_1F_MapScripts::
	.byte 0

SlateportCity_SternsShipyard_1F_EventScript_Dock::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_SternsShipyard_1F_EventScript_FerryReady
	goto_if_set FLAG_BADGE07_GET, SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined
	goto_if_set FLAG_DELIVERED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran
	goto_if_set FLAG_DOCK_REJECTED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_GoFindStern
	msgbox SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails, MSGBOX_DEFAULT
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_DOCK_REJECTED_DEVON_GOODS
	setflag FLAG_HIDE_SLATEPORT_CITY_TEAM_AQUA
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_FerryReady::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_FerryIsReady, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_GoFindStern::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist1::
	msgbox SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist2::
	msgbox SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Briney::
	msgbox SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails:
	.string "{CHN}嗯…如果这个放这里，那个\n"
	.string "放在那里…\p"
	.string "那这个东西放哪？\n"
	.string "那个玩意儿呢？\p"
	.string "啊！我完全\n"
	.string "搞不懂了！$"

SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern:
	.string "{CHN}嗯？\n"
	.string "嗨，我是多克。\p"
	.string "帅哥船长委托我\n"
	.string "设计一艘渡轮。\p"
	.string "哦！那个…\n"
	.string "是得文货物吗？\p"
	.string "但是，嗯…\n"
	.string "这样不行…\p"
	.string "帅哥船长去哪里了。\n"
	.string "他说他有些工作要做。\p"
	.string "能不能麻烦你去找到\n"
	.string "帅哥船长把这个交给他？$"

SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern:
	.string "{CHN}多克：帅哥船长会去\n"
	.string "哪里呢？\p"
	.string "能不能麻烦你去找到\n"
	.string "帅哥船长把包裹交给他？$"

SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran:
	.string "{CHN}多克：造船是一门艺术。\p"
	.string "很多东西不是\n"
	.string "光靠计算就能搞懂的。\p"
	.string "我真的需要一位了解大海的\n"
	.string "老手给我建议…$"

SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs:
	.string "{CHN}多克：嗨！布莱利先生来\n"
	.string "帮我们了。\p"
	.string "多亏了这位老水手，\n"
	.string "渡轮正在稳步建造中。$"

SlateportCity_SternsShipyard_1F_Text_FerryIsReady:
	.string "{CHN}多克：渡轮终于完工了！\p"
	.string "新的破浪号真是\n"
	.string "技术的奇迹！\p"
	.string "但是，我觉得我们还能\n"
	.string "造出更好的东西。\p"
	.string "你知道的，技术的进步\n"
	.string "永远不会停止。$"

SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock:
	.string "{CHN}布莱利先生：啊，{PLAYER}{KUN}！\n"
	.string "好久不见了！\p"
	.string "是啊，自从遇见你，这把老骨头\n"
	.string "又精神起来了！\p"
	.string "所以我决定帮多克\n"
	.string "造一艘渡轮。\p"
	.string "是啊，毕竟渡轮能\n"
	.string "载很多人。\p"
	.string "但是，你知道，那个多克真的很\n"
	.string "了不起。\p"
	.string "凭借他的技术天赋和\n"
	.string "我的经验，我相信我们能\l"
	.string "造出一艘好船，没错！$"

SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing:
	.string "{CHN}季节、天气、月亮\n"
	.string "在天空中的位置…\p"
	.string "这些和其他条件让\n"
	.string "大海改变了表情。\p"
	.string "没错！\n"
	.string "大海就像一个活物！$"

SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily:
	.string "{CHN}我很容易晕船。\n"
	.string "所以我就在这里帮忙了。$"

