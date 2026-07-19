Route119_House_MapScripts::
	.byte 0

Route119_House_EventScript_Woman::
	msgbox Route119_House_Text_RumorAboutCaveOfOrigin, MSGBOX_NPC
	end

Route119_House_EventScript_Wingull::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
	msgbox Route119_House_Text_Wingull, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route119_House_Text_RumorAboutCaveOfOrigin:
	.string "{CHN}我听说有一个叫\n"
	.string "起源之洞的洞窟。\p"
	.string "人们传说宝可梦的灵魂\n"
	.string "会在那里复活。\l"
	.string "这种事真的可能发生吗？$"

Route119_House_Text_Wingull:
	.string "{CHN}长翅鸥：皮哟！$"
