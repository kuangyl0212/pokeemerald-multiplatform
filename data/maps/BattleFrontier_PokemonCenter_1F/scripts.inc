BattleFrontier_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

BattleFrontier_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_BATTLE_FRONTIER_OUTSIDE_EAST
	end

BattleFrontier_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_FRONTIER_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_PokemonCenter_1F_EventScript_SchoolKid::
	msgbox BattleFrontier_PokemonCenter_1F_Text_NeverSeenPokemon, MSGBOX_NPC
	end

BattleFrontier_PokemonCenter_1F_EventScript_Man::
	msgbox BattleFrontier_PokemonCenter_1F_Text_NextStopBattleArena, MSGBOX_NPC
	end

BattleFrontier_PokemonCenter_1F_EventScript_Picnicker::
	msgbox BattleFrontier_PokemonCenter_1F_Text_GoingThroughEveryChallenge, MSGBOX_NPC
	end

BattleFrontier_PokemonCenter_1F_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox BattleFrontier_PokemonCenter_1F_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_PokemonCenter_1F_Text_NeverSeenPokemon:
	.string "{CHN}刚才有人在这里使用\n"
	.string "一只我从未见过的宝可梦。\p"
	.string "至少我在训练家学校里\n"
	.string "从没学过这种宝可梦。\p"
	.string "不知道在哪里才能捕捉到\n"
	.string "那样的宝可梦呢。$"

BattleFrontier_PokemonCenter_1F_Text_NextStopBattleArena:
	.string "{CHN}好！下一站，对战竞技场！\n"
	.string "我得从电脑存储系统里\l"
	.string "选出合适的宝可梦。$"

BattleFrontier_PokemonCenter_1F_Text_GoingThroughEveryChallenge:
	.string "{CHN}嘻嘻……我要带着这只小宝贝\n"
	.string "挑战每一个项目！$"

BattleFrontier_PokemonCenter_1F_Text_Skitty:
	.string "{CHN}向尾喵：喵呜喵啊！$"

