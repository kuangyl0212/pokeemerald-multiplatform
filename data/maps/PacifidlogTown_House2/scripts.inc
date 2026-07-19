PacifidlogTown_House2_MapScripts::
	.byte 0

PacifidlogTown_House2_EventScript_FanClubYoungerBrother::
	lock
	faceplayer
	dotimebasedevents
	call PacifidlogTown_House2_EventScript_UpdateFanClubTMFlag
	goto_if_set FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK, PacifidlogTown_House2_EventScript_ComeBackInXDays
	call_if_set FLAG_MET_FANCLUB_YOUNGER_BROTHER, PacifidlogTown_House2_EventScript_MonAssessment
	call_if_unset FLAG_MET_FANCLUB_YOUNGER_BROTHER, PacifidlogTown_House2_EventScript_FirstMonAssessment
	setflag FLAG_MET_FANCLUB_YOUNGER_BROTHER
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	goto_if_ge VAR_RESULT, FRIENDSHIP_150_TO_199, PacifidlogTown_House2_EventScript_GiveReturn
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	goto_if_ge VAR_RESULT, FRIENDSHIP_50_TO_99, PacifidlogTown_House2_EventScript_PutInEffort
	goto PacifidlogTown_House2_EventScript_GiveFrustration
	end

PacifidlogTown_House2_EventScript_UpdateFanClubTMFlag::
	goto_if_unset FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK, Common_EventScript_NopReturn
	specialvar VAR_RESULT, GetDaysUntilPacifidlogTMAvailable
	call_if_eq VAR_RESULT, 0, PacifidlogTown_House2_EventScript_ClearReceivedFanClubTM
	return

PacifidlogTown_House2_EventScript_MonAssessment::
	msgbox PacifidlogTown_House2_Text_AhYourPokemon, MSGBOX_DEFAULT
	return

PacifidlogTown_House2_EventScript_FirstMonAssessment::
	msgbox PacifidlogTown_House2_Text_ChairmansYoungerBrotherOnVacation, MSGBOX_DEFAULT
	msgbox PacifidlogTown_House2_Text_AhYourPokemon, MSGBOX_DEFAULT
	return

PacifidlogTown_House2_EventScript_ClearReceivedFanClubTM::
	clearflag FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK
	return

PacifidlogTown_House2_EventScript_GiveReturn::
	msgbox PacifidlogTown_House2_Text_AdoringPokemonTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_RETURN
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK
	special SetPacifidlogTMReceivedDay
	msgbox PacifidlogTown_House2_Text_ExplainReturnFrustration, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_PutInEffort::
	msgbox PacifidlogTown_House2_Text_PutInSomeMoreEffort, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_GiveFrustration::
	msgbox PacifidlogTown_House2_Text_ViciousPokemonTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_FRUSTRATION
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK
	special SetPacifidlogTMReceivedDay
	msgbox PacifidlogTown_House2_Text_ExplainReturnFrustration, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_ComeBackInXDays::
	specialvar VAR_RESULT, GetDaysUntilPacifidlogTMAvailable
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox PacifidlogTown_House2_Text_GetGoodTMInXDays, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_HappyAzurill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, CRY_MODE_NORMAL
	msgbox PacifidlogTown_House2_Text_Rurii, MSGBOX_DEFAULT
	waitmoncry
	msgbox PacifidlogTown_House2_Text_VeryFriendlyWithTrainer, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_UnhappyAzurill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, CRY_MODE_ENCOUNTER
	msgbox PacifidlogTown_House2_Text_Rururi, MSGBOX_DEFAULT
	waitmoncry
	msgbox PacifidlogTown_House2_Text_DoesntLikeTrainerVeryMuch, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_Text_ChairmansYoungerBrotherOnVacation:
	.string "{CHN}咳咳！\p"
	.string "我是宝可梦俱乐部最重要的\n"
	.string "人物——主席的\l"
	.string "弟弟。\p"
	.string "我正在这里和宝可梦一起\n"
	.string "享受假期，没错。$"

PacifidlogTown_House2_Text_AhYourPokemon:
	.string "{CHN}啊！\n"
	.string "你的宝可梦……$"

PacifidlogTown_House2_Text_AdoringPokemonTakeThis:
	.string "{CHN}它显然非常喜欢你。\p"
	.string "如此喜爱训练家又可爱的\n"
	.string "宝可梦，理应得到这样的招式学习器，你说呢？$"

PacifidlogTown_House2_Text_PutInSomeMoreEffort:
	.string "{CHN}嗯……\n"
	.string "不算差，但也不算好。\p"
	.string "你作为训练家，\n"
	.string "还需要再努力一些。$"

PacifidlogTown_House2_Text_ViciousPokemonTakeThis:
	.string "{CHN}它看起来很凶暴。\p"
	.string "这样可怕的宝可梦\n"
	.string "理应得到这样的招式学习器。$"

PacifidlogTown_House2_Text_ExplainReturnFrustration:
	.string "{CHN}如果宝可梦非常喜欢你，报恩的\n"
	.string "威力就会增强。\p"
	.string "如果它不喜欢你，迁怒的\n"
	.string "威力就会提升。$"

PacifidlogTown_House2_Text_GetGoodTMInXDays:
	.string "{CHN}哦，对了。大约{STR_VAR_1}天左右，\n"
	.string "我应该会得到一两个好的招式学习器。\p"
	.string "到时候你来看看吧。\n"
	.string "我会给你一个适合\l"
	.string "你的宝可梦的招式学习器。$"

PacifidlogTown_House2_Text_Rurii:
	.string "{CHN}露力丽：露丽。$"

PacifidlogTown_House2_Text_VeryFriendlyWithTrainer:
	.string "{CHN}它似乎和训练家\n"
	.string "非常亲密。$"

PacifidlogTown_House2_Text_Rururi:
	.string "{CHN}露力丽：露露丽！$"

PacifidlogTown_House2_Text_DoesntLikeTrainerVeryMuch:
	.string "{CHN}它似乎不太\n"
	.string "喜欢训练家。$"
