MauvilleCity_Mart_MapScripts::
	.byte 0

MauvilleCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MauvilleCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MauvilleCity_Mart_Pokemart:
	.short ITEM_POKE_BALL
	.short ITEM_GREAT_BALL
	.short ITEM_SUPER_POTION
	.short ITEM_ANTIDOTE
	.short ITEM_PARALYZE_HEAL
	.short ITEM_AWAKENING
	.short ITEM_X_SPEED
	.short ITEM_X_ATTACK
	.short ITEM_X_DEFEND
	.short ITEM_GUARD_SPEC
	.short ITEM_DIRE_HIT
	.short ITEM_X_ACCURACY
	pokemartlistend

MauvilleCity_Mart_EventScript_ExpertM::
	msgbox MauvilleCity_Mart_Text_ItemsToTemporarilyElevateStats, MSGBOX_NPC
	end

MauvilleCity_Mart_EventScript_Man::
	msgbox MauvilleCity_Mart_Text_DecisionsDetermineBattle, MSGBOX_NPC
	end

MauvilleCity_Mart_Text_ItemsToTemporarilyElevateStats:
	.string "{CHN}有些道具可以临时\n"
	.string "提升宝可梦的能力。\p"
	.string "我知道你在对战中使用的\n"
	.string "有攻击强化和防御强化……\p"
	.string "我相信还有其他\n"
	.string "类似的道具。$"

MauvilleCity_Mart_Text_DecisionsDetermineBattle:
	.string "{CHN}使用某个招式，或者使用道具\n"
	.string "代替……\p"
	.string "训练家的决定\n"
	.string "决定着对战的走向，我是这么想的。$"
