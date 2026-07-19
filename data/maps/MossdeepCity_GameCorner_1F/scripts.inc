MossdeepCity_GameCorner_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MossdeepCity_GameCorner_1F_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, MossdeepCity_GameCorner_1F_OnWarp
	map_script MAP_SCRIPT_ON_LOAD, CableClub_OnLoad
	.byte 0

MossdeepCity_GameCorner_1F_OnWarp:
	map_script_2 VAR_CABLE_CLUB_STATE, USING_MINIGAME, CableClub_EventScript_CheckTurnAttendant
	.short 0

MossdeepCity_GameCorner_1F_OnFrame:
	map_script_2 VAR_CABLE_CLUB_STATE, USING_MINIGAME, CableClub_EventScript_ExitMinigameRoom
	.short 0

/* Script is redundant, the label in the goto also does lock and faceplayer*/
MossdeepCity_GameCorner_1F_EventScript_InfoMan::
	lock
	faceplayer
	goto MossdeepCity_GameCorner_1F_EventScript_InfoMan2
	release
	end

/* Script is redundant, the label in the goto also does lock and faceplayer*/
MossdeepCity_GameCorner_1F_EventScript_OldMan::
	lock
	faceplayer
	goto MossdeepCity_GameCorner_1F_EventScript_OldMan2
	release
	end


/* Everything below is leftover from RS*/
/* The house that was here in RS was moved to Sootopolis and replaced by the Game Corner*/
/* The text below is unused and duplicated in its replacement in Sootopolis City*/
/* And the BG Door event was moved inaccessibly into a wall*/

RS_MysteryEventsHouse_EventScript_Door::
	msgbox RS_MysteryEventsHouse_Text_DoorIsLocked, MSGBOX_SIGN
	end

RS_MysteryEventsHouse_Text_OldManGreeting:
	.string "{CHN}我年轻的时候，作为宝可梦训练家\n"
	.string "周游了世界。\p"
	.string "现在我成了个老古董，\n"
	.string "唯一的乐趣就是看年轻\l"
	.string "训练家们对战了。$"

RS_MysteryEventsHouse_Text_DoorIsLocked:
	.string "{CHN}门好像锁着。$"

RS_MysteryEventsHouse_Text_ChallengeVisitingTrainer:
	.string "{CHN}一位名叫{STR_VAR_1}的训练家\n"
	.string "正在拜访我家。\p"
	.string "你想要挑战\n"
	.string "{STR_VAR_1}吗？$"

RS_MysteryEventsHouse_Text_YouWontBattle:
	.string "{CHN}你不战斗吗？我很失望\n"
	.string "不能看到你战斗……$"

RS_MysteryEventsHouse_Text_KeepItToA3On3:
	.string "{CHN}哦，好好！\p"
	.string "但我的房子不是很结实。\p"
	.string "能不能请你们控制在\n"
	.string "3对3的比赛呢？$"

RS_MysteryEventsHouse_Text_SaveYourProgress:
	.string "{CHN}在你们两个战斗之前，你应该\n"
	.string "保存你的进度。$"

RS_MysteryEventsHouse_Text_HopeToSeeAGoodMatch:
	.string "{CHN}我希望能看到一场精彩的比赛！$"

RS_MysteryEventsHouse_Text_BattleTie:
	.string "{CHN}所以，变成了平局。\p"
	.string "那是一场精彩的比赛，\n"
	.string "双方都不肯退让一步！$"

RS_MysteryEventsHouse_Text_BattleWon:
	.string "{CHN}那太出色了！\p"
	.string "哇，就像看到了年轻时的\n"
	.string "我自己！$"

RS_MysteryEventsHouse_Text_BattleLost:
	.string "{CHN}啊，你太倒霉了！\p"
	.string "但这是一场精彩的比赛。\n"
	.string "希望你下次能赢。$"
