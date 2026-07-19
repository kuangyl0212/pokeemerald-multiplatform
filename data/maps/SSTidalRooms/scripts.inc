SSTidalRooms_MapScripts::
	.byte 0

SSTidalRooms_EventScript_SnatchGiver::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_SNATCH, SSTidalRooms_EventScript_ExplainSnatch
	msgbox SSTidalRooms_Text_NotSuspiciousTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_SNATCH
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_SNATCH
	msgbox SSTidalRooms_Text_ExplainSnatch, MSGBOX_DEFAULT
	release
	end

SSTidalRooms_EventScript_ExplainSnatch::
	msgbox SSTidalRooms_Text_ExplainSnatch, MSGBOX_DEFAULT
	release
	end

SSTidalRooms_EventScript_Bed::
	lockall
	msgbox SSTidalRooms_Text_TakeRestOnBed, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	call SSTidalRooms_EventScript_ProgessCruiseAfterBed
	releaseall
	end

SSTidalRooms_EventScript_Colton::
	trainerbattle_single TRAINER_COLTON, SSTidalRooms_Text_ColtonIntro, SSTidalRooms_Text_ColtonDefeat
	msgbox SSTidalRooms_Text_ColtonPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Micah::
	trainerbattle_single TRAINER_MICAH, SSTidalRooms_Text_MicahIntro, SSTidalRooms_Text_MicahDefeat
	msgbox SSTidalRooms_Text_MicahPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Thomas::
	trainerbattle_single TRAINER_THOMAS, SSTidalRooms_Text_ThomasIntro, SSTidalRooms_Text_ThomasDefeat
	msgbox SSTidalRooms_Text_ThomasPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Jed::
	trainerbattle_double TRAINER_LEA_AND_JED, SSTidalRooms_Text_JedIntro, SSTidalRooms_Text_JedDefeat, SSTidalRooms_Text_JedNotEnoughMons
	msgbox SSTidalRooms_Text_JedPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Lea::
	trainerbattle_double TRAINER_LEA_AND_JED, SSTidalRooms_Text_LeaIntro, SSTidalRooms_Text_LeaDefeat, SSTidalRooms_Text_LeaNotEnoughMons
	msgbox SSTidalRooms_Text_LeaPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Garret::
	trainerbattle_single TRAINER_GARRET, SSTidalRooms_Text_GarretIntro, SSTidalRooms_Text_GarretDefeat
	msgbox SSTidalRooms_Text_GarretPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Naomi::
	trainerbattle_single TRAINER_NAOMI, SSTidalRooms_Text_NaomiIntro, SSTidalRooms_Text_NaomiDefeat
	msgbox SSTidalRooms_Text_NaomiPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_Text_TakeRestOnBed:
	.string "{CHN}有一张床……\n"
	.string "休息一下吧。$"

SSTidalRooms_Text_ColtonIntro:
	.string "{CHN}我经常坐船去水静市。\p"
	.string "我喜欢参加选拔赛，\n"
	.string "你知道的。$"

SSTidalRooms_Text_ColtonDefeat:
	.string "{CHN}真是一场愉快的比赛！$"

SSTidalRooms_Text_ColtonPostBattle:
	.string "{CHN}想象下一场选拔赛\n"
	.string "会看到什么样的宝可梦，\l"
	.string "我就兴奋不已。这种期待感真刺激！$"

SSTidalRooms_Text_MicahIntro:
	.string "{CHN}你的伙伴强吗？$"

SSTidalRooms_Text_MicahDefeat:
	.string "{CHN}你的伙伴确实很强。$"

SSTidalRooms_Text_MicahPostBattle:
	.string "{CHN}朋友不一定要是人类。\n"
	.string "对我来说，宝可梦就是珍视的朋友！$"

SSTidalRooms_Text_ThomasIntro:
	.string "{CHN}孩子……\n"
	.string "你敲门了吗？$"

SSTidalRooms_Text_ThomasDefeat:
	.string "{CHN}失败应当从容接受，\n"
	.string "不要惊慌。$"

SSTidalRooms_Text_ThomasPostBattle:
	.string "{CHN}在任何情况下都不动声色，\n"
	.string "这是绅士的行为准则。$"

SSTidalRooms_Text_JedIntro:
	.string "{CHN}杰德：我有点不好意思，但是……\n"
	.string "我们要让你见识我们的恩爱力量！$"

SSTidalRooms_Text_JedDefeat:
	.string "{CHN}杰德：唉……$"

SSTidalRooms_Text_JedPostBattle:
	.string "{CHN}杰德：这是我们的恩爱力量\n"
	.string "第一次没能取胜！\l"
	.string "你一定是个超强的训练家！$"

SSTidalRooms_Text_JedNotEnoughMons:
	.string "{CHN}杰德：你只有一只宝可梦？\n"
	.string "那不是太孤单了吗？$"

SSTidalRooms_Text_LeaIntro:
	.string "{CHN}莉亚：我觉得有点傻，但是……\n"
	.string "我们要让你见识我们的恩爱力量！$"

SSTidalRooms_Text_LeaDefeat:
	.string "{CHN}莉亚：哎呀，讨厌！$"

SSTidalRooms_Text_LeaPostBattle:
	.string "{CHN}莉亚：真不敢相信！\n"
	.string "我们的恩爱力量竟然失败了……\l"
	.string "你一定是个超强的训练家！$"

SSTidalRooms_Text_LeaNotEnoughMons:
	.string "{CHN}莉亚：我想对战……\n"
	.string "但你连两只宝可梦都没有……$"

SSTidalRooms_Text_GarretIntro:
	.string "{CHN}啊，你来得正是时候。\p"
	.string "我正无聊呢。\n"
	.string "你可以陪我消遣一下。$"

SSTidalRooms_Text_GarretDefeat:
	.string "{CHN}……还行吧。$"

SSTidalRooms_Text_GarretPostBattle:
	.string "{CHN}也许我该让父亲给我买\n"
	.string "一艘游艇。\l"
	.string "一艘属于我和宝可梦的游艇！$"

SSTidalRooms_Text_NaomiIntro:
	.string "{CHN}哦，你真是个可爱的训练家。\n"
	.string "想喝杯茶吗？\l"
	.string "还是更想对战？$"

SSTidalRooms_Text_NaomiDefeat:
	.string "{CHN}我明白了。\n"
	.string "你是好动型的。$"

SSTidalRooms_Text_NaomiPostBattle:
	.string "{CHN}乘坐豪华邮轮环游世界\n"
	.string "确实有它的魅力……\p"
	.string "不过，我也得承认，坐渡轮游览丰缘\n"
	.string "也有其吸引人的一面。$"

SSTidalRooms_Text_NotSuspiciousTakeThis:
	.string "{CHN}呃……嗨！我……我没有可疑举动！\n"
	.string "呃……这个给你！免费的！\p"
	.string "它……说实话，我没有从别人那里\n"
	.string "抢来这个！我才不会做这种事！\l"
	.string "它是干净的！你可以用！$"

SSTidalRooms_Text_ExplainSnatch:
	.string "{CHN}抢夺能在敌人或同伴\n"
	.string "使用某些招式之前，\l"
	.string "夺取其有益效果。$"
