Route119_WeatherInstitute_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route119_WeatherInstitute_1F_OnTransition
	.byte 0

Route119_WeatherInstitute_1F_OnTransition:
	call_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Route119_WeatherInstitute_1F_EventScript_SetLittleBoyPos
	end

Route119_WeatherInstitute_1F_EventScript_SetLittleBoyPos::
	setobjectxyperm LOCALID_WEATHER_INSTITUTE_LITTLE_BOY, 0, 5
	setobjectmovementtype LOCALID_WEATHER_INSTITUTE_LITTLE_BOY, MOVEMENT_TYPE_FACE_RIGHT
	return

Route119_WeatherInstitute_1F_EventScript_LittleBoy::
	lock
	faceplayer
	special GetPlayerBigGuyGirlString
	goto_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Route119_WeatherInstitute_1F_EventScript_LittleBoyTeamAquaHere
	msgbox Route119_WeatherInstitute_1F_Text_WowYoureStrong, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_LittleBoyTeamAquaHere::
	msgbox Route119_WeatherInstitute_1F_Text_EveryoneWentUpstairs, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_InstituteWorker1::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, Route119_WeatherInstitute_1F_EventScript_StudyingRain
	setvar VAR_0x8004, 0
	call_if_set FLAG_DEFEATED_KYOGRE, Route119_WeatherInstitute_1F_EventScript_LegendaryDefeated
	call_if_set FLAG_DEFEATED_GROUDON, Route119_WeatherInstitute_1F_EventScript_LegendaryDefeated
	goto_if_eq VAR_0x8004, 2, Route119_WeatherInstitute_1F_EventScript_StudyingRain  /* Both defeated*/
	msgbox Route119_WeatherInstitute_1F_Text_NoticingAbnormalWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_LegendaryDefeated::
	addvar VAR_0x8004, 1
	return

Route119_WeatherInstitute_1F_EventScript_StudyingRain::
	msgbox Route119_WeatherInstitute_1F_Text_ProfStudyingRain, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_InstituteWorker2::
	msgbox Route119_WeatherInstitute_1F_Text_WhatWereAquasUpTo, MSGBOX_NPC
	end

Route119_WeatherInstitute_1F_EventScript_Bed::
	lockall
	msgbox Route119_WeatherInstitute_1F_Text_TakeRestInBed, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	releaseall
	end

Route119_WeatherInstitute_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_1, Route119_WeatherInstitute_1F_Text_Grunt1Intro, Route119_WeatherInstitute_1F_Text_Grunt1Defeat
	msgbox Route119_WeatherInstitute_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_1F_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_4, Route119_WeatherInstitute_1F_Text_Grunt4Intro, Route119_WeatherInstitute_1F_Text_Grunt4Defeat
	msgbox Route119_WeatherInstitute_1F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_1F_Text_Grunt1Intro:
	.string "{CHN}老大对这里进行的\n"
	.string "研究产生了兴趣，\l"
	.string "所以派我们来了。\p"
	.string "你别多管闲事！$"

Route119_WeatherInstitute_1F_Text_Grunt1Defeat:
	.string "{CHN}可恶……\n"
	.string "竟然被一个小鬼打败……$"

Route119_WeatherInstitute_1F_Text_Grunt1PostBattle:
	.string "{CHN}我们的老大无所不知。\p"
	.string "但我只是个小卒。我怎么可能知道\n"
	.string "他在想什么呢？$"

Route119_WeatherInstitute_1F_Text_Grunt4Intro:
	.string "{CHN}嗯？\n"
	.string "小鬼来这里干什么？$"

Route119_WeatherInstitute_1F_Text_Grunt4Defeat:
	.string "{CHN}嗯？\n"
	.string "我输了？！$"

Route119_WeatherInstitute_1F_Text_Grunt4PostBattle:
	.string "{CHN}哦，不……\n"
	.string "输给小鬼会被骂一顿……\p"
	.string "我还是在床上睡一觉吧……$"

Route119_WeatherInstitute_1F_Text_EveryoneWentUpstairs:
	.string "{CHN}我睡觉的时候，大家都\n"
	.string "跑到楼上去了！$"

Route119_WeatherInstitute_1F_Text_WowYoureStrong:
	.string "{CHN}哇，你真厉害！\p"
	.string "我也希望能成为\n"
	.string "像你一样的宝可梦训练家！$"

Route119_WeatherInstitute_1F_Text_ProfStudyingRain:
	.string "{CHN}教授喜欢下雨。\n"
	.string "这是事实。\p"
	.string "但如果一直下雨，人们就会有麻烦。\n"
	.string "这也是事实。\p"
	.string "因此，教授正在研究\n"
	.string "是否能善加利用雨水。$"

Route119_WeatherInstitute_1F_Text_NoticingAbnormalWeather:
	.string "{CHN}在研究所的2楼，\n"
	.string "我们研究丰缘地区\l"
	.string "的天气模式。\p"
	.string "最近我们注意到了暂时性、\n"
	.string "局部性的干旱和\l"
	.string "暴雨现象……$"

Route119_WeatherInstitute_1F_Text_WhatWereAquasUpTo:
	.string "{CHN}你好！\n"
	.string "多亏了你我们才得救！\p"
	.string "我不明白的是水舰队\n"
	.string "到底想干什么。$"

Route119_WeatherInstitute_1F_Text_TakeRestInBed:
	.string "{CHN}这里有一张床……\n"
	.string "休息一下吧。$"

