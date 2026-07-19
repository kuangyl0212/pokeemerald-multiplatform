Route110_TrickHousePuzzle8_MapScripts::
	.byte 0

Route110_TrickHousePuzzle8_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_8_STATE, 0, Route110_TrickHousePuzzle8_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle8_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_8_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle8_EventScript_Vincent::
	trainerbattle_single TRAINER_VINCENT, Route110_TrickHousePuzzle8_Text_VincentIntro, Route110_TrickHousePuzzle8_Text_VincentDefeat
	msgbox Route110_TrickHousePuzzle8_Text_VincentPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_EventScript_Keira::
	trainerbattle_single TRAINER_KEIRA, Route110_TrickHousePuzzle8_Text_KeiraIntro, Route110_TrickHousePuzzle8_Text_KeiraDefeat
	msgbox Route110_TrickHousePuzzle8_Text_KeiraPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_EventScript_Leroy::
	trainerbattle_single TRAINER_LEROY, Route110_TrickHousePuzzle8_Text_LeroyIntro, Route110_TrickHousePuzzle8_Text_LeroyDefeat
	msgbox Route110_TrickHousePuzzle8_Text_LeroyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_Text_WroteSecretCodeLockOpened::
	.string "{CHN}{PLAYER}在门上\n"
	.string "写下了暗号。\p"
	.string "“诡计大师我爱你。”\n"
	.string "… … … … … … … …\p"
	.string "咔嗒，锁开了！$"

Route110_TrickHousePuzzle8_Text_VincentIntro:
	.string "{CHN}没多少训练家能\n"
	.string "走到这一步。$"

Route110_TrickHousePuzzle8_Text_VincentDefeat:
	.string "{CHN}那说明你也很厉害……$"

Route110_TrickHousePuzzle8_Text_VincentPostBattle:
	.string "{CHN}你打败过宝可梦联盟\n"
	.string "冠军？太夸张了！$"

Route110_TrickHousePuzzle8_Text_KeiraIntro:
	.string "{CHN}能和我对战\n"
	.string "算你走运！$"

Route110_TrickHousePuzzle8_Text_KeiraDefeat:
	.string "{CHN}这不对劲！\n"
	.string "我不可能输！$"

Route110_TrickHousePuzzle8_Text_KeiraPostBattle:
	.string "{CHN}你能打败我真是个奇迹。\n"
	.string "你可以拿这事炫耀了。$"

Route110_TrickHousePuzzle8_Text_LeroyIntro:
	.string "{CHN}你也一直在苦战诡计\n"
	.string "屋的挑战吧。$"

Route110_TrickHousePuzzle8_Text_LeroyDefeat:
	.string "{CHN}我明白了……\n"
	.string "你的风格非同凡响。$"

Route110_TrickHousePuzzle8_Text_LeroyPostBattle:
	.string "{CHN}看到你这样的人，诡计大师\n"
	.string "应该会很高兴。$"

