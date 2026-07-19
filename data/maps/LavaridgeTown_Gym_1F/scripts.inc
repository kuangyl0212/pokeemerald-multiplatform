LavaridgeTown_Gym_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_Gym_1F_OnTransition
	.byte 0

LavaridgeTown_Gym_1F_OnTransition:
	call LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars
	call LavaridgeTown_Gym_1F_EventScript_CheckBuryTrainers
	end

/* Unclear where/if these temp vars are getting checked*/
LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars::
	setvar VAR_TEMP_B, 0
	setvar VAR_TEMP_C, 0
	setvar VAR_TEMP_D, 0
	setvar VAR_TEMP_E, 0
	setvar VAR_TEMP_F, 0
	goto_if_defeated TRAINER_COLE, LavaridgeTown_Gym_1F_EventScript_SetGeraldTempVar
	setvar VAR_TEMP_B, 1
LavaridgeTown_Gym_1F_EventScript_SetGeraldTempVar::
	goto_if_defeated TRAINER_GERALD, LavaridgeTown_Gym_1F_EventScript_SetAxleTempVar
	setvar VAR_TEMP_C, 1
LavaridgeTown_Gym_1F_EventScript_SetAxleTempVar::
	goto_if_defeated TRAINER_AXLE, LavaridgeTown_Gym_1F_EventScript_SetDanielleTempVar
	setvar VAR_TEMP_D, 1
LavaridgeTown_Gym_1F_EventScript_SetDanielleTempVar::
	goto_if_defeated TRAINER_DANIELLE, LavaridgeTown_Gym_1F_EventScript_EndSetTrainerTempVars
	setvar VAR_TEMP_E, 1
LavaridgeTown_Gym_1F_EventScript_EndSetTrainerTempVars::
	return

LavaridgeTown_Gym_1F_EventScript_CheckBuryTrainers::
	goto_if_defeated TRAINER_COLE, LavaridgeTown_Gym_1F_EventScript_CheckBuryGerald
	setobjectmovementtype LOCALID_COLE, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_CheckBuryGerald::
	goto_if_defeated TRAINER_GERALD, LavaridgeTown_Gym_1F_EventScript_CheckBuryAxle
	setobjectmovementtype LOCALID_GERALD, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_CheckBuryAxle::
	goto_if_defeated TRAINER_AXLE, LavaridgeTown_Gym_1F_EventScript_CheckBuryDanielle
	setobjectmovementtype LOCALID_AXLE, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_CheckBuryDanielle::
	goto_if_defeated TRAINER_DANIELLE, LavaridgeTown_Gym_1F_EventScript_EndCheckBuryTrainers
	setobjectmovementtype LOCALID_DANIELLE, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_EndCheckBuryTrainers::
	return

LavaridgeTown_Gym_1F_EventScript_Flannery::
	trainerbattle_single TRAINER_FLANNERY_1, LavaridgeTown_Gym_1F_Text_FlanneryIntro, LavaridgeTown_Gym_1F_Text_FlanneryDefeat, LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, LavaridgeTown_Gym_1F_EventScript_FlanneryRematch
	goto_if_unset FLAG_RECEIVED_TM_OVERHEAT, LavaridgeTown_Gym_1F_EventScript_GiveOverheat2
	msgbox LavaridgeTown_Gym_1F_Text_FlanneryPostBattle, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated::
	message LavaridgeTown_Gym_1F_Text_ReceivedHeatBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox LavaridgeTown_Gym_1F_Text_ExplainHeatBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_WHITEOUT_TO_LAVARIDGE
	setflag FLAG_DEFEATED_LAVARIDGE_GYM
	setflag FLAG_BADGE04_GET
	addvar VAR_PETALBURG_GYM_STATE, 1
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	setvar VAR_0x8008, 4
	call Common_EventScript_SetGymTrainers
	setflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	setvar VAR_LAVARIDGE_TOWN_STATE, 1
	call LavaridgeTown_Gym_1F_EventScript_GiveOverheat
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox LavaridgeTown_Gym_1F_Text_RegisteredFlannery, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_FLANNERY_MATCH_CALL
	release
	end

LavaridgeTown_Gym_1F_EventScript_GiveOverheat2::
	giveitem ITEM_TM_OVERHEAT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox LavaridgeTown_Gym_1F_Text_ExplainOverheat, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_OVERHEAT
	release
	end

LavaridgeTown_Gym_1F_EventScript_GiveOverheat::
	giveitem ITEM_TM_OVERHEAT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox LavaridgeTown_Gym_1F_Text_ExplainOverheat, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_OVERHEAT
	return

LavaridgeTown_Gym_1F_EventScript_FlanneryRematch::
	trainerbattle_rematch_double TRAINER_FLANNERY_1, LavaridgeTown_Gym_1F_Text_FlanneryPreRematch, LavaridgeTown_Gym_1F_Text_FlanneryRematchDefeat, LavaridgeTown_Gym_1F_Text_FlanneryRematchNeedTwoMons
	msgbox LavaridgeTown_Gym_1F_Text_FlanneryPostRematch, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Cole::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_COLE, LOCALID_COLE, LavaridgeTown_Gym_1F_Text_ColeIntro, LavaridgeTown_Gym_1F_Text_ColeDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_ColePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_EventScript_CheckTrainerScript::
	call LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars
	release
	special ShouldTryGetTrainerScript
	goto_if_eq VAR_RESULT, 1, EventScript_GotoTrainerScript
	end

LavaridgeTown_Gym_1F_EventScript_Axle::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_AXLE, LOCALID_AXLE, LavaridgeTown_Gym_1F_Text_AxleIntro, LavaridgeTown_Gym_1F_Text_AxleDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_AxlePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Keegan::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_KEEGAN, LOCALID_KEEGAN, LavaridgeTown_Gym_B1F_Text_KeeganIntro, LavaridgeTown_Gym_B1F_Text_KeeganDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_KeeganPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Danielle::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_DANIELLE, LOCALID_DANIELLE, LavaridgeTown_Gym_1F_Text_DanielleIntro, LavaridgeTown_Gym_1F_Text_DanielleDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_DaniellePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Gerald::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_GERALD, LOCALID_GERALD, LavaridgeTown_Gym_1F_Text_GeraldIntro, LavaridgeTown_Gym_1F_Text_GeraldDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_GeraldPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Jace::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_JACE, LOCALID_JACE, LavaridgeTown_Gym_B1F_Text_JaceIntro, LavaridgeTown_Gym_B1F_Text_JaceDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_JacePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Jeff::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_JEFF, LOCALID_JEFF, LavaridgeTown_Gym_B1F_Text_JeffIntro, LavaridgeTown_Gym_B1F_Text_JeffDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_JeffPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Eli::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_ELI, LOCALID_ELI, LavaridgeTown_Gym_B1F_Text_EliIntro, LavaridgeTown_Gym_B1F_Text_EliDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_EliPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, LavaridgeTown_Gym_1F_EventScript_GymGuidePostVictory
	msgbox LavaridgeTown_Gym_1F_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_GymGuidePostVictory::
	msgbox LavaridgeTown_Gym_1F_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE04_GET, LavaridgeTown_Gym_1F_EventScript_GymStatueCertified
	goto LavaridgeTown_Gym_1F_EventScript_GymStatue
	end

LavaridgeTown_Gym_1F_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE04_GET, LavaridgeTown_Gym_1F_EventScript_GymStatueCertified
	goto LavaridgeTown_Gym_1F_EventScript_GymStatue
	end

LavaridgeTown_Gym_1F_EventScript_GymStatueCertified::
	msgbox LavaridgeTown_Gym_1F_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_Gym_1F_EventScript_GymStatue::
	msgbox LavaridgeTown_Gym_1F_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_Gym_1F_Text_GymGuideAdvice:
	.string "{CHN}嘿，最近怎么样，\n"
	.string "迈向冠军的{PLAYER}？\p"
	.string "烟突道馆馆主亚莎\n"
	.string "使用火属性宝可梦。\p"
	.string "她对宝可梦的热情比\n"
	.string "火山还要强烈、炽热。\p"
	.string "别离她太近——会烧伤的！\n"
	.string "用水浇灭她，然后\l"
	.string "上吧！$"

LavaridgeTown_Gym_1F_Text_GymGuidePostVictory:
	.string "{CHN}哟！那真是一场火热激烈的战斗！$"

LavaridgeTown_Gym_1F_Text_ColeIntro:
	.string "{CHN}噢噢噢噢噢！\n"
	.string "哎呀，好烫！$"

LavaridgeTown_Gym_1F_Text_ColeDefeat:
	.string "{CHN}汗水迷住了眼睛，我看不清了……$"

LavaridgeTown_Gym_1F_Text_ColePostBattle:
	.string "{CHN}埋在热沙里能促进\n"
	.string "血液循环。\p"
	.string "对缓解关节疼痛\n"
	.string "很有效。$"

LavaridgeTown_Gym_1F_Text_AxleIntro:
	.string "{CHN}我正在缓解压力。\n"
	.string "别来烦我让我更有压力！$"

LavaridgeTown_Gym_1F_Text_AxleDefeat:
	.string "{CHN}希望亚莎好好用火焰烧你！$"

LavaridgeTown_Gym_1F_Text_AxlePostBattle:
	.string "{CHN}哈啊……呼……\p"
	.string "在热沙里埋太久，\n"
	.string "会让人精疲力竭……$"

LavaridgeTown_Gym_B1F_Text_KeeganIntro:
	.string "{CHN}你现在一定累了吧。\n"
	.string "想在热沙里休息一下，\l"
	.string "对吧？\p"
	.string "但你应该知道，保持\n"
	.string "意志力对所有训练家\l"
	.string "来说都是重要的能力。$"

LavaridgeTown_Gym_B1F_Text_KeeganDefeat:
	.string "{CHN}玩火者必自焚……$"

LavaridgeTown_Gym_B1F_Text_KeeganPostBattle:
	.string "{CHN}你的实力是真的……\n"
	.string "但我们的馆主亚莎很强。\p"
	.string "如果不小心，你会被\n"
	.string "严重烧伤的。$"

LavaridgeTown_Gym_1F_Text_GeraldIntro:
	.string "{CHN}你的宝可梦能承受\n"
	.string "392度的高温吗？$"

LavaridgeTown_Gym_1F_Text_GeraldDefeat:
	.string "{CHN}烧得还不够热……$"

LavaridgeTown_Gym_1F_Text_GeraldPostBattle:
	.string "{CHN}岩浆的温度是\n"
	.string "392度。\p"
	.string "你的宝可梦打败了我，所以它们\n"
	.string "应该能在岩浆中存活。$"

LavaridgeTown_Gym_1F_Text_DanielleIntro:
	.string "{CHN}嗯……\n"
	.string "好吧，我和你对战。$"

LavaridgeTown_Gym_1F_Text_DanielleDefeat:
	.string "{CHN}哦，你太强了。$"

LavaridgeTown_Gym_1F_Text_DaniellePostBattle:
	.string "{CHN}我要成为像亚莎那样\n"
	.string "既美丽又强大的训练家。$"

LavaridgeTown_Gym_B1F_Text_JaceIntro:
	.string "{CHN}来吧，打起精神！\n"
	.string "趁我的热情还没冷却，开战吧！$"

LavaridgeTown_Gym_B1F_Text_JaceDefeat:
	.string "{CHN}明明这么热，我的心\n"
	.string "却被冰封住了……$"

LavaridgeTown_Gym_B1F_Text_JacePostBattle:
	.string "{CHN}看你身上燃烧的战斗精神，\n"
	.string "你可能有机会\l"
	.string "战胜我们的馆主。$"

LavaridgeTown_Gym_B1F_Text_JeffIntro:
	.string "{CHN}看那熊熊燃烧的火焰！\n"
	.string "它们是为我的胜利而燃烧的！$"

LavaridgeTown_Gym_B1F_Text_JeffDefeat:
	.string "{CHN}事情不太顺利。$"

LavaridgeTown_Gym_B1F_Text_JeffPostBattle:
	.string "{CHN}嗯，那又怎样？我说那又怎样？\n"
	.string "我能光脚走在炭火上！\p"
	.string "……你想都别想试！$"

LavaridgeTown_Gym_B1F_Text_EliIntro:
	.string "{CHN}我喜欢山，\n"
	.string "但我特别喜欢火山。$"

LavaridgeTown_Gym_B1F_Text_EliDefeat:
	.string "{CHN}嗯，看来我输了，\n"
	.string "而且从头到尾都没占过上风。$"

LavaridgeTown_Gym_B1F_Text_EliPostBattle:
	.string "{CHN}我留在这里是因为我成了\n"
	.string "亚莎力量的粉丝。\p"
	.string "嘿嘿嘿嘿。$"

LavaridgeTown_Gym_1F_Text_FlanneryIntro:
	.string "{CHN}欢迎……不，等等。\p"
	.string "弱小的训练家，很高兴见到你\n"
	.string "来到这里！\p"
	.string "我被委托管理……\n"
	.string "不，等等。\p"
	.string "我是亚莎，是这里的道馆\n"
	.string "馆主！\p"
	.string "呃……\n"
	.string "虽然我才刚当上馆主不久，\l"
	.string "但别小看我！\p"
	.string "凭借从祖父那里继承的技艺，\n"
	.string "我要，呃……展示我们\l"
	.string "在这片土地上磨练出的火热招式！$"

LavaridgeTown_Gym_1F_Text_FlanneryDefeat:
	.string "{CHN}哦……\n"
	.string "我想我太用力了……\p"
	.string "我……我才刚刚成为\n"
	.string "道馆馆主。\p"
	.string "我太努力想成为\n"
	.string "不是我自己的人。\p"
	.string "我必须用我自己的方式。如果\n"
	.string "我不这样，我的宝可梦会困惑的。\p"
	.string "谢谢你教会我这一点。\n"
	.string "为此，这个给你。$"

LavaridgeTown_Gym_1F_Text_ReceivedHeatBadge:
	.string "{CHN}{PLAYER}从亚莎那里\n"
	.string "获得了高温徽章。$"

LavaridgeTown_Gym_1F_Text_ExplainHeatBadgeTakeThis:
	.string "{CHN}如果你有高温徽章，所有\n"
	.string "50级以下的宝可梦，即使是\l"
	.string "和别人交换来的，也会\l"
	.string "完全服从你。\p"
	.string "而且，它能让宝可梦\n"
	.string "在战斗外使用秘传学习器怪力。\p"
	.string "这是我的心意。\n"
	.string "别客气，收下吧！$"

LavaridgeTown_Gym_1F_Text_ExplainOverheat:
	.string "{CHN}那个TM50里包含的是过热。\p"
	.string "那招会对对手\n"
	.string "造成巨大伤害。\p"
	.string "但它也会大幅降低使用它的\n"
	.string "宝可梦的特攻。可能不\l"
	.string "适合持久的战斗。$"

LavaridgeTown_Gym_1F_Text_RegisteredFlannery:
	.string "{CHN}已将道馆馆主亚莎\n"
	.string "登录到宝可梦领航员。$"

LavaridgeTown_Gym_1F_Text_FlanneryPostBattle:
	.string "{CHN}你的力量让我想起了某人……\p"
	.string "哦！我知道了！你战斗起来像千里，\n"
	.string "橙华道馆的馆主。$"

LavaridgeTown_Gym_1F_Text_GymStatue:
	.string "{CHN}烟突市宝可梦道馆$"

LavaridgeTown_Gym_1F_Text_GymStatueCertified:
	.string "{CHN}烟突市宝可梦道馆\p"
	.string "亚莎认证的训练家：\n"
	.string "{PLAYER}$"

LavaridgeTown_Gym_1F_Text_FlanneryPreRematch:
	.string "{CHN}亚莎：输掉一场战斗不会\n"
	.string "让我气馁。\p"
	.string "我爱宝可梦。\n"
	.string "我爱战斗。\l"
	.string "而且……我爱这个道馆！\p"
	.string "让我们在另一场战斗中\n"
	.string "交换火热的招式吧！$"

LavaridgeTown_Gym_1F_Text_FlanneryRematchDefeat:
	.string "{CHN}呼！\n"
	.string "快要爆发了！$"

LavaridgeTown_Gym_1F_Text_FlanneryPostRematch:
	.string "{CHN}亚莎：我输了比赛，\n"
	.string "但我完全满足。\p"
	.string "我难得能享受一场\n"
	.string "这么激烈的战斗。\p"
	.string "下次再来一场\n"
	.string "这样的战斗吧！$"

LavaridgeTown_Gym_1F_Text_FlanneryRematchNeedTwoMons:
	.string "{CHN}亚莎：输掉一场战斗不会\n"
	.string "让我气馁。\p"
	.string "我爱宝可梦。\n"
	.string "我爱战斗。\l"
	.string "而且……我爱这个道馆！\p"
	.string "让我们在另一场战斗中\n"
	.string "交换火热的招式吧！\p"
	.string "哦，等等。你是不是只有一只\n"
	.string "能战斗的宝可梦？\p"
	.string "我不想这么说，但你来\n"
	.string "找我时，至少带两只宝可梦。$"
