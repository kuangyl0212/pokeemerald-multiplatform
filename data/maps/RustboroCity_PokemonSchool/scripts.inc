RustboroCity_PokemonSchool_MapScripts::
	.byte 0

RustboroCity_PokemonSchool_EventScript_Blackboard::
	lockall
	msgbox RustboroCity_PokemonSchool_Text_BlackboardListsStatusChanges, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic::
	message RustboroCity_PokemonSchool_Text_ReadWhichTopic
	waitmessage
	multichoicegrid 8, 1, MULTI_STATUS_INFO, 3, FALSE
	switch VAR_RESULT
	case 0, RustboroCity_PokemonSchool_EventScript_Poison
	case 1, RustboroCity_PokemonSchool_EventScript_Paralysis
	case 2, RustboroCity_PokemonSchool_EventScript_Sleep
	case 3, RustboroCity_PokemonSchool_EventScript_Burn
	case 4, RustboroCity_PokemonSchool_EventScript_Freeze
	case 5, RustboroCity_PokemonSchool_EventScript_ExitTopicSelect
	case MULTI_B_PRESSED, RustboroCity_PokemonSchool_EventScript_ExitTopicSelect
	end

RustboroCity_PokemonSchool_EventScript_Poison::
	msgbox RustboroCity_PokemonSchool_Text_ExplainPoison, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Paralysis::
	msgbox RustboroCity_PokemonSchool_Text_ExplainParalysis, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Sleep::
	msgbox RustboroCity_PokemonSchool_Text_ExplainSleep, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Burn::
	msgbox RustboroCity_PokemonSchool_Text_ExplainBurn, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Freeze::
	msgbox RustboroCity_PokemonSchool_Text_ExplainFreeze, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_ExitTopicSelect::
	releaseall
	end

RustboroCity_PokemonSchool_EventScript_GameboyKid1::
	msgbox RustboroCity_PokemonSchool_Text_TradingRightNow, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_GameboyKid2::
	msgbox RustboroCity_PokemonSchool_Text_AlwaysWantedSeedot, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_RichBoy::
	msgbox RustboroCity_PokemonSchool_Text_PokemontCantUseManMadeItems, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_Lass::
	msgbox RustboroCity_PokemonSchool_Text_ConfusedPokemonAttacksItself, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_SchoolKidM::
	msgbox RustboroCity_PokemonSchool_Text_PokemonHealItselfWithBerry, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_StudentNotebook::
	msgbox RustboroCity_PokemonSchool_Text_StudentsNotes, MSGBOX_SIGN
	end

RustboroCity_PokemonSchool_EventScript_Teacher::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_QUICK_CLAW, RustboroCity_PokemonSchool_EventScript_GaveQuickClaw
	call_if_eq VAR_FACING, DIR_EAST, RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsEast
	call_if_eq VAR_FACING, DIR_WEST, RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsWest
	msgbox RustboroCity_PokemonSchool_Text_StudentsWhoDontStudyGetQuickClaw, MSGBOX_DEFAULT
	giveitem ITEM_QUICK_CLAW
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	setflag FLAG_RECEIVED_QUICK_CLAW
	release
	end

RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsEast::
	applymovement VAR_LAST_TALKED, RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsEast
	waitmovement 0
	return

RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsWest::
	applymovement VAR_LAST_TALKED, RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsWest
	waitmovement 0
	return

RustboroCity_PokemonSchool_EventScript_GaveQuickClaw::
	msgbox RustboroCity_PokemonSchool_Text_ExplainQuickClaw, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	release
	end

RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsWest:
	walk_left
	walk_down
	walk_down
	walk_right
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	walk_down
	walk_in_place_faster_left
	delay_16
	delay_16
	walk_right
	delay_16
	delay_16
	delay_8
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	walk_right
	step_end

RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsEast:
	walk_right
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	walk_down
	walk_in_place_faster_left
	delay_16
	delay_16
	walk_right
	delay_16
	delay_16
	delay_8
	walk_up
	walk_right
	walk_up
	walk_up
	walk_left
	walk_left
	step_end

RustboroCity_PokemonSchool_EventScript_Scott::
	lock
	faceplayer
	goto_if_set FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE, RustboroCity_PokemonSchool_EventScript_ScottWatchStudents
	goto_if_set FLAG_MET_SCOTT_RUSTBORO, RustboroCity_PokemonSchool_EventScript_ScottSpokeAlready
	goto_if_set FLAG_BADGE01_GET, RustboroCity_PokemonSchool_EventScript_ScottGreetHasBadge
	msgbox RustboroCity_PokemonSchool_Text_ScottMetAlreadyCut, MSGBOX_DEFAULT
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_RUSTBORO
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottSpokeAlready::
	goto_if_set FLAG_BADGE01_GET, RustboroCity_PokemonSchool_EventScript_ScottNoticeBadge
	msgbox RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown, MSGBOX_DEFAULT
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottGreetHasBadge::
	msgbox RustboroCity_PokemonSchool_Text_ScottMetAlreadyStoneBadge, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge
	end

RustboroCity_PokemonSchool_EventScript_ScottNoticeBadge::
	msgbox RustboroCity_PokemonSchool_Text_ScottStoneBadge, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge
	end

RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge::
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottWatchStudents::
	msgbox RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown, MSGBOX_DEFAULT
	release
	end

RustboroCity_PokemonSchool_Text_BlackboardListsStatusChanges:
	.string "{CHN}黑板上列出了对战中\n"
	.string "可能影响宝可梦的状态变化.$"

RustboroCity_PokemonSchool_Text_ReadWhichTopic:
	.string "{CHN}你想读哪个主题?$"

RustboroCity_PokemonSchool_Text_ExplainPoison:
	.string "{CHN}如果宝可梦中毒了，\n"
	.string "HP会持续减少.\p"
	.string "中毒的效果在对战\n"
	.string "结束后仍然存在.\p"
	.string "中毒的宝可梦在\n"
	.string "行走时HP会下降.\p"
	.string "使用解毒药可以治疗中毒.$"

RustboroCity_PokemonSchool_Text_ExplainParalysis:
	.string "{CHN}如果宝可梦麻痹了，\n"
	.string "速度会下降.\p"
	.string "在对战中它也可能\n"
	.string "无法行动.\p"
	.string "麻痹在对战后仍然存在.\n"
	.string "使用麻痹治愈药可以治愈.$"

RustboroCity_PokemonSchool_Text_ExplainSleep:
	.string "{CHN}如果宝可梦睡着了，\n"
	.string "就无法攻击.\p"
	.string "宝可梦可能会自己醒来，\n"
	.string "但如果对战结束时它还\l"
	.string "在睡眠，就会继续睡着.\p"
	.string "使用清醒药可以唤醒它.$"

RustboroCity_PokemonSchool_Text_ExplainBurn:
	.string "{CHN}灼伤会降低攻击力，\n"
	.string "并持续减少受害者的HP.\p"
	.string "灼伤在对战后仍然存在.\n"
	.string "使用灼伤治愈药可以治愈灼伤.$"

RustboroCity_PokemonSchool_Text_ExplainFreeze:
	.string "{CHN}如果宝可梦被冰冻了，\n"
	.string "它将完全无法行动.\p"
	.string "冰冻状态在对战后仍然存在.\n"
	.string "使用冰冻治愈药可以解冻.$"

RustboroCity_PokemonSchool_Text_StudentsWhoDontStudyGetQuickClaw:
	.string "{CHN}不学习的学生会尝尝\n"
	.string "我的先制之爪.\p"
	.string "你是不是一个好学生，\n"
	.string "从你使用这个道具\l"
	.string "的方式就能看出来.$"

RustboroCity_PokemonSchool_Text_ExplainQuickClaw:
	.string "{CHN}携带先制之爪的宝可梦\n"
	.string "偶尔会加速，\l"
	.string "抢在对手之前行动.\p"
	.string "还有很多其他\n"
	.string "让宝可梦携带的道具.\p"
	.string "光是这些就够你研究\n"
	.string "好一阵子了！$"

RustboroCity_PokemonSchool_Text_TradingRightNow:
	.string "{CHN}我现在正在和朋友\n"
	.string "交换宝可梦.$"

RustboroCity_PokemonSchool_Text_AlwaysWantedSeedot:
	.string "{CHN}我一直想要一只橡实果，\n"
	.string "终于要得到了！$"

RustboroCity_PokemonSchool_Text_PokemontCantUseManMadeItems:
	.string "{CHN}宝可梦可以携带道具，但它们\n"
	.string "不知道如何使用人造\l"
	.string "道具，比如伤药和解毒药.$"

RustboroCity_PokemonSchool_Text_ConfusedPokemonAttacksItself:
	.string "{CHN}你知道有些宝可梦招式\n"
	.string "会让宝可梦混乱吗？\p"
	.string "混乱的宝可梦有时会\n"
	.string "无意中攻击自己.\p"
	.string "但一旦离开对战，\n"
	.string "它就会恢复正常.$"

RustboroCity_PokemonSchool_Text_PokemonHealItselfWithBerry:
	.string "{CHN}携带树果的宝可梦\n"
	.string "会自己治疗…\p"
	.string "宝可梦可以携带的道具\n"
	.string "有很多种…\p"
	.string "天哪，做笔记\n"
	.string "真难啊…$"

RustboroCity_PokemonSchool_Text_StudentsNotes:
	.string "{CHN}这是这个学生的笔记本…\p"
	.string "要用精灵球\n"
	.string "捕捉宝可梦.\p"
	.string "最多可以有六只宝可梦\n"
	.string "跟随训练家.\p"
	.string "训练家是捕捉、培育宝可梦，\n"
	.string "并用它们进行对战\l"
	.string "的人.\p"
	.string "训练家的使命是击败\n"
	.string "在宝可梦道馆\l"
	.string "等待挑战者的强大训练家.$"

RustboroCity_PokemonSchool_Text_ScottMetAlreadyCut:
	.string "{CHN}你好？我们是不是见过？\n"
	.string "我想是在橙华市.\p"
	.string "让我自我介绍一下.\n"
	.string "我叫斯科特.\p"
	.string "我一直在到处旅行，\n"
	.string "寻找优秀的训练家.\p"
	.string "更准确地说，我在找\n"
	.string "宝可梦对战专家.\p"
	.string "那么，你来这所学校做什么？\n"
	.string "你也是训练家吗？\p"
	.string "你首先应该做的，\n"
	.string "是让宝可梦学会居合劈.\p"
	.string "如果我没记错，\n"
	.string "这个镇上有人会居合劈.$"

RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown:
	.string "{CHN}斯科特：嗯…\p"
	.string "这里学生的天赋水平\n"
	.string "还不清楚. 但潜力是有的.$"

RustboroCity_PokemonSchool_Text_ScottStoneBadge:
	.string "{CHN}斯科特：哦，那是什么？\p"
	.string "是岩石徽章吧？\n"
	.string "挺厉害的，我说真的.\p"
	.string "但是，你知道吗，我真希望\n"
	.string "能亲眼看到你对战.\p"
	.string "光从联盟徽章很难看出\n"
	.string "你作为训练家是什么水平.$"

RustboroCity_PokemonSchool_Text_ScottMetAlreadyStoneBadge:
	.string "{CHN}你好？我们是不是见过？\n"
	.string "我想是在橙华市.\p"
	.string "让我自我介绍一下.\n"
	.string "我叫斯科特.\p"
	.string "我一直在到处旅行，\n"
	.string "寻找优秀的训练家.\p"
	.string "更准确地说，我在找\n"
	.string "宝可梦对战专家.\p"
	.string "哦，那是什么？\n"
	.string "是岩石徽章吧？\p"
	.string "对像你这样的新手训练家来说，\n"
	.string "挺厉害的，我说真的.\p"
	.string "但是，你知道吗，我真希望\n"
	.string "能亲眼看到你对战.\p"
	.string "光从联盟徽章很难看出\n"
	.string "你作为训练家是什么水平.$"

