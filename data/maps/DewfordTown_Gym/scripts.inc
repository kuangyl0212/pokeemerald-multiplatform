DewfordTown_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordTown_Gym_OnTransition
	.byte 0

DewfordTown_Gym_OnTransition:
	call DewfordTown_Gym_EventScript_SetFlashLevel
	end

DewfordTown_Gym_EventScript_SetFlashLevel::
	goto_if_defeated TRAINER_BRAWLY_1, DewfordTown_Gym_EventScript_SetLightsOn
	call DewfordTown_Gym_EventScript_CountTrainersDefeated
	copyvar VAR_0x8001, VAR_0x8000
	goto_if_eq VAR_0x8000, 0, DewfordTown_Gym_EventScript_SetFlashLevel7
	goto_if_eq VAR_0x8000, 1, DewfordTown_Gym_EventScript_SetFlashLevel6
	goto_if_eq VAR_0x8000, 2, DewfordTown_Gym_EventScript_SetFlashLevel5
	goto_if_eq VAR_0x8000, 3, DewfordTown_Gym_EventScript_SetFlashLevel4
	goto_if_eq VAR_0x8000, 4, DewfordTown_Gym_EventScript_SetFlashLevel3
	goto_if_eq VAR_0x8000, 5, DewfordTown_Gym_EventScript_SetFlashLevel2
	goto DewfordTown_Gym_EventScript_SetFlashLevel1

DewfordTown_Gym_EventScript_SetLightsOn::
	setflashlevel 0
	return

@ Brightest
DewfordTown_Gym_EventScript_SetFlashLevel1::
	setflashlevel 1
	return

DewfordTown_Gym_EventScript_SetFlashLevel2::
	setflashlevel 2
	return

DewfordTown_Gym_EventScript_SetFlashLevel3::
	setflashlevel 3
	return

DewfordTown_Gym_EventScript_SetFlashLevel4::
	setflashlevel 4
	return

DewfordTown_Gym_EventScript_SetFlashLevel5::
	setflashlevel 5
	return

DewfordTown_Gym_EventScript_SetFlashLevel6::
	setflashlevel 6
	return

@ Darkest
DewfordTown_Gym_EventScript_SetFlashLevel7::
	setflashlevel 7
	return

DewfordTown_Gym_EventScript_BrightenRoom::
	call DewfordTown_Gym_EventScript_CountTrainersDefeated
	nop1
	goto_if_eq VAR_0x8000, VAR_0x8001, DewfordTown_Gym_EventScript_NoLightChange
	copyvar VAR_0x8001, VAR_0x8000
	goto_if_eq VAR_0x8000, 1, DewfordTown_Gym_EventScript_AnimateFlash1Trainer
	goto_if_eq VAR_0x8000, 2, DewfordTown_Gym_EventScript_AnimateFlash2Trainers
	goto_if_eq VAR_0x8000, 3, DewfordTown_Gym_EventScript_AnimateFlash3Trainers
	goto_if_eq VAR_0x8000, 4, DewfordTown_Gym_EventScript_AnimateFlash4Trainers
	goto_if_eq VAR_0x8000, 5, DewfordTown_Gym_EventScript_AnimateFlash5Trainers
	goto_if_eq VAR_0x8000, 6, DewfordTown_Gym_EventScript_AnimateFlash6Trainers

DewfordTown_Gym_EventScript_NoLightChange::
	return

/* NOTE: A little confusingly, a larger animateflash param value is a smaller flash radius*/
DewfordTown_Gym_EventScript_AnimateFlash1Trainer::
	playse SE_SWITCH
	animateflash 6
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash2Trainers::
	playse SE_SWITCH
	animateflash 5
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash3Trainers::
	playse SE_SWITCH
	animateflash 4
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash4Trainers::
	playse SE_SWITCH
	animateflash 3
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash5Trainers::
	playse SE_SWITCH
	animateflash 2
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash6Trainers::
	playse SE_SWITCH
	animateflash 1
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlashFullBrightness::
	playse SE_SWITCH
	animateflash 0
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_CountTrainersDefeated::
	setvar VAR_0x8000, 0
	goto_if_not_defeated TRAINER_TAKAO, DewfordTown_Gym_EventScript_CheckJocelyn
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckJocelyn::
	goto_if_not_defeated TRAINER_JOCELYN, DewfordTown_Gym_EventScript_CheckLaura
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckLaura::
	goto_if_not_defeated TRAINER_LAURA, DewfordTown_Gym_EventScript_CheckBrenden
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckBrenden::
	goto_if_not_defeated TRAINER_BRENDEN, DewfordTown_Gym_EventScript_CheckCristian
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckCristian::
	goto_if_not_defeated TRAINER_CRISTIAN, DewfordTown_Gym_EventScript_CheckLilith
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckLilith::
	goto_if_not_defeated TRAINER_LILITH, DewfordTown_Gym_EventScript_StopCountingTrainers
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_StopCountingTrainers::
	return

DewfordTown_Gym_EventScript_Brawly::
	trainerbattle_single TRAINER_BRAWLY_1, DewfordTown_Gym_Text_BrawlyIntro, DewfordTown_Gym_Text_BrawlyDefeat, DewfordTown_Gym_EventScript_BrawlyDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, DewfordTown_Gym_EventScript_BrawlyRematch
	goto_if_unset FLAG_RECEIVED_TM_BULK_UP, DewfordTown_Gym_EventScript_GiveBulkUp2
	msgbox DewfordTown_Gym_Text_BrawlyPostBattle, MSGBOX_DEFAULT
	release
	end

DewfordTown_Gym_EventScript_BrawlyDefeated::
	call DewfordTown_Gym_EventScript_AnimateFlashFullBrightness
	message DewfordTown_Gym_Text_ReceivedKnuckleBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox DewfordTown_Gym_Text_KnuckleBadgeInfoTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_DEWFORD_GYM
	setflag FLAG_BADGE02_GET
	addvar VAR_PETALBURG_GYM_STATE, 1
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	setvar VAR_0x8008, 2
	call Common_EventScript_SetGymTrainers
	call DewfordTown_Gym_EventScript_GiveBulkUp
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox DewfordTown_Gym_Text_RegisteredBrawly, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_BRAWLY_MATCH_CALL
	setvar VAR_ROXANNE_CALL_STEP_COUNTER, 0
	setflag FLAG_ENABLE_ROXANNE_FIRST_CALL
	release
	end

DewfordTown_Gym_EventScript_GiveBulkUp::
	giveitem ITEM_TM_BULK_UP
	goto_if_eq VAR_RESULT, 0, Common_EventScript_BagIsFull
	msgbox DewfordTown_Gym_Text_ExplainBulkUp, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_BULK_UP
	return

DewfordTown_Gym_EventScript_GiveBulkUp2:
	giveitem ITEM_TM_BULK_UP
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	msgbox DewfordTown_Gym_Text_ExplainBulkUp, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_BULK_UP
	release
	end

DewfordTown_Gym_EventScript_BrawlyRematch::
	trainerbattle_rematch_double TRAINER_BRAWLY_1, DewfordTown_Gym_Text_BrawlyPreRematch, DewfordTown_Gym_Text_BrawlyRematchDefeat, DewfordTown_Gym_Text_BrawlyRematchNeedTwoMons
	msgbox DewfordTown_Gym_Text_BrawlyPostRematch, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_Takao::
	trainerbattle_single TRAINER_TAKAO, DewfordTown_Gym_Text_TakaoIntro, DewfordTown_Gym_Text_TakaoDefeat, DewfordTown_Gym_EventScript_TakaoBrightenRoom
	msgbox DewfordTown_Gym_Text_TakaoPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_TakaoBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Jocelyn::
	trainerbattle_single TRAINER_JOCELYN, DewfordTown_Gym_Text_JocelynIntro, DewfordTown_Gym_Text_JocelynDefeat, DewfordTown_Gym_EventScript_JocelynBrightenRoom
	msgbox DewfordTown_Gym_Text_JocelynPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_JocelynBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Laura::
	trainerbattle_single TRAINER_LAURA, DewfordTown_Gym_Text_LauraIntro, DewfordTown_Gym_Text_LauraDefeat, DewfordTown_Gym_EventScript_LauraBrightenRoom
	msgbox DewfordTown_Gym_Text_LauraPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_LauraBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Brenden::
	trainerbattle_single TRAINER_BRENDEN, DewfordTown_Gym_Text_BrendenIntro, DewfordTown_Gym_Text_BrendenDefeat, DewfordTown_Gym_EventScript_BrendenBrightenRoom
	msgbox DewfordTown_Gym_Text_BrendenPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_BrendenBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Cristian::
	trainerbattle_single TRAINER_CRISTIAN, DewfordTown_Gym_Text_CristianIntro, DewfordTown_Gym_Text_CristianDefeat, DewfordTown_Gym_EventScript_CristianBrightenRoom
	msgbox DewfordTown_Gym_Text_CristianPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_CristianBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Lilith::
	trainerbattle_single TRAINER_LILITH, DewfordTown_Gym_Text_LilithIntro, DewfordTown_Gym_Text_LilithDefeat, DewfordTown_Gym_EventScript_LilithBrightenRoom
	msgbox DewfordTown_Gym_Text_LilithPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_LilithBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_DEWFORD_GYM, DewfordTown_Gym_EventScript_GymGuidePostVictory
	msgbox DewfordTown_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

DewfordTown_Gym_EventScript_GymGuidePostVictory::
	msgbox DewfordTown_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

DewfordTown_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE02_GET, DewfordTown_Gym_EventScript_GymStatueCertified
	goto DewfordTown_Gym_EventScript_GymStatue
	end

DewfordTown_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE02_GET, DewfordTown_Gym_EventScript_GymStatueCertified
	goto DewfordTown_Gym_EventScript_GymStatue
	end

DewfordTown_Gym_EventScript_GymStatueCertified::
	msgbox DewfordTown_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Gym_EventScript_GymStatue::
	msgbox DewfordTown_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Gym_Text_GymGuideAdvice:
	.string "{CHN}嘿，你怎么样啊，朝着\n"
	.string "冠军前进的{PLAYER}？\p"
	.string "武斗镇的道馆馆主藤树使用的是\n"
	.string "格斗属性的宝可梦。\p"
	.string "用一般属性的\n"
	.string "宝可梦去对战他会自讨苦吃。\p"
	.string "格斗宝可梦会对一般宝可梦\n"
	.string "造成严重打击，\l"
	.string "所以要小心！\p"
	.string "更糟糕的是，道馆里黑得\n"
	.string "像海底一样。\p"
	.string "但是打败挡路的\n"
	.string "训练家后就会变亮。\p"
	.string "嘿，好了，去吧！$"

DewfordTown_Gym_Text_GymGuidePostVictory:
	.string "{CHN}哇！这里变得太亮了！\p"
	.string "你的未来也是光明的！$"

DewfordTown_Gym_Text_TakaoIntro:
	.string "{CHN}力量即正义！\n"
	.string "来吧！$"

DewfordTown_Gym_Text_TakaoDefeat:
	.string "{CHN}力量不够……$"

DewfordTown_Gym_Text_TakaoPostBattle:
	.string "{CHN}你的技术战胜了我的力量！\n"
	.string "你的技巧值得称赞！$"

DewfordTown_Gym_Text_JocelynIntro:
	.string "{CHN}不需要藤树\n"
	.string "出面！\p"
	.string "我会粉碎你！$"

DewfordTown_Gym_Text_JocelynDefeat:
	.string "{CHN}但是……怎么会？\n"
	.string "我怎么这么容易就输了？$"

DewfordTown_Gym_Text_JocelynPostBattle:
	.string "{CHN}我不会浪费这次失败。\n"
	.string "我会用它来激励我训练！\p"
	.string "总有一天我会成为道馆馆主……\p"
	.string "不，我会成为宝可梦联盟\n"
	.string "冠军！$"

DewfordTown_Gym_Text_LauraIntro:
	.string "{CHN}你敢敷衍我！\n"
	.string "你哭起来可别怪我！$"

DewfordTown_Gym_Text_LauraDefeat:
	.string "{CHN}哇啊啊啊啊！\n"
	.string "我输了！$"

DewfordTown_Gym_Text_LauraPostBattle:
	.string "I battle in the dark to make my heart\n"
	.string "stronger.\p"
	.string "But because it's so dark, I can never\n"
	.string "see BRAWLY's face…$"

DewfordTown_Gym_Text_LilithIntro:
	.string "{CHN}呵呵呵……\n"
	.string "你在黑暗中跌跌撞撞吗？$"

DewfordTown_Gym_Text_LilithDefeat:
	.string "{CHN}哦，你……\n"
	.string "我不想认识你！$"

DewfordTown_Gym_Text_LilithPostBattle:
	.string "{CHN}你活该迷路，\n"
	.string "最后又回到入口！$"

DewfordTown_Gym_Text_BrendenIntro:
	.string "{CHN}我会让你见识一下\n"
	.string "水手的气魄！$"

DewfordTown_Gym_Text_BrendenDefeat:
	.string "{CHN}怎么会这样？\n"
	.string "我不像会这样输的人！$"

DewfordTown_Gym_Text_BrendenPostBattle:
	.string "{CHN}哦，是啊！你有资格见\n"
	.string "我们的道馆馆主了。$"

DewfordTown_Gym_Text_CristianIntro:
	.string "{CHN}如果你想通过，就必须\n"
	.string "先过我这一关！$"

DewfordTown_Gym_Text_CristianDefeat:
	.string "{CHN}呃啊啊啊！\n"
	.string "完全被压制了！$"

DewfordTown_Gym_Text_CristianPostBattle:
	.string "{CHN}你赢了！\n"
	.string "去争取那个徽章吧！$"

DewfordTown_Gym_Text_BrawlyIntro:
	.string "{CHN}我是藤树！\n"
	.string "武斗镇的道馆馆主！\p"
	.string "我在这一带汹涌的浪潮中\n"
	.string "经受锤炼，在漆黑的洞窟中\l"
	.string "变得坚强！\p"
	.string "所以你想挑战我？\n"
	.string "让我看看你的实力！$"

DewfordTown_Gym_Text_BrawlyDefeat:
	.string "{CHN}哇，哇哦！你激起的浪花\n"
	.string "比我想象的还要大！\p"
	.string "你把我淹没了！\p"
	.string "好吧，你赢了。\n"
	.string "拿着这个道馆徽章！$"

DewfordTown_Gym_Text_ReceivedKnuckleBadge:
	.string "{CHN}{PLAYER}从藤树\n"
	.string "那里得到了拳击徽章。$"

DewfordTown_Gym_Text_KnuckleBadgeInfoTakeThis:
	.string "{CHN}拳击徽章能让所有\n"
	.string "30级以下的宝可梦，即使是通过交换得到的，\l"
	.string "都无条件服从你。\p"
	.string "而且，你可以在战斗外使用\n"
	.string "秘传学习器招式闪光了。\p"
	.string "如果你愿意的话，也可以使用这个\n"
	.string "招式学习器。$"

DewfordTown_Gym_Text_ExplainBulkUp:
	.string "{CHN}那个招式学习器08含有健美。\p"
	.string "它是一个能同时提升攻击\n"
	.string "和防御的招式。\p"
	.string "…… …… …… …… …… ……"

DewfordTown_Gym_Text_RegisteredBrawly:
	.string "{CHN}已将道馆馆主藤树\n"
	.string "登录到宝可梦领航员中。$"

DewfordTown_Gym_Text_BrawlyPostBattle:
	.string "{CHN}我能看到你的才华有朝一日\n"
	.string "会成为掀起惊叹风暴的\l"
	.string "巨浪，让训练家们为之震惊！$"

DewfordTown_Gym_Text_GymStatue:
	.string "{CHN}武斗镇 宝可梦道馆$"

DewfordTown_Gym_Text_GymStatueCertified:
	.string "{CHN}武斗镇 宝可梦道馆\p"
	.string "藤树认证的训练家：\n"
	.string "{PLAYER}$"

DewfordTown_Gym_Text_BrawlyPreRematch:
	.string "{CHN}藤树：海浪或许会退去，但它\n"
	.string "总会回到岸边。\p"
	.string "像你这样才华横溢的巨浪……\n"
	.string "我就知道你会回来！\p"
	.string "让我看看你\n"
	.string "提升了多少！$"

DewfordTown_Gym_Text_BrawlyRematchDefeat:
	.string "{CHN}哇！\n"
	.string "又被淹没了！$"

DewfordTown_Gym_Text_BrawlyPostRematch:
	.string "{CHN}藤树：对战是广阔而深邃的。\n"
	.string "你看不到底。\l"
	.string "就像丰缘的大海一样！$"

DewfordTown_Gym_Text_BrawlyRematchNeedTwoMons:
	.string "{CHN}藤树：海浪或许会退去，但它\n"
	.string "总会回到岸边。\p"
	.string "像你这样才华横溢的巨浪……\n"
	.string "我就知道你会回来！\p"
	.string "哦？你只有一只\n"
	.string "能战斗的宝可梦。\p"
	.string "很抱歉，但我希望你带着\n"
	.string "至少两只宝可梦再来。$"
