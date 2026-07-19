Route114_LanettesHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_LanettesHouse_OnTransition
	.byte 0

Route114_LanettesHouse_OnTransition:
	setflag FLAG_LANDMARK_LANETTES_HOUSE
	end

Route114_LanettesHouse_EventScript_Lanette::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_DOLL_LANETTE, Route114_LanettesHouse_EventScript_OfferAdvice
	setflag FLAG_SYS_PC_LANETTE
	msgbox Route114_LanettesHouse_Text_EverythingClutteredKeepThis, MSGBOX_DEFAULT
	givedecoration DECOR_LOTAD_DOLL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowNoRoomForDecor
	setflag FLAG_RECEIVED_DOLL_LANETTE
	release
	end

Route114_LanettesHouse_EventScript_OfferAdvice::
	msgbox Route114_LanettesHouse_Text_OrganizeYourBoxes, MSGBOX_DEFAULT
	release
	end

Route114_LanettesHouse_EventScript_Notebook::
	lockall
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route114_LanettesHouse_EventScript_NotebookPage2
	msgbox Route114_LanettesHouse_Text_ClosedTheNotebook, MSGBOX_DEFAULT
	releaseall
	end

Route114_LanettesHouse_EventScript_NotebookPage2::
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage2, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, Route114_LanettesHouse_EventScript_NotebookPage3
	releaseall
	end

Route114_LanettesHouse_EventScript_NotebookPage3::
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage3, MSGBOX_DEFAULT
	return

Route114_LanettesHouse_EventScript_PC::
	msgbox Route114_LanettesHouse_Text_EmailFromBill, MSGBOX_SIGN
	end

Route114_LanettesHouse_Text_EverythingClutteredKeepThis:
	.string "{CHN}茱莉：哦！{PLAYER}{KUN}！\p"
	.string "抱歉一切都这么乱……\n"
	.string "当我沉浸于研究时，\l"
	.string "就会变成这样……\p"
	.string "太丢人了……请保守\n"
	.string "秘密，作为交换这个给你。$"

Route114_LanettesHouse_Text_OrganizeYourBoxes:
	.string "{CHN}我可以给你一些关于我的宝可梦\n"
	.string "储存系统的建议吗？\p"
	.string "你应该整理你的箱子，这样你\n"
	.string "就能知道里面装着哪些宝可梦。$"

Route114_LanettesHouse_Text_ResearchNotesPage1:
	.string "{CHN}这是茱莉的研究笔记。\n"
	.string "里面有关于箱子的信息。\p"
	.string "设计每个箱子可存放30只宝可梦。\p"
	.string "每个训练家应该能在PC系统\n"
	.string "里存放420只宝可梦。\p"
	.string "继续阅读吗？$"

Route114_LanettesHouse_Text_ResearchNotesPage2:
	.string "{CHN}应该加入标记系统，\n"
	.string "让宝可梦更容易整理。\p"
	.string "每个箱子的名称和壁纸设计\n"
	.string "都可以更改，让存放的\l"
	.string "宝可梦高兴。\p"
	.string "继续阅读吗？$"

Route114_LanettesHouse_Text_ResearchNotesPage3:
	.string "{CHN}存放宝可梦时，应该\n"
	.string "把它送到最近查看的箱子。\p"
	.string "如果那个箱子满了，收到的\n"
	.string "宝可梦就会被存到下一个箱子。\p"
	.string "也就是说，当你查看某个箱子时，\n"
	.string "它就会自动被选为\l"
	.string "存放宝可梦的箱子。$"

Route114_LanettesHouse_Text_ClosedTheNotebook:
	.string "{CHN}{PLAYER}合上了笔记本。$"

Route114_LanettesHouse_Text_EmailFromBill:
	.string "{CHN}PC上有一封\n"
	.string "某人发来的邮件。\p"
	.string "“… … … … … … …\p"
	.string "你的储存系统比我的\n"
	.string "更方便。\p"
	.string "它有很多用户友好的功能，\n"
	.string "既好玩又实用。\p"
	.string "能参与它的开发，\n"
	.string "我感到很自豪。\p"
	.string "希望你能继续\n"
	.string "储存系统的研究。\p"
	.string "——正辉\n"
	.string "… … … … … … … …”$"

