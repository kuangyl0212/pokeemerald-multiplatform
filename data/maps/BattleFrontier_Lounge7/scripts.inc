BattleFrontier_Lounge7_MapScripts::
	.byte 0

BattleFrontier_Lounge7_EventScript_LeftMoveTutor::
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_1
	goto_if_set FLAG_MET_FRONTIER_BEAUTY_MOVE_TUTOR, BattleFrontier_Lounge7_EventScript_AlreadyMetLeftTutor
	msgbox BattleFrontier_Lounge7_Text_LeftTutorIntro, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_BEAUTY_MOVE_TUTOR
	goto BattleFrontier_Lounge7_EventScript_ChooseLeftTutorMove
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetLeftTutor::
	msgbox BattleFrontier_Lounge7_Text_LeftTutorWelcomeBack, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseLeftTutorMove
	end

BattleFrontier_Lounge7_EventScript_ChooseLeftTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 0
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_1
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_Softboiled
	case 1, BattleFrontier_Lounge7_EventScript_SeismicToss
	case 2, BattleFrontier_Lounge7_EventScript_DreamEater
	case 3, BattleFrontier_Lounge7_EventScript_MegaPunch
	case 4, BattleFrontier_Lounge7_EventScript_MegaKick
	case 5, BattleFrontier_Lounge7_EventScript_BodySlam
	case 6, BattleFrontier_Lounge7_EventScript_RockSlide
	case 7, BattleFrontier_Lounge7_EventScript_Counter
	case 8, BattleFrontier_Lounge7_EventScript_ThunderWave
	case 9, BattleFrontier_Lounge7_EventScript_SwordsDance
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_ChooseNewLeftTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 0
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_1
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_Softboiled
	case 1, BattleFrontier_Lounge7_EventScript_SeismicToss
	case 2, BattleFrontier_Lounge7_EventScript_DreamEater
	case 3, BattleFrontier_Lounge7_EventScript_MegaPunch
	case 4, BattleFrontier_Lounge7_EventScript_MegaKick
	case 5, BattleFrontier_Lounge7_EventScript_BodySlam
	case 6, BattleFrontier_Lounge7_EventScript_RockSlide
	case 7, BattleFrontier_Lounge7_EventScript_Counter
	case 8, BattleFrontier_Lounge7_EventScript_ThunderWave
	case 9, BattleFrontier_Lounge7_EventScript_SwordsDance
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_Softboiled::
	setvar VAR_0x8008, 16
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_SeismicToss::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_DreamEater::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_MegaPunch::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_MegaKick::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_BodySlam::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_RockSlide::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Counter::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_ThunderWave::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_SwordsDance::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_RightMoveTutor::
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_2
	goto_if_set FLAG_MET_FRONTIER_SWIMMER_MOVE_TUTOR, BattleFrontier_Lounge7_EventScript_AlreadyMetRightTutor
	msgbox BattleFrontier_Lounge7_Text_RightTutorIntro, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_SWIMMER_MOVE_TUTOR
	goto BattleFrontier_Lounge7_EventScript_ChooseRightTutorMove
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetRightTutor::
	msgbox BattleFrontier_Lounge7_Text_RightTutorWelcomeBack, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseRightTutorMove
	end

BattleFrontier_Lounge7_EventScript_ChooseRightTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 1
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_2
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_DefenseCurl
	case 1, BattleFrontier_Lounge7_EventScript_Snore
	case 2, BattleFrontier_Lounge7_EventScript_MudSlap
	case 3, BattleFrontier_Lounge7_EventScript_Swift
	case 4, BattleFrontier_Lounge7_EventScript_IcyWind
	case 5, BattleFrontier_Lounge7_EventScript_Endure
	case 6, BattleFrontier_Lounge7_EventScript_PsychUp
	case 7, BattleFrontier_Lounge7_EventScript_IcePunch
	case 8, BattleFrontier_Lounge7_EventScript_ThunderPunch
	case 9, BattleFrontier_Lounge7_EventScript_FirePunch
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_ChooseNewRightTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 1
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_2
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_DefenseCurl
	case 1, BattleFrontier_Lounge7_EventScript_Snore
	case 2, BattleFrontier_Lounge7_EventScript_MudSlap
	case 3, BattleFrontier_Lounge7_EventScript_Swift
	case 4, BattleFrontier_Lounge7_EventScript_IcyWind
	case 5, BattleFrontier_Lounge7_EventScript_Endure
	case 6, BattleFrontier_Lounge7_EventScript_PsychUp
	case 7, BattleFrontier_Lounge7_EventScript_IcePunch
	case 8, BattleFrontier_Lounge7_EventScript_ThunderPunch
	case 9, BattleFrontier_Lounge7_EventScript_FirePunch
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_DefenseCurl::
	setvar VAR_0x8008, 16
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Snore::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_MudSlap::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Swift::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_IcyWind::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Endure::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_PsychUp::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_IcePunch::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_ThunderPunch::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_FirePunch::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect::
	special CloseBattleFrontierTutorWindow
	special CloseBattlePointsWindow
	msgbox BattleFrontier_Lounge7_Text_YouDontWantTo, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge7_EventScript_CancelChooseMon::
	msgbox BattleFrontier_Lounge7_Text_YouDontWantTo, MSGBOX_DEFAULT
	release
	end

/* VAR_0x8008 is the price*/
/* VAR_TEMP_C is the scroll multichoice ID*/
/* VAR_TEMP_FRONTIER_TUTOR_SELECTION is the move selection*/
/* VAR_TEMP_FRONTIER_TUTOR_ID is which move tutor was spoken to*/
BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection::
	copyvar VAR_0x8004, VAR_TEMP_FRONTIER_TUTOR_SELECTION
	copyvar VAR_0x8005, VAR_TEMP_FRONTIER_TUTOR_ID
	special BufferBattleFrontierTutorMoveName
	buffernumberstring STR_VAR_2, VAR_0x8008
	copyvar VAR_0x8004, VAR_TEMP_C
	msgbox BattleFrontier_Lounge7_Text_MoveWillBeXBattlePoints, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge7_EventScript_ChooseNewMove
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	goto_if_ge VAR_TEMP_1, VAR_0x8008, BattleFrontier_Lounge7_EventScript_TeachTutorMove
	msgbox BattleFrontier_Lounge7_Text_HaventGotEnoughPoints, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseNewMove
	end

BattleFrontier_Lounge7_EventScript_TeachTutorMove::
	msgbox BattleFrontier_Lounge7_Text_TeachMoveToWhichMon, MSGBOX_DEFAULT
	special GetBattleFrontierTutorMoveIndex
	fadescreen FADE_TO_BLACK
	special CloseBattlePointsWindow
	special CloseBattleFrontierTutorWindow
	special ChooseMonForMoveTutor
	waitstate
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_Lounge7_EventScript_CancelChooseMon
	msgbox BattleFrontier_Lounge7_Text_IllTakeBattlePoints, MSGBOX_DEFAULT
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	release
	end

BattleFrontier_Lounge7_EventScript_ChooseNewMove::
	goto_if_eq VAR_TEMP_FRONTIER_TUTOR_ID, 0, BattleFrontier_Lounge7_EventScript_ChooseNewLeftTutorMove
	goto BattleFrontier_Lounge7_EventScript_ChooseNewRightTutorMove
	end

BattleFrontier_Lounge7_EventScript_Sailor::
	msgbox BattleFrontier_Lounge7_Text_ThinkLadiesDontGetAlong, MSGBOX_NPC
	end

BattleFrontier_Lounge7_EventScript_Gentleman::
	msgbox BattleFrontier_Lounge7_Text_LadiesWereStrongAndBeautiful, MSGBOX_NPC
	end

BattleFrontier_Lounge7_Text_LeftTutorIntro:
	.string "{CHN}哈哈哈！\p"
	.string "你现在看不出来，\n"
	.string "但我以前可是个厉害的训练家。\p"
	.string "我有最美少女的美名，\n"
	.string "我告诉你！\p"
	.string "………………\p"
	.string "怎么了？\n"
	.string "你不相信我。\p"
	.string "我可不像那边那个吹牛的女人。\n"
	.string "我是真的有才能！\p"
	.string "让我证明给你看。\n"
	.string "我能教你的宝可梦特殊又\l"
	.string "可爱的招式。\p"
	.string "但我的课不是免费的。\n"
	.string "用一点对战点数来支付\l"
	.string "我教的招式怎么样？$"

BattleFrontier_Lounge7_Text_LeftTutorWelcomeBack:
	.string "{CHN}哈哈哈！\p"
	.string "你回来学特殊又\n"
	.string "可爱的宝可梦招式了吗？$"

BattleFrontier_Lounge7_Text_TeachWhichMove:
	.string "{CHN}好好好，看这里！\n"
	.string "我该教哪个招式呢？$"

BattleFrontier_Lounge7_Text_MoveWillBeXBattlePoints:
	.string "{CHN}招式{STR_VAR_1}，是吗？\n"
	.string "那需要{STR_VAR_2}个对战点数，可以吗？$"

BattleFrontier_Lounge7_Text_TeachMoveToWhichMon:
	.string "{CHN}好好好，现在选出\n"
	.string "我应该教招式的宝可梦。$"

BattleFrontier_Lounge7_Text_HaventGotEnoughPoints:
	.string "{CHN}什么……\n"
	.string "你的对战点数不够！$"

BattleFrontier_Lounge7_Text_IllTakeBattlePoints:
	.string "{CHN}现在你看到我有多熟练了吧？\n"
	.string "我就收下你的对战点数了，谢谢！$"

BattleFrontier_Lounge7_Text_YouDontWantTo:
	.string "{CHN}什么？\n"
	.string "你不想……\p"
	.string "如果你想看我的本领，\n"
	.string "随时来找我！$"

BattleFrontier_Lounge7_Text_RightTutorIntro:
	.string "{CHN}嘻嘻嘻！\p"
	.string "我知道现在很难看出来，\n"
	.string "但我以前可是个了不起的训练家。\p"
	.string "我有最无敌泳者的美名，\n"
	.string "我告诉你！\p"
	.string "………………\p"
	.string "怎么了？\n"
	.string "你不相信我。\p"
	.string "我可不像那边那个愚蠢的女人。\n"
	.string "我是真的有经验！\p"
	.string "我可以证明给你看。\n"
	.string "我能教你的宝可梦强硬又\l"
	.string "漂亮的招式。\p"
	.string "但我的课不是免费的。\n"
	.string "用一点对战点数来支付\l"
	.string "我教的招式怎么样？$"

BattleFrontier_Lounge7_Text_RightTutorWelcomeBack:
	.string "{CHN}嘻嘻嘻！\p"
	.string "你来学强硬又\n"
	.string "漂亮的宝可梦招式了吗？$"

BattleFrontier_Lounge7_Text_ThinkLadiesDontGetAlong:
	.string "{CHN}那些女士们，她们互相说坏话\n"
	.string "的样子，你大概觉得\l"
	.string "她们相处不好。\p"
	.string "但如果是那样的话，她们就不会\n"
	.string "一起待在这里了，对吧？$"

BattleFrontier_Lounge7_Text_LadiesWereStrongAndBeautiful:
	.string "{CHN}当我还是个小短裤的时候，\n"
	.string "那些女士们既强大又美丽。\p"
	.string "她们是我们训练家中的偶像。\p"
	.string "即使现在，岁月也没有磨灭\n"
	.string "她们的实力。\p"
	.string "事实上，她们的宝可梦招式\n"
	.string "变得更加精湛了。\p"
	.string "但是……出于某种原因，\n"
	.string "我不禁有这样的感觉……\p"
	.string "时间真是太残酷了……$"

BattleFrontier_Lounge7_Text_SoftboiledDesc::
	.string "{CHN}恢复最多\n"
	.string "使用者最大HP的\n"
	.string "一半。$"

BattleFrontier_Lounge7_Text_SeismicTossDesc::
	.string "{CHN}造成与\n"
	.string "使用者等级\n"
	.string "相同的伤害。$"

BattleFrontier_Lounge7_Text_DreamEaterDesc::
	.string "{CHN}恢复对\n"
	.string "睡眠中的对手\n"
	.string "造成伤害的一半。$"

BattleFrontier_Lounge7_Text_MegaPunchDesc::
	.string "{CHN}用惊人的力量\n"
	.string "挥出的\n"
	.string "强力拳击。$"

BattleFrontier_Lounge7_Text_MegaKickDesc::
	.string "{CHN}用猛烈力量\n"
	.string "踢出的极其\n"
	.string "强大的踢击。$"

BattleFrontier_Lounge7_Text_BodySlamDesc::
	.string "{CHN}用全身撞击，\n"
	.string "可能造成\n"
	.string "麻痹。$"

BattleFrontier_Lounge7_Text_RockSlideDesc::
	.string "{CHN}投掷巨石。\n"
	.string "可能造成\n"
	.string "畏缩。$"

BattleFrontier_Lounge7_Text_CounterDesc::
	.string "{CHN}以两倍的力量\n"
	.string "反击任何物理\n"
	.string "攻击。$"

BattleFrontier_Lounge7_Text_ThunderWaveDesc::
	.string "{CHN}微弱的电流\n"
	.string "使对手\n"
	.string "陷入麻痹。$"

BattleFrontier_Lounge7_Text_SwordsDanceDesc::
	.string "{CHN}战斗之舞，\n"
	.string "大幅提升\n"
	.string "攻击。$"

BattleFrontier_Lounge7_Text_DefenseCurlDesc::
	.string "{CHN}蜷缩身体隐藏\n"
	.string "弱点并提升\n"
	.string "防御。$"

BattleFrontier_Lounge7_Text_SnoreDesc::
	.string "{CHN}响亮的攻击，\n"
	.string "只有在睡眠时\n"
	.string "才能使用。$"

BattleFrontier_Lounge7_Text_MudSlapDesc::
	.string "{CHN}向对手脸上\n"
	.string "泼泥，降低其\n"
	.string "命中率。$"

BattleFrontier_Lounge7_Text_SwiftDesc::
	.string "{CHN}喷射星形光线，\n"
	.string "绝对不会\n"
	.string "打偏。$"

BattleFrontier_Lounge7_Text_IcyWindDesc::
	.string "{CHN}冰冷的攻击，\n"
	.string "降低对手的\n"
	.string "速度。$"

BattleFrontier_Lounge7_Text_EndureDesc::
	.string "{CHN}忍耐一回合内\n"
	.string "的任何攻击，\n"
	.string "留下1HP。$"

BattleFrontier_Lounge7_Text_PsychUpDesc::
	.string "{CHN}复制对手的能力\n"
	.string "变化效果并\n"
	.string "加到自己身上。$"

BattleFrontier_Lounge7_Text_IcePunchDesc::
	.string "{CHN}冰冷的拳击，\n"
	.string "可能\n"
	.string "冻结对手。$"

BattleFrontier_Lounge7_Text_ThunderPunchDesc::
	.string "{CHN}带电的拳击，\n"
	.string "可能使对手\n"
	.string "陷入麻痹。$"

BattleFrontier_Lounge7_Text_FirePunchDesc::
	.string "{CHN}火焰的拳击，\n"
	.string "可能使对手\n"
	.string "陷入灼伤。$"
