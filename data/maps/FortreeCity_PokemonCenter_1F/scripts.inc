FortreeCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

FortreeCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_FORTREE_CITY
	end

FortreeCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_FORTREE_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

FortreeCity_PokemonCenter_1F_EventScript_Gentleman::
	msgbox FortreeCity_PokemonCenter_1F_Text_GoToSafariZone, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_EventScript_Man::
	msgbox FortreeCity_PokemonCenter_1F_Text_RecordCornerIsNeat, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_EventScript_Boy::
	msgbox FortreeCity_PokemonCenter_1F_Text_DoYouKnowAboutPokenav, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_Text_GoToSafariZone:
	.string "{CHN}听着，孩子，你在做\n"
	.string "宝可梦图鉴吗？\p"
	.string "嗯……去狩猎地带吧。\n"
	.string "这是我的建议。$"

FortreeCity_PokemonCenter_1F_Text_RecordCornerIsNeat:
	.string "{CHN}你去过记录角落\n"
	.string "吗？\p"
	.string "挺有趣的。它会混合和匹配\n"
	.string "训练家们的记录。\p"
	.string "我不太清楚它是怎么运作的，\n"
	.string "但很酷。甚至很刺激！$"

FortreeCity_PokemonCenter_1F_Text_DoYouKnowAboutPokenav:
	.string "{CHN}哇，你有宝可梦导航器！\n"
	.string "和我的好像！\p"
	.string "你知道宝可梦导航器的\n"
	.string "对战呼叫功能吗？\p"
	.string "打开它，你就能随时和\n"
	.string "已登录的训练家聊天。\p"
	.string "它还会告诉你哪些训练家\n"
	.string "想和你再战一场。\p"
	.string "真的很方便！得文的那些人\n"
	.string "真有两下子！$"

