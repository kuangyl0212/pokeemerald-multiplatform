LavaridgeTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

LavaridgeTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_LAVARIDGE_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_LAVARIDGE_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Youngster::
	msgbox LavaridgeTown_PokemonCenter_1F_Text_HotSpringCanInvigorate, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Woman::
	msgbox LavaridgeTown_PokemonCenter_1F_Text_TrainersPokemonSpendTimeTogether, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox LavaridgeTown_PokemonCenter_1F_Text_TrainersShouldRestToo, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_Text_TrainersPokemonSpendTimeTogether:
	.string "{CHN}我觉得宝可梦和训练家\n"
	.string "相处时间越长，关系就越亲密。\p"
	.string "越长越好。\n"
	.string "我是这么想的。$"

LavaridgeTown_PokemonCenter_1F_Text_HotSpringCanInvigorate:
	.string "{CHN}只要坐在温泉池里\n"
	.string "就能精神焕发，真有点神奇。\p"
	.string "我希望我的宝可梦\n"
	.string "也能泡一泡。$"

LavaridgeTown_PokemonCenter_1F_Text_TrainersShouldRestToo:
	.string "{CHN}呵呵呵！嘿，孩子，从这里\n"
	.string "就能到温泉。\p"
	.string "如果宝可梦在休息，\n"
	.string "训练家也该休息。$"
