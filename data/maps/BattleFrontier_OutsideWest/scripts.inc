BattleFrontier_OutsideWest_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideWest_OnTransition
	.byte 0

BattleFrontier_OutsideWest_OnTransition:
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	end

BattleFrontier_OutsideWest_EventScript_FerryAttendant::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_MayISeeYourTicket, MSGBOX_DEFAULT
	checkitem ITEM_SS_TICKET
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_OutsideWest_EventScript_NoSSTicket
	message BattleFrontier_OutsideWest_Text_WhereWouldYouLikeToGo
	waitmessage
	goto BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination
	end

BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination::
	multichoicedefault 18, 6, MULTI_SSTIDAL_BATTLE_FRONTIER, 2, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_OutsideWest_EventScript_FerryToSlateport
	case 1, BattleFrontier_OutsideWest_EventScript_FerryToLilycove
	case 2, BattleFrontier_OutsideWest_EventScript_CancelFerrySelect
	case MULTI_B_PRESSED, BattleFrontier_OutsideWest_EventScript_CancelFerrySelect
	end

BattleFrontier_OutsideWest_EventScript_NoSSTicket::
	msgbox BattleFrontier_OutsideWest_Text_MustHaveTicketToBoard, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_FerryToSlateport::
	msgbox BattleFrontier_OutsideWest_Text_SlateportItIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination
	msgbox BattleFrontier_OutsideWest_Text_PleaseBoardFerry, MSGBOX_DEFAULT
	call BattleFrontier_OutsideWest_EventScript_BoardFerry
	warp MAP_SLATEPORT_CITY_HARBOR, 8, 11
	waitstate
	release
	end

BattleFrontier_OutsideWest_EventScript_FerryToLilycove::
	msgbox BattleFrontier_OutsideWest_Text_LilycoveItIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination
	msgbox BattleFrontier_OutsideWest_Text_PleaseBoardFerry, MSGBOX_DEFAULT
	call BattleFrontier_OutsideWest_EventScript_BoardFerry
	warp MAP_LILYCOVE_CITY_HARBOR, 8, 11
	waitstate
	release
	end

BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination::
	message BattleFrontier_OutsideWest_Text_ThenWhereWouldYouLikeToGo
	waitmessage
	goto BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination
	end

BattleFrontier_OutsideWest_EventScript_BoardFerry::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	hideobjectat LOCALID_FRONTIER_FERRY_ATTENDANT, MAP_BATTLE_FRONTIER_OUTSIDE_WEST
	setvar VAR_0x8004, LOCALID_FRONTIER_SS_TIDAL
	call Common_EventScript_FerryDepartIsland
	return

BattleFrontier_OutsideWest_EventScript_CancelFerrySelect::
	msgbox BattleFrontier_OutsideWest_Text_SailWithUsAnotherTime, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_BattleDomeSign::
	msgbox BattleFrontier_OutsideWest_Text_BattleDomeSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattleFactorySign::
	msgbox BattleFrontier_OutsideWest_Text_BattleFactorySign, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattlePikeSign::
	msgbox BattleFrontier_OutsideWest_Text_BattlePikeSign, MSGBOX_SIGN
	end

/* Unused. Of note, Battle Tower is in the East section in the final release*/
BattleFrontier_OutsideWest_EventScript_UnusedNPC1::
	msgbox BattleFrontier_OutsideWest_Text_ThisIsBattleTower, MSGBOX_NPC
	end

/* Unused*/
BattleFrontier_OutsideWest_EventScript_UnusedNPC2::
	msgbox BattleFrontier_OutsideWest_Text_CantFindBattleTower, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Boy1::
	msgbox BattleFrontier_OutsideWest_Text_BestOutOfAllMyFriends, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Fisherman2::
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere
	waitmessage
	applymovement LOCALID_FRONTIER_FISHERMAN_2, Common_Movement_FaceAwayPlayer
	waitmovement 0
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_Man1::
	msgbox BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Maniac1::
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk
	end

BattleFrontier_OutsideWest_EventScript_Maniac2::
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk
	end

BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk::
	applymovement LOCALID_FRONTIER_MANIAC_1, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons, MSGBOX_DEFAULT
	applymovement LOCALID_FRONTIER_MANIAC_2, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons, MSGBOX_DEFAULT
	closemessage
	delay 25
	applymovement LOCALID_FRONTIER_MANIAC_1, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_FRONTIER_MANIAC_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_Camper::
	lock
	faceplayer
	delay 20
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_OutsideWest_EventScript_CamperAlreadyFacingFactory
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	msgbox BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_CamperFaceFactory::
	applymovement LOCALID_FRONTIER_CAMPER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_CamperAlreadyFacingFactory::
	return

BattleFrontier_OutsideWest_EventScript_Girl::
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper
	waitmessage
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_GirlShudderNorth
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_OutsideWest_EventScript_GirlShudderSouth
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_OutsideWest_EventScript_GirlShudderWest
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_OutsideWest_EventScript_GirlShudderEast
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_GirlShudderNorth::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderNorth
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderSouth::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderSouth
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderWest::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderWest
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderEast::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderEast
	waitmovement 0
	return

BattleFrontier_OutsideWest_Movement_GirlShudderNorth:
	walk_in_place_faster_down
	walk_in_place_faster_down
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderSouth:
	walk_in_place_faster_up
	walk_in_place_faster_up
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderWest:
	walk_in_place_faster_right
	walk_in_place_faster_right
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderEast:
	walk_in_place_faster_left
	walk_in_place_faster_left
	step_end

BattleFrontier_OutsideWest_EventScript_Woman2::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors, MSGBOX_DEFAULT
	random 2
	goto_if_eq VAR_RESULT, 1, BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors
	goto BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors
	end

BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors::
	msgbox BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors::
	msgbox BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Fisherman1::
	msgbox BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling, MSGBOX_NPC
	end

/* Unused*/
BattleFrontier_OutsideWest_EventScript_UnusedNPC3::
	msgbox BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Gentleman::
	msgbox BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Lass::
	msgbox BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_ExpertM::
	msgbox BattleFrontier_OutsideWest_Text_WontLetGentlemenBeatMe, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Man2::
	msgbox BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Woman1::
	msgbox BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_FatMan1::
	msgbox BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_FatMan2::
	msgbox BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Woman3::
	lock
	msgbox BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Boy2::
	lock
	msgbox BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_OldMan::
	msgbox BattleFrontier_OutsideWest_Text_DomeAceIsMine, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Man4::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_MAN_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_PokefanF::
	msgbox BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_Text_BattleDomeSign:
	.string "{CHN}这里是「对战巨蛋」！\n"
	.string "通往无敌巨星的舞台！$"

BattleFrontier_OutsideWest_Text_BattleFactorySign:
	.string "{CHN}这里是「对战工厂」！\n"
	.string "寻找最强大的宝可梦吧！$"

BattleFrontier_OutsideWest_Text_BattlePikeSign:
	.string "{CHN}这里是「对战管道」！\n"
	.string "从三条路径中选择一条！$"

BattleFrontier_OutsideWest_Text_ThisIsBattleTower:
	.string "{CHN}这里是「对战塔」。\p"
	.string "训练家们带着自己精心培育的\n"
	.string "宝可梦进行淘汰赛。$"

BattleFrontier_OutsideWest_Text_MayISeeYourTicket:
	.string "{CHN}您好，您是来乘坐渡轮的吗？\n"
	.string "请出示您的船票。$"

BattleFrontier_OutsideWest_Text_MustHaveTicketToBoard:
	.string "{CHN}{PLAYER}没有船票……\p"
	.string "非常抱歉。\p"
	.string "您必须有船票才能\n"
	.string "乘坐渡轮。$"

BattleFrontier_OutsideWest_Text_WhereWouldYouLikeToGo:
	.string "{CHN}{PLAYER}出示了船票。\p"
	.string "完美！这就够了！\p"
	.string "那么您想去哪里呢？$"

BattleFrontier_OutsideWest_Text_SlateportItIs:
	.string "{CHN}那就去凯那市吧！$"

BattleFrontier_OutsideWest_Text_LilycoveItIs:
	.string "{CHN}那就去水静市吧！$"

BattleFrontier_OutsideWest_Text_SailWithUsAnotherTime:
	.string "{CHN}请下次再来乘坐我们的渡轮吧！$"

BattleFrontier_OutsideWest_Text_PleaseBoardFerry:
	.string "{CHN}请上船等待出发。$"

BattleFrontier_OutsideWest_Text_ThenWhereWouldYouLikeToGo:
	.string "{CHN}那么，您想去哪里呢？$"

BattleFrontier_OutsideWest_Text_BestOutOfAllMyFriends:
	.string "{CHN}在所有朋友中我是最强的。\n"
	.string "但是在这里……\l"
	.string "我竟然一无是处！$"

BattleFrontier_OutsideWest_Text_CantFindBattleTower:
	.string "{CHN}我想去「对战塔」，\n"
	.string "但即使我手里有对战开拓区\l"
	.string "的地图也找不到。\p"
	.string "这地方实在是太大了！$"

BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere:
	.string "{CHN}我本来想一到就马上挑战的。\p"
	.string "但来的路上我晕船了……\n"
	.string "呕……$"

BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere:
	.string "{CHN}你知道的，不是任何人都能\n"
	.string "来到这里的。\p"
	.string "只有那些被认可为强大的训练家\n"
	.string "才能被带到这里。\p"
	.string "所以很多训练家甚至不知道\n"
	.string "对战开拓区的存在。$"

BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons:
	.string "{CHN}嘿，兄弟……\p"
	.string "你确定即使我们一只宝可梦\n"
	.string "都没有也能挑战吗？$"

BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons:
	.string "{CHN}呃……\n"
	.string "应该没问题的。\p"
	.string "我想……\p"
	.string "但是记得那个高大可怕的家伙吗？\n"
	.string "他说：「我借给你们宝可梦！」$"

BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons:
	.string "{CHN}那是「对战工厂」。\n"
	.string "你可以在那里租借强大的宝可梦。\p"
	.string "但我想知道。\n"
	.string "是谁在培育那些租借的宝可梦呢？$"

BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper:
	.string "{CHN}因为饭匙蛇，\n"
	.string "我不敢进入「对战管道」……\p"
	.string "但-但我都来了这里，\n"
	.string "我要努力征服一切！\l"
	.string "……发抖……$"

BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors:
	.string "{CHN}我们来玩石头剪刀布吧！\n"
	.string "一、二、三！\p"
	.string "………………$"

BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge:
	.string "{CHN}耶！我赢了！\n"
	.string "我要去挑战「对战管道」！$"

BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge:
	.string "{CHN}哦，不……\n"
	.string "我输了。\p"
	.string "看来我今天运气不太好。\n"
	.string "我把「对战管道」的挑战\l"
	.string "推迟到明天吧。$"

BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling:
	.string "{CHN}我想我是这里唯一一个，\n"
	.string "因为某种不明原因，\l"
	.string "宁愿钓鱼也不愿对战的人。\p"
	.string "咦？这里什么也钓不到？\n"
	.string "真令人失望……$"

BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol:
	.string "{CHN}今天，我要不停地战斗，\n"
	.string "无论如何，直到拿到象征为止。$"

BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome:
	.string "{CHN}哦？你要去挑战\n"
	.string "「对战巨蛋」吗？\p"
	.string "我祝你好运。\n"
	.string "让我们一起一路赢上去，\l"
	.string "在挑战中相见吧。$"

BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa:
	.string "{CHN}爷爷，这边！\n"
	.string "「对战巨蛋」在这里！\l"
	.string "加油，爷爷！$"

BattleFrontier_OutsideWest_Text_WontLetGentlemenBeatMe:
	.string "{CHN}啊，这里就是「对战巨蛋」？\n"
	.string "我不会让那些绅士打败我的！\p"
	.string "但入口在哪里呢？$"

BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo:
	.string "{CHN}不久之前这里还什么都没有。\p"
	.string "但是，你看看现在这地方！太惊人了！\n"
	.string "我要带我妈妈来看看。$"

BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier:
	.string "{CHN}我终于到达对战开拓区了！\p"
	.string "我一定会用我的容貌和实力\n"
	.string "吸引众人的目光！$"

BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople:
	.string "{CHN}咀嚼，咀嚼……\p"
	.string "看起来这个广场上\n"
	.string "到处都是厉害的人。\p"
	.string "咀嚼，咀嚼……$"

BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike:
	.string "{CHN}嘎嘣，咀嚼……\p"
	.string "前阵子，我在「对战管道」\n"
	.string "遇到了一个年长的女孩。\p"
	.string "她的眼神\n"
	.string "凶狠得可怕。\p"
	.string "嘎嘣，咀嚼……\p"
	.string "她大发雷霆：「你能不能\n"
	.string "别吃了！」然后狠狠揍了我一顿。\p"
	.string "那真是一次\n"
	.string "让人毛骨悚然的经历啊。\p"
	.string "嘎嘣，咀嚼……$"

BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet:
	.string "{CHN}啊？你听听你自己说的话？\n"
	.string "那算什么！\p"
	.string "哼，上次我为他加油的时候，\n"
	.string "我们的目光相遇，火花四溅！$"

BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering:
	.string "{CHN}什么什么？！\n"
	.string "噗！\p"
	.string "那只是因为\n"
	.string "我碰巧坐在你旁边！\p"
	.string "巨蛋王牌朝我们这边看，\n"
	.string "是因为我的加油声太响了！$"

BattleFrontier_OutsideWest_Text_DomeAceIsMine:
	.string "{CHN}哦，闭嘴！\n"
	.string "小声点！\p"
	.string "你们这些墙头草粉丝还是去\n"
	.string "给什么道馆馆主加油吧！\p"
	.string "巨蛋王牌是我的！\n"
	.string "他是我唯一的偶像！$"

BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers:
	.string "{CHN}那边那些吵吵闹闹的人……\p"
	.string "很难相信，但他们曾经\n"
	.string "是训练家，而且是优秀的训练家。\p"
	.string "他们曾经非常强大，\n"
	.string "也很有名气。\p"
	.string "但他们被某位训练家\n"
	.string "在一场锦标赛中彻底击败了。\p"
	.string "他们被打得如此惨烈，\n"
	.string "以至于对那位训练家着迷了。\p"
	.string "现在他们只是那位训练家的粉丝。\n"
	.string "他们现在每天都会去「对战巨蛋」\l"
	.string "为他们偶像加油。$"

BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier:
	.string "{CHN}我听到一个传闻，说有人\n"
	.string "在对战开拓区的某个地方\l"
	.string "看到了一只尾巴特别长的宝可梦。\p"
	.string "它一定很可爱。我确信……\p"
	.string "哦，挑战可以等一等。我觉得\n"
	.string "我非找到那只迷人的小生物不可！$"

