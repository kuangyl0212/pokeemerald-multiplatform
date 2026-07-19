PetalburgCity_House2_MapScripts::
	.byte 0

PetalburgCity_House2_EventScript_Woman::
	msgbox PetalburgCity_House2_Text_NormanBecameGymLeader, MSGBOX_NPC
	end

PetalburgCity_House2_EventScript_SchoolKid::
	msgbox PetalburgCity_House2_Text_BattledNormanOnce, MSGBOX_NPC
	end

PetalburgCity_House2_Text_NormanBecameGymLeader:
	.string "{CHN}千里成为了我们城镇新的\n"
	.string "道馆馆主。\p"
	.string "我记得他是从某个\n"
	.string "遥远的地方把家人接来的。$"

PetalburgCity_House2_Text_BattledNormanOnce:
	.string "{CHN}我曾经和千里对战过一次，不过，呼，\n"
	.string "他实在太强了。\p"
	.string "怎么形容呢？\p"
	.string "我只是觉得\n"
	.string "他简直是为宝可梦而生的。$"

