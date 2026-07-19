VerdanturfTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

VerdanturfTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_VERDANTURF_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

VerdanturfTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_VERDANTURF_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

VerdanturfTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox VerdanturfTown_PokemonCenter_1F_Text_FaithInYourPokemon, MSGBOX_NPC
	end

VerdanturfTown_PokemonCenter_1F_EventScript_ExpertM::
	msgbox VerdanturfTown_PokemonCenter_1F_Text_VisitForBattleTent, MSGBOX_NPC
	end

VerdanturfTown_PokemonCenter_1F_Text_FaithInYourPokemon:
	.string "{CHN}如果你不相信自己的\n"
	.string "宝可梦，就不能算是一个真正的\l"
	.string "训练家。\p"
	.string "只有那些相信自己战斗中的宝可梦\n"
	.string "的人，才能赢得\l"
	.string "最终的胜利。$"

VerdanturfTown_PokemonCenter_1F_Text_VisitForBattleTent:
	.string "{CHN}人们来绿荫镇\n"
	.string "的原因…\p"
	.string "当然是对战帐篷了。这是\n"
	.string "不言而喻的。\p"
	.string "还是说这里有你\n"
	.string "想见的人呢？$"

