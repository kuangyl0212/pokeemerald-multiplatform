VerdanturfTown_Mart_MapScripts::
	.byte 0

VerdanturfTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart VerdanturfTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
VerdanturfTown_Mart_Pokemart:
	.short ITEM_GREAT_BALL
	.short ITEM_NEST_BALL
	.short ITEM_SUPER_POTION
	.short ITEM_ANTIDOTE
	.short ITEM_PARALYZE_HEAL
	.short ITEM_AWAKENING
	.short ITEM_BURN_HEAL
	.short ITEM_ICE_HEAL
	.short ITEM_REPEL
	.short ITEM_X_SPECIAL
	.short ITEM_FLUFFY_TAIL
	pokemartlistend

VerdanturfTown_Mart_EventScript_Boy::
	msgbox VerdanturfTown_Mart_Text_XSpecialIsCrucial, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_ExpertF::
	msgbox VerdanturfTown_Mart_Text_NoStrategyGuidesForBattleTent, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_Lass::
	msgbox VerdanturfTown_Mart_Text_NestBallOnWeakenedPokemon, MSGBOX_NPC
	end

VerdanturfTown_Mart_Text_XSpecialIsCrucial:
	.string "{CHN}在任何宝可梦对战中，特攻提升剂\n"
	.string "都是至关重要的。\p"
	.string "它能增强某些招式的威力，\n"
	.string "尽管只持续一场对战。$"

VerdanturfTown_Mart_Text_NoStrategyGuidesForBattleTent:
	.string "{CHN}他们似乎不卖任何关于对战帐篷\n"
	.string "的必胜策略指南…\p"
	.string "看来还是得依靠自己\n"
	.string "的智慧啊…$"

VerdanturfTown_Mart_Text_NestBallOnWeakenedPokemon:
	.string "{CHN}巢穴球对已经虚弱\n"
	.string "的宝可梦效果更好。\p"
	.string "绿荫镇是你唯一能\n"
	.string "买到它的地方。$"

