Route119_WeatherInstitute_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route119_WeatherInstitute_2F_OnTransition
	.byte 0

Route119_WeatherInstitute_2F_OnTransition:
	call_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Route119_WeatherInstitute_2F_EventScript_SetScientistPosAquaHere
	call_if_eq VAR_WEATHER_INSTITUTE_STATE, 1, Route119_WeatherInstitute_2F_EventScript_SetScientistPosAquaGone
	call_if_set FLAG_SYS_GAME_CLEAR, Route119_WeatherInstitute_2F_EventScript_SetScientistPosGameClear
	end

Route119_WeatherInstitute_2F_EventScript_SetScientistPosAquaHere::
	setobjectxyperm LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, 1, 6
	setobjectmovementtype LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, MOVEMENT_TYPE_FACE_RIGHT
	return

Route119_WeatherInstitute_2F_EventScript_SetScientistPosAquaGone::
	setobjectxyperm LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, 4, 6
	setobjectmovementtype LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, MOVEMENT_TYPE_FACE_RIGHT
	return

Route119_WeatherInstitute_2F_EventScript_SetScientistPosGameClear::
	setobjectxyperm LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, 2, 2
	setobjectmovementtype LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, MOVEMENT_TYPE_FACE_UP
	return

Route119_WeatherInstitute_2F_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_5, Route119_WeatherInstitute_2F_Text_Grunt5Intro, Route119_WeatherInstitute_2F_Text_Grunt5Defeat
	msgbox Route119_WeatherInstitute_2F_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_2F_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_2, Route119_WeatherInstitute_2F_Text_Grunt2Intro, Route119_WeatherInstitute_2F_Text_Grunt2Defeat
	msgbox Route119_WeatherInstitute_2F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_2F_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_3, Route119_WeatherInstitute_2F_Text_Grunt3Intro, Route119_WeatherInstitute_2F_Text_Grunt3Defeat
	msgbox Route119_WeatherInstitute_2F_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_2F_EventScript_Shelly::
	trainerbattle_single TRAINER_SHELLY_WEATHER_INSTITUTE, Route119_WeatherInstitute_2F_Text_ShellyIntro, Route119_WeatherInstitute_2F_Text_ShellyDefeat, Route119_WeatherInstitute_2F_EventScript_ShellyDefeated
	msgbox Route119_WeatherInstitute_2F_Text_ShellyPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_2F_EventScript_ShellyDefeated::
	msgbox Route119_WeatherInstitute_2F_Text_ShellyPostBattle, MSGBOX_DEFAULT
	closemessage
	addobject LOCALID_WEATHER_INSTITUTE_2F_GRUNT_3
	applymovement LOCALID_WEATHER_INSTITUTE_2F_GRUNT_3, Route119_WeatherInstitute_2F_Movement_GruntApproachShelly
	applymovement LOCALID_PLAYER, Route119_WeatherInstitute_2F_Movement_ShovePlayerOutOfWay
	waitmovement 0
	msgbox Route119_WeatherInstitute_2F_Text_TeamMagmaJustPassedBy, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_WEATHER_INSTITUTE_2F_SHELLY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WEATHER_INSTITUTE_2F_SHELLY, Common_Movement_Delay48
	waitmovement 0
	msgbox Route119_WeatherInstitute_2F_Text_WeHaveToHurryToMtPyre, MSGBOX_DEFAULT
	closemessage
	setvar VAR_WEATHER_INSTITUTE_STATE, 1
	clearflag FLAG_HIDE_WEATHER_INSTITUTE_2F_WORKERS
	fadedefaultbgm
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_ROUTE_119_TEAM_AQUA
	setflag FLAG_HIDE_WEATHER_INSTITUTE_2F_AQUA_GRUNT_M
	removeobject LOCALID_WEATHER_INSTITUTE_2F_GRUNT_1
	removeobject LOCALID_WEATHER_INSTITUTE_2F_GRUNT_2
	removeobject LOCALID_WEATHER_INSTITUTE_2F_SHELLY
	removeobject LOCALID_WEATHER_INSTITUTE_2F_GRUNT_4
	removeobject LOCALID_WEATHER_INSTITUTE_2F_GRUNT_3
	applymovement LOCALID_PLAYER, Route119_WeatherInstitute_2F_Movement_PlayerReturnToPosition
	waitmovement 0
	fadescreen FADE_FROM_BLACK
	applymovement LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, Route119_WeatherInstitute_2F_Movement_ScientistApproachPlayer
	waitmovement 0
	copyobjectxytoperm LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST
	goto Route119_WeatherInstitute_2F_EventScript_ReceiveCastform
	end

Route119_WeatherInstitute_2F_EventScript_ReceiveCastform::
	msgbox Route119_WeatherInstitute_2F_Text_ThanksPleaseTakePokemon, MSGBOX_DEFAULT
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_CASTFORM
	givemon SPECIES_CASTFORM, 25, ITEM_MYSTIC_WATER
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, Route119_WeatherInstitute_2F_EventScript_ReceiveCastformParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, Route119_WeatherInstitute_2F_EventScript_ReceiveCastformPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

Route119_WeatherInstitute_2F_EventScript_ReceiveCastformParty::
	call Route119_WeatherInstitute_2F_EventScript_ReceivedCastformFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route119_WeatherInstitute_2F_EventScript_ExplainCastform
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto Route119_WeatherInstitute_2F_EventScript_ExplainCastform
	end

Route119_WeatherInstitute_2F_EventScript_ReceiveCastformPC::
	call Route119_WeatherInstitute_2F_EventScript_ReceivedCastformFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route119_WeatherInstitute_2F_EventScript_SendCastformToPC
	call Common_EventScript_NameReceivedBoxMon
	goto Route119_WeatherInstitute_2F_EventScript_SendCastformToPC
	end

Route119_WeatherInstitute_2F_EventScript_SendCastformToPC::
	call Common_EventScript_TransferredToPC
	goto Route119_WeatherInstitute_2F_EventScript_ExplainCastform
	end

Route119_WeatherInstitute_2F_EventScript_ReceivedCastformFanfare::
	playfanfare MUS_OBTAIN_ITEM
	message Route119_WeatherInstitute_2F_Text_PlayerReceivedCastform
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_CASTFORM
	return

Route119_WeatherInstitute_2F_EventScript_ExplainCastform::
	msgbox Route119_WeatherInstitute_2F_Text_PokemonChangesWithWeather, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_CASTFORM
	release
	end

Route119_WeatherInstitute_2F_EventScript_ScientistMentionWeather::
	goto_if_set FLAG_SYS_GAME_CLEAR, Route119_WeatherInstitute_2F_EventScript_TryStartAbnormalWeather
	msgbox Route119_WeatherInstitute_2F_Text_ChangingWeatherRidiculous, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_2F_EventScript_TryStartAbnormalWeather::
	setvar VAR_0x8004, 0
	call_if_set FLAG_DEFEATED_KYOGRE, Route119_WeatherInstitute_2F_EventScript_LegendaryDefeated
	call_if_set FLAG_DEFEATED_GROUDON, Route119_WeatherInstitute_2F_EventScript_LegendaryDefeated
	goto_if_eq VAR_0x8004, 2, Route119_WeatherInstitute_2F_EventScript_NoAbnormalWeather  /* Both defeated*/
	call_if_unset FLAG_TEMP_2, Route119_WeatherInstitute_2F_EventScript_CreateAbnormalWeather
	specialvar VAR_RESULT, GetAbnormalWeatherMapNameAndType
	goto_if_eq VAR_RESULT, 1, Route119_WeatherInstitute_2F_EventScript_KyogreWeather
	msgbox Route119_WeatherInstitute_2F_Text_GroudonWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_2F_EventScript_KyogreWeather::
	msgbox Route119_WeatherInstitute_2F_Text_KyogreWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_2F_EventScript_CreateAbnormalWeather::
	special CreateAbnormalWeatherEvent
	setflag FLAG_TEMP_2
	return

Route119_WeatherInstitute_2F_EventScript_LegendaryDefeated::
	addvar VAR_0x8004, 1
	return

Route119_WeatherInstitute_2F_EventScript_NoAbnormalWeather::
	msgbox Route119_WeatherInstitute_2F_Text_NoAbnormalWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_2F_Movement_GruntApproachShelly:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

Route119_WeatherInstitute_2F_Movement_ShovePlayerOutOfWay:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	ride_water_current_up
	walk_in_place_faster_down
	step_end

Route119_WeatherInstitute_2F_Movement_PlayerReturnToPosition:
	slide_down
	walk_in_place_faster_left
	step_end

Route119_WeatherInstitute_2F_Movement_ScientistApproachPlayer:
	walk_right
	walk_right
	walk_right
	step_end

Route119_WeatherInstitute_2F_EventScript_WeatherScientist::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CASTFORM, Route119_WeatherInstitute_2F_EventScript_ScientistMentionWeather
	goto Route119_WeatherInstitute_2F_EventScript_ReceiveCastform
	end

Route119_WeatherInstitute_2F_Text_Grunt2Intro:
	.string "{CHN}研究所创造出了一种\n"
	.string "和天气有关的\l"
	.string "宝可梦。我们是来带走它们的！$"

Route119_WeatherInstitute_2F_Text_Grunt2Defeat:
	.string "{CHN}我们的计划竟然被小鬼破坏了？$"

Route119_WeatherInstitute_2F_Text_Grunt2PostBattle:
	.string "{CHN}如果他们在这里做的宝可梦\n"
	.string "能自由控制天气，那我们\l"
	.string "水舰队就一定要得到它！$"

Route119_WeatherInstitute_2F_Text_Grunt3Intro:
	.string "{CHN}我们是水舰队！\n"
	.string "哪里有稀罕东西，\l"
	.string "我们就出现在哪里！$"

Route119_WeatherInstitute_2F_Text_Grunt3Defeat:
	.string "{CHN}你赢了！$"

Route119_WeatherInstitute_2F_Text_Grunt3PostBattle:
	.string "{CHN}你根本不知道\n"
	.string "我们水舰队的\l"
	.string "目标是什么！\p"
	.string "别挡我们的路！$"

Route119_WeatherInstitute_2F_Text_Grunt5Intro:
	.string "{CHN}你该不会也在找\n"
	.string "那只天气宝可梦吧？\p"
	.string "那可不行！\n"
	.string "我们可是先来一步的！$"

Route119_WeatherInstitute_2F_Text_Grunt5Defeat:
	.string "{CHN}哦，看看我的宝可梦吧？$"

Route119_WeatherInstitute_2F_Text_Grunt5PostBattle:
	.string "{CHN}哼，那又怎样？\n"
	.string "我们想要的……\p"
	.string "我们真正想要的不在这里……\n"
	.string "嘿嘿嘿嘿……$"

Route119_WeatherInstitute_2F_Text_ShellyIntro:
	.string "{CHN}啊哈哈哈！\p"
	.string "你要插手水舰队\n"
	.string "的事情吗？\p"
	.string "你要么是绝对无畏，\n"
	.string "要么是一无所知，要么两者都是！\p"
	.string "你可爱得让人恶心！\n"
	.string "让我来收拾你，小鬼！$"

Route119_WeatherInstitute_2F_Text_ShellyDefeat:
	.string "{CHN}啊哈哈哈！\n"
	.string "你强得让人恶心！$"

Route119_WeatherInstitute_2F_Text_ShellyPostBattle:
	.string "{CHN}火焰队来捣乱\n"
	.string "就够受的了，现在还有你！\p"
	.string "到底是什么让你想\n"
	.string "插手我们的事情呢？$"

Route119_WeatherInstitute_2F_Text_TeamMagmaJustPassedBy:
	.string "{CHN}出状况了！\p"
	.string "一群火焰队的人刚刚经过\n"
	.string "气象研究所。\p"
	.string "他们好像是\n"
	.string "朝送火山去的！$"

Route119_WeatherInstitute_2F_Text_WeHaveToHurryToMtPyre:
	.string "{CHN}什么？！\p"
	.string "我们不能在这里再浪费时间了！\n"
	.string "我们也得赶紧去送火山！\p"
	.string "啊哈哈哈！\n"
	.string "火焰队，你们等着！$"

Route119_WeatherInstitute_2F_Text_ThanksPleaseTakePokemon:
	.string "{CHN}谢谢！\n"
	.string "多亏了你我们才安全了！\p"
	.string "这种感谢方式可能有点奇怪，\n"
	.string "但请收下这只宝可梦。$"

/* Unused*/
Route119_WeatherInstitute_2F_Text_NoRoomForPokemon:
	.string "{CHN}嗯？你好像没有\n"
	.string "空间放这只宝可梦了。$"

Route119_WeatherInstitute_2F_Text_PlayerReceivedCastform:
	.string "{CHN}{PLAYER}获得了漂浮泡泡！$"

Route119_WeatherInstitute_2F_Text_PokemonChangesWithWeather:
	.string "{CHN}那只宝可梦会根据\n"
	.string "天气情况改变形态。\p"
	.string "研究所里有很多——\n"
	.string "请带走它吧。$"

Route119_WeatherInstitute_2F_Text_ChangingWeatherRidiculous:
	.string "{CHN}我研究雨已经很多\n"
	.string "年了，但人类能自由\l"
	.string "改变天气这种想法太荒谬了。$"

Route119_WeatherInstitute_2F_Text_GroudonWeather:
	.string "{CHN}我追踪丰缘地区\n"
	.string "的天气模式。\p"
	.string "目前，{STR_VAR_1}出现了\n"
	.string "干旱现象。\p"
	.string "难道说，在{STR_VAR_1}\n"
	.string "附近的某个地方……$"

Route119_WeatherInstitute_2F_Text_KyogreWeather:
	.string "{CHN}我追踪丰缘地区\n"
	.string "的天气模式。\p"
	.string "目前，{STR_VAR_1}出现了\n"
	.string "强降雨现象。\p"
	.string "难道说，在{STR_VAR_1}\n"
	.string "附近的某个地方……$"

Route119_WeatherInstitute_2F_Text_NoAbnormalWeather:
	.string "{CHN}异常天气现象\n"
	.string "已经不再出现了。\p"
	.string "偶尔下场雨其实\n"
	.string "是种福分。$"

