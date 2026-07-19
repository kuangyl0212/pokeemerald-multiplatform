SeafloorCavern_Room4_MapScripts::
	.byte 0

SeafloorCavern_Room4_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_3, SeafloorCavern_Room4_Text_Grunt3Intro, SeafloorCavern_Room4_Text_Grunt3Defeat
	msgbox SeafloorCavern_Room4_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room4_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_4, SeafloorCavern_Room4_Text_Grunt4Intro, SeafloorCavern_Room4_Text_Grunt4Defeat
	msgbox SeafloorCavern_Room4_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room4_Text_Grunt3Intro:
	.string "{CHN}你是谁？\n"
	.string "你从哪进来的？$"

SeafloorCavern_Room4_Text_Grunt3Defeat:
	.string "{CHN}输了…$"

SeafloorCavern_Room4_Text_Grunt3PostBattle:
	.string "{CHN}我找不到出路！\p"
	.string "我不是害怕。别误会！$"

SeafloorCavern_Room4_Text_Grunt4Intro:
	.string "{CHN}你是谁？\n"
	.string "你以为你要去哪？$"

SeafloorCavern_Room4_Text_Grunt4Defeat:
	.string "{CHN}我没能赢！$"

SeafloorCavern_Room4_Text_Grunt4PostBattle:
	.string "{CHN}我搭档把地图忘在\n"
	.string "那艘潜水艇里了！\p"
	.string "这叫什么猪队友？$"
