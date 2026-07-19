OldaleTown_House2_MapScripts::
	.byte 0

OldaleTown_House2_EventScript_Woman::
	msgbox OldaleTown_House2_Text_PokemonLevelUp, MSGBOX_NPC
	end

OldaleTown_House2_EventScript_Man::
	msgbox OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon, MSGBOX_NPC
	end

OldaleTown_House2_Text_PokemonLevelUp:
	.string "{CHN}宝可梦通过战斗，最终会\n"
	.string "升级并变得更强.$"

OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon:
	.string "{CHN}如果身边的宝可梦\n"
	.string "变强了，你就能去离这里\l"
	.string "更远的地方.$"

