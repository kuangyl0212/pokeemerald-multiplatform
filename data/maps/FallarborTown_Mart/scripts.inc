FallarborTown_Mart_MapScripts::
	.byte 0

FallarborTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart FallarborTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
FallarborTown_Mart_Pokemart:
	.short ITEM_GREAT_BALL
	.short ITEM_SUPER_POTION
	.short ITEM_ANTIDOTE
	.short ITEM_PARALYZE_HEAL
	.short ITEM_ESCAPE_ROPE
	.short ITEM_SUPER_REPEL
	.short ITEM_X_SPECIAL
	.short ITEM_X_SPEED
	.short ITEM_X_ATTACK
	.short ITEM_X_DEFEND
	.short ITEM_DIRE_HIT
	.short ITEM_GUARD_SPEC
	pokemartlistend

FallarborTown_Mart_EventScript_Woman::
	msgbox FallarborTown_Mart_Text_DecidingSkittyEvolve, MSGBOX_NPC
	end

FallarborTown_Mart_EventScript_PokefanM::
	msgbox FallarborTown_Mart_Text_SellNuggetIFound, MSGBOX_NPC
	end

FallarborTown_Mart_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox FallarborTown_Mart_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FallarborTown_Mart_Text_DecidingSkittyEvolve:
	.string "{CHN}我正在苦恼要不要\n"
	.string "让我的向尾猫进化。\p"
	.string "我只需要用这块月之石，\n"
	.string "但就是难以决定……\p"
	.string "如果让它进化，它会变得\n"
	.string "更强。\p"
	.string "但它的样子也会大不一样。$"

FallarborTown_Mart_Text_Skitty:
	.string "{CHN}向尾猫：喵？$"

FallarborTown_Mart_Text_SellNuggetIFound:
	.string "{CHN}我在这里找到的这颗金珠……\n"
	.string "我想我只能把它卖了，\l"
	.string "反正它也没别的用处。$"
