SeafloorCavern_Room3_MapScripts::
	.byte 0

SeafloorCavern_Room3_EventScript_Shelly::
	trainerbattle_single TRAINER_SHELLY_SEAFLOOR_CAVERN, SeafloorCavern_Room3_Text_ShellyIntro, SeafloorCavern_Room3_Text_ShellyDefeat
	msgbox SeafloorCavern_Room3_Text_ShellyPostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room3_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_5, SeafloorCavern_Room3_Text_Grunt5Intro, SeafloorCavern_Room3_Text_Grunt5Defeat
	msgbox SeafloorCavern_Room3_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room3_Text_ShellyIntro:
	.string "{CHN}啊哈哈哈哈！\p"
	.string "没有潜水艇你是怎么\n"
	.string "到这里来的？\l"
	.string "真是个了不起的孩子！\p"
	.string "但是… 不能让你\n"
	.string "在这里捣乱。\p"
	.string "而且，我想为\n"
	.string "气象研究所的事报仇…\p"
	.string "我要让你尝尝\n"
	.string "痛苦的滋味！认命吧！$"

SeafloorCavern_Room3_Text_ShellyDefeat:
	.string "{CHN}啊哈哈哈哈！\p"
	.string "好痛！$"

SeafloorCavern_Room3_Text_ShellyPostBattle:
	.string "{CHN}啊哈哈哈哈！\n"
	.string "你真是强得离谱。\p"
	.string "太遗憾了，你\n"
	.string "不是水舰队的队员。\p"
	.string "你本可以享受我们\n"
	.string "老大承诺的那个\l"
	.string "美妙世界…$"

SeafloorCavern_Room3_Text_Grunt5Intro:
	.string "{CHN}为了让梦想成真，我们需要\n"
	.string "宝可梦的力量。\p"
	.string "但像你这种多管闲事的人，\n"
	.string "居然在这种地方\l"
	.string "还用宝可梦的力量来捣乱！\p"
	.string "世事就是不如意！$"

SeafloorCavern_Room3_Text_Grunt5Defeat:
	.string "{CHN}呃啊！$"

SeafloorCavern_Room3_Text_Grunt5PostBattle:
	.string "{CHN}你知道吗，我们不敢\n"
	.string "质疑首领的动机。\p"
	.string "但你呢，只是个小鬼，\n"
	.string "却敢反抗我们老大。\p"
	.string "也许…\n"
	.string "你一定有什么了不起的…$"
