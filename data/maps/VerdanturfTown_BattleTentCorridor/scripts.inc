VerdanturfTown_BattleTentCorridor_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VerdanturfTown_BattleTentCorridor_OnFrame
	.byte 0

VerdanturfTown_BattleTentCorridor_OnFrame:
	map_script_2 VAR_TEMP_0, 0, VerdanturfTown_BattleTentCorridor_EventScript_EnterCorridor
	.short 0

VerdanturfTown_BattleTentCorridor_EventScript_EnterCorridor::
	lockall
	setvar VAR_TEMP_0, 1
	applymovement LOCALID_VERDANTURF_TENT_CORRIDOR_ATTENDANT, VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor
	applymovement LOCALID_PLAYER, VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor
	waitmovement 0
	opendoor 2, 1
	waitdooranim
	applymovement LOCALID_VERDANTURF_TENT_CORRIDOR_ATTENDANT, VerdanturfTown_BattleTentCorridor_Movement_AttendantEnterDoor
	applymovement LOCALID_PLAYER, VerdanturfTown_BattleTentCorridor_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 2, 1
	waitdooranim
	setvar VAR_0x8006, 0
	warp MAP_VERDANTURF_TOWN_BATTLE_TENT_BATTLE_ROOM, 6, 5
	waitstate
	releaseall
	end

VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

VerdanturfTown_BattleTentCorridor_Movement_PlayerEnterDoor:
	walk_up
VerdanturfTown_BattleTentCorridor_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end


/* Leftover text from when this was a Contest Hall in R/S*/
/* Unused*/
VerdanturfTown_ContestHall_Text_WhichContestYouEntering:
	.string "{CHN}你要参加哪个华丽大赛？\n"
	.string "想听个建议吗？\p"
	.string "在任何华丽大赛中，比如可爱\n"
	.string "大赛，我认为第一回合不会只\l"
	.string "以可爱度来评判你。\p"
	.string "你需要研究出更好的方法\n"
	.string "来培育宝可梦。$"

/* Unused*/
VerdanturfTown_ContestHall_Text_RaisedMonToBeCute:
	.string "{CHN}我把我的宝可梦培育得很可爱。\p"
	.string "我发现可以让宝可梦参加\n"
	.string "可爱华丽大赛！\p"
	.string "我真庆幸我用爱心\n"
	.string "培育了我的宝可梦…$"

/* Unused*/
VerdanturfTown_ContestHall_Text_MyMonRules:
	.string "{CHN}我的宝可梦最棒了！\p"
	.string "它既帅气、强壮又美丽、可爱，\n"
	.string "而且聪明。它很完美！\p"
	.string "我索性去参加每一个\n"
	.string "华丽大赛并赢得胜利。$"

/* Unused*/
VerdanturfTown_ContestHall_Text_NormalRankStage:
	.string "{CHN}宝可梦华丽大赛\n"
	.string "普通级舞台！$"

