MtChimney_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, MtChimney_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, MtChimney_OnTransition
	.byte 0

MtChimney_OnTransition:
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 1
	end

MtChimney_OnResume:
	setstepcallback STEP_CB_ASH
	end

MtChimney_EventScript_Archie::
	lock
	faceplayer
	call_if_unset FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieGoStopTeamMagma
	call_if_set FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieBusyFighting
	closemessage
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_EVIL_LEADER_PLEASE_STOP
	release
	end

MtChimney_EventScript_ArchieGoStopTeamMagma::
	msgbox MtChimney_Text_ArchieGoStopTeamMagma, MSGBOX_DEFAULT
	return

MtChimney_EventScript_ArchieBusyFighting::
	msgbox MtChimney_Text_ArchieIHaveMyHandsFull, MSGBOX_DEFAULT
	return

MtChimney_EventScript_Maxie::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	msgbox MtChimney_Text_MeteoriteWillActivateVolcano, MSGBOX_DEFAULT
	applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_Delay48
	waitmovement 0
	msgbox MtChimney_Text_MaxieIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MAXIE_MT_CHIMNEY, MtChimney_Text_MaxieDefeat
	msgbox MtChimney_Text_MaxieYouHaventSeenLastOfMagma, MSGBOX_DEFAULT
	closemessage
	delay 30
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_MT_CHIMNEY_MAXIE
	removeobject LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1
	removeobject LOCALID_MT_CHIMNEY_TABITHA
	removeobject LOCALID_MT_CHIMNEY_MAGMA_GRUNT_2
	setflag FLAG_HIDE_MT_CHIMNEY_TEAM_MAGMA
	fadescreen FADE_FROM_BLACK
	setobjectxyperm LOCALID_MT_CHIMNEY_ARCHIE, 10, 12
	addobject LOCALID_MT_CHIMNEY_ARCHIE
	call_if_eq VAR_FACING, DIR_EAST, MtChimney_EventScript_ArchieApproachPlayerEast
	call_if_eq VAR_FACING, DIR_NORTH, MtChimney_EventScript_ArchieApproachPlayerNorth
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox MtChimney_Text_ArchieThankYou, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_EAST, MtChimney_EventScript_ArchieExitEast
	call_if_eq VAR_FACING, DIR_NORTH, MtChimney_EventScript_ArchieExitNorth
	removeobject LOCALID_MT_CHIMNEY_ARCHIE
	setflag FLAG_HIDE_MT_CHIMNEY_TEAM_AQUA
	setflag FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY
	clearflag FLAG_HIDE_FALLARBOR_HOUSE_PROF_COZMO
	setflag FLAG_HIDE_METEOR_FALLS_1F_1R_COZMO
	clearflag FLAG_HIDE_MT_CHIMNEY_LAVA_COOKIE_LADY
	releaseall
	end

MtChimney_EventScript_ArchieApproachPlayerEast::
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieApproachPlayerEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieApproachPlayerNorth::
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieApproachPlayerNorth
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitEast::
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieExitEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitNorth::
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieExitNorth
	waitmovement 0
	return

MtChimney_EventScript_LavaCookieLady::
	lock
	faceplayer
	showmoneybox 0, 0
	msgbox MtChimney_Text_LavaCookiesJust200, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtChimney_EventScript_DeclineLavaCookie
	checkmoney 200
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_NotEnoughMoney
	msgbox MtChimney_Text_ThankYouDear, MSGBOX_DEFAULT
	checkitemspace ITEM_LAVA_COOKIE
	call_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_RemoveMoney
	giveitem ITEM_LAVA_COOKIE
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_BagIsFull
	hidemoneybox
	release
	end

MtChimney_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_EventScript_RemoveMoney::
	removemoney 200
	updatemoneybox
	return

MtChimney_EventScript_DeclineLavaCookie::
	msgbox MtChimney_Text_OhFineThen, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_EventScript_NotEnoughMoney::
	msgbox MtChimney_Text_YouveNotGotTheMoney, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_Movement_ArchieApproachPlayerEast:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	step_end

MtChimney_Movement_ArchieExitEast:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_ArchieApproachPlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

MtChimney_Movement_ArchieExitNorth:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused1:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused2:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused3:
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused4:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused5:
	delay_16
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused6:
	delay_16
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused7:
	delay_16
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused8:
	delay_16
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

MtChimney_Movement_Unused9:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused10:
	walk_down
	step_end

MtChimney_Movement_Unused11:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused12:
	delay_16
	delay_16
	walk_in_place_faster_left
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused13:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	delay_16
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused14:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	face_right
	step_end

MtChimney_Movement_Unused15:
	walk_left
	walk_in_place_faster_right
	delay_16
	step_end

MtChimney_EventScript_BusyAquaGrunt1::
	msgbox MtChimney_Text_MagmaOutnumbersUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt2::
	msgbox MtChimney_Text_LessHabitatForWaterPokemon, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt3::
	msgbox MtChimney_Text_MagmasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_Tabitha::
	trainerbattle_single TRAINER_TABITHA_MT_CHIMNEY, MtChimney_Text_TabithaIntro, MtChimney_Text_TabithaDefeat
	msgbox MtChimney_Text_TabithaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_MT_CHIMNEY_2, MtChimney_Text_Grunt2Intro, MtChimney_Text_Grunt2Defeat
	msgbox MtChimney_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_BusyMagmaGrunt1::
	msgbox MtChimney_Text_TeamAquaAlwaysMessingWithPlans, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt2::
	msgbox MtChimney_Text_MeteoritesPackAmazingPower, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt3::
	msgbox MtChimney_Text_YouBetterNotMessWithUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt4::
	msgbox MtChimney_Text_AquasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt5::
	msgbox MtChimney_Text_DouseThemInFire, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt6::
	msgbox MtChimney_Text_KeepMakingMoreLand, MSGBOX_SIGN
	end

MtChimney_EventScript_MagmaPoochyena::
	msgbox MtChimney_Text_Bufoh, MSGBOX_SIGN
	end

MtChimney_EventScript_AquaPoochyena::
	msgbox MtChimney_Text_Bushaa, MSGBOX_SIGN
	end

MtChimney_EventScript_MeteoriteMachine::
	lockall
	goto_if_unset FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, MtChimney_EventScript_MachineOn
	goto_if_set FLAG_RECEIVED_METEORITE, MtChimney_EventScript_MachineOff
	msgbox MtChimney_Text_RemoveTheMeteorite, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtChimney_EventScript_LeaveMeteoriteAlone
	msgbox MtChimney_Text_PlayerRemovedMeteorite, MSGBOX_DEFAULT
	giveitem ITEM_METEORITE
	setflag FLAG_RECEIVED_METEORITE
	releaseall
	end

MtChimney_EventScript_LeaveMeteoriteAlone::
	msgbox MtChimney_Text_PlayerLeftMeteorite, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOff::
	msgbox MtChimney_Text_MachineMakesNoResponse, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOn::
	msgbox MtChimney_Text_MetoriteFittedOnMachine, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_RouteSign::
	msgbox MtChimney_Text_RouteSign, MSGBOX_SIGN
	end

MtChimney_EventScript_Shelby::
	trainerbattle_single TRAINER_SHELBY_1, MtChimney_Text_ShelbyIntro, MtChimney_Text_ShelbyDefeat, MtChimney_EventScript_DefeatedShelby
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_RematchShelby
	msgbox MtChimney_Text_ShelbyPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_DefeatedShelby::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_ShelbyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SHELBY_1
	release
	end

MtChimney_EventScript_RematchShelby::
	trainerbattle_rematch TRAINER_SHELBY_1, MtChimney_Text_ShelbyRematchIntro, MtChimney_Text_ShelbyRematchDefeat
	msgbox MtChimney_Text_ShelbyPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Melissa::
	trainerbattle_single TRAINER_MELISSA, MtChimney_Text_MelissaIntro, MtChimney_Text_MelissaDefeat
	msgbox MtChimney_Text_MelissaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sheila::
	trainerbattle_single TRAINER_SHEILA, MtChimney_Text_SheilaIntro, MtChimney_Text_SheilaDefeat
	msgbox MtChimney_Text_SheilaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Shirley::
	trainerbattle_single TRAINER_SHIRLEY, MtChimney_Text_ShirleyIntro, MtChimney_Text_ShirleyDefeat
	msgbox MtChimney_Text_ShirleyPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MT_CHIMNEY_1, MtChimney_Text_Grunt1Intro, MtChimney_Text_Grunt1Defeat
	msgbox MtChimney_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sawyer::
	trainerbattle_single TRAINER_SAWYER_1, MtChimney_Text_SawyerIntro, MtChimney_Text_SawyerDefeat, MtChimney_EventScript_SawyerDefeated
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_SawyerRematch
	msgbox MtChimney_Text_SawyerPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_SawyerDefeated::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_SawyerRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SAWYER_1
	release
	end

MtChimney_EventScript_SawyerRematch::
	trainerbattle_rematch TRAINER_SAWYER_1, MtChimney_Text_SawyerRematchIntro, MtChimney_Text_SawyerRematchDefeat
	msgbox MtChimney_Text_SawyerPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_Text_MeteoriteWillActivateVolcano:
	.string "{CHN}这颗陨石中蕴含的力量…\p"
	.string "用这台机器放大它的力量，\n"
	.string "烟突山的火山\l"
	.string "活动就会瞬间加剧…\p"
	.string "它的能量会在火山口深处\n"
	.string "不断增长，然后…\l"
	.string "呼呼呼…$"

MtChimney_Text_MaxieIntro:
	.string "{CHN}赤焰：嗯？\n"
	.string "你是谁？\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "我听水梧桐抱怨过一个\n"
	.string "一直在干涉水舰队\l"
	.string "事务的小孩。\p"
	.string "他说的就是你吧。\p"
	.string "哼！所以你也想\n"
	.string "干涉我们熔岩队吗？\p"
	.string "你听好了。\n"
	.string "很久以前，生物利用\l"
	.string "土地来生存和成长。\p"
	.string "这就是为什么土地至关重要！\n"
	.string "它是一切的摇篮！\p"
	.string "这就是为什么熔岩队致力于\n"
	.string "扩张陆地的面积。\p"
	.string "这是为了人类和宝可梦\n"
	.string "的进一步发展！\p"
	.string "为此，我们需要\n"
	.string "沉睡在这座山中的力量…\p"
	.string "哦！你没必要\n"
	.string "知道这么多。\p"
	.string "不过，没关系！\n"
	.string "我会让你见识一下干涉\l"
	.string "我们伟大计划的后果！$"

MtChimney_Text_MaxieDefeat:
	.string "{CHN}什么？！\p"
	.string "我，赤焰，竟然大意了？！$"

MtChimney_Text_MaxieYouHaventSeenLastOfMagma:
	.string "{CHN}赤焰：不过，够了。\n"
	.string "这次我就先退下。\p"
	.string "但别以为这就是你\n"
	.string "最后一次见到熔岩队了。\p"
	.string "呼呼呼…\p"
	.string "即使没有陨石，如果我们\n"
	.string "能得到那颗宝珠… 呼呼呼…$"

MtChimney_Text_TabithaIntro:
	.string "{CHN}嘿嘿嘿！\p"
	.string "你竟然追到这儿来了！\p"
	.string "但是太迟了！\n"
	.string "我已经把从流星瀑布\l"
	.string "得到的陨石交给老大 了！$"

MtChimney_Text_TabithaDefeat:
	.string "{CHN}嘿嘿嘿…\p"
	.string "虽然我输了，但如果我们的首领\n"
	.string "唤醒了那个东西…$"

MtChimney_Text_TabithaPostBattle:
	.string "{CHN}老大，快点！\n"
	.string "把陨石的能量给它！\p"
	.string "嘿嘿嘿…$"

MtChimney_Text_Grunt2Intro:
	.string "{CHN}我们熔岩队是为了大家\n"
	.string "在努力工作。\p"
	.string "比如，如果那个东西的力量能造出\n"
	.string "更多的陆地，就会有更多的地方住人。\p"
	.string "大家都会幸福的！$"

MtChimney_Text_Grunt2Defeat:
	.string "{CHN}嗯？\n"
	.string "你说我输了是什么意思？$"

MtChimney_Text_Grunt2PostBattle:
	.string "{CHN}我们老大说：“这会让大家\n"
	.string "都幸福。”\p"
	.string "但为什么大家总是\n"
	.string "阻碍我们呢？$"

MtChimney_Text_Grunt1Intro:
	.string "{CHN}如果有更多的陆地，我就能\n"
	.string "有一栋自己的大房子了！\p"
	.string "我要把它建在凝固的熔岩上！$"

MtChimney_Text_Grunt1Defeat:
	.string "{CHN}我大房子的梦想…$"

MtChimney_Text_Grunt1PostBattle:
	.string "{CHN}像你这样的小孩子，\n"
	.string "应该去海浪里玩水才对！$"

MtChimney_Text_TeamAquaAlwaysMessingWithPlans:
	.string "{CHN}那个讨厌的水舰队…\n"
	.string "他们总是妨碍我们的计划！$"

MtChimney_Text_MeteoritesPackAmazingPower:
	.string "{CHN}陨石蕴含着惊人的力量！$"

MtChimney_Text_YouBetterNotMessWithUs:
	.string "{CHN}你最好别妨碍我们！\p"
	.string "我们正在试图唤醒那个东西\n"
	.string "为了大家的利益！$"

MtChimney_Text_AquasNameSimilar:
	.string "{CHN}我们是熔岩队！\p"
	.string "他们是水舰队！\p"
	.string "真让我恼火，他们居然\n"
	.string "用跟我们类似的名字！$"

MtChimney_Text_DouseThemInFire:
	.string "{CHN}好！\n"
	.string "用火烧他们！$"

MtChimney_Text_KeepMakingMoreLand:
	.string "{CHN}我们要继续制造更多的陆地！$"

MtChimney_Text_Bufoh:
	.string "{CHN}呜哦！$"

MtChimney_Text_ArchieGoStopTeamMagma:
	.string "{CHN}水梧桐：呃，{PLAYER}！\n"
	.string "我就知道你会出现！\p"
	.string "你自己看看熔岩队的\n"
	.string "狂热分子在搞什么鬼！\p"
	.string "他们正试图把偷来的\n"
	.string "陨石的力量注入火山！\p"
	.string "这样做会引发\n"
	.string "火山喷发！$"

MtChimney_Text_ArchieIHaveMyHandsFull:
	.string "{CHN}水梧桐：呃呃…\p"
	.string "我想阻止那个赤焰，\n"
	.string "但我做不到！\p"
	.string "在我同时应付三个对手的时候\n"
	.string "根本分身乏术！$"

MtChimney_Text_ArchieThankYou:
	.string "{CHN}水梧桐：{PLAYER}！\n"
	.string "谢谢你！\p"
	.string "多亏了你的帮助，我们挫败了熔岩队\n"
	.string "的破坏计划！\p"
	.string "但是…你…\n"
	.string "到底是哪一边的？\p"
	.string "啊，那不重要了。\p"
	.string "我们会继续保持警惕，\n"
	.string "追击熔岩队。\p"
	.string "{PLAYER}，我们后会有期！$"

MtChimney_Text_MagmaOutnumbersUs:
	.string "{CHN}可恶…熔岩队的人数比我们多！\n"
	.string "我们应付不过来！$"

MtChimney_Text_LessHabitatForWaterPokemon:
	.string "{CHN}如果他们扩张陆地，水属性宝可梦\n"
	.string "的栖息地就会减少！$"

MtChimney_Text_MagmasNameSimilar:
	.string "{CHN}我们是水舰队！\p"
	.string "他们是熔岩队！\p"
	.string "真让我火大，他们居然\n"
	.string "用这么容易混淆的名字！$"

MtChimney_Text_Bushaa:
	.string "{CHN}呜沙！$"

MtChimney_Text_LavaCookiesJust200:
	.string "{CHN}熔岩饼干是烟突山的\n"
	.string "特产。\p"
	.string "尝一个吧。只要¥200。$"

MtChimney_Text_ThankYouDear:
	.string "{CHN}谢谢你，亲爱的！$"

MtChimney_Text_YouveNotGotTheMoney:
	.string "{CHN}哦，亲爱的。如果你\n"
	.string "没有钱的话，什么也买不了。$"

MtChimney_Text_OhFineThen:
	.string "{CHN}哦，那好吧。$"

MtChimney_Text_MetoriteFittedOnMachine:
	.string "{CHN}一颗陨石被装在一台神秘的\n"
	.string "机器上…\p"
	.string "这台机器似乎正在将\n"
	.string "能量储存到陨石中。$"

MtChimney_Text_RemoveTheMeteorite:
	.string "{CHN}一颗陨石被装在一台神秘的\n"
	.string "机器上…\p"
	.string "你想拿走这颗陨石吗？$"

MtChimney_Text_PlayerRemovedMeteorite:
	.string "{CHN}{PLAYER}从神秘的机器上\n"
	.string "取下了陨石。$"

MtChimney_Text_PlayerLeftMeteorite:
	.string "{CHN}{PLAYER}把陨石留在了\n"
	.string "原来的位置。$"

MtChimney_Text_MachineMakesNoResponse:
	.string "{CHN}这台神秘的机器…\n"
	.string "一点反应也没有。$"

MtChimney_Text_RouteSign:
	.string "{CHN}{DOWN_ARROW} 凹凸山道\n"
	.string "前方是烟突市$"

MtChimney_Text_ShelbyIntro:
	.string "{CHN}我去泡了温泉，\n"
	.string "舒缓了疲惫的骨头。\l"
	.string "现在我觉得自己浑身是劲！$"

MtChimney_Text_ShelbyDefeat:
	.string "{CHN}哎呀，我的天哪。\n"
	.string "你可真了不起！$"

MtChimney_Text_ShelbyPostBattle:
	.string "{CHN}哎哟，我输了。这样的话，\n"
	.string "我就不能自称是行家了，对吧？$"

MtChimney_Text_ShelbyRegister:
	.string "{CHN}谢谢你，孩子。这场对战很愉快，\n"
	.string "就像在跟我自己的孙子战斗一样。\p"
	.string "请再来找我\n"
	.string "重赛一场吧。$"

MtChimney_Text_ShelbyRematchIntro:
	.string "{CHN}如果你能和自己的宝可梦心连心，\n"
	.string "那你应该\l"
	.string "能成就一番大事业。$"

MtChimney_Text_ShelbyRematchDefeat:
	.string "{CHN}哎呀，我的天哪。\n"
	.string "你可真了不起！$"

MtChimney_Text_ShelbyPostRematch:
	.string "{CHN}也许你的心已经和\n"
	.string "宝可梦的心融为一体了。$"

MtChimney_Text_MelissaIntro:
	.string "{CHN}我体内有一团火，宝贝。\n"
	.string "我受不了了！我得战斗！$"

MtChimney_Text_MelissaDefeat:
	.string "{CHN}哦，这场对战真是火热！$"

MtChimney_Text_MelissaPostBattle:
	.string "{CHN}烟突山的热气让我\n"
	.string "浑身暖洋洋的，宝贝！$"

MtChimney_Text_SheilaIntro:
	.string "{CHN}我终于到了烟突山。\n"
	.string "我要让我的宝可梦战斗！$"

MtChimney_Text_SheilaDefeat:
	.string "{CHN}你的战斗方式…\n"
	.string "就像烟突山的喷发一样！$"

MtChimney_Text_SheilaPostBattle:
	.string "{CHN}正如我说的，我终于到了\n"
	.string "烟突山。如果只是\l"
	.string "稍微观光一下那就太可惜了…\p"
	.string "我想多打几场对战，\n"
	.string "再买些饼干当纪念品。$"

MtChimney_Text_ShirleyIntro:
	.string "{CHN}自从泡了温泉之后，\n"
	.string "我觉得棒极了！\l"
	.string "我确信我一定会赢！$"

MtChimney_Text_ShirleyDefeat:
	.string "{CHN}哎哟！\n"
	.string "离开水后我感觉有点冷。$"

MtChimney_Text_ShirleyPostBattle:
	.string "{CHN}我得再去泡一次温泉。\n"
	.string "你想一起来吗？\p"
	.string "开玩笑的啦！$"

MtChimney_Text_SawyerIntro:
	.string "{CHN}这座山真不错！\n"
	.string "周围有好多热情的人作伴！$"

MtChimney_Text_SawyerDefeat:
	.string "{CHN}哦，你也是个火爆的家伙！$"

MtChimney_Text_SawyerPostBattle:
	.string "{CHN}我觉得我需要和当地人\n"
	.string "一起去烟突市温泉泡一泡！$"

MtChimney_Text_SawyerRegister:
	.string "{CHN}我喜欢你这样的小火球。\n"
	.string "让我把你的资料登录到我的宝可领航员里吧。$"

MtChimney_Text_SawyerRematchIntro:
	.string "{CHN}在这一带我被热情的人包围着，\n"
	.string "真开心。我不会输的！$"

MtChimney_Text_SawyerRematchDefeat:
	.string "{CHN}天哪，你还是和以前一样\n"
	.string "是个火爆的家伙！$"

MtChimney_Text_SawyerPostRematch:
	.string "{CHN}说实话，这里确实很热。\n"
	.string "我在这地方穿得太多了。$"

