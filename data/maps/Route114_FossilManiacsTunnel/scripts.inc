Route114_FossilManiacsTunnel_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_FossilManiacsTunnel_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route114_FossilManiacsTunnel_OnLoad
	.byte 0

Route114_FossilManiacsTunnel_OnTransition:
	call_if_set FLAG_SYS_GAME_CLEAR, Route114_FossilManiacsTunnel_EventScript_MoveFossilManiac
	end

Route114_FossilManiacsTunnel_EventScript_MoveFossilManiac::
	setobjectxyperm LOCALID_FOSSIL_MANIAC, 6, 5
	setobjectmovementtype LOCALID_FOSSIL_MANIAC, MOVEMENT_TYPE_FACE_DOWN
	return

Route114_FossilManiacsTunnel_OnLoad:
	call_if_unset FLAG_SYS_GAME_CLEAR, Route114_FossilManiacsTunnel_EventScript_CloseDesertUnderpass
	end

Route114_FossilManiacsTunnel_EventScript_CloseDesertUnderpass::
	setmetatile 6, 1, METATILE_Fallarbor_RedRockWall, TRUE
	setmetatile 6, 2, METATILE_Fallarbor_RedRockWall, TRUE
	return

Route114_FossilManiacsTunnel_EventScript_ManiacMentionCaveIn::
	lockall
	applymovement LOCALID_FOSSIL_MANIAC, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox Route114_FossilManiacsTunnel_Text_NotSafeThatWay, MSGBOX_DEFAULT
	setvar VAR_FOSSIL_MANIAC_STATE, 2
	releaseall
	end

Route114_FossilManiacsTunnel_EventScript_FossilManiac::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_REVIVED_FOSSIL_MON, Route114_FossilManiacsTunnel_EventScript_PlayerRevivedFossil
	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil
	msgbox Route114_FossilManiacsTunnel_Text_LookInDesertForFossils, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil::
	msgbox Route114_FossilManiacsTunnel_Text_DevonCorpRevivingFossils, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_EventScript_PlayerRevivedFossil::
	msgbox Route114_FossilManiacsTunnel_Text_FossilsAreWonderful, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_Text_LookInDesertForFossils:
	.string "{CHN}我是化石狂人……\n"
	.string "我是个喜欢化石的好人……\p"
	.string "你想要化石吗？\p"
	.string "但这附近的化石都\n"
	.string "是我的……没有你的份……\p"
	.string "如果你实在想要化石，\n"
	.string "就去沙漠找找，那里\l"
	.string "的巨石和沙子下可能藏着\l"
	.string "化石……$"

Route114_FossilManiacsTunnel_Text_DevonCorpRevivingFossils:
	.string "{CHN}你找到了化石对吧？\n"
	.string "太好了……真令人向往……\p"
	.string "你打算拿那个化石\n"
	.string "怎么办？\p"
	.string "听说得文公司正在研究\n"
	.string "从化石中复活宝可梦\l"
	.string "……\p"
	.string "我喜欢我的化石，所以我绝不会\n"
	.string "做那种事……$"

Route114_FossilManiacsTunnel_Text_FossilsAreWonderful:
	.string "{CHN}化石真是太……奇妙了……\n"
	.string "真令人向往……$"

Route114_FossilManiacsTunnel_Text_NotSafeThatWay:
	.string "{CHN}哦……\n"
	.string "那边不安全……\p"
	.string "你知道的，我当时正在挖洞……\n"
	.string "结果整面墙都塌了……\p"
	.string "我想现在下面有一个\n"
	.string "巨大的洞窟……\p"
	.string "但我没去管它，因为我觉得\n"
	.string "那里没有化石……$"

