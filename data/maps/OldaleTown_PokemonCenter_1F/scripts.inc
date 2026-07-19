OldaleTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OldaleTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

OldaleTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_OLDALE_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

OldaleTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_OLDALE_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

OldaleTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox OldaleTown_PokemonCenter_1F_Text_TrainersCanUsePC, MSGBOX_NPC
	end

OldaleTown_PokemonCenter_1F_EventScript_Boy::
	msgbox OldaleTown_PokemonCenter_1F_Text_PokemonCentersAreGreat, MSGBOX_NPC
	end

OldaleTown_PokemonCenter_1F_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_SYS_POKEDEX_GET, OldaleTown_PokemonCenter_1F_EventScript_WirelessClubAvailable
	msgbox OldaleTown_PokemonCenter_1F_Text_WirelessClubNotAvailable, MSGBOX_DEFAULT
	release
	end

OldaleTown_PokemonCenter_1F_EventScript_WirelessClubAvailable::
	msgbox OldaleTown_PokemonCenter_1F_Text_TradedInWirelessClub, MSGBOX_DEFAULT
	release
	end

OldaleTown_PokemonCenter_1F_Text_TrainersCanUsePC:
	.string "{CHN}角落里的那台电脑\n"
	.string "是供宝可梦训练家使用的.\p"
	.string "当然，也就是说你也可以\n"
	.string "自由使用它.$"

OldaleTown_PokemonCenter_1F_Text_PokemonCentersAreGreat:
	.string "{CHN}宝可梦中心真棒！\p"
	.string "你可以无限次\n"
	.string "使用他们的服务，而且完全免费.\l"
	.string "完全不用担心！$"

OldaleTown_PokemonCenter_1F_Text_WirelessClubNotAvailable:
	.string "{CHN}二楼的宝可梦无线俱乐部\n"
	.string "是最近建成的.\p"
	.string "但他们说还在进行\n"
	.string "调整.$"

OldaleTown_PokemonCenter_1F_Text_TradedInWirelessClub:
	.string "{CHN}二楼的宝可梦无线俱乐部\n"
	.string "是最近建成的.\p"
	.string "我马上就交换了宝可梦.$"

