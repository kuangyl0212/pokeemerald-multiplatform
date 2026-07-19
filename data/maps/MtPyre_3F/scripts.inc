MtPyre_3F_MapScripts::
	.byte 0

MtPyre_3F_EventScript_William::
	trainerbattle_single TRAINER_WILLIAM, MtPyre_3F_Text_WilliamIntro, MtPyre_3F_Text_WilliamDefeat
	msgbox MtPyre_3F_Text_WilliamPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_EventScript_Kayla::
	trainerbattle_single TRAINER_KAYLA, MtPyre_3F_Text_KaylaIntro, MtPyre_3F_Text_KaylaDefeat
	msgbox MtPyre_3F_Text_KaylaPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_EventScript_Gabrielle::
	trainerbattle_single TRAINER_GABRIELLE_1, MtPyre_3F_Text_GabrielleIntro, MtPyre_3F_Text_GabrielleDefeat, MtPyre_3F_EventScript_RegisterGabrielle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtPyre_3F_EventScript_RematchGabrielle
	msgbox MtPyre_3F_Text_GabriellePostBattle, MSGBOX_DEFAULT
	release
	end

MtPyre_3F_EventScript_RegisterGabrielle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtPyre_3F_Text_GabrielleRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_GABRIELLE_1
	release
	end

MtPyre_3F_EventScript_RematchGabrielle::
	trainerbattle_rematch TRAINER_GABRIELLE_1, MtPyre_3F_Text_GabrielleRematchIntro, MtPyre_3F_Text_GabrielleRematchDefeat
	msgbox MtPyre_3F_Text_GabriellePostRematch, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_Text_WilliamIntro:
	.string "{CHN}这座山上浓郁的灵气\n"
	.string "提升了我的超能力！\p"
	.string "像你这样的小孩子……\n"
	.string "还妄想获胜吗？$"

MtPyre_3F_Text_WilliamDefeat:
	.string "{CHN}我陷入自怜之中……$"

MtPyre_3F_Text_WilliamPostBattle:
	.string "{CHN}我的超能力确实\n"
	.string "增长了好几倍，但是……$"

MtPyre_3F_Text_KaylaIntro:
	.string "{CHN}啊哈哈哈！\p"
	.string "这里可不是小孩子来的地方，\n"
	.string "尤其是你！$"

MtPyre_3F_Text_KaylaDefeat:
	.string "{CHN}我输得心服口服……$"

MtPyre_3F_Text_KaylaPostBattle:
	.string "{CHN}这说明我的修行\n"
	.string "还不够……\p"
	.string "我必须继续朝着\n"
	.string "山顶努力……\p"
	.string "加油，我自己！$"

MtPyre_3F_Text_GabrielleIntro:
	.string "{CHN}你为什么来这里？$"

MtPyre_3F_Text_GabrielleDefeat:
	.string "{CHN}太厉害了！\n"
	.string "你是个非常特别的训练家。$"

MtPyre_3F_Text_GabriellePostBattle:
	.string "{CHN}已经离开这个世界的宝可梦。\n"
	.string "现在陪在你身边的宝可梦。\p"
	.string "还有你将来会遇到的宝可梦……\p"
	.string "它们都同样值得珍惜。\n"
	.string "请记住这一点。$"

MtPyre_3F_Text_GabrielleRegister:
	.string "{CHN}我想看看你的宝可梦\n"
	.string "再长大一些的样子……\p"
	.string "请让我看看你的宝可梦导航器。$"

MtPyre_3F_Text_GabrielleRematchIntro:
	.string "{CHN}哦，是你啊……\p"
	.string "你是来给我看你长大了\n"
	.string "的宝可梦的吗？$"

MtPyre_3F_Text_GabrielleRematchDefeat:
	.string "{CHN}太厉害了！\n"
	.string "你是个特别的人。$"

MtPyre_3F_Text_GabriellePostRematch:
	.string "{CHN}已经离开这个世界的宝可梦。\n"
	.string "现在陪在你身边的宝可梦。\p"
	.string "还有你将来会遇到的宝可梦……\p"
	.string "它们都同样值得珍惜。\n"
	.string "看来你已经记住了这一点。$"

