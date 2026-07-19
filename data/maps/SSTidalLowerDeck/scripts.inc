SSTidalLowerDeck_MapScripts::
	.byte 0

SSTidalLowerDeck_EventScript_Phillip::
	trainerbattle_single TRAINER_PHILLIP, SSTidalLowerDeck_Text_PhillipIntro, SSTidalLowerDeck_Text_PhillipDefeat
	msgbox SSTidalLowerDeck_Text_PhillipPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalLowerDeck_EventScript_Leonard::
	trainerbattle_single TRAINER_LEONARD, SSTidalLowerDeck_Text_LeonardIntro, SSTidalLowerDeck_Text_LeonardDefeat
	msgbox SSTidalLowerDeck_Text_LeonardPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalLowerDeck_Text_PhillipIntro:
	.string "{CHN}啊——！我受够了也累坏了，\n"
	.string "打扫这么大的地方！\p"
	.string "来快速打一场吧！$"

SSTidalLowerDeck_Text_PhillipDefeat:
	.string "{CHN}弟弟，我输了！$"

SSTidalLowerDeck_Text_PhillipPostBattle:
	.string "{CHN}我们是清扫兄弟！\p"
	.string "哥哥倒洗涤剂，\n"
	.string "弟弟负责刷洗！$"

SSTidalLowerDeck_Text_LeonardIntro:
	.string "{CHN}这是船舱的最底层。\n"
	.string "这里空间很大。\l"
	.string "用来打宝可梦对战没问题。$"

SSTidalLowerDeck_Text_LeonardDefeat:
	.string "{CHN}哥哥，我输了！$"

SSTidalLowerDeck_Text_LeonardPostBattle:
	.string "{CHN}我们是清扫兄弟！\p"
	.string "哥哥倒洗涤剂，\n"
	.string "弟弟负责刷洗！$"
