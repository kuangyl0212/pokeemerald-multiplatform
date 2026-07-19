MossdeepCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_OnTransition
	.byte 0

MossdeepCity_OnTransition:
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_1
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_2
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_3
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_4
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	end

MossdeepCity_EventScript_PokefanF::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_DIVE, MossdeepCity_EventScript_PokefanFMagmaGone
	msgbox MossdeepCity_Text_SpaceCenterReceivedLetter, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_PokefanFMagmaGone::
	msgbox MossdeepCity_Text_SpaceCenterLaunchingRockets, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_Sailor::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_DIVE, MossdeepCity_EventScript_SailorMagmaGone
	msgbox MossdeepCity_Text_MossdeepTargetedByMagma, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_SailorMagmaGone::
	msgbox MossdeepCity_Text_FeelReliefOnLand, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_NinjaBoy::
	msgbox MossdeepCity_Text_WailmerWatching, MSGBOX_NPC
	end

MossdeepCity_EventScript_ExpertM::
	msgbox MossdeepCity_Text_LifeNeedsSeaToLive, MSGBOX_NPC
	end

MossdeepCity_EventScript_Girl::
	msgbox MossdeepCity_Text_NiceIfWorldCoveredByFlowers, MSGBOX_NPC
	end

MossdeepCity_EventScript_Woman::
	msgbox MossdeepCity_Text_SpecialSpaceCenterRock, MSGBOX_NPC
	end

MossdeepCity_EventScript_WhiteRock::
	msgbox MossdeepCity_Text_ItsAWhiteRock, MSGBOX_SIGN
	end

MossdeepCity_EventScript_GymSign::
	msgbox MossdeepCity_Text_GymSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_CitySign::
	msgbox MossdeepCity_Text_CitySign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_SpaceCenterSign::
	msgbox MossdeepCity_Text_SpaceCenterSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_VisitedMossdeep::
	setflag FLAG_VISITED_MOSSDEEP_CITY
	setvar VAR_TEMP_1, 1
	end

MossdeepCity_EventScript_TeamMagmaEnterSpaceCenter::
	lockall
	applymovement LOCALID_MOSSDEEP_MAXIE, MossdeepCity_Movement_MaxieGestureToSpaceCenter
	waitmovement 0
	applymovement LOCALID_MOSSDEEP_GRUNT_1, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_2, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_3, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_4, MossdeepCity_Movement_GruntFaceSpaceCenter
	waitmovement 0
	applymovement LOCALID_MOSSDEEP_MAXIE, MossdeepCity_Movement_MaxieEnterSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_1, MossdeepCity_Movement_Grunt1EnterSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_2, MossdeepCity_Movement_Grunt2EnterSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_3, MossdeepCity_Movement_Grunt3EnterSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_4, MossdeepCity_Movement_Grunt4EnterSpaceCenter
	waitmovement 0
	removeobject LOCALID_MOSSDEEP_MAXIE
	removeobject LOCALID_MOSSDEEP_GRUNT_1
	removeobject LOCALID_MOSSDEEP_GRUNT_2
	removeobject LOCALID_MOSSDEEP_GRUNT_3
	removeobject LOCALID_MOSSDEEP_GRUNT_4
	delay 30
	setvar VAR_MOSSDEEP_CITY_STATE, 2
	setflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	releaseall
	end

MossdeepCity_Movement_MaxieGestureToSpaceCenter:
	delay_16
	face_right
	delay_16
	delay_16
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_GruntFaceSpaceCenter:
	face_right
	delay_16
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_MaxieEnterSpaceCenter:
	walk_down
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt1EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt2EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt3EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt4EnterSpaceCenter:
	delay_16
	delay_8
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_EventScript_Man::
	lock
	faceplayer
	msgbox MossdeepCity_Text_SurfExhilarating, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MossdeepCity_EventScript_KingsRockBoy::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_KINGS_ROCK, MossdeepCity_EventScript_ReceivedKingsRock
	msgbox MossdeepCity_Text_WantKingsRockStevenGaveMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MossdeepCity_EventScript_DeclineKingsRock
	msgbox MossdeepCity_Text_YouCanKeepIt, MSGBOX_DEFAULT
	giveitem ITEM_KINGS_ROCK
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_KINGS_ROCK
	release
	end

MossdeepCity_EventScript_ReceivedKingsRock::
	msgbox MossdeepCity_Text_StevensHouseOverThere, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_DeclineKingsRock::
	msgbox MossdeepCity_Text_WhatToDoWithWeirdRock, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_BlackBelt::
	msgbox MossdeepCity_Text_SootopolisNewGymLeader, MSGBOX_NPC
	end

MossdeepCity_EventScript_Scott::
	lock
	faceplayer
	msgbox MossdeepCity_Text_ScottSomethingWrongWithTown, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, MossdeepCity_EventScript_ScottExitNorth
	call_if_eq VAR_FACING, DIR_EAST, MossdeepCity_EventScript_ScottExitEast
	addvar VAR_SCOTT_STATE, 1
	removeobject LOCALID_MOSSDEEP_SCOTT
	release
	end

MossdeepCity_EventScript_ScottExitNorth::
	applymovement LOCALID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_MOSSDEEP_SCOTT, MossdeepCity_Movement_ScottExitNorth
	waitmovement 0
	return

MossdeepCity_EventScript_ScottExitEast::
	applymovement LOCALID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_MOSSDEEP_SCOTT, MossdeepCity_Movement_ScottExitEast
	waitmovement 0
	return

MossdeepCity_Movement_PlayerWatchScottExit:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MossdeepCity_Movement_ScottExitNorth:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Movement_ScottExitEast:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Text_WantKingsRockStevenGaveMe:
	.string "{CHN}这是我从大吾那里得到的，但我\n"
	.string "不知道它有什么用。\p"
	.string "好像叫王者之证。\n"
	.string "你要吗？$"

MossdeepCity_Text_YouCanKeepIt:
	.string "{CHN}你为什么要它？\n"
	.string "你真奇怪。\p"
	.string "你拿着吧，但要对大吾\n"
	.string "保密。$"

MossdeepCity_Text_StevensHouseOverThere:
	.string "{CHN}大吾的家就在那边！$"

MossdeepCity_Text_WhatToDoWithWeirdRock:
	.string "{CHN}是啊，你也这么想吧！这种奇怪的\n"
	.string "石头到底用来干嘛的？$"

MossdeepCity_Text_WailmerWatching:
	.string "{CHN}在琉璃市附近，能看到野生的\n"
	.string "吼吼鲸。\p"
	.string "那个叫什么来着……\n"
	.string "叫什么来着……\p"
	.string "吼，吼，吼……\p"
	.string "观赏吼吼鲸！$"

MossdeepCity_Text_SpaceCenterReceivedLetter:
	.string "{CHN}这座岛上的宇宙中心一直在\n"
	.string "发射巨大的火箭。\p"
	.string "最近他们收到一封信，\n"
	.string "引起了一阵骚动。$"

MossdeepCity_Text_SpaceCenterLaunchingRockets:
	.string "{CHN}这座岛上的宇宙中心一直在\n"
	.string "发射巨大的火箭。$"

MossdeepCity_Text_MossdeepTargetedByMagma:
	.string "{CHN}我听一个船员朋友说，水舰队\n"
	.string "在水静市设了据点。\p"
	.string "我还听说有人去把他们\n"
	.string "打得落花流水！\p"
	.string "可是琉璃市这边却被火焰队\n"
	.string "盯上了。\p"
	.string "如果你想知道他们在干什么，\n"
	.string "就去宇宙中心看看吧。$"

MossdeepCity_Text_FeelReliefOnLand:
	.string "{CHN}我是船员，所以大海对我来说\n"
	.string "当然更重要。\p"
	.string "不过你知道吗？经过漫长的航海后\n"
	.string "回到陆地，确实会感到安心！$"

MossdeepCity_Text_NiceIfWorldCoveredByFlowers:
	.string "{CHN}那不是很美好吗？\p"
	.string "如果整个世界都像这座岛一样，\n"
	.string "被植物和花朵覆盖的话？$"

MossdeepCity_Text_LifeNeedsSeaToLive:
	.string "{CHN}所有生命都需要大海才能生存，\n"
	.string "即使它们在陆地上安家。\p"
	.string "生命走完历程后，会化为\n"
	.string "泥土回归大地。\p"
	.string "而大海始终与\n"
	.string "陆地相连。\p"
	.string "没错，就像这里的海岸线一样。$"

MossdeepCity_Text_SurfExhilarating:
	.string "{CHN}坐船航海也不错。\p"
	.string "但是和宝可梦一起用冲浪\n"
	.string "渡过大海……\p"
	.string "那才是令人心旷神怡的旅程！\n"
	.string "你说对吧，年轻人？$"

MossdeepCity_Text_SpecialSpaceCenterRock:
	.string "{CHN}这块石头对宇宙中心的人\n"
	.string "来说有着特殊的意义。\p"
	.string "他们把它放在这里，祈愿\n"
	.string "火箭能安全飞行。\p"
	.string "当你许愿的时候，你会用什么？\n"
	.string "你会对着星星许愿吗？\p"
	.string "我用许愿牌来实现愿望。\n"
	.string "我就是这么做的。$"

MossdeepCity_Text_ItsAWhiteRock:
	.string "{CHN}是一块白色的石头。$"

MossdeepCity_Text_GymSign:
	.string "{CHN}琉璃市宝可梦道馆\n"
	.string "馆主：南&枫\p"
	.string "“神秘的组合！”$"

MossdeepCity_Text_CitySign:
	.string "{CHN}琉璃市\n"
	.string "“我们的口号：珍惜宝可梦！”$"

MossdeepCity_Text_SpaceCenterSign:
	.string "{CHN}琉璃宇宙中心\n"
	.string "“离宇宙最近的地方。”$"

MossdeepCity_Text_ScottSomethingWrongWithTown:
	.string "{CHN}水木：{PLAYER}{KUN}，感觉好吗？\n"
	.string "我很好！\p"
	.string "我听说琉璃市的道馆馆主\n"
	.string "相当强，所以决定\l"
	.string "亲自来看看。\p"
	.string "可是这座城市\n"
	.string "有些不对劲。\p"
	.string "大家都在谈论警告信\n"
	.string "和宇宙中心的事……\p"
	.string "不过我觉得这事和我\n"
	.string "没什么关系。$"

MossdeepCity_Text_SootopolisNewGymLeader:
	.string "{CHN}啊……让海浪拍打双脚\n"
	.string "的感觉真棒……\p"
	.string "说起海浪，你知道那座\n"
	.string "岛屿城市暮水镇吗？\p"
	.string "我听说那里的道馆换了一位\n"
	.string "新馆主。\p"
	.string "有人告诉我，新馆主曾经\n"
	.string "指导过米可利。$"
