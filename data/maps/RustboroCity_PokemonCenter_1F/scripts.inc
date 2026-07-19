RustboroCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

RustboroCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_RUSTBORO_CITY
	call Common_EventScript_UpdateBrineyLocation
	end

RustboroCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_RUSTBORO_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

RustboroCity_PokemonCenter_1F_EventScript_Man::
	msgbox RustboroCity_PokemonCenter_1F_Text_PokemonHavePersonalities, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_Boy::
	msgbox RustboroCity_PokemonCenter_1F_Text_MaleAndFemalePokemon, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_Girl::
	msgbox RustboroCity_PokemonCenter_1F_Text_HMCutNextDoor, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_Text_PokemonHavePersonalities:
	.string "{CHN}我的宝可梦是天真性格，\n"
	.string "我朋友的是急躁性格.\p"
	.string "宝可梦有自己的性格，\n"
	.string "真是太有趣了！$"

RustboroCity_PokemonCenter_1F_Text_MaleAndFemalePokemon:
	.string "{CHN}和人一样，宝可梦也分\n"
	.string "雄性和雌性.\p"
	.string "但似乎没人知道\n"
	.string "它们有什么不同.$"

RustboroCity_PokemonCenter_1F_Text_HMCutNextDoor:
	.string "{CHN}隔壁的男人给了我一台秘传学习器！\p"
	.string "我用它教会了我的宝可梦\n"
	.string "如何用居合劈砍倒细小的树木.$"

