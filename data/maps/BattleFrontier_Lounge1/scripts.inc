BattleFrontier_Lounge1_MapScripts::
	.byte 0

/* NPC that rates pokemon based on their IVs*/
BattleFrontier_Lounge1_EventScript_Breeder::
	lock
	faceplayer
	call_if_unset FLAG_MET_BATTLE_FRONTIER_BREEDER, BattleFrontier_Lounge1_EventScript_BreederIntro
	call_if_set FLAG_MET_BATTLE_FRONTIER_BREEDER, BattleFrontier_Lounge1_EventScript_AlreadyMetBreeder
	setflag FLAG_MET_BATTLE_FRONTIER_BREEDER
	goto BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder
	end

BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder::
	special ChoosePartyMon
	waitstate
	goto_if_ne VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge1_EventScript_ShowMonToBreeder
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge1_EventScript_CancelMonSelect
	end

BattleFrontier_Lounge1_EventScript_BreederIntro::
	msgbox BattleFrontier_Lounge1_Text_PokemonBreederIntro, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge1_EventScript_AlreadyMetBreeder::
	msgbox BattleFrontier_Lounge1_Text_LetsLookAtYourPokemon, MSGBOX_DEFAULT
	return

/* BufferVarsForIVRater buffers the following values*/
/* VAR_0x8005: Sum of the mons IVs*/
/* VAR_0x8006: Stat id of highest IV stat*/
/* VAR_0x8007: IV of the highest IV stat*/
BattleFrontier_Lounge1_EventScript_ShowMonToBreeder::
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, BattleFrontier_Lounge1_EventScript_ShowEggToBreeder
	special BufferVarsForIVRater
	goto_if_le VAR_0x8005, 90, BattleFrontier_Lounge1_EventScript_AverageTotalIVs       /* Average of 15*/
	goto_if_le VAR_0x8005, 120, BattleFrontier_Lounge1_EventScript_AboveAverageTotalIVs /* Average of 20*/
	goto_if_le VAR_0x8005, 150, BattleFrontier_Lounge1_EventScript_HighTotalIVs         /* Average of 25*/
	goto_if_ge VAR_0x8005, 151, BattleFrontier_Lounge1_EventScript_VeryHighTotalIVs     /* Average of > 25*/
	end

BattleFrontier_Lounge1_EventScript_ShowEggToBreeder::
	msgbox BattleFrontier_Lounge1_Text_EvenICantTell, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder
	end

/* Comment on the highest IV stat*/
BattleFrontier_Lounge1_EventScript_HighestIVStat::
	goto_if_eq VAR_0x8006, STAT_HP, BattleFrontier_Lounge1_EventScript_HighestIVHP
	goto_if_eq VAR_0x8006, STAT_ATK, BattleFrontier_Lounge1_EventScript_HighestIVAtk
	goto_if_eq VAR_0x8006, STAT_DEF, BattleFrontier_Lounge1_EventScript_HighestIVDef
	goto_if_eq VAR_0x8006, STAT_SPEED, BattleFrontier_Lounge1_EventScript_HighestIVSpeed
	goto_if_eq VAR_0x8006, STAT_SPATK, BattleFrontier_Lounge1_EventScript_HighestIVSpAtk
	goto_if_eq VAR_0x8006, STAT_SPDEF, BattleFrontier_Lounge1_EventScript_HighestIVSpDef
	end

/* Comment on the highest IV value*/
BattleFrontier_Lounge1_EventScript_HighestIVValue::
	goto_if_le VAR_0x8007, 15, BattleFrontier_Lounge1_EventScript_HighestIVLow
	goto_if_le VAR_0x8007, 25, BattleFrontier_Lounge1_EventScript_HighestIVMid
	goto_if_le VAR_0x8007, 30, BattleFrontier_Lounge1_EventScript_HighestIVHigh
	goto_if_ge VAR_0x8007, 31, BattleFrontier_Lounge1_EventScript_HighestIVMax
	end

BattleFrontier_Lounge1_EventScript_EndBreederComments::
	release
	end

BattleFrontier_Lounge1_EventScript_AverageTotalIVs::
	msgbox BattleFrontier_Lounge1_Text_AverageAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_AboveAverageTotalIVs::
	msgbox BattleFrontier_Lounge1_Text_BetterThanAverageAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_HighTotalIVs::
	msgbox BattleFrontier_Lounge1_Text_ImpressiveAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_VeryHighTotalIVs::
	msgbox BattleFrontier_Lounge1_Text_OutstandingAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_HighestIVHP::
	msgbox BattleFrontier_Lounge1_Text_BestAspectHP, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVAtk::
	msgbox BattleFrontier_Lounge1_Text_BestAspectAtk, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVDef::
	msgbox BattleFrontier_Lounge1_Text_BestAspectDef, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVSpeed::
	msgbox BattleFrontier_Lounge1_Text_BestAspectSpeed, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVSpAtk::
	msgbox BattleFrontier_Lounge1_Text_BestAspectSpAtk, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVSpDef::
	msgbox BattleFrontier_Lounge1_Text_BestAspectSpDef, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVLow::
	msgbox BattleFrontier_Lounge1_Text_StatRelativelyGood, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_HighestIVMid::
	msgbox BattleFrontier_Lounge1_Text_StatImpressive, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_HighestIVHigh::
	msgbox BattleFrontier_Lounge1_Text_StatOutstanding, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_HighestIVMax::
	msgbox BattleFrontier_Lounge1_Text_StatFlawless, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_CancelMonSelect::
	msgbox BattleFrontier_Lounge1_Text_NoTimeForMyAdvice, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge1_EventScript_Boy1::
	msgbox BattleFrontier_Lounge1_Text_SaidMyMonIsOutstanding, MSGBOX_NPC
	end

BattleFrontier_Lounge1_EventScript_Boy2::
	msgbox BattleFrontier_Lounge1_Text_DidntDoAnythingSpecialRaisingIt, MSGBOX_NPC
	end

BattleFrontier_Lounge1_Text_PokemonBreederIntro:
	.string "{CHN}我培育宝可梦已经七十年了！\n"
	.string "我就是被人们尊称为\l"
	.string "传奇首席宝可梦培育家的人！\p"
	.string "如果你也像我一样经验丰富，\n"
	.string "你一眼就能看出宝可梦\l"
	.string "的能力如何。\p"
	.string "你是个训练家。难道你不想\n"
	.string "了解自己宝可梦的\l"
	.string "能力吗？\p"
	.string "来吧！\n"
	.string "让我看看你的宝可梦！$"

BattleFrontier_Lounge1_Text_AverageAbility:
	.string "{CHN}……嗯……\p"
	.string "这一只，整体来说，\n"
	.string "我会说它的能力属于平均水平。$"

BattleFrontier_Lounge1_Text_BetterThanAverageAbility:
	.string "{CHN}……嗯……\p"
	.string "这一只，整体来说，\n"
	.string "我会说它的能力高于平均水平。$"

BattleFrontier_Lounge1_Text_ImpressiveAbility:
	.string "{CHN}……嗯……\p"
	.string "这一只，整体来说，\n"
	.string "我会说它的能力相当出色！$"

BattleFrontier_Lounge1_Text_OutstandingAbility:
	.string "{CHN}……嗯……\p"
	.string "这一只，整体来说，\n"
	.string "我会说它的能力出类拔萃！$"

BattleFrontier_Lounge1_Text_BestAspectHP:
	.string "{CHN}顺便一提，它最出色的方面，\n"
	.string "我会说是它的HP……$"

BattleFrontier_Lounge1_Text_BestAspectAtk:
	.string "{CHN}顺便一提，它最出色的方面，\n"
	.string "我会说是它的攻击……$"

BattleFrontier_Lounge1_Text_BestAspectDef:
	.string "{CHN}顺便一提，它最出色的方面，\n"
	.string "我会说是它的防御……$"

BattleFrontier_Lounge1_Text_BestAspectSpAtk:
	.string "{CHN}顺便一提，它最出色的方面，\n"
	.string "我会说是它的特攻……$"

BattleFrontier_Lounge1_Text_BestAspectSpDef:
	.string "{CHN}顺便一提，它最出色的方面，\n"
	.string "我会说是它的特防……$"

BattleFrontier_Lounge1_Text_BestAspectSpeed:
	.string "{CHN}顺便一提，它最出色的方面，\n"
	.string "我会说是它的速度……$"

BattleFrontier_Lounge1_Text_StatRelativelyGood:
	.string "{CHN}那项能力还算不错。\n"
	.string "……嗯……我这么说。$"

BattleFrontier_Lounge1_Text_StatImpressive:
	.string "{CHN}那项能力相当出色。\n"
	.string "……嗯……我这么说。$"

BattleFrontier_Lounge1_Text_StatOutstanding:
	.string "{CHN}那项能力出类拔萃！\n"
	.string "……嗯……我这么说。$"

BattleFrontier_Lounge1_Text_StatFlawless:
	.string "{CHN}完美无瑕！无可挑剔！\n"
	.string "……嗯……我这么说。$"

BattleFrontier_Lounge1_Text_NoTimeForMyAdvice:
	.string "{CHN}什么？\n"
	.string "你没时间听我的建议？\p"
	.string "你应该时刻渴望从长辈的\n"
	.string "经验中学习才对！$"

/* Unused*/
BattleFrontier_Lounge1_Text_HaveBusinessNeedsTending:
	.string "{CHN}是的，什么事？\p"
	.string "我还有事情要处理！\n"
	.string "下次再说吧！$"

BattleFrontier_Lounge1_Text_LetsLookAtYourPokemon:
	.string "{CHN}啊，小家伙！你对你的宝可梦\n"
	.string "的能力感兴趣吗？\p"
	.string "来，来！\n"
	.string "让我看看你的宝可梦！$"

BattleFrontier_Lounge1_Text_EvenICantTell:
	.string "{CHN}虽然我是专家，但即使是我也\n"
	.string "无法判断未孵化的宝可梦！\p"
	.string "给我看宝可梦！\n"
	.string "我需要看的是宝可梦！$"

BattleFrontier_Lounge1_Text_SaidMyMonIsOutstanding:
	.string "{CHN}他说我的宝可梦出类拔萃！\n"
	.string "我很高兴我用心培育了它！$"

BattleFrontier_Lounge1_Text_DidntDoAnythingSpecialRaisingIt:
	.string "{CHN}他说我的宝可梦出类拔萃！\n"
	.string "但我培育它的时候\l"
	.string "并没有做什么特别的事……$"

