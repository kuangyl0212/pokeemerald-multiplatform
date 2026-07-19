AbandonedShip_Rooms_1F_MapScripts::
	.byte 0

AbandonedShip_Rooms_1F_EventScript_Gentleman::
	msgbox AbandonedShip_Rooms_1F_Text_TakingALookAround, MSGBOX_NPC
	end

AbandonedShip_Rooms_1F_EventScript_Demetrius::
	trainerbattle_single TRAINER_DEMETRIUS, AbandonedShip_Rooms_1F_Text_DemetriusIntro, AbandonedShip_Rooms_1F_Text_DemetriusDefeat
	msgbox AbandonedShip_Rooms_1F_Text_DemetriusPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms_1F_EventScript_Thalia::
	trainerbattle_single TRAINER_THALIA_1, AbandonedShip_Rooms_1F_Text_ThaliaIntro, AbandonedShip_Rooms_1F_Text_ThaliaDefeat, AbandonedShip_Rooms_1F_EventScript_RegisterThalia
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms_1F_EventScript_ThaliaRematch
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms_1F_EventScript_RegisterThalia::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_THALIA_1
	release
	end

AbandonedShip_Rooms_1F_EventScript_ThaliaRematch::
	trainerbattle_rematch TRAINER_THALIA_1, AbandonedShip_Rooms_1F_Text_ThaliaRematchIntro, AbandonedShip_Rooms_1F_Text_ThaliaRematchDefeat
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms_1F_Text_TakingALookAround:
	.string "{CHN}这种船很罕见，所以我\n"
	.string "在到处看看。\p"
	.string "嗯嗯……\n"
	.string "好像还有其他船舱……$"

AbandonedShip_Rooms_1F_Text_ThaliaIntro:
	.string "{CHN}到底是什么促使你\n"
	.string "来这里？你一定很好奇！$"

AbandonedShip_Rooms_1F_Text_ThaliaDefeat:
	.string "{CHN}不只是好奇，还很强大……$"

AbandonedShip_Rooms_1F_Text_ThaliaPostBattle:
	.string "{CHN}隔壁那个男人……\p"
	.string "他说他只是在观光，\n"
	.string "但我可不那么认为。$"

AbandonedShip_Rooms_1F_Text_ThaliaRegister:
	.string "{CHN}你真是个厉害的训练家！\n"
	.string "让我把你登记下来作为纪念！$"

AbandonedShip_Rooms_1F_Text_ThaliaRematchIntro:
	.string "{CHN}到底是什么促使你\n"
	.string "回来？你真的很好奇！$"

AbandonedShip_Rooms_1F_Text_ThaliaRematchDefeat:
	.string "{CHN}你是不是太强了？$"

AbandonedShip_Rooms_1F_Text_ThaliaPostRematch:
	.string "{CHN}我敢肯定那个男人在搞什么鬼！\n"
	.string "他的行为太可疑了！$"

AbandonedShip_Rooms_1F_Text_DemetriusIntro:
	.string "{CHN}哇！\n"
	.string "被发现了！……咦？$"

AbandonedShip_Rooms_1F_Text_DemetriusDefeat:
	.string "{CHN}哦，你不是我妈妈。$"

AbandonedShip_Rooms_1F_Text_DemetriusPostBattle:
	.string "{CHN}我惹妈妈生气了，所以我跑出来了。\n"
	.string "请保密我在这里！$"
