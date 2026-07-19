MeteorFalls_1F_2R_MapScripts::
	.byte 0

MeteorFalls_1F_2R_EventScript_Nicolas::
	trainerbattle_single TRAINER_NICOLAS_1, MeteorFalls_1F_2R_Text_NicolasIntro, MeteorFalls_1F_2R_Text_NicolasDefeat, MeteorFalls_1F_2R_EventScript_RegisterNicolas
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MeteorFalls_1F_2R_EventScript_RematchNicolas
	msgbox MeteorFalls_1F_2R_Text_NicolasPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterNicolas::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MeteorFalls_1F_2R_Text_NicolasRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_NICOLAS_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchNicolas::
	trainerbattle_rematch TRAINER_NICOLAS_1, MeteorFalls_1F_2R_Text_NicolasRematchIntro, MeteorFalls_1F_2R_Text_NicolasRematchDefeat
	msgbox MeteorFalls_1F_2R_Text_NicolasPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_EventScript_John::
	trainerbattle_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JohnIntro, MeteorFalls_1F_2R_Text_JohnDefeat, MeteorFalls_1F_2R_Text_JohnNotEnoughMons, MeteorFalls_1F_2R_EventScript_RegisterJohn
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MeteorFalls_1F_2R_EventScript_RematchJohn
	msgbox MeteorFalls_1F_2R_Text_JohnPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterJohn::
	msgbox MeteorFalls_1F_2R_Text_JohnRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOHN_AND_JAY_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchJohn::
	trainerbattle_rematch_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JohnRematchIntro, MeteorFalls_1F_2R_Text_JohnRematchDefeat, MeteorFalls_1F_2R_Text_JohnRematchNotEnoughMons
	msgbox MeteorFalls_1F_2R_Text_JohnPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_EventScript_Jay::
	trainerbattle_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JayIntro, MeteorFalls_1F_2R_Text_JayDefeat, MeteorFalls_1F_2R_Text_JayNotEnoughMons, MeteorFalls_1F_2R_EventScript_RegisterJay
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MeteorFalls_1F_2R_EventScript_RematchJay
	msgbox MeteorFalls_1F_2R_Text_JayPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterJay::
	msgbox MeteorFalls_1F_2R_Text_JohnRegister, MSGBOX_DEFAULT  /* John speaks for both during register*/
	register_matchcall TRAINER_JOHN_AND_JAY_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchJay::
	trainerbattle_rematch_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JayRematchIntro, MeteorFalls_1F_2R_Text_JayRematchDefeat, MeteorFalls_1F_2R_Text_JayRematchNotEnoughMons
	msgbox MeteorFalls_1F_2R_Text_JayPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_Text_NicolasIntro:
	.string "{CHN}这是我们龙属性宝可梦使用者\n"
	.string "训练的地方。\p"
	.string "冠军都会来。\n"
	.string "现在你知道这里有多特别了吧？$"

MeteorFalls_1F_2R_Text_NicolasDefeat:
	.string "{CHN}呃啊！\n"
	.string "没想到你这么强！$"

MeteorFalls_1F_2R_Text_NicolasPostBattle:
	.string "{CHN}前方的路还很长、很艰苦。\p"
	.string "我和我的宝可梦什么时候才能\n"
	.string "成为最强的？$"

MeteorFalls_1F_2R_Text_NicolasRegister:
	.string "{CHN}我想更多地了解你的实力。\n"
	.string "让我把你登录到我的宝可梦领航员里吧。$"

MeteorFalls_1F_2R_Text_NicolasRematchIntro:
	.string "{CHN}自从我们相遇后，我们就以\n"
	.string "第一为目标努力训练。\p"
	.string "帮我们看看我们变得\n"
	.string "多强了吧！$"

MeteorFalls_1F_2R_Text_NicolasRematchDefeat:
	.string "{CHN}呃啊！\n"
	.string "没想到你这么强！$"

MeteorFalls_1F_2R_Text_NicolasPostRematch:
	.string "{CHN}你显然一直在坚持\n"
	.string "宝可梦训练。\p"
	.string "只要你保持强大，我也能\n"
	.string "变得更强！$"

MeteorFalls_1F_2R_Text_JohnIntro:
	.string "{CHN}约翰：我们一直作为夫妻搭档\n"
	.string "一起对战宝可梦。\l"
	.string "我们对自己有信心。$"

MeteorFalls_1F_2R_Text_JohnDefeat:
	.string "{CHN}约翰：哦，天哪。\n"
	.string "我们输了，亲爱的妻子。$"

MeteorFalls_1F_2R_Text_JohnPostBattle:
	.string "{CHN}约翰：我们结婚\n"
	.string "五十年了。\p"
	.string "回想起来，我还没在战斗中\n"
	.string "赢过我亲爱的妻子呢。$"

MeteorFalls_1F_2R_Text_JohnNotEnoughMons:
	.string "{CHN}约翰：哎呀，多么年轻的训练家！\p"
	.string "你要和我们战斗吗？如果要，\n"
	.string "你需要带更多的宝可梦回来。$"

MeteorFalls_1F_2R_Text_JohnRegister:
	.string "{CHN}约翰：年轻的训练家，如果有\n"
	.string "机会，你愿意再和我们战斗吗？$"

MeteorFalls_1F_2R_Text_JayIntro:
	.string "{CHN}杰伊：我们结婚\n"
	.string "五十年了。\p"
	.string "我们作为夫妻的纽带\n"
	.string "永远不会被打破。$"

MeteorFalls_1F_2R_Text_JayDefeat:
	.string "{CHN}杰伊：哦，亲爱的。\n"
	.string "我们输了，亲爱的丈夫。$"

MeteorFalls_1F_2R_Text_JayPostBattle:
	.string "{CHN}杰伊：五十年的婚姻……\p"
	.string "如果我们吵架了，我们总是\n"
	.string "用宝可梦战斗来解决……$"

MeteorFalls_1F_2R_Text_JayNotEnoughMons:
	.string "{CHN}杰伊：哎呀，你是个年轻的\n"
	.string "训练家啊？\p"
	.string "如果你想和我们战斗，\n"
	.string "你需要带更多的宝可梦回来。$"

MeteorFalls_1F_2R_Text_JohnRematchIntro:
	.string "{CHN}约翰：我们一直作为夫妻搭档\n"
	.string "一起对战宝可梦。\l"
	.string "我们对自己有信心。$"

MeteorFalls_1F_2R_Text_JohnRematchDefeat:
	.string "{CHN}约翰：哦，天哪。\n"
	.string "我们输了，亲爱的妻子。$"

MeteorFalls_1F_2R_Text_JohnPostRematch:
	.string "{CHN}约翰：结婚五十年……\p"
	.string "回想起来，亲爱的妻子和我，\n"
	.string "我们天天都在战斗……$"

MeteorFalls_1F_2R_Text_JohnRematchNotEnoughMons:
	.string "{CHN}约翰：哎呀，多么年轻的训练家！\p"
	.string "你要和我们战斗吗？如果要，\n"
	.string "你需要带更多的宝可梦回来。$"

MeteorFalls_1F_2R_Text_JayRematchIntro:
	.string "{CHN}杰伊：我们结婚\n"
	.string "五十年了。\p"
	.string "我们一直互相支持。\n"
	.string "我们让自己变得强大。$"

MeteorFalls_1F_2R_Text_JayRematchDefeat:
	.string "{CHN}杰伊：哦，亲爱的。\n"
	.string "我们输了，亲爱的丈夫。$"

MeteorFalls_1F_2R_Text_JayPostRematch:
	.string "{CHN}杰伊：五十年的婚姻……\n"
	.string "发生了很多事。\p"
	.string "我希望我们能继续\n"
	.string "一起创造快乐的回忆。$"

MeteorFalls_1F_2R_Text_JayRematchNotEnoughMons:
	.string "{CHN}杰伊：哎呀，你是个年轻的\n"
	.string "训练家啊？\p"
	.string "如果你想和我们战斗，\n"
	.string "你需要带更多的宝可梦回来。$"
