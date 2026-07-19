PetalburgCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PetalburgCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

PetalburgCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_PETALBURG_CITY
	call Common_EventScript_UpdateBrineyLocation
	end

PetalburgCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_PETALBURG_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

PetalburgCity_PokemonCenter_1F_EventScript_FatMan::
	msgbox PetalburgCity_PokemonCenter_1F_Text_PCStorageSystem, MSGBOX_NPC
	end

PetalburgCity_PokemonCenter_1F_EventScript_Youngster::
	msgbox PetalburgCity_PokemonCenter_1F_Text_OranBerryRegainedHP, MSGBOX_NPC
	end

PetalburgCity_PokemonCenter_1F_EventScript_Woman::
	lock
	faceplayer
	msgbox PetalburgCity_PokemonCenter_1F_Text_ManyTypesOfPokemon, MSGBOX_DEFAULT
	specialvar VAR_RESULT, IsStarterInParty
	goto_if_eq VAR_RESULT, TRUE, PetalburgCity_PokemonCenter_1F_EventScript_SayStarterTypeInfo
	release
	end

PetalburgCity_PokemonCenter_1F_EventScript_SayStarterTypeInfo::
	call_if_eq VAR_STARTER_MON, 0, PetalburgCity_PokemonCenter_1F_EventScript_SayTreeckoType
	call_if_eq VAR_STARTER_MON, 1, PetalburgCity_PokemonCenter_1F_EventScript_SayTorchicType
	call_if_eq VAR_STARTER_MON, 2, PetalburgCity_PokemonCenter_1F_EventScript_SayMudkipType
	release
	end

PetalburgCity_PokemonCenter_1F_EventScript_SayTreeckoType::
	msgbox PetalburgCity_PokemonCenter_1F_Text_TreeckoIsGrassType, MSGBOX_DEFAULT
	return

PetalburgCity_PokemonCenter_1F_EventScript_SayTorchicType::
	msgbox PetalburgCity_PokemonCenter_1F_Text_TorchicIsFireType, MSGBOX_DEFAULT
	return

PetalburgCity_PokemonCenter_1F_EventScript_SayMudkipType::
	msgbox PetalburgCity_PokemonCenter_1F_Text_MudkipIsWaterType, MSGBOX_DEFAULT
	return

PetalburgCity_PokemonCenter_1F_Text_PCStorageSystem:
	.string "{CHN}那个电脑上的宝可梦\n"
	.string "存储系统……\p"
	.string "能做出它的\n"
	.string "人一定是位科学天才吧！$"

PetalburgCity_PokemonCenter_1F_Text_OranBerryRegainedHP:
	.string "{CHN}我的宝可梦吃了一颗\n"
	.string "橙橙果后，HP就恢复了！$"

PetalburgCity_PokemonCenter_1F_Text_ManyTypesOfPokemon:
	.string "{CHN}宝可梦有很多种属性。\p"
	.string "每种属性对其他属性\n"
	.string "都有它的强项和弱点。\p"
	.string "根据宝可梦的属性，\n"
	.string "对战可能轻松也可能艰难。$"

PetalburgCity_PokemonCenter_1F_Text_TreeckoIsGrassType:
	.string "{CHN}比如说，你的木守宫\n"
	.string "是草属性的。\p"
	.string "它对水属性和\n"
	.string "地面属性很强。\p"
	.string "但是，它对火属性\n"
	.string "宝可梦很弱。$"

PetalburgCity_PokemonCenter_1F_Text_TorchicIsFireType:
	.string "{CHN}比如说，你的火稚鸡\n"
	.string "是火属性的。\p"
	.string "它对草属性和\n"
	.string "虫属性很强。\p"
	.string "但是，它对水属性\n"
	.string "宝可梦很弱。$"

PetalburgCity_PokemonCenter_1F_Text_MudkipIsWaterType:
	.string "{CHN}比如说，你的水跃鱼\n"
	.string "是水属性的。\p"
	.string "它对火属性很强。\p"
	.string "但是，它对草属性\n"
	.string "和电属性宝可梦很弱。$"

