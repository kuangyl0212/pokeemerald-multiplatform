Route110_TrickHousePuzzle4_MapScripts::
	.byte 0

Route110_TrickHousePuzzle4_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_4_STATE, 0, Route110_TrickHousePuzzle4_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle4_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_4_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle4_EventScript_Cora::
	trainerbattle_single TRAINER_CORA, Route110_TrickHousePuzzle4_Text_CoraIntro, Route110_TrickHousePuzzle4_Text_CoraDefeat
	msgbox Route110_TrickHousePuzzle4_Text_CoraPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_EventScript_Yuji::
	trainerbattle_single TRAINER_YUJI, Route110_TrickHousePuzzle4_Text_YujiIntro, Route110_TrickHousePuzzle4_Text_YujiDefeat
	msgbox Route110_TrickHousePuzzle4_Text_YujiPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_EventScript_Paula::
	trainerbattle_single TRAINER_PAULA, Route110_TrickHousePuzzle4_Text_PaulaIntro, Route110_TrickHousePuzzle4_Text_PaulaDefeat
	msgbox Route110_TrickHousePuzzle4_Text_PaulaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_Text_WroteSecretCodeLockOpened:
	.string "{CHN}{PLAYER}在门上\n"
	.string "写下了暗号。\p"
	.string "“诡计大师真酷。”\n"
	.string "… … … … … … … …\p"
	.string "咔嗒，锁开了！$"

Route110_TrickHousePuzzle4_Text_CoraIntro:
	.string "{CHN}想这些太麻烦了。\n"
	.string "我只想对战！$"

Route110_TrickHousePuzzle4_Text_CoraDefeat:
	.string "{CHN}虽然输了，但我还是\n"
	.string "最喜欢对战！$"

Route110_TrickHousePuzzle4_Text_CoraPostBattle:
	.string "{CHN}你不觉得吗？只要有训练家\n"
	.string "在的地方你就会去。$"

Route110_TrickHousePuzzle4_Text_YujiIntro:
	.string "{CHN}哼！这种巨石，我一根\n"
	.string "手指就能推开！$"

Route110_TrickHousePuzzle4_Text_YujiDefeat:
	.string "{CHN}我会推石头，但不会\n"
	.string "解谜题……$"

Route110_TrickHousePuzzle4_Text_YujiPostBattle:
	.string "It's not good enough to be brawny…\n"
	.string "You have to use your head. Be brainy!$"

Route110_TrickHousePuzzle4_Text_PaulaIntro:
	.string "The TRICK HOUSE is getting trickier,\n"
	.string "isn't it?$"

Route110_TrickHousePuzzle4_Text_PaulaDefeat:
	.string "{CHN}啊啊啊！$"

Route110_TrickHousePuzzle4_Text_PaulaPostBattle:
	.string "{CHN}有人走到过终点吗？$"

