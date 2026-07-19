MossdeepCity_House4_MapScripts::
	.byte 0

MossdeepCity_House4_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, MossdeepCity_House4_EventScript_CanBattleAtSecretBases
	msgbox MossdeepCity_House4_Text_BrotherLikesToFindBases, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_CanBattleAtSecretBases::
	msgbox MossdeepCity_House4_Text_BrotherLikesToVisitBasesAndBattle, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_NinjaBoy::
	lock
	faceplayer
	special CheckPlayerHasSecretBase
	goto_if_eq VAR_RESULT, FALSE, MossdeepCity_House4_EventScript_NoSecretBase
	special GetSecretBaseNearbyMapName
	msgbox MossdeepCity_House4_Text_YouMadeSecretBaseNearX, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_NoSecretBase::
	msgbox MossdeepCity_House4_Text_MakeSecretBase, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox MossdeepCity_House4_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

MossdeepCity_House4_Text_BrotherLikesToFindBases:
	.string "{CHN}我弟弟说他喜欢去\n"
	.string "寻找别人的秘密基地。$"

MossdeepCity_House4_Text_BrotherLikesToVisitBasesAndBattle:
	.string "{CHN}我弟弟说他喜欢去\n"
	.string "拜访别人的秘密基地，并进行\l"
	.string "宝可梦对战。$"

MossdeepCity_House4_Text_YouMadeSecretBaseNearX:
	.string "{CHN}在{STR_VAR_1}附近建造\n"
	.string "秘密基地的人是你吗？$"

MossdeepCity_House4_Text_MakeSecretBase:
	.string "{CHN}你应该在什么地方建一个\n"
	.string "秘密基地。我会去找的！$"

MossdeepCity_House4_Text_Skitty:
	.string "{CHN}向尾喵：喵呜？$"
