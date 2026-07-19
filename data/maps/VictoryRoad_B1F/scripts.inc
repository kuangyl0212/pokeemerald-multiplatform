VictoryRoad_B1F_MapScripts::
	.byte 0

VictoryRoad_B1F_EventScript_Samuel::
	trainerbattle_single TRAINER_SAMUEL, VictoryRoad_B1F_Text_SamuelIntro, VictoryRoad_B1F_Text_SamuelDefeat
	msgbox VictoryRoad_B1F_Text_SamuelPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Shannon::
	trainerbattle_single TRAINER_SHANNON, VictoryRoad_B1F_Text_ShannonIntro, VictoryRoad_B1F_Text_ShannonDefeat
	msgbox VictoryRoad_B1F_Text_ShannonPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Michelle::
	trainerbattle_single TRAINER_MICHELLE, VictoryRoad_B1F_Text_MichelleIntro, VictoryRoad_B1F_Text_MichelleDefeat
	msgbox VictoryRoad_B1F_Text_MichellePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Mitchell::
	trainerbattle_single TRAINER_MITCHELL, VictoryRoad_B1F_Text_MitchellIntro, VictoryRoad_B1F_Text_MitchellDefeat
	msgbox VictoryRoad_B1F_Text_MitchellPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Halle::
	trainerbattle_single TRAINER_HALLE, VictoryRoad_B1F_Text_HalleIntro, VictoryRoad_B1F_Text_HalleDefeat
	msgbox VictoryRoad_B1F_Text_HallePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_Text_SamuelIntro:
	.string "{CHN}一想到我离宝可梦联盟\n"
	.string "越来越近……\p"
	.string "我就开始怯场了……$"

VictoryRoad_B1F_Text_SamuelDefeat:
	.string "{CHN}我什么都没能做到……$"

VictoryRoad_B1F_Text_SamuelPostBattle:
	.string "{CHN}宝可梦联盟又变得\n"
	.string "遥不可及了……真让人失望……$"

VictoryRoad_B1F_Text_ShannonIntro:
	.string "{CHN}要闯过宝可梦联盟，\n"
	.string "你需要宝可梦\l"
	.string "对你的信任。$"

VictoryRoad_B1F_Text_ShannonDefeat:
	.string "{CHN}你们的关系建立在\n"
	.string "坚实的信任之上。$"

VictoryRoad_B1F_Text_ShannonPostBattle:
	.string "{CHN}通过朝夕相处，\n"
	.string "宝可梦和训练家之间的信任会不断加深。$"

VictoryRoad_B1F_Text_MichelleIntro:
	.string "{CHN}这里不是终点。这只是\n"
	.string "前往宝可梦联盟路上的一站。$"

VictoryRoad_B1F_Text_MichelleDefeat:
	.string "{CHN}就是这样！$"

VictoryRoad_B1F_Text_MichellePostBattle:
	.string "{CHN}你肯定没问题的！\n"
	.string "你的宝可梦都跃跃欲试呢！$"

VictoryRoad_B1F_Text_MitchellIntro:
	.string "{CHN}我的宝可梦简直\n"
	.string "宇宙无敌！$"

VictoryRoad_B1F_Text_MitchellDefeat:
	.string "{CHN}我从未遇到过像你这样的人。$"

VictoryRoad_B1F_Text_MitchellPostBattle:
	.string "{CHN}即使在战斗之外，我也能感受到\n"
	.string "从你和你的宝可梦身上\l"
	.string "散发出的惊人力量。$"

VictoryRoad_B1F_Text_HalleIntro:
	.string "{CHN}好了，别紧张！\n"
	.string "放轻松，我们慢慢来！$"

VictoryRoad_B1F_Text_HalleDefeat:
	.string "{CHN}哇！\n"
	.string "太精彩了！$"

VictoryRoad_B1F_Text_HallePostBattle:
	.string "{CHN}没错，这里是冠军之路。\p"
	.string "但它和你至今走过的路\n"
	.string "也没什么不同。\p"
	.string "剩下的路程，\n"
	.string "试着享受一下吧！$"
