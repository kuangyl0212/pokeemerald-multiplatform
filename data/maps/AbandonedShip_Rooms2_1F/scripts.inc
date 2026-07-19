AbandonedShip_Rooms2_1F_MapScripts::
	.byte 0

AbandonedShip_Rooms2_1F_EventScript_Dan::
	trainerbattle_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_DanIntro, AbandonedShip_Rooms2_1F_Text_DanDefeat, AbandonedShip_Rooms2_1F_Text_DanNotEnoughMons, AbandonedShip_Rooms2_1F_EventScript_RegisterDan
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms2_1F_EventScript_DanRematch
	msgbox AbandonedShip_Rooms2_1F_Text_DanPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms2_1F_EventScript_RegisterDan::
	msgbox AbandonedShip_Rooms2_1F_Text_KiraRegister, MSGBOX_DEFAULT  /* Kira speaks for both when registering KiraAndDan*/
	register_matchcall TRAINER_KIRA_AND_DAN_1
	release
	end

AbandonedShip_Rooms2_1F_EventScript_DanRematch::
	trainerbattle_rematch_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_DanRematchIntro, AbandonedShip_Rooms2_1F_Text_DanRematchDefeat, AbandonedShip_Rooms2_1F_Text_DanRematchNotEnoughMons
	msgbox AbandonedShip_Rooms2_1F_Text_DanPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Kira::
	trainerbattle_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_KiraIntro, AbandonedShip_Rooms2_1F_Text_KiraDefeat, AbandonedShip_Rooms2_1F_Text_KiraNotEnoughMons, AbandonedShip_Rooms2_1F_EventScript_RegisterKira
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms2_1F_EventScript_KiraRematch
	msgbox AbandonedShip_Rooms2_1F_Text_KiraPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms2_1F_EventScript_RegisterKira::
	msgbox AbandonedShip_Rooms2_1F_Text_KiraRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_KIRA_AND_DAN_1
	release
	end

AbandonedShip_Rooms2_1F_EventScript_KiraRematch::
	trainerbattle_rematch_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_KiraRematchIntro, AbandonedShip_Rooms2_1F_Text_KiraRematchDefeat, AbandonedShip_Rooms2_1F_Text_KiraRematchNotEnoughMons
	msgbox AbandonedShip_Rooms2_1F_Text_KiraPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Jani::
	trainerbattle_single TRAINER_JANI, AbandonedShip_Rooms2_1F_Text_JaniIntro, AbandonedShip_Rooms2_1F_Text_JaniDefeat
	msgbox AbandonedShip_Rooms2_1F_Text_JaniPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Garrison::
	trainerbattle_single TRAINER_GARRISON, AbandonedShip_Rooms2_1F_Text_GarrisonIntro, AbandonedShip_Rooms2_1F_Text_GarrisonDefeat
	msgbox AbandonedShip_Rooms2_1F_Text_GarrisonPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_Text_DanIntro:
	.string "{CHN}丹：在寻找宝藏的时候，\n"
	.string "我们遇到了训练家！$"

AbandonedShip_Rooms2_1F_Text_DanDefeat:
	.string "{CHN}丹：即使我们联手\n"
	.string "还是赢不了……$"

AbandonedShip_Rooms2_1F_Text_DanPostBattle:
	.string "{CHN}丹：我们找不到宝藏……\n"
	.string "会不会已经有人拿走了？$"

AbandonedShip_Rooms2_1F_Text_DanNotEnoughMons:
	.string "{CHN}丹：你连两只宝可梦都没有。\n"
	.string "那样是不可能打赢我们的。$"

AbandonedShip_Rooms2_1F_Text_KiraIntro:
	.string "{CHN}绮罗：哦？\n"
	.string "我们本来在找宝藏。\l"
	.string "却遇到了训练家！$"

AbandonedShip_Rooms2_1F_Text_KiraDefeat:
	.string "{CHN}绮罗：哦，好强！$"

AbandonedShip_Rooms2_1F_Text_KiraPostBattle:
	.string "{CHN}绮罗：宝藏会在哪里呢？\p"
	.string "我已经决定好找到宝藏后\n"
	.string "要买什么了！$"

AbandonedShip_Rooms2_1F_Text_KiraNotEnoughMons:
	.string "{CHN}绮罗：哦，你没有两只宝可梦吗？\n"
	.string "那我们下次再对战吧！$"

AbandonedShip_Rooms2_1F_Text_KiraRegister:
	.string "{CHN}绮罗：哦，你让我好生气！\n"
	.string "我要因此登记你！$"

AbandonedShip_Rooms2_1F_Text_DanRematchIntro:
	.string "{CHN}丹：我们一直在\n"
	.string "找宝藏。\p"
	.string "我们的宝可梦也变强了。\n"
	.string "让我们展示给你看，好吗？$"

AbandonedShip_Rooms2_1F_Text_DanRematchDefeat:
	.string "{CHN}丹：你还是一样强！$"

AbandonedShip_Rooms2_1F_Text_DanPostRematch:
	.string "{CHN}丹：我们找不到宝藏，\n"
	.string "宝可梦对战也输了……\p"
	.string "我想回家……但如果我这样说，\n"
	.string "她就会对我发脾气……$"

AbandonedShip_Rooms2_1F_Text_DanRematchNotEnoughMons:
	.string "{CHN}丹：你连两只宝可梦都没有。\n"
	.string "那样是不可能打赢我们的。$"

AbandonedShip_Rooms2_1F_Text_KiraRematchIntro:
	.string "{CHN}绮罗：哦？我们又见面了！\p"
	.string "和我们一样，你还没有放弃\n"
	.string "寻找宝藏，对吧？\p"
	.string "要不要赌输的人\n"
	.string "放弃寻找宝藏？$"

AbandonedShip_Rooms2_1F_Text_KiraRematchDefeat:
	.string "{CHN}绮罗：哦，我们又输了……$"

AbandonedShip_Rooms2_1F_Text_KiraPostRematch:
	.string "{CHN}绮罗：在培养宝可梦\n"
	.string "并找到这里的\l"
	.string "宝藏之前，我们不会离开！$"

AbandonedShip_Rooms2_1F_Text_KiraRematchNotEnoughMons:
	.string "{CHN}绮罗：哦，你没有两只宝可梦吗？\n"
	.string "那我们下次再对战吧！$"

AbandonedShip_Rooms2_1F_Text_JaniIntro:
	.string "{CHN}我不太擅长游泳，\n"
	.string "但我擅长对战！$"

AbandonedShip_Rooms2_1F_Text_JaniDefeat:
	.string "{CHN}哎呀。\n"
	.string "不太顺利呢。$"

AbandonedShip_Rooms2_1F_Text_JaniPostBattle:
	.string "{CHN}光着脚在这艘船上\n"
	.string "走来走去有点恶心。$"

AbandonedShip_Rooms2_1F_Text_GarrisonIntro:
	.string "{CHN}力量与慈悲……\n"
	.string "那才是训练家的宝藏！$"

AbandonedShip_Rooms2_1F_Text_GarrisonDefeat:
	.string "{CHN}啊，你身上有什么东西\n"
	.string "在闪闪发光。$"

AbandonedShip_Rooms2_1F_Text_GarrisonPostBattle:
	.string "{CHN}在船上某个船舱里，\n"
	.string "我看到有东西在闪光。$"
