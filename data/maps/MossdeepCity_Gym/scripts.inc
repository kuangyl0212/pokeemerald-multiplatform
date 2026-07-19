MossdeepCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MossdeepCity_Gym_OnLoad
	.byte 0

/* NOTE: Mossdeep Gym was redesigned between R/S and E. Leftover (and now functionally unused) scripts are commented below*/

/* All the below checks are leftover from RS. FLAG_MOSSDEEP_GYM_SWITCH_X is never set*/
MossdeepCity_Gym_OnLoad:
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_1, MossdeepCity_Gym_EventScript_SetSwitch1Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch2
	end

MossdeepCity_Gym_EventScript_CheckSwitch2::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_2, MossdeepCity_Gym_EventScript_SetSwitch2Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch3
	end

MossdeepCity_Gym_EventScript_CheckSwitch3::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_3, MossdeepCity_Gym_EventScript_SetSwitch3Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch4
	end

MossdeepCity_Gym_EventScript_CheckSwitch4::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_4, MossdeepCity_Gym_EventScript_SetSwitch4Metatiles
	end

/* All the below set metatile scripts are leftover from RS and are functionally unused*/
MossdeepCity_Gym_EventScript_SetSwitch1Metatiles::
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch2
	end

MossdeepCity_Gym_EventScript_SetSwitch2Metatiles::
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch3
	end

MossdeepCity_Gym_EventScript_SetSwitch3Metatiles::
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch4
	end

MossdeepCity_Gym_EventScript_SetSwitch4Metatiles::
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Up, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Down, TRUE
	end

MossdeepCity_Gym_EventScript_TateAndLiza::
	trainerbattle_double TRAINER_TATE_AND_LIZA_1, MossdeepCity_Gym_Text_TateAndLizaIntro, MossdeepCity_Gym_Text_TateAndLizaDefeat, MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons, MossdeepCity_Gym_EventScript_TateAndLizaDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MossdeepCity_Gym_EventScript_TateAndLizaRematch
	goto_if_unset FLAG_RECEIVED_TM_CALM_MIND, MossdeepCity_Gym_EventScript_GiveCalmMind2
	msgbox MossdeepCity_Gym_Text_TateAndLizaPostBattle, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Gym_EventScript_TateAndLizaDefeated::
	message MossdeepCity_Gym_Text_ReceivedMindBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MossdeepCity_Gym_Text_ExplainMindBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_MOSSDEEP_GYM
	setflag FLAG_BADGE07_GET
	setflag FLAG_HIDE_AQUA_HIDEOUT_GRUNTS
	clearflag FLAG_HIDE_SLATEPORT_CITY_STERNS_SHIPYARD_MR_BRINEY
	clearflag FLAG_UNKNOWN_0x393
	setvar VAR_0x8008, 7
	call Common_EventScript_SetGymTrainers
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_PATRONS
	clearflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_2F_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_2F_STEVEN
	setvar VAR_MOSSDEEP_CITY_STATE, 1
	setflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_STEVEN
	setvar VAR_MOSSDEEP_SPACE_CENTER_STATE, 1
	call MossdeepCity_Gym_EventScript_GiveCalmMind
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MossdeepCity_Gym_Text_RegisteredTateAndLiza, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_TATE_AND_LIZA_MATCH_CALL
	release
	end

MossdeepCity_Gym_EventScript_GiveCalmMind2::
	giveitem ITEM_TM_CALM_MIND
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox MossdeepCity_Gym_Text_ExplainCalmMind, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_CALM_MIND
	release
	end

MossdeepCity_Gym_EventScript_GiveCalmMind::
	giveitem ITEM_TM_CALM_MIND
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox MossdeepCity_Gym_Text_ExplainCalmMind, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_CALM_MIND
	return

MossdeepCity_Gym_EventScript_TateAndLizaRematch::
	trainerbattle_rematch_double TRAINER_TATE_AND_LIZA_1, MossdeepCity_Gym_Text_TateAndLizaPreRematch, MossdeepCity_Gym_Text_TateAndLizaRematchDefeat, MossdeepCity_Gym_Text_TateAndLizaRematchNeedTwoMons
	msgbox MossdeepCity_Gym_Text_TateAndLizaPostRematch, MSGBOX_AUTOCLOSE
	end

/* All the below switch scripts are leftover from RS and are functionally unused*/
MossdeepCity_Gym_EventScript_Switch1::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_1, MossdeepCity_Gym_EventScript_ClearSwitch1
	setflag FLAG_MOSSDEEP_GYM_SWITCH_1
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed::
	special DrawWholeMapView
	playse SE_CLICK
	releaseall
	end

MossdeepCity_Gym_EventScript_ClearSwitch1::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_1
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch2::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_2, MossdeepCity_Gym_EventScript_ClearSwitch2
	setflag FLAG_MOSSDEEP_GYM_SWITCH_2
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch2::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_2
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Down, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch3::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_3, MossdeepCity_Gym_EventScript_ClearSwitch3
	setflag FLAG_MOSSDEEP_GYM_SWITCH_3
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch3::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_3
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch4::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_4, MossdeepCity_Gym_EventScript_ClearSwitch4
	setflag FLAG_MOSSDEEP_GYM_SWITCH_4
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Up, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch4::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_4
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_WarpToEntrance::
	lockall
	warpmossdeepgym MAP_MOSSDEEP_CITY_GYM, 7, 30
	waitstate
	releaseall
	end

MossdeepCity_Gym_EventScript_Preston::
	trainerbattle_single TRAINER_PRESTON, MossdeepCity_Gym_Text_PrestonIntro, MossdeepCity_Gym_Text_PrestonDefeat
	msgbox MossdeepCity_Gym_Text_PrestonPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Virgil::
	trainerbattle_single TRAINER_VIRGIL, MossdeepCity_Gym_Text_VirgilIntro, MossdeepCity_Gym_Text_VirgilDefeat
	msgbox MossdeepCity_Gym_Text_VirgilPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Blake::
	trainerbattle_single TRAINER_BLAKE, MossdeepCity_Gym_Text_BlakeIntro, MossdeepCity_Gym_Text_BlakeDefeat
	msgbox MossdeepCity_Gym_Text_BlakePostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Hannah::
	trainerbattle_single TRAINER_HANNAH, MossdeepCity_Gym_Text_HannahIntro, MossdeepCity_Gym_Text_HannahDefeat
	msgbox MossdeepCity_Gym_Text_HannahPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Samantha::
	trainerbattle_single TRAINER_SAMANTHA, MossdeepCity_Gym_Text_SamanthaIntro, MossdeepCity_Gym_Text_SamanthaDefeat
	msgbox MossdeepCity_Gym_Text_SamanthaPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Maura::
	trainerbattle_single TRAINER_MAURA, MossdeepCity_Gym_Text_MauraIntro, MossdeepCity_Gym_Text_MauraDefeat
	msgbox MossdeepCity_Gym_Text_MauraPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Sylvia::
	trainerbattle_single TRAINER_SYLVIA, MossdeepCity_Gym_Text_SylviaIntro, MossdeepCity_Gym_Text_SylviaDefeat
	msgbox MossdeepCity_Gym_Text_SylviaPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Nate::
	trainerbattle_single TRAINER_NATE, MossdeepCity_Gym_Text_NateIntro, MossdeepCity_Gym_Text_NateDefeat
	msgbox MossdeepCity_Gym_Text_NatePostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Macey::
	trainerbattle_single TRAINER_MACEY, MossdeepCity_Gym_Text_MaceyIntro, MossdeepCity_Gym_Text_MaceyDefeat
	msgbox MossdeepCity_Gym_Text_MaceyPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Clifford::
	trainerbattle_single TRAINER_CLIFFORD, MossdeepCity_Gym_Text_CliffordIntro, MossdeepCity_Gym_Text_CliffordDefeat
	msgbox MossdeepCity_Gym_Text_CliffordPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Nicholas::
	trainerbattle_single TRAINER_NICHOLAS, MossdeepCity_Gym_Text_NicholasIntro, MossdeepCity_Gym_Text_NicholasDefeat
	msgbox MossdeepCity_Gym_Text_NicholasPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Kathleen::
	trainerbattle_single TRAINER_KATHLEEN, MossdeepCity_Gym_Text_KathleenIntro, MossdeepCity_Gym_Text_KathleenDefeat
	msgbox MossdeepCity_Gym_Text_KathleenPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MOSSDEEP_GYM, MossdeepCity_Gym_EventScript_GymGuidePostVictory
	msgbox MossdeepCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Gym_EventScript_GymGuidePostVictory::
	msgbox MossdeepCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

/* Leftover from RS, functionally unused*/
MossdeepCity_Gym_Movement_WaitAfterSwitchUse:
	delay_16
	delay_16
	step_end

MossdeepCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE07_GET, MossdeepCity_Gym_EventScript_GymStatueCertified
	goto MossdeepCity_Gym_EventScript_GymStatue
	end

MossdeepCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE07_GET, MossdeepCity_Gym_EventScript_GymStatueCertified
	goto MossdeepCity_Gym_EventScript_GymStatue
	end

MossdeepCity_Gym_EventScript_GymStatueCertified::
	msgbox MossdeepCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_Gym_EventScript_GymStatue::
	msgbox MossdeepCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_Gym_EventScript_YellowFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 0
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_BlueFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 1
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_GreenFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 2
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_PurpleFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 3
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_RedFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 4
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_Text_GymGuideAdvice:
	.string "{CHN}哟，朝着冠军迈进的\n"
	.string "{PLAYER}，最近怎么样？\p"
	.string "这里的道馆馆主使用的是\n"
	.string "超能力属性的宝可梦。\p"
	.string "如果你用格斗属性或毒属性的\n"
	.string "宝可梦去对战，\l"
	.string "会遭到严重的打击！\p"
	.string "而且，他们会用出色的\n"
	.string "组合攻击来对付你。\p"
	.string "想要获胜，就得让他们看到\n"
	.string "你和宝可梦之间的\l"
	.string "默契。加油吧！$"

MossdeepCity_Gym_Text_GymGuidePostVictory:
	.string "{CHN}哇，你真了不起！\n"
	.string "你是一位出色的训练家！$"

MossdeepCity_Gym_Text_PrestonIntro:
	.string "{CHN}对战取决于精神的力量！\n"
	.string "精神软弱的人永远赢不了！$"

MossdeepCity_Gym_Text_PrestonDefeat:
	.string "{CHN}我输了！\n"
	.string "我必须再次磨炼我的精神！$"

MossdeepCity_Gym_Text_PrestonPostBattle:
	.string "{CHN}优柔寡断的人会输。\n"
	.string "这是我对你的忠告。$"

MossdeepCity_Gym_Text_VirgilIntro:
	.string "{CHN}让我看看你的才能！$"

MossdeepCity_Gym_Text_VirgilDefeat:
	.string "{CHN}你拥有惊人的才能！$"

MossdeepCity_Gym_Text_VirgilPostBattle:
	.string "{CHN}如果世上有天才的话，\n"
	.string "那我们的道馆馆主就是！\p"
	.string "不过，你可能比他们\n"
	.string "更有才能……$"

MossdeepCity_Gym_Text_BlakeIntro:
	.string "{CHN}呼呼呼呼……看我让精灵球\n"
	.string "用念力浮起来！\p"
	.string "嗷嗷嗷嗷嗷嗷嗷！\n"
	.string "… … … … … … …\p"
	.string "有时候，我会失调……$"

MossdeepCity_Gym_Text_BlakeDefeat:
	.string "{CHN}我的宝可梦对战技巧也\n"
	.string "失调了！$"

MossdeepCity_Gym_Text_BlakePostBattle:
	.string "{CHN}精灵球太重了，用念力\n"
	.string "举不起来。但是这个灰尘团……\p"
	.string "呜呜呜呜呜呜呜呜！\n"
	.string "… … … … … …\p"
	.string "不，我没有作弊！\n"
	.string "我没有吹气！真的！$"

MossdeepCity_Gym_Text_HannahIntro:
	.string "{CHN}输给我的时候，别太自责。\p"
	.string "不是你太弱——而是我\n"
	.string "太强了！$"

MossdeepCity_Gym_Text_HannahDefeat:
	.string "{CHN}你太强了！$"

MossdeepCity_Gym_Text_HannahPostBattle:
	.string "{CHN}我不会因为输了就\n"
	.string "气馁。我只需要更加努力训练。\p"
	.string "积极的心态——那是我的\n"
	.string "优点！$"

MossdeepCity_Gym_Text_SamanthaIntro:
	.string "{CHN}我看到了……\n"
	.string "我看到了你的未来……\p"
	.string "如果你能打败我，我就告诉你\n"
	.string "你的未来！$"

MossdeepCity_Gym_Text_SamanthaDefeat:
	.string "{CHN}我认输！$"

MossdeepCity_Gym_Text_SamanthaPostBattle:
	.string "{CHN}你将和我们的道馆馆主\n"
	.string "展开一场激烈的战斗……\p"
	.string "结果嘛……\n"
	.string "我可不会告诉你！$"

MossdeepCity_Gym_Text_MauraIntro:
	.string "{CHN}你走过的路……\n"
	.string "你经历过的事……\p"
	.string "用你学到的所有东西\n"
	.string "来挑战我吧！$"

MossdeepCity_Gym_Text_MauraDefeat:
	.string "{CHN}你走过了一条伟大的道路！$"

MossdeepCity_Gym_Text_MauraPostBattle:
	.string "{CHN}光明的前途属于那些\n"
	.string "勤奋努力的人。\p"
	.string "对于那些懒惰虚度的人，\n"
	.string "等待他们的只有绝望。\p"
	.string "善有善报，恶有恶报……$"

MossdeepCity_Gym_Text_SylviaIntro:
	.string "{CHN}即使冒着生命危险，我也要\n"
	.string "赢得这场对战！$"

MossdeepCity_Gym_Text_SylviaDefeat:
	.string "{CHN}你做的事……\n"
	.string "让我感到恐惧……$"

MossdeepCity_Gym_Text_SylviaPostBattle:
	.string "{CHN}你居然敢打败我……\p"
	.string "如果你遇到什么\n"
	.string "可怕的事，可别怪我……$"

MossdeepCity_Gym_Text_NateIntro:
	.string "{CHN}呵呵呵。\p"
	.string "需要我让你看看超能力属性\n"
	.string "有多顽强吗。$"

MossdeepCity_Gym_Text_NateDefeat:
	.string "{CHN}哦！天哪！\n"
	.string "你的对战风格太棒了！$"

MossdeepCity_Gym_Text_NatePostBattle:
	.string "{CHN}我……我不会因为失败而动摇，\n"
	.string "无论多么糟糕。$"

MossdeepCity_Gym_Text_KathleenIntro:
	.string "{CHN}让我给你一个绝对可怕的\n"
	.string "惊悚时刻！$"

MossdeepCity_Gym_Text_KathleenDefeat:
	.string "{CHN}不——不要！$"

MossdeepCity_Gym_Text_KathleenPostBattle:
	.string "{CHN}你的生命力会传染！\n"
	.string "快离我远点！$"

MossdeepCity_Gym_Text_CliffordIntro:
	.string "{CHN}我也许过了鼎盛时期，但我劝\n"
	.string "你别小看我。$"

MossdeepCity_Gym_Text_CliffordDefeat:
	.string "{CHN}啊，你浑身充满了\n"
	.string "青春的力量！$"

MossdeepCity_Gym_Text_CliffordPostBattle:
	.string "{CHN}看来我无法战胜\n"
	.string "你青春的活力。$"

MossdeepCity_Gym_Text_MaceyIntro:
	.string "{CHN}你休想走到最后！\n"
	.string "只要有我在！$"

MossdeepCity_Gym_Text_MaceyDefeat:
	.string "{CHN}你怎么会强得\n"
	.string "这么离谱？$"

MossdeepCity_Gym_Text_MaceyPostBattle:
	.string "{CHN}哼！你可能很强，但你\n"
	.string "不适合超能力属性！\p"
	.string "你的对战方式有点粗暴！$"

MossdeepCity_Gym_Text_NicholasIntro:
	.string "{CHN}嗷嗷嗷！来尝尝我的宝可梦\n"
	.string "超级对战力量！$"

MossdeepCity_Gym_Text_NicholasDefeat:
	.string "{CHN}哦！\n"
	.string "被击败了！$"

MossdeepCity_Gym_Text_NicholasPostBattle:
	.string "{CHN}好！我想接下来我要开发一种\n"
	.string "特殊的无敌宝可梦力量。$"

MossdeepCity_Gym_Text_TateAndLizaIntro:
	.string "{CHN}枫：嘿嘿嘿……吓了一跳吗？\p"
	.string "南：呼呼呼……吓了一跳吗？\p"
	.string "枫：居然有两位道馆馆主？\n"
	.string "南：居然有两位道馆馆主？\p"
	.string "枫：我们是双胞胎！\n"
	.string "南：我们是双胞胎！\p"
	.string "枫：我们不需要说话，因为……\n"
	.string "南：我们各自都能明白……\p"
	.string "枫：对方在想什么……\n"
	.string "南：全在心里！\p"
	.string "枫：我们的这个组合……\n"
	.string "南：你能打败吗？$"

MossdeepCity_Gym_Text_TateAndLizaDefeat:
	.string "{CHN}枫：什么？！我们的组合……\n"
	.string "南：被瓦解了！\p"
	.string "枫：没办法了。你赢了……\n"
	.string "南：所以，作为认可，收下这个吧。$"

MossdeepCity_Gym_Text_ReceivedMindBadge:
	.string "{CHN}{PLAYER}从枫和南那里得到了\n"
	.string "心灵徽章。$"

MossdeepCity_Gym_Text_ExplainMindBadgeTakeThis:
	.string "{CHN}枫：心灵徽章能提升宝可梦的\n"
	.string "特攻和特防。\p"
	.string "南：它还能让你在对战外使用\n"
	.string "秘传学习器潜水。\p"
	.string "枫：你还应该收下这个。$"

MossdeepCity_Gym_Text_ExplainCalmMind:
	.string "{CHN}枫：那个招式学习器04里装的是……\n"
	.string "南：冥想！\p"
	.string "枫：它能提升特攻，而且……\n"
	.string "南：它能提升特防！\p"
	.string "枫：这是一个非常适合……\n"
	.string "南：超能力宝可梦的招式！\p"
	.string "… … … … … …$"

MossdeepCity_Gym_Text_RegisteredTateAndLiza:
	.string "{CHN}已将道馆馆主枫&南\n"
	.string "登录到宝可梦导航器中。$"

MossdeepCity_Gym_Text_TateAndLizaPostBattle:
	.string "{CHN}枫：看来你和宝可梦之间的羁绊\n"
	.string "远比我们\l"
	.string "作为双胞胎的羁绊还要深厚。\p"
	.string "南：你会变得更强！\n"
	.string "我们和你对战过，所以知道。$"

MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons:
	.string "{CHN}枫：嘿嘿嘿……吓了一跳吗？\p"
	.string "南：居然有两位道馆馆主？\p"
	.string "枫：糟糕，你只有一只……\n"
	.string "南：能对战的宝可梦。\p"
	.string "枫：这样我们没法对战！\p"
	.string "南：如果你想挑战我们，\n"
	.string "多带几只宝可梦来吧。$"

MossdeepCity_Gym_Text_GymStatue:
	.string "{CHN}琉璃市宝可梦道馆$"

MossdeepCity_Gym_Text_GymStatueCertified:
	.string "{CHN}琉璃市宝可梦道馆\p"
	.string "南和枫认证的训练家：\n"
	.string "{PLAYER}$"

MossdeepCity_Gym_Text_TateAndLizaPreRematch:
	.string "{CHN}枫：宝可梦……\n"
	.string "南：宝可梦……\p"
	.string "枫：通过改变队伍的组合……\n"
	.string "南：对战风格也会改变。\p"
	.string "枫：但是我……\n"
	.string "南：但是我……\p"
	.string "枫：我会永远和南在一起！\n"
	.string "南：我会永远和枫在一起！\p"
	.string "枫：我们的组合……\n"
	.string "南：我们会一次又一次地展示给你看！$"

MossdeepCity_Gym_Text_TateAndLizaRematchDefeat:
	.string "{CHN}枫：你和你的宝可梦……\n"
	.string "南：简直就像兄弟姐妹一样！$"

MossdeepCity_Gym_Text_TateAndLizaPostRematch:
	.string "{CHN}枫：你可以把我们击倒，\n"
	.string "但我们绝不会倒下！\p"
	.string "南：因为我们两个，\n"
	.string "永远互相支持！$"

MossdeepCity_Gym_Text_TateAndLizaRematchNeedTwoMons:
	.string "{CHN}枫：你又回来了……\n"
	.string "南：你又回来了……\p"
	.string "枫：来和我们再战。\n"
	.string "南：来和我们再战。\p"
	.string "枫：可是……\n"
	.string "南：我们的对战……\p"
	.string "枫：你只带了一只宝可梦！\n"
	.string "南：你只带了一只宝可梦！\p"
	.string "枫：我们需要你至少带……\n"
	.string "南：两只宝可梦再回来。$"
