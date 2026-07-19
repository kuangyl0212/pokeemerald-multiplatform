VerdanturfTown_WandasHouse_MapScripts::
	.byte 0

VerdanturfTown_WandasHouse_EventScript_Wally::
	lock
	faceplayer
	goto_if_set FLAG_WALLY_SPEECH, VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeech, MSGBOX_DEFAULT
	setflag FLAG_WALLY_SPEECH
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech::
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeechShort, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncle::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff
	msgbox VerdanturfTown_WandasHouse_Text_WallysNextDoor, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff::
	msgbox VerdanturfTown_WandasHouse_Text_WallySlippedOff, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyGoneThatFar, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandasBoyfriend::
	msgbox VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay, MSGBOX_NPC
	end

VerdanturfTown_WandasHouse_EventScript_Wanda::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WandaDontWorry
	goto_if_set FLAG_DEFEATED_WALLY_MAUVILLE, VerdanturfTown_WandasHouse_EventScript_MeetWanda
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_MeetWanda::
	msgbox VerdanturfTown_WandasHouse_Text_MeetWanda, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandaDontWorry::
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAunt::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen::
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened::
	msgbox VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_Text_StrongerSpeech:
	.string "{CHN}小光：我输给你了，{PLAYER}，但我\n"
	.string "已经不再沮丧了。\p"
	.string "因为我有了新的人生目标。\n"
	.string "我要和我的拉鲁拉丝一起，去\l"
	.string "挑战宝可梦道馆，成为\l"
	.string "伟大的训练家。\p"
	.string "请看着我吧，{PLAYER}。\n"
	.string "我会变得比你更强。\p"
	.string "到那时，我会向你发起\n"
	.string "再次对战。$"

VerdanturfTown_WandasHouse_Text_StrongerSpeechShort:
	.string "{CHN}小光：请看着我吧，{PLAYER}。\n"
	.string "我会变得比你更强。\p"
	.string "到那时，我会向你发起\n"
	.string "再次对战。$"

VerdanturfTown_WandasHouse_Text_WallysNextDoor:
	.string "{CHN}叔叔：哦！{PLAYER}{KUN}！\n"
	.string "小光就在隔壁。\p"
	.string "不过，孩子，有件事我必须\n"
	.string "告诉你。\p"
	.string "这里的自然环境对小光\n"
	.string "的健康大有裨益。\p"
	.string "也许不仅是环境的原因。\n"
	.string "可能是宝可梦给了\l"
	.string "这孩子希望。$"

VerdanturfTown_WandasHouse_Text_WallySlippedOff:
	.string "{CHN}小光离开了…\n"
	.string "他自己一个人偷偷溜走了…$"

VerdanturfTown_WandasHouse_Text_WallyGoneThatFar:
	.string "{CHN}叔叔：是这样吗？\n"
	.string "小光居然一个人走了\l"
	.string "那么远…\p"
	.string "嗯，我不得不佩服他——他毕竟\n"
	.string "是我弟弟的儿子。$"

VerdanturfTown_WandasHouse_Text_MeetWanda:
	.string "{CHN}琳达：你是？\n"
	.string "哦，对，我明白了！\p"
	.string "你就是小光跟我提过的\n"
	.string "{PLAYER}啊。\p"
	.string "我是小光的表姐。\n"
	.string "很高兴见到你！\p"
	.string "我觉得小光自从来到这里后，\n"
	.string "变得更有活力也更健康了。$"

VerdanturfTown_WandasHouse_Text_DontWorryAboutWally:
	.string "{CHN}琳达：不用担心小光。\n"
	.string "他会没事的。\p"
	.string "我了解我的表弟，而且他\n"
	.string "也有宝可梦陪着他。$"

VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay:
	.string "{CHN}多亏了你，我现在每天\n"
	.string "都能见到我的女朋友。\l"
	.string "高兴？那是当然的！$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven:
	.string "{CHN}我女儿的男友是一个非常有\n"
	.string "干劲和热情的人。\p"
	.string "为了能见到我女儿，他一直在\n"
	.string "不停地挖着隧道。\p"
	.string "我女儿有点担心，\n"
	.string "所以经常去隧道那边。$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging:
	.string "{CHN}太惊人了。我女儿的男友\n"
	.string "竟然是徒手在挖隧道！\p"
	.string "真是不可思议！$"

VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally:
	.string "{CHN}如果小光出了什么事，\n"
	.string "我就再也无法面对他在\l"
	.string "橙华市的父母了…$"

VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande:
	.string "{CHN}小光在彩幽市？\p"
	.string "他在橙华市的父母\n"
	.string "听到这个一定会很吃惊的！$"

