CaveOfOrigin_B1F_MapScripts::
	.byte 0

CaveOfOrigin_B1F_EventScript_Wallace::
	lock
	faceplayer
	msgbox CaveOfOrigin_B1F_Text_WallaceStory, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CAVE_OF_ORIGIN_WALLACE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 60
	playse SE_PIN
	applymovement LOCALID_CAVE_OF_ORIGIN_WALLACE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_CAVE_OF_ORIGIN_WALLACE, Common_Movement_Delay48
	waitmovement 0
	delay 30
	applymovement LOCALID_CAVE_OF_ORIGIN_WALLACE, Common_Movement_FacePlayer
	waitmovement 0
	message CaveOfOrigin_B1F_Text_WhereIsRayquaza
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_WheresRayquaza::
	multichoice 0, 0, MULTI_WHERES_RAYQUAZA, FALSE
	switch VAR_RESULT
	case 0, CaveOfOrigin_B1F_EventScript_AtCaveOfOrigin
	case 1, CaveOfOrigin_B1F_EventScript_AtMtPyre
	case 2, CaveOfOrigin_B1F_EventScript_AtSkyPillar
	case 3, CaveOfOrigin_B1F_EventScript_DontRemember
	goto CaveOfOrigin_B1F_EventScript_DontRemember
	end

CaveOfOrigin_B1F_EventScript_AtCaveOfOrigin::
	message CaveOfOrigin_B1F_Text_ButWereInCaveOfOrigin
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_AtMtPyre::
	message CaveOfOrigin_B1F_Text_OldLadyDidntMentionThat
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_DontRemember::
	message CaveOfOrigin_B1F_Text_CantYouRememberSomehow
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_AtSkyPillar::
	msgbox CaveOfOrigin_B1F_Text_WellHeadToSkyPillar, MSGBOX_DEFAULT
	closemessage
	playse SE_EXIT
	fadescreenspeed FADE_TO_BLACK, 4
	setflag FLAG_WALLACE_GOES_TO_SKY_PILLAR
	setvar VAR_SOOTOPOLIS_CITY_STATE, 3
	removeobject LOCALID_CAVE_OF_ORIGIN_WALLACE
	clearflag FLAG_HIDE_SKY_PILLAR_WALLACE
	fadescreen FADE_FROM_BLACK
	release
	end

CaveOfOrigin_B1F_Text_WallaceStory:
	.string "{CHN}啊，你就是{PLAYER}{KUN}？\n"
	.string "我听说过你的事迹。\p"
	.string "我叫米可利。\p"
	.string "我曾是琉璃市的道馆馆主，\n"
	.string "但出了点事。\p"
	.string "所以现在，我把道馆\n"
	.string "交给了我的师父阿旦。\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "固拉多和盖欧卡，这两只\n"
	.string "在这里大闹的宝可梦，\l"
	.string "被认为是超古代宝可梦。\p"
	.string "但超古代\n"
	.string "宝可梦不只有两只。\p"
	.string "还有一只在某处。\p"
	.string "在某处，有一只名为\n"
	.string "烈空坐的超古代宝可梦。\p"
	.string "据说在遥远的过去，\n"
	.string "是烈空坐平息了\l"
	.string "这两只战斗的宝可梦。\p"
	.string "但连我也不知道\n"
	.string "烈空坐的下落…$"

CaveOfOrigin_B1F_Text_WhereIsRayquaza:
	.string "{CHN}米可利：{PLAYER}{KUN}，你\n"
	.string "也许知道烈空坐现在在哪？\p"
	.string "如果知道，请告诉我。$"

CaveOfOrigin_B1F_Text_ButWereInCaveOfOrigin:
	.string "{CHN}米可利：起源洞穴？\p"
	.string "但这里就是起源洞穴啊！\n"
	.string "你得想个更好的答案！\p"
	.string "拜托，好好想想\n"
	.string "烈空坐现在可能在哪里。$"

CaveOfOrigin_B1F_Text_OldLadyDidntMentionThat:
	.string "{CHN}米可利：送火山？\p"
	.string "但我之前在那里遇到老奶奶时，\n"
	.string "她没提到这件事。\p"
	.string "我很难相信老奶奶\n"
	.string "会想瞒着我什么…\p"
	.string "{PLAYER}{KUN}，你能再\n"
	.string "仔细想想吗？$"

CaveOfOrigin_B1F_Text_CantYouRememberSomehow:
	.string "{CHN}米可利：啊？你不记得了？\n"
	.string "嗯… 这就麻烦了…\p"
	.string "你就不能想起来吗？$"

CaveOfOrigin_B1F_Text_WellHeadToSkyPillar:
	.string "{CHN}米可利：天空之柱？\p"
	.string "就是它！\n"
	.string "一定是天空之柱！\p"
	.string "{PLAYER}{KUN}，一刻也不能耽搁！\n"
	.string "我们马上去天空之柱！$"
