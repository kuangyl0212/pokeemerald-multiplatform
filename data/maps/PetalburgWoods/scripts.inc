PetalburgWoods_MapScripts::
	.byte 0

PetalburgWoods_EventScript_DevonResearcherLeft::
	lockall
	call PetalburgWoods_EventScript_DevonResearcherIntro
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherApproachPlayerLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_HaveYouSeenShroomish, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaEntrance
	waitmovement 0
	msgbox PetalburgWoods_Text_IWasGoingToAmbushYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaApproachResearcherLeft
	waitmovement 0
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_Text_HandOverThosePapers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherFleeToPlayerLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_YouHaveToHelpMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaApproachPlayer
	waitmovement 0
	msgbox PetalburgWoods_Text_NoOneCrossesTeamAqua, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_PETALBURG_WOODS, PetalburgWoods_Text_YoureKiddingMe
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaBackOff
	waitmovement 0
	call PetalburgWoods_EventScript_DevonResearcherPostBattle
	applymovement LOCALID_PLAYER, PetalburgWoods_Movement_WatchResearcherLeave
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherExitLeft
	waitmovement 0
	goto PetalburgWoods_EventScript_RemoveDevonResearcher
	end

PetalburgWoods_EventScript_DevonResearcherRight::
	lockall
	call PetalburgWoods_EventScript_DevonResearcherIntro
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherApproachPlayerRight
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_HaveYouSeenShroomish, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaEntrance
	waitmovement 0
	msgbox PetalburgWoods_Text_IWasGoingToAmbushYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaApproachResearcherRight
	waitmovement 0
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_Text_HandOverThosePapers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherFleeToPlayerRight
	waitmovement 0
	msgbox PetalburgWoods_Text_YouHaveToHelpMe, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_Text_NoOneCrossesTeamAqua, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_PETALBURG_WOODS, PetalburgWoods_Text_YoureKiddingMe
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaBackOff
	waitmovement 0
	call PetalburgWoods_EventScript_DevonResearcherPostBattle
	applymovement LOCALID_PLAYER, PetalburgWoods_Movement_WatchResearcherLeave
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherExitRight
	waitmovement 0
	goto PetalburgWoods_EventScript_RemoveDevonResearcher
	end

PetalburgWoods_EventScript_DevonResearcherIntro::
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherLookAround
	waitmovement 0
	msgbox PetalburgWoods_Text_NotAOneToBeFound, MSGBOX_DEFAULT
	closemessage
	return

PetalburgWoods_EventScript_DevonResearcherPostBattle::
	msgbox PetalburgWoods_Text_YouveGotSomeNerve, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaRunAway
	waitmovement 0
	removeobject LOCALID_PETALBURG_WOODS_GRUNT
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox PetalburgWoods_Text_ThatWasAwfullyClose, MSGBOX_DEFAULT
	giveitem ITEM_GREAT_BALL
	goto_if_eq VAR_RESULT, FALSE, PetalburgWoods_EventScript_BagFull
	goto PetalburgWoods_EventScript_DevonResearcherFinish
	end

PetalburgWoods_EventScript_BagFull::
	msgbox PetalburgWoods_Text_YoureLoadedWithItems, MSGBOX_DEFAULT
	goto PetalburgWoods_EventScript_DevonResearcherFinish
	end

PetalburgWoods_EventScript_DevonResearcherFinish::
	msgbox PetalburgWoods_Text_TeamAquaAfterSomethingInRustboro, MSGBOX_DEFAULT
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherStartExit
	waitmovement 0
	msgbox PetalburgWoods_Text_ICantBeWastingTime, MSGBOX_DEFAULT
	closemessage
	return

PetalburgWoods_EventScript_RemoveDevonResearcher::
	removeobject LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE
	setvar VAR_PETALBURG_WOODS_STATE, 1
	releaseall
	end

PetalburgWoods_Movement_DevonResearcherLookAround:
	face_up
	delay_16
	delay_4
	face_right
	delay_16
	delay_8
	face_left
	delay_16
	delay_8
	face_down
	delay_16
	face_right
	delay_16
	delay_8
	face_up
	delay_16
	step_end

PetalburgWoods_Movement_DevonResearcherExitLeft:
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

PetalburgWoods_Movement_DevonResearcherApproachPlayerLeft:
	delay_16
	face_player
	walk_down
	walk_down
	step_end

PetalburgWoods_Movement_DevonResearcherApproachPlayerRight:
	delay_16
	face_player
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

PetalburgWoods_Movement_DevonResearcherExitRight:
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

PetalburgWoods_Movement_WatchResearcherLeave:
	delay_16
	delay_16
	walk_in_place_faster_up
	step_end

PetalburgWoods_Movement_DevonResearcherFleeToPlayerLeft:
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_in_place_faster_up
	step_end

PetalburgWoods_Movement_DevonResearcherFleeToPlayerRight:
	walk_fast_down
	walk_fast_right
	walk_in_place_faster_up
	step_end

PetalburgWoods_Movement_DevonResearcherStartExit:
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	face_up
	step_end

PetalburgWoods_Movement_AquaApproachResearcherLeft:
	walk_fast_down
	walk_fast_down
	step_end

PetalburgWoods_Movement_AquaBackOff:
	lock_facing_direction
	walk_up
	unlock_facing_direction
	step_end

PetalburgWoods_Movement_AquaRunAway:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	delay_16
	delay_16
	step_end

PetalburgWoods_Movement_AquaApproachResearcherRight:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

PetalburgWoods_Movement_AquaEntrance:
	walk_down
	walk_down
	delay_16
	delay_16
	step_end

PetalburgWoods_Movement_AquaApproachPlayer:
	walk_down
	step_end

PetalburgWoods_EventScript_Boy1::
	msgbox PetalburgWoods_Text_StayOutOfTallGrass, MSGBOX_NPC
	end

PetalburgWoods_EventScript_Boy2::
	msgbox PetalburgWoods_Text_HiddenItemsExplanation, MSGBOX_NPC
	end

PetalburgWoods_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_MIRACLE_SEED, PetalburgWoods_EventScript_ExplainMiracleSeed
	msgbox PetalburgWoods_Text_TryUsingThisItem, MSGBOX_DEFAULT
	giveitem ITEM_MIRACLE_SEED
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MIRACLE_SEED
	release
	end

PetalburgWoods_EventScript_ExplainMiracleSeed::
	msgbox PetalburgWoods_Text_MiracleSeedExplanation, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_Sign1::
	msgbox PetalburgWoods_Text_TrainerTipsExperience, MSGBOX_SIGN
	end

PetalburgWoods_EventScript_Sign2::
	msgbox PetalburgWoods_Text_TrainerTipsPP, MSGBOX_SIGN
	end

PetalburgWoods_EventScript_Lyle::
	trainerbattle_single TRAINER_LYLE, PetalburgWoods_Text_GoBugPokemonTeam, PetalburgWoods_Text_ICouldntWin
	msgbox PetalburgWoods_Text_ImOutOfPokeBalls, MSGBOX_AUTOCLOSE
	end

PetalburgWoods_EventScript_James::
	trainerbattle_single TRAINER_JAMES_1, PetalburgWoods_Text_InstantlyPopularWithBugPokemon, PetalburgWoods_Text_CantBePopularIfILose, PetalburgWoods_EventScript_TryRegisterJames
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, PetalburgWoods_EventScript_JamesRematch
	setvar VAR_0x8004, TRAINER_JAMES_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, PetalburgWoods_EventScript_TryRegisterJames2
	msgbox PetalburgWoods_Text_PeopleRespectYou, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_TryRegisterJames::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, PetalburgWoods_EventScript_RegisterJames
	release
	end

PetalburgWoods_EventScript_RegisterJames::
	msgbox PetalburgWoods_Text_IWantRematch1, MSGBOX_DEFAULT
	register_matchcall TRAINER_JAMES_1
	release
	end

PetalburgWoods_EventScript_TryRegisterJames2::
	goto_if_set FLAG_HAS_MATCH_CALL, PetalburgWoods_EventScript_RegisterJames2
	msgbox PetalburgWoods_Text_PeopleRespectYou, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_RegisterJames2::
	msgbox PetalburgWoods_Text_IWantRematch2, MSGBOX_DEFAULT
	register_matchcall TRAINER_JAMES_1
	release
	end

PetalburgWoods_EventScript_JamesRematch::
	trainerbattle_rematch TRAINER_JAMES_1, PetalburgWoods_Text_MyPokemonHaveGrown, PetalburgWoods_Text_CantBePopularIfLose
	msgbox PetalburgWoods_Text_IveBeenTrainingHard, MSGBOX_AUTOCLOSE
	end

PetalburgWoods_Text_NotAOneToBeFound:
	.string "{CHN}嗯……\n"
	.string "一只都没找到……$"

PetalburgWoods_Text_HaveYouSeenShroomish:
	.string "{CHN}你好，你在这附近有没有看到\n"
	.string "叫蘑蘑菇的宝可梦？\p"
	.string "我真的很喜欢那只宝可梦。$"

PetalburgWoods_Text_IWasGoingToAmbushYou:
	.string "{CHN}我本来打算伏击你的，但你\n"
	.string "非要在橙华森林里\l"
	.string "磨蹭个没完，不是吗？\p"
	.string "我等得不耐烦了，所以就来了！$"

PetalburgWoods_Text_HandOverThosePapers:
	.string "{CHN}你！得文研究员！\p"
	.string "把那些文件交出来！$"

PetalburgWoods_Text_YouHaveToHelpMe:
	.string "{CHN}啊呀！\p"
	.string "你是宝可梦训练家，对吧？\n"
	.string "请你一定要帮帮我！$"

PetalburgWoods_Text_NoOneCrossesTeamAqua:
	.string "{CHN}嗯？你在干什么？\n"
	.string "什么，你要保护他？\p"
	.string "得罪水舰队的人\n"
	.string "别想得到任何怜悯，小孩子也不例外！\p"
	.string "来吧，和我对战！$"

PetalburgWoods_Text_YoureKiddingMe:
	.string "{CHN}开什么玩笑！你挺厉害的！$"

PetalburgWoods_Text_YouveGotSomeNerve:
	.string "{CHN}呃……你竟然敢\n"
	.string "插手水舰队的事！\l"
	.string "来吧，再和我对战一场！\p"
	.string "我倒想这么说，但我的\n"
	.string "宝可梦都用完了……\p"
	.string "对了，我们水舰队也在\n"
	.string "卡那兹市寻找某样东西。\p"
	.string "今天就放你走！$"

PetalburgWoods_Text_ThatWasAwfullyClose:
	.string "{CHN}呼……\n"
	.string "刚才真是太险了！\p"
	.string "多亏了你，他没有抢走\n"
	.string "这些重要的文件。\p"
	.string "这样吧，我送你一个高级球\n"
	.string "作为谢意！$"

PetalburgWoods_Text_TeamAquaAfterSomethingInRustboro:
	.string "{CHN}那个水舰队的家伙\n"
	.string "不是说他们也在\l"
	.string "卡那兹市寻找什么吗？$"

PetalburgWoods_Text_ICantBeWastingTime:
	.string "{CHN}糟了！出大事了！\n"
	.string "我可不能浪费时间！$"

PetalburgWoods_Text_YoureLoadedWithItems:
	.string "{CHN}你的道具已经满了。\n"
	.string "我没办法把这个高级球给你。$"

PetalburgWoods_Text_GoBugPokemonTeam:
	.string "{CHN}我抓了好多宝可梦！\p"
	.string "上吧，上吧，上吧！\n"
	.string "我的虫宝可梦队伍！$"

PetalburgWoods_Text_ICouldntWin:
	.string "{CHN}我有这么多宝可梦，\n"
	.string "却还是没能赢……$"

PetalburgWoods_Text_ImOutOfPokeBalls:
	.string "{CHN}我抓了一堆宝可梦。\n"
	.string "现在我的精灵球用完了。$"

PetalburgWoods_Text_InstantlyPopularWithBugPokemon:
	.string "{CHN}如果你把虫宝可梦带到学校，\n"
	.string "你会立刻变得很受欢迎！$"

PetalburgWoods_Text_CantBePopularIfILose:
	.string "{CHN}如果我输了就不受欢迎了。$"

PetalburgWoods_Text_PeopleRespectYou:
	.string "{CHN}如果你有一只大虫宝可梦，\n"
	.string "人们就会尊重你。$"

PetalburgWoods_Text_IWantRematch1:
	.string "{CHN}等我的虫宝可梦\n"
	.string "长大了我想要再战一场！\p"
	.string "我要把你登记到我的宝可领航员里！$"

PetalburgWoods_Text_IWantRematch2:
	.string "{CHN}等我的虫宝可梦\n"
	.string "长大了我想要再战一场！\p"
	.string "我要把你登记到我的宝可领航员里！$"

PetalburgWoods_Text_MyPokemonHaveGrown:
	.string "{CHN}我的虫宝可梦长大了。\n"
	.string "我又要受欢迎了。$"

PetalburgWoods_Text_CantBePopularIfLose:
	.string "{CHN}如果我输了就不受欢迎了。$"

PetalburgWoods_Text_IveBeenTrainingHard:
	.string "{CHN}有强大的宝可梦\n"
	.string "就会受欢迎，对吧？\l"
	.string "所以，我一直在努力训练。$"

PetalburgWoods_Text_StayOutOfTallGrass:
	.string "{CHN}喂，那边的！\n"
	.string "你的宝可梦还好吗？\p"
	.string "如果你的宝可梦很弱，又想\n"
	.string "避免对战，那就别\l"
	.string "走进草丛里。$"

PetalburgWoods_Text_HiddenItemsExplanation:
	.string "{CHN}有时候，地上会有东西，\n"
	.string "即使你看不见。\p"
	.string "所以我走路的时候\n"
	.string "总是会仔细查看。$"

PetalburgWoods_Text_TryUsingThisItem:
	.string "{CHN}哦，不错！\n"
	.string "那是卡那兹道馆的徽章！\p"
	.string "你一定是训练家。\n"
	.string "你应该试试用这个道具。$"

PetalburgWoods_Text_MiracleSeedExplanation:
	.string "{CHN}这是奇迹种子。\n"
	.string "如果宝可梦带着它，\l"
	.string "草属性招式的威力会变强。\p"
	.string "除了奇迹种子，\n"
	.string "我觉得应该还有其他\l"
	.string "方便宝可梦携带的道具。$"

PetalburgWoods_Text_TrainerTipsExperience:
	.string "{CHN}训练家小贴士\p"
	.string "任何宝可梦只要\n"
	.string "在对战中出现过一次，就能获得经验值。\p"
	.string "要培养弱小的宝可梦，把它放在\n"
	.string "队伍名单的左侧。\p"
	.string "对战一开始就换下它。\n"
	.string "这样它就能在不\l"
	.string "受到任何伤害的情况下获得经验值。$"

PetalburgWoods_Text_TrainerTipsPP:
	.string "{CHN}训练家小贴士\p"
	.string "除了体力值（HP）外，宝可梦\n"
	.string "还有技能点数（PP），\l"
	.string "对战中用来使出招式。\p"
	.string "如果宝可梦的PP用完了，\n"
	.string "就必须送去宝可梦中心。$"

