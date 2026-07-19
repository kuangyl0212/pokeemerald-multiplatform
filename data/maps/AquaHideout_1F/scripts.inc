AquaHideout_1F_MapScripts::
	.byte 0

/* The below two entrance guards give hints about what to do to progress the story*/
AquaHideout_1F_EventScript_HideoutEntranceGrunt1::
	lock
	faceplayer
	goto_if_set FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT, AquaHideout_1F_EventScript_SlateportHint1
	goto_if_set FLAG_RECEIVED_RED_OR_BLUE_ORB, AquaHideout_1F_EventScript_MagmaHideoutHint1
	msgbox AquaHideout_1F_Text_OurBossIsSnatchingSomething, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_MagmaHideoutHint1::
	msgbox AquaHideout_1F_Text_WhereMightMagmaHideoutBe, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_SlateportHint1::
	msgbox AquaHideout_1F_Text_BossWentToJackASubmarine, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_HideoutEntranceGrunt2::
	lock
	faceplayer
	goto_if_set FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT, AquaHideout_1F_EventScript_SlateportHint2
	goto_if_set FLAG_RECEIVED_RED_OR_BLUE_ORB, AquaHideout_1F_EventScript_MagmaHideoutHint2
	msgbox AquaHideout_1F_Text_BossIsOnRoute122, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_MagmaHideoutHint2::
	msgbox AquaHideout_1F_Text_TeamMagmaAtMtChimney, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_SlateportHint2::
	msgbox AquaHideout_1F_Text_BossIsInSlateportCity, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_1, AquaHideout_1F_Text_Grunt1Intro, AquaHideout_1F_Text_Grunt1Defeat, AquaHideout_1F_EventScript_Grunt1Defeated
	msgbox AquaHideout_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_1F_EventScript_Grunt1Defeated::
	msgbox AquaHideout_1F_Text_Grunt1PostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_Text_OurBossIsSnatchingSomething:
	.string "{CHN}什么？什么？你找水舰队 \n"
	.string "有什么事？\p"
	.string "我们老大不在这里！他出去\n"
	.string "抢夺重要的东西了！\p"
	.string "… …\n"
	.string "他去哪里了？\p"
	.string "哇哈哈！你以为我真的会告诉\n"
	.string "你那么重要的事吗？$"

AquaHideout_1F_Text_WhereMightMagmaHideoutBe:
	.string "{CHN}什么？什么？\n"
	.string "你是火焰队的队员吗？\p"
	.string "我听说火焰队想在他们的\n"
	.string "基地里唤醒一只厉害的\l"
	.string "宝可梦。\p"
	.string "但是他们的基地在哪里呢？$"

AquaHideout_1F_Text_BossWentToJackASubmarine:
	.string "{CHN}什么？什么？你找水舰队 \n"
	.string "有什么事？\p"
	.string "我们老大不在这里！\n"
	.string "他去抢潜水艇了！\p"
	.string "… …\n"
	.string "他去哪里了？\p"
	.string "哇哈哈！你以为我真的会告诉\n"
	.string "你那么重要的事吗？$"

AquaHideout_1F_Text_BossIsOnRoute122:
	.string "{CHN}什么？什么？你找水舰队 \n"
	.string "有什么事？\p"
	.string "我们老大不在这里！他正前往\n"
	.string "122号道路的送火山！\p"
	.string "… …\n"
	.string "他为什么去？\p"
	.string "哇哈哈！你以为我真的会告诉\n"
	.string "你那么重要的事吗？$"

AquaHideout_1F_Text_TeamMagmaAtMtChimney:
	.string "{CHN}什么？什么？\n"
	.string "你是火焰队的队员吗？\p"
	.string "我听说火焰队在烟突山\n"
	.string "追捕一只厉害的宝可梦。\p"
	.string "但那是只什么样的宝可梦呢？$"

AquaHideout_1F_Text_BossIsInSlateportCity:
	.string "{CHN}什么？什么？你找\n"
	.string "水舰队有什么事？\p"
	.string "我们老大不在这里！\n"
	.string "他正前往凯那市！\p"
	.string "… …\n"
	.string "他为什么去？\p"
	.string "哇哈哈！你以为我真的会告诉\n"
	.string "你那么重要的事吗？$"

AquaHideout_1F_Text_Grunt1Intro:
	.string "{CHN}哎呀呀！\n"
	.string "发现可疑人物！$"

AquaHideout_1F_Text_Grunt1Defeat:
	.string "{CHN}呃呃呃…\n"
	.string "我输了！$"

AquaHideout_1F_Text_Grunt1PostBattle:
	.string "{CHN}我为了团队输了，\n"
	.string "但我完成了任务…$"
