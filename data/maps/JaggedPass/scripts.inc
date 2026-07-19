JaggedPass_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, JaggedPass_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, JaggedPass_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, JaggedPass_OnLoad
	.byte 0

JaggedPass_OnResume:
	setstepcallback STEP_CB_ASH
	call_if_eq VAR_JAGGED_PASS_STATE, 0, JaggedPass_EventScript_CheckHasMagmaEmblem
	end

JaggedPass_EventScript_CheckHasMagmaEmblem::
	checkitem ITEM_MAGMA_EMBLEM
	goto_if_eq VAR_RESULT, TRUE, JaggedPass_EventScript_SetReadyToOpenHideout
	return

JaggedPass_EventScript_SetReadyToOpenHideout::
	setvar VAR_JAGGED_PASS_STATE, 1
	return

JaggedPass_OnTransition:
	call_if_eq VAR_JAGGED_PASS_ASH_WEATHER, 1, JaggedPass_EventScript_SetWeatherAsh
	end

JaggedPass_EventScript_SetWeatherAsh::
	setweather WEATHER_VOLCANIC_ASH
	doweather
	return

JaggedPass_OnLoad:
	goto_if_le VAR_JAGGED_PASS_STATE, 1, JaggedPass_EventScript_ConcealHideoutEntrance
	end

JaggedPass_EventScript_ConcealHideoutEntrance::
	setmetatile 16, 17, METATILE_Lavaridge_RockWall, TRUE
	setmetatile 16, 18, METATILE_Lavaridge_RockWall, TRUE
	end

JaggedPass_EventScript_OpenMagmaHideout::
	lockall
	setvar VAR_0x8004, 1  /* vertical pan*/
	setvar VAR_0x8005, 1  /* horizontal pan*/
	setvar VAR_0x8006, 8  /* num shakes*/
	setvar VAR_0x8007, 5  /* shake delay*/
	special ShakeCamera
	waitstate
	msgbox JaggedPass_Text_BoulderShakingInResponseToEmblem, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 1   /* vertical pan*/
	setvar VAR_0x8005, 1   /* horizontal pan*/
	setvar VAR_0x8006, 16  /* num shakes*/
	setvar VAR_0x8007, 3   /* shake delay*/
	special ShakeCamera
	waitstate
	playse SE_EFFECTIVE
	setmetatile 16, 17, METATILE_Lavaridge_CaveEntrance_Top, TRUE
	setmetatile 16, 18, METATILE_Lavaridge_CaveEntrance_Bottom, FALSE
	special DrawWholeMapView
	delay 30
	setvar VAR_JAGGED_PASS_STATE, 2
	waitse
	releaseall
	end

JaggedPass_EventScript_MagmaHideoutGuard::
	lockall
	goto_if_set FLAG_BEAT_MAGMA_GRUNT_JAGGED_PASS, JaggedPass_EventScript_GuardDefeated
	waitse
	playse SE_PIN
	applymovement LOCALID_MAGMA_HIDEOUT_GUARD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAGMA_HIDEOUT_GUARD, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_MAGMA_HIDEOUT_GUARD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox JaggedPass_Text_GruntIntro, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_GRUNT_JAGGED_PASS, JaggedPass_Text_GruntDefeat
	setflag FLAG_BEAT_MAGMA_GRUNT_JAGGED_PASS
	applymovement LOCALID_MAGMA_HIDEOUT_GUARD, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

JaggedPass_EventScript_GuardDefeated::
	applymovement LOCALID_MAGMA_HIDEOUT_GUARD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox JaggedPass_Text_GoWhereverYouWant, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAGMA_HIDEOUT_GUARD, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

JaggedPass_EventScript_Eric::
	trainerbattle_single TRAINER_ERIC, JaggedPass_Text_EricIntro, JaggedPass_Text_EricDefeat
	msgbox JaggedPass_Text_EricPostBattle, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Diana::
	trainerbattle_single TRAINER_DIANA_1, JaggedPass_Text_DianaIntro, JaggedPass_Text_DianaDefeat, JaggedPass_EventScript_RegisterDiana
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, JaggedPass_EventScript_DianaRematch
	msgbox JaggedPass_Text_DianaPostBattle, MSGBOX_DEFAULT
	release
	end

JaggedPass_EventScript_RegisterDiana::
	special PlayerFaceTrainerAfterBattle
	msgbox JaggedPass_Text_DianaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_DIANA_1
	release
	end

JaggedPass_EventScript_DianaRematch::
	trainerbattle_rematch TRAINER_DIANA_1, JaggedPass_Text_DianaRematchIntro, JaggedPass_Text_DianaRematchDefeat
	msgbox JaggedPass_Text_DianaPostRematch, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Ethan::
	trainerbattle_single TRAINER_ETHAN_1, JaggedPass_Text_EthanIntro, JaggedPass_Text_EthanDefeat, JaggedPass_EventScript_RegisterEthan
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, JaggedPass_EventScript_EthanRematch
	msgbox JaggedPass_Text_EthanPostBattle, MSGBOX_DEFAULT
	release
	end

JaggedPass_EventScript_RegisterEthan::
	special PlayerFaceTrainerAfterBattle
	msgbox JaggedPass_Text_EthanRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ETHAN_1
	release
	end

JaggedPass_EventScript_EthanRematch::
	trainerbattle_rematch TRAINER_ETHAN_1, JaggedPass_Text_EthanRematchIntro, JaggedPass_Text_EthanRematchDefeat
	msgbox JaggedPass_Text_EthanPostRematch, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Julio::
	trainerbattle_single TRAINER_JULIO, JaggedPass_Text_JulioIntro, JaggedPass_Text_JulioDefeat
	msgbox JaggedPass_Text_JulioPostBattle, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Autumn::
	trainerbattle_single TRAINER_AUTUMN, JaggedPass_Text_AutumnIntro, JaggedPass_Text_AutumnDefeat
	msgbox JaggedPass_Text_AutumnPostBattle, MSGBOX_AUTOCLOSE
	end

JaggedPass_Text_EricIntro:
	.string "{CHN}烟突山的凹凸山道…\p"
	.string "这正是我一直想要的\n"
	.string "山脉的样子。\p"
	.string "这种凹凸不平的感觉…\n"
	.string "震撼着我的灵魂！$"

JaggedPass_Text_EricDefeat:
	.string "{CHN}输了让我心里很不是滋味！$"

JaggedPass_Text_EricPostBattle:
	.string "{CHN}是的，我确实在宝可梦对战上输了…\p"
	.string "但是说到对山的热爱，\n"
	.string "我可比你强多了！$"

JaggedPass_Text_DianaIntro:
	.string "{CHN}这里可不是随便爬爬山的地方。\n"
	.string "不适合野餐。$"

JaggedPass_Text_DianaDefeat:
	.string "{CHN}哦，不！\n"
	.string "地面太凹凸不平了…$"

JaggedPass_Text_DianaPostBattle:
	.string "{CHN}你知道吗？\p"
	.string "有些人很聪明地骑着自行车\n"
	.string "爬上这条凹凸得要命的山道。$"

JaggedPass_Text_DianaRegister:
	.string "{CHN}你还会再回这一带吗？\n"
	.string "如果你再来的话，我想跟你重赛。$"

JaggedPass_Text_DianaRematchIntro:
	.string "{CHN}野餐到哪里都很有趣。\n"
	.string "就像宝可梦一样！$"

JaggedPass_Text_DianaRematchDefeat:
	.string "{CHN}我只是因为地面太凹凸不平\n"
	.string "才输的！$"

JaggedPass_Text_DianaPostRematch:
	.string "{CHN}我会忘掉输的事，\n"
	.string "好好享受这凹凸不平的登山之旅。$"

JaggedPass_Text_EthanIntro:
	.string "{CHN}凹凸山道很难走。\n"
	.string "这是个训练的好地方。$"

JaggedPass_Text_EthanDefeat:
	.string "{CHN}我们还在找稳当的立足点时，\n"
	.string "战斗就已经结束了…$"

JaggedPass_Text_EthanPostBattle:
	.string "{CHN}如果我有一辆特技自行车，\n"
	.string "我就能跳过台阶了。$"

JaggedPass_Text_EthanRegister:
	.string "{CHN}等我更习惯这种凹凸不平的路，\n"
	.string "我一定会赢的！\p"
	.string "你能把我登录到\n"
	.string "你的宝可领航员里吗？$"

JaggedPass_Text_EthanRematchIntro:
	.string "{CHN}我已经习惯了这种凹凸不平。\n"
	.string "现在我一边爬一边唱歌。$"

JaggedPass_Text_EthanRematchDefeat:
	.string "{CHN}在这种凹凸不平的地面上战斗\n"
	.string "还是不容易…$"

JaggedPass_Text_EthanPostRematch:
	.string "{CHN}我应该去紫堇市找翔太\n"
	.string "弄一辆特技自行车…$"

JaggedPass_Text_GruntIntro:
	.string "{CHN}哇！\n"
	.string "你在这里做什么？\p"
	.string "那我又在这种地方做什么？\p"
	.string "这关你什么事？$"

JaggedPass_Text_GruntDefeat:
	.string "{CHN}呃呃…\p"
	.string "我应该直接躲进\n"
	.string "我们的秘密基地里才对…$"

JaggedPass_Text_GoWhereverYouWant:
	.string "{CHN}好，好吧！\n"
	.string "我承认——你很强！\p"
	.string "别管我了。\n"
	.string "你想去哪里就去哪里吧！$"

JaggedPass_Text_BoulderShakingInResponseToEmblem:
	.string "{CHN}哦！这块巨石感应到\n"
	.string "熔岩徽章在震动！$"

JaggedPass_Text_JulioIntro:
	.string "{CHN}哇啊！\n"
	.string "一口气冲下山真是可怕极了！$"

JaggedPass_Text_JulioDefeat:
	.string "{CHN}我感觉自己要散架了…$"

JaggedPass_Text_JulioPostBattle:
	.string "{CHN}我的自行车颠得厉害，\n"
	.string "我的屁股都疼了…$"

JaggedPass_Text_AutumnIntro:
	.string "{CHN}我每天都会爬这座山。\n"
	.string "我对自己的体力很有信心！$"

JaggedPass_Text_AutumnDefeat:
	.string "{CHN}嗯…\n"
	.string "哪里出问题了？$"

JaggedPass_Text_AutumnPostBattle:
	.string "{CHN}从这里往山上走一点，\n"
	.string "那个奇怪的岩石突起是什么？$"

