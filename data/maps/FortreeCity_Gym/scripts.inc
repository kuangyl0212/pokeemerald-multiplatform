FortreeCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_Gym_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, FortreeCity_Gym_OnWarp
	.byte 0

FortreeCity_Gym_OnTransition:
	special RotatingGate_InitPuzzle
	end

FortreeCity_Gym_OnWarp:
	map_script_2 VAR_TEMP_0, VAR_TEMP_0, FortreeCity_Gym_EventScript_InitRotatingGates
	.short 0

@ NOTE: This rotating gate puzzle makes use of VAR_TEMP_0 - VAR_TEMP_3
FortreeCity_Gym_EventScript_InitRotatingGates::
	special RotatingGate_InitPuzzleAndGraphics
	end

FortreeCity_Gym_EventScript_Winona::
	trainerbattle_single TRAINER_WINONA_1, FortreeCity_Gym_Text_WinonaIntro, FortreeCity_Gym_Text_WinonaDefeat, FortreeCity_Gym_EventScript_WinonaDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_Gym_EventScript_WinonaRematch
	goto_if_unset FLAG_RECEIVED_TM_AERIAL_ACE, FortreeCity_Gym_EventScript_GiveAerialAce2
	msgbox FortreeCity_Gym_Text_WinonaPostBattle, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_WinonaDefeated::
	message FortreeCity_Gym_Text_ReceivedFeatherBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox FortreeCity_Gym_Text_ExplainFeatherBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_FORTREE_GYM
	setflag FLAG_BADGE06_GET
	setvar VAR_0x8008, 6
	call Common_EventScript_SetGymTrainers
	call FortreeCity_Gym_EventScript_GiveAerialAce
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox FortreeCity_Gym_Text_RegisteredWinona, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WINONA_MATCH_CALL
	setvar VAR_SCOTT_FORTREE_CALL_STEP_COUNTER, 0
	setflag FLAG_SCOTT_CALL_FORTREE_GYM
	release
	end

FortreeCity_Gym_EventScript_GiveAerialAce2::
	giveitem ITEM_TM_AERIAL_ACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox FortreeCity_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_AERIAL_ACE
	release
	end

FortreeCity_Gym_EventScript_GiveAerialAce::
	giveitem ITEM_TM_AERIAL_ACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox FortreeCity_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_AERIAL_ACE
	return

FortreeCity_Gym_EventScript_WinonaRematch::
	trainerbattle_rematch_double TRAINER_WINONA_1, FortreeCity_Gym_Text_WinonaPreRematch, FortreeCity_Gym_Text_WinonaRematchDefeat, FortreeCity_Gym_Text_WinonaRematchNeedTwoMons
	msgbox FortreeCity_Gym_Text_WinonaPostRematch, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Jared::
	trainerbattle_single TRAINER_JARED, FortreeCity_Gym_Text_JaredIntro, FortreeCity_Gym_Text_JaredDefeat
	msgbox FortreeCity_Gym_Text_JaredPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Edwardo::
	trainerbattle_single TRAINER_EDWARDO, FortreeCity_Gym_Text_EdwardoIntro, FortreeCity_Gym_Text_EdwardoDefeat
	msgbox FortreeCity_Gym_Text_EdwardoPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Flint::
	trainerbattle_single TRAINER_FLINT, FortreeCity_Gym_Text_FlintIntro, FortreeCity_Gym_Text_FlintDefeat
	msgbox FortreeCity_Gym_Text_FlintPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Ashley::
	trainerbattle_single TRAINER_ASHLEY, FortreeCity_Gym_Text_AshleyIntro, FortreeCity_Gym_Text_AshleyDefeat
	msgbox FortreeCity_Gym_Text_AshleyPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Humberto::
	trainerbattle_single TRAINER_HUMBERTO, FortreeCity_Gym_Text_HumbertoIntro, FortreeCity_Gym_Text_HumbertoDefeat
	msgbox FortreeCity_Gym_Text_HumbertoPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Darius::
	trainerbattle_single TRAINER_DARIUS, FortreeCity_Gym_Text_DariusIntro, FortreeCity_Gym_Text_DariusDefeat
	msgbox FortreeCity_Gym_Text_DariusPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_FORTREE_GYM, FortreeCity_Gym_EventScript_GymGuidePostVictory
	msgbox FortreeCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_GymGuidePostVictory::
	msgbox FortreeCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE06_GET, FortreeCity_Gym_EventScript_GymStatueCertified
	goto FortreeCity_Gym_EventScript_GymStatue
	end

FortreeCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE06_GET, FortreeCity_Gym_EventScript_GymStatueCertified
	goto FortreeCity_Gym_EventScript_GymStatue
	end

FortreeCity_Gym_EventScript_GymStatueCertified::
	msgbox FortreeCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_Gym_EventScript_GymStatue::
	msgbox FortreeCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_Gym_Text_GymGuideAdvice:
	.string "{CHN}哟，最近怎么样，朝冠军\n"
	.string "迈进的{PLAYER}？\p"
	.string "茵郁道馆馆主娜琪\n"
	.string "是飞行属性宝可梦的大师。\p"
	.string "她就在这道馆的深处，\n"
	.string "旋转门的后面等着你。\p"
	.string "她正在等待着\n"
	.string "试图展翅高飞的新挑战者！\p"
	.string "好了，去吧！$"

FortreeCity_Gym_Text_GymGuidePostVictory:
	.string "{CHN}你做到了！\n"
	.string "你成功起飞了！$"

FortreeCity_Gym_Text_JaredIntro:
	.string "{CHN}见识一下\n"
	.string "鸟宝可梦优雅的战斗风格吧！$"

FortreeCity_Gym_Text_JaredDefeat:
	.string "{CHN}你……\n"
	.string "你很强……$"

FortreeCity_Gym_Text_JaredPostBattle:
	.string "{CHN}训练家必须机智才能\n"
	.string "应对突发状况。\p"
	.string "你有足够的智慧去见\n"
	.string "我们的馆主吗？$"

FortreeCity_Gym_Text_EdwardoIntro:
	.string "{CHN}喜爱鸟宝可梦的人\n"
	.string "都渴望加入这道馆。\p"
	.string "作为茵郁道馆的一员，\n"
	.string "我绝不能输！$"

FortreeCity_Gym_Text_EdwardoDefeat:
	.string "{CHN}这对我来说\n"
	.string "负担太重了……$"

FortreeCity_Gym_Text_EdwardoPostBattle:
	.string "{CHN}世界很大，\n"
	.string "有无数强大的训练家。\p"
	.string "我要继续特训，\n"
	.string "让自己变得更强。$"

FortreeCity_Gym_Text_FlintIntro:
	.string "{CHN}用不着我们的道馆\n"
	.string "馆主娜琪亲自出手！\p"
	.string "我就足够对付你了！$"

FortreeCity_Gym_Text_FlintDefeat:
	.string "{CHN}娜琪，我……\n"
	.string "我输了！$"

FortreeCity_Gym_Text_FlintPostBattle:
	.string "{CHN}娜琪又可爱又强大。\n"
	.string "她是终极的馆主！\p"
	.string "脸红……$"

FortreeCity_Gym_Text_AshleyIntro:
	.string "{CHN}娜琪亲自指导过我！\n"
	.string "你别想轻易打败我！$"

FortreeCity_Gym_Text_AshleyDefeat:
	.string "{CHN}我输了……$"

FortreeCity_Gym_Text_AshleyPostBattle:
	.string "{CHN}多亏了娜琪，\n"
	.string "茵郁市的居民才能安居无忧。$"

FortreeCity_Gym_Text_HumbertoIntro:
	.string "{CHN}娜琪战斗时，\n"
	.string "她的脸上闪耀着美丽的决心……\p"
	.string "我绝不会让你\n"
	.string "看到那美丽的景象！$"

FortreeCity_Gym_Text_HumbertoDefeat:
	.string "{CHN}呃！\n"
	.string "我没能阻止你。$"

FortreeCity_Gym_Text_HumbertoPostBattle:
	.string "{CHN}你最好小心点！\n"
	.string "别盯着娜琪看得出神，\l"
	.string "否则你会摔个四脚朝天！$"

FortreeCity_Gym_Text_DariusIntro:
	.string "{CHN}你最好知道飞行属性的\n"
	.string "宝可梦有各种各样。\p"
	.string "你应该知道吧？$"

FortreeCity_Gym_Text_DariusDefeat:
	.string "{CHN}看来你挺懂的！$"

FortreeCity_Gym_Text_DariusPostBattle:
	.string "{CHN}是，你确实打败了我。\n"
	.string "但你最好小心点！我们的馆主\l"
	.string "娜琪的宝可梦可不是闹着玩的。$"

FortreeCity_Gym_Text_WinonaIntro:
	.string "{CHN}我是娜琪。我是\n"
	.string "茵郁宝可梦道馆的馆主。\p"
	.string "我与鸟宝可梦合而为一，\n"
	.string "翱翔于天空……\p"
	.string "无论战斗多么艰苦，\n"
	.string "我们都优雅地取得了胜利……\p"
	.string "见识一下\n"
	.string "鸟宝可梦与我优雅的舞姿吧！$"

FortreeCity_Gym_Text_WinonaDefeat:
	.string "{CHN}我从未见过哪位训练家\n"
	.string "能以比我更优雅的姿态\l"
	.string "指挥宝可梦……\p"
	.string "为表彰你的实力，\n"
	.string "我将这枚道馆徽章授予你。$"

FortreeCity_Gym_Text_ReceivedFeatherBadge:
	.string "{CHN}{PLAYER}从娜琪那里\n"
	.string "获得了羽毛徽章。$"

FortreeCity_Gym_Text_ExplainFeatherBadgeTakeThis:
	.string "{CHN}有了羽毛徽章，等级在70以下的\n"
	.string "所有宝可梦，即使是\l"
	.string "通过交换得到的，也会完全听从你的命令。\p"
	.string "你还可以在战斗之外\n"
	.string "使用秘传学习器飞翔。\p"
	.string "还有这个……\n"
	.string "这是我送你的礼物。$"

FortreeCity_Gym_Text_ExplainAerialAce:
	.string "{CHN}招式学习器40装有燕返。\p"
	.string "它的速度……\n"
	.string "没有任何宝可梦能够避开。\p"
	.string "…… …… …… …… …… ……$"

FortreeCity_Gym_Text_RegisteredWinona:
	.string "{CHN}已在宝可梦导航器中\n"
	.string "登记道馆馆主娜琪。$"

FortreeCity_Gym_Text_WinonaPostBattle:
	.string "{CHN}虽然我输给了你，\n"
	.string "但我仍会致力于鸟宝可梦。$"

FortreeCity_Gym_Text_GymStatue:
	.string "{CHN}茵郁市宝可梦道馆$"

FortreeCity_Gym_Text_GymStatueCertified:
	.string "{CHN}茵郁市宝可梦道馆\p"
	.string "娜琪认证的训练家：\n"
	.string "{PLAYER}$"

FortreeCity_Gym_Text_WinonaPreRematch:
	.string "{CHN}娜琪：我们人类永远无法\n"
	.string "摆脱大地的引力。\p"
	.string "但通过追求卓越，\n"
	.string "我们拥有了翱翔的力量！\p"
	.string "你已经作为现任冠军\n"
	.string "登上了巅峰。\p"
	.string "请让我见识一下\n"
	.string "你全力展翅飞翔的力量！$"

FortreeCity_Gym_Text_WinonaRematchDefeat:
	.string "{CHN}我又一次未能达到你的高度……$"

FortreeCity_Gym_Text_WinonaPostRematch:
	.string "{CHN}娜琪：虽然我输了，\n"
	.string "但我心中的翅膀依然完好。\p"
	.string "我可以再次起飞，\n"
	.string "一次又一次地翱翔。\p"
	.string "我深信不疑！$"

FortreeCity_Gym_Text_WinonaRematchNeedTwoMons:
	.string "{CHN}娜琪：我们人类永远无法\n"
	.string "摆脱大地的引力。\p"
	.string "但通过追求卓越，\n"
	.string "我们拥有了翱翔的力量！\p"
	.string "你已经作为现任冠军\n"
	.string "登上了巅峰。\p"
	.string "请让我见识一下\n"
	.string "你全力展翅飞翔的力量！\p"
	.string "哎呀，糟糕……你\n"
	.string "只带了一只宝可梦吗？\p"
	.string "请至少带两只宝可梦\n"
	.string "再来吧。$"
