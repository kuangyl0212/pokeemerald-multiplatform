LilycoveCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, LilycoveCity_OnLoad
	.byte 0

LilycoveCity_OnTransition:
	setflag FLAG_VISITED_LILYCOVE_CITY
	setvar VAR_CONTEST_HALL_STATE, 0
	setflag FLAG_HIDE_LILYCOVE_CONTEST_HALL_REPORTER
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	call Common_EventScript_SetupRivalGfxId
	end

LilycoveCity_OnLoad:
	call_if_unset FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_SetWailmerMetatiles
	end

LilycoveCity_EventScript_SetWailmerMetatiles::
	setmetatile 76, 12, METATILE_Lilycove_Wailmer0, TRUE
	setmetatile 77, 12, METATILE_Lilycove_Wailmer1, TRUE
	setmetatile 76, 13, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 77, 13, METATILE_Lilycove_Wailmer3, TRUE
	setmetatile 76, 14, METATILE_Lilycove_Wailmer0_Alt, TRUE
	setmetatile 77, 14, METATILE_Lilycove_Wailmer1_Alt, TRUE
	setmetatile 76, 15, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 77, 15, METATILE_Lilycove_Wailmer3, TRUE
	setmetatile 77, 16, METATILE_Lilycove_Wailmer0_Alt, TRUE
	setmetatile 78, 16, METATILE_Lilycove_Wailmer1_Alt, TRUE
	setmetatile 77, 17, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 78, 17, METATILE_Lilycove_Wailmer3, TRUE
	return

LilycoveCity_EventScript_BerryGentleman::
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_LILYCOVE_RECEIVED_BERRY, LilycoveCity_EventScript_ReceivedBerry
	msgbox LilycoveCity_Text_BerrySuitsYou, MSGBOX_DEFAULT
	random 10
	addvar VAR_RESULT, FIRST_BERRY_INDEX
	giveitem VAR_RESULT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_LILYCOVE_RECEIVED_BERRY
	msgbox LilycoveCity_Text_BecauseYoureTrainer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_ReceivedBerry::
	msgbox LilycoveCity_Text_PokeblocksSuitPokemon, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Man3::
	msgbox LilycoveCity_Text_ContestHallInTown, MSGBOX_NPC
	end

LilycoveCity_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_EventScript_GirlAquaGone
	msgbox LilycoveCity_Text_StrangeCaveInCove, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_GirlAquaGone::
	msgbox LilycoveCity_Text_GoingToMoveDeleterForHMs, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_RichBoy::
	msgbox LilycoveCity_Text_ImFromKanto, MSGBOX_NPC
	end

LilycoveCity_EventScript_Sailor2::
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_Sailor2AquaGone
	msgbox LilycoveCity_Text_TeamAquaBeenTrainingWailmer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Sailor2AquaGone::
	msgbox LilycoveCity_Text_SomeonePuntedTeamAquaOut, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Woman2::
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_Woman2AquaGone
	msgbox LilycoveCity_Text_SomeoneStoleMyPokemon, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Woman2AquaGone::
	msgbox LilycoveCity_Text_MissingPokemonCameBack, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Man2::
	msgbox LilycoveCity_Text_ImArtDealer, MSGBOX_NPC
	end

LilycoveCity_EventScript_ExpertM1::
	msgbox LilycoveCity_Text_SeaRemainsForeverYoung, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ExpertF::
	msgbox LilycoveCity_Text_SixtyYearsAgoHusbandProposed, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ExpertM2::
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_EventScript_ExpertM2AquaGone
	msgbox LilycoveCity_Text_TeamAquaRenovatedCavern, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_ExpertM2AquaGone::
	msgbox LilycoveCity_Text_TeamAquaLotGoneForGood, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Sailor1::
	msgbox LilycoveCity_Text_HeardTowerCalledSkyPillar, MSGBOX_NPC
	end

LilycoveCity_EventScript_FatMan::
	msgbox LilycoveCity_Text_SawTallTowerOnRoute131, MSGBOX_NPC
	end

LilycoveCity_EventScript_Man1::
	lockall
	msgbox LilycoveCity_Text_JustArrivedAndSawRarePokemon, MSGBOX_NPC
	applymovement LOCALID_LILYCOVE_MAN_1, Common_Movement_FaceOriginalDirection
	end

LilycoveCity_EventScript_Woman1::
	lockall
	msgbox LilycoveCity_Text_HoneymoonVowToSeeRarePokemon, MSGBOX_NPC
	applymovement LOCALID_LILYCOVE_WOMAN_1, Common_Movement_FaceOriginalDirection
	end

LilycoveCity_EventScript_CitySign::
	msgbox LilycoveCity_Text_CitySign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ContestHallSign::
	msgbox LilycoveCity_Text_ContestHallSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MotelSign::
	msgbox LilycoveCity_Text_MotelSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MuseumSign::
	lockall
	specialvar VAR_0x8004, CountPlayerMuseumPaintings
	switch VAR_0x8004
	case 0, LilycoveCity_EventScript_MuseumSignNoPaintings
	msgbox LilycoveCity_Text_MuseumSignPlayersExhibit, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_MuseumSignNoPaintings::
	msgbox LilycoveCity_Text_MuseumSign, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_HarborSign::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_HarborSignFerryReady
	msgbox LilycoveCity_Text_HarborSignUnderConstruction, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_HarborSignFerryReady::
	msgbox LilycoveCity_Text_HarborSign, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_TrainerFanClubSign::
	msgbox LilycoveCity_Text_TrainerFanClubSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_DepartmentStoreSign::
	msgbox LilycoveCity_Text_DepartmentStoreSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MoveDeletersHouseSign::
	msgbox LilycoveCity_Text_MoveDeletersHouseSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_WailmerTrainerGrunt::
	lockall
	goto_if_set FLAG_MET_WAILMER_TRAINER, LilycoveCity_EventScript_MetWailmerTrainer
	msgbox LilycoveCity_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_Text_GetLostMessingUpTraining, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_MET_WAILMER_TRAINER
	releaseall
	end

LilycoveCity_EventScript_MetWailmerTrainer::
	msgbox LilycoveCity_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_AquaGrunt1::
	msgbox LilycoveCity_Text_MovedLootIntoHideoutToday, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt2::
	msgbox LilycoveCity_Text_ChanceToDoBigThings, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt3::
	msgbox LilycoveCity_Text_DontGoNearCaveInCove, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt4::
	msgbox LilycoveCity_Text_IfWorldBecomesOurs, MSGBOX_NPC
	end

LilycoveCity_EventScript_Rival::
	lock
	faceplayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LilycoveCity_EventScript_May
	goto_if_eq VAR_RESULT, FEMALE, LilycoveCity_EventScript_Brendan
	end

LilycoveCity_EventScript_May::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	call_if_set FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_MayAskToBattleAgain
	call_if_unset FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_MayAskToBattle
	goto_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DeclineMayBattle
	msgbox LilycoveCity_Text_MayWontBeBeaten, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, LilycoveCity_EventScript_BattleMayTreecko
	case 1, LilycoveCity_EventScript_BattleMayTorchic
	case 2, LilycoveCity_EventScript_BattleMayMudkip
	end

LilycoveCity_EventScript_MayAskToBattleAgain::
	msgbox LilycoveCity_Text_MayBattleMe, MSGBOX_YESNO
	return

LilycoveCity_EventScript_MayAskToBattle::
	msgbox LilycoveCity_Text_MayShoppingLetsBattle, MSGBOX_YESNO
	return

LilycoveCity_EventScript_DeclineMayBattle::
	setflag FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE
	msgbox LilycoveCity_Text_MayNotRaisingPokemon, MSGBOX_DEFAULT
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

LilycoveCity_EventScript_Brendan::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	call_if_set FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_BrendanAskToBattleAgain
	call_if_unset FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_BrendanAskToBattle
	goto_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DeclineBrendanBattle
	msgbox LilycoveCity_Text_BrendanWontBeBeaten, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, LilycoveCity_EventScript_BattleBrendanTreecko
	case 1, LilycoveCity_EventScript_BattleBrendanTorchic
	case 2, LilycoveCity_EventScript_BattleBrendanMudkip
	end

LilycoveCity_EventScript_BrendanAskToBattleAgain::
	msgbox LilycoveCity_Text_BrendanBattleMe, MSGBOX_YESNO
	return

LilycoveCity_EventScript_BrendanAskToBattle::
	msgbox LilycoveCity_Text_BrendanShoppingLetsBattle, MSGBOX_YESNO
	return

LilycoveCity_EventScript_DeclineBrendanBattle::
	setflag FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE
	msgbox LilycoveCity_Text_BrendanNoConfidence, MSGBOX_DEFAULT
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

LilycoveCity_EventScript_BattleMayTreecko::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_TREECKO, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleMayTorchic::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_TORCHIC, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleMayMudkip::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_MUDKIP, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleBrendanTreecko::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_TREECKO, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_BattleBrendanTorchic::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_TORCHIC, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_BattleBrendanMudkip::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_MUDKIP, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_DefeatedMay::
	msgbox LilycoveCity_Text_MayGoingBackToLittleroot, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	call_if_set FLAG_BADGE06_GET, LilycoveCity_EventScript_CheckFinalBadge
	call_if_eq VAR_RESULT, FALSE, LilycoveCity_EventScript_MayCollectBadges
	call_if_eq VAR_RESULT, TRUE, LilycoveCity_EventScript_MayPokemonLeague
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_PICHU_DOLL
	goto LilycoveCity_EventScript_RivalFlyAway
	end

LilycoveCity_EventScript_CheckFinalBadge::
	goto_if_set FLAG_BADGE08_GET, LilycoveCity_EventScript_HasFinalBadge
	return

LilycoveCity_EventScript_HasFinalBadge::
	setvar VAR_RESULT, TRUE
	return

LilycoveCity_EventScript_MayCollectBadges::
	msgbox LilycoveCity_Text_MayYouGoingToCollectBadges, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_MayPokemonLeague::
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_MayBattleFrontier
	msgbox LilycoveCity_Text_MayYouGoingToPokemonLeague, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_MayBattleFrontier::
	msgbox LilycoveCity_Text_MayYouGoingToBattleFrontier, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_DefeatedBrendan::
	msgbox LilycoveCity_Text_BrendanGoingBackToLittleroot, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	call_if_set FLAG_BADGE06_GET, LilycoveCity_EventScript_CheckFinalBadge
	call_if_eq VAR_RESULT, FALSE, LilycoveCity_EventScript_BrendanCollectBadges
	call_if_eq VAR_RESULT, TRUE, LilycoveCity_EventScript_BrendanPokemonLeague
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_SWABLU_DOLL
	goto LilycoveCity_EventScript_RivalFlyAway
	end

LilycoveCity_EventScript_BrendanCollectBadges::
	msgbox LilycoveCity_Text_BrendanYouGoingToCollectBadges, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_BrendanPokemonLeague::
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_BrendanBattleFrontier
	msgbox LilycoveCity_Text_BrendanYouGoingToPokemonLeague, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_BrendanBattleFrontier::
	msgbox LilycoveCity_Text_BrendanYouGoingToBattleFrontier, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_RivalFlyAway::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject VAR_LAST_TALKED
	waitfieldeffect FLDEFF_NPCFLY_OUT
	savebgm MUS_DUMMY
	fadedefaultbgm
	setflag FLAG_MET_RIVAL_LILYCOVE
	release
	end

LilycoveCity_EventScript_SchoolKidM::
	lock
	faceplayer
	msgbox LilycoveCity_Text_DoYouKnowAboutBerryBlender, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, LilycoveCity_EventScript_KnowAboutBerryBlender
	call_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DontKnowAboutBerryBlender
	release
	end

LilycoveCity_EventScript_KnowAboutBerryBlender::
	msgbox LilycoveCity_Text_FasterSpinBetterPokeblocks, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_DontKnowAboutBerryBlender::
	msgbox LilycoveCity_Text_ExplainBerryBlender, MSGBOX_DEFAULT
	return

LilycoveCity_Text_MayShoppingLetsBattle:
	.string "{CHN}小遥：噢，喂？\n"
	.string "{PLAYER}{KUN}，你也在购物吗？\p"
	.string "我买了一堆玩偶和\n"
	.string "海报。\p"
	.string "当然，我也抓了很多宝可梦，\n"
	.string "而且也把它们培养得\l"
	.string "很好。\p"
	.string "其实，我更担心你有没有\n"
	.string "好好培养宝可梦，{PLAYER}{KUN}。\p"
	.string "我和你对战一场，\n"
	.string "好让我看看你的宝可梦，{PLAYER}{KUN}。$"

LilycoveCity_Text_MayNotRaisingPokemon:
	.string "{CHN}小遥：噢，为什么？{PLAYER}{KUN}，你\n"
	.string "没有好好培养宝可梦吗？\p"
	.string "作为训练家这可不太好啊……$"

LilycoveCity_Text_MayBattleMe:
	.string "{CHN}小遥：来吧，和我对战一场，\n"
	.string "好让我看看你的宝可梦！$"

LilycoveCity_Text_MayWontBeBeaten:
	.string "{CHN}小遥：我培养的宝可梦\n"
	.string "绝不会输给你的宝可梦，{PLAYER}{KUN}！$"

LilycoveCity_Text_MayDefeat:
	.string "{CHN}………………\p"
	.string "我还记得在103号道路上\n"
	.string "和你对战的事，{PLAYER}{KUN}。\p"
	.string "那场对战让你变得\n"
	.string "这么强，{PLAYER}{KUN}，对吧？$"

LilycoveCity_Text_MayGoingBackToLittleroot:
	.string "{CHN}小遥：我想着差不多\n"
	.string "回未白镇了。\p"
	.string "我抓了不少宝可梦，\n"
	.string "宝可梦图鉴也进展顺利，\l"
	.string "所以我打算回家给爸爸看看。$"

LilycoveCity_Text_MayYouGoingToCollectBadges:
	.string "{CHN}{PLAYER}{KUN}，你接下来打算做什么？\p"
	.string "是收集齐所有道馆徽章，\n"
	.string "挑战宝可梦联盟吗？\p"
	.string "那你去收集徽章的时候，\n"
	.string "{PLAYER}{KUN}，我要去搞我的\l"
	.string "宝可梦图鉴。我会比你先完成！\p"
	.string "再见啦！$"

LilycoveCity_Text_MayYouGoingToPokemonLeague:
	.string "{CHN}{PLAYER}{KUN}，你接下来打算做什么？\p"
	.string "你要挑战\n"
	.string "宝可梦联盟吗？\p"
	.string "还是说，你要去完成\n"
	.string "宝可梦图鉴？\p"
	.string "对战我可能输给了你，\n"
	.string "但宝可梦图鉴我一定会比你先完成！\p"
	.string "再见啦！$"

LilycoveCity_Text_MayYouGoingToBattleFrontier:
	.string "{CHN}{PLAYER}{KUN}，你接下来打算做什么？\p"
	.string "你要挑战\n"
	.string "对战开拓区吗？\p"
	.string "还是说，你要去完成\n"
	.string "宝可梦图鉴？\p"
	.string "对战我可能输给了你，\n"
	.string "但宝可梦图鉴我一定会比你先完成！\p"
	.string "再见啦！$"

LilycoveCity_Text_BrendanShoppingLetsBattle:
	.string "{CHN}佑树：噢，喂，是{PLAYER}啊。\p"
	.string "我在帮我爸爸跑腿。\n"
	.string "不，我才不买玩偶呢。\p"
	.string "话说回来，好久不见了。\p"
	.string "想不想来对战一场，\n"
	.string "看看谁培养宝可梦更厉害？$"

LilycoveCity_Text_BrendanNoConfidence:
	.string "{CHN}佑树：噢，怎么了？\n"
	.string "没自信吗？$"

LilycoveCity_Text_BrendanBattleMe:
	.string "{CHN}佑树：想不想对战一场，\n"
	.string "看看谁培养宝可梦更厉害？$"

LilycoveCity_Text_BrendanWontBeBeaten:
	.string "{CHN}佑树：啊，不过你知道的，\n"
	.string "我才不会输给{PLAYER}呢。$"

LilycoveCity_Text_BrendanDefeat:
	.string "{CHN}哼……\n"
	.string "你培养了不少啊。\p"
	.string "有点不甘心——我作为训练家\n"
	.string "可是先你一步开始的……$"

LilycoveCity_Text_BrendanGoingBackToLittleroot:
	.string "{CHN}佑树：我……\n"
	.string "我打算回未白镇的家。\p"
	.string "你知道我在帮我爸爸搞\n"
	.string "宝可梦图鉴。已经进展得\l"
	.string "差不多了，我该回去给他看看了。$"

LilycoveCity_Text_BrendanYouGoingToCollectBadges:
	.string "{CHN}{PLAYER}，你接下来打算做什么？\p"
	.string "是收集齐所有道馆徽章，\n"
	.string "挑战宝可梦联盟吗？\p"
	.string "也许我也会那么做……\p"
	.string "总之，加油！$"

LilycoveCity_Text_BrendanYouGoingToPokemonLeague:
	.string "{CHN}{PLAYER}，你接下来打算做什么？\p"
	.string "你都这么强了，\n"
	.string "是要挑战宝可梦联盟吗？\p"
	.string "嘿，就连我——只要再多训练一下宝可梦，\n"
	.string "应该就会比你\l"
	.string "更强，{PLAYER}。\p"
	.string "总之，加油！$"

LilycoveCity_Text_BrendanYouGoingToBattleFrontier:
	.string "{CHN}{PLAYER}，你接下来打算做什么？\p"
	.string "你要挑战\n"
	.string "对战开拓区吗？\p"
	.string "还是说，你要去完成\n"
	.string "宝可梦图鉴？\p"
	.string "你都这么强了，\n"
	.string "应该考虑一下对战开拓区。\p"
	.string "嘿，只要我再多训练一下宝可梦，\n"
	.string "就会比你强，{PLAYER}。\p"
	.string "也许我也该去\n"
	.string "对战开拓区看看。\p"
	.string "总之，加油！$"

LilycoveCity_Text_MovedLootIntoHideoutToday:
	.string "{CHN}呼呼呼……\p"
	.string "今天我们又往藏身处\n"
	.string "搬了不少战利品……\p"
	.string "你、你是谁？\n"
	.string "我只是在自言自语！$"

LilycoveCity_Text_ChanceToDoBigThings:
	.string "{CHN}我只是个小卒，所以我不知道\n"
	.string "老大在想什么……\p"
	.string "但在水舰队里，我知道我一定能\n"
	.string "干出一番大事！\p"
	.string "你、你是谁？\n"
	.string "我只是在自言自语！$"

LilycoveCity_Text_DontGoNearCaveInCove:
	.string "{CHN}喂，你！\p"
	.string "别靠近海湾里的那个洞窟！\p"
	.string "为什么？不需要理由！\n"
	.string "我是大人，你就听我的！$"

LilycoveCity_Text_IfWorldBecomesOurs:
	.string "{CHN}如果这整个世界都变成我们的，\n"
	.string "也就是水舰队的世界，\l"
	.string "对宝可梦来说也会更幸福。$"

LilycoveCity_Text_WailmerLeapOutOfWater:
	.string "{CHN}那里！吼吼鲸！\n"
	.string "现在从水里跳出来！$"

LilycoveCity_Text_GetLostMessingUpTraining:
	.string "{CHN}嗯？你要干什么？\p"
	.string "你打扰我们训练了，\n"
	.string "能不能识相点走开？$"

LilycoveCity_Text_ContestHallInTown:
	.string "{CHN}这个镇上就有一座\n"
	.string "宝可梦选拔赛会堂。\p"
	.string "这意味着来自全国各地的\n"
	.string "精心培养的宝可梦都会聚集到这里。\p"
	.string "我的心都激动得砰砰跳！$"

LilycoveCity_Text_StrangeCaveInCove:
	.string "{CHN}你看到镇子边缘那个海湾里\n"
	.string "奇怪的洞窟了吗？$"

LilycoveCity_Text_GoingToMoveDeleterForHMs:
	.string "{CHN}我要教我的宝可梦一些新招式，\n"
	.string "好去参加选拔赛。\p"
	.string "所以我要去找招式遗忘师，\n"
	.string "让它忘掉秘传学习器的招式。$"

LilycoveCity_Text_ImFromKanto:
	.string "{CHN}我从关都来的。\p"
	.string "丰缘地区有那么多水\n"
	.string "和翠绿的自然，真是太美了。\p"
	.string "嗯？等等……\p"
	.string "会不会有珍稀的宝可梦\n"
	.string "只住在这个地区呢？$"

LilycoveCity_Text_TeamAquaBeenTrainingWailmer:
	.string "{CHN}水舰队一直在海湾里\n"
	.string "训练他们的吼吼鲸。\p"
	.string "他们挡着路，\n"
	.string "我们这些水手都没法把船开到海上去！$"

LilycoveCity_Text_SomeonePuntedTeamAquaOut:
	.string "{CHN}嘿，你知道吗？\p"
	.string "有人把水舰队\n"
	.string "赶走了！\p"
	.string "吼吼鲸也离开了海湾，\n"
	.string "我们又能把船开出去了。$"

LilycoveCity_Text_SomeoneStoleMyPokemon:
	.string "{CHN}我在海边旅馆听着海浪声\n"
	.string "舒舒服服地打盹儿……\p"
	.string "结果有人偷了我的宝可梦！\p"
	.string "是谁干的？\n"
	.string "水舰队？是水舰队吗？$"

LilycoveCity_Text_MissingPokemonCameBack:
	.string "{CHN}我失踪的宝可梦……\n"
	.string "它不知不觉地回来了！$"

LilycoveCity_Text_ImArtDealer:
	.string "{CHN}我是美术商。\p"
	.string "我做艺术品买卖，\n"
	.string "尤其是画作。\p"
	.string "听说这里的博物馆\n"
	.string "有展出精美的作品……$"

LilycoveCity_Text_SeaRemainsForeverYoung:
	.string "{CHN}即便我们老得满脸皱纹，\n"
	.string "大海依然永远年轻，\l"
	.string "闪耀着生命的鲜明光彩……\p"
	.string "呼呵呵呼呵呵呵呵……$"

LilycoveCity_Text_SixtyYearsAgoHusbandProposed:
	.string "{CHN}六十年前，我丈夫\n"
	.string "就是在这里向我求婚的。\l"
	.string "大海还是那么美。\p"
	.string "呼呼呼呼 呼呼呼呼呼呼……$"

LilycoveCity_Text_TeamAquaRenovatedCavern:
	.string "{CHN}嗯，你知道这个海湾里\n"
	.string "那个奇怪的洞窟吗？\p"
	.string "那本是天然形成的，\n"
	.string "但水舰队那帮家伙\l"
	.string "过来做了改造。\p"
	.string "他们自称是\n"
	.string "“热爱自然的水舰队”！\p"
	.string "但他们做的和说的\n"
	.string "完全不一样！$"

LilycoveCity_Text_TeamAquaLotGoneForGood:
	.string "{CHN}海湾里那个洞窟……\p"
	.string "我一开始没注意，\n"
	.string "但现在里面空空如也。\p"
	.string "水舰队那帮家伙，\n"
	.string "应该是彻底走掉了。$"

LilycoveCity_Text_CitySign:
	.string "{CHN}彩幽市\p"
	.string "“陆地尽头，\n"
	.string "海洋起点。”$"

LilycoveCity_Text_ContestHallSign:
	.string "{CHN}宝可梦选拔赛会堂\n"
	.string "“训练家聚集之地！”$"

LilycoveCity_Text_MotelSign:
	.string "{CHN}百合海湾汽车旅馆\p"
	.string "“请把我们当作彩幽市的\n"
	.string "百合海湾来记住。”$"

LilycoveCity_Text_MuseumSign:
	.string "{CHN}彩幽市博物馆\p"
	.string "“展出宝可梦\n"
	.string "杰作集！”$"

LilycoveCity_Text_MuseumSignPlayersExhibit:
	.string "{CHN}彩幽市博物馆\p"
	.string "“展出{PLAYER}的\n"
	.string "宝可梦收藏！”$"

LilycoveCity_Text_HarborSignUnderConstruction:
	.string "{CHN}彩幽市港口\p"
	.string "“渡轮潮汐号正在\n"
	.string "凯那市建造中。\p"
	.string "“服务预计\n"
	.string "近期开始。”$"

LilycoveCity_Text_HarborSign:
	.string "{CHN}彩幽市港口\p"
	.string "“请尽情享受\n"
	.string "潮汐号渡轮的愉快航行。”$"

LilycoveCity_Text_TrainerFanClubSign:
	.string "{CHN}宝可梦训练家粉丝俱乐部\p"
	.string "招牌上到处都涂写着\n"
	.string "训练家的名字……$"

LilycoveCity_Text_DepartmentStoreSign:
	.string "{CHN}彩幽百货公司\p"
	.string "“满满的优质商品\n"
	.string "和兴奋！\p"
	.string "“寻找你需要的\n"
	.string "东西的好地方！”$"

LilycoveCity_Text_MoveDeletersHouseSign:
	.string "{CHN}招式遗忘师的家\p"
	.string "“删除宝可梦不需要的招式。”$"

LilycoveCity_Text_DoYouKnowAboutBerryBlender:
	.string "{CHN}你知道树果搅拌机\n"
	.string "这种机器吗？$"

LilycoveCity_Text_FasterSpinBetterPokeblocks:
	.string "{CHN}大家必须齐心协力，\n"
	.string "才能让它转得更快。\p"
	.string "听说转得越快，\n"
	.string "做出来的{POKEBLOCK}就越好。$"

LilycoveCity_Text_ExplainBerryBlender:
	.string "{CHN}它是用来制作一种叫{POKEBLOCK}的\n"
	.string "糖果的。\p"
	.string "给宝可梦吃下好的{POKEBLOCK}，\n"
	.string "它的状态就会大幅提升。$"

LilycoveCity_Text_HeardTowerCalledSkyPillar:
	.string "{CHN}我听说海路上\n"
	.string "某处有一座塔。\p"
	.string "好像是叫天空之柱。$"

LilycoveCity_Text_SawTallTowerOnRoute131:
	.string "{CHN}我在131号道路\n"
	.string "附近看到一座高塔。\p"
	.string "那会不会是……？$"

LilycoveCity_Text_JustArrivedAndSawRarePokemon:
	.string "{CHN}我们是来度蜜月\n"
	.string "刚到这里。\p"
	.string "碰巧看到一只龙属性\n"
	.string "宝可梦高高飞在天上。\p"
	.string "丰缘地区\n"
	.string "也有这么酷的宝可梦吗？$"

LilycoveCity_Text_HoneymoonVowToSeeRarePokemon:
	.string "{CHN}蜜月旅行时，我们发誓要尽可能\n"
	.string "多看一些珍稀的宝可梦。\p"
	.string "所以我们一到就看到了\n"
	.string "珍稀的宝可梦，真是太高兴了。\p"
	.string "就是说，我们超级幸福！$"
