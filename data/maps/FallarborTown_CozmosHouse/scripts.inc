FallarborTown_CozmosHouse_MapScripts::
	.byte 0

FallarborTown_CozmosHouse_EventScript_ProfCozmo::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_RETURN, FallarborTown_CozmosHouse_EventScript_GaveMeteorite
	checkitem ITEM_METEORITE
	goto_if_eq VAR_RESULT, TRUE, FallarborTown_CozmosHouse_EventScript_PlayerHasMeteorite
	msgbox FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_PlayerHasMeteorite::
	call_if_unset FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_NoticeMeteorite
	call_if_set FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_AskForMeteorite
	goto_if_eq VAR_RESULT, NO, FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite
	msgbox FallarborTown_CozmosHouse_Text_PleaseUseThisTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_RETURN
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_0x8004, ITEM_METEORITE
	call Common_EventScript_PlayerHandedOverTheItem
	setflag FLAG_RECEIVED_TM_RETURN
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_NoticeMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow, MSGBOX_DEFAULT
	msgbox FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_AskForMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_MayIHaveMeteorite, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite::
	setflag FLAG_TEMP_2
	msgbox FallarborTown_CozmosHouse_Text_CrushedWithDisappointment, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_GaveMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmosWife::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_RETURN, FallarborTown_CozmosHouse_EventScript_CozmoIsHappy
	goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FallarborTown_CozmosHouse_EventScript_CozmoIsSad
	msgbox FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsSad::
	msgbox FallarborTown_CozmosHouse_Text_FeelSorryForCozmo, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsHappy::
	msgbox FallarborTown_CozmosHouse_Text_CozmoIsSoHappy, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow:
	.string "{CHN}小岭博士：哦……\n"
	.string "我不该让自己\l"
	.string "被诱骗告诉熔岩队\l"
	.string "在哪里能找到陨石……\p"
	.string "那块从流星瀑布来的陨石……\n"
	.string "现在永远也不会是我的了……$"

FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt:
	.string "{CHN}哦！\n"
	.string "嗯？\p"
	.string "那个东西……\p"
	.string "难道是？\p"
	.string "那是熔岩队从流星瀑布\n"
	.string "拿走的陨石吗？\p"
	.string "求你了，能给我吗？\p"
	.string "我不是白要的。\n"
	.string "用这个招式学习器交换怎么样？$"

FallarborTown_CozmosHouse_Text_PleaseUseThisTM:
	.string "{CHN}小岭博士：这个招式学习器，代表\n"
	.string "我的感激之情。\l"
	.string "请使用它！$"

FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch:
	.string "{CHN}小岭博士：哦，我简直不敢相信。\n"
	.string "这真是太棒了！\p"
	.string "这对我的研究真的很有帮助！$"

FallarborTown_CozmosHouse_Text_CrushedWithDisappointment:
	.string "{CHN}小岭博士：哦，可是……\n"
	.string "我失望得要命……$"

FallarborTown_CozmosHouse_Text_MayIHaveMeteorite:
	.string "{CHN}小岭博士：求你了，能把那块\n"
	.string "陨石给我吗？\p"
	.string "我不是白要的。\n"
	.string "用这个招式学习器交换怎么样？$"

FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls:
	.string "{CHN}小岭博士和熔岩队的人\n"
	.string "一起去了114号道路的\l"
	.string "流星瀑布。$"

FallarborTown_CozmosHouse_Text_FeelSorryForCozmo:
	.string "{CHN}可怜的小岭博士……\n"
	.string "他那么沮丧……我真替他难过。$"

FallarborTown_CozmosHouse_Text_CozmoIsSoHappy:
	.string "{CHN}看看小岭博士……\n"
	.string "他多开心啊！我觉得真可爱。$"
