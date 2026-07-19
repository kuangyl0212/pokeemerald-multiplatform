SootopolisCity_House3_MapScripts::
	.byte 0

SootopolisCity_House3_EventScript_Woman::
	lock
	faceplayer
	msgbox SootopolisCity_House3_Text_JuanHasManyFansDoYou, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SootopolisCity_House3_EventScript_HaveFans
	msgbox SootopolisCity_House3_Text_LonesomeTryWorkingHarder, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House3_EventScript_HaveFans::
	msgbox SootopolisCity_House3_Text_YouMustBePrettyStrong, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House3_EventScript_Girl::
	msgbox SootopolisCity_House3_Text_TrainerFanClubWasWild, MSGBOX_NPC
	end

SootopolisCity_House3_Text_JuanHasManyFansDoYou:
	.string "{CHN}你是宝可梦训练家，对吧？\p"
	.string "琉璃市的亚当有很多粉丝。\n"
	.string "甚至比他的学生米可利还多！\p"
	.string "你有粉丝吗？$"

SootopolisCity_House3_Text_YouMustBePrettyStrong:
	.string "{CHN}哦，那你一定很厉害了。$"

SootopolisCity_House3_Text_LonesomeTryWorkingHarder:
	.string "{CHN}哎呀……\n"
	.string "那有点寂寞呢。\p"
	.string "再努力一下，争取\n"
	.string "有粉丝追随你吧。$"

SootopolisCity_House3_Text_TrainerFanClubWasWild:
	.string "{CHN}连丰缘以外的\n"
	.string "地方都有狂热粉丝过来。\p"
	.string "我去彩幽市的训练家粉丝俱乐部时，\n"
	.string "那里真的热闹非凡。$"

