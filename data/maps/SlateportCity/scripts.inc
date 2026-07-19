SlateportCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SlateportCity_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SlateportCity_OnFrame
	.byte 0

SlateportCity_OnTransition:
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 0
	call SlateportCity_EventScript_EnterSlateport
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_MovePeopleForSternInterview
	call_if_eq VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1, SlateportCity_EventScript_SetReadyForScottScene
	end

SlateportCity_EventScript_EnterSlateport::
	setflag FLAG_VISITED_SLATEPORT_CITY
	setvar VAR_CONTEST_HALL_STATE, 0
	setflag FLAG_HIDE_SLATEPORT_CITY_CONTEST_REPORTER
	return

SlateportCity_EventScript_MovePeopleForSternInterview::
	setobjectxyperm LOCALID_SLATEPORT_CAPT_STERN, 28, 13
	setobjectxyperm LOCALID_SLATEPORT_OLD_WOMAN, 25, 13
	setobjectxyperm LOCALID_SLATEPORT_RICH_BOY, 25, 14
	setobjectxyperm LOCALID_SLATEPORT_COOK, 27, 16
	setobjectxyperm LOCALID_SLATEPORT_GIRL, 28, 16
	setobjectxyperm LOCALID_SLATEPORT_FAT_MAN, 29, 16
	setobjectxyperm LOCALID_SLATEPORT_MAN_1, 31, 14
	setobjectmovementtype LOCALID_SLATEPORT_CAPT_STERN, MOVEMENT_TYPE_FACE_DOWN
	setobjectmovementtype LOCALID_SLATEPORT_OLD_WOMAN, MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT
	setobjectmovementtype LOCALID_SLATEPORT_RICH_BOY, MOVEMENT_TYPE_FACE_UP_AND_RIGHT
	setobjectmovementtype LOCALID_SLATEPORT_COOK, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_SLATEPORT_GIRL, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_SLATEPORT_FAT_MAN, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_SLATEPORT_MAN_1, MOVEMENT_TYPE_FACE_LEFT
	return

SlateportCity_EventScript_SetReadyForScottScene::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8004, 30, SlateportCity_EventScript_MoveScottLeft
	setobjectxyperm LOCALID_SLATEPORT_SCOTT, 23, 27
	setobjectmovementtype LOCALID_SLATEPORT_SCOTT, MOVEMENT_TYPE_FACE_RIGHT
	return

SlateportCity_EventScript_MoveScottLeft::
	setobjectxyperm LOCALID_SLATEPORT_SCOTT, 22, 27
	setobjectmovementtype LOCALID_SLATEPORT_SCOTT, MOVEMENT_TYPE_FACE_RIGHT
	return

SlateportCity_OnFrame:
	map_script_2 VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1, SlateportCity_EventScript_ScottScene
	.short 0

SlateportCity_EventScript_ScottScene::
	lockall
	addobject LOCALID_SLATEPORT_SCOTT
	applymovement LOCALID_PLAYER, SlateportCity_Movement_PlayerFaceScott
	applymovement LOCALID_SLATEPORT_SCOTT, SlateportCity_Movement_ScottApproachPlayer
	waitmovement 0
	msgbox SlateportCity_Text_YouDroveTeamAquaAway, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_SCOTT, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 60
	msgbox SlateportCity_Text_MaybeThisTrainer, MSGBOX_DEFAULT
	applymovement LOCALID_SLATEPORT_SCOTT, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox SlateportCity_Text_LetsRegisterEachOther, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox SlateportCity_Text_RegisteredScott, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_SCOTT_MATCH_CALL
	msgbox SlateportCity_Text_KeepEyeOnTrainersBeSeeingYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_SCOTT, SlateportCity_Movement_ScottExit
	waitmovement 0
	removeobject LOCALID_SLATEPORT_SCOTT
	setobjectxyperm LOCALID_SLATEPORT_SCOTT, 10, 12
	setobjectmovementtype LOCALID_SLATEPORT_SCOTT, MOVEMENT_TYPE_FACE_DOWN
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 2
	addvar VAR_SCOTT_STATE, 1
	releaseall
	end

SlateportCity_Movement_PlayerFaceScott:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

SlateportCity_Movement_ScottApproachPlayer:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_Movement_ScottExit:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SlateportCity_EventScript_EnergyGuru::
	lock
	faceplayer
	message SlateportCity_Text_EnergyGuruSellWhatYouNeed
	waitmessage
	pokemart SlateportCity_Pokemart_EnergyGuru
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_Pokemart_EnergyGuru:
	.short ITEM_PROTEIN
	.short ITEM_IRON
	.short ITEM_CARBOS
	.short ITEM_ZINC
	.short ITEM_CALCIUM
	.short ITEM_HP_UP
	pokemartlistend

SlateportCity_EventScript_EffortRibbonWoman::
	lock
	faceplayer
	bufferleadmonspeciesname STR_VAR_1
	msgbox SlateportCity_Text_OhYourPokemon, MSGBOX_DEFAULT
	specialvar VAR_RESULT, LeadMonHasEffortRibbon
	call_if_eq VAR_RESULT, TRUE, SlateportCity_EventScript_MonHasEffortRibbon
	specialvar VAR_RESULT, Special_AreLeadMonEVsMaxedOut
	call_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_MonEVsNotMaxed
	msgbox SlateportCity_Text_PleaseGiveItThisEffortRibbon, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message SlateportCity_Text_ReceivedEffortRibbon
	waitfanfare
	msgbox SlateportCity_Text_PutEffortRibbonOnMon, MSGBOX_DEFAULT
	special GiveLeadMonEffortRibbon
	release
	end

SlateportCity_EventScript_MonEVsNotMaxed::
	msgbox SlateportCity_Text_GoForItLittleHarder, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_MonHasEffortRibbon::
	msgbox SlateportCity_Text_EffortRibbonLooksGoodOnIt, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Cook::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_CookSternInterview
	msgbox SlateportCity_Text_SeaweedFullOfLife, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_CookSternInterview::
	msgbox SlateportCity_Text_CaptainComeBackWithBigFish, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_OldWoman::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_OldWomanSternInterview
	msgbox SlateportCity_Text_HowTownIsBornAndGrows, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_OldWomanSternInterview::
	msgbox SlateportCity_Text_CaptSternBeingInterviewed, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Girl::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_GirlSternInterview
	goto_if_set FLAG_RECEIVED_SECRET_POWER, SlateportCity_EventScript_GirlSecretBase
	msgbox SlateportCity_Text_SlateportWonderfulPlace, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_GirlSternInterview::
	msgbox SlateportCity_Text_InterviewerSoCool, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_GirlSecretBase::
	msgbox SlateportCity_Text_BuyBricksSoDecorWontGetDirty, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_RichBoy::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_RichBoySternInterview
	msgbox SlateportCity_Text_GoingToCompeteInBattleTent, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_RichBoySternInterview::
	msgbox SlateportCity_Text_SternSaysDiscoveredSomething, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_FatMan::
	goto_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_FatManSternInterview
	msgbox SlateportCity_Text_BushedHikingFromMauville, MSGBOX_NPC
	end

SlateportCity_EventScript_FatManSternInterview::
	msgbox SlateportCity_Text_AmIOnTV, MSGBOX_SIGN
	end

SlateportCity_EventScript_Man1::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_Man1SternInterview
	msgbox SlateportCity_Text_EveryoneCallsHimCaptStern, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Man1SternInterview::
	msgbox SlateportCity_Text_CaptainsACelebrity, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Woman1::
	lock
	faceplayer
	goto_if_set FLAG_DOCK_REJECTED_DEVON_GOODS, SlateportCity_EventScript_Woman1AquaGone
	msgbox SlateportCity_Text_WhatsLongLineOverThere, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Woman1AquaGone::
	msgbox SlateportCity_Text_VisitedMuseumOften, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_BattleTentSign::
	msgbox SlateportCity_Text_BattleTentSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_SternsShipyardSign::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_EventScript_SternsShipyardFerryComplete
	goto_if_set FLAG_BADGE07_GET, SlateportCity_EventScript_SternsShipyardNearsCompletion
	msgbox SlateportCity_Text_SternsShipyardWantedSign, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_SternsShipyardNearsCompletion::
	msgbox SlateportCity_Text_SternsShipyardNearsCompletion, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_SternsShipyardFerryComplete::
	msgbox SlateportCity_Text_SternsShipyardFerryComplete, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_PokemonFanClubSign::
	msgbox SlateportCity_Text_PokemonFanClubSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_OceanicMuseumSign::
	msgbox SlateportCity_Text_OceanicMuseumSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_CitySign::
	msgbox SlateportCity_Text_CitySign, MSGBOX_SIGN
	end

SlateportCity_EventScript_MarketSign::
	msgbox SlateportCity_Text_MarketSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_HarborSign::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_EventScript_HarborSignFerryComplete
	msgbox SlateportCity_Text_HarborFerryUnderConstruction, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_HarborSignFerryComplete::
	msgbox SlateportCity_Text_HarborSign, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_NameRatersHouseSign::
	msgbox SlateportCity_Text_NameRatersHouseSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_Maniac::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_ManiacSternInterview
	msgbox SlateportCity_Text_GetNameRaterToHelpYou, MSGBOX_DEFAULT
	release
	end

/* Unclear if the text here was meant to be different, but its not*/
SlateportCity_EventScript_ManiacSternInterview::
	msgbox SlateportCity_Text_GetNameRaterToHelpYou, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Woman2::
	msgbox SlateportCity_Text_CantChangeTradeMonName, MSGBOX_NPC
	end

SlateportCity_EventScript_Sailor1::
	msgbox SlateportCity_Text_SeaIsSoWet, MSGBOX_NPC
	end

SlateportCity_EventScript_Sailor2::
	msgbox SlateportCity_Text_SinkOldBoats, MSGBOX_NPC
	end

SlateportCity_EventScript_PokefanF::
	msgbox SlateportCity_Text_BuyTooMuch, MSGBOX_NPC
	end

SlateportCity_EventScript_Man2::
	msgbox SlateportCity_Text_BattleTentBuiltRecently, MSGBOX_NPC
	end

SlateportCity_EventScript_AquaGrunt1::
	lock
	faceplayer
	msgbox SlateportCity_Text_QuitPushing, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt2::
	lock
	faceplayer
	msgbox SlateportCity_Text_AquaHasPolicy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt3::
	lock
	faceplayer
	msgbox SlateportCity_Text_BossIsBrilliant, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt4::
	lock
	faceplayer
	msgbox SlateportCity_Text_WhatsNewSchemeIWonder, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt5::
	lock
	faceplayer
	msgbox SlateportCity_Text_ShouldTakeItAll, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_5, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt6::
	lock
	faceplayer
	msgbox SlateportCity_Text_DontButtIn, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_6, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt7::
	lock
	faceplayer
	msgbox SlateportCity_Text_RemindsMeOfLongLineForGames, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_7, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt8::
	lock
	faceplayer
	msgbox SlateportCity_Text_WhyAreWeLiningUp, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_8, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt9::
	lock
	faceplayer
	playse SE_PIN
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_Delay48
	waitmovement 0
	msgbox SlateportCity_Text_WhatDoYouWant, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_FaceOriginalDirection
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, SlateportCity_Movement_DelayAquaGrunt
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_Text_IllReadSignForYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_FaceOriginalDirection
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, SlateportCity_Movement_DelayAquaGrunt
	waitmovement 0
	msgbox SlateportCity_Text_SaysSomethingLikeSeaIsEndless, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, SlateportCity_Movement_DelayAquaGrunt
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_Movement_DelayAquaGrunt:
	delay_16
	delay_16
	step_end

SlateportCity_EventScript_AquaGrunt10::
	msgbox SlateportCity_Text_ShouldveBroughtMyGameBoy, MSGBOX_SIGN
	end

SlateportCity_EventScript_AquaGrunt11::
	lock
	faceplayer
	msgbox SlateportCity_Text_HotSpringsAfterOperation, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_11, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_DollClerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration SlateportCity_PokemartDecor_Dolls
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_PokemartDecor_Dolls:
	.short DECOR_AZURILL_DOLL
	.short DECOR_MARILL_DOLL
	.short DECOR_SKITTY_DOLL
	pokemartlistend

SlateportCity_EventScript_ComeBackWithSecretPower::
	msgbox gText_ComeBackWithSecretPower, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_DecorClerk::
	lock
	faceplayer
	goto_if_unset FLAG_RECEIVED_SECRET_POWER, SlateportCity_EventScript_ComeBackWithSecretPower
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration SlateportCity_PokemartDecor
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_PokemartDecor:
	.short DECOR_RED_BRICK
	.short DECOR_BLUE_BRICK
	.short DECOR_YELLOW_BRICK
	.short DECOR_RED_BALLOON
	.short DECOR_BLUE_BALLOON
	.short DECOR_YELLOW_BALLOON
	.short DECOR_C_LOW_NOTE_MAT
	.short DECOR_D_NOTE_MAT
	.short DECOR_E_NOTE_MAT
	.short DECOR_F_NOTE_MAT
	.short DECOR_G_NOTE_MAT
	.short DECOR_A_NOTE_MAT
	.short DECOR_B_NOTE_MAT
	.short DECOR_C_HIGH_NOTE_MAT
	pokemartlistend

SlateportCity_EventScript_PowerTMClerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart SlateportCity_Pokemart_PowerTMs
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_Pokemart_PowerTMs:
	.short ITEM_TM_HIDDEN_POWER
	.short ITEM_TM_SECRET_POWER
	pokemartlistend

/* Scene with Capt Sterns interview and Team Aqua announcing plans to steal Submarine*/
SlateportCity_EventScript_CaptStern::
	lockall
	msgbox SlateportCity_Text_SternMoveAheadWithExploration, MSGBOX_DEFAULT
	msgbox SlateportCity_Text_GabbyWonderfulThanksForInterview, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GABBY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 10
	applymovement LOCALID_SLATEPORT_TY, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 25
	applymovement LOCALID_SLATEPORT_CAPT_STERN, SlateportCity_Movement_SternWatchGabbyAndTyExit
	applymovement LOCALID_PLAYER, SlateportCity_Movement_PlayerFaceStern
	applymovement LOCALID_SLATEPORT_GABBY, SlateportCity_Movement_GabbyExit
	applymovement LOCALID_SLATEPORT_TY, SlateportCity_Movement_TyExit
	waitmovement 0
	removeobject LOCALID_SLATEPORT_GABBY
	removeobject LOCALID_SLATEPORT_TY
	msgbox SlateportCity_Text_SternWhewFirstInterview, MSGBOX_DEFAULT
	applymovement LOCALID_SLATEPORT_CAPT_STERN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SlateportCity_Text_OhPlayerWeMadeDiscovery, MSGBOX_DEFAULT
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	msgbox SlateportCity_Text_AquaWillAssumeControlOfSubmarine, MSGBOX_DEFAULT
	applymovement LOCALID_SLATEPORT_COOK, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_SLATEPORT_FAT_MAN, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_SLATEPORT_OLD_WOMAN, SlateportCity_Movement_OldWomanConcern
	applymovement LOCALID_SLATEPORT_RICH_BOY, Common_Movement_QuestionMark
	applymovement LOCALID_SLATEPORT_MAN_1, SlateportCity_Movement_ManConcern
	waitmovement 0
	applymovement LOCALID_SLATEPORT_CAPT_STERN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox SlateportCity_Text_SternWhatWasAllThat, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement LOCALID_SLATEPORT_CAPT_STERN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_SLATEPORT_CAPT_STERN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_SLATEPORT_CAPT_STERN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SlateportCity_Text_FromHarborTryingToTakeSub, MSGBOX_DEFAULT
	msgbox SlateportCity_Text_PleaseComeWithMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_CAPT_STERN, SlateportCity_Movement_SternEnterHarbor
	applymovement LOCALID_PLAYER, SlateportCity_Movement_PlayerEnterHarbor
	waitmovement 0
	removeobject LOCALID_SLATEPORT_CAPT_STERN
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_CAPTAIN_STERN
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_SUBMARINE_SHADOW
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_AQUA_GRUNT
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_ARCHIE
	setvar VAR_SLATEPORT_CITY_STATE, 2
	warp MAP_SLATEPORT_CITY_HARBOR, 11, 14
	waitstate
	releaseall
	end

SlateportCity_Movement_OldWomanConcern:
	delay_16
	delay_16
	emote_question_mark
	walk_in_place_faster_right
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

SlateportCity_Movement_ManConcern:
	emote_question_mark
	walk_in_place_faster_up
	delay_16
	walk_in_place_faster_down
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

SlateportCity_Movement_GabbyExit:
	delay_16
	walk_left
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SlateportCity_Movement_TyExit:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SlateportCity_Movement_Unused:
	walk_down
	walk_in_place_faster_up
	step_end

SlateportCity_Movement_SternEnterHarbor:
	walk_right
	walk_up
	walk_up
	set_invisible
	step_end

SlateportCity_Movement_SternWatchGabbyAndTyExit:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_down
	walk_left
	step_end

SlateportCity_Movement_PlayerEnterHarbor:
	walk_in_place_faster_right
	delay_16
	delay_16
	walk_right
	walk_up
	step_end

SlateportCity_Movement_PlayerFaceStern:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_down
	step_end

SlateportCity_EventScript_Ty::
	msgbox SlateportCity_Text_BigSmileForCamera, MSGBOX_SIGN
	end

SlateportCity_EventScript_Gabby::
	msgbox SlateportCity_Text_MostInvaluableExperience, MSGBOX_SIGN
	end

SlateportCity_EventScript_Man3::
	msgbox SlateportCity_Text_WonderIfLighthouseStartlesPokemon, MSGBOX_NPC
	end

SlateportCity_EventScript_BerryPowderClerk::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_POWDER_JAR, SlateportCity_EventScript_ReceivedPowderJar
	msgbox SlateportCity_Text_ExplainBerries, MSGBOX_DEFAULT
	giveitem ITEM_POWDER_JAR
	setflag FLAG_RECEIVED_POWDER_JAR
	msgbox SlateportCity_Text_ExplainBerryPowder, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_ReceivedPowderJar::
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, HasEnoughBerryPowder
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_ExplainBerryPowder
	msgbox SlateportCity_Text_BroughtMeSomeBerryPowder, MSGBOX_DEFAULT
	special DisplayBerryPowderVendorMenu
	goto SlateportCity_EventScript_ChooseBerryPowderItem
	end

SlateportCity_EventScript_ExplainBerryPowder::
	msgbox SlateportCity_Text_ExplainBerryPowder, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_ChooseBerryPowderItem::
	message SlateportCity_Text_ExchangeWhatWithIt
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_BERRY_POWDER_VENDOR
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, SlateportCity_EventScript_EnergyPowder
	case 1, SlateportCity_EventScript_EnergyRoot
	case 2, SlateportCity_EventScript_HealPowder
	case 3, SlateportCity_EventScript_RevivalHerb
	case 4, SlateportCity_EventScript_Protein
	case 5, SlateportCity_EventScript_Iron
	case 6, SlateportCity_EventScript_Carbos
	case 7, SlateportCity_EventScript_Calcium
	case 8, SlateportCity_EventScript_Zinc
	case 9, SlateportCity_EventScript_HPUp
	case 10, SlateportCity_EventScript_PPUp
	case 11, SlateportCity_EventScript_CancelPowderItemSelect
	case MULTI_B_PRESSED, SlateportCity_EventScript_CancelPowderItemSelect
	end

SlateportCity_EventScript_EnergyPowder::
	bufferitemname STR_VAR_1, ITEM_ENERGY_POWDER
	setvar VAR_0x8008, ITEM_ENERGY_POWDER
	setvar VAR_0x8009, 50
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_EnergyRoot::
	bufferitemname STR_VAR_1, ITEM_ENERGY_ROOT
	setvar VAR_0x8008, ITEM_ENERGY_ROOT
	setvar VAR_0x8009, 80
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_HealPowder::
	bufferitemname STR_VAR_1, ITEM_HEAL_POWDER
	setvar VAR_0x8008, ITEM_HEAL_POWDER
	setvar VAR_0x8009, 50
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_RevivalHerb::
	bufferitemname STR_VAR_1, ITEM_REVIVAL_HERB
	setvar VAR_0x8008, ITEM_REVIVAL_HERB
	setvar VAR_0x8009, 300
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Protein::
	bufferitemname STR_VAR_1, ITEM_PROTEIN
	setvar VAR_0x8008, ITEM_PROTEIN
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Iron::
	bufferitemname STR_VAR_1, ITEM_IRON
	setvar VAR_0x8008, ITEM_IRON
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Carbos::
	bufferitemname STR_VAR_1, ITEM_CARBOS
	setvar VAR_0x8008, ITEM_CARBOS
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Calcium::
	bufferitemname STR_VAR_1, ITEM_CALCIUM
	setvar VAR_0x8008, ITEM_CALCIUM
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Zinc::
	bufferitemname STR_VAR_1, ITEM_ZINC
	setvar VAR_0x8008, ITEM_ZINC
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_HPUp::
	bufferitemname STR_VAR_1, ITEM_HP_UP
	setvar VAR_0x8008, ITEM_HP_UP
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_PPUp::
	bufferitemname STR_VAR_1, ITEM_PP_UP
	setvar VAR_0x8008, ITEM_PP_UP
	setvar VAR_0x8009, 3000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_CancelPowderItemSelect::
	msgbox SlateportCity_Text_ComeBackToTradeBerryPowder, MSGBOX_DEFAULT
	special RemoveBerryPowderVendorMenu
	release
	end

SlateportCity_EventScript_TryBuyBerryPowderItem::
	msgbox SlateportCity_Text_ExchangeBerryPowderForItem, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SlateportCity_EventScript_ChooseBerryPowderItem
	copyvar VAR_0x8004, VAR_0x8009
	specialvar VAR_RESULT, HasEnoughBerryPowder
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_NotEnoughBerryPowder
	giveitem VAR_0x8008
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_NoRoomForBerryPowderItem
	copyvar VAR_0x8004, VAR_0x8009
	special TakeBerryPowder
	special PrintPlayerBerryPowderAmount
	msgbox SlateportCity_Text_FineBerryPowderTradeSomethingElse, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_EventScript_ChooseBerryPowderItem
	msgbox SlateportCity_Text_WhenYouGetMoreBringItToMe, MSGBOX_DEFAULT
	special RemoveBerryPowderVendorMenu
	release
	end

SlateportCity_EventScript_NoRoomForBerryPowderItem::
	msgbox gText_TheBagIsFull, MSGBOX_DEFAULT
	special RemoveBerryPowderVendorMenu
	release
	end

SlateportCity_EventScript_NotEnoughBerryPowder::
	msgbox SlateportCity_Text_DontHaveEnoughBerryPowder, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_ChooseBerryPowderItem
	end

SlateportCity_EventScript_ScottBattleTentScene::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	opendoor 10, 12
	waitdooranim
	addobject LOCALID_SLATEPORT_SCOTT
	applymovement LOCALID_PLAYER, SlateportCity_Movement_PushPlayerDown
	applymovement LOCALID_SLATEPORT_SCOTT, SlateportCity_Movement_ScottExitBattleTent
	waitmovement 0
	closedoor 10, 12
	waitdooranim
	msgbox SlateportCity_Text_TakingBattleTentChallenge, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, SlateportCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_SLATEPORT_SCOTT, SlateportCity_Movement_ScottExitAfterBattleTent
	waitmovement 0
	removeobject LOCALID_SLATEPORT_SCOTT
	addvar VAR_SCOTT_STATE, 1
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 3
	releaseall
	end

SlateportCity_Movement_PushPlayerDown:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

SlateportCity_Movement_PlayerWatchScottExit:
	delay_16
	walk_in_place_faster_right
	step_end

SlateportCity_Movement_ScottExitBattleTent:
	delay_8
	walk_down
	step_end

SlateportCity_Movement_ScottExitAfterBattleTent:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_EventScript_BerryCrushRankingsSign::
	lockall
	special ShowBerryCrushRankings
	waitstate
	releaseall
	end

SlateportCity_Text_EnergyGuruSellWhatYouNeed:
	.string "{CHN}我是能量大师！我会努力\n"
	.string "卖给你你需要的东西！$"

SlateportCity_Text_OhYourPokemon:
	.string "{CHN}哦？\n"
	.string "你的{STR_VAR_1}…$"

SlateportCity_Text_PleaseGiveItThisEffortRibbon:
	.string "{CHN}非常努力地拼搏了！\p"
	.string "作为奖励，请给它这个\n"
	.string "努力奖章吧。$"

SlateportCity_Text_ReceivedEffortRibbon:
	.string "{CHN}{PLAYER}获得了努力奖章。$"

SlateportCity_Text_PutEffortRibbonOnMon:
	.string "{CHN}{PLAYER}把努力奖章\n"
	.string "戴在了{STR_VAR_1}身上。$"

SlateportCity_Text_GoForItLittleHarder:
	.string "{CHN}你还得再努力一点才行。\p"
	.string "如果你做到了，我就给你的宝可梦\n"
	.string "一些好东西。$"

SlateportCity_Text_EffortRibbonLooksGoodOnIt:
	.string "{CHN}哦！你的{STR_VAR_1}，那个努力\n"
	.string "奖章戴在它身上真好看！$"

SlateportCity_Text_WonderIfLighthouseStartlesPokemon:
	.string "{CHN}灯塔的光芒能照射到\n"
	.string "数十英里之外。\p"
	.string "我在想，这会不会惊吓到\n"
	.string "海里的宝可梦呢。$"

SlateportCity_Text_SeaweedFullOfLife:
	.string "{CHN}哦，看看这个！\p"
	.string "这一带能采到的海藻\n"
	.string "新鲜又充满生机。\p"
	.string "哎呀，看起来它甚至能\n"
	.string "站起来攻击呢！$"

SlateportCity_Text_HowTownIsBornAndGrows:
	.string "{CHN}水质清澈的地方，\n"
	.string "会有丰收的果实聚集。\p"
	.string "人们聚集的地方，\n"
	.string "很快就会出现市场。\p"
	.string "城镇就是这样诞生并发展起来的。$"

SlateportCity_Text_SlateportWonderfulPlace:
	.string "{CHN}一边购物一边呼吸\n"
	.string "海洋的气息…\p"
	.string "凯那市真是个好地方！$"

SlateportCity_Text_BuyBricksSoDecorWontGetDirty:
	.string "{CHN}如果把玩偶或坐垫放在\n"
	.string "地板上，它们会变脏。\p"
	.string "我要去买一些砖块，这样我的\n"
	.string "玩偶和坐垫放在外面\l"
	.string "就不会弄脏了。$"

SlateportCity_Text_GoingToCompeteInBattleTent:
	.string "{CHN}吼哦哦！我也要去\n"
	.string "对战帐篷挑战！\p"
	.string "不过在那之前，我得先\n"
	.string "抓一些宝可梦！$"

SlateportCity_Text_BushedHikingFromMauville:
	.string "{CHN}呼…我累坏了…\p"
	.string "我从紫堇市一路走来。\n"
	.string "不过，这座城市真大。\p"
	.string "早知道的话，我就骑\n"
	.string "自行车来了。$"

SlateportCity_Text_EveryoneCallsHimCaptStern:
	.string "{CHN}建造了这座博物馆的帅哥，\n"
	.string "同时也是一个海底探险队\l"
	.string "的队长。\p"
	.string "所以，大家都叫他帅哥船长。$"

SlateportCity_Text_WhatsLongLineOverThere:
	.string "{CHN}那边是什么？\n"
	.string "那么长的队伍…$"

SlateportCity_Text_VisitedMuseumOften:
	.string "{CHN}小时候，我经常\n"
	.string "来博物馆参观。\p"
	.string "看完展览后，我总会梦到\n"
	.string "大海的奥秘。$"

SlateportCity_Text_QuitPushing:
	.string "{CHN}喂，你！别推了！\n"
	.string "这里是排队的地方，你看不见吗？$"

SlateportCity_Text_AquaHasPolicy:
	.string "{CHN}水舰队的方针是\n"
	.string "在作战现场集合\l"
	.string "然后解散。$"

SlateportCity_Text_BossIsBrilliant:
	.string "{CHN}我们的首领很英明。\p"
	.string "他现在想对博物馆\n"
	.string "做什么呢？$"

SlateportCity_Text_WhatsNewSchemeIWonder:
	.string "{CHN}新计划是什么呢？\p"
	.string "我们首领生气的时候很可怕，\n"
	.string "所以我最好别搞砸了…$"

SlateportCity_Text_ShouldTakeItAll:
	.string "{CHN}如果博物馆里有\n"
	.string "我们需要的东西，就应该全部拿走！$"

SlateportCity_Text_DontButtIn:
	.string "{CHN}喂，你！\n"
	.string "别插手！$"

SlateportCity_Text_RemindsMeOfLongLineForGames:
	.string "{CHN}很长的队伍啊？\p"
	.string "这让我想起以前排队买\n"
	.string "热销游戏的日子…$"

SlateportCity_Text_WhyAreWeLiningUp:
	.string "{CHN}我们为什么要排队付钱？\n"
	.string "直接冲进去不就好了！$"

SlateportCity_Text_WhatDoYouWant:
	.string "{CHN}什么？\n"
	.string "你想干什么？$"

SlateportCity_Text_IllReadSignForYou:
	.string "{CHN}你想看这块牌子？\n"
	.string "我念给你听！$"

SlateportCity_Text_SaysSomethingLikeSeaIsEndless:
	.string "{CHN}让我看看…\p"
	.string "嗯…我想它说的是\n"
	.string "“海中的生命是无尽的。”\p"
	.string "没错，我确定上面就是这么\n"
	.string "写的。$"

SlateportCity_Text_ShouldveBroughtMyGameBoy:
	.string "{CHN}咕哝…\p"
	.string "我应该带上Game Boy\n"
	.string "Advance的，这样排队就不会无聊了…\p"
	.string "咕哝…$"

SlateportCity_Text_HotSpringsAfterOperation:
	.string "{CHN}这次行动结束后，我会带\n"
	.string "你去泡温泉！\p"
	.string "这是我们首领说的。\n"
	.string "我等不及了！$"

SlateportCity_Text_SeaIsSoWet:
	.string "{CHN}大海真是太广阔了…\p"
	.string "大海会不会是宝可梦\n"
	.string "流下的眼泪汇聚而成的呢？$"

SlateportCity_Text_SinkOldBoats:
	.string "{CHN}你知道那些老朽得\n"
	.string "无法航行的旧船会怎么处理吗？\p"
	.string "他们会把船沉入海中，\n"
	.string "让它们成为宝可梦的栖息地。$"

SlateportCity_Text_BuyTooMuch:
	.string "{CHN}每次来这里，我都会\n"
	.string "买太多东西。$"

SlateportCity_Text_GetNameRaterToHelpYou:
	.string "{CHN}如果你想更改宝可梦的\n"
	.string "昵称，就得请命名评委\l"
	.string "帮忙。$"

SlateportCity_Text_CantChangeTradeMonName:
	.string "{CHN}通过交换得到的宝可梦，\n"
	.string "你无法更改它的昵称。\p"
	.string "原训练家对那只\n"
	.string "宝可梦的爱就寄托在昵称里。$"

SlateportCity_Text_BattleTentBuiltRecently:
	.string "{CHN}最近，凯那市\n"
	.string "建了一座对战帐篷。\p"
	.string "道馆很有趣，但对战帐篷\n"
	.string "也有它独特的魅力。\p"
	.string "你应该去找一些强力的宝可梦\n"
	.string "来挑战对战帐篷！$"

SlateportCity_Text_CaptSternBeingInterviewed:
	.string "{CHN}我本来希望是哪位\n"
	.string "明星能让我要到签名。\p"
	.string "但那个接受采访的是谁？\n"
	.string "那不是帅哥船长吗？$"

SlateportCity_Text_InterviewerSoCool:
	.string "{CHN}那位女记者好酷\n"
	.string "好漂亮。\p"
	.string "我长大后也要当一名\n"
	.string "国际记者！$"

SlateportCity_Text_SternSaysDiscoveredSomething:
	.string "{CHN}帅哥船长说他们在\n"
	.string "海底发现了什么东西。\p"
	.string "那会是什么呢？\n"
	.string "到底是什么呢？$"

SlateportCity_Text_CaptainComeBackWithBigFish:
	.string "{CHN}这里发生什么事了？\p"
	.string "那位船长是不是从\n"
	.string "海底带回了一条大鱼？$"

SlateportCity_Text_AmIOnTV:
	.string "{CHN}喂！你在看吗？\n"
	.string "我上电视了吗？$"

SlateportCity_Text_CaptainsACelebrity:
	.string "{CHN}电视采访！就在这里！\n"
	.string "船长可是个名人！$"

SlateportCity_Text_BigSmileForCamera:
	.string "{CHN}泰：好的，帅哥船长，对着\n"
	.string "镜头笑一个！$"

SlateportCity_Text_MostInvaluableExperience:
	.string "{CHN}嘉比：我明白了，明白了。您有着\n"
	.string "非常宝贵的经历…$"

SlateportCity_Text_SternMoveAheadWithExploration:
	.string "{CHN}帅哥船长：是的，没错。我们打算\n"
	.string "继续推进我们的探险。$"

SlateportCity_Text_GabbyWonderfulThanksForInterview:
	.string "{CHN}嘉比：太棒了，帅哥船长！\n"
	.string "感谢您在百忙之中\l"
	.string "抽出时间接受我们的采访。\p"
	.string "希望下次有更多发现时\n"
	.string "还能再采访您！$"

SlateportCity_Text_SternWhewFirstInterview:
	.string "{CHN}帅哥船长：呼…\p"
	.string "这是我第一次上电视\n"
	.string "接受采访。真是让人紧张啊。$"

SlateportCity_Text_OhPlayerWeMadeDiscovery:
	.string "{CHN}哦！{PLAYER}{KUN}！\n"
	.string "你看起来精神不错！\p"
	.string "我们在上次的海底探险中\n"
	.string "有了重大发现。\p"
	.string "我们在128号水路发现了\n"
	.string "一个海底洞窟。\p"
	.string "我们认为那里可能栖息着\n"
	.string "一种据说早已灭绝的宝可梦。$"

SlateportCity_Text_AquaWillAssumeControlOfSubmarine:
	.string "{CHN}呼呼呼…\n"
	.string "帅哥船长，对吧。\p"
	.string "我们水舰队将接管\n"
	.string "你的潜水艇！\p"
	.string "你们的反对是毫无意义的！\n"
	.string "我们期待你们的全力配合！\p"
	.string "呼呼呼…\n"
	.string "好好看着水舰队\n"
	.string "接下来要做什么吧！$"

SlateportCity_Text_SternWhatWasAllThat:
	.string "{CHN}帅哥船长：那是怎么回事？\p"
	.string "听起来像是有人在用\n"
	.string "扩音器说话…\p"
	.string "是从哪里传来的？$"

SlateportCity_Text_FromHarborTryingToTakeSub:
	.string "{CHN}是从港口传来的！\p"
	.string "潜水艇！\n"
	.string "他们想把潜水艇抢走！$"

SlateportCity_Text_PleaseComeWithMe:
	.string "{CHN}{PLAYER}{KUN}！\n"
	.string "请跟我来！$"

SlateportCity_Text_BattleTentSign:
	.string "{CHN}对战帐篷 凯那市会场\n"
	.string "“寻找吧！最强的宝可梦！”$"

SlateportCity_Text_SternsShipyardWantedSign:
	.string "{CHN}帅哥造船厂\p"
	.string "“招募：能够在任何\n"
	.string "海流中航行的水手。”$"

SlateportCity_Text_SternsShipyardNearsCompletion:
	.string "{CHN}帅哥造船厂\p"
	.string "“穿梭于凯那市与\n"
	.string "琉璃市之间的\n"
	.string "游轮海啸号即将完工。”$"

SlateportCity_Text_SternsShipyardFerryComplete:
	.string "{CHN}帅哥造船厂\p"
	.string "“凯那市-琉璃市游轮\n"
	.string "海啸号的乘船手续\l"
	.string "在港口办理。”$"

SlateportCity_Text_PokemonFanClubSign:
	.string "{CHN}宝可梦俱乐部\n"
	.string "“召集所有宝可梦爱好者！”$"

SlateportCity_Text_OceanicMuseumSign:
	.string "{CHN}“无尽的大海\n"
	.string "孕育着所有生命。”\p"
	.string "海洋博物馆$"

SlateportCity_Text_CitySign:
	.string "{CHN}凯那市\p"
	.string "“人与宝可梦\n"
	.string "交汇的港口。”$"

SlateportCity_Text_MarketSign:
	.string "{CHN}凯那市场\n"
	.string "“别处找不到的独特商品！”$"

SlateportCity_Text_HarborFerryUnderConstruction:
	.string "{CHN}凯那市港口\p"
	.string "“游轮海啸号正在\n"
	.string "造船厂建造中。\p"
	.string "“服务即将\n"
	.string "开始。”$"

SlateportCity_Text_HarborSign:
	.string "{CHN}凯那市港口\p"
	.string "“请在海啸号上\n"
	.string "享受愉快的航程。”$"

SlateportCity_Text_NameRatersHouseSign:
	.string "{CHN}命名评委的家\n"
	.string "“评估宝可梦的昵称。”$"

SlateportCity_Text_ExplainBerries:
	.string "{CHN}野生的宝可梦受伤后，\n"
	.string "会通过嚼树果来治愈自己。\p"
	.string "你知道吗？\p"
	.string "有人看到了这一点，\n"
	.string "就想到用树果来制作药物。\p"
	.string "你知道吗？\p"
	.string "要把树果变成药物，\n"
	.string "必须先把它磨成粉末。\p"
	.string "你知道吗？\p"
	.string "你似乎对树果\n"
	.string "很感兴趣！\p"
	.string "我有一样好东西要送给\n"
	.string "像你这样的人。$"

SlateportCity_Text_ExplainBerryPowder:
	.string "{CHN}我最近在宝可梦中心\n"
	.string "安装了磨碎树果的机器。\p"
	.string "树果粉碎机在\n"
	.string "楼上的联络角落。\p"
	.string "你知道吗？\p"
	.string "你能用那些机器帮我\n"
	.string "制作树果粉末吗？\p"
	.string "如果你能带很多树果粉末来，\n"
	.string "我就能为你制作各种药物。$"

SlateportCity_Text_BroughtMeSomeBerryPowder:
	.string "{CHN}你带树果粉末\n"
	.string "来了吗？$"

SlateportCity_Text_ExchangeWhatWithIt:
	.string "{CHN}你想用它\n"
	.string "换什么呢？$"

SlateportCity_Text_ExchangeBerryPowderForItem:
	.string "{CHN}好的，你想用树果粉末\n"
	.string "换一个{STR_VAR_1}吗？$"

SlateportCity_Text_DontHaveEnoughBerryPowder:
	.string "{CHN}哎呀。你的树果粉末\n"
	.string "不够呢。$"

SlateportCity_Text_FineBerryPowderTradeSomethingElse:
	.string "{CHN}这是上等的树果粉末。\n"
	.string "能做出很好的药物。\p"
	.string "你想再用树果粉末\n"
	.string "换别的东西吗？$"

SlateportCity_Text_WhenYouGetMoreBringItToMe:
	.string "{CHN}好的！等你收集到更多\n"
	.string "树果粉末后，请再带来给我！$"

SlateportCity_Text_ComeBackToTradeBerryPowder:
	.string "{CHN}如果想用树果粉末换药物，\n"
	.string "请再来找我。\p"
	.string "我这里总是开着集市。\p"
	.string "你知道吗？$"

SlateportCity_Text_YouDroveTeamAquaAway:
	.string "{CHN}斯科特：嗯？\n"
	.string "我肯定在哪里见过你。\p"
	.string "我向你自我介绍过了吗？\n"
	.string "如果没有的话，我叫斯科特。\p"
	.string "我刚才看到水舰队从这里\n"
	.string "像被蛰了一样逃走了。\p"
	.string "让我猜猜——是你把他们赶走的？$"

SlateportCity_Text_MaybeThisTrainer:
	.string "{CHN}斯科特：嗯…\n"
	.string "也许，只是也许，这位训练家…$"

SlateportCity_Text_LetsRegisterEachOther:
	.string "{CHN}斯科特：好的！我觉得你会\n"
	.string "成为一个好朋友。\p"
	.string "那么，让我们在宝可梦导航器里\n"
	.string "互相登录吧。\p"
	.string "… … … … … …$"

SlateportCity_Text_RegisteredScott:
	.string "{CHN}已将斯科特这个人\n"
	.string "登录到宝可梦导航器中。$"

SlateportCity_Text_KeepEyeOnTrainersBeSeeingYou:
	.string "{CHN}斯科特：我很想跟着你\n"
	.string "一起走，但我也想\l"
	.string "关注其他人的才能。\p"
	.string "所以，我还要去其他\n"
	.string "城镇多转转。\p"
	.string "再见，{PLAYER}{KUN}！$"

SlateportCity_Text_TakingBattleTentChallenge:
	.string "{CHN}斯科特：哦，嘿！\n"
	.string "这不是{PLAYER}{KUN}吗！\p"
	.string "{PLAYER}{KUN}，让我猜猜——你是要\n"
	.string "去挑战对战帐篷吧？\p"
	.string "对！这个想法不错！\n"
	.string "这真是个好主意！\p"
	.string "毕竟，强大的训练家\n"
	.string "最适合对战帐篷了！\p"
	.string "加油哦！$"
