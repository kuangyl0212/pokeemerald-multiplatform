MauvilleCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MauvilleCity_Gym_OnLoad
	.byte 0

MauvilleCity_Gym_OnLoad:
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_DeactivatePuzzle
	switch VAR_MAUVILLE_GYM_STATE
	case 0, MauvilleCity_Gym_EventScript_UpdateBarriers
	case 1, MauvilleCity_Gym_EventScript_Switch1Pressed
	case 2, MauvilleCity_Gym_EventScript_Switch2Pressed
	case 3, MauvilleCity_Gym_EventScript_Switch3Pressed
	case 4, MauvilleCity_Gym_EventScript_Switch4Pressed
	end

MauvilleCity_Gym_EventScript_UpdateBarriers::
	goto_if_set FLAG_MAUVILLE_GYM_BARRIERS_STATE, MauvilleCity_Gym_EventScript_SetAltBarriers
	end

MauvilleCity_Gym_EventScript_SetAltBarriers::
	setmetatile 3, 11, METATILE_MauvilleGym_RedBeamV1_On, TRUE
	setmetatile 3, 12, METATILE_MauvilleGym_RedBeamV2_On, TRUE
	setmetatile 3, 13, METATILE_MauvilleGym_PoleTop_On, TRUE
	setmetatile 4, 10, METATILE_MauvilleGym_RedBeamH1_On, FALSE
	setmetatile 5, 10, METATILE_MauvilleGym_RedBeamH2_On, FALSE
	setmetatile 4, 11, METATILE_MauvilleGym_RedBeamH3_On, TRUE
	setmetatile 5, 11, METATILE_MauvilleGym_RedBeamH4_On, TRUE
	setmetatile 7, 10, METATILE_MauvilleGym_RedBeamH1_On, FALSE
	setmetatile 8, 10, METATILE_MauvilleGym_RedBeamH2_On, FALSE
	setmetatile 7, 11, METATILE_MauvilleGym_RedBeamH3_On, TRUE
	setmetatile 8, 11, METATILE_MauvilleGym_RedBeamH4_On, TRUE
	setmetatile 4, 13, METATILE_MauvilleGym_GreenBeamH1_Off, FALSE
	setmetatile 5, 13, METATILE_MauvilleGym_GreenBeamH2_Off, FALSE
	setmetatile 4, 14, METATILE_MauvilleGym_GreenBeamH3_Off, FALSE
	setmetatile 5, 14, METATILE_MauvilleGym_GreenBeamH4_Off, FALSE
	setmetatile 1, 10, METATILE_MauvilleGym_GreenBeamH1_Off, FALSE
	setmetatile 2, 10, METATILE_MauvilleGym_GreenBeamH2_Off, FALSE
	setmetatile 1, 11, METATILE_MauvilleGym_GreenBeamH3_Off, FALSE
	setmetatile 2, 11, METATILE_MauvilleGym_GreenBeamH4_Off, FALSE
	setmetatile 6, 8, METATILE_MauvilleGym_PoleBottom_On, TRUE
	setmetatile 6, 9, METATILE_MauvilleGym_FloorTile, FALSE
	setmetatile 6, 10, METATILE_MauvilleGym_PoleTop_Off, FALSE
	setmetatile 4, 6, METATILE_MauvilleGym_GreenBeamH1_Off, FALSE
	setmetatile 5, 6, METATILE_MauvilleGym_GreenBeamH2_Off, FALSE
	setmetatile 4, 7, METATILE_MauvilleGym_GreenBeamH3_Off, FALSE
	setmetatile 5, 7, METATILE_MauvilleGym_GreenBeamH4_Off, FALSE
	end

MauvilleCity_Gym_EventScript_Switch1Pressed::
	setvar VAR_0x8004, 0
	special MauvilleGymPressSwitch
	goto MauvilleCity_Gym_EventScript_UpdateBarriers
	end

MauvilleCity_Gym_EventScript_Switch2Pressed::
	setvar VAR_0x8004, 1
	special MauvilleGymPressSwitch
	goto MauvilleCity_Gym_EventScript_UpdateBarriers
	end

MauvilleCity_Gym_EventScript_Switch3Pressed::
	setvar VAR_0x8004, 2
	special MauvilleGymPressSwitch
	goto MauvilleCity_Gym_EventScript_UpdateBarriers
	end

MauvilleCity_Gym_EventScript_Switch4Pressed::
	setvar VAR_0x8004, 3
	special MauvilleGymPressSwitch
	goto MauvilleCity_Gym_EventScript_UpdateBarriers
	end

MauvilleCity_Gym_EventScript_DeactivatePuzzle::
	special MauvilleGymDeactivatePuzzle
	end

MauvilleCity_Gym_EventScript_Wattson::
	trainerbattle_single TRAINER_WATTSON_1, MauvilleCity_Gym_Text_WattsonIntro, MauvilleCity_Gym_Text_WattsonDefeat, MauvilleCity_Gym_EventScript_WattsonDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_Gym_EventScript_WattsonRematch
	goto_if_unset FLAG_RECEIVED_TM_SHOCK_WAVE, MauvilleCity_Gym_EventScript_GiveShockWave2
	goto_if_eq VAR_NEW_MAUVILLE_STATE, 2, MauvilleCity_Gym_EventScript_CompletedNewMauville
	msgbox MauvilleCity_Gym_Text_WattsonPostBattle, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_WattsonDefeated::
	message MauvilleCity_Gym_Text_ReceivedDynamoBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MauvilleCity_Gym_Text_ExplainDynamoBadgeTakeThis, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 3
	clearflag FLAG_HIDE_VERDANTURF_TOWN_SCOTT
	setflag FLAG_DEFEATED_MAUVILLE_GYM
	setflag FLAG_BADGE03_GET
	addvar VAR_PETALBURG_GYM_STATE, 1
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	setvar VAR_0x8008, 3
	call Common_EventScript_SetGymTrainers
	special MauvilleGymDeactivatePuzzle
	special DrawWholeMapView
	playse SE_UNLOCK
	call MauvilleCity_Gym_EventScript_GiveShockWave
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MauvilleCity_Gym_Text_RegisteredWattson, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WATTSON_MATCH_CALL
	release
	end

MauvilleCity_Gym_EventScript_GiveShockWave2::
	giveitem ITEM_TM_SHOCK_WAVE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox MauvilleCity_Gym_Text_ExplainShockWave, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_SHOCK_WAVE
	release
	end

MauvilleCity_Gym_EventScript_GiveShockWave::
	giveitem ITEM_TM_SHOCK_WAVE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox MauvilleCity_Gym_Text_ExplainShockWave, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_SHOCK_WAVE
	return

MauvilleCity_Gym_EventScript_CompletedNewMauville::
	msgbox MauvilleCity_Gym_Text_WattsonGoForthAndEndeavor, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_WattsonRematch::
	trainerbattle_rematch_double TRAINER_WATTSON_1, MauvilleCity_Gym_Text_WattsonPreRematch, MauvilleCity_Gym_Text_WattsonRematchDefeat, MauvilleCity_Gym_Text_WattsonRematchNeedTwoMons
	msgbox MauvilleCity_Gym_Text_WattsonPostRematch, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Switch1::
	lockall
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_SwitchDoNothing
	goto_if_eq VAR_MAUVILLE_GYM_STATE, 1, MauvilleCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_MAUVILLE_GYM_STATE, 1
	setvar VAR_0x8004, 0
	goto MauvilleCity_Gym_EventScript_PressFloorSwitch
	end

MauvilleCity_Gym_EventScript_Switch2::
	lockall
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_SwitchDoNothing
	goto_if_eq VAR_MAUVILLE_GYM_STATE, 2, MauvilleCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_MAUVILLE_GYM_STATE, 2
	setvar VAR_0x8004, 1
	goto MauvilleCity_Gym_EventScript_PressFloorSwitch
	end

MauvilleCity_Gym_EventScript_Switch3::
	lockall
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_SwitchDoNothing
	goto_if_eq VAR_MAUVILLE_GYM_STATE, 3, MauvilleCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_MAUVILLE_GYM_STATE, 3
	setvar VAR_0x8004, 2
	goto MauvilleCity_Gym_EventScript_PressFloorSwitch
	end

MauvilleCity_Gym_EventScript_Switch4::
	lockall
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_SwitchDoNothing
	goto_if_eq VAR_MAUVILLE_GYM_STATE, 4, MauvilleCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_MAUVILLE_GYM_STATE, 4
	setvar VAR_0x8004, 3
	goto MauvilleCity_Gym_EventScript_PressFloorSwitch
	end

MauvilleCity_Gym_EventScript_PressFloorSwitch::
	special MauvilleGymSetDefaultBarriers
	special MauvilleGymPressSwitch
	special DrawWholeMapView
	playse SE_UNLOCK
	goto_if_set FLAG_MAUVILLE_GYM_BARRIERS_STATE, MauvilleCity_Gym_EventScript_ClearBarriersAltState
	goto_if_unset FLAG_MAUVILLE_GYM_BARRIERS_STATE, MauvilleCity_Gym_EventScript_SetBarriersAltState
	releaseall
	end

MauvilleCity_Gym_EventScript_SwitchDoNothing::
	releaseall
	end

MauvilleCity_Gym_EventScript_SetBarriersAltState::
	setflag FLAG_MAUVILLE_GYM_BARRIERS_STATE
	releaseall
	end

MauvilleCity_Gym_EventScript_ClearBarriersAltState::
	clearflag FLAG_MAUVILLE_GYM_BARRIERS_STATE
	releaseall
	end

MauvilleCity_Gym_EventScript_Kirk::
	trainerbattle_single TRAINER_KIRK, MauvilleCity_Gym_Text_KirkIntro, MauvilleCity_Gym_Text_KirkDefeat
	msgbox MauvilleCity_Gym_Text_KirkPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Shawn::
	trainerbattle_single TRAINER_SHAWN, MauvilleCity_Gym_Text_ShawnIntro, MauvilleCity_Gym_Text_ShawnDefeat
	msgbox MauvilleCity_Gym_Text_ShawnPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Ben::
	trainerbattle_single TRAINER_BEN, MauvilleCity_Gym_Text_BenIntro, MauvilleCity_Gym_Text_BenDefeat
	msgbox MauvilleCity_Gym_Text_BenPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Vivian::
	trainerbattle_single TRAINER_VIVIAN, MauvilleCity_Gym_Text_VivianIntro, MauvilleCity_Gym_Text_VivianDefeat
	msgbox MauvilleCity_Gym_Text_VivianPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Angelo::
	trainerbattle_single TRAINER_ANGELO, MauvilleCity_Gym_Text_AngeloIntro, MauvilleCity_Gym_Text_AngeloDefeat
	msgbox MauvilleCity_Gym_Text_AngeloPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_GymGuidePostVictory
	msgbox MauvilleCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_GymGuidePostVictory::
	msgbox MauvilleCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE03_GET, MauvilleCity_Gym_EventScript_GymStatueCertified
	goto MauvilleCity_Gym_EventScript_GymStatue
	end

MauvilleCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE03_GET, MauvilleCity_Gym_EventScript_GymStatueCertified
	goto MauvilleCity_Gym_EventScript_GymStatue
	end

MauvilleCity_Gym_EventScript_GymStatueCertified::
	msgbox MauvilleCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

MauvilleCity_Gym_EventScript_GymStatue::
	msgbox MauvilleCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

MauvilleCity_Gym_Text_GymGuideAdvice:
	.string "{CHN}嘿，最近怎么样，\n"
	.string "未来的冠军{PLAYER}？\p"
	.string "紫堇道馆的馆主铁旋\n"
	.string "使用电属性的宝可梦。\p"
	.string "如果你用水属性的宝可梦\n"
	.string "挑战他，他会电到它们！噼啪！\p"
	.string "而且，他在道馆里到处都装了\n"
	.string "开关控制的门！真古怪！\p"
	.string "嘿，加油吧！$"

MauvilleCity_Gym_Text_GymGuidePostVictory:
	.string "{CHN}哇，你真带电！\n"
	.string "你把门给通电打开了！$"

MauvilleCity_Gym_Text_KirkIntro:
	.string "{CHN}我那带电的灵魂，将粉碎你的\n"
	.string "梦想，哇耶啊！$"

MauvilleCity_Gym_Text_KirkDefeat:
	.string "{CHN}那是接通电源、放大电流、\n"
	.string "超负荷驱动的电力，伙计！$"

MauvilleCity_Gym_Text_KirkPostBattle:
	.string "{CHN}宝可梦和摇滚，都是用心的事，\n"
	.string "哇耶！$"

MauvilleCity_Gym_Text_ShawnIntro:
	.string "{CHN}我在铁旋门下修行过！\n"
	.string "我绝不会轻易输掉！$"

MauvilleCity_Gym_Text_ShawnDefeat:
	.string "{CHN}被拔掉插头，关掉电源了……$"

MauvilleCity_Gym_Text_ShawnPostBattle:
	.string "{CHN}铁旋，我们的道馆馆主，\n"
	.string "已经出道很久很久了。\p"
	.string "甚至在你的爸爸出生之前\n"
	.string "他就在战斗了，那个硬骨头老头。$"

MauvilleCity_Gym_Text_BenIntro:
	.string "{CHN}这个道馆有谜题！\n"
	.string "很有趣吧？$"

MauvilleCity_Gym_Text_BenDefeat:
	.string "{CHN}输了真没意思……$"

MauvilleCity_Gym_Text_BenPostBattle:
	.string "{CHN}铁旋说他喜欢用开关\n"
	.string "布置小陷阱。$"

MauvilleCity_Gym_Text_VivianIntro:
	.string "{CHN}凭借我的魅力和宝可梦的招式，\n"
	.string "你会被电到的！$"

MauvilleCity_Gym_Text_VivianDefeat:
	.string "{CHN}你的实力让我触电了！$"

MauvilleCity_Gym_Text_VivianPostBattle:
	.string "{CHN}我听说紫堇市是由\n"
	.string "铁旋建立的。\p"
	.string "在我们成为训练家之前，\n"
	.string "他早就是训练家了。\l"
	.string "他一定知道各种各样的事情！$"

MauvilleCity_Gym_Text_AngeloIntro:
	.string "{CHN}我喜欢闪亮的东西！$"

MauvilleCity_Gym_Text_AngeloDefeat:
	.string "{CHN}哦……\n"
	.string "我的眼睛花了……$"

MauvilleCity_Gym_Text_AngeloPostBattle:
	.string "{CHN}紫堇道馆的铁旋有一个闪亮的\n"
	.string "额头。这让我很高兴！$"

MauvilleCity_Gym_Text_WattsonIntro:
	.string "{CHN}我已经放弃了改造城市的计划，\n"
	.string "真的。\p"
	.string "所以，我把时间花在\n"
	.string "道馆里制作门陷阱上。\p"
	.string "哦？你怎么在这里？\p"
	.string "什么？你说你已经通过了\n"
	.string "我所有的机关门？\p"
	.string "哇哈哈哈哈！\n"
	.string "那可真有意思！\p"
	.string "那么，我，紫堇道馆的馆主铁旋，\n"
	.string "要让你触电了！$"

MauvilleCity_Gym_Text_WattsonDefeat:
	.string "{CHN}哇哈哈哈哈！\n"
	.string "好吧，我输了！\p"
	.string "你给了我一次刺激的体验！\n"
	.string "拿着这个徽章！$"

MauvilleCity_Gym_Text_ReceivedDynamoBadge:
	.string "{CHN}{PLAYER}从铁旋那里\n"
	.string "得到了发电徽章。$"

MauvilleCity_Gym_Text_ExplainDynamoBadgeTakeThis:
	.string "{CHN}有了发电徽章，宝可梦\n"
	.string "就能在对战外使用碎岩了。\p"
	.string "而且，它还能让你的宝可梦\n"
	.string "稍微变快一点。\p"
	.string "嗯……\n"
	.string "你也应该收下这个！$"

MauvilleCity_Gym_Text_ExplainShockWave:
	.string "{CHN}那个招式学习器34里装有电击波。\p"
	.string "那是一个值得信赖的绝不会\n"
	.string "打偏的招式！你可以信赖它！\p"
	.string "………………$"

MauvilleCity_Gym_Text_RegisteredWattson:
	.string "{CHN}已将道馆馆主铁旋\n"
	.string "登录到宝可梦领航员中。$"

MauvilleCity_Gym_Text_WattsonPostBattle:
	.string "{CHN}看到你这样一位有前途的\n"
	.string "年轻训练家，我心中充满乐观！$"

MauvilleCity_Gym_Text_WattsonGoForthAndEndeavor:
	.string "{CHN}哇哈哈哈哈！\n"
	.string "前进并努力吧，年轻人！$"

MauvilleCity_Gym_Text_GymStatue:
	.string "{CHN}紫堇市宝可梦道馆$"

MauvilleCity_Gym_Text_GymStatueCertified:
	.string "{CHN}紫堇市宝可梦道馆\p"
	.string "铁旋认证的训练家：\n"
	.string "{PLAYER}$"

MauvilleCity_Gym_Text_WattsonPreRematch:
	.string "{CHN}铁旋：啊哈！终于来了！\n"
	.string "我知道你想要什么。\l"
	.string "你想要和我的宝可梦对战！\p"
	.string "哇哈哈哈哈！\p"
	.string "我会让你冒出火花的！\n"
	.string "别说我没警告过你！$"

MauvilleCity_Gym_Text_WattsonRematchDefeat:
	.string "{CHN}哦哦……\n"
	.string "我们的电池没电了……$"

MauvilleCity_Gym_Text_WattsonPostRematch:
	.string "{CHN}铁旋：我们得重新\n"
	.string "充电了。\p"
	.string "当我们充满电的时候，\n"
	.string "我们会很乐意接受你的挑战。\p"
	.string "所以，改天再来吧，\n"
	.string "好吗？$"

MauvilleCity_Gym_Text_WattsonRematchNeedTwoMons:
	.string "{CHN}铁旋：啊哈！终于来了！\n"
	.string "我知道你想要什么。\l"
	.string "你想要和我的宝可梦对战！\p"
	.string "哇哈哈哈哈！\p"
	.string "哎呀！等等！\n"
	.string "你只带了一只宝可梦！\p"
	.string "带两只或更多宝可梦\n"
	.string "来见我吧，好吗？$"
