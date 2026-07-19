SlateportCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SlateportCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

SlateportCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_SLATEPORT_CITY
	call Common_EventScript_UpdateBrineyLocation
	end

SlateportCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_SLATEPORT_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

SlateportCity_PokemonCenter_1F_EventScript_Sailor::
	msgbox SlateportCity_PokemonCenter_1F_Text_RaiseDifferentTypesOfPokemon, MSGBOX_NPC
	end

SlateportCity_PokemonCenter_1F_EventScript_Woman::
	msgbox SlateportCity_PokemonCenter_1F_Text_TradedMonWithFriend, MSGBOX_NPC
	end

SlateportCity_PokemonCenter_1F_Text_RaiseDifferentTypesOfPokemon:
	.string "{CHN}想要对战的技巧吗？\p"
	.string "我认为应该均衡地培养不同种类\n"
	.string "的宝可梦。\p"
	.string "只让一只宝可梦变强\n"
	.string "是不行的。\p"
	.string "如果它有属性劣势，\n"
	.string "可能就毫无胜算了。$"

SlateportCity_PokemonCenter_1F_Text_TradedMonWithFriend:
	.string "{CHN}我和朋友们交换宝可梦。\p"
	.string "如果交换来的宝可梦携带了道具，\n"
	.string "我会加倍开心！$"

