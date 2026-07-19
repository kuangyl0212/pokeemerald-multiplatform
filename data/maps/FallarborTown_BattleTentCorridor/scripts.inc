FallarborTown_BattleTentCorridor_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, FallarborTown_BattleTentCorridor_OnFrame
	.byte 0

FallarborTown_BattleTentCorridor_OnFrame:
	map_script_2 VAR_TEMP_0, 0, FallarborTown_BattleTentCorridor_EventScript_EnterCorridor
	.short 0

FallarborTown_BattleTentCorridor_EventScript_EnterCorridor::
	lockall
	setvar VAR_TEMP_0, 1
	applymovement LOCALID_FALLARBOR_TENT_CORRIDOR_ATTENDANT, FallarborTown_BattleTentCorridor_Movement_WalkToDoor
	applymovement LOCALID_PLAYER, FallarborTown_BattleTentCorridor_Movement_WalkToDoor
	waitmovement 0
	opendoor 2, 1
	waitdooranim
	applymovement LOCALID_FALLARBOR_TENT_CORRIDOR_ATTENDANT, FallarborTown_BattleTentCorridor_Movement_AttendantEnterDoor
	applymovement LOCALID_PLAYER, FallarborTown_BattleTentCorridor_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 2, 1
	waitdooranim
	setvar VAR_0x8006, 0
	warp MAP_FALLARBOR_TOWN_BATTLE_TENT_BATTLE_ROOM, 4, 4
	waitstate
	releaseall
	end

FallarborTown_BattleTentCorridor_Movement_WalkToDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

FallarborTown_BattleTentCorridor_Movement_PlayerEnterDoor:
	walk_up
FallarborTown_BattleTentCorridor_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end

/* Leftover text from when this was a Contest Hall in R/S*/
/* Unused*/
FallarborTown_ContestHall_Text_DoAllRightInPreliminary:
	.string "{CHN}我们在预赛中表现得还不错，\n"
	.string "但从来赢不了评审……\p"
	.string "也许这意味着我需要观察\n"
	.string "其他选手在做什么……$"

/* Unused*/
FallarborTown_ContestHall_Text_MonAllTheseRibbons:
	.string "{CHN}看！\n"
	.string "我的宝可梦赢得了所有这些缎带！\p"
	.string "你的宝可梦赢得过缎带吗？\n"
	.string "你可以在宝可梦领航员上查看。$"

/* Unused*/
FallarborTown_ContestHall_Text_CantWinEverywhere:
	.string "{CHN}我打不过道馆馆主……\p"
	.string "我赢不了任何华丽大赛……\p"
	.string "我到处跑来跑去，\n"
	.string "全都是徒劳……$"

/* Unused*/
FallarborTown_ContestHall_Text_SuperRankStage:
	.string "{CHN}宝可梦华丽大赛\n"
	.string "超级级舞台！$"
