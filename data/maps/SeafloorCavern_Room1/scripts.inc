SeafloorCavern_Room1_MapScripts::
	.byte 0

SeafloorCavern_Room1_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_1, SeafloorCavern_Room1_Text_Grunt1Intro, SeafloorCavern_Room1_Text_Grunt1Defeat
	msgbox SeafloorCavern_Room1_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room1_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_2, SeafloorCavern_Room1_Text_Grunt2Intro, SeafloorCavern_Room1_Text_Grunt2Defeat
	msgbox SeafloorCavern_Room1_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room1_Text_Grunt1Intro:
	.string "{CHN}我们这里不需要小孩！\n"
	.string "快回家去吧！$"

SeafloorCavern_Room1_Text_Grunt1Defeat:
	.string "{CHN}我想回家…$"

SeafloorCavern_Room1_Text_Grunt1PostBattle:
	.string "{CHN}我想升职，这样\n"
	.string "就能指挥队员了…$"

SeafloorCavern_Room1_Text_Grunt2Intro:
	.string "{CHN}那艘潜水艇… 里面太挤了。\n"
	.string "我浑身都酸痛！$"

SeafloorCavern_Room1_Text_Grunt2Defeat:
	.string "{CHN}输了更酸痛了！$"

SeafloorCavern_Room1_Text_Grunt2PostBattle:
	.string "{CHN}我们抢来的那艘潜水艇，天哪，\n"
	.string "坐起来真要命。\l"
	.string "里面太挤了！$"
