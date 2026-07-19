MossdeepCity_House1_MapScripts::
	.byte 0

MossdeepCity_House1_EventScript_BlackBelt::
	lock
	faceplayer
	bufferleadmonspeciesname STR_VAR_1
	msgbox MossdeepCity_House1_Text_HmmYourPokemon, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetPokeblockNameByMonNature
	goto_if_eq VAR_RESULT, 0, MossdeepCity_House1_EventScript_NeutralNature
	msgbox MossdeepCity_House1_Text_ItLikesXPokeblocks, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House1_EventScript_NeutralNature::
	msgbox MossdeepCity_House1_Text_DoesntLikeOrDislikePokeblocks, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House1_EventScript_Woman::
	msgbox MossdeepCity_House1_Text_HusbandCanTellPokeblockMonLikes, MSGBOX_NPC
	end

MossdeepCity_House1_Text_HmmYourPokemon:
	.string "{CHN}嗯！\n"
	.string "你的{STR_VAR_1}……$"

MossdeepCity_House1_Text_ItLikesXPokeblocks:
	.string "{CHN}它喜欢{STR_VAR_1}，\n"
	.string "对吧？\p"
	.string "没错，我确信！它绝对\n"
	.string "喜欢{STR_VAR_1}！$"

MossdeepCity_House1_Text_DoesntLikeOrDislikePokeblocks:
	.string "{CHN}它似乎不特别喜欢也不讨厌\n"
	.string "任何{POKEBLOCK}。$"

MossdeepCity_House1_Text_HusbandCanTellPokeblockMonLikes:
	.string "{CHN}我丈夫一眼就能看出宝可梦\n"
	.string "喜欢什么样的{POKEBLOCK}。$"
