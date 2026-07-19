SeafloorCavern_Room9_MapScripts::
	.byte 0

SeafloorCavern_Room9_EventScript_ArchieAwakenKyogre::
	lockall
	setvar VAR_0x8004, LOCALID_SEAFLOOR_CAVERN_ARCHIE
	setvar VAR_0x8005, LOCALID_SEAFLOOR_CAVERN_MAXIE
	setvar VAR_0x8006, LOCALID_SEAFLOOR_CAVERN_GRUNT_1
	setvar VAR_0x8007, LOCALID_SEAFLOOR_CAVERN_GRUNT_2
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	applymovement LOCALID_PLAYER, SeafloorCavern_Room9_Movement_Delay32
	waitmovement 0
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	msgbox SeafloorCavern_Room9_Text_ArchieHoldItRightThere, MSGBOX_DEFAULT
	closemessage
	addobject VAR_0x8004
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement VAR_0x8004, SeafloorCavern_Room9_Movement_ArchieApproachPlayer
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_ArchieSoItWasYou, MSGBOX_DEFAULT
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_ArchieBeholdKyogre, MSGBOX_DEFAULT
	applymovement VAR_0x8004, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_ArchieYouMustDisappear, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_ARCHIE, SeafloorCavern_Room9_Text_ArchieDefeat
	msgbox SeafloorCavern_Room9_Text_ArchieWithThisRedOrb, MSGBOX_DEFAULT
	setweather WEATHER_NONE
	doweather
	special Script_FadeOutMapMusic
	waitstate
	msgbox SeafloorCavern_Room9_Text_RedOrbShinesByItself, MSGBOX_DEFAULT
	special WaitWeather
	waitstate
	setvar VAR_RESULT, 1
	playse SE_M_DETECT
	dofieldeffectsparkle 16, 42, 0
	waitfieldeffect FLDEFF_SPARKLE
	closemessage
	setvar VAR_RESULT, 0
	playfanfare MUS_AWAKEN_LEGEND
	playse SE_ORB
	special DoOrbEffect
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 150
	removeobject LOCALID_SEAFLOOR_CAVERN_KYOGRE_SLEEPING
	addobject LOCALID_SEAFLOOR_CAVERN_KYOGRE
	waitstate
	delay 60
	applymovement LOCALID_SEAFLOOR_CAVERN_KYOGRE, SeafloorCavern_Room9_Movement_KyogreApproach
	waitmovement 0
	special FadeOutOrbEffect
	waitstate
	setvar VAR_0x8004, 1  /* vertical pan*/
	setvar VAR_0x8005, 1  /* horizontal pan*/
	setvar VAR_0x8006, 8  /* num shakes*/
	setvar VAR_0x8007, 5  /* shake delay*/
	special ShakeCamera
	waitstate
	applymovement LOCALID_SEAFLOOR_CAVERN_KYOGRE, SeafloorCavern_Room9_Movement_KyogreExit
	waitmovement 0
	removeobject LOCALID_SEAFLOOR_CAVERN_KYOGRE
	delay 4
	setvar VAR_0x8004, 2  /* vertical pan*/
	setvar VAR_0x8005, 2  /* horizontal pan*/
	setvar VAR_0x8006, 8  /* num shakes*/
	setvar VAR_0x8007, 5  /* shake delay*/
	special ShakeCamera
	waitstate
	delay 30
	setvar VAR_0x8004, LOCALID_SEAFLOOR_CAVERN_ARCHIE
	setvar VAR_0x8005, LOCALID_SEAFLOOR_CAVERN_MAXIE
	setvar VAR_0x8006, LOCALID_SEAFLOOR_CAVERN_GRUNT_1
	setvar VAR_0x8007, LOCALID_SEAFLOOR_CAVERN_GRUNT_2
	msgbox SeafloorCavern_Room9_Text_ArchieWhereDidKyogreGo, MSGBOX_DEFAULT
	playse SE_PC_LOGIN
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_ArchieAMessageFromOutside, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_0x8004, SeafloorCavern_Room9_Movement_ArchieListenMessage
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_ArchieWhatRainingTooHard, MSGBOX_DEFAULT
	closemessage
	playse SE_PC_OFF
	delay 20
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_ArchieWhyDidKyogreDisappear, MSGBOX_DEFAULT
	closemessage
	addobject VAR_0x8005
	addobject VAR_0x8006
	addobject VAR_0x8007
	applymovement VAR_0x8007, SeafloorCavern_Room9_Movement_MagmaGruntArrive
	applymovement VAR_0x8006, SeafloorCavern_Room9_Movement_MagmaGruntArrive
	applymovement VAR_0x8005, SeafloorCavern_Room9_Movement_MaxieArrive
	waitmovement 0
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_MaxieWhatHaveYouWrought, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement VAR_0x8004, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_0x8004, Common_Movement_Delay48
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_ArchieDontGetAllHighAndMighty, MSGBOX_DEFAULT
	msgbox SeafloorCavern_Room9_Text_MaxieWeDontHaveTimeToArgue, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_0x8005, SeafloorCavern_Room9_Movement_MaxieExit
	applymovement VAR_0x8004, SeafloorCavern_Room9_Movement_ArchieExit
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_MaxieComeOnPlayer, MSGBOX_DEFAULT
	setvar VAR_ROUTE128_STATE, 1
	setvar VAR_SOOTOPOLIS_CITY_STATE, 1
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_STEVEN
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_ARCHIE
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_MAXIE
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_RESIDENTS
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_GROUDON
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_KYOGRE
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_MAN_1
	setflag FLAG_LEGENDARIES_IN_SOOTOPOLIS
	clearflag FLAG_HIDE_ROUTE_128_ARCHIE
	clearflag FLAG_HIDE_ROUTE_128_MAXIE
	setflag FLAG_SYS_WEATHER_CTRL
	setflag FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN
	setflag FLAG_HIDE_MOSSDEEP_CITY_STEVENS_HOUSE_STEVEN
	setvar VAR_STEVENS_HOUSE_STATE, 2
	setvar VAR_SEAFLOOR_CAVERN_STATE, 1
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_ROOM_9_ARCHIE
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_ROOM_9_MAXIE
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_ROOM_9_MAGMA_GRUNTS
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_ROOM_9_KYOGRE
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_AQUA_GRUNTS
	setflag FLAG_HIDE_MAP_NAME_POPUP
	warp MAP_ROUTE128, 38, 22
	waitstate
	releaseall
	end

SeafloorCavern_Room9_Movement_ArchieApproachPlayer:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SeafloorCavern_Room9_Movement_Unused1:
	walk_left
	walk_left
	step_end

SeafloorCavern_Room9_Movement_ArchieListenMessage:
	walk_left
	delay_16
	step_end

SeafloorCavern_Room9_Movement_Unused2:
	walk_right
	step_end

SeafloorCavern_Room9_Movement_ArchieExit:
	face_up
	lock_facing_direction
	walk_down
	unlock_facing_direction
	walk_in_place_faster_right
	step_end

SeafloorCavern_Room9_Movement_KyogreApproach:
	delay_16
	delay_16
	walk_slow_down
	delay_16
	delay_16
	delay_16
	walk_slow_down
	delay_16
	delay_16
	delay_16
	step_end

SeafloorCavern_Room9_Movement_KyogreExit:
	slide_up
	slide_up
	step_end

SeafloorCavern_Room9_Movement_MaxieArrive:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

SeafloorCavern_Room9_Movement_MaxieExit:
	walk_right
	walk_right
	step_end

SeafloorCavern_Room9_Movement_MagmaGruntArrive:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

SeafloorCavern_Room9_Movement_Delay32:
	delay_16
	delay_16
	step_end

SeafloorCavern_Room9_Text_ArchieHoldItRightThere:
	.string "{CHN}水梧桐：站住。$"

SeafloorCavern_Room9_Text_ArchieSoItWasYou:
	.string "{CHN}水梧桐：呼呼呼…\n"
	.string "果然是你。$"

SeafloorCavern_Room9_Text_ArchieBeholdKyogre:
	.string "{CHN}水梧桐：看吧！\p"
	.string "看看它有多美，古代\n"
	.string "宝可梦盖欧卡沉睡的身姿！\p"
	.string "我等待这一天\n"
	.string "已经等了好久…$"

SeafloorCavern_Room9_Text_ArchieYouMustDisappear:
	.string "{CHN}水梧桐：真让我惊讶，你\n"
	.string "居然能追到这里。\p"
	.string "但一切都结束了。\p"
	.string "为了实现我的梦想，\n"
	.string "你现在必须消失！$"

SeafloorCavern_Room9_Text_ArchieDefeat:
	.string "{CHN}什么？！\n"
	.string "我居然输给你这种小孩？！$"

SeafloorCavern_Room9_Text_ArchieWithThisRedOrb:
	.string "{CHN}水梧桐：呼呼呼…\p"
	.string "我赞赏你。我必须承认\n"
	.string "你确实很有天赋。\p"
	.string "但是！\n"
	.string "我有这个！\p"
	.string "用这颗红色宝珠，我能让盖欧卡…$"

SeafloorCavern_Room9_Text_RedOrbShinesByItself:
	.string "{CHN}红色宝珠突然\n"
	.string "自己发出光芒！$"

SeafloorCavern_Room9_Text_ArchieWhereDidKyogreGo:
	.string "{CHN}水梧桐：什么？！\p"
	.string "我什么都没做。\n"
	.string "红色宝珠为什么…\p"
	.string "盖欧卡去哪了？$"

SeafloorCavern_Room9_Text_ArchieAMessageFromOutside:
	.string "{CHN}水梧桐：嗯？是外面\n"
	.string "队员传来的消息…$"

SeafloorCavern_Room9_Text_ArchieWhatRainingTooHard:
	.string "{CHN}水梧桐：喂，怎么了？\p"
	.string "嗯…\n"
	.string "雨下得很大？\p"
	.string "很好… 应该的。\n"
	.string "这正是我们唤醒盖欧卡的原因，\l"
	.string "为了实现水舰队扩大\l"
	.string "海洋的愿景。\p"
	.string "什么？！\p"
	.string "雨比我们设想的\n"
	.string "大得多？你们有危险？\p"
	.string "不可能…\n"
	.string "这不可能…\p"
	.string "坚守岗位，\n"
	.string "监视情况！$"

SeafloorCavern_Room9_Text_ArchieWhyDidKyogreDisappear:
	.string "{CHN}水梧桐：有点不对劲…\p"
	.string "红色宝珠应该能唤醒\n"
	.string "并控制盖欧卡…\p"
	.string "但是… 为什么？\n"
	.string "盖欧卡为什么消失了？\p"
	.string "为什么？！$"

SeafloorCavern_Room9_Text_MaxieWhatHaveYouWrought:
	.string "{CHN}赤焰松：你做了什么？\p"
	.string "水梧桐… 你终于唤醒了\n"
	.string "盖欧卡，对吧？\p"
	.string "如果这场暴雨永远\n"
	.string "下下去，世界会怎样？\p"
	.string "世界的大陆将被\n"
	.string "不断上涨的海水淹没…$"

SeafloorCavern_Room9_Text_ArchieDontGetAllHighAndMighty:
	.string "{CHN}水梧桐：什…什么？！\n"
	.string "别跟我摆架子！\p"
	.string "激怒固拉多的\n"
	.string "不是你们火焰队吗？\p"
	.string "只要有这颗红色宝珠，\n"
	.string "我就应该能控制盖欧卡…\p"
	.string "我应该能控制它…$"

SeafloorCavern_Room9_Text_MaxieWeDontHaveTimeToArgue:
	.string "{CHN}赤焰松：我们没时间\n"
	.string "在这里争吵！\p"
	.string "出去自己看看！\p"
	.string "看看你造成的\n"
	.string "是不是我们想要的世界！$"

SeafloorCavern_Room9_Text_MaxieComeOnPlayer:
	.string "{CHN}赤焰松：{PLAYER}，快，你也\n"
	.string "得赶紧离开这里！$"
