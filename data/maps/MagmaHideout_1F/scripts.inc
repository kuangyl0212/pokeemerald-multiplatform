MagmaHideout_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MagmaHideout_1F_OnTransition
	.byte 0

MagmaHideout_1F_OnTransition:
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 0
	end

MagmaHideout_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_1, MagmaHideout_1F_Text_Grunt1Intro, MagmaHideout_1F_Text_Grunt1Defeat
	msgbox MagmaHideout_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_2, MagmaHideout_1F_Text_Grunt2Intro, MagmaHideout_1F_Text_Grunt2Defeat
	msgbox MagmaHideout_1F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_Text_Grunt1Intro:
	.string "{CHN}火焰队点名时，我们\n"
	.string "按排队的顺序\l"
	.string "得到重要的守卫任务。\p"
	.string "所以我才被扔在这个角落。\n"
	.string "我点名总是迟到！$"

MagmaHideout_1F_Text_Grunt1Defeat:
	.string "{CHN}我训练也总是\n"
	.string "迟到！\p"
	.string "我不愿意承认，但我很弱…$"

MagmaHideout_1F_Text_Grunt1PostBattle:
	.string "{CHN}好吧，以后我会\n"
	.string "多努力一点的…$"

MagmaHideout_1F_Text_Grunt2Intro:
	.string "{CHN}我们的首领让我们挖进\n"
	.string "烟突山，我们就挖啊挖。\p"
	.string "在挖掘的过程中，我们\n"
	.string "发现了令人震惊的东西！\p"
	.string "我们发现了什么？\p"
	.string "呼哈哈哈！\n"
	.string "你打赢我我就告诉你！$"

MagmaHideout_1F_Text_Grunt2Defeat:
	.string "{CHN}啊！\n"
	.string "被打倒了！$"

MagmaHideout_1F_Text_Grunt2PostBattle:
	.string "{CHN}我毕竟还是不告诉你。\n"
	.string "你到了那里就知道了！\p"
	.string "把惊喜留到最后\n"
	.string "不是更好吗，你不觉得吗？$"
