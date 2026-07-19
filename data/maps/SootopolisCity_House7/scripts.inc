SootopolisCity_House7_MapScripts::
	.byte 0

SootopolisCity_House7_EventScript_OldMan::
	msgbox SootopolisCity_House7_Text_CityFromEruptedVolcano, MSGBOX_NPC
	end

SootopolisCity_House7_EventScript_PokefanF::
	msgbox SootopolisCity_House7_Text_CaveMadeToKeepSomething, MSGBOX_NPC
	end

SootopolisCity_House7_Text_CityFromEruptedVolcano:
	.string "{CHN}海底火山喷发，\n"
	.string "从深处向上涌出。\p"
	.string "火山口从海面露出，\n"
	.string "积满了雨水。\p"
	.string "琉璃市就是这样\n"
	.string "形成的。$"

SootopolisCity_House7_Text_CaveMadeToKeepSomething:
	.string "{CHN}连接琉璃市和\n"
	.string "外界的那个洞窟……\p"
	.string "仿佛是为了不让\n"
	.string "什么东西出去而建造的。\p"
	.string "还是说只是我的错觉？$"

