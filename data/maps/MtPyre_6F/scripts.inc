MtPyre_6F_MapScripts::
	.byte 0

MtPyre_6F_EventScript_Valerie::
	trainerbattle_single TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieIntro, MtPyre_6F_Text_ValerieDefeat, MtPyre_6F_EventScript_RegisterValerie
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtPyre_6F_EventScript_RematchValerie
	msgbox MtPyre_6F_Text_ValeriePostBattle, MSGBOX_DEFAULT
	release
	end

MtPyre_6F_EventScript_RegisterValerie::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtPyre_6F_Text_ValerieRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_VALERIE_1
	release
	end

MtPyre_6F_EventScript_RematchValerie::
	trainerbattle_rematch TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieRematchIntro, MtPyre_6F_Text_ValerieRematchDefeat
	msgbox MtPyre_6F_Text_ValeriePostRematch, MSGBOX_AUTOCLOSE
	end

MtPyre_6F_EventScript_Cedric::
	trainerbattle_single TRAINER_CEDRIC, MtPyre_6F_Text_CedricIntro, MtPyre_6F_Text_CedricDefeat
	msgbox MtPyre_6F_Text_CedricPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_6F_Text_ValerieIntro:
	.string "{CHN}当我在这里时……\n"
	.string "一股奇妙的力量涌入我的体内……$"

MtPyre_6F_Text_ValerieDefeat:
	.string "{CHN}那股力量正在消退……$"

MtPyre_6F_Text_ValeriePostBattle:
	.string "{CHN}也许那力量来自\n"
	.string "在此辗转难眠的宝可梦的灵魂……$"

MtPyre_6F_Text_ValerieRegister:
	.string "{CHN}呼呼呼……我虽然输了，\n"
	.string "但我有这个小本事……\p"
	.string "不用碰你的宝可梦导航器……\n"
	.string "嘿呀！$"

MtPyre_6F_Text_ValerieRematchIntro:
	.string "{CHN}你身后……\n"
	.string "是什么……$"

MtPyre_6F_Text_ValerieRematchDefeat:
	.string "{CHN}有什么东西消失了……$"

MtPyre_6F_Text_ValeriePostRematch:
	.string "{CHN}安息在这里的宝可梦……\n"
	.string "有时会出来玩耍……$"

MtPyre_6F_Text_CedricIntro:
	.string "{CHN}你迷路了吗？\n"
	.string "别怕，有我在！$"

MtPyre_6F_Text_CedricDefeat:
	.string "{CHN}你不是迷路了吗？$"

MtPyre_6F_Text_CedricPostBattle:
	.string "{CHN}我原本以为迷路的训练家\n"
	.string "会慌张，容易打败。\p"
	.string "这种做法太卑鄙了，我不会再犯了……$"

