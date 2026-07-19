Route110_TrickHousePuzzle1_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Route110_TrickHousePuzzle1_OnLoad
	.byte 0

Route110_TrickHousePuzzle1_OnLoad:
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_1_STATE, 2, Route110_TrickHousePuzzle1_EventScript_OpenDoor
	end

Route110_TrickHousePuzzle1_EventScript_OpenDoor::
	setmetatile 13, 1, METATILE_TrickHousePuzzle_Stairs_Down, FALSE
	end

Route110_TrickHousePuzzle1_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_1_STATE, 0, Route110_TrickHousePuzzle1_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle1_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_1_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle1_EventScript_Sally::
	trainerbattle_single TRAINER_SALLY, Route110_TrickHousePuzzle1_Text_SallyIntro, Route110_TrickHousePuzzle1_Text_SallyDefeat
	msgbox Route110_TrickHousePuzzle1_Text_SallyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle1_EventScript_Eddie::
	trainerbattle_single TRAINER_EDDIE, Route110_TrickHousePuzzle1_Text_EddieIntro, Route110_TrickHousePuzzle1_Text_EddieDefeat
	msgbox Route110_TrickHousePuzzle1_Text_EddiePostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle1_EventScript_Robin::
	trainerbattle_single TRAINER_ROBIN, Route110_TrickHousePuzzle1_Text_RobinIntro, Route110_TrickHousePuzzle1_Text_RobinDefeat
	msgbox Route110_TrickHousePuzzle1_Text_RobinPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle1_Text_WroteSecretCodeLockOpened::
	.string "{CHN}{PLAYER}在门上\n"
	.string "写下了暗号。\p"
	.string "“诡计大师真了不起。”\n"
	.string "… … … … … … … …\p"
	.string "咔嗒，锁开了！$"

Route110_TrickHousePuzzle1_Text_SallyIntro:
	.string "{CHN}我要用刚学会的居合劈\n"
	.string "劈砍出一条胜利之路！$"

Route110_TrickHousePuzzle1_Text_SallyDefeat:
	.string "{CHN}你怎么这么认真？$"

Route110_TrickHousePuzzle1_Text_SallyPostBattle:
	.string "{CHN}我永远都不会厌倦\n"
	.string "劈劈砍砍！$"

Route110_TrickHousePuzzle1_Text_EddieIntro:
	.string "{CHN}我迷迷糊糊地\n"
	.string "闯进了这个奇怪的房子……$"

Route110_TrickHousePuzzle1_Text_EddieDefeat:
	.string "{CHN}结果我还输了……$"

Route110_TrickHousePuzzle1_Text_EddiePostBattle:
	.string "{CHN}我迷了路，输了对战，\n"
	.string "现在更加迷失了……我出不去了……$"

Route110_TrickHousePuzzle1_Text_RobinIntro:
	.string "{CHN}诡计大师到底是什么人？$"

Route110_TrickHousePuzzle1_Text_RobinDefeat:
	.string "{CHN}我正想着出神，结果就输了！$"

Route110_TrickHousePuzzle1_Text_RobinPostBattle:
	.string "{CHN}你真强！\n"
	.string "你到底是谁？$"

