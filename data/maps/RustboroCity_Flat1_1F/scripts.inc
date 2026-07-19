RustboroCity_Flat1_1F_MapScripts::
	.byte 0

RustboroCity_Flat1_1F_EventScript_Man::
	msgbox RustboroCity_Flat1_1F_Text_EveryPokemonHasAbility, MSGBOX_NPC
	end

RustboroCity_Flat1_1F_EventScript_Woman::
	msgbox RustboroCity_Flat1_1F_Text_PokemonStrange, MSGBOX_NPC
	end

RustboroCity_Flat1_1F_Text_EveryPokemonHasAbility:
	.string "{CHN}每只宝可梦都有一种\n"
	.string "可以使用的特殊能力.$"

RustboroCity_Flat1_1F_Text_PokemonStrange:
	.string "{CHN}宝可梦真是奇妙的生物.$"

