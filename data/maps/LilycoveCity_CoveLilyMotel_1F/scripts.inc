LilycoveCity_CoveLilyMotel_1F_MapScripts::
	.byte 0

LilycoveCity_CoveLilyMotel_1F_EventScript_MotelOwner::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_CoveLilyMotel_1F_EventScript_Gameclear
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_CoveLilyMotel_1F_EventScript_AquaHideoutBusted
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_GuestsDoubledByMascot, MSGBOX_DEFAULT
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_NoGuestsWithTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

LilycoveCity_CoveLilyMotel_1F_EventScript_AquaHideoutBusted::
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_MonFoundLostItem, MSGBOX_DEFAULT
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_HeardAquaHideoutBusted, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

LilycoveCity_CoveLilyMotel_1F_EventScript_Gameclear::
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_HouseSittingMonCaughtBurglar, MSGBOX_DEFAULT
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_BetterGetWorkingOnGuestsDinner, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

LilycoveCity_CoveLilyMotel_1F_EventScript_BlockingTV::
	lockall
	playse SE_PIN
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_CantSeeTheTV, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, LilycoveCity_CoveLilyMotel_1F_Movement_PlayerPushFromTV
	applymovement LOCALID_MOTEL_OWNER, LilycoveCity_CoveLilyMotel_1F_Movement_OwnerPushPlayer
	waitmovement 0
	applymovement LOCALID_MOTEL_OWNER, LilycoveCity_CoveLilyMotel_1F_Movement_OwnerReturn
	waitmovement 0
	release
	end

LilycoveCity_CoveLilyMotel_1F_Movement_PlayerPushFromTV:
	face_right
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

LilycoveCity_CoveLilyMotel_1F_Movement_OwnerPushPlayer:
	walk_up
	step_end

LilycoveCity_CoveLilyMotel_1F_Movement_OwnerReturn:
	face_down
	walk_down
	face_up
	step_end

LilycoveCity_CoveLilyMotel_1F_Text_GuestsDoubledByMascot:
	.string "{CHN}嗯，他们用宝可梦作为\n"
	.string "招揽手段让客人翻倍了？\p"
	.string "嗯，也许我该弄一只可爱的\n"
	.string "宝可梦当我们旅馆的吉祥物。\p"
	.string "我想这是不是能吸引更多\n"
	.string "客人来我们这里住呢？$"

LilycoveCity_CoveLilyMotel_1F_Text_NoGuestsWithTeamAqua:
	.string "{CHN}哦，对不起，对不起！\n"
	.string "我看电视看得太入迷了！\p"
	.string "自从那个水舰队来到镇上，\n"
	.string "游客都不来了。$"

LilycoveCity_CoveLilyMotel_1F_Text_CantSeeTheTV:
	.string "{CHN}喂，前面的让一让！\n"
	.string "我看不到电视了！$"

LilycoveCity_CoveLilyMotel_1F_Text_MonFoundLostItem:
	.string "{CHN}了不起！你是说一只宝可梦\n"
	.string "找到了别人遗失的物品？\p"
	.string "真了不起。如果我们有这样聪明的\n"
	.string "宝可梦…\p"
	.string "我们就能找回客人\n"
	.string "遗失的任何东西了…$"

LilycoveCity_CoveLilyMotel_1F_Text_HeardAquaHideoutBusted:
	.string "{CHN}哦，对不起，对不起！\n"
	.string "我看电视看得太入迷了！\p"
	.string "我听说有人捣毁了\n"
	.string "水舰队的藏身处。\p"
	.string "多亏了这样，我们刚接到了\n"
	.string "一个大团的预订。\p"
	.string "那家公司叫…呃…\n"
	.string "GAME什么的…$"

LilycoveCity_CoveLilyMotel_1F_Text_HouseSittingMonCaughtBurglar:
	.string "{CHN}了不起！看家的宝可梦\n"
	.string "抓住了小偷？\p"
	.string "真了不起。如果我们有一只强壮的\n"
	.string "宝可梦当保安…\p"
	.string "我们就能为客人\n"
	.string "提供更大的安全保障。$"

LilycoveCity_CoveLilyMotel_1F_Text_BetterGetWorkingOnGuestsDinner:
	.string "{CHN}哦，对不起，对不起！\n"
	.string "我看电视看得太入迷了。\p"
	.string "哦，对了。刚才有一大团客人\n"
	.string "到达了。\p"
	.string "他们以GAME FREAK的名字登记入住，\n"
	.string "我想他们应该是做游戏的。\p"
	.string "糟了，我得去准备\n"
	.string "他们的晚餐了！$"
