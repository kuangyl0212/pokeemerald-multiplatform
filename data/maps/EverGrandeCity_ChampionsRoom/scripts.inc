EverGrandeCity_ChampionsRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_ChampionsRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_ChampionsRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_ChampionsRoom_OnFrame
	.byte 0

EverGrandeCity_ChampionsRoom_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	end

EverGrandeCity_ChampionsRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth
	.short 0

EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

EverGrandeCity_ChampionsRoom_OnFrame:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_EnterRoom
	.short 0

EverGrandeCity_ChampionsRoom_EventScript_EnterRoom::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp4
	waitmovement 0
	delay 40
	applymovement LOCALID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace
	waitmovement 0
	setvar VAR_TEMP_1, 1
	goto EverGrandeCity_ChampionsRoom_EventScript_Wallace
	releaseall
	end

EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace:
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_EventScript_Wallace::
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	msgbox EverGrandeCity_ChampionsRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLACE, EverGrandeCity_ChampionsRoom_Text_Defeat
	goto EverGrandeCity_ChampionsRoom_EventScript_Defeated
	end

EverGrandeCity_ChampionsRoom_EventScript_Defeated::
	playse SE_DOOR
	setmetatile 6, 1, METATILE_EliteFour_OpenDoorChampion_Frame, FALSE
	setmetatile 6, 2, METATILE_EliteFour_OpenDoorChampion_Opening, FALSE
	special DrawWholeMapView
	msgbox EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic
	addobject LOCALID_CHAMPIONS_ROOM_RIVAL
	call EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_MayAdvice
	goto_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice
	end

EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_MayAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_MayAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF::
	closemessage
	addobject LOCALID_CHAMPIONS_ROOM_BIRCH
	applymovement LOCALID_CHAMPIONS_ROOM_BIRCH, EverGrandeCity_ChampionsRoom_Movement_BirchArrives
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex, MSGBOX_DEFAULT
	call ProfBirch_EventScript_RatePokedex
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchCongratulations, MSGBOX_DEFAULT
	applymovement LOCALID_CHAMPIONS_ROOM_WALLACE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	applymovement LOCALID_CHAMPIONS_ROOM_WALLACE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_WallaceComeWithMe, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement LOCALID_CHAMPIONS_ROOM_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart
	applymovement LOCALID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart
	applymovement LOCALID_CHAMPIONS_ROOM_BIRCH, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalFollows
	waitmovement 0
	delay 20
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_WallaceWaitOutside, MSGBOX_DEFAULT
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations
	closemessage
	applymovement LOCALID_CHAMPIONS_ROOM_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExit
	applymovement LOCALID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExit
	waitmovement 0
	setflag FLAG_HIDE_PETALBURG_GYM_GREETER
	warp MAP_EVER_GRANDE_CITY_HALL_OF_FAME, 7, 16
	waitstate
	releaseall
	end

EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations::
	msgbox EverGrandeCity_ChampionsRoom_Text_MayCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations::
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer::
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth::
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart:
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_PlayerExit:
	walk_up
	delay_16
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_in_place_faster_right
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth:
	walk_in_place_faster_up
	delay_16
	walk_in_place_faster_right
	delay_16
	walk_in_place_faster_up
	delay_8
	walk_in_place_faster_right
	delay_16
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalFollows:
	walk_right
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart:
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExit:
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_BirchArrives:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_in_place_faster_left
	step_end

EverGrandeCity_ChampionsRoom_Text_IntroSpeech:
	.string "{CHN}米可利：欢迎你，{PLAYER}{KUN}。\p"
	.string "在刺刺市发生的那件事……\n"
	.string "你独自一人平息了那场危机，\l"
	.string "干得真漂亮。\p"
	.string "哎呀！\p"
	.string "说你是独自一人平息了危机，\n"
	.string "这未免有些不公平。\p"
	.string "你是和宝可梦齐心协力，\n"
	.string "才克服了那个困难的局面。\p"
	.string "我们训练家通过给宝可梦道具，\n"
	.string "教会它们新的招式，\l"
	.string "来培育宝可梦。\p"
	.string "但我们自己也从宝可梦身上\n"
	.string "学到了许多东西。\p"
	.string "而这里，正是你的成就\n"
	.string "接受考验，与像你这样的\l"
	.string "其他训练家一较高下的地方。\p"
	.string "那么！\p"
	.string "在丰缘，谁能与自己的宝可梦\n"
	.string "跳起最优雅的舞蹈？\p"
	.string "就在此时此地，展示给我看吧！$"

EverGrandeCity_ChampionsRoom_Text_Defeat:
	.string "{CHN}我身为冠军，竟然败北了……\p"
	.string "干得真漂亮。\n"
	.string "你的姿态优雅得令人恼火，\l"
	.string "却又无比辉煌！\p"
	.string "向你致敬，{PLAYER}{KUN}！\p"
	.string "你是一位真正高尚的宝可梦\n"
	.string "训练家！$"

EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech:
	.string "{CHN}米可利：你派上战场的\n"
	.string "宝可梦……\p"
	.string "它们时而如春风般翩翩起舞，\n"
	.string "时而又如闪电般出击，\l"
	.string "真是精彩。\p"
	.string "你以轻盈而稳健的优雅，\n"
	.string "指挥着你的宝可梦。\p"
	.string "就连我也为你的精彩表演\n"
	.string "而感到目眩神迷！\p"
	.string "如今你已站在宝可梦联盟\n"
	.string "光荣的顶峰。\p"
	.string "我现在宣布，你是丰缘地区\n"
	.string "新的……$"

EverGrandeCity_ChampionsRoom_Text_MayAdvice:
	.string "{CHN}小遥：{PLAYER}{KUN}！\p"
	.string "在你挑战冠军之前，\n"
	.string "给你一个建议……$"

EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver:
	.string "{CHN}小遥：嗯？\n"
	.string "什么什么什么？\p"
	.string "{PLAYER}{KUN}……\n"
	.string "难道说……\l"
	.string "已经结束了？$"

EverGrandeCity_ChampionsRoom_Text_BrendanAdvice:
	.string "{CHN}佑树：{PLAYER}！\p"
	.string "在你挑战冠军之前，\n"
	.string "要不要听点建议？……$"

EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon:
	.string "{CHN}佑树：{PLAYER}……\p"
	.string "你是想告诉我……\n"
	.string "你打败了冠军？$"

EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex:
	.string "{CHN}小田卷博士：看到了吧？\n"
	.string "我怎么说来着，{RIVAL}？\p"
	.string "我不是说过不用担心\n"
	.string "{PLAYER}{KUN}吗？\p"
	.string "… … … … … … … …\n"
	.string "{PLAYER}{KUN}，你终于做到了。\p"
	.string "当我听说你在橙华道馆打败了\n"
	.string "自己的父亲时，\l"
	.string "我就觉得你或许有机会……\p"
	.string "没想到你竟然真的\n"
	.string "成为了冠军！\p"
	.string "啊，对了！\p"
	.string "你的宝可梦图鉴怎么样了？\n"
	.string "来，让我看看。$"

EverGrandeCity_ChampionsRoom_Text_BirchCongratulations:
	.string "{CHN}小田卷博士：总之，\n"
	.string "恭喜你！\p"
	.string "现在，昂首走进最后的房间吧！$"

EverGrandeCity_ChampionsRoom_Text_WallaceComeWithMe:
	.string "{CHN}米可利：{PLAYER}{KUN}……\p"
	.string "不，让我重新措辞。\p"
	.string "新的冠军！\p"
	.string "跟我来吧。$"

EverGrandeCity_ChampionsRoom_Text_WallaceWaitOutside:
	.string "{CHN}米可利：很抱歉，但是……\p"
	.string "从这里开始，只有成为冠军的\n"
	.string "训练家才能进入。\p"
	.string "你和小田卷博士一起\n"
	.string "在外面等等吧。$"

EverGrandeCity_ChampionsRoom_Text_MayCongratulations:
	.string "{CHN}小遥：呜……\p"
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "我开玩笑的！没关系啦！\n"
	.string "这就是规矩嘛！\p"
	.string "{PLAYER}{KUN}！\n"
	.string "真心祝贺你！$"

EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations:
	.string "{CHN}佑树：什么？！… … … … …\n"
	.string "… … … … … … … …\p"
	.string "规矩如此，那也没办法。\p"
	.string "{PLAYER}，干得漂亮！\n"
	.string "恭喜你！$"
