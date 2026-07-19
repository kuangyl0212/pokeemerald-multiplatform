VerdanturfTown_House_MapScripts::
	.byte 0

VerdanturfTown_House_EventScript_Woman1::
	msgbox VerdanturfTown_House_Text_TrainersGatherAtPokemonLeague, MSGBOX_NPC
	end

VerdanturfTown_House_EventScript_Woman2::
	msgbox VerdanturfTown_House_Text_DefeatEliteFourInARow, MSGBOX_NPC
	end

VerdanturfTown_House_Text_TrainersGatherAtPokemonLeague:
	.string "{CHN}在遥远的彩幽市深处，\n"
	.string "就是宝可梦联盟。\p"
	.string "聚集在那里的训练家\n"
	.string "都拥有令人恐惧的高超技艺。$"

VerdanturfTown_House_Text_DefeatEliteFourInARow:
	.string "{CHN}在宝可梦联盟，我记得\n"
	.string "规则是必须连续挑战\l"
	.string "四天王。\p"
	.string "如果输给其中任何一个，就必须\n"
	.string "从第一个开始重新\l"
	.string "挑战。$"

