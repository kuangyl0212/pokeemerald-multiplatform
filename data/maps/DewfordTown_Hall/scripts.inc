DewfordTown_Hall_MapScripts::
	.byte 0

DewfordTown_Hall_EventScript_Girl::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	special IsTrendyPhraseBoring
	goto_if_eq VAR_RESULT, TRUE, DewfordTown_Hall_EventScript_GirlBoredOfTrend
	msgbox DewfordTown_Hall_Text_CantImagineLifeWithoutTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_GirlBoredOfTrend::
	msgbox DewfordTown_Hall_Text_GettingBoredOfTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Woman::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_TeachingMonAboutTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Man::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	special BufferDeepLinkPhrase
	msgbox DewfordTown_Hall_Text_DeepLinkBetweenXAndY, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, DewfordTown_Hall_EventScript_ConfirmTrendLink
	goto_if_eq VAR_RESULT, NO, DewfordTown_Hall_EventScript_RejectTrendLink
	end

DewfordTown_Hall_EventScript_ConfirmTrendLink::
	msgbox DewfordTown_Hall_Text_MyHunchWasRight, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_RejectTrendLink::
	msgbox DewfordTown_Hall_Text_NotEasyToKeepUp, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_ExpertM::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_TVShowAboutTrend, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEWFORD_HALL_EXPERT_M, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

DewfordTown_Hall_EventScript_Twin::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_IsTrendMorePopularAcrossSea, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEWFORD_HALL_TWIN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

DewfordTown_Hall_EventScript_LittleBoy::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_CollectTrendMerchandise, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Bookshelf::
	lockall
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_BooksAboutTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_Painting::
	lockall
	call Common_EventScript_BufferTrendyPhrase
	special GetDewfordHallPaintingNameIndex
	switch VAR_RESULT
	case 0, DewfordTown_Hall_EventScript_ScreamTitle
	case 4, DewfordTown_Hall_EventScript_ScreamTitle
	case 1, DewfordTown_Hall_EventScript_SmileTitle
	case 5, DewfordTown_Hall_EventScript_ScreamTitle
	case 2, DewfordTown_Hall_EventScript_LastTitle
	case 6, DewfordTown_Hall_EventScript_LastTitle
	case 3, DewfordTown_Hall_EventScript_BirthTitle
	case 7, DewfordTown_Hall_EventScript_LastTitle
	end

DewfordTown_Hall_EventScript_ScreamTitle::
	msgbox DewfordTown_Hall_Text_TrendsScream, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_SmileTitle::
	msgbox DewfordTown_Hall_Text_TrendsSmile, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_LastTitle::
	msgbox DewfordTown_Hall_Text_LastTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_BirthTitle::
	msgbox DewfordTown_Hall_Text_BirthOfTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_SchoolKidM::
	lockall
	setvar VAR_0x8008, 0
	goto DewfordTown_Hall_EventScript_DoTrendDebate
	end

DewfordTown_Hall_EventScript_PsychicM::
	lockall
	setvar VAR_0x8008, 1
	goto DewfordTown_Hall_EventScript_DoTrendDebate
	end

DewfordTown_Hall_EventScript_DoTrendDebate::
	call Common_EventScript_BufferTrendyPhrase
	special GetDewfordHallPaintingNameIndex
	switch VAR_RESULT
	case 0, DewfordTown_Hall_EventScript_TrendDebate1
	case 1, DewfordTown_Hall_EventScript_TrendDebate1
	case 2, DewfordTown_Hall_EventScript_TrendDebate2
	case 3, DewfordTown_Hall_EventScript_TrendDebate2
	case 4, DewfordTown_Hall_EventScript_TrendDebate3
	case 5, DewfordTown_Hall_EventScript_TrendDebate3
	case 6, DewfordTown_Hall_EventScript_TrendDebate4
	case 7, DewfordTown_Hall_EventScript_TrendDebate5
	end

DewfordTown_Hall_EventScript_TrendDebate1::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_SawTrendCoolestThing, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_AllegedTrendNotAuthentic, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate2::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_ComposedTrendThemeSong, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_WorkOnYourSinging, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate3::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_OrganizeTrendParty, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_BrilliantIndeed, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate4::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_TrendHasBecomePartOfLife, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_TrendWeighsHeavilyOnMind, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate5::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_IfWeTeamUpWellBeInvincible, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_WellBeTrendDuo, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_DontMovePlayer1::
	return

DewfordTown_Hall_EventScript_DebateReact1::
	applymovement LOCALID_DEWFORD_HALL_PSYCHIC_M, DewfordTown_Hall_Movement_PsychicWalkInPlaceLeft
	waitmovement 0
	goto_if_eq VAR_0x8008, 0, DewfordTown_Hall_EventScript_PlayerReactWest
	goto_if_eq VAR_0x8008, 1, DewfordTown_Hall_EventScript_DontMovePlayer2
	end

DewfordTown_Hall_EventScript_PlayerReactWest::
	goto_if_eq VAR_FACING, DIR_EAST, DewfordTown_Hall_EventScript_DontMovePlayer1
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

DewfordTown_Hall_EventScript_DontMovePlayer2::
	return

DewfordTown_Hall_EventScript_DebateReact2::
	applymovement LOCALID_DEWFORD_HALL_SCHOOL_KID_M, DewfordTown_Hall_Movement_SchoolKidWalkInPlaceRight
	waitmovement 0
	goto_if_eq VAR_0x8008, 0, DewfordTown_Hall_EventScript_PlayerReactNorthSouth
	goto_if_eq VAR_0x8008, 1, DewfordTown_Hall_EventScript_PlayerReactEast
	end

DewfordTown_Hall_EventScript_PlayerReactNorthSouth::
	call_if_eq VAR_FACING, DIR_NORTH, DewfordTown_Hall_EventScript_PlayerWalkInPlaceUp
	call_if_eq VAR_FACING, DIR_SOUTH, DewfordTown_Hall_EventScript_PlayerWalkInPlaceDown
	return

DewfordTown_Hall_EventScript_PlayerWalkInPlaceUp::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

DewfordTown_Hall_EventScript_PlayerWalkInPlaceDown::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

DewfordTown_Hall_EventScript_PlayerReactEast::
	goto_if_eq VAR_FACING, DIR_WEST, DewfordTown_Hall_EventScript_DontMovePlayer1
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

DewfordTown_Hall_Movement_PsychicWalkInPlaceLeft:
	walk_in_place_left
	step_end

DewfordTown_Hall_Movement_SchoolKidWalkInPlaceRight:
	walk_in_place_right
	step_end

DewfordTown_Hall_EventScript_SludgeBombMan::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	goto_if_set FLAG_RECEIVED_TM_SLUDGE_BOMB, DewfordTown_Hall_EventScript_ReceivedSludgeBomb
	msgbox DewfordTown_Hall_Text_GiveYouSludgeBomb, MSGBOX_DEFAULT
	giveitem ITEM_TM_SLUDGE_BOMB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_SLUDGE_BOMB
	release
	end

DewfordTown_Hall_EventScript_ReceivedSludgeBomb::
	msgbox DewfordTown_Hall_Text_LoveSludgeBombButTrendInToo, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_Text_CantImagineLifeWithoutTrend:
	.string "{CHN}现在流行什么？当然是\n"
	.string "“{STR_VAR_1}”！\p"
	.string "我无法想象没有\n"
	.string "“{STR_VAR_1}”的生活会是什么样子！$"

DewfordTown_Hall_Text_GettingBoredOfTrend:
	.string "{CHN}现在流行什么？当然是\n"
	.string "“{STR_VAR_1}”！\p"
	.string "但我有点厌倦了。\p"
	.string "我该寻找下一个大热门了。$"

DewfordTown_Hall_Text_TeachingMonAboutTrend:
	.string "{CHN}我在教我的宝可梦关于\n"
	.string "“{STR_VAR_1}”的事，\l"
	.string "但进行得不太顺利。\p"
	.string "我觉得有点太难了。$"

DewfordTown_Hall_Text_DeepLinkBetweenXAndY:
	.string "{CHN}我正在研究时下流行的\n"
	.string "“{STR_VAR_1}”。\p"
	.string "“{STR_VAR_1}”\n"
	.string "和“{STR_VAR_2}”之间\l"
	.string "真的有深刻的联系吗？$"

DewfordTown_Hall_Text_MyHunchWasRight:
	.string "{CHN}哦！\n"
	.string "所以，我的直觉是对的！\p"
	.string "我离成为时尚达人又近了一步，\n"
	.string "太棒了！$"

DewfordTown_Hall_Text_NotEasyToKeepUp:
	.string "{CHN}什么？！\n"
	.string "是这样吗？！\p"
	.string "像我这样的老人家\n"
	.string "要跟上潮流可不容易！$"

DewfordTown_Hall_Text_TVShowAboutTrend:
	.string "{CHN}关于\n"
	.string "“{STR_VAR_1}”的这整件事……\l"
	.string "难道没有关于它的电视节目吗？$"

DewfordTown_Hall_Text_IsTrendMorePopularAcrossSea:
	.string "{CHN}在大海的对岸……\p"
	.string "“{STR_VAR_1}”是不是\n"
	.string "更受欢迎？$"

DewfordTown_Hall_Text_CollectTrendMerchandise:
	.string "{CHN}我收集官方\n"
	.string "“{STR_VAR_1}”\l"
	.string "授权商品。\p"
	.string "我有官方\n"
	.string "“{STR_VAR_1}”玩偶……\p"
	.string "官方“{STR_VAR_1}”\n"
	.string "品牌服装……\p"
	.string "还有官方授权的\n"
	.string "“{STR_VAR_1}”\l"
	.string "图画书。\p"
	.string "嘿嘿，都是我的！\n"
	.string "我什么都不会分给你！$"

DewfordTown_Hall_Text_BooksAboutTrend:
	.string "{CHN}辨别好的\n"
	.string "“{STR_VAR_1}”和\l"
	.string "坏的“{STR_VAR_1}”……\p"
	.string "“{STR_VAR_1}”\n"
	.string "与宝可梦之间的\l"
	.string "联系……\p"
	.string "有用的\n"
	.string "“{STR_VAR_1}”……\p"
	.string "整整齐齐地塞满了关于\n"
	.string "“{STR_VAR_1}”的书。$"

DewfordTown_Hall_Text_TrendsScream:
	.string "{CHN}标题是“{STR_VAR_1}的\n"
	.string "尖叫”。$"

DewfordTown_Hall_Text_TrendsSmile:
	.string "{CHN}标题是“{STR_VAR_1}的\n"
	.string "微笑”。$"

DewfordTown_Hall_Text_LastTrend:
	.string "{CHN}标题是“最后的\n"
	.string "{STR_VAR_1}”。$"

DewfordTown_Hall_Text_BirthOfTrend:
	.string "{CHN}标题是“{STR_VAR_1}的\n"
	.string "诞生”。$"

DewfordTown_Hall_Text_SawTrendCoolestThing:
	.string "{CHN}我看到了“{STR_VAR_1}”！\n"
	.string "很酷吧？\p"
	.string "那可是最酷的东西了！\p"
	.string "太棒了！\n"
	.string "那是真正的宝贝，没错！$"

DewfordTown_Hall_Text_AllegedTrendNotAuthentic:
	.string "{CHN}哦，不，不，不。\p"
	.string "你声称看到的那个所谓的\n"
	.string "“{STR_VAR_1}”\l"
	.string "——那不是真的。\p"
	.string "真正的物品要更加……\n"
	.string "怎么说呢？\l"
	.string "更加犀利，却又更加醇厚！\p"
	.string "啊，不管怎样。太惊人了！$"

DewfordTown_Hall_Text_ComposedTrendThemeSong:
	.string "{CHN}嘿，听着，我为\n"
	.string "“{STR_VAR_1}”作了一首主题曲。\p"
	.string "“{STR_VAR_1}”\n"
	.string "现在真的很受欢迎。\p"
	.string "好了，听着！\n"
	.string "…… …...\p"
	.string "哦！\n"
	.string "{STR_VAR_1}！\p"
	.string "美妙的\n"
	.string "{STR_VAR_1}！$"

DewfordTown_Hall_Text_WorkOnYourSinging:
	.string "{CHN}…… …...\p"
	.string "我敢说，老兄，在你\n"
	.string "涉足“{STR_VAR_1}”之前，\l"
	.string "你还是先练练唱歌吧，\l"
	.string "这样会更好。$"

DewfordTown_Hall_Text_OrganizeTrendParty:
	.string "{CHN}总之，就像我之前说的，我们\n"
	.string "应该聚在一起组织一个\l"
	.string "“{STR_VAR_1}”派对，\l"
	.string "在岛上举办。$"

DewfordTown_Hall_Text_BrilliantIndeed:
	.string "{CHN}哦，真是个绝妙的好主意！\p"
	.string "这将一劳永逸地决定\n"
	.string "谁最擅长\l"
	.string "“{STR_VAR_1}”。\l"
	.string "确实太棒了！\p"
	.string "从今天开始，我们的生活将围绕\n"
	.string "“{STR_VAR_1}”转！$"

DewfordTown_Hall_Text_TrendHasBecomePartOfLife:
	.string "{CHN}不过我在想……\p"
	.string "你不同意吗？\n"
	.string "“{STR_VAR_1}”已经\l"
	.string "从一种潮流变成了\l"
	.string "我们日常生活的一部分了？$"

DewfordTown_Hall_Text_TrendWeighsHeavilyOnMind:
	.string "{CHN}你说什么？\n"
	.string "那么多，什么？\p"
	.string "不过，确实\n"
	.string "“{STR_VAR_1}”\l"
	.string "在你的心头占据着很重要的位置，无论\l"
	.string "你是醒着还是睡着。\p"
	.string "毫无疑问，你就是\n"
	.string "“{STR_VAR_1}”\l"
	.string "教授，老兄！$"

DewfordTown_Hall_Text_IfWeTeamUpWellBeInvincible:
	.string "{CHN}如果你和我联手组队，\n"
	.string "在所有关于\l"
	.string "“{STR_VAR_1}”的事情上我们将无敌！$"

DewfordTown_Hall_Text_WellBeTrendDuo:
	.string "{CHN}说得好，我的朋友！\p"
	.string "我们将成为\n"
	.string "“{STR_VAR_1}”二人组！\p"
	.string "这画面不错吧？\n"
	.string "哈哈哈哈！$"

DewfordTown_Hall_Text_GiveYouSludgeBomb:
	.string "{CHN}对我来说，污泥炸弹正处于\n"
	.string "人气的顶峰。就是它了。\p"
	.string "嗯？你告诉我你不知道\n"
	.string "污泥炸弹？\p"
	.string "那真是太可怜了。\n"
	.string "我给你一个。$"

DewfordTown_Hall_Text_LoveSludgeBombButTrendInToo:
	.string "{CHN}我喜欢污泥炸弹。\p"
	.string "但是会“{STR_VAR_1}”\n"
	.string "招式的宝可梦\l"
	.string "也很流行。$"

