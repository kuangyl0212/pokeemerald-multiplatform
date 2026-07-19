SootopolisCity_Gym_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SootopolisCity_Gym_1F_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, SootopolisCity_Gym_1F_OnResume
	map_script MAP_SCRIPT_ON_LOAD, SootopolisCity_Gym_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, SootopolisCity_Gym_1F_OnTransition
	.byte 0

SootopolisCity_Gym_1F_OnTransition:
	setvar VAR_ICE_STEP_COUNT, 1
	end

SootopolisCity_Gym_1F_OnResume:
	setstepcallback STEP_CB_SOOTOPOLIS_ICE
	end

SootopolisCity_Gym_1F_OnLoad:
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special SetSootopolisGymCrackedIceMetatiles
	end

SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles::
	goto_if_lt VAR_ICE_STEP_COUNT, 8, SootopolisCity_Gym_1F_EventScript_StopCheckingStairs  /* All stairs ice*/
	goto_if_lt VAR_ICE_STEP_COUNT, 28, SootopolisCity_Gym_1F_EventScript_OpenFirstStairs
	goto_if_lt VAR_ICE_STEP_COUNT, 67, SootopolisCity_Gym_1F_EventScript_OpenFirstAndSecondStairs
	setmetatile 8, 4, METATILE_SootopolisGym_Stairs, FALSE
	setmetatile 8, 5, METATILE_SootopolisGym_Stairs, FALSE
SootopolisCity_Gym_1F_EventScript_OpenFirstAndSecondStairs::
	setmetatile 8, 10, METATILE_SootopolisGym_Stairs, FALSE
	setmetatile 8, 11, METATILE_SootopolisGym_Stairs, FALSE
SootopolisCity_Gym_1F_EventScript_OpenFirstStairs::
	setmetatile 8, 15, METATILE_SootopolisGym_Stairs, FALSE
	setmetatile 8, 16, METATILE_SootopolisGym_Stairs, FALSE
SootopolisCity_Gym_1F_EventScript_StopCheckingStairs::
	return

SootopolisCity_Gym_1F_OnFrame:
	map_script_2 VAR_ICE_STEP_COUNT, 8, SootopolisCity_Gym_1F_EventScript_UnlockFirstStairs
	map_script_2 VAR_ICE_STEP_COUNT, 28, SootopolisCity_Gym_1F_EventScript_UnlockSecondStairs
	map_script_2 VAR_ICE_STEP_COUNT, 67, SootopolisCity_Gym_1F_EventScript_UnlockThirdStairs
	map_script_2 VAR_ICE_STEP_COUNT, 0, SootopolisCity_Gym_1F_EventScript_FallThroughIce
	.short 0

SootopolisCity_Gym_1F_EventScript_UnlockFirstStairs::
	addvar VAR_ICE_STEP_COUNT, 1
	delay 40
	playse SE_ICE_STAIRS
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special DrawWholeMapView
	end

SootopolisCity_Gym_1F_EventScript_UnlockSecondStairs::
	addvar VAR_ICE_STEP_COUNT, 1
	delay 40
	playse SE_ICE_STAIRS
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special DrawWholeMapView
	end

SootopolisCity_Gym_1F_EventScript_UnlockThirdStairs::
	addvar VAR_ICE_STEP_COUNT, 1
	delay 40
	playse SE_ICE_STAIRS
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special DrawWholeMapView
	end

SootopolisCity_Gym_1F_EventScript_FallThroughIce::
	lockall
	delay 20
	applymovement LOCALID_PLAYER, SootopolisCity_Gym_1F_Movement_FallThroughIce
	waitmovement 0
	playse SE_FALL
	delay 60
	warphole MAP_SOOTOPOLIS_CITY_GYM_B1F
	waitstate
	end

SootopolisCity_Gym_1F_Movement_FallThroughIce:
	set_invisible
	step_end

SootopolisCity_Gym_1F_EventScript_Juan::
	trainerbattle_single TRAINER_JUAN_1, SootopolisCity_Gym_1F_Text_JuanIntro, SootopolisCity_Gym_1F_Text_JuanDefeat, SootopolisCity_Gym_1F_EventScript_JuanDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, SootopolisCity_Gym_1F_EventScript_JuanRematch
	goto_if_unset FLAG_RECEIVED_TM_WATER_PULSE, SootopolisCity_Gym_1F_EventScript_GiveWaterPulse2
	goto_if_unset FLAG_BADGE06_GET, SootopolisCity_Gym_1F_EventScript_GoGetFortreeBadge
	msgbox SootopolisCity_Gym_1F_Text_JuanPostBattle, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_JuanDefeated::
	message SootopolisCity_Gym_1F_Text_ReceivedRainBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox SootopolisCity_Gym_1F_Text_ExplainRainBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_SOOTOPOLIS_GYM
	setflag FLAG_BADGE08_GET
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_RESIDENTS
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_STEVEN
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_WALLACE
	setvar VAR_SOOTOPOLIS_CITY_STATE, 6
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_MAN_1
	setvar VAR_0x8008, 8
	call Common_EventScript_SetGymTrainers
	call SootopolisCity_Gym_1F_EventScript_GiveWaterPulse
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox SootopolisCity_Gym_1F_Text_RegisteredJuan, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_JUAN_MATCH_CALL
	release
	end

SootopolisCity_Gym_1F_EventScript_GiveWaterPulse::
	giveitem ITEM_TM_WATER_PULSE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox SootopolisCity_Gym_1F_Text_ExplainWaterPulse, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_WATER_PULSE
	return

SootopolisCity_Gym_1F_EventScript_GiveWaterPulse2::
	giveitem ITEM_TM_WATER_PULSE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox SootopolisCity_Gym_1F_Text_ExplainWaterPulse, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_WATER_PULSE
	release
	end

SootopolisCity_Gym_1F_EventScript_GoGetFortreeBadge::
	msgbox SootopolisCity_Gym_1F_Text_GoGetFortreeBadge, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_JuanRematch::
	trainerbattle_rematch_double TRAINER_JUAN_1, SootopolisCity_Gym_1F_Text_JuanPreRematch, SootopolisCity_Gym_1F_Text_JuanRematchDefeat, SootopolisCity_Gym_1F_Text_JuanRematchNeedTwoMons
	msgbox SootopolisCity_Gym_1F_Text_JuanPostRematch, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_1F_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SOOTOPOLIS_GYM, SootopolisCity_Gym_1F_EventScript_GymGuidePostVictory
	msgbox SootopolisCity_Gym_1F_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_GymGuidePostVictory::
	msgbox SootopolisCity_Gym_1F_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE08_GET, SootopolisCity_Gym_1F_EventScript_GymStatueCertified
	goto SootopolisCity_Gym_1F_EventScript_GymStatue
	end

SootopolisCity_Gym_1F_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE08_GET, SootopolisCity_Gym_1F_EventScript_GymStatueCertified
	goto SootopolisCity_Gym_1F_EventScript_GymStatue
	end

SootopolisCity_Gym_1F_EventScript_GymStatueCertified::
	msgbox SootopolisCity_Gym_1F_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_Gym_1F_EventScript_GymStatue::
	msgbox SootopolisCity_Gym_1F_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_Gym_1F_Text_GymGuideAdvice:
	.string "{CHN}哟！最近怎么样，迈向\n"
	.string "冠军的{PLAYER}？\p"
	.string "琉璃市的道馆馆主亚当是\n"
	.string "水属性宝可梦的大师。\p"
	.string "而且，要到达亚当那里，\n"
	.string "结冰的地板会阻碍你前进……\p"
	.string "听着，很抱歉，我能给你的\n"
	.string "建议就这么多了。\p"
	.string "剩下的路，你得\n"
	.string "自己闯了！$"

SootopolisCity_Gym_1F_Text_GymGuidePostVictory:
	.string "{CHN}哇！你连亚当都打败了，\n"
	.string "他可是丰缘最强的！\p"
	.string "好！看看你的训练家卡片。\p"
	.string "如果你已经集齐了所有徽章，\n"
	.string "就可以挑战宝可梦联盟了！$"

SootopolisCity_Gym_1F_Text_JuanIntro:
	.string "{CHN}让我问你。\n"
	.string "你知道吗？\l"
	.string "啊，我不该这么拐弯抹角。\p"
	.string "是我教米可利关于宝可梦\n"
	.string "的一切。\p"
	.string "我曾一度放弃了\n"
	.string "道馆馆主的职位。\p"
	.string "我把道馆\n"
	.string "托付给了米可利。\p"
	.string "但是，出现了一个\n"
	.string "让我不得不复出的理由。\p"
	.string "啊，闲话少说。\n"
	.string "让我们开始比赛吧，好吗？\p"
	.string "请你见证\n"
	.string "我们的艺术。\p"
	.string "由宝可梦和我共同雕琢的\n"
	.string "华丽水之幻象！$"

/* NOTE: This defeat text actually causes a buffer overflow. It's about 50 bytes too long for*/
/* the gDisplayedStringBattle buffer that it's put into, and it stomps all over the gBattleTextBuffs*/
/* after, as well as the otherwise unused array after that. One wonders if that's the reason for*/
/* the existence of that unused array of ints.*/
SootopolisCity_Gym_1F_Text_JuanDefeat:
	.string "{CHN}哈哈哈，太精彩了！\n"
	.string "好吧，你赢了。\p"
	.string "从你身上，我感受到了能克服\n"
	.string "一切的璀璨技艺之光。\p"
	.string "不过，和我甚至\n"
	.string "米可利相比，你还缺少优雅。\p"
	.string "也许我该把我的衣服\n"
	.string "借给你？\p"
	.string "…… …… …… …… …… …\n"
	.string "…… …… …… …… …… …\p"
	.string "哈哈哈，我只是开玩笑！\p"
	.string "比起我的衣服，我还是\n"
	.string "用这个雨之徽章来奖励你吧！$"

SootopolisCity_Gym_1F_Text_ReceivedRainBadge:
	.string "{CHN}{PLAYER}从亚当那里获得了\n"
	.string "雨之徽章。$"

SootopolisCity_Gym_1F_Text_ExplainRainBadgeTakeThis:
	.string "{CHN}拥有雨之徽章可以确保\n"
	.string "你的所有宝可梦\l"
	.string "完全服从你的每个命令。\p"
	.string "雨之徽章还允许你使用\n"
	.string "秘传招式攀瀑来攀上\l"
	.string "倾泻的水壁。\p"
	.string "而且，为了让你永远不忘\n"
	.string "我们之间的对战，收下这个……$"

SootopolisCity_Gym_1F_Text_ExplainWaterPulse:
	.string "{CHN}我给你的技能学习器\n"
	.string "里装的是水之波动。\p"
	.string "使用时，它会用超声波\n"
	.string "偶尔让对手陷入混乱。\p"
	.string "…… …… …… …… …… …$"

SootopolisCity_Gym_1F_Text_RegisteredJuan:
	.string "{CHN}在宝可梦导航器中登录了\n"
	.string "道馆馆主亚当。$"

SootopolisCity_Gym_1F_Text_JuanPostBattle:
	.string "{CHN}集齐了丰缘所有\n"
	.string "道馆徽章的训练家，该前往\l"
	.string "最终目的地了。\p"
	.string "宝可梦联盟。\p"
	.string "前往丰缘的最东端，\n"
	.string "到达暮水镇岛。\p"
	.string "在那里，你会找到\n"
	.string "宝可梦联盟。$"

SootopolisCity_Gym_1F_Text_GoGetFortreeBadge:
	.string "{CHN}丰缘还有一个\n"
	.string "徽章没有获得。\p"
	.string "如果你想挑战宝可梦\n"
	.string "联盟，你必须从茵郁的道馆\l"
	.string "获得最后一个徽章。$"

SootopolisCity_Gym_1F_Text_GymStatue:
	.string "{CHN}琉璃市宝可梦道馆$"

SootopolisCity_Gym_1F_Text_GymStatueCertified:
	.string "{CHN}琉璃市宝可梦道馆\p"
	.string "亚当认证的训练家：\n"
	.string "{PLAYER}$"

SootopolisCity_Gym_1F_Text_JuanPreRematch:
	.string "{CHN}亚当：啊，这座道馆已经恢复了\n"
	.string "往日的宁静……\p"
	.string "但我们的小台风又回来了\n"
	.string "要再次考验我们！\p"
	.string "好的，我的朋友，当然！\p"
	.string "我很乐意和你一起舞蹈，\n"
	.string "想跳多少次都行！$"

SootopolisCity_Gym_1F_Text_JuanRematchDefeat:
	.string "{CHN}哈哈哈，你赢了！\n"
	.string "你又打败我了！$"

SootopolisCity_Gym_1F_Text_JuanPostRematch:
	.string "{CHN}亚当：如果我让你做我的\n"
	.string "徒弟，你一定会拒绝。\p"
	.string "我想把我的外套\n"
	.string "送给你。\p"
	.string "但你也会拒绝。\n"
	.string "我想应该是这样。\p"
	.string "而那，我的朋友，正是\n"
	.string "高贵品质的象征！$"

SootopolisCity_Gym_1F_Text_JuanRematchNeedTwoMons:
	.string "{CHN}亚当：啊，这座道馆已经恢复了\n"
	.string "往日的宁静……\p"
	.string "但我们的小台风又回来了\n"
	.string "要再次考验我们！\p"
	.string "好的，我的朋友，当然！\n"
	.string "我很乐意和你一起舞蹈……\p"
	.string "啊，不不不。\n"
	.string "你只带了一只宝可梦。\p"
	.string "希望你带着两只，\n"
	.string "也许更多宝可梦再来吧。$"

