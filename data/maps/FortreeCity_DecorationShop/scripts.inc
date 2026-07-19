FortreeCity_DecorationShop_MapScripts::
	.byte 0

FortreeCity_DecorationShop_EventScript_PokefanM::
	msgbox FortreeCity_DecorationShop_Text_MerchandiseSentToPC, MSGBOX_NPC
	end

FortreeCity_DecorationShop_EventScript_Girl::
	msgbox FortreeCity_DecorationShop_Text_BuyingDeskForDolls, MSGBOX_NPC
	end

FortreeCity_DecorationShop_EventScript_ClerkDesks::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration FortreeCity_DecorationShop_PokemartDecor_Desks
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
FortreeCity_DecorationShop_PokemartDecor_Desks:
	.short DECOR_SMALL_DESK
	.short DECOR_POKEMON_DESK
	.short DECOR_HEAVY_DESK
	.short DECOR_RAGGED_DESK
	.short DECOR_COMFORT_DESK
	.short DECOR_BRICK_DESK
	.short DECOR_CAMP_DESK
	.short DECOR_HARD_DESK
	pokemartlistend

FortreeCity_DecorationShop_EventScript_ClerkChairs::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration FortreeCity_DecorationShop_PokemartDecor_Chairs
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
FortreeCity_DecorationShop_PokemartDecor_Chairs:
	.short DECOR_SMALL_CHAIR
	.short DECOR_POKEMON_CHAIR
	.short DECOR_HEAVY_CHAIR
	.short DECOR_RAGGED_CHAIR
	.short DECOR_COMFORT_CHAIR
	.short DECOR_BRICK_CHAIR
	.short DECOR_CAMP_CHAIR
	.short DECOR_HARD_CHAIR
	pokemartlistend

FortreeCity_DecorationShop_Text_MerchandiseSentToPC:
	.string "{CHN}在这里买的商品会送到\n"
	.string "你自己的电脑里。\p"
	.string "太棒了！真希望他们也能\n"
	.string "那样把我送回家。$"

FortreeCity_DecorationShop_Text_BuyingDeskForDolls:
	.string "{CHN}我要买一张漂亮的桌子，\n"
	.string "把可爱的布偶放在上面。\p"
	.string "不然的话，等我装饰\n"
	.string "秘密基地的时候，我的布偶会\l"
	.string "弄脏或者被木刺扎到。$"

