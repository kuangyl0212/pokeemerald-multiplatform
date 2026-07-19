MeteorFalls_StevensCave_MapScripts::
	.byte 0

MeteorFalls_StevensCave_EventScript_Steven::
	lock
	goto_if_set FLAG_DEFEATED_METEOR_FALLS_STEVEN, MeteorFalls_StevensCave_EventScript_Defeated
	waitse
	playse SE_PIN
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STEVEN, MeteorFalls_StevensCave_Text_StevenDefeat
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_METEOR_FALLS_STEVEN
	release
	end

MeteorFalls_StevensCave_EventScript_Defeated::
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	release
	end

MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst:
	.string "{CHN}大吾：哦，哇，{PLAYER}{KUN}。\n"
	.string "我真惊讶你知道在哪里能找到我。\p"
	.string "你，呃……是不是把我\n"
	.string "当成石头迷了？\p"
	.string "不，那不可能。\p"
	.string "我们在暮水镇宇宙中心\n"
	.string "并肩作战过。\p"
	.string "你应该非常清楚\n"
	.string "我有多厉害。\p"
	.string "好吧，{PLAYER}{KUN}，如果你要发起认真的挑战，\n"
	.string "那就做好最坏的打算吧！$"

MeteorFalls_StevensCave_Text_StevenDefeat:
	.string "{CHN}你……\n"
	.string "我没想到你变得这么强……$"

MeteorFalls_StevensCave_Text_MyPredictionCameTrue:
	.string "{CHN}大吾：回想起来，自从我们在武斗镇的\n"
	.string "石之洞窟初次相遇，\l"
	.string "我就有这种感觉。\p"
	.string "我觉得你最终\n"
	.string "会成为冠军。\p"
	.string "我的预测通常会成真。\p"
	.string "那你接下来要去哪里？\p"
	.string "………………\n"
	.string "………………\p"
	.string "呼呼呼，这个连我也没法告诉你。$"
