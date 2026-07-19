DewfordTown_House1_MapScripts::
	.byte 0

DewfordTown_House1_EventScript_Man::
	msgbox DewfordTown_House1_Text_LotToBeSaidForLivingOnIsland, MSGBOX_NPC
	end

DewfordTown_House1_EventScript_Woman::
	msgbox DewfordTown_House1_Text_LifeGoesSlowlyOnIsland, MSGBOX_NPC
	end

DewfordTown_House1_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox DewfordTown_House1_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

DewfordTown_House1_Text_LotToBeSaidForLivingOnIsland:
	.string "{CHN}住在像这样\n"
	.string "与宝可梦和家人和谐相处的\l"
	.string "小岛上，有很多好处。$"

DewfordTown_House1_Text_LifeGoesSlowlyOnIsland:
	.string "{CHN}我嫁给丈夫后离开了\n"
	.string "大港口凯那市来到这里。\p"
	.string "在这个小岛上生活节奏很慢。\n"
	.string "但是被美丽的\l"
	.string "大海环绕——那也是一种幸福。$"

DewfordTown_House1_Text_Zigzagoon:
	.string "{CHN}蛇纹熊：咕咕uh！$"

