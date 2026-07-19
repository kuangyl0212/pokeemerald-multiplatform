PetalburgCity_House1_MapScripts::
	.byte 0

PetalburgCity_House1_EventScript_Man::
	msgbox PetalburgCity_House1_Text_TravelingIsWonderful, MSGBOX_NPC
	end

PetalburgCity_House1_EventScript_Woman::
	msgbox PetalburgCity_House1_Text_GoOnAdventure, MSGBOX_NPC
	end

PetalburgCity_House1_Text_TravelingIsWonderful:
	.string "{CHN}旅行真是太棒了！\p"
	.string "我年轻的时候，\n"
	.string "走过大海和高山！$"

PetalburgCity_House1_Text_GoOnAdventure:
	.string "{CHN}唉……\p"
	.string "要是我能和\n"
	.string "宝可梦一起去冒险就好了……\p"
	.string "爬过潮湿的草丛……\n"
	.string "攀越崎岖的山岭……\p"
	.string "横渡汹涌的大海……\n"
	.string "在漆黑的洞窟里徘徊……\p"
	.string "偶尔，也会有点\n"
	.string "想家……\p"
	.string "能去旅行一定很棒！$"

