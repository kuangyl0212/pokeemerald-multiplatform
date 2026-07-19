BattleFrontier_OutsideEast_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_OutsideEast_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideEast_OnTransition
	.byte 0

BattleFrontier_OutsideEast_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo
	end

BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

BattleFrontier_OutsideEast_OnTransition:
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	call_if_unset FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_ShowSudowoodo
	end

BattleFrontier_OutsideEast_EventScript_ShowSudowoodo::
	clearflag FLAG_HIDE_BATTLE_FRONTIER_SUDOWOODO
	return

BattleFrontier_OutsideEast_EventScript_BattleTowerSign::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePalaceSign::
	msgbox BattleFrontier_OutsideEast_Text_BattlePalaceSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattleArenaSign::
	msgbox BattleFrontier_OutsideEast_Text_BattleArenaSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePyramidSign::
	msgbox BattleFrontier_OutsideEast_Text_BattlePyramidSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_NinjaBoy::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man1::
	msgbox BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Hiker::
	msgbox BattleFrontier_OutsideEast_Text_PyramidTooHarsh, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_HexManiac::
	msgbox BattleFrontier_OutsideEast_Text_ThriveInDarkness, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt1::
	msgbox BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Cook::
	lock
	msgbox BattleFrontier_OutsideEast_Text_BelieveInYouBuddy, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_OutsideEast_EventScript_RichBoy::
	msgbox BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_ExpertF::
	msgbox BattleFrontier_OutsideEast_Text_OnceBeatGymLeader, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_TriathleteF::
	msgbox BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Twin::
	msgbox BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man2::
	lock
	msgbox BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_TriathleteM::
	msgbox BattleFrontier_OutsideEast_Text_DidScottBringYouHere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Sudowoodo::
	lock
	faceplayer
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_FRONTIER_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake
	waitmovement 0
	release
	end

BattleFrontier_OutsideEast_EventScript_WaterSudowoodo::
	lock
	faceplayer
	special DoWateringBerryTreeAnim
	waitstate
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_FRONTIER_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake
	waitmovement 0
	msgbox gText_Sudowoodo_Attacked, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_SUDOWOODO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_FRONTIER_SUDOWOODO
	setwildbattle SPECIES_SUDOWOODO, 40
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	setflag FLAG_DEFEATED_SUDOWOODO
	release
	end

BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo::
	setflag FLAG_DEFEATED_SUDOWOODO
	goto Common_EventScript_RemoveStaticPokemon
	end

BattleFrontier_OutsideEast_Movement_SudowoodoShake:
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	step_end

BattleFrontier_OutsideEast_EventScript_Maniac1::
	msgbox BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Girl::
	msgbox BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_PsychicM::
	msgbox BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man3::
	msgbox BattleFrontier_OutsideEast_Text_GotWipedOut, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman1::
	msgbox BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman2::
	msgbox BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt2::
	msgbox BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Maniac2::
	lock
	msgbox BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Woman3::
	lock
	msgbox BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_RankingHallSign::
	msgbox BattleFrontier_OutsideEast_Text_RankingHallSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_ExchangeCornerSign::
	msgbox BattleFrontier_OutsideEast_Text_ExchangeCornerSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_Gentleman::
	msgbox BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_OldWoman::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_OldWomanSudowoodoGone
	msgbox BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_OldWomanSudowoodoGone::
	msgbox BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Camper::
	msgbox BattleFrontier_OutsideEast_Text_StickyMonWithLongTail, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Text_BattleTowerSign:
	.string "{CHN}这里是对战塔！\n"
	.string "作为最强的训练家\l"
	.string "保持连胜吧！$"

BattleFrontier_OutsideEast_Text_BattlePalaceSign:
	.string "{CHN}这里是对战宫殿！\n"
	.string "专注于宝可梦对战吧！$"

BattleFrontier_OutsideEast_Text_BattleArenaSign:
	.string "{CHN}这里是对战竞技场！\n"
	.string "让最强的队伍聚集吧！$"

BattleFrontier_OutsideEast_Text_BattlePyramidSign:
	.string "{CHN}这里是对战金字塔！\n"
	.string "在对战探险中前进吧！$"

BattleFrontier_OutsideEast_Text_RankingHallSign:
	.string "{CHN}对战开拓区名人堂\n"
	.string "瞄准新记录吧！$"

BattleFrontier_OutsideEast_Text_ExchangeCornerSign:
	.string "{CHN}对战点数兑换服务柜台\n"
	.string "兑换你的对战点数吧！$"

BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial:
	.string "{CHN}哇！\n"
	.string "好大啊！\p"
	.string "对战塔感觉很特别。\n"
	.string "和其他的不一样。$"

BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier:
	.string "{CHN}我的宏伟目标是征服\n"
	.string "对战开拓区和宝可梦\l"
	.string "联盟。\p"
	.string "如果我的梦想成真……\p"
	.string "我……我要去请隔壁的咪咪\n"
	.string "做我的朋友！$"

BattleFrontier_OutsideEast_Text_PyramidTooHarsh:
	.string "{CHN}对战金字塔太残酷了！\n"
	.string "我就是到不了顶端！\p"
	.string "既然没别的办法了，也许我可以\n"
	.string "从外面爬上去……$"

BattleFrontier_OutsideEast_Text_ThriveInDarkness:
	.string "{CHN}我在黑暗中茁壮成长……\n"
	.string "是的……什么才配得上我？\l"
	.string "非对战金字塔莫属……\p"
	.string "你觉得在黑暗中\n"
	.string "和彻底的绝望中徘徊如何？$"

BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam:
	.string "{CHN}我一周没睡觉，但终于\n"
	.string "组建了终极队伍！\p"
	.string "我看不到自己会输，不开玩笑。\n"
	.string "我们要横扫对战竞技场！$"

BattleFrontier_OutsideEast_Text_DidScottBringYouHere:
	.string "{CHN}亚希达也把你带到这里来了吗？\n"
	.string "那个人是怎么回事？\p"
	.string "听起来他确实知道\n"
	.string "如何发掘有才能的训练家，但是……\p"
	.string "我从没见过他\n"
	.string "亲自对战过。$"

BattleFrontier_OutsideEast_Text_BelieveInYouBuddy:
	.string "{CHN}之之！\n"
	.string "我相信你，小家伙！\p"
	.string "如果你赢了，我就给你做\n"
	.string "你最喜欢的美味点心！$"

BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant:
	.string "{CHN}蛇纹熊看起来发呆的样子……$"

BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody:
	.string "{CHN}人们说我爱多管闲事，\n"
	.string "但我就是忍不住。\p"
	.string "你的帽子歪了！\n"
	.string "哦不，地上有垃圾！\l"
	.string "哎呀，快到晚饭时间了！\p"
	.string "我不知道在对战宫殿\n"
	.string "只看着能不能受得了……$"

BattleFrontier_OutsideEast_Text_OnceBeatGymLeader:
	.string "{CHN}我现在看起来可能不怎么样，\n"
	.string "但我曾经打败过一位道馆馆主。\p"
	.string "谁知道呢，也许我该再\n"
	.string "争取一次荣耀。$"

BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles:
	.string "{CHN}我骑自行车很快，\n"
	.string "对战也是一样。\p"
	.string "我眨眼间就能\n"
	.string "赢得比赛！$"

BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon:
	.string "{CHN}我比爸爸\n"
	.string "更擅长宝可梦。$"

BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy:
	.string "{CHN}去吧，我的心肝宝贝！\n"
	.string "为爸爸赢几场吧！\p"
	.string "你就像你妈妈一样，\n"
	.string "所以你一定会称霸的！$"

BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena:
	.string "{CHN}来到这里不容易，\n"
	.string "但我听说对战竞技场\l"
	.string "有个漂亮的女孩。\p"
	.string "结果不是她，你知道\n"
	.string "我发现了什么吗？\p"
	.string "一大群满身臭汗、\n"
	.string "原始的武术家！$"

BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere:
	.string "{CHN}我有时会看到一个看起来很了不起的\n"
	.string "老人走进那里。\p"
	.string "他有那些非常厉害的宝可梦。\n"
	.string "不过他看起来人很好。$"

BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid:
	.string "{CHN}你知道吗？\n"
	.string "对战金字塔的传说？\p"
	.string "当有一个自信的训练家\n"
	.string "向金色巅峰迈进时，\l"
	.string "就会出现一位人中豪杰。\p"
	.string "不知道那个传说？\n"
	.string "当然不知道！\l"
	.string "我刚编的！\p"
	.string "它是什么意思？\n"
	.string "这个嘛，朋友，我说不上来！$"

BattleFrontier_OutsideEast_Text_GotWipedOut:
	.string "{CHN}天哪！我的天哪！\n"
	.string "我以前从未输过！\p"
	.string "但我被彻底打败了，\n"
	.string "毫无还手之力！\p"
	.string "然后还被告知我没有\n"
	.string "天赋？！天哪！$"

BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower:
	.string "{CHN}这个人在挑战对战塔时\n"
	.string "遇到了一个极其强大的\l"
	.string "训练家。\p"
	.string "现在看看他这样子……\p"
	.string "如果你决定去对战塔，\n"
	.string "一定要小心谨慎。$"

BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll:
	.string "{CHN}太好了！\n"
	.string "我终于攒够对战点数了！\p"
	.string "我想再换一个\n"
	.string "大毛绒玩偶！$"

BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere:
	.string "{CHN}哦，对，好的！\n"
	.string "所以这就是名人堂！\p"
	.string "我想作为超级冠军名留青史，\n"
	.string "让我的名字\l"
	.string "永远记录在这里。$"

BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou:
	.string "{CHN}有你在我身边，我什么都能做到。$"

BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome:
	.string "{CHN}哦，亲爱的，你太棒了！\p"
	.string "哦，我再也等不及了！\p"
	.string "我们现在就去\n"
	.string "多人对战房吧！\p"
	.string "如果我们在对战沙龙一起组队，\n"
	.string "我们爱的力量将战胜\l"
	.string "我们遇到的每一个人。\p"
	.string "亲爱的，在我们面前，\n"
	.string "一切都会像多米诺骨牌一样倒下！$"

BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers:
	.string "{CHN}对战开拓区并不只是\n"
	.string "为强大的训练家而设。\p"
	.string "似乎许多有特殊能力的人\n"
	.string "也被邀请来了。\p"
	.string "那个叫亚希达的人……\p"
	.string "他建造这个地方可能是为了\n"
	.string "更大的目标……$"

BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle:
	.string "{CHN}打扰一下，年轻人。\n"
	.string "你视力好吗？\p"
	.string "前面有棵奇怪的树，\n"
	.string "在我疲惫的眼中它似乎在扭动。$"

BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere:
	.string "{CHN}打扰一下，年轻人。\n"
	.string "你记性好吗？\p"
	.string "我总觉得以前\n"
	.string "前面有棵奇怪的树。$"

BattleFrontier_OutsideEast_Text_StickyMonWithLongTail:
	.string "{CHN}我……\n"
	.string "我看到了！\p"
	.string "前面有一只黏糊糊的宝可梦，\n"
	.string "长着长尾巴！\p"
	.string "它藏在巨石下面，\n"
	.string "一直盯着我看！$"
