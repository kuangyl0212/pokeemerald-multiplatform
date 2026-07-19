LavaridgeTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LavaridgeTown_OnFrame
	.byte 0

LavaridgeTown_OnTransition:
	setflag FLAG_VISITED_LAVARIDGE_TOWN
	call_if_set FLAG_WHITEOUT_TO_LAVARIDGE, LavaridgeTown_EventScript_ClearLavaridgeWhiteOut
	call_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, LavaridgeTown_EventScript_ShowMtChimneyTrainers
	call Common_EventScript_SetupRivalGfxId
	call Common_EventScript_SetupRivalOnBikeGfxId
	call_if_eq VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_CheckSetRivalPos
	call_if_eq VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_HideMapNamePopup
	end

LavaridgeTown_EventScript_ClearLavaridgeWhiteOut::
	clearflag FLAG_WHITEOUT_TO_LAVARIDGE
	return

LavaridgeTown_EventScript_CheckSetRivalPos::
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8004, 9, LavaridgeTown_EventScript_SetRivalPos
	return

LavaridgeTown_EventScript_SetRivalPos::
	setobjectxyperm LOCALID_LAVARIDGE_RIVAL, 11, 9
	setobjectxyperm LOCALID_LAVARIDGE_RIVAL_ON_BIKE, 9, 8
	setobjectmovementtype LOCALID_LAVARIDGE_RIVAL_ON_BIKE, MOVEMENT_TYPE_FACE_UP
	clearflag FLAG_HIDE_LAVARIDGE_TOWN_RIVAL
	return

LavaridgeTown_EventScript_ShowMtChimneyTrainers::
	clearflag FLAG_HIDE_MT_CHIMNEY_TRAINERS
	return

LavaridgeTown_EventScript_HideMapNamePopup::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

LavaridgeTown_OnFrame:
	map_script_2 VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_RivalGiveGoGoggles
	.short 0

LavaridgeTown_EventScript_RivalGiveGoGoggles::
	lockall
	getplayerxy VAR_0x8008, VAR_0x8009
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalNoticePlayer
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExitHerbShop
	delay 20
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LavaridgeTown_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, LavaridgeTown_EventScript_PlayBrendanMusic
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalApproachPlayer1
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalApproachPlayer2
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LavaridgeTown_EventScript_MayGiveGoGoggles
	goto_if_eq VAR_RESULT, FEMALE, LavaridgeTown_EventScript_BrendanGiveGoGoggles
	end

LavaridgeTown_EventScript_MayGiveGoGoggles::
	msgbox LavaridgeTown_Text_MayNiceBadgesTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox LavaridgeTown_Text_MayExplainGoGogglesChallengeDad, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_RivalExit
	end

LavaridgeTown_EventScript_BrendanGiveGoGoggles::
	msgbox LavaridgeTown_Text_BrendanNiceBadgesTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox LavaridgeTown_Text_BrendanExplainGoGogglesChallengeDad, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_RivalExit
	end

LavaridgeTown_EventScript_RivalExit::
	closemessage
	removeobject LOCALID_LAVARIDGE_RIVAL
	addobject LOCALID_LAVARIDGE_RIVAL_ON_BIKE
	delay 30
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExit1
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExit2
	removeobject LOCALID_LAVARIDGE_RIVAL_ON_BIKE
	setvar VAR_LAVARIDGE_TOWN_STATE, 2
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LavaridgeTown_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	return

LavaridgeTown_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	return

LavaridgeTown_EventScript_RivalNoticePlayer::
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_Delay48
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExitHerbShop::
	opendoor 12, 15
	waitdooranim
	addobject LOCALID_LAVARIDGE_RIVAL
	applymovement LOCALID_LAVARIDGE_RIVAL, LavaridgeTown_Movement_RivalExitHerbShop
	waitmovement 0
	closedoor 12, 15
	waitdooranim
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalApproachPlayer1::
	applymovement LOCALID_LAVARIDGE_RIVAL, LavaridgeTown_Movement_RivalApproachPlayer1
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalApproachPlayer2::
	applymovement LOCALID_LAVARIDGE_RIVAL, LavaridgeTown_Movement_RivalApproachPlayer2
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExit1::
	applymovement LOCALID_PLAYER, LavaridgeTown_Movement_PlayerWatchRivalExit
	applymovement LOCALID_LAVARIDGE_RIVAL_ON_BIKE, LavaridgeTown_Movement_RivalExit1
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExit2::
	applymovement LOCALID_LAVARIDGE_RIVAL_ON_BIKE, LavaridgeTown_Movement_RivalExit2
	waitmovement 0
	return

LavaridgeTown_Movement_RivalExit2:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

LavaridgeTown_Movement_PlayerWatchRivalExit:
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

LavaridgeTown_Movement_RivalExit1:
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

LavaridgeTown_Movement_RivalApproachPlayer2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LavaridgeTown_Movement_RivalApproachPlayer1:
	walk_left
	walk_left
	walk_up
	step_end

LavaridgeTown_Movement_RivalExitHerbShop:
	walk_down
	step_end

LavaridgeTown_EventScript_HotSpringsTrigger::
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_SOUTH, LavaridgeTown_EventScript_EnteredHotSprings
	end

LavaridgeTown_EventScript_EnteredHotSprings::
	incrementgamestat GAME_STAT_ENTERED_HOT_SPRINGS
	end

LavaridgeTown_EventScript_ExpertM::
	msgbox LavaridgeTown_Text_HotSpringsNeverRunDry, MSGBOX_NPC
	end

LavaridgeTown_EventScript_OldMan::
	msgbox LavaridgeTown_Text_PokemonNippedBackside, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_Twin::
	msgbox LavaridgeTown_Text_BatheInHotSpringsEveryDay, MSGBOX_NPC
	end

LavaridgeTown_EventScript_HotSpringsOldWoman1::
	msgbox LavaridgeTown_Text_IfPokemonInHotSprings, MSGBOX_NPC
	end

LavaridgeTown_EventScript_HotSpringsOldWoman2::
	msgbox LavaridgeTown_Text_HotSpringsClaims, MSGBOX_NPC
	end

LavaridgeTown_EventScript_ExpertF::
	msgbox LavaridgeTown_Text_OhYouLikeHotSprings, MSGBOX_NPC
	end

LavaridgeTown_EventScript_EggWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_LAVARIDGE_EGG, LavaridgeTown_EventScript_ReceivedEgg
	msgbox LavaridgeTown_Text_HaveEggWillYouTakeIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LavaridgeTown_EventScript_DeclineEgg
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, LavaridgeTown_EventScript_NoRoomForEgg
	msgbox LavaridgeTown_Text_HopeYoullWalkPlentyWithEgg, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_LAVARIDGE_EGG
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_ReceivedTheEgg
	waitfanfare
	giveegg SPECIES_WYNAUT
	release
	end

LavaridgeTown_EventScript_ReceivedEgg::
	msgbox LavaridgeTown_Text_EverySoOftenEggFoundAtDayCare, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_NoRoomForEgg::
	msgbox LavaridgeTown_Text_NoRoomForThisEgg, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_DeclineEgg::
	msgbox LavaridgeTown_Text_AsYouWishThen, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_TownSign::
	msgbox LavaridgeTown_Text_TownSign, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_GymSign::
	msgbox LavaridgeTown_Text_GymSign, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_HerbShopSign::
	msgbox LavaridgeTown_Text_HerbShopSign, MSGBOX_SIGN
	end

LavaridgeTown_Text_MayNiceBadgesTakeThis:
	.string "{CHN}小遥：{PLAYER}{KUN}！好久不见！\p"
	.string "哦？我去泡温泉的时候，\n"
	.string "你已经拿到了烟突道馆的徽章。\p"
	.string "你一定收集了\n"
	.string "很好的宝可梦……\l"
	.string "不，我相信你是培养出来的。\p"
	.string "我想把这个\n"
	.string "给你也没关系。$"

LavaridgeTown_Text_MayExplainGoGogglesChallengeDad:
	.string "{CHN}小遥：有了那个防沙护目镜，你\n"
	.string "通过111号道路附近的\l"
	.string "沙漠就没问题了。\p"
	.string "但是，哇，{PLAYER}{KUN}……\n"
	.string "挑战道馆……\p"
	.string "你这么努力，是因为不想\n"
	.string "输给我吧，我猜！\p"
	.string "{PLAYER}{KUN}，我想我应该去挑战\n"
	.string "你爸爸在橙华道馆。\p"
	.string "再见啦！$"

LavaridgeTown_Text_BrendanNiceBadgesTakeThis:
	.string "{CHN}佑树：{PLAYER}，嘿，好久不见。\n"
	.string "最近怎么样？\p"
	.string "嗯……\n"
	.string "徽章收集得不错。\p"
	.string "那好吧。\n"
	.string "这个给你。$"

LavaridgeTown_Text_BrendanExplainGoGogglesChallengeDad:
	.string "{CHN}佑树：如果你打算去111号道路\n"
	.string "附近的那片沙漠，\l"
	.string "就把这个带在身上。\p"
	.string "那里应该有一些\n"
	.string "沙漠特有的宝可梦。\l"
	.string "你可以找找看。\p"
	.string "至于我……\n"
	.string "我在考虑挑战\l"
	.string "橙华道馆的馆主千里。\p"
	.string "不像你，{PLAYER}，你爸爸看起来\n"
	.string "真的很强。\p"
	.string "再见！$"

LavaridgeTown_Text_HaveEggWillYouTakeIt:
	.string "{CHN}我这里有一颗蛋。\p"
	.string "我本想通过在温泉旁用热沙\n"
	.string "把它盖住来孵化它。\l"
	.string "但那似乎不够……\p"
	.string "我听说最好把它和宝可梦\n"
	.string "放在一起，\l"
	.string "带在身边走动。\p"
	.string "你是训练家，对吧？\n"
	.string "而且你的宝可梦充满活力。\p"
	.string "所以，你觉得呢？\n"
	.string "你愿意带着这颗蛋去孵化吗？$"

LavaridgeTown_Text_HopeYoullWalkPlentyWithEgg:
	.string "{CHN}太好了！希望你多带着\n"
	.string "这颗蛋走走！$"

LavaridgeTown_Text_ReceivedTheEgg:
	.string "{CHN}{PLAYER}获得了蛋。$"

LavaridgeTown_Text_NoRoomForThisEgg:
	.string "{CHN}哦？你的宝可梦太多了。\n"
	.string "这颗蛋没地方放了……$"

LavaridgeTown_Text_AsYouWishThen:
	.string "{CHN}那就随你吧……\p"
	.string "如果你改变主意\n"
	.string "想孵化这颗蛋，我会在这里。$"

LavaridgeTown_Text_EverySoOftenEggFoundAtDayCare:
	.string "{CHN}每隔一段时间，宝可梦\n"
	.string "寄放屋就会发现一颗蛋。\p"
	.string "至少传说是这样的。$"

LavaridgeTown_Text_HotSpringsNeverRunDry:
	.string "{CHN}我们想抽多少热水就抽多少，\n"
	.string "温泉却从不干涸。\p"
	.string "是不是很神奇？\p"
	.string "这些温泉出现在活火山附近。\n"
	.string "地下的水脉被\l"
	.string "岩浆加热，涌出地面\l"
	.string "成为温泉。$"

LavaridgeTown_Text_PokemonNippedBackside:
	.string "{CHN}被埋在这热沙里……\n"
	.string "唉……\p"
	.string "又温暖又舒服……\p"
	.string "嗯？呀啊！好痛！\p"
	.string "有宝可梦咬了我的屁股！$"

LavaridgeTown_Text_OhYouLikeHotSprings:
	.string "{CHN}哦，你喜欢温泉吗？\p"
	.string "对像你这么年轻的人来说\n"
	.string "还真少见。$"

LavaridgeTown_Text_BatheInHotSpringsEveryDay:
	.string "{CHN}我每天都泡温泉。\p"
	.string "我想成为像亚莎那样\n"
	.string "美丽又强大的道馆馆主。$"

LavaridgeTown_Text_IfPokemonInHotSprings:
	.string "{CHN}如果人们把宝可梦放进温泉里，\n"
	.string "那可能真的很奇怪。\p"
	.string "可能是电浴，或者\n"
	.string "泡泡浴，甚至是岩浆浴……$"

LavaridgeTown_Text_HotSpringsClaims:
	.string "{CHN}他们声称这温泉\n"
	.string "对缓解精神紧张、\l"
	.string "舒缓肌肉酸痛、解决\l"
	.string "感情问题、招财\l"
	.string "都有好处……$"

LavaridgeTown_Text_TownSign:
	.string "{CHN}烟突市\p"
	.string "“宝可梦中心温泉\n"
	.string "放松的绝佳去处！”$"

LavaridgeTown_Text_GymSign:
	.string "{CHN}烟突市宝可梦道馆\n"
	.string "馆主：亚莎\l"
	.string "“燃烧着火热热情的人！”$"

LavaridgeTown_Text_HerbShopSign:
	.string "{CHN}宝可梦草药店\n"
	.string "“苦口良药！”$"
