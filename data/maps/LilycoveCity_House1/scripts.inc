LilycoveCity_House1_MapScripts::
	.byte 0

LilycoveCity_House1_EventScript_ExpertM::
	msgbox LilycoveCity_House1_Text_PokemonPartnersNotTools, MSGBOX_NPC
	end

LilycoveCity_House1_EventScript_Kecleon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KECLEON, CRY_MODE_NORMAL
	msgbox LilycoveCity_House1_Text_Kecleon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

LilycoveCity_House1_Text_PokemonPartnersNotTools:
	.string "{CHN}宝可梦是人们的伙伴。\n"
	.string "它们不是我们的工具。\p"
	.string "可惜的是，有些人\n"
	.string "就是不明白这一点……$"

LilycoveCity_House1_Text_Kecleon:
	.string "{CHN}变隐龙：噜喽喽？$"
