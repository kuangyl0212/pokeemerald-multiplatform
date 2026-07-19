Route111_Text_MakingRoomUseTMToMakeYourOwn:
	.string "{CHN}什么？\n"
	.string "我在做什么？\p"
	.string "我在想用宝可梦的招式\n"
	.string "在这里做自己的房间。\p"
	.string "对了！我把这个技能机给你。\n"
	.string "你要用它来做自己的房间吗？$"

Route111_Text_ExplainSecretPower:
	.string "{CHN}找一棵看起来会垂下藤蔓的大树。\n"
	.string "在树前使用秘密之力。\p"
	.string "藤蔓应该会松开并垂下来，\l"
	.string "这样你就可以爬上树了。\p"
	.string "你会发现有很大的空间可以\n"
	.string "放置你喜欢的东西。\p"
	.string "那将是你自己的秘密房间……\n"
	.string "秘密基地！\p"
	.string "你也应该做一个。\p"
	.string "另外，你不一定要在树上\n"
	.string "做你的秘密基地。\p"
	.string "试着在有凹陷的岩壁上\n"
	.string "使用秘密之力。\p"
	.string "我也会去寻找其他地方。\n"
	.string "好的，再见！$"

Route111_Text_DontWantThis:
	.string "{CHN}哦，你不要这个吗？\n"
	.string "如果你改变主意了，告诉我，好吗？$"

Route111_Text_DontHaveAnyRoom:
	.string "{CHN}哦，你没有空间放这个。\p"
	.string "我会保留着它，下次\n"
	.string "再来拿吧，好吗？$"

Route111_EventScript_SecretPowerMan::
	lock
	faceplayer
	msgbox Route111_Text_MakingRoomUseTMToMakeYourOwn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route111_EventScript_GiveSecretPower
	msgbox Route111_Text_DontWantThis, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_GiveSecretPower::
	giveitem ITEM_TM_SECRET_POWER
	goto_if_eq VAR_RESULT, FALSE, Route111_EventScript_NoRoomForSecretPower
	msgbox Route111_Text_ExplainSecretPower, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_RECEIVED_SECRET_POWER
	clearflag FLAG_HIDE_SLATEPORT_CITY_TM_SALESMAN
	call_if_eq VAR_FACING, DIR_WEST, Route111_EventScript_SecretPowerManExit
	call_if_eq VAR_FACING, DIR_EAST, Route111_EventScript_SecretPowerManExit
	call_if_eq VAR_FACING, DIR_NORTH, Route111_EventScript_SecretPowerManExitNorth
	removeobject VAR_LAST_TALKED
	release
	end

Route111_EventScript_SecretPowerManExit::
	applymovement VAR_LAST_TALKED, Route111_Movement_SecretPowerManExit
	waitmovement 0
	return

Route111_EventScript_SecretPowerManExitNorth::
	applymovement VAR_LAST_TALKED, Route111_Movement_SecretPowerManExitNorth
	waitmovement 0
	return

Route111_EventScript_NoRoomForSecretPower::
	msgbox Route111_Text_DontHaveAnyRoom, MSGBOX_DEFAULT
	release
	end

Route111_Movement_SecretPowerManExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

Route111_Movement_SecretPowerManExitNorth:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end
