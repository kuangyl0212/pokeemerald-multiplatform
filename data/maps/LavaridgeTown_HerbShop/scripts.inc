LavaridgeTown_HerbShop_MapScripts::
	.byte 0

LavaridgeTown_HerbShop_EventScript_Clerk::
	lock
	faceplayer
	message LavaridgeTown_HerbShop_Text_WelcomeToHerbShop
	waitmessage
	pokemart LavaridgeTown_HerbShop_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LavaridgeTown_HerbShop_Pokemart:
	.short ITEM_ENERGY_POWDER
	.short ITEM_ENERGY_ROOT
	.short ITEM_HEAL_POWDER
	.short ITEM_REVIVAL_HERB
	pokemartlistend

LavaridgeTown_HerbShop_EventScript_ExpertM::
	msgbox LavaridgeTown_HerbShop_Text_HerbalMedicineWorksButMonWillDislike, MSGBOX_NPC
	end

LavaridgeTown_HerbShop_EventScript_OldMan::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CHARCOAL, LavaridgeTown_HerbShop_EventScript_ExplainCharcoal
	msgbox LavaridgeTown_HerbShop_Text_YouveComeToLookAtHerbalMedicine, MSGBOX_DEFAULT
	giveitem ITEM_CHARCOAL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CHARCOAL
	release
	end

LavaridgeTown_HerbShop_EventScript_ExplainCharcoal::
	msgbox LavaridgeTown_HerbShop_Text_ExplainCharcoal, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_HerbShop_Text_WelcomeToHerbShop:
	.string "{CHN}欢迎来到草药店，这里\n"
	.string "有有效又便宜的药！$"

LavaridgeTown_HerbShop_Text_YouveComeToLookAtHerbalMedicine:
	.string "{CHN}你来烟突市\n"
	.string "看草药？\p"
	.string "那真值得赞赏。\p"
	.string "我喜欢你！拿着这个！$"

LavaridgeTown_HerbShop_Text_ExplainCharcoal:
	.string "{CHN}我给你的那个木炭，是用来\n"
	.string "制作草药的。\p"
	.string "宝可梦携带它\n"
	.string "也有奇效。\p"
	.string "它能增强火属性\n"
	.string "招式的威力。$"

LavaridgeTown_HerbShop_Text_HerbalMedicineWorksButMonWillDislike:
	.string "{CHN}草药效果非常好。\n"
	.string "但你的宝可梦会因此讨厌你。\l"
	.string "一定苦得要命！$"
