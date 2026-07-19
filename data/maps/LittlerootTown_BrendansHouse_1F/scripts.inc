LittlerootTown_BrendansHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, LittlerootTown_BrendansHouse_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_BrendansHouse_1F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_BrendansHouse_1F_OnFrame
	.byte 0

LittlerootTown_BrendansHouse_1F_OnLoad:
	call_if_lt VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_SetMovingBoxes
	call_if_set FLAG_RECEIVED_RUNNING_SHOES, LittlerootTown_BrendansHouse_1F_EventScript_CheckShowShoesManual
	end

LittlerootTown_BrendansHouse_1F_EventScript_SetMovingBoxes::
	setmetatile 5, 4, METATILE_BrendansMaysHouse_MovingBox_Open, TRUE
	setmetatile 5, 2, METATILE_BrendansMaysHouse_MovingBox_Closed, TRUE
	return

LittlerootTown_BrendansHouse_1F_EventScript_CheckShowShoesManual::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual
	return

LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual::
	setmetatile 3, 7, METATILE_BrendansMaysHouse_BookOnTable, TRUE
	return

LittlerootTown_BrendansHouse_1F_OnTransition:
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 3, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToDoor
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 5, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToStairs
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToTV
	end

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToStairs::
	setobjectxyperm LOCALID_PLAYERS_HOUSE_1F_MOM, 8, 4
	setobjectmovementtype LOCALID_PLAYERS_HOUSE_1F_MOM, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToTV::
	setobjectxyperm LOCALID_PLAYERS_HOUSE_1F_MOM, 4, 5
	setobjectmovementtype LOCALID_PLAYERS_HOUSE_1F_MOM, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToDoor::
	setobjectxyperm LOCALID_PLAYERS_HOUSE_1F_MOM, 9, 8
	setobjectmovementtype LOCALID_PLAYERS_HOUSE_1F_MOM, MOVEMENT_TYPE_FACE_UP
	return

/* Many of the below scripts have no gender check because they assume youre in the correct house*/
/* The below SS Ticket script uses Mays house state by accident(?), but theyre both set identically after the intro*/
LittlerootTown_BrendansHouse_1F_OnFrame:
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 3, LittlerootTown_BrendansHouse_1F_EventScript_EnterHouseMovingIn
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 5, LittlerootTown_BrendansHouse_1F_EventScript_GoUpstairsToSetClock
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_PetalburgGymReport
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_MAY, 1, LittlerootTown_BrendansHouse_1F_EventScript_YoureNewNeighbor
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_MAY, 3, PlayersHouse_1F_EventScript_GetSSTicketAndSeeLatiTV
	.short 0

LittlerootTown_BrendansHouse_1F_EventScript_GoUpstairsToSetClock::
	lockall
	msgbox PlayersHouse_1F_Text_GoSetTheClock, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs
	applymovement LOCALID_PLAYERS_HOUSE_1F_MOM, LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs
	waitmovement 0
	warp MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F, 7, 1
	waitstate
	releaseall
	end

LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs:
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_EnterHouseMovingIn::
	lockall
	setvar VAR_0x8004, LOCALID_PLAYERS_HOUSE_1F_MOM
	setvar VAR_0x8005, MALE
	goto PlayersHouse_1F_EventScript_EnterHouseMovingIn
	end

LittlerootTown_BrendansHouse_1F_EventScript_PetalburgGymReport::
	lockall
	setvar VAR_0x8004, MALE
	setvar VAR_0x8005, LOCALID_PLAYERS_HOUSE_1F_MOM
	goto PlayersHouse_1F_EventScript_PetalburgGymReportMale
	end

LittlerootTown_BrendansHouse_1F_EventScript_YoureNewNeighbor::
	lockall
	playse SE_PIN
	applymovement LOCALID_RIVALS_HOUSE_1F_MOM, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVALS_HOUSE_1F_MOM, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_RIVALS_HOUSE_1F_MOM, LittlerootTown_BrendansHouse_1F_Movement_RivalMomApproach
	waitmovement 0
	special GetRivalSonDaughterString
	msgbox RivalsHouse_1F_Text_OhYoureTheNewNeighbor, MSGBOX_DEFAULT
	setflag FLAG_MET_RIVAL_MOM
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 2
	releaseall
	end

LittlerootTown_BrendansHouse_1F_Movement_RivalMomApproach:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_GoSeeRoom::
	lockall
	setvar VAR_0x8004, LOCALID_PLAYERS_HOUSE_1F_MOM
	setvar VAR_0x8005, MALE
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	goto PlayersHouse_1F_EventScript_MomGoSeeRoom
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival0::
	lockall
	setvar VAR_0x8008, 0
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival1::
	lockall
	setvar VAR_0x8008, 1
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival2::
	lockall
	setvar VAR_0x8008, 2
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival::
	playse SE_EXIT
	delay 10
	addobject LOCALID_RIVALS_HOUSE_1F_RIVAL
	delay 30
	playse SE_PIN
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call_if_ne VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_PlayerFaceBrendan
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	call_if_eq VAR_0x8008, 0, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer0
	call_if_eq VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer1
	call_if_eq VAR_0x8008, 2, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer2
	msgbox RivalsHouse_1F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_0x8008, 0, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs0
	call_if_eq VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs1
	call_if_eq VAR_0x8008, 2, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs2
	playse SE_EXIT
	removeobject LOCALID_RIVALS_HOUSE_1F_RIVAL
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_BRENDAN
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	delay 30
	setvar VAR_LITTLEROOT_RIVAL_STATE, 3
	setvar VAR_LITTLEROOT_TOWN_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LittlerootTown_BrendansHouse_1F_EventScript_PlayerFaceBrendan::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer0::
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer0
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer1::
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer1
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer2::
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer2
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer0:
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer1:
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer2:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs0::
	applymovement LOCALID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit0
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs0
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs1::
	applymovement LOCALID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit1
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs1
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs2::
	applymovement LOCALID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit2
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs2
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit0:
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit1:
	delay_16
	delay_8
	walk_in_place_faster_right
	delay_16
	delay_16
	walk_in_place_faster_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit2:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs0:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs1:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs2:
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	walk_up
	step_end

PlayersHouse_1F_Text_IsntItNiceInHere:
	.string "{CHN}妈妈：看到了吗，{PLAYER}？\n"
	.string "这里面也不错吧？$"

PlayersHouse_1F_Text_MoversPokemonGoSetClock:
	.string "{CHN}搬家工人的宝可梦包揽了\n"
	.string "搬东西和打扫卫生的所有工作。\l"
	.string "真是太方便了！\p"
	.string "{PLAYER}，你的房间在楼上。\n"
	.string "上去看看吧，亲爱的！\p"
	.string "为了纪念我们搬到这里，\n"
	.string "爸爸给你买了一个新时钟。\l"
	.string "别忘了调好时间！$"

PlayersHouse_1F_Text_ArentYouInterestedInRoom:
	.string "{CHN}妈妈：怎么样，{PLAYER}？\p"
	.string "你不想去看看\n"
	.string "自己的房间吗？$"

PlayersHouse_1F_Text_GoSetTheClock:
	.string "{CHN}妈妈：{PLAYER}。\p"
	.string "去把房间里的时钟调好吧，亲爱的。$"

PlayersHouse_1F_Text_OhComeQuickly:
	.string "{CHN}妈妈：哦！{PLAYER}，{PLAYER}！\n"
	.string "快！快过来！$"

PlayersHouse_1F_Text_MaybeDadWillBeOn:
	.string "{CHN}妈妈：看！是橙华道馆！\n"
	.string "也许爸爸会上电视！$"

PlayersHouse_1F_Text_ItsOverWeMissedHim:
	.string "{CHN}妈妈：哦……结束了。\p"
	.string "我想爸爸上电视了，可是我们错过了。\n"
	.string "真可惜。$"

PlayersHouse_1F_Text_GoIntroduceYourselfNextDoor:
	.string "{CHN}哦，对了。\n"
	.string "爸爸的一个朋友也住在这个镇上。\p"
	.string "他叫小田卷博士。\p"
	.string "他就住在隔壁，你应该\n"
	.string "过去自我介绍一下。$"

PlayersHouse_1F_Text_SeeYouHoney:
	.string "{CHN}妈妈：再见，亲爱的！$"

PlayersHouse_1F_Text_DidYouMeetProfBirch:
	.string "{CHN}妈妈：你向小田卷博士\n"
	.string "自我介绍了吗？$"

PlayersHouse_1F_Text_YouShouldRestABit:
	.string "{CHN}妈妈：你最近怎么样，{PLAYER}？\n"
	.string "你看起来有点累了。\p"
	.string "我觉得你应该休息一下。$"

PlayersHouse_1F_Text_TakeCareHoney:
	.string "{CHN}妈妈：保重，亲爱的！$"

PlayersHouse_1F_Text_GotDadsBadgeHeresSomethingFromMom:
	.string "{CHN}妈妈：哦？爸爸给了你那个徽章？\p"
	.string "那妈妈也要送你点东西！$"

PlayersHouse_1F_Text_DontPushYourselfTooHard:
	.string "{CHN}别太勉强自己，亲爱的。\n"
	.string "随时都可以回家。\p"
	.string "加油哦，亲爱的！$"

PlayersHouse_1F_Text_IsThatAPokenav:
	.string "{CHN}妈妈：那是什么，亲爱的？宝可梦导航器？\n"
	.string "是得文公司的人给你的？\p"
	.string "那，亲爱的，要不要把\n"
	.string "妈妈登录上去？\p"
	.string "…… ……$"

PlayersHouse_1F_Text_RegisteredMom:
	.string "{CHN}把妈妈登录到了\n"
	.string "宝可梦导航器中。$"

PlayersHouse_1F_Text_Vigoroth1:
	.string "{CHN} fugiiiiih！$"

PlayersHouse_1F_Text_Vigoroth2:
	.string "{CHN} huggoh，uggo uggo……$"

PlayersHouse_1F_Text_ReportFromPetalburgGym:
	.string "{CHN}记者：……我们\n"
	.string "在橙华道馆前为您带来报道。$"

PlayersHouse_1F_Text_TheresAMovieOnTV:
	.string "{CHN}电视上正在播放电影。\p"
	.string "两个男人在一架大型钢琴的\n"
	.string "键盘上跳舞。\p"
	.string "该出发了！$"

PlayersHouse_1F_Text_RunningShoesManual:
	.string "{CHN}这是跑鞋的\n"
	.string "说明书。\p"
	.string "“穿上跑鞋后按下B键，\n"
	.string "就可以奔跑。\p"
	.string "“系好鞋带，\n"
	.string "在路上奔跑吧！”$"

PlayersHouse_1F_Text_TicketFromBrineyCameForYou:
	.string "{CHN}爸爸：嗯？\p"
	.string "哦，是{PLAYER}！\p"
	.string "好久不见了，\n"
	.string "不过你看起来……更结实了。\p"
	.string "这是我的感觉。\n"
	.string "不过老爸我还没有放弃呢！\p"
	.string "哦，对了，我有东西要给你。\n"
	.string "这是一个叫\n"
	.string "布林尼先生的人寄给你的。$"

PlayersHouse_1F_Text_PortsInSlateportLilycove:
	.string "{CHN}爸爸：嗯，是船票？\p"
	.string "如果我没记错，\n"
	.string "凯那市和茵郁市都有港口。$"

PlayersHouse_1F_Text_BetterGetBackToGym:
	.string "{CHN}我得回橙华道馆了。\p"
	.string "妈妈，谢谢你\n"
	.string "在我离开时照看家里。$"

PlayersHouse_1F_Text_DadShouldStayLonger:
	.string "{CHN}妈妈：你那个爸爸……\p"
	.string "好久才回一次家，\n"
	.string "却满嘴都是宝可梦的事。\p"
	.string "他应该放松一下，多待一会儿才对。$"

PlayersHouse_1F_Text_IsThatABreakingStory:
	.string "{CHN}妈妈：那是突发新闻报道吗？$"

PlayersHouse_1F_Text_LatiEmergencyNewsFlash:
	.string "{CHN}我们为您插播\n"
	.string "紧急新闻！\p"
	.string "在丰缘地区的多处地点，\n"
	.string "有人目击到一只紫红色……不，\l"
	.string "彩色的宝可梦在飞行。\p"
	.string "目前这只宝可梦的身份\n"
	.string "尚不清楚。\p"
	.string "现在让我们回到\n"
	.string "正在播放的电影节目。$"

PlayersHouse_1F_Text_WhatColorDidTheySay:
	.string "{CHN}妈妈：{PLAYER}，你听见了吗？\p"
	.string "播音员说\n"
	.string "那只宝可梦是什么颜色来着？$"

PlayersHouse_1F_Text_StillUnknownPokemon:
	.string "{CHN}妈妈：哇，真了不起！\n"
	.string "居然还有未知的宝可梦存在。$"
