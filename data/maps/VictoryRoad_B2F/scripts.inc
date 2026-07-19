VictoryRoad_B2F_MapScripts::
	.byte 0

VictoryRoad_B2F_EventScript_Vito::
	trainerbattle_single TRAINER_VITO, VictoryRoad_B2F_Text_VitoIntro, VictoryRoad_B2F_Text_VitoDefeat
	msgbox VictoryRoad_B2F_Text_VitoPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Owen::
	trainerbattle_single TRAINER_OWEN, VictoryRoad_B2F_Text_OwenIntro, VictoryRoad_B2F_Text_OwenDefeat
	msgbox VictoryRoad_B2F_Text_OwenPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Caroline::
	trainerbattle_single TRAINER_CAROLINE, VictoryRoad_B2F_Text_CarolineIntro, VictoryRoad_B2F_Text_CarolineDefeat
	msgbox VictoryRoad_B2F_Text_CarolinePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Julie::
	trainerbattle_single TRAINER_JULIE, VictoryRoad_B2F_Text_JulieIntro, VictoryRoad_B2F_Text_JulieDefeat
	msgbox VictoryRoad_B2F_Text_JuliePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Felix::
	trainerbattle_single TRAINER_FELIX, VictoryRoad_B2F_Text_FelixIntro, VictoryRoad_B2F_Text_FelixDefeat
	msgbox VictoryRoad_B2F_Text_FelixPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Dianne::
	trainerbattle_single TRAINER_DIANNE, VictoryRoad_B2F_Text_DianneIntro, VictoryRoad_B2F_Text_DianneDefeat
	msgbox VictoryRoad_B2F_Text_DiannePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_Text_VitoIntro:
	.string "{CHN}我和全家人一起训练，\n"
	.string "我们每一个人都是！\l"
	.string "我不会输给任何人的！$"

VictoryRoad_B2F_Text_VitoDefeat:
	.string "{CHN}比我的家人还强？！\n"
	.string "这怎么可能？！$"

VictoryRoad_B2F_Text_VitoPostBattle:
	.string "{CHN}我比家里的任何人都强。\n"
	.string "我从来没输过……\p"
	.string "我失去了自信……\n"
	.string "也许我该回家了……$"

VictoryRoad_B2F_Text_OwenIntro:
	.string "{CHN}我听说这里有个厉害的小鬼。\n"
	.string "他们说的是你吗？$"

VictoryRoad_B2F_Text_OwenDefeat:
	.string "{CHN}这小鬼真厉害！$"

VictoryRoad_B2F_Text_OwenPostBattle:
	.string "{CHN}我听到的传言中，那个厉害的小鬼\n"
	.string "来自橙华市。$"

VictoryRoad_B2F_Text_CarolineIntro:
	.string "{CHN}你一定有点累了吧。$"

VictoryRoad_B2F_Text_CarolineDefeat:
	.string "{CHN}完全看不出有疲倦的迹象！$"

VictoryRoad_B2F_Text_CarolinePostBattle:
	.string "{CHN}冠军之路和宝可梦联盟\n"
	.string "是漫长而艰苦的挑战。\l"
	.string "要小心疲劳！$"

VictoryRoad_B2F_Text_JulieIntro:
	.string "{CHN}你不应该因为有很多道馆徽章\n"
	.string "就自满。\p"
	.string "总会有人\n"
	.string "比你更强！$"

VictoryRoad_B2F_Text_JulieDefeat:
	.string "{CHN}你比我强！$"

VictoryRoad_B2F_Text_JuliePostBattle:
	.string "{CHN}凝视你收集的徽章，\n"
	.string "回忆你遇到过的训练家吧。$"

VictoryRoad_B2F_Text_FelixIntro:
	.string "{CHN}我走到这里了，但紧张得\n"
	.string "胃疼得厉害……$"

VictoryRoad_B2F_Text_FelixDefeat:
	.string "{CHN}呜……\n"
	.string "好痛……$"

VictoryRoad_B2F_Text_FelixPostBattle:
	.string "{CHN}一想到快到宝可梦联盟了，\n"
	.string "我就忍不住紧张。\p"
	.string "我只能强装镇定。$"

VictoryRoad_B2F_Text_DianneIntro:
	.string "{CHN}精英中的精英都聚集在\n"
	.string "这个洞窟里。\p"
	.string "你觉得怎么样？$"

VictoryRoad_B2F_Text_DianneDefeat:
	.string "{CHN}一点都不慌乱！$"

VictoryRoad_B2F_Text_DiannePostBattle:
	.string "{CHN}你真有胆量！我喜欢！\n"
	.string "继续保持！$"
