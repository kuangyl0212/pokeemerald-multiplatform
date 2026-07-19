BattleFrontier_BattlePyramidFloor_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattlePyramidFloor_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePyramidFloor_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattlePyramidFloor_OnTransition
	.byte 0

BattleFrontier_BattlePyramidFloor_OnFrame:
	map_script_2 VAR_TEMP_D, 1, BattleFrontier_BattlePyramidFloor_EventScript_UpdateLight
	map_script_2 VAR_TEMP_PLAYING_PYRAMID_MUSIC, 0, BattleFrontier_BattlePyramidFloor_EventScript_PlayPyramidMusic
	map_script_2 VAR_TEMP_F, 1, BattleFrontier_BattlePyramidFloor_EventScript_ShowMapName
	.short 0

BattleFrontier_BattlePyramidFloor_EventScript_UpdateLight::
	lockall
	/* pyramid_updatelight, cant use macro because it straddles the loop*/
	setvar VAR_0x8004, BATTLE_PYRAMID_FUNC_UPDATE_LIGHT
	setvar VAR_0x8005, 4
	setvar VAR_0x8006, PYRAMID_LIGHT_INCR_RADIUS
	setvar VAR_0x8007, SE_SAVE
	setvar VAR_RESULT, 0
BattleFrontier_BattlePyramidFloor_EventScript_UpdateLightLoop::
	special CallBattlePyramidFunction
	delay 2
	goto_if_ne VAR_RESULT, 2, BattleFrontier_BattlePyramidFloor_EventScript_UpdateLightLoop
	setvar VAR_TEMP_D, 0
	releaseall
	end

BattleFrontier_BattlePyramidFloor_EventScript_ShowMapName::
	special ShowMapNamePopup
	setvar VAR_TEMP_F, 0
	end

BattleFrontier_BattlePyramidFloor_EventScript_PlayPyramidMusic::
	playbgm MUS_B_PYRAMID, FALSE
	setvar VAR_TEMP_PLAYING_PYRAMID_MUSIC, 1
	end

BattleFrontier_BattlePyramidFloor_OnResume:
	pyramid_setfloorpal
	frontier_getstatus
	switch VAR_TEMP_CHALLENGE_STATUS
	case 0, BattleFrontier_BattlePyramidFloor_EventScript_ReadyChallenge
	case CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePyramid_EventScript_WarpToLobby
	case CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePyramidFloor_EventScript_ReadyChallenge
	frontier_get FRONTIER_DATA_BATTLE_OUTCOME
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, BattleFrontier_BattlePyramidFloor_EventScript_ResetParty
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, BattleFrontier_BattlePyramidFloor_EventScript_ResetParty
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidFloor_EventScript_ResetParty
	goto_if_eq VAR_RESULT, B_OUTCOME_LOST, BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	goto_if_eq VAR_RESULT, B_OUTCOME_DREW, BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	goto_if_eq VAR_RESULT, B_OUTCOME_FORFEITED, BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	frontier_isbattletype BATTLE_TYPE_TRAINER  /* VAR_RESULT seems to be ignored here*/
	setvar VAR_TEMP_D, 1
BattleFrontier_BattlePyramidFloor_EventScript_ResetParty::
	pyramid_resetparty
	end

BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST
	pyramid_set PYRAMID_DATA_TRAINER_FLAGS, 255
BattleFrontier_BattlePyramid_EventScript_WarpToLobby::
	pyramid_updatelight 0, PYRAMID_LIGHT_SET_RADIUS
	pyramid_clearhelditems
	special HealPlayerParty
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_LOBBY, 7, 13
	waitstate
	end

BattleFrontier_BattlePyramidFloor_EventScript_ReadyChallenge::
	pyramid_save CHALLENGE_STATUS_SAVING
	special SavePlayerParty
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	pyramid_settrainers
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	setvar VAR_TEMP_F, 1
	end

BattleFrontier_BattlePyramidFloor_OnTransition:
	call BattleFrontier_BattlePyramidFloor_EventScript_SetLightRadius
	setvar VAR_TEMP_F, 1
	end

BattleFrontier_BattlePyramidFloor_EventScript_SetLightRadius::
	pyramid_updatelight 32, PYRAMID_LIGHT_SET_RADIUS
	return

BattlePyramid_WarpToNextFloor::
	call BattleFrontier_EventScript_IncrementWinStreak
	frontier_get FRONTIER_DATA_BATTLE_NUM  /* Floor number*/
	addvar VAR_RESULT, 1
	frontier_set FRONTIER_DATA_BATTLE_NUM, VAR_RESULT
	goto_if_eq VAR_RESULT, 7, BattlePyramid_WarpToTop
	pyramid_seedfloor
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_RESULT, 0
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR, 1, 1
	waitstate
	end

BattlePyramid_WarpToTop::
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_TOP, 17, 17
	waitstate
	end

/* TRAINER_PHILLIP is used as a placeholder*/
BattlePyramid_TrainerBattle::
	trainerbattle TRAINER_BATTLE_PYRAMID, TRAINER_PHILLIP, LOCALID_NONE, BattleFacility_TrainerBattle_PlaceholderText, BattleFacility_TrainerBattle_PlaceholderText
	pyramid_showhint
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BattlePyramid_FindItemBall::
	pyramid_setitem
	callstd STD_FIND_ITEM
	goto_if_eq VAR_0x8007, 0, BattlePyramid_FindItemBallEnd
	pyramid_hideitem
BattlePyramid_FindItemBallEnd::
	end

BattlePyramid_Retire::
	goto BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost

/* Also used by Trainer Hill*/
BattleFacility_TrainerBattle_PlaceholderText:
	.string "{CHN}这是一条示例消息。$"

gText_BattlePyramidConfirmRest::
	.string "{CHN}你的对战金字塔挑战\n"
	.string "将被保存，你可以暂时退出。\l"
	.string "可以吗？$"

gText_BattlePyramidConfirmRetire::
	.string "{CHN}你确定要退出\n"
	.string "金字塔挑战吗？$"

BattlePyramid_Text_ExitHintUp1::
	.string "{CHN}这层的出口在\n"
	.string "那个方向：{UP_ARROW}$"

BattlePyramid_Text_ExitHintLeft1::
	.string "{CHN}这层的出口在\n"
	.string "那个方向：{LEFT_ARROW}$"

BattlePyramid_Text_ExitHintRight1::
	.string "{CHN}这层的出口在\n"
	.string "那个方向：{RIGHT_ARROW}$"

BattlePyramid_Text_ExitHintDown1::
	.string "{CHN}这层的出口在\n"
	.string "那个方向：{DOWN_ARROW}$"

BattlePyramid_Text_ExitHintUp2::
	.string "{CHN}这层的出口在\n"
	.string "{UP_ARROW}方向。$"

BattlePyramid_Text_ExitHintLeft2::
	.string "{CHN}这层的出口在\n"
	.string "{LEFT_ARROW}方向。$"

BattlePyramid_Text_ExitHintRight2::
	.string "{CHN}这层的出口在\n"
	.string "{RIGHT_ARROW}方向。$"

BattlePyramid_Text_ExitHintDown2::
	.string "{CHN}这层的出口在\n"
	.string "{DOWN_ARROW}方向。$"

BattlePyramid_Text_ExitHintUp3::
	.string "{CHN}出口在\n"
	.string "{UP_ARROW}那边。$"

BattlePyramid_Text_ExitHintLeft3::
	.string "{CHN}出口在\n"
	.string "{LEFT_ARROW}那边。$"

BattlePyramid_Text_ExitHintRight3::
	.string "{CHN}出口在\n"
	.string "{RIGHT_ARROW}那边。$"

BattlePyramid_Text_ExitHintDown3::
	.string "{CHN}出口在\n"
	.string "{DOWN_ARROW}那边。$"

BattlePyramid_Text_ExitHintUp4::
	.string "{CHN}这层的出口在\n"
	.string "{UP_ARROW}方向的某处。$"

BattlePyramid_Text_ExitHintLeft4::
	.string "{CHN}这层的出口在\n"
	.string "{LEFT_ARROW}方向的某处。$"

BattlePyramid_Text_ExitHintRight4::
	.string "{CHN}这层的出口在\n"
	.string "{RIGHT_ARROW}方向的某处。$"

BattlePyramid_Text_ExitHintDown4::
	.string "{CHN}这层的出口在\n"
	.string "{DOWN_ARROW}方向的某处。$"

BattlePyramid_Text_ExitHintUp5::
	.string "{CHN}出口？\n"
	.string "在{UP_ARROW}那边。$"

BattlePyramid_Text_ExitHintLeft5::
	.string "{CHN}出口？\n"
	.string "在{LEFT_ARROW}那边。$"

BattlePyramid_Text_ExitHintRight5::
	.string "{CHN}出口？\n"
	.string "在{RIGHT_ARROW}那边。$"

BattlePyramid_Text_ExitHintDown5::
	.string "{CHN}出口？\n"
	.string "在{DOWN_ARROW}那边。$"

BattlePyramid_Text_ExitHintUp6::
	.string "{CHN}出口正好在\n"
	.string "{UP_ARROW}方向。$"

BattlePyramid_Text_ExitHintLeft6::
	.string "{CHN}出口正好在\n"
	.string "{LEFT_ARROW}方向。$"

BattlePyramid_Text_ExitHintRight6::
	.string "{CHN}出口正好在\n"
	.string "{RIGHT_ARROW}方向。$"

BattlePyramid_Text_ExitHintDown6::
	.string "{CHN}出口正好在\n"
	.string "{DOWN_ARROW}方向。$"

BattlePyramid_Text_EightItemsRemaining1::
	.string "{CHN}你在找道具吗？\p"
	.string "还有八个道具\n"
	.string "等待发现。$"

BattlePyramid_Text_SevenItemsRemaining1::
	.string "{CHN}你在找道具吗？\p"
	.string "还有七个道具\n"
	.string "等待发现。$"

BattlePyramid_Text_SixItemsRemaining1::
	.string "{CHN}你在找道具吗？\p"
	.string "还有六个道具\n"
	.string "等待发现。$"

BattlePyramid_Text_FiveItemsRemaining1::
	.string "{CHN}你在找道具吗？\p"
	.string "还有五个道具\n"
	.string "等待发现。$"

BattlePyramid_Text_FourItemsRemaining1::
	.string "{CHN}你在找道具吗？\p"
	.string "还有四个道具\n"
	.string "等待发现。$"

BattlePyramid_Text_ThreeItemsRemaining1::
	.string "{CHN}你在找道具吗？\p"
	.string "还有三个道具\n"
	.string "等待发现。$"

BattlePyramid_Text_TwoItemsRemaining1::
	.string "{CHN}你在找道具吗？\p"
	.string "还有两个道具\n"
	.string "等待发现。$"

BattlePyramid_Text_OneItemRemaining1::
	.string "{CHN}你在找道具吗？\p"
	.string "还有一个道具\n"
	.string "等待发现。$"

BattlePyramid_Text_ZeroItemsRemaining1::
	.string "{CHN}你在找道具吗？\p"
	.string "已经没有\n"
	.string "可发现的道具了！$"

BattlePyramid_Text_EightItemsRemaining2::
	.string "{CHN}因为你赢了，我告诉你\n"
	.string "一个小秘密！\p"
	.string "这里有八个\n"
	.string "散落的道具。$"

BattlePyramid_Text_SevenItemsRemaining2::
	.string "{CHN}因为你赢了，我告诉你\n"
	.string "一个小秘密！\p"
	.string "还有七个\n"
	.string "散落的道具。$"

BattlePyramid_Text_SixItemsRemaining2::
	.string "{CHN}因为你赢了，我告诉你\n"
	.string "一个小秘密！\p"
	.string "还有六个\n"
	.string "散落的道具。$"

BattlePyramid_Text_FiveItemsRemaining2::
	.string "{CHN}因为你赢了，我告诉你\n"
	.string "一个小秘密！\p"
	.string "还有五个\n"
	.string "散落的道具。$"

BattlePyramid_Text_FourItemsRemaining2::
	.string "{CHN}因为你赢了，我告诉你\n"
	.string "一个小秘密！\p"
	.string "还有四个\n"
	.string "散落的道具。$"

BattlePyramid_Text_ThreeItemsRemaining2::
	.string "{CHN}因为你赢了，我告诉你\n"
	.string "一个小秘密！\p"
	.string "还有三个\n"
	.string "散落的道具。$"

BattlePyramid_Text_TwoItemsRemaining2::
	.string "{CHN}因为你赢了，我告诉你\n"
	.string "一个小秘密！\p"
	.string "还有两个\n"
	.string "散落的道具。$"

BattlePyramid_Text_OneItemRemaining2::
	.string "{CHN}因为你赢了，我告诉你\n"
	.string "一个小秘密！\p"
	.string "只剩一个\n"
	.string "散落的道具。$"

BattlePyramid_Text_ZeroItemsRemaining2::
	.string "{CHN}因为你赢了，我告诉你\n"
	.string "一个小秘密！\p"
	.string "已经没有\n"
	.string "散落的道具了。$"

BattlePyramid_Text_EightItemsRemaining3::
	.string "{CHN}你的道具储备怎么样了？\p"
	.string "我估计这层还有八个道具\n"
	.string "等待被发现。$"

BattlePyramid_Text_SevenItemsRemaining3::
	.string "{CHN}你的道具储备怎么样了？\p"
	.string "我估计这层还有七个道具\n"
	.string "等待被发现。$"

BattlePyramid_Text_SixItemsRemaining3::
	.string "{CHN}你的道具储备怎么样了？\p"
	.string "我估计这层还有六个道具\n"
	.string "等待被发现。$"

BattlePyramid_Text_FiveItemsRemaining3::
	.string "{CHN}你的道具储备怎么样了？\p"
	.string "我估计这层还有五个道具\n"
	.string "等待被发现。$"

BattlePyramid_Text_FourItemsRemaining3::
	.string "{CHN}你的道具储备怎么样了？\p"
	.string "我估计这层还有四个道具\n"
	.string "等待被发现。$"

BattlePyramid_Text_ThreeItemsRemaining3::
	.string "{CHN}你的道具储备怎么样了？\p"
	.string "我估计这层还有三个道具\n"
	.string "等待被发现。$"

BattlePyramid_Text_TwoItemsRemaining3::
	.string "{CHN}你的道具储备怎么样了？\p"
	.string "我估计这层还有两个道具\n"
	.string "等待被发现。$"

BattlePyramid_Text_OneItemRemaining3::
	.string "{CHN}你的道具储备怎么样了？\p"
	.string "我估计这层只剩一个道具\n"
	.string "等待被发现。$"

BattlePyramid_Text_ZeroItemsRemaining3::
	.string "{CHN}你的道具储备怎么样了？\p"
	.string "我估计这层已经没有\n"
	.string "道具等待被发现了。\l"
	.string "保重！$"

BattlePyramid_Text_EightItemsRemaining4::
	.string "{CHN}你很强，所以你赢得了\n"
	.string "一个提示！\p"
	.string "地上似乎还有八个\n"
	.string "道具。$"

BattlePyramid_Text_SevenItemsRemaining4::
	.string "{CHN}你很强，所以你赢得了\n"
	.string "一个提示！\p"
	.string "地上似乎还有七个\n"
	.string "道具。$"

BattlePyramid_Text_SixItemsRemaining4::
	.string "{CHN}你很强，所以你赢得了\n"
	.string "一个提示！\p"
	.string "地上似乎还有六个\n"
	.string "道具。$"

BattlePyramid_Text_FiveItemsRemaining4::
	.string "{CHN}你很强，所以你赢得了\n"
	.string "一个提示！\p"
	.string "地上似乎还有五个\n"
	.string "道具。$"

BattlePyramid_Text_FourItemsRemaining4::
	.string "{CHN}你很强，所以你赢得了\n"
	.string "一个提示！\p"
	.string "地上似乎还有四个\n"
	.string "道具。$"

BattlePyramid_Text_ThreeItemsRemaining4::
	.string "{CHN}你很强，所以你赢得了\n"
	.string "一个提示！\p"
	.string "地上似乎还有三个\n"
	.string "道具。$"

BattlePyramid_Text_TwoItemsRemaining4::
	.string "{CHN}你很强，所以你赢得了\n"
	.string "一个提示！\p"
	.string "地上似乎还有两个\n"
	.string "道具。$"

BattlePyramid_Text_OneItemRemaining4::
	.string "{CHN}你很强，所以你赢得了\n"
	.string "一个提示！\p"
	.string "地上似乎只剩一个\n"
	.string "道具了。$"

BattlePyramid_Text_ZeroItemsRemaining4::
	.string "{CHN}你很强，所以你赢得了\n"
	.string "一个提示！\p"
	.string "地上似乎已经没有\n"
	.string "道具了。$"

BattlePyramid_Text_EightItemsRemaining5::
	.string "{CHN}在这层金字塔里，\n"
	.string "我听说有八个道具……$"

BattlePyramid_Text_SevenItemsRemaining5::
	.string "{CHN}在这层金字塔里，\n"
	.string "我听说有七个道具……$"

BattlePyramid_Text_SixItemsRemaining5::
	.string "{CHN}在这层金字塔里，\n"
	.string "我听说有六个道具……$"

BattlePyramid_Text_FiveItemsRemaining5::
	.string "{CHN}在这层金字塔里，\n"
	.string "我听说有五个道具……$"

BattlePyramid_Text_FourItemsRemaining5::
	.string "{CHN}在这层金字塔里，\n"
	.string "我听说有四个道具……$"

BattlePyramid_Text_ThreeItemsRemaining5::
	.string "{CHN}在这层金字塔里，\n"
	.string "我听说有三个道具……$"

BattlePyramid_Text_TwoItemsRemaining5::
	.string "{CHN}在这层金字塔里，\n"
	.string "我听说有两个道具……$"

BattlePyramid_Text_OneItemRemaining5::
	.string "{CHN}在这层金字塔里，\n"
	.string "我听说有一个道具……$"

BattlePyramid_Text_ZeroItemsRemaining5::
	.string "{CHN}在这层金字塔里，\n"
	.string "我听说没有道具……$"

BattlePyramid_Text_EightItemsRemaining6::
	.string "{CHN}你收集到道具了吗？\p"
	.string "我相信这层还有八个\n"
	.string "道具。$"

BattlePyramid_Text_SevenItemsRemaining6::
	.string "{CHN}你收集到道具了吗？\p"
	.string "我相信这层还有七个\n"
	.string "道具。$"

BattlePyramid_Text_SixItemsRemaining6::
	.string "{CHN}你收集到道具了吗？\p"
	.string "我相信这层还有六个\n"
	.string "道具。$"

BattlePyramid_Text_FiveItemsRemaining6::
	.string "{CHN}你收集到道具了吗？\p"
	.string "我相信这层还有五个\n"
	.string "道具。$"

BattlePyramid_Text_FourItemsRemaining6::
	.string "{CHN}你收集到道具了吗？\p"
	.string "我相信这层还有四个\n"
	.string "道具。$"

BattlePyramid_Text_ThreeItemsRemaining6::
	.string "{CHN}你收集到道具了吗？\p"
	.string "我相信这层还有三个\n"
	.string "道具。$"

BattlePyramid_Text_TwoItemsRemaining6::
	.string "{CHN}你收集到道具了吗？\p"
	.string "我相信这层还有两个\n"
	.string "道具。$"

BattlePyramid_Text_OneItemRemaining6::
	.string "{CHN}你收集到道具了吗？\p"
	.string "我相信这层还有一个\n"
	.string "道具。$"

BattlePyramid_Text_ZeroItemsRemaining6::
	.string "{CHN}你收集到道具了吗？\p"
	.string "我相信这层已经没有\n"
	.string "道具了。$"

BattlePyramid_Text_SevenTrainersRemaining1::
	.string "{CHN}你真是太厉害了！\p"
	.string "但除了我，\n"
	.string "还有七位强力的训练家！$"

BattlePyramid_Text_SixTrainersRemaining1::
	.string "{CHN}你真是太厉害了！\p"
	.string "但除了我，\n"
	.string "还有六位强力的训练家！$"

BattlePyramid_Text_FiveTrainersRemaining1::
	.string "{CHN}你真是太厉害了！\p"
	.string "但除了我，\n"
	.string "还有五位强力的训练家！$"

BattlePyramid_Text_FourTrainersRemaining1::
	.string "{CHN}你真是太厉害了！\p"
	.string "但除了我，\n"
	.string "还有四位强力的训练家！$"

BattlePyramid_Text_ThreeTrainersRemaining1::
	.string "{CHN}你真是太厉害了！\p"
	.string "但除了我，\n"
	.string "还有三位强力的训练家！$"

BattlePyramid_Text_TwoTrainersRemaining1::
	.string "{CHN}你真是太厉害了！\p"
	.string "但除了我，\n"
	.string "还有两位强力的训练家！$"

BattlePyramid_Text_OneTrainersRemaining1::
	.string "{CHN}你真是太厉害了！\p"
	.string "但除了我，\n"
	.string "还有一位强力的训练家！$"

BattlePyramid_Text_ZeroTrainersRemaining1::
	.string "{CHN}你真是太厉害了！\p"
	.string "已经没有人\n"
	.string "能打败你了！$"

BattlePyramid_Text_SevenTrainersRemaining2::
	.string "{CHN}真是太气人了！\p"
	.string "但还有七位训练家！\n"
	.string "总有人会让你吃瘪的！$"

BattlePyramid_Text_SixTrainersRemaining2::
	.string "{CHN}真是太气人了！\p"
	.string "但还有六位训练家！\n"
	.string "总有人会让你吃瘪的！$"

BattlePyramid_Text_FiveTrainersRemaining2::
	.string "{CHN}真是太气人了！\p"
	.string "但还有五位训练家！\n"
	.string "总有人会让你吃瘪的！$"

BattlePyramid_Text_FourTrainersRemaining2::
	.string "{CHN}真是太气人了！\p"
	.string "但还有四位训练家！\n"
	.string "总有人会让你吃瘪的！$"

BattlePyramid_Text_ThreeTrainersRemaining2::
	.string "{CHN}真是太气人了！\p"
	.string "但还有三位训练家！\n"
	.string "总有人会让你吃瘪的！$"

BattlePyramid_Text_TwoTrainersRemaining2::
	.string "{CHN}真是太气人了！\p"
	.string "但还有两位训练家！\n"
	.string "总有人会让你吃瘪的！$"

BattlePyramid_Text_OneTrainersRemaining2::
	.string "{CHN}真是太气人了！\p"
	.string "但还有一位训练家！\n"
	.string "你一定会吃瘪的！$"

BattlePyramid_Text_ZeroTrainersRemaining2::
	.string "{CHN}真是太气人了！\p"
	.string "但已经没有训练家\n"
	.string "能与你交手了！$"

BattlePyramid_Text_SevenTrainersRemaining3::
	.string "{CHN}真了不起！\p"
	.string "但这层还有七位训练家。\n"
	.string "你能全部击败吗？$"

BattlePyramid_Text_SixTrainersRemaining3::
	.string "{CHN}真了不起！\p"
	.string "但这层还有六位训练家。\n"
	.string "你能全部击败吗？$"

BattlePyramid_Text_FiveTrainersRemaining3::
	.string "{CHN}真了不起！\p"
	.string "但这层还有五位训练家。\n"
	.string "你能全部击败吗？$"

BattlePyramid_Text_FourTrainersRemaining3::
	.string "{CHN}真了不起！\p"
	.string "但这层还有四位训练家。\n"
	.string "你能全部击败吗？$"

BattlePyramid_Text_ThreeTrainersRemaining3::
	.string "{CHN}真了不起！\p"
	.string "但这层还有三位训练家。\n"
	.string "你能全部击败吗？$"

BattlePyramid_Text_TwoTrainersRemaining3::
	.string "{CHN}真了不起！\p"
	.string "但这层还有两位训练家。\n"
	.string "你能全部击败吗？$"

BattlePyramid_Text_OneTrainersRemaining3::
	.string "{CHN}真了不起！\p"
	.string "但这层还有一位训练家。\n"
	.string "你能取胜吗？$"

BattlePyramid_Text_ZeroTrainersRemaining3::
	.string "{CHN}真了不起！\p"
	.string "你已经击败了这层\n"
	.string "所有的训练家。$"

BattlePyramid_Text_SevenTrainersRemaining4::
	.string "{CHN}也许你能横扫\n"
	.string "这层剩下的七位训练家。$"

BattlePyramid_Text_SixTrainersRemaining4::
	.string "{CHN}也许你能横扫\n"
	.string "这层剩下的六位训练家。$"

BattlePyramid_Text_FiveTrainersRemaining4::
	.string "{CHN}也许你能横扫\n"
	.string "这层剩下的五位训练家。$"

BattlePyramid_Text_FourTrainersRemaining4::
	.string "{CHN}也许你能横扫\n"
	.string "这层剩下的四位训练家。$"

BattlePyramid_Text_ThreeTrainersRemaining4::
	.string "{CHN}也许你能横扫\n"
	.string "这层剩下的三位训练家。$"

BattlePyramid_Text_TwoTrainersRemaining4::
	.string "{CHN}也许你能横扫\n"
	.string "这层剩下的两位训练家。$"

BattlePyramid_Text_OneTrainersRemaining4::
	.string "{CHN}也许你能击败\n"
	.string "这层最后一位训练家完成横扫。$"

BattlePyramid_Text_ZeroTrainersRemaining4::
	.string "{CHN}现在已经没有人\n"
	.string "能击败你了……$"

BattlePyramid_Text_SevenTrainersRemaining5::
	.string "{CHN}你也许有能力击败\n"
	.string "剩下的七位专家训练家。$"

BattlePyramid_Text_SixTrainersRemaining5::
	.string "{CHN}你也许有能力击败\n"
	.string "剩下的六位专家训练家。$"

BattlePyramid_Text_FiveTrainersRemaining5::
	.string "{CHN}你也许有能力击败\n"
	.string "剩下的五位专家训练家。$"

BattlePyramid_Text_FourTrainersRemaining5::
	.string "{CHN}你也许有能力击败\n"
	.string "剩下的四位专家训练家。$"

BattlePyramid_Text_ThreeTrainersRemaining5::
	.string "{CHN}你也许有能力击败\n"
	.string "剩下的三位专家训练家。$"

BattlePyramid_Text_TwoTrainersRemaining5::
	.string "{CHN}你也许有能力击败\n"
	.string "剩下的两位专家训练家。$"

BattlePyramid_Text_OneTrainersRemaining5::
	.string "{CHN}你也许有能力击败\n"
	.string "剩下的那位专家训练家。$"

BattlePyramid_Text_ZeroTrainersRemaining5::
	.string "{CHN}你的实力无可挑剔。\p"
	.string "这里已经没有训练家\n"
	.string "有任何机会击败你了。$"

BattlePyramid_Text_SevenTrainersRemaining6::
	.string "{CHN}你能继续战胜\n"
	.string "剩下的七位训练家吗？$"

BattlePyramid_Text_SixTrainersRemaining6::
	.string "{CHN}你能继续战胜\n"
	.string "剩下的六位训练家吗？$"

BattlePyramid_Text_FiveTrainersRemaining6::
	.string "{CHN}你能继续战胜\n"
	.string "剩下的五位训练家吗？$"

BattlePyramid_Text_FourTrainersRemaining6::
	.string "{CHN}你能继续战胜\n"
	.string "剩下的四位训练家吗？$"

BattlePyramid_Text_ThreeTrainersRemaining6::
	.string "{CHN}你能继续战胜\n"
	.string "剩下的三位训练家吗？$"

BattlePyramid_Text_TwoTrainersRemaining6::
	.string "{CHN}你能继续战胜\n"
	.string "剩下的两位训练家吗？$"

BattlePyramid_Text_OneTrainersRemaining6::
	.string "{CHN}你能继续战胜\n"
	.string "最后那位训练家吗？$"

BattlePyramid_Text_ZeroTrainersRemaining6::
	.string "{CHN}现在已经没有训练家\n"
	.string "能与你交手了……$"
