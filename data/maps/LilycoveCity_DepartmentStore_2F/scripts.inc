LilycoveCity_DepartmentStore_2F_MapScripts::
	.byte 0

LilycoveCity_DepartmentStore_2F_EventScript_Cook::
	msgbox LilycoveCity_DepartmentStore_2F_Text_LearnToUseItemsProperly, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_2F_EventScript_PokefanF::
	msgbox LilycoveCity_DepartmentStore_2F_Text_GoodGiftForHusband, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_2F_EventScript_Sailor::
	msgbox LilycoveCity_DepartmentStore_2F_Text_StockUpOnItems, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_2F_EventScript_ClerkLeft::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LilycoveCity_DepartmentStore_2F_Pokemart1
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_2F_Pokemart1:
	.short ITEM_POKE_BALL
	.short ITEM_GREAT_BALL
	.short ITEM_ULTRA_BALL
	.short ITEM_ESCAPE_ROPE
	.short ITEM_FULL_HEAL
	.short ITEM_ANTIDOTE
	.short ITEM_PARALYZE_HEAL
	.short ITEM_BURN_HEAL
	.short ITEM_ICE_HEAL
	.short ITEM_AWAKENING
	.short ITEM_FLUFFY_TAIL
	pokemartlistend

LilycoveCity_DepartmentStore_2F_EventScript_ClerkRight::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LilycoveCity_DepartmentStore_2F_Pokemart2
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_2F_Pokemart2:
	.short ITEM_POTION
	.short ITEM_SUPER_POTION
	.short ITEM_HYPER_POTION
	.short ITEM_MAX_POTION
	.short ITEM_REVIVE
	.short ITEM_REPEL
	.short ITEM_SUPER_REPEL
	.short ITEM_MAX_REPEL
	.short ITEM_WAVE_MAIL
	.short ITEM_MECH_MAIL
	pokemartlistend

LilycoveCity_DepartmentStore_2F_Text_LearnToUseItemsProperly:
	.string "{CHN}学会正确使用道具。\n"
	.string "这是基本功。$"

LilycoveCity_DepartmentStore_2F_Text_GoodGiftForHusband:
	.string "{CHN}我丈夫在家里等着。\n"
	.string "送他什么礼物好呢？$"

LilycoveCity_DepartmentStore_2F_Text_StockUpOnItems:
	.string "{CHN}我马上要踏上长途旅行了。\n"
	.string "得储备些道具才行。$"

