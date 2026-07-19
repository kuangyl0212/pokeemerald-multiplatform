VerdanturfTown_FriendshipRatersHouse_MapScripts::
	.byte 0

VerdanturfTown_FriendshipRatersHouse_EventScript_FriendshipRater::
	lock
	faceplayer
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_SeeHowMuchPokemonLikesYou, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	switch VAR_RESULT
	case FRIENDSHIP_NONE, VerdanturfTown_FriendshipRatersHouse_EventScript_DetestsYou
	case FRIENDSHIP_1_TO_49, VerdanturfTown_FriendshipRatersHouse_EventScript_VeryWary
	case FRIENDSHIP_50_TO_99, VerdanturfTown_FriendshipRatersHouse_EventScript_NotUsedToYou
	case FRIENDSHIP_100_TO_149, VerdanturfTown_FriendshipRatersHouse_EventScript_GettingUsedToYou
	case FRIENDSHIP_150_TO_199, VerdanturfTown_FriendshipRatersHouse_EventScript_LikesYouQuiteALot
	case FRIENDSHIP_200_TO_254, VerdanturfTown_FriendshipRatersHouse_EventScript_VeryHappy
	case FRIENDSHIP_MAX, VerdanturfTown_FriendshipRatersHouse_EventScript_AdoresYou
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_DetestsYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_DetestsYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_VeryWary::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_VeryWary, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_NotUsedToYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_NotUsedToYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_GettingUsedToYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_GettingUsedToYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_LikesYouQuiteALot::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_LikesYouQuiteALot, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_VeryHappy::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_VeryHappy, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_AdoresYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_AdoresYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_Pikachu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_Pikachu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

VerdanturfTown_FriendshipRatersHouse_Text_SeeHowMuchPokemonLikesYou:
	.string "{CHN}让我看看你的宝可梦。\n"
	.string "我来检查一下它有多喜欢你。\p"
	.string "哦。\n"
	.string "你的宝可梦…$"

VerdanturfTown_FriendshipRatersHouse_Text_AdoresYou:
	.string "{CHN}它非常喜爱你。\n"
	.string "它对你的喜爱已经到了无以复加的地步。\l"
	.string "连我看着都觉得幸福。$"

VerdanturfTown_FriendshipRatersHouse_Text_VeryHappy:
	.string "{CHN}它看起来非常幸福。\n"
	.string "显然它非常喜欢你。$"

VerdanturfTown_FriendshipRatersHouse_Text_LikesYouQuiteALot:
	.string "{CHN}它相当喜欢你。\n"
	.string "它似乎想被你娇宠一下。$"

VerdanturfTown_FriendshipRatersHouse_Text_GettingUsedToYou:
	.string "{CHN}它正在逐渐习惯你。\n"
	.string "它似乎开始信任你了。$"

VerdanturfTown_FriendshipRatersHouse_Text_NotUsedToYou:
	.string "{CHN}它还不太习惯你。\n"
	.string "它既不讨厌你也不喜欢你。$"

VerdanturfTown_FriendshipRatersHouse_Text_VeryWary:
	.string "{CHN}它非常警惕。\n"
	.string "它的眼中透着可怕的凶光。\l"
	.string "它一点也不喜欢你。$"

VerdanturfTown_FriendshipRatersHouse_Text_DetestsYou:
	.string "{CHN}这话有点难以启齿…\p"
	.string "你的宝可梦简直是厌恶你。\n"
	.string "这不会让你感到不舒服吗？$"

VerdanturfTown_FriendshipRatersHouse_Text_Pikachu:
	.string "{CHN}皮卡丘：皮卡皮卡！$"

