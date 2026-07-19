FallarborTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FallarborTown_OnTransition
	.byte 0

FallarborTown_OnTransition:
	setflag FLAG_VISITED_FALLARBOR_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	clearflag FLAG_CONTEST_SKETCH_CREATED
	end

FallarborTown_EventScript_ExpertM::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FallarborTown_EventScript_ExpertMNormal
	msgbox FallarborTown_Text_ShadyCharactersCozmosHome, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_ExpertMNormal::
	msgbox FallarborTown_Text_RegionKnownForMeteors, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_Girl::
	msgbox FallarborTown_Text_MyPreciousAzurill, MSGBOX_NPC
	end

FallarborTown_EventScript_Gentleman::
	msgbox FallarborTown_Text_HaveYouChallengedFlannery, MSGBOX_NPC
	end

FallarborTown_EventScript_Azurill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, CRY_MODE_NORMAL
	msgbox FallarborTown_Text_Azurill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FallarborTown_EventScript_BattleTentSign::
	msgbox FallarborTown_Text_BattleTentSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_TownSign::
	msgbox FallarborTown_Text_TownSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_MoveTutorSign::
	msgbox FallarborTown_Text_MoveTutorSign, MSGBOX_SIGN
	end

FallarborTown_Text_ShadyCharactersCozmosHome:
	.string "{CHN}有些事情正在发生，\n"
	.string "我不喜欢这样！\p"
	.string "我看到可疑的人物\n"
	.string "在小岭博士家进进出出……$"

FallarborTown_Text_RegionKnownForMeteors:
	.string "{CHN}这个地区自古以来\n"
	.string "就以陨石闻名。\p"
	.string "据说流星瀑布是很久以前\n"
	.string "由陨石坠落砸出来的。$"

FallarborTown_Text_MyPreciousAzurill:
	.string "{CHN}看！瞧瞧！\n"
	.string "这是我珍贵的露力丽！\p"
	.string "它又滑又顺又柔软！$"

FallarborTown_Text_Azurill:
	.string "{CHN}露力丽：噜噜哩哩。$"

FallarborTown_Text_HaveYouChallengedFlannery:
	.string "{CHN}你已经挑战过烟突道馆的馆主\n"
	.string "亚莎了吗？\p"
	.string "那女孩的祖父很有名。\n"
	.string "他曾经是宝可梦联盟\l"
	.string "四天王的一员。\p"
	.string "我相信亚莎\n"
	.string "凭借自己的实力\l"
	.string "也会成为出色的训练家。$"

FallarborTown_Text_BattleTentSign:
	.string "{CHN}对战帐篷 秋叶镇场地\n"
	.string "“愿最伟大的队伍齐聚！”$"

FallarborTown_Text_TownSign:
	.string "{CHN}秋叶镇\n"
	.string "“有着小花园的农业小镇。”$"

FallarborTown_Text_MoveTutorSign:
	.string "{CHN}招式教学家的家\n"
	.string "“教会宝可梦新招式。”$"
