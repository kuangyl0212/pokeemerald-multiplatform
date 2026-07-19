Route110_TrickHousePuzzle6_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route110_TrickHousePuzzle6_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route110_TrickHousePuzzle6_OnWarp
	.byte 0

Route110_TrickHousePuzzle6_OnTransition:
	special RotatingGate_InitPuzzle
	end

Route110_TrickHousePuzzle6_OnWarp:
	map_script_2 VAR_TEMP_0, VAR_TEMP_0, Route110_TrickHousePuzzle6_EventScript_InitPuzzle
	.short 0

@ NOTE: This rotating gate puzzle makes use of VAR_TEMP_0 - VAR_TEMP_5
Route110_TrickHousePuzzle6_EventScript_InitPuzzle::
	special RotatingGate_InitPuzzleAndGraphics
	end

Route110_TrickHousePuzzle6_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_6_STATE, 0, Route110_TrickHousePuzzle6_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle6_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_6_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle6_EventScript_Sophia::
	trainerbattle_single TRAINER_SOPHIA, Route110_TrickHousePuzzle6_Text_SophiaIntro, Route110_TrickHousePuzzle6_Text_SophiaDefeat
	msgbox Route110_TrickHousePuzzle6_Text_SophiaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_EventScript_Benny::
	trainerbattle_single TRAINER_BENNY, Route110_TrickHousePuzzle6_Text_BennyIntro, Route110_TrickHousePuzzle6_Text_BennyDefeat
	msgbox Route110_TrickHousePuzzle6_Text_BennyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_EventScript_Sebastian::
	trainerbattle_single TRAINER_SEBASTIAN, Route110_TrickHousePuzzle6_Text_SebastianIntro, Route110_TrickHousePuzzle6_Text_SebastianDefeat
	msgbox Route110_TrickHousePuzzle6_Text_SebastianPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_Text_WroteSecretCodeLockOpened:
	.string "{CHN}{PLAYER}在门上\n"
	.string "写下了暗号。\p"
	.string "“诡计大师是我的生命。”\n"
	.string "… … … … … … … …\p"
	.string "咔嗒，锁开了！$"

Route110_TrickHousePuzzle6_Text_SophiaIntro:
	.string "{CHN}听说有一栋奇怪的房子，\n"
	.string "我非得来看看不可。$"

Route110_TrickHousePuzzle6_Text_SophiaDefeat:
	.string "{CHN}我碰上了一个厉害的训练家！$"

Route110_TrickHousePuzzle6_Text_SophiaPostBattle:
	.string "{CHN}我在这里逛得可开心了。\p"
	.string "这是个值得反复\n"
	.string "挑战的谜题！$"

Route110_TrickHousePuzzle6_Text_BennyIntro:
	.string "{CHN}也许我可以让我的鸟宝可梦\n"
	.string "从墙上飞过去……$"

Route110_TrickHousePuzzle6_Text_BennyDefeat:
	.string "{CHN}哇啊啊！我搞砸了！$"

Route110_TrickHousePuzzle6_Text_BennyPostBattle:
	.string "{CHN}嘿嘿嘿……我想我输了\n"
	.string "是因为我想作弊吧。$"

Route110_TrickHousePuzzle6_Text_SebastianIntro:
	.string "{CHN}这些旋转门\n"
	.string "转得我头晕……$"

Route110_TrickHousePuzzle6_Text_SebastianDefeat:
	.string "{CHN}一切都在转啊转。\n"
	.string "我再也受不了啦……$"

Route110_TrickHousePuzzle6_Text_SebastianPostBattle:
	.string "{CHN}你好像一点都不受影响。\n"
	.string "还是说你摆着一张扑克脸？$"

