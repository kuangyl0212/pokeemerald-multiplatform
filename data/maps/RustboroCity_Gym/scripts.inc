RustboroCity_Gym_MapScripts::
	.byte 0

RustboroCity_Gym_EventScript_Roxanne::
	trainerbattle_single TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxanneIntro, RustboroCity_Gym_Text_RoxanneDefeat, RustboroCity_Gym_EventScript_RoxanneDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Gym_EventScript_RoxanneRematch
	goto_if_unset FLAG_RECEIVED_TM_ROCK_TOMB, RustboroCity_Gym_EventScript_GiveRockTomb
	msgbox RustboroCity_Gym_Text_RoxannePostBattle, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_RoxanneDefeated::
	message RustboroCity_Gym_Text_ReceivedStoneBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox RustboroCity_Gym_Text_StoneBadgeInfoTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_RUSTBORO_GYM
	setflag FLAG_BADGE01_GET
	setvar VAR_RUSTBORO_CITY_STATE, 1
	addvar VAR_PETALBURG_GYM_STATE, 1
	setvar VAR_0x8008, 1
	call Common_EventScript_SetGymTrainers
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	goto RustboroCity_Gym_EventScript_GiveRockTomb
	end

RustboroCity_Gym_EventScript_GiveRockTomb::
	giveitem ITEM_TM_ROCK_TOMB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_ROCK_TOMB
	msgbox RustboroCity_Gym_Text_ExplainRockTomb, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_RoxanneRematch::
	trainerbattle_rematch_double TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxannePreRematch, RustboroCity_Gym_Text_RoxanneRematchDefeat, RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons
	msgbox RustboroCity_Gym_Text_RoxannePostRematch, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Josh::
	trainerbattle_single TRAINER_JOSH, RustboroCity_Gym_Text_JoshIntro, RustboroCity_Gym_Text_JoshDefeat
	msgbox RustboroCity_Gym_Text_JoshPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Tommy::
	trainerbattle_single TRAINER_TOMMY, RustboroCity_Gym_Text_TommyIntro, RustboroCity_Gym_Text_TommyDefeat
	msgbox RustboroCity_Gym_Text_TommyPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Marc::
	trainerbattle_single TRAINER_MARC, RustboroCity_Gym_Text_MarcIntro, RustboroCity_Gym_Text_MarcDefeat
	msgbox RustboroCity_Gym_Text_MarcPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_RUSTBORO_GYM, RustboroCity_Gym_EventScript_GymGuidePostVictory
	msgbox RustboroCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_GymGuidePostVictory::
	msgbox RustboroCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
	goto RustboroCity_Gym_EventScript_GymStatue
	end

RustboroCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
	goto RustboroCity_Gym_EventScript_GymStatue
	end

RustboroCity_Gym_EventScript_GymStatueCertified::
	msgbox RustboroCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_Gym_EventScript_GymStatue::
	msgbox RustboroCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_Gym_EventScript_RegisterRoxanne::
	lockall
	pokenavcall RustboroCity_Gym_Text_RoxanneRegisterCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox RustboroCity_Gym_Text_RegisteredRoxanne, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_ROXANNE_MATCH_CALL
	clearflag FLAG_ENABLE_ROXANNE_FIRST_CALL
	releaseall
	end

RustboroCity_Gym_Text_GymGuideAdvice:
	.string "{CHN}哟，最近怎么样？\p"
	.string "听着，朋友！\n"
	.string "你想成为冠军吗？\p"
	.string "我不是训练家，不是我，但我\n"
	.string "绝对能给你获胜的建议.\p"
	.string "那就这么说定了！我们一起朝\n"
	.string "宝可梦冠军的目标前进！\p"
	.string "作为训练家，收集道馆\n"
	.string "徽章就是你的工作，对吧？\p"
	.string "但道馆馆主可不是好惹的！\p"
	.string "这就是我发挥作用的地方！\n"
	.string "我在这里提供专家建议！\p"
	.string "杜娟，道馆馆主，是岩石属性\n"
	.string "宝可梦的使用者.\p"
	.string "岩石属性非常坚固，但\n"
	.string "它承受不住水属性和\l"
	.string "草属性的招式.\p"
	.string "如果你打败了道馆馆主，\n"
	.string "之后再来见我.\p"
	.string "好了，去吧！$"

RustboroCity_Gym_Text_GymGuidePostVictory:
	.string "{CHN}哇！真是惊心动魄的胜利！\n"
	.string "我的加油一定起作用了！\p"
	.string "太棒了！\n"
	.string "检查一下你的训练家卡片.\p"
	.string "你得到的岩石徽章应该\n"
	.string "已经正确记录在上面了.\p"
	.string "也就是说…\p"
	.string "你已经迈上了通往\n"
	.string "冠军之路的第一级台阶！\p"
	.string "那感觉一定很棒！$"

RustboroCity_Gym_Text_JoshIntro:
	.string "{CHN}别小看我们道馆训练家！\n"
	.string "我会让你明白我们更强的原因！$"

RustboroCity_Gym_Text_JoshDefeat:
	.string "{CHN}你实在太强了…$"

RustboroCity_Gym_Text_JoshPostBattle:
	.string "{CHN}你还没见识到岩石属性\n"
	.string "恐怖的力量呢！$"

RustboroCity_Gym_Text_TommyIntro:
	.string "{CHN}如果你连我都打不过，就别想\n"
	.string "战胜杜娟了！$"

RustboroCity_Gym_Text_TommyDefeat:
	.string "{CHN}哇！你还挺有潜力的！$"

RustboroCity_Gym_Text_TommyPostBattle:
	.string "{CHN}杜娟比我强\n"
	.string "好几倍.\p"
	.string "你最好小心提防！$"

RustboroCity_Gym_Text_MarcIntro:
	.string "{CHN}虽然我们在市中心，\n"
	.string "但那又怎样？\p"
	.string "我的岩石宝可梦需要\n"
	.string "足够的空间发威！$"

RustboroCity_Gym_Text_MarcDefeat:
	.string "{CHN}哎呀，天哪！\n"
	.string "我们的挑战者真是个厉害角色！$"

RustboroCity_Gym_Text_MarcPostBattle:
	.string "{CHN}我不得不佩服我们的馆主.\p"
	.string "她年纪轻轻就选择了岩石属性，\n"
	.string "真是聪明又有眼光.$"

RustboroCity_Gym_Text_RoxanneIntro:
	.string "{CHN}你好，我是杜娟，卡那兹市\n"
	.string "宝可梦道馆的馆主.\p"
	.string "我成为道馆馆主是为了\n"
	.string "将我在宝可梦\l"
	.string "训练家学校学到的知识用于对战.\p"
	.string "能否请你展示一下\n"
	.string "你是如何对战的，用哪些宝可梦?$"

RustboroCity_Gym_Text_RoxanneDefeat:
	.string "{CHN}所以…\n"
	.string "我输了…\p"
	.string "看来我还有很多\n"
	.string "需要学习的地方…\p"
	.string "我明白了.\p"
	.string "宝可梦联盟的规则规定，\n"
	.string "训练家击败道馆馆主后\l"
	.string "可以获得这个.\p"
	.string "请收下这枚正式的\n"
	.string "宝可梦联盟岩石徽章.$"

RustboroCity_Gym_Text_ReceivedStoneBadge:
	.string "{CHN}{PLAYER}从杜娟那里\n"
	.string "得到了岩石徽章.$"

RustboroCity_Gym_Text_StoneBadgeInfoTakeThis:
	.string "{CHN}岩石徽章能提升\n"
	.string "宝可梦的攻击力.\p"
	.string "它还能让宝可梦在对战之外\n"
	.string "使用秘传学习器居合劈.\p"
	.string "这个也请收下.$"

RustboroCity_Gym_Text_ExplainRockTomb:
	.string "{CHN}那台招式学习器，TM39，\n"
	.string "装的是岩石封.\p"
	.string "它不仅通过落下岩石造成伤害，\n"
	.string "还能降低速度.\p"
	.string "如果使用招式学习器，就能立即\n"
	.string "教会宝可梦招式.\p"
	.string "请记住，招式学习器只能使用一次，\n"
	.string "使用前要三思.$"

RustboroCity_Gym_Text_RoxannePostBattle:
	.string "{CHN}既然你这么强，应该去\n"
	.string "挑战其他道馆馆主.\p"
	.string "通过与许多训练家对战，\n"
	.string "你会学到很多东西.$"

RustboroCity_Gym_Text_GymStatue:
	.string "{CHN}卡那兹市宝可梦道馆$"

RustboroCity_Gym_Text_GymStatueCertified:
	.string "{CHN}卡那兹市宝可梦道馆\p"
	.string "杜娟认证训练家：\n"
	.string "{PLAYER}$"

RustboroCity_Gym_Text_RoxanneRegisterCall:
	.string "{CHN}… … … … … …\n"
	.string "… … … … … 嘟！\p"
	.string "杜娟：哦，你好，{PLAYER}？\n"
	.string "我是卡那兹市的杜娟.\p"
	.string "我听藤树说你以惊人的速度\n"
	.string "在训练家排名中\l"
	.string "不断上升.\p"
	.string "嗯，我可不想认为自己\n"
	.string "打不过你.\p"
	.string "我保证，我会整顿好我的道馆，\n"
	.string "让你可以再次挑战我们.\p"
	.string "希望你也和我一样\n"
	.string "期待那一天！\p"
	.string "… … … … … …\n"
	.string "… … … … … 咔嗒！$"

RustboroCity_Gym_Text_RegisteredRoxanne:
	.string "{CHN}在宝可梦导航器中登录了\n"
	.string "道馆馆主杜娟.$"

RustboroCity_Gym_Text_RoxannePreRematch:
	.string "{CHN}杜娟：很高兴再次见到你.\n"
	.string "我是杜娟，这里的道馆馆主.\p"
	.string "我相信自上次见面以来，\n"
	.string "我们都经历了许多对战.\p"
	.string "我想看看我们进步了多少.\n"
	.string "让我们对战吧！$"

RustboroCity_Gym_Text_RoxanneRematchDefeat:
	.string "{CHN}呜…\n"
	.string "我又输了…$"

RustboroCity_Gym_Text_RoxannePostRematch:
	.string "{CHN}杜娟：在宝可梦对战方面\n"
	.string "我还有很多要学的.\p"
	.string "这种认识让我更加\n"
	.string "热爱对战了！$"

RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons:
	.string "{CHN}杜娟：很高兴再次见到你.\n"
	.string "我是杜娟，这里的道馆馆主.\p"
	.string "我相信自上次见面以来，\n"
	.string "我们都经历了许多对战.\p"
	.string "我想看看我们进步了多少…\p"
	.string "哦，不…\n"
	.string "你身边只有一只宝可梦吗？\p"
	.string "请至少带多一只\n"
	.string "宝可梦再来.$"
