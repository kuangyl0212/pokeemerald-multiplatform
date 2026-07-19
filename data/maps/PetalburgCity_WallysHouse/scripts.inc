PetalburgCity_WallysHouse_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PetalburgCity_WallysHouse_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PetalburgCity_WallysHouse_OnWarp
	.byte 0

PetalburgCity_WallysHouse_OnWarp:
	map_script_2 VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_WallysHouse_EventScript_PlayerWallysDadFaceEachOther
	.short 0

PetalburgCity_WallysHouse_EventScript_PlayerWallysDadFaceEachOther::
	turnobject LOCALID_PLAYER, DIR_EAST
	turnobject LOCALID_WALLYS_HOUSE_WALLYS_DAD, DIR_WEST
	end

PetalburgCity_WallysHouse_OnFrame:
	map_script_2 VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_WallysHouse_EventScript_GiveHMSurf
	.short 0

PetalburgCity_WallysHouse_EventScript_GiveHMSurf::
	lockall
	msgbox PetalburgCity_WallysHouse_Text_PleaseExcuseUs, MSGBOX_DEFAULT
	giveitem ITEM_HM_SURF
	setflag FLAG_RECEIVED_HM_SURF
	msgbox PetalburgCity_WallysHouse_Text_SurfGoAllSortsOfPlaces, MSGBOX_DEFAULT
	setvar VAR_PETALBURG_CITY_STATE, 5
	releaseall
	end

PetalburgCity_WallysHouse_EventScript_WallysDad::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, PetalburgCity_WallysHouse_EventScript_DefeatedWallyInVictoryRoad
	goto_if_set FLAG_RECEIVED_HM_SURF, PetalburgCity_WallysHouse_EventScript_ReceievedHMSurf
	goto_if_set FLAG_THANKED_FOR_PLAYING_WITH_WALLY, PetalburgCity_WallysHouse_EventScript_PlayedWithWally
	msgbox PetalburgCity_WallysHouse_Text_ThanksForPlayingWithWally, MSGBOX_DEFAULT
	setflag FLAG_THANKED_FOR_PLAYING_WITH_WALLY
	release
	end

PetalburgCity_WallysHouse_EventScript_ReceievedHMSurf::
	msgbox PetalburgCity_WallysHouse_Text_WallyIsComingHomeSoon, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_DefeatedWallyInVictoryRoad::
	msgbox PetalburgCity_WallysHouse_Text_YouMetWallyInEverGrandeCity, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_PlayedWithWally::
	msgbox PetalburgCity_WallysHouse_Text_WonderHowWallyIsDoing, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_WallysMom::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_SURF, PetalburgCity_WallysHouse_EventScript_ReceivedHMSurf
	msgbox PetalburgCity_WallysHouse_Text_WallyWasReallyHappy, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_ReceivedHMSurf::
	msgbox PetalburgCity_WallysHouse_Text_WallyLeftWithoutTelling, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_Text_ThanksForPlayingWithWally:
	.string "{CHN}你是……\n"
	.string "啊，你一定是{PLAYER}{KUN}，对吧？\p"
	.string "谢谢你之前陪\n"
	.string "小光玩了一会。\p"
	.string "他从婴儿时期起\n"
	.string "就身体虚弱。\p"
	.string "我们把他送去\n"
	.string "和我茵郁市的亲戚住一阵子。\p"
	.string "那里的空气\n"
	.string "比这里干净得多。\p"
	.string "什么？小光在哪里？\n"
	.string "他已经出发了，我们家的小光。\p"
	.string "不知道他现在\n"
	.string "已经走到哪里了呢？$"

PetalburgCity_WallysHouse_Text_WonderHowWallyIsDoing:
	.string "{CHN}不知道我们家的小光过得怎么样？$"

PetalburgCity_WallysHouse_Text_PleaseExcuseUs:
	.string "{CHN}{PLAYER}{KUN}！抱歉把你\n"
	.string "这样硬拉过来。\p"
	.string "不过我们家的小光自从去了茵郁市，\n"
	.string "身体变得非常健康。\p"
	.string "这都多亏了你！\p"
	.string "小光离开城镇的时候，\n"
	.string "你帮他捕捉了宝可梦，对吧？\p"
	.string "我觉得那让小光\n"
	.string "非常开心。\p"
	.string "其实，不只是小光。\n"
	.string "作为他的父亲，我也很开心。\p"
	.string "开心他能交到\n"
	.string "你这么棒的朋友。\p"
	.string "这不是什么贿赂，\n"
	.string "但我真的很想把这个送给你。$"

PetalburgCity_WallysHouse_Text_SurfGoAllSortsOfPlaces:
	.string "{CHN}如果你的宝可梦会冲浪，\n"
	.string "你就能去各种各样的地方了。$"

PetalburgCity_WallysHouse_Text_WallyIsComingHomeSoon:
	.string "{CHN}小光很快就要回家了。\n"
	.string "我很期待那一天。$"

PetalburgCity_WallysHouse_Text_YouMetWallyInEverGrandeCity:
	.string "{CHN}哦？你在彩幽市\n"
	.string"遇到了小光？\p"
	.string "哦，{PLAYER}{KUN}，别说傻话了。\p"
	.string "他虽然身体变好了，\n"
	.string "但不可能一个人\l"
	.string "去那么远的地方。$"

PetalburgCity_WallysHouse_Text_WallyWasReallyHappy:
	.string "{CHN}小光告诉我们他捕捉到了宝可梦时，\n"
	.string "他真的很开心。\p"
	.string "我已经好久没看到他\n"
	.string "那样笑了。$"

PetalburgCity_WallysHouse_Text_WallyLeftWithoutTelling:
	.string "{CHN}这件事请你\n"
	.string "对我丈夫保密……\p"
	.string "但我们家的小光没告诉任何人\n"
	.string "就离开了茵郁市。\p"
	.string "你知道，小光虽然身体虚弱，\n"
	.string "但他的意志却出奇地坚强。\p"
	.string "我相信总有一天\n"
	.string "他会平安无事地回来！$"

