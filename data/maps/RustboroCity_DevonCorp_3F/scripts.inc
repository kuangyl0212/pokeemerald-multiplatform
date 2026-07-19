RustboroCity_DevonCorp_3F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_3F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, RustboroCity_DevonCorp_3F_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RustboroCity_DevonCorp_3F_OnFrame
	.byte 0

RustboroCity_DevonCorp_3F_OnTransition:
	call_if_eq VAR_DEVON_CORP_3F_STATE, 0, RustboroCity_DevonCorp_3F_EventScript_SetEmployeePos
	end

RustboroCity_DevonCorp_3F_EventScript_SetEmployeePos::
	setobjectxyperm LOCALID_DEVON_CORP_3F_EMPLOYEE, 3, 2
	setobjectmovementtype LOCALID_DEVON_CORP_3F_EMPLOYEE, MOVEMENT_TYPE_FACE_LEFT
	return

RustboroCity_DevonCorp_3F_OnWarp:
	map_script_2 VAR_DEVON_CORP_3F_STATE, 0, RustboroCity_DevonCorp_3F_EventScript_PlayerFaceEast
	.short 0

RustboroCity_DevonCorp_3F_EventScript_PlayerFaceEast::
	turnobject LOCALID_PLAYER, DIR_EAST
	end

RustboroCity_DevonCorp_3F_OnFrame:
	map_script_2 VAR_DEVON_CORP_3F_STATE, 0, RustboroCity_DevonCorp_3F_EventScript_MeetPresident
	.short 0

RustboroCity_DevonCorp_3F_EventScript_MeetPresident::
	lockall
	msgbox RustboroCity_DevonCorp_3F_Text_ThisIs3rdFloorWaitHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_EmployeeWalkOffscreen
	waitmovement 0
	delay 80
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_EmployeeReturnToPlayer
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_WordWithPresidentComeWithMe, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_FOLLOW_ME, FALSE
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_LeadPlayerToPresident
	applymovement LOCALID_PLAYER, RustboroCity_DevonCorp_3F_Movement_PlayerFollowToPresident
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_PleaseGoAhead, MSGBOX_DEFAULT
	closemessage
	fadedefaultbgm
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_EmployeeFaceDesk
	applymovement LOCALID_PLAYER, RustboroCity_DevonCorp_3F_Movement_PlayerApproachDesk
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneIHaveFavor, MSGBOX_DEFAULT
	giveitem ITEM_LETTER
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneWantYouToHaveThis, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_3F_Text_ReceivedPokenav
	waitfanfare
	setflag FLAG_SYS_POKENAV_GET
	setflag FLAG_RECEIVED_POKENAV
	setflag FLAG_HIDE_RUSTBORO_CITY_POKEMON_SCHOOL_SCOTT
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneExplainPokenavRestUp, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneGoWithCautionAndCare, MSGBOX_DEFAULT
	setflag FLAG_HIDE_ROUTE_116_WANDAS_BOYFRIEND
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_WANDAS_BOYFRIEND
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_WANDA
	clearflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	clearflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	setvar VAR_BRINEY_LOCATION, 1
	clearflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	setvar VAR_DEVON_CORP_3F_STATE, 1
	setvar VAR_RUSTBORO_CITY_STATE, 6
	releaseall
	end

RustboroCity_DevonCorp_3F_Movement_Unused:
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_left
	step_end

RustboroCity_DevonCorp_3F_Movement_LeadPlayerToPresident:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_left
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeFaceDesk:
	delay_16
	walk_in_place_faster_down
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeWalkOffscreen:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeReturnToPlayer:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_left
	walk_left
	walk_left
	step_end

RustboroCity_DevonCorp_3F_Movement_PlayerFollowToPresident:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RustboroCity_DevonCorp_3F_Movement_PlayerApproachDesk:
	delay_16
	delay_16
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

RustboroCity_DevonCorp_3F_EventScript_MrStone::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_EXP_SHARE, RustboroCity_DevonCorp_3F_EventScript_MrStoneAfterFavor
	goto_if_set FLAG_DELIVERED_STEVEN_LETTER, RustboroCity_DevonCorp_3F_EventScript_GiveExpShare
	msgbox RustboroCity_DevonCorp_3F_Text_CountingOnYou, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_GiveExpShare::
	msgbox RustboroCity_DevonCorp_3F_Text_ThankYouForDeliveringLetter, MSGBOX_DEFAULT
	giveitem ITEM_EXP_SHARE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_EXP_SHARE
	msgbox RustboroCity_DevonCorp_3F_Text_ExplainExpShare, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_MrStoneAfterFavor::
	msgbox RustboroCity_DevonCorp_3F_Text_NotFamiliarWithTrends, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_Employee::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_REPEAT_BALL, RustboroCity_DevonCorp_3F_EventScript_EmployeeBalls
	msgbox RustboroCity_DevonCorp_3F_Text_VisitCaptSternShipyard, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_3F_EventScript_EmployeeBalls::
	msgbox RustboroCity_DevonCorp_3F_Text_RepeatAndTimerHugelyPopular, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_3F_EventScript_RareRocksDisplay::
	msgbox RustboroCity_DevonCorp_3F_Text_RareRocksDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_3F_Text_MrStoneIHaveFavor:
	.string "{CHN}我是得文公司的总裁，\n"
	.string "斯通先生。\p"
	.string "我刚刚听说了你的事！\p"
	.string "你救了我们的员工，\n"
	.string "不是一次，而是两次！\p"
	.string "我想请你这样了不起的人\n"
	.string "帮个忙。\p"
	.string "我知道你要把货物送到\n"
	.string "凯那市的造船厂。\p"
	.string "那么，途中能不能顺路\n"
	.string "去一趟武斗镇？\p"
	.string "我希望你能把一封信\n"
	.string "送到武斗镇的大吾那里。$"

RustboroCity_DevonCorp_3F_Text_MrStoneWantYouToHaveThis:
	.string "{CHN}斯通先生：嗯，你要知道，\n"
	.string "我可是个伟大的总裁。\p"
	.string "所以，我绝不会小气到\n"
	.string "让你白白帮忙。\p"
	.string "所以，我希望你收下这个！$"

RustboroCity_DevonCorp_3F_Text_ReceivedPokenav:
	.string "{CHN}{PLAYER}得到了宝可领航员。$"

RustboroCity_DevonCorp_3F_Text_MrStoneExplainPokenavRestUp:
	.string "{CHN}斯通先生：那个装置……\p"
	.string "是宝可梦导航器，\n"
	.string "简称宝可领航员。\p"
	.string "对踏上冒险旅程的训练家来说，\n"
	.string "它是不可或缺的工具。\p"
	.string "它有丰缘地区的地图。\p"
	.string "你可以轻松查看\n"
	.string "武斗镇和凯那市的位置！\p"
	.string "对了，我听说有些邪恶的犯罪分子\n"
	.string "——好像是叫火焰队和水舰队——\l"
	.string "到处惹是生非。\p"
	.string "我想你最好在出发前\n"
	.string "好好休息一下。$"

RustboroCity_DevonCorp_3F_Text_MrStoneGoWithCautionAndCare:
	.string "{CHN}斯通先生：那么，{PLAYER}{KUN}，\n"
	.string "路上小心！$"

RustboroCity_DevonCorp_3F_Text_CountingOnYou:
	.string "{CHN}斯通先生：拜托你了！$"

RustboroCity_DevonCorp_3F_Text_ThankYouForDeliveringLetter:
	.string "{CHN}斯通先生：你把我的信送到了？\n"
	.string "太感谢了！\p"
	.string "这是我的一点心意。\n"
	.string "它应该能帮到你这样的训练家。$"

RustboroCity_DevonCorp_3F_Text_ExplainExpShare:
	.string "{CHN}斯通先生：携带经验分享的宝可梦\n"
	.string "能从战斗中获得一部分\l"
	.string "经验值。\p"
	.string "即使它没有真正参战，\n"
	.string "也能获得经验值。\p"
	.string "我觉得经验分享对培养\n"
	.string "弱小的宝可梦非常有用。$"

RustboroCity_DevonCorp_3F_Text_NotFamiliarWithTrends:
	.string "{CHN}斯通先生：从年轻时起，\n"
	.string "我就埋头于工作。\p"
	.string "因此，我对流行趋势\n"
	.string "之类的东西不太了解。\p"
	.string "不过，年轻人都想成为\n"
	.string "宝可梦联盟的训练家吗？$"

RustboroCity_DevonCorp_3F_Text_ThisIs3rdFloorWaitHere:
	.string "{CHN}这里是得文公司的三楼。\p"
	.string "我们总裁的办公室\n"
	.string "就在这层。\p"
	.string "总之，我无法用言语表达\n"
	.string "对你的感谢。\p"
	.string "嗯……对了，你帮我们\n"
	.string "抢回来的那个包裹……\p"
	.string "能不能麻烦你把它送到\n"
	.string "凯那市的造船厂？\p"
	.string "要是那些强盗再来抢\n"
	.string "就糟糕了。\p"
	.string "呃……嘿嘿嘿，那么，呃，\n"
	.string "能拜托你吗？\p"
	.string "啊，对了。\n"
	.string "你能在这里稍等一下吗？$"

RustboroCity_DevonCorp_3F_Text_WordWithPresidentComeWithMe:
	.string "{CHN}我们总裁想跟你说几句话。\p"
	.string "请跟我来。$"

RustboroCity_DevonCorp_3F_Text_PleaseGoAhead:
	.string "{CHN}请进。$"

RustboroCity_DevonCorp_3F_Text_VisitCaptSternShipyard:
	.string "{CHN}如果你去凯那市的造船厂，\n"
	.string "应该去见见斯特恩船长。$"

RustboroCity_DevonCorp_3F_Text_RepeatAndTimerHugelyPopular:
	.string "{CHN}得文的新产品重复球\n"
	.string "和计时球在训练家之间\l"
	.string "大受欢迎。$"

RustboroCity_DevonCorp_3F_Text_RareRocksDisplay:
	.string "{CHN}这是总裁收集的\n"
	.string "珍奇岩石和石头的展览。$"

