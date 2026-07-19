Route111_WinstrateFamilysHouse_MapScripts::
	.byte 0

Route111_WinstrateFamilysHouse_EventScript_Victor::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VICTOR
	msgbox Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Victoria::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VICTORIA
	goto_if_set FLAG_RECEIVED_MACHO_BRACE, Route111_WinstrateFamilysHouse_EventScript_ReceivedMachoBrace
	msgbox Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace, MSGBOX_DEFAULT
	giveitem ITEM_MACHO_BRACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MACHO_BRACE
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_ReceivedMachoBrace::
	msgbox Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vivi::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VIVI
	msgbox Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vicky::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VICKY
	goto_if_set FLAG_TEMP_4, Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrong, MSGBOX_DEFAULT
	setflag FLAG_TEMP_4
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo::
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection::
	closemessage
	applymovement VAR_0x8008, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou:
	.string "{CHN}你是我见过的第一个能如此\n"
	.string "熟练地指挥宝可梦的训练家。\p"
	.string "不过我得告诉你——我儿子\n"
	.string "比你更强。\p"
	.string "他甚至挑战过宝可梦联盟，\n"
	.string "告诉你吧。$"

Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace:
	.string "{CHN}我们用这个竞争背心能更\n"
	.string "有效地强化宝可梦\l"
	.string "的训练。\p"
	.string "既然你打败了我们这里所有人，\n"
	.string "我不知道你是不是需要它，但我们\l"
	.string "还是想把这竞争背心送给你。$"

Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles:
	.string "{CHN}提到宝可梦对战，\n"
	.string "我们可是相当热忱。$"

Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers:
	.string "{CHN}妈妈比爸爸强。\p"
	.string "我比妈妈强。\p"
	.string "奶奶比我还要强！\p"
	.string "但我哥哥比奶奶\n"
	.string "还要强。$"

Route111_WinstrateFamilysHouse_Text_GrandsonStrong:
	.string "{CHN}你很强，这是毫无疑问的。\p"
	.string "但如果你和我孙子对战，\n"
	.string "你会沮丧得直哭。\p"
	.string "他比我们家认识的任何训练家\n"
	.string "都要强得多。\p"
	.string "他现在一定正在挑战宝可梦\n"
	.string "联盟冠军。\p"
	.string "就我孙子那本事，他说不定已经是\n"
	.string "冠军了！$"

Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort:
	.string "{CHN}我孙子现在一定正在挑战\n"
	.string "宝可梦联盟冠军。\p"
	.string "就我孙子那本事，他说不定已经是\n"
	.string "冠军了！$"

