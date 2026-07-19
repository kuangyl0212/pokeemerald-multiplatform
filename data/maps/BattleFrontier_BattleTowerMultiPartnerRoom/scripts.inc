BattleFrontier_BattleTowerMultiPartnerRoom_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattleTowerMultiPartnerRoom_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattleTowerMultiPartnerRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_OnFrame
	.byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_OnResume:
	pyramid_resetparty
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnTransition:
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_1
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_2
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_3
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_4
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_5
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_6
	setflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_1
	setflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_2
	tower_loadpartners
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_3, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_4, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_5, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_6, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_7, OBJ_EVENT_GFX_BOY_1
	setvar VAR_TEMP_1, 1
	setvar VAR_TEMP_3, 1
	setobjectxyperm LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, 10, 2
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnWarp:
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth
	.short 0

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnFrame:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom
	.short 0

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom::
	lockall
	setvar VAR_TEMP_3, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom::
	lockall
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom
	waitmovement 0
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit
	waitmovement 0
	copyobjectxytoperm LOCALID_TOWER_PARTNER_ROOM_ATTENDANT
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner, MSGBOX_DEFAULT
	special HealPlayerParty
	setvar VAR_TEMP_1, 1
	releaseall
	end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom:
	walk_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit:
	walk_left
	walk_in_place_faster_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Attendant::
	lock
	faceplayer
	message BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner2, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge::
	frontier_set FRONTIER_DATA_RECORD_DISABLED, TRUE
	goto BattleFrontier_BattleTower_EventScript_WarpToLobbyLost
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator::
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor 10, 1
	waitdooranim
	call BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator
	closedoor 10, 1
	waitdooranim
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_ELEVATOR, 1, 6
	waitstate
	releaseall
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator::
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator
	waitmovement 0
	return

/* Unused*/
BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevatorEast:
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevatorEast
	waitmovement 0
	return

/* Unused*/
BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevatorWest:
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEneterElevatorWest
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator:
	walk_up
	walk_up
	set_invisible
	step_end

/* Functionally unused*/
BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevatorEast:
	walk_right
	walk_up
	set_invisible
	step_end

/* Functionally unused*/
BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEneterElevatorWest:
	walk_left
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner1::
	lock
	faceplayer
	setvar VAR_TEMP_2, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner::
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	tower_dopartnermsg PARTNER_MSGID_INTRO
	waitmessage
	waitbuttonpress
	tower_dopartnermsg PARTNER_MSGID_MON1
	waitmessage
	waitbuttonpress
	tower_dopartnermsg PARTNER_MSGID_MON2_ASK
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	tower_dopartnermsg PARTNER_MSGID_ACCEPT
	waitmessage
	waitbuttonpress
	closemessage
	call_if_ne VAR_FACING, DIR_SOUTH, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExitSouth
	removeobject VAR_LAST_TALKED
	setflag FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_TOWER_MULTI_PARTNER_ROOM, 10, 3
	waitstate
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner::
	tower_dopartnermsg PARTNER_MSGID_REJECT
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit::
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExitSouth::
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExitSouth
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExitSouth:
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner2::
	lock
	faceplayer
	setvar VAR_TEMP_2, 1
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner3::
	lock
	faceplayer
	setvar VAR_TEMP_2, 2
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner4::
	lock
	faceplayer
	setvar VAR_TEMP_2, 3
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner5::
	lock
	faceplayer
	setvar VAR_TEMP_2, 4
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner6::
	lock
	faceplayer
	setvar VAR_TEMP_2, 5
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner7::
	lock
	faceplayer
	setvar VAR_TEMP_2, 6
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner8::
	lock
	faceplayer
	setvar VAR_TEMP_2, 7
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner:
	.string "{CHN}请从这里的训练家\n"
	.string "中找一位搭档。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner:
	.string "{CHN}{PLAYER}，你还没有\n"
	.string "找到搭档组队。\p"
	.string "要放弃寻找并返回\n"
	.string "接待柜台吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner2:
	.string "{CHN}那么，请从这里的\n"
	.string "训练家中找一位搭档。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner::
	.string "{CHN}感谢你选择了搭档。\p"
	.string "我现在带你去\n"
	.string "多人对战室。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Intro::
	.string "{CHN}我是{STR_VAR_1}的第{STR_VAR_2}号学徒。\n"
	.string "你可以叫我{STR_VAR_3}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon1::
	.string "{CHN}按照{STR_VAR_1}的建议，\n"
	.string "我带了一只会{STR_VAR_2}的{STR_VAR_3}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "请让我和你组成双人队伍吧。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Accept::
	.string "{CHN}谢谢你！\n"
	.string "我现在就去登记。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Reject::
	.string "{CHN}我真的很想和你\n"
	.string "组成双人队伍，{PLAYER}……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Intro::
	.string "{CHN}我是{STR_VAR_1}的第{STR_VAR_2}号学徒。\n"
	.string "我的名字是{STR_VAR_3}。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon1::
	.string "{CHN}我听取了{STR_VAR_1}的建议，\n"
	.string "选择了一只会{STR_VAR_2}的{STR_VAR_3}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "请让我们组成双人队伍吧！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Accept::
	.string "{CHN}非常感谢！\n"
	.string "我很快就会完成登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Reject::
	.string "{CHN}{PLAYER}，我一直希望能\n"
	.string "和你搭档……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Intro::
	.string "{CHN}嗯，我叫{STR_VAR_3}，\n"
	.string "是{STR_VAR_1}的第{STR_VAR_2}号学徒。\p"
	.string "抽噎……\p"
	.string "对不起！\n"
	.string "紧张得我都哭了……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon1::
	.string "{CHN}{STR_VAR_3}给我建议，\n"
	.string "我有一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "抽噎……\n"
	.string "请、请和我组队吧！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Accept::
	.string "{CHN}哦，真的吗？你愿意？\n"
	.string "太棒了！太厉害了！哇呜！\p"
	.string "哦……对不起……\n"
	.string "我太高兴，都哭了……\p"
	.string "我马上就去登记。\n"
	.string "请你不要走开哦！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Reject::
	.string "{CHN}哦，可、可是……\n"
	.string "呜……哇啊啊啊！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Intro::
	.string "{CHN}嗨，你好！我是{STR_VAR_3}！\n"
	.string "我是{STR_VAR_1}的第{STR_VAR_2}号学徒！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon1::
	.string "{CHN}{STR_VAR_3}推荐了我的队伍。\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}，\n"
	.string "这就是我的队伍！很酷吧？\p"
	.string "所以来吧！\n"
	.string "让我们组成双人队伍！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Accept::
	.string "{CHN}耶！太好了！\n"
	.string "好，我去登记，好吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Reject::
	.string "{CHN}啊，为什么？\n"
	.string "我想和你组队，{PLAYER}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Intro::
	.string "{CHN}我是{STR_VAR_3}，是著名的{STR_VAR_1}\n"
	.string "的第{STR_VAR_2}号学徒！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon1::
	.string "{CHN}我请教了{STR_VAR_3}。\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}，\n"
	.string "这就是我的组合。\p"
	.string "请你和我一起\n"
	.string "组成双人队伍好吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Accept::
	.string "{CHN}谢谢你！\n"
	.string "我马上去登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Reject::
	.string "{CHN}{PLAYER}，我一直希望能和你\n"
	.string "组成双人队伍……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Intro::
	.string "{CHN}嗯……我真心高兴你\n"
	.string "愿意花时间和我说话。\p"
	.string "我是{STR_VAR_3}。\n"
	.string "是{STR_VAR_1}的第{STR_VAR_2}号学徒……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon1::
	.string "{CHN}{STR_VAR_3}给了我建议。\n"
	.string "我非常感激。\p"
	.string "我的队伍是一只会{STR_VAR_1}的{STR_VAR_2}\n"
	.string "和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon2Ask::
	.string "{CHN}一只会{STR_VAR_1}的{STR_VAR_2}。\n"
	.string "我知道我要求得太多了……\p"
	.string "我觉得你可能不愿意，\n"
	.string "但我可以成为你的搭档吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Accept::
	.string "{CHN}真的吗？我简直不敢相信！\n"
	.string "不敢相信你愿意让我加入！\l"
	.string "我……我不会让你失望的！\p"
	.string "嗯……如果真的可以，我现在\n"
	.string "就去登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Reject::
	.string "{CHN}哦……\n"
	.string "我就知道我不够好……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Intro::
	.string "{CHN}嗨，我是{STR_VAR_3}。\n"
	.string "我是{STR_VAR_1}的第{STR_VAR_2}号学徒！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon1::
	.string "{CHN}{STR_VAR_3}告诉我\n"
	.string "组成这样的队伍会很好：\l"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon2Ask::
	.string "{CHN}和一只会使用\n"
	.string "{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "不错吧？\n"
	.string "你要和我组队吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Accept::
	.string "{CHN}好的，很高兴加入你！\n"
	.string "希望你不会拖我后腿！\l"
	.string "我现在就去登记。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Reject::
	.string "{CHN}啊？你为什么拒绝我？\n"
	.string "你真不会看人！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Intro::
	.string "{CHN}我是{STR_VAR_3}，是一名铁人三项选手。\n"
	.string "我每天都很忙，要慢跑、\l"
	.string "训练，还要说唱。\p"
	.string "我同时也是{STR_VAR_1}的\n"
	.string "第{STR_VAR_2}号学徒。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon1::
	.string "{CHN}这是{STR_VAR_3}推荐的。\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的\n"
	.string "{STR_VAR_2}。\p"
	.string "我虽然很忙，但还是花了很多\n"
	.string "精力培养它们。\p"
	.string "让我们组成双人队伍\n"
	.string "挑战一下吧！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Accept::
	.string "{CHN}谢谢，就是这种精神！\n"
	.string "我去登记，你稍等哦？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Reject::
	.string "{CHN}我从百忙之中抽空\n"
	.string "来这里！你就饶了我吧！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Intro::
	.string "{CHN}嗨！\n"
	.string "最近怎么样？\p"
	.string "我是{STR_VAR_3}，是{STR_VAR_1}的\n"
	.string "第{STR_VAR_2}号学徒。很高兴认识你！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon1::
	.string "{CHN}听我说，听我说！你一定要听听\n"
	.string "{STR_VAR_3}推荐的宝可梦。\l"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}。\n"
	.string "当然我把它们培养得非常出色！\p"
	.string "所以，要组队吗？\n"
	.string "我相信这会是个很棒的组合！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Accept::
	.string "{CHN}耶，我觉得这会很有趣！\n"
	.string "我去登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Reject::
	.string "{CHN}哦，你真坏！\n"
	.string "我可是有人推荐的哦。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Intro::
	.string "{CHN}请允许我自我介绍。\n"
	.string "我是{STR_VAR_3}。\p"
	.string "我担任{STR_VAR_1}的\n"
	.string "第{STR_VAR_2}号学徒。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon1::
	.string "{CHN}我请教了{STR_VAR_3}\n"
	.string "的高明建议，培养了我的队伍：\l"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "请答应和我组成双人队伍！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Accept::
	.string "{CHN}哦……我太高兴了！\n"
	.string "我保证会全力以赴！\p"
	.string "当然我会去登记我们！\n"
	.string "请稍等！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Reject::
	.string "{CHN}我一直希望能和你组队，\n"
	.string "{PLAYER}……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Intro::
	.string "{CHN}哎呀！你跟我说话了！\n"
	.string "我……我太高兴了！\p"
	.string "我是{STR_VAR_3}！是{STR_VAR_1}的\n"
	.string "第{STR_VAR_2}号学徒！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon1::
	.string "{CHN}按照{STR_VAR_3}的建议，\n"
	.string "我培养了一只会{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的\n"
	.string "{STR_VAR_2}。\p"
	.string "请你满足我的愿望好吗？\n"
	.string "我想成为你的双人队伍搭档！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Accept::
	.string "{CHN}哎呀！我……我头晕目眩！\n"
	.string "太感谢你了！\l"
	.string "我马上就去登记我们！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Reject::
	.string "{CHN}哇！你一点都不同情我吗？\n"
	.string "但这样你显得更酷了……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Intro::
	.string "{CHN}哟嚯！我是{STR_VAR_1}的\n"
	.string "第{STR_VAR_2}号学徒！\p"
	.string "我叫{STR_VAR_3}，你好，你好！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon1::
	.string "{CHN}我的导师{STR_VAR_3}推荐了\n"
	.string "一只精通{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon2Ask::
	.string "{CHN}和一只精通{STR_VAR_1}的\n"
	.string "{STR_VAR_2}。\p"
	.string "不错吧？\n"
	.string "你愿意和我搭档吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Accept::
	.string "{CHN}好，太好了！\n"
	.string "我马上就完成登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Reject::
	.string "{CHN}哇啊！\n"
	.string "你真会算计，{PLAYER}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Intro::
	.string "{CHN}嘿！出大事了！今天是\n"
	.string "对战塔的最后一天！\p"
	.string "………………\n"
	.string "我开玩笑的！\p"
	.string "大家叫我{STR_VAR_3}，我自己也是！\n"
	.string "我是{STR_VAR_1}的第一千号学徒！\l"
	.string "其实，我是第{STR_VAR_2}号！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon1::
	.string "{CHN}{STR_VAR_3}给了我建议。\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}。\n"
	.string "每种我有十只！\l"
	.string "其实，每种只有一只！\p"
	.string "怎么样？\n"
	.string "想不想和我试试双打？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Accept::
	.string "{CHN}太好了！\n"
	.string "作为感谢我要送你一只宝可梦！\p"
	.string "开玩笑的！不过我真的会去\n"
	.string "登记，好吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Reject::
	.string "{CHN}哦，太冷酷了！我要为此\n"
	.string "毁掉对战塔！\p"
	.string "当然我不会的！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Intro::
	.string "{CHN}嘿，我在摇滚登场！\n"
	.string "宝可梦，由我掌控！\p"
	.string "我是说唱水手{STR_VAR_3}。\n"
	.string "别把我当成只会哭的人！\p"
	.string "我是{STR_VAR_1}的第{STR_VAR_2}号学徒。\n"
	.string "你可不要小看我！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon1::
	.string "{CHN}按照{STR_VAR_3}的建议，\n"
	.string "我组成了我引以为豪的队伍！\l"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的\n"
	.string "{STR_VAR_2}！\p"
	.string "我们的相遇值得纪念，\n"
	.string "用双人队伍的胜利来庆祝吧！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Accept::
	.string "{CHN}嘿，嘿，我喜欢你的风格！\n"
	.string "我们的登记，我去办妥！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Reject::
	.string "{CHN}哦，嘿，{PLAYER}，那太冷酷了！\n"
	.string "请恕我大胆直言！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Intro::
	.string "{CHN}耶嗬！\n"
	.string "哦，别跑！我只是开玩笑！\p"
	.string "你好！我是{STR_VAR_3}！\n"
	.string "我是{STR_VAR_1}的第{STR_VAR_2}号学徒！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon1::
	.string "{CHN}{STR_VAR_3}告诉了我该怎么做。\n"
	.string "所以我选了一只会{STR_VAR_1}的{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的\n"
	.string "{STR_VAR_2}。\p"
	.string "所以，怎么样？\n"
	.string "来吧，让我开心一下！\p"
	.string "求你了！\n"
	.string "让我加入你，别让我难过！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Accept::
	.string "{CHN}耶啊！我运气真好！\n"
	.string "这真让我开心！\p"
	.string "在我们上战场之前，\n"
	.string "我马上去登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Reject::
	.string "{CHN}你拒绝我？\n"
	.string "{PLAYER}，你让我皱眉头了！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Intro::
	.string "{CHN}咳咳！\p"
	.string "哦，对不起，我感冒了。\n"
	.string "不过我的宝可梦没事。\p"
	.string "我叫{STR_VAR_3}，是{STR_VAR_1}的\n"
	.string "第{STR_VAR_2}号学徒。咳咳！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon1::
	.string "{CHN}我把{STR_VAR_3}的建议记在心里，\n"
	.string "组成了我的队伍：\l"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "我每天都在训练它们，\n"
	.string "风雨无阻。\p"
	.string "所以我才感冒了，\n"
	.string "我想。\p"
	.string "这就是我。\n"
	.string "想成为我的双打搭档吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Accept::
	.string "{CHN}谢谢，我很感激！\n"
	.string "咳咳，咳咳！\l"
	.string "稍等，我去登记。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Reject::
	.string "{CHN}哦，你不愿意？\n"
	.string "{PLAYER}，我觉得我们会是很好的一对。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Intro::
	.string "{CHN}哦，你好！\n"
	.string "这真让人紧张。\p"
	.string "我是{STR_VAR_3}。\n"
	.string "我是{STR_VAR_1}的第{STR_VAR_2}号学徒。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon1::
	.string "{CHN}{STR_VAR_3}说这支队伍会很好——\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "我对此有点不自在，\n"
	.string "但你能让我加入你吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Accept::
	.string "{CHN}哦，天哪，谢谢你！\n"
	.string "我有点害羞，但我会尽力的！\p"
	.string "我去把登记办好。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Reject::
	.string "{CHN}哦，请不要说不！\n"
	.string "我已经够不自在的了……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Intro::
	.string "{CHN}我是{STR_VAR_3}，这是实话。\n"
	.string "我是{STR_VAR_1}的第{STR_VAR_2}号学徒。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon1::
	.string "{CHN}{STR_VAR_3}推荐了我的队伍。\p"
	.string "因为那建议听起来很真诚，\n"
	.string "我决定带着\l"
	.string "我会{STR_VAR_1}的{STR_VAR_2}和$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon2Ask::
	.string "{CHN}我会{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "如果可能的话，我希望你能接纳我\n"
	.string "成为你的双人队伍搭档。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Accept::
	.string "{CHN}你真的愿意接纳我？\n"
	.string "不然就太糟糕了。\p"
	.string "既然你答应了，那就没问题。\n"
	.string "我去登记我们两个。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Reject::
	.string "{CHN}嗯？那你为什么要拒绝？\n"
	.string "你在开玩笑吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassIntro::
	.string "{CHN}我是{STR_VAR_1}，是一名短裙少女！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon1::
	.string "{CHN}我有的是一只会{STR_VAR_1}的\n"
	.string "{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}。\n"
	.string "这就是我带来的。\p"
	.string "你愿意成为我的搭档吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassAccept::
	.string "{CHN}谢谢你！\n"
	.string "我去登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassReject::
	.string "{CHN}你不想成为我的搭档？\n"
	.string "你以后会后悔的！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterIntro::
	.string "{CHN}你好！\p"
	.string "我是短裤小子{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon1::
	.string "{CHN}想知道我有什么吗？\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "你会成为我的双人队伍搭档，\n"
	.string "对吧？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterAccept::
	.string "{CHN}耶！\n"
	.string "我去登记，好吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterReject::
	.string "{CHN}啊！要是你愿意和我的宝可梦\n"
	.string "组成双人队伍，我们就会无敌！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerIntro::
	.string "{CHN}呀吼！\n"
	.string "我是登山客{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon1::
	.string "{CHN}知道我带了什么吗？\n"
	.string "我会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon2Ask::
	.string "{CHN}和我会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "听起来不错吧？\n"
	.string "要组成双人队伍吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerAccept::
	.string "{CHN}呀吼！\n"
	.string "那我去登记了。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerReject::
	.string "{CHN}我本来希望你能和我\n"
	.string "并肩作战的。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyIntro::
	.string "{CHN}你好！\n"
	.string "我是{STR_VAR_1}，是一名美少女！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon1::
	.string "{CHN}你知道我在培养什么吗？\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "你觉得怎么样？\n"
	.string "要不要一起组成双人队伍？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyAccept::
	.string "{CHN}太好了！\n"
	.string "我现在就去登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyReject::
	.string "{CHN}真令人失望！\p"
	.string "我们两个在一起——本可以\n"
	.string "成为最强的！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanIntro::
	.string "{CHN}哟！\p"
	.string "你知道我是谁吗？\n"
	.string "我是钓客{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon1::
	.string "{CHN}我带了一支队伍，\n"
	.string "有一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "那，怎么样？\n"
	.string "你愿意和我并肩作战吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanAccept::
	.string "{CHN}好，好！\n"
	.string "交给我吧！\p"
	.string "我现在就去登记我们。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanReject::
	.string "{CHN}我们本来配合得很完美……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyIntro::
	.string "{CHN}很高兴认识你。\n"
	.string "我是{STR_VAR_1}，是一位大小姐。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon1::
	.string "{CHN}我带着一支队伍，\n"
	.string "有一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "希望我能让你满意。\n"
	.string "因为我希望你能成为我的搭档。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyAccept::
	.string "{CHN}我衷心感谢你。\n"
	.string "我会去办登记手续。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyReject::
	.string "{CHN}我确信你会后悔\n"
	.string "没有让我做你的搭档。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFIntro::
	.string "{CHN}我是铁人三项选手{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon1::
	.string "{CHN}我有的是……\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\n"
	.string "这就是我的组合！\p"
	.string "拜托？\n"
	.string "你愿意和我组成双人队伍吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFAccept::
	.string "{CHN}天哪，谢谢！\n"
	.string "我去柜台登记。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFReject::
	.string "{CHN}我们两个在一起，肯定\n"
	.string "会很强！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherIntro::
	.string "{CHN}嗨！\n"
	.string "我是捕虫少年{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon1::
	.string "{CHN}看看我有什么！\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "所以，听着！\n"
	.string "你想组成双人队伍吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherAccept::
	.string "{CHN}收到！\p"
	.string "我去柜台\n"
	.string "办登记手续。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherReject::
	.string "{CHN}啊，我的宝可梦很厉害的。\n"
	.string "希望你不会后悔！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMIntro::
	.string "{CHN}你好！\n"
	.string "我是男生学生{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon1::
	.string "{CHN}我培养的是一只\n"
	.string "会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的\n"
	.string "{STR_VAR_2}。\p"
	.string "还不错吧，你觉得呢？\n"
	.string "你愿意组成双人队伍吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMAccept::
	.string "{CHN}非常感谢！\n"
	.string "我去把登记办好。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMReject::
	.string "{CHN}那太可惜了……\p"
	.string "我本来希望作为你的搭档\n"
	.string "向你学习的……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyIntro::
	.string "{CHN}哟！让我告诉你我是谁！\n"
	.string "我是富家少爷{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon1::
	.string "{CHN}猜猜我有什么！\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "我愿意给你一个机会，\n"
	.string "和我组成双人队伍。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyAccept::
	.string "{CHN}聪明的选择！\p"
	.string "我会很快完成\n"
	.string "登记手续！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyReject::
	.string "{CHN}你居然拒绝我这样的人？\n"
	.string "你肯定会后悔那个决定！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltIntro::
	.string "{CHN}嘿！\n"
	.string "我是空手道王{STR_VAR_1}。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon1::
	.string "{CHN}作为我的伙伴，我有\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的\n"
	.string "{STR_VAR_2}。\p"
	.string "请满足我的愿望！\n"
	.string "让我成为你的双打搭档！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltAccept::
	.string "{CHN}嘿！\n"
	.string "我马上就去登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltReject::
	.string "{CHN}我明白了……希望下次\n"
	.string "我们再见面时能有机会……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFIntro::
	.string "{CHN}嗨，你好！\n"
	.string "我是{STR_VAR_1}，是玩水小孩！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon1::
	.string "{CHN}我告诉你我有什么。\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\n"
	.string "我可以加入你的双人队伍吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFAccept::
	.string "{CHN}谢谢你！\n"
	.string "我现在就去登记我们！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFReject::
	.string "{CHN}如果我们能成为搭档，我们\n"
	.string "就会变得很强！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacIntro::
	.string "{CHN}你好……\n"
	.string "我是灵异少女{STR_VAR_1}……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon1::
	.string "{CHN}我带着一只会{STR_VAR_1}的\n"
	.string "{STR_VAR_2}，还有一只$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon2Ask::
	.string "{CHN}会{STR_VAR_1}的{STR_VAR_2}……\p"
	.string "我恳求你……\n"
	.string "和我组成双人队伍……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacAccept::
	.string "{CHN}我谢谢你……\n"
	.string "我会去登记我们……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacReject::
	.string "{CHN}我多么渴望加入你……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMIntro::
	.string "{CHN}你好？我是{STR_VAR_1}，\n"
	.string "是一名宝可梦培育家！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon1::
	.string "{CHN}我在培养几只不错的！\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "怎么样？\n"
	.string "想和我组成双人队伍吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMAccept::
	.string "{CHN}非常感谢！\p"
	.string "我去办登记手续，\n"
	.string "你在这里等着！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMReject::
	.string "{CHN}我本来很期待成为\n"
	.string "你的搭档……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFIntro::
	.string "{CHN}哎，你好！\n"
	.string "我是铁人三项选手{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon1::
	.string "{CHN}想知道我跑的时候带什么吗？\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "怎么样？\n"
	.string "想和我组成双人队伍吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFAccept::
	.string "{CHN}干得好！\p"
	.string "我会很快把登记\n"
	.string "办好！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFReject::
	.string "{CHN}你和我，我们本可以成为最棒的。\n"
	.string "太可惜了……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMIntro::
	.string "{CHN}嘿，你好！我叫{STR_VAR_1}！\n"
	.string "我是铁人三项选手！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon1::
	.string "{CHN}我带着我耐力强的队伍跑步——\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "还不错吧？\n"
	.string "我们应该一起组成双人队伍！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMAccept::
	.string "{CHN}好！\n"
	.string "我马上去登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMReject::
	.string "{CHN}我真的想作为你的双人\n"
	.string "队伍搭档战斗……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlIntro::
	.string "{CHN}我是格斗女孩{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon1::
	.string "{CHN}我锻炼了一只会{STR_VAR_1}的\n"
	.string "{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "你喜欢这个组合吗？\n"
	.string "你和我搭档怎么样？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlAccept::
	.string "{CHN}哎，谢谢！\p"
	.string "我现在就去\n"
	.string "把登记办好！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlReject::
	.string "{CHN}和你在一起，我觉得我们本可以组成\n"
	.string "最强的双人队伍……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMIntro::
	.string "{CHN}我是铁人三项选手{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon1::
	.string "{CHN}我一直带着一只会{STR_VAR_1}的\n"
	.string "{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "我们可以组成双人队伍。\n"
	.string "那不是很好吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMAccept::
	.string "{CHN}谢谢你！\p"
	.string "我去登记我们，\n"
	.string "现在就去！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMReject::
	.string "{CHN}啊，太可惜了。我们本可以成为\n"
	.string "最强的双人队伍！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMIntro::
	.string "{CHN}我？\n"
	.string "我是玩水小孩{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon1::
	.string "{CHN}我带了什么？\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "嘿？\n"
	.string "你会和我组队，对吧？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMAccept::
	.string "{CHN}好！\p"
	.string "我去登记！\n"
	.string "让我们一起出色吧！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMReject::
	.string "{CHN}我的宝可梦肯定很强……\n"
	.string "太可惜你不想组队。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristIntro::
	.string "{CHN}耶嘿！\n"
	.string "叫我吉他手{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon1::
	.string "{CHN}看看我的随从！\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "耶嘿！挺狂野的吧？\n"
	.string "我们得在双人队伍里合奏一曲！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristAccept::
	.string "{CHN}耶嘿！好极了！\n"
	.string "我现在就去办登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristReject::
	.string "{CHN}我的宝可梦摇滚得很！\n"
	.string "你会后悔的，我告诉你！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanIntro::
	.string "{CHN}很高兴认识你。\n"
	.string "我是{STR_VAR_1}，是一位绅士。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon1::
	.string "{CHN}我身边有我信赖的\n"
	.string "会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "能否请你和我组成双人\n"
	.string "队伍搭档？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanAccept::
	.string "{CHN}啊，感谢你的信任。\n"
	.string "我会去办登记手续。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanReject::
	.string "{CHN}那真是太遗憾了……\p"
	.string "我期待下一次\n"
	.string "机会……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMIntro::
	.string "{CHN}你好，我是{STR_VAR_1}，\n"
	.string "是一名宝可梦粉丝。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon1::
	.string "{CHN}我现在带着一只\n"
	.string "会{STR_VAR_1}招式的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "你觉得怎么样？\n"
	.string "要做我的双打搭档吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMAccept::
	.string "{CHN}谢谢你！\n"
	.string "我会去办登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMReject::
	.string "{CHN}我的宝可梦是顶级的……\n"
	.string "太可惜你不会欣赏。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMIntro::
	.string "{CHN}嗯！\n"
	.string "我是{STR_VAR_1}，是一名专家！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon1::
	.string "{CHN}我锻炼的宝可梦是\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "你觉得和我组成双人队伍怎么样？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMAccept::
	.string "{CHN}嗯！\n"
	.string "我马上去登记我们！\l"
	.string "让我们一起尽力而为！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMReject::
	.string "{CHN}我希望你的选择\n"
	.string "确实是正确的……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFIntro::
	.string "{CHN}你好，你好。\n"
	.string "我是{STR_VAR_1}，是一名专家。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon1::
	.string "{CHN}我彻底地培养了我的宝可梦。\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}——\n"
	.string "这就是我的队伍。\p"
	.string "你不想和我组队吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFAccept::
	.string "{CHN}好，好。\n"
	.string "我马上去办登记。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFReject::
	.string "{CHN}也许下次我们再见面时\n"
	.string "可以组成一支队伍。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerIntro::
	.string "{CHN}我是龙使者{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon1::
	.string "{CHN}我一直在锻炼的队伍是\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "怎么样？\n"
	.string "想做我的搭档吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerAccept::
	.string "{CHN}好，我会尽力！\n"
	.string "我现在去登记，好吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerReject::
	.string "{CHN}你找不到多少\n"
	.string "比我更强的搭档！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperIntro::
	.string "{CHN}我是鸟使{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon1::
	.string "{CHN}我有什么宝可梦？\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "你不觉得我们会是不错的\n"
	.string "双人队伍吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperAccept::
	.string "{CHN}太好了，谢谢！\n"
	.string "我会去办登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperReject::
	.string "{CHN}我的宝可梦和我都很强。\n"
	.string "真让人失望。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyIntro::
	.string "{CHN}我是忍者小子{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon1::
	.string "{CHN}我的宝可梦队伍有一只\n"
	.string "会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "让我们一起组成双人队伍！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyAccept::
	.string "{CHN}耶！\n"
	.string "让我去登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyReject::
	.string "{CHN}你会后悔没有我强壮的\n"
	.string "宝可梦在你身边的！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyIntro::
	.string "{CHN}你好！\n"
	.string "我是阳伞小姐{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon1::
	.string "{CHN}现在我身边陪伴的是我的\n"
	.string "会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon2Ask::
	.string "{CHN}和一只会\n"
	.string "{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "不错吧？\n"
	.string "愿意和我们一起组成双人队伍吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyAccept::
	.string "{CHN}非常感谢！\p"
	.string "我去柜台登记。\n"
	.string "让我们不要让彼此失望！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyReject::
	.string "{CHN}我的宝可梦非常强。\n"
	.string "真令人失望……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacIntro::
	.string "{CHN}你好。\n"
	.string "我是{STR_VAR_1}，是一名昆虫狂热者！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon1::
	.string "{CHN}我找到了我的宝可梦。\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}——\n"
	.string "这就是我找到的。\p"
	.string "我能不能让你有兴趣\n"
	.string "组成双人队伍？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacAccept::
	.string "{CHN}好！\n"
	.string "明白了！\p"
	.string "我很快就会办完登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacReject::
	.string "{CHN}有了我找到的宝可梦，我们\n"
	.string "不会输的……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorIntro::
	.string "{CHN}嘿，你好！\n"
	.string "我是水手{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon1::
	.string "{CHN}让我给你看看我的骄傲！\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "你当然不会拒绝\n"
	.string "我。我们会组队的，对吧？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorAccept::
	.string "{CHN}我期待的就是这个！\n"
	.string "我现在去登记。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorReject::
	.string "{CHN}我们本可以横扫\n"
	.string "对手！太可惜了！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorIntro::
	.string "{CHN}嗨，我是{STR_VAR_1}。\n"
	.string "我是一名收藏家。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon1::
	.string "{CHN}我收藏中的宝石是\n"
	.string "我会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "不错吧？\n"
	.string "我们应该一起组队。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorAccept::
	.string "{CHN}哦，好！\p"
	.string "我们不要浪费时间了。\n"
	.string "我去登记我们两个。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorReject::
	.string "{CHN}哎，那真令人不快。\n"
	.string "你不欣赏我的宝可梦。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMIntro::
	.string "{CHN}你好，我是{STR_VAR_1}。\n"
	.string "我是一名宝可梦护林员。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon1::
	.string "{CHN}陪着我的是一只\n"
	.string "会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "你不觉得我们会是不错的\n"
	.string "双人队伍吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMAccept::
	.string "{CHN}太棒了！\n"
	.string "我现在就办登记。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMReject::
	.string "{CHN}下次，选我的宝可梦，\n"
	.string "好吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFIntro::
	.string "{CHN}我叫{STR_VAR_1}。\n"
	.string "我是宝可梦护林员！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon1::
	.string "{CHN}让我告诉你我的队伍。我有\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "你愿意和我的小队\n"
	.string "组成双人队伍吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFAccept::
	.string "{CHN}我们会发挥出最好的水平！\n"
	.string "我马上就办完登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFReject::
	.string "{CHN}我希望下次你能选我的\n"
	.string "宝可梦。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyIntro::
	.string "{CHN}很高兴认识你。我是{STR_VAR_1}。\n"
	.string "我自认是一名芳香姐姐。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon1::
	.string "{CHN}我和一只会{STR_VAR_1}的\n"
	.string "{STR_VAR_2}一起旅行，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon2Ask::
	.string "{CHN}和一只会\n"
	.string "{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "希望它们能让你中意。\n"
	.string "你愿意做我的搭档吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyAccept::
	.string "{CHN}我很荣幸你接受了。\n"
	.string "我现在就去登记。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyReject::
	.string "{CHN}如果下次我们见面时能组成\n"
	.string "双人队伍，那真是太好了。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacIntro::
	.string "{CHN}想知道我是谁吗？\n"
	.string "我是{STR_VAR_1}，遗迹狂热者！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon1::
	.string "{CHN}我带的宝可梦是\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "有趣吧？\n"
	.string "你和我搭档怎么样？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacAccept::
	.string "{CHN}那是个明智的决定！\n"
	.string "我去办登记手续。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacReject::
	.string "{CHN}嗯……\n"
	.string "我觉得我的宝可梦挺强……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMIntro::
	.string "{CHN}我是酷酷训练家{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon1::
	.string "{CHN}我现在有的宝可梦是\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}。\n"
	.string "酷吧？\p"
	.string "你不觉得如果我们组成\n"
	.string "双人队伍会很酷吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMAccept::
	.string "{CHN}酷！\n"
	.string "我马上去办登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMReject::
	.string "{CHN}我以为我们会成为\n"
	.string "史上最棒的队伍。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFIntro::
	.string "{CHN}我是酷酷训练家{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon1::
	.string "{CHN}我一直在培养的队伍有一只\n"
	.string "会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "听起来还行吗？\n"
	.string "我们成为双打搭档怎么样？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFAccept::
	.string "{CHN}听起来没问题！\n"
	.string "我得去办登记了。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFReject::
	.string "{CHN}我在想我们会成为\n"
	.string "一支很强的队伍……$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacIntro::
	.string "{CHN}嘿！\n"
	.string "我是{STR_VAR_1}，宝可梦狂热者！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon1::
	.string "{CHN}像我这样的人有什么？\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}，\n"
	.string "就是这些！\p"
	.string "来吧！\n"
	.string "我们组成双人队伍去闯荡吧！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacAccept::
	.string "{CHN}好选择！\n"
	.string "我去登记我们两个！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacReject::
	.string "{CHN}我的宝可梦很凶猛！\n"
	.string "如果你后悔了可不是我的错！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerIntro::
	.string "{CHN}哟，你好！\n"
	.string "我是点火小子{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon1::
	.string "{CHN}你知道我的训练练出了什么吗？\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "怎么样，你觉得呢？\n"
	.string "想组成双人队伍吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerAccept::
	.string "{CHN}好！\n"
	.string "我去办登记。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerReject::
	.string "{CHN}答应我下次我们再见面时\n"
	.string "和我组队。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperIntro::
	.string "{CHN}我是{STR_VAR_1}，是野营少年！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon1::
	.string "{CHN}我在培养一只\n"
	.string "会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "你觉得组队会很有趣吗？\n"
	.string "我敢肯定会的！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperAccept::
	.string "{CHN}耶！\n"
	.string "我去登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperReject::
	.string "{CHN}下次，好吗？\n"
	.string "我想加入你的队伍。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerIntro::
	.string "{CHN}你好！\n"
	.string "我是{STR_VAR_1}，是野餐少女！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon1::
	.string "{CHN}我带的宝可梦是\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "你有兴趣和我\n"
	.string "组成双人队伍吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerAccept::
	.string "{CHN}哎，谢谢你！\n"
	.string "我现在去办登记。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerReject::
	.string "{CHN}如果下次能让我加入你\n"
	.string "就好了。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMIntro::
	.string "{CHN}我是超能力者{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon1::
	.string "{CHN}我培养的两个是\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "你愿意和我组成\n"
	.string "双人队伍吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMAccept::
	.string "{CHN}当然！\n"
	.string "我去办登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMReject::
	.string "{CHN}如果我们再见面，那时我希望能\n"
	.string "和你组队。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFIntro::
	.string "{CHN}我是{STR_VAR_1}。\n"
	.string "我是一名超能力者。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon1::
	.string "{CHN}一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}——\n"
	.string "是我的弟子。\p"
	.string "组成双人队伍搭档\n"
	.string "这主意不让你感兴趣吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFAccept::
	.string "{CHN}谢谢你。\n"
	.string "我去办登记。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFReject::
	.string "{CHN}希望下次还有机会\n"
	.string "结成同盟。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFIntro::
	.string "{CHN}我是女生学生{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon1::
	.string "{CHN}一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的\n"
	.string "{STR_VAR_2}，是我的宝可梦组合。\p"
	.string "请让我成为你的\n"
	.string "双人队伍搭档好吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFAccept::
	.string "{CHN}哦，谢谢你！\n"
	.string "我马上去柜台登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFReject::
	.string "{CHN}拜托？\n"
	.string "下次我可以加入你吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFIntro::
	.string "{CHN}嗨呀！我叫{STR_VAR_1}！\n"
	.string "我是一名宝可梦培育家！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon1::
	.string "{CHN}我培养的宝可梦是\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "听起来有趣吗？\n"
	.string "那我们组成双人队伍怎么样？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFAccept::
	.string "{CHN}好嘞！\n"
	.string "登记就交给我吧！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFReject::
	.string "{CHN}下次你一定要和我组队，\n"
	.string "好吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFIntro::
	.string "{CHN}我是{STR_VAR_1}，我很自豪地\n"
	.string "说我是一名宝可梦粉丝。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon1::
	.string "{CHN}我培养的心肝宝可梦是\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "它们不是最可爱的吗？\n"
	.string "我们应该组成一支队伍！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFAccept::
	.string "{CHN}谢谢你，亲爱的！\n"
	.string "我这就去登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFReject::
	.string "{CHN}我的心肝宝可梦是最棒的，\n"
	.string "我要让你知道。真讨厌！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFIntro::
	.string "{CHN}嗨，我是游泳女孩{STR_VAR_1}。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon1::
	.string "{CHN}一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的\n"
	.string "{STR_VAR_2}，是我培养的。\p"
	.string "你和我，让我们组成双人队伍吧。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFAccept::
	.string "{CHN}酷！\n"
	.string "我去登记我们两个。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFReject::
	.string "{CHN}如果我们再见面，你欠我\n"
	.string "一支双人队伍！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMIntro::
	.string "{CHN}最近怎么样？\n"
	.string "我是{STR_VAR_1}，是铁人三项选手。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon1::
	.string "{CHN}我有几只不错的宝可梦。\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "如果我们能组成双人队伍\n"
	.string "就好了，怎么样？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMAccept::
	.string "{CHN}好极了！\n"
	.string "我登记时你稍等，好吗？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMReject::
	.string "{CHN}我希望下次你能让我\n"
	.string "加入你，怎么样？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFIntro::
	.string "{CHN}我是铁人三项选手{STR_VAR_1}！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon1::
	.string "{CHN}一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon2Ask::
	.string "{CHN}和另一只会\n"
	.string "{STR_VAR_1}的{STR_VAR_2}。这就是我的组合。\p"
	.string "你觉得怎么样？\n"
	.string "我说，我们会是不错的队伍。$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFAccept::
	.string "{CHN}我喜欢这个回答！\n"
	.string "我会很快办完登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFReject::
	.string "{CHN}你会再给我一次结成\n"
	.string "搭档的机会，对吧？$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMIntro::
	.string "{CHN}嗨，你好！你好！\n"
	.string "我是{STR_VAR_1}，是游泳男孩！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon1::
	.string "{CHN}看看我一直在培养什么！\n"
	.string "一只会{STR_VAR_1}的{STR_VAR_2}，$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon2Ask::
	.string "{CHN}和一只会{STR_VAR_1}的{STR_VAR_2}！\p"
	.string "不错吧？\n"
	.string "组队也不错！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMAccept::
	.string "{CHN}非常感谢！\n"
	.string "我去办这个登记！$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMReject::
	.string "{CHN}如果我们再见面，你必须和我\n"
	.string "组队。你会的，对吧？$"

