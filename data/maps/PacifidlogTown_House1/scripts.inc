PacifidlogTown_House1_MapScripts::
	.byte 0

PacifidlogTown_House1_EventScript_Man::
	msgbox PacifidlogTown_House1_Text_RegiStory, MSGBOX_NPC
	end

PacifidlogTown_House1_EventScript_Woman::
	msgbox PacifidlogTown_House1_Text_SixDotsOpenThreeDoors, MSGBOX_NPC
	end

PacifidlogTown_House1_Text_RegiStory:
	.string "{CHN}在丰缘地区，有三只\n"
	.string "代表岩石、冰和钢铁之力量的\l"
	.string "宝可梦。\p"
	.string "据说它们各自隐藏在\n"
	.string "深邃的洞穴之中。\p"
	.string "这是我小时候\n"
	.string "听来的故事。$"

PacifidlogTown_House1_Text_SixDotsOpenThreeDoors:
	.string "{CHN}“六点开三门。”\p"
	.string "爷爷过去常这么说，\n"
	.string "但我不知道他是什么意思。$"
