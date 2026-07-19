MauvilleCity_PokemonCenter_1F_EventScript_MauvilleOldMan::
	special Script_GetCurrentMauvilleMan
	switch VAR_RESULT
	case MAUVILLE_MAN_BARD, MauvilleCity_PokemonCenter_1F_EventScript_Bard
	case MAUVILLE_MAN_HIPSTER, MauvilleCity_PokemonCenter_1F_EventScript_Hipster
	case MAUVILLE_MAN_TRADER, MauvilleCity_PokemonCenter_1F_EventScript_Trader
	case MAUVILLE_MAN_STORYTELLER, MauvilleCity_PokemonCenter_1F_EventScript_Storyteller
	case MAUVILLE_MAN_GIDDY, MauvilleCity_PokemonCenter_1F_EventScript_Giddy
	end

/* Bard*/
MauvilleCity_PokemonCenter_1F_EventScript_Bard::
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToHearMySong, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_PlaySong
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineSong
	end

MauvilleCity_PokemonCenter_1F_EventScript_PlaySong::
	setvar VAR_0x8004, FALSE  @ Play his current song
	special PlayBardSong
	delay 60
	special HasBardSongBeenChanged
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_AskToWriteLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_WishICouldPlaySongForOthers, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineSong::
	msgbox MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues1, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_AskToWriteLyrics::
	msgbox MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToWriteSomeLyrics, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics
	end

MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics::
	setvar VAR_0x8004, EASY_CHAT_TYPE_BARD_SONG
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_LetMeSingItForYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, TRUE  @ Play the new song
	special PlayBardSong
	delay 60
	msgbox MauvilleCity_PokemonCenter_1F_Text_ThatHowYouWantedSongToGo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics
	special SaveBardSongLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_IllSingThisSongForAWhile, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics::
	msgbox MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues2, MSGBOX_DEFAULT
	release
	end

/* Hipster*/
MauvilleCity_PokemonCenter_1F_EventScript_Hipster::
	lock
	faceplayer
	setflag FLAG_UNLOCKED_TRENDY_SAYINGS
	msgbox MauvilleCity_PokemonCenter_1F_Text_TeachWhatsHipAndHappening, MSGBOX_DEFAULT
	special HasHipsterTaughtWord
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_TryTeachWord
	msgbox MauvilleCity_PokemonCenter_1F_Text_IAlreadyTaughtYou, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTeachWord::
	special HipsterTryTeachWord
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_TeachWord
	msgbox MauvilleCity_PokemonCenter_1F_Text_IveGotNothingNewToTeach, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TeachWord::
	msgbox MauvilleCity_PokemonCenter_1F_Text_HaveYouHeardOfWord, MSGBOX_DEFAULT
	special SetHipsterTaughtWord
	release
	end

/* Trader*/
MauvilleCity_PokemonCenter_1F_Text_WantToTradeDecor:
	.string "{CHN}嗨，我是交换者。\n"
	.string "想和我交换装饰品吗？$"

MauvilleCity_PokemonCenter_1F_Text_TraderFeelingTheBlues:
	.string "{CHN}哦……\n"
	.string "你让我感到忧伤……$"

MauvilleCity_PokemonCenter_1F_Text_WeveAlreadyTraded:
	.string "{CHN}但是我们之间已经交换过\n"
	.string "装饰品了。$"

MauvilleCity_PokemonCenter_1F_Text_PickADecorItem:
	.string "{CHN}如果你看到我的任何装饰品\n"
	.string "有想要的，就说出来。$"

MauvilleCity_PokemonCenter_1F_Text_YouDontWantAnything:
	.string "{CHN}你什么都不想要吗？\n"
	.string "我感觉自己不被需要……$"

MauvilleCity_PokemonCenter_1F_Text_OnceBelongedToPlayerDoYouWantIt:
	.string "{CHN}那件装饰品曾经属于\n"
	.string "{STR_VAR_1}。\p"
	.string "你想要吗？$"

MauvilleCity_PokemonCenter_1F_Text_YouDontHaveAnyDecor:
	.string "{CHN}呃……等一下。你连一件\n"
	.string "装饰品都没有！$"

MauvilleCity_PokemonCenter_1F_Text_PickTheDecorToTrade:
	.string "{CHN}好的，挑选你要和我\n"
	.string "交换的装饰品吧。$"

MauvilleCity_PokemonCenter_1F_Text_YouDontWantToTrade:
	.string "{CHN}你不和我交换吗？\n"
	.string "我感觉自己不被需要……$"

MauvilleCity_PokemonCenter_1F_Text_YouveNoRoomForThis:
	.string "{CHN}你已经拥有了所有能存放的\n"
	.string "{STR_VAR_2}。你放不下这个了。$"

MauvilleCity_PokemonCenter_1F_Text_SoWellTradeTheseDecor:
	.string "{CHN}好的，所以我们要用我的{STR_VAR_3}\n"
	.string "交换你的{STR_VAR_2}吗？$"

MauvilleCity_PokemonCenter_1F_Text_ThatDecorIsInUse:
	.string "{CHN}那件装饰品正在使用中。\n"
	.string "你不能交换它。$"

MauvilleCity_PokemonCenter_1F_Text_SendDecorToYourPC:
	.string "{CHN}那我们就交换吧！\n"
	.string "我会把我的装饰品送到你的电脑里。$"

MauvilleCity_PokemonCenter_1F_Text_CantTradeThatOne:
	.string "{CHN}哎呀！对不起！那是一件非常稀有的\n"
	.string "装饰品。\l"
	.string "我不能把它交换出去！\p"
	.string "能让你对其他东西感兴趣吗？$"

MauvilleCity_PokemonCenter_1F_EventScript_Trader::
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_WantToTradeDecor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineTrade
	special GetTraderTradedFlag
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_AlreadyTraded
	message MauvilleCity_PokemonCenter_1F_Text_PickADecorItem
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineTrade::
	msgbox MauvilleCity_PokemonCenter_1F_Text_TraderFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_AlreadyTraded::
	msgbox MauvilleCity_PokemonCenter_1F_Text_WeveAlreadyTraded, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive::
	special TraderMenuGetDecoration
	waitstate
	goto_if_eq VAR_0x8004, 0, MauvilleCity_PokemonCenter_1F_EventScript_CancelPickDecor
	goto_if_eq VAR_0x8004, 0xFFFF, MauvilleCity_PokemonCenter_1F_EventScript_InvalidDecor
	msgbox MauvilleCity_PokemonCenter_1F_Text_OnceBelongedToPlayerDoYouWantIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_PickDifferentDecor
	special DoesPlayerHaveNoDecorations
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_DontHaveAnyDecor
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	end

MauvilleCity_PokemonCenter_1F_EventScript_CancelPickDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontWantAnything, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_InvalidDecor::
	message MauvilleCity_PokemonCenter_1F_Text_CantTradeThatOne
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDifferentDecor::
	message MauvilleCity_PokemonCenter_1F_Text_PickADecorItem
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_DontHaveAnyDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontHaveAnyDecor, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive::
	msgbox MauvilleCity_PokemonCenter_1F_Text_PickTheDecorToTrade, MSGBOX_DEFAULT
	special TraderShowDecorationMenu
	waitstate
	goto_if_eq VAR_0x8006, 0, MauvilleCity_PokemonCenter_1F_EventScript_CancelGiveDecor
	goto_if_eq VAR_0x8006, 0xFFFF, MauvilleCity_PokemonCenter_1F_EventScript_DecorInUse
	special IsDecorationCategoryFull
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_NoRoomForDecor
	msgbox MauvilleCity_PokemonCenter_1F_Text_SoWellTradeTheseDecor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	special TraderDoDecorationTrade
	msgbox MauvilleCity_PokemonCenter_1F_Text_SendDecorToYourPC, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_CancelGiveDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontWantToTrade, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DecorInUse::
	msgbox MauvilleCity_PokemonCenter_1F_Text_ThatDecorIsInUse, MSGBOX_DEFAULT
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	end

MauvilleCity_PokemonCenter_1F_EventScript_NoRoomForDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouveNoRoomForThis, MSGBOX_DEFAULT
	release
	end

/* Storyteller*/
MauvilleCity_PokemonCenter_1F_Text_WillYouHearMyTale:
	.string "{CHN}我是说书人。\n"
	.string "我会给你讲述传奇训练家\l"
	.string "的故事。\p"
	.string "你愿意听我的故事吗？$"

MauvilleCity_PokemonCenter_1F_Text_StorytellerFeelingTheBlues:
	.string "{CHN}哦……\n"
	.string "你让我感到忧伤……$"

MauvilleCity_PokemonCenter_1F_Text_WhichTaleToTell:
	.string "{CHN}我知道这些传奇。\n"
	.string "你要我讲哪一个故事？$"

MauvilleCity_PokemonCenter_1F_Text_IKnowNoTales:
	.string "{CHN}但是，我不知道任何传奇训练家。\n"
	.string "因此，我不知道任何故事。\p"
	.string "到哪里才能找到一个\n"
	.string "值得传奇故事记载的训练家呢？$"

MauvilleCity_PokemonCenter_1F_Text_YouDidStatXTimes:
	.string "{CHN}什么？！\n"
	.string "你……你……\p"
	.string "{STR_VAR_2}\n"
	.string "{STR_VAR_1}次？！\p"
	.string "这真是了不起！\n"
	.string "这是一个新传奇的诞生！$"

MauvilleCity_PokemonCenter_1F_Text_CouldThereBeOtherLegends:
	.string "{CHN}这让我想，是不是还有其他\n"
	.string "训练家有着更令人惊叹的\l"
	.string "传奇等待被发现？$"

MauvilleCity_PokemonCenter_1F_Text_HaveYouAnyLegendaryTales:
	.string "{CHN}你是训练家吗？\p"
	.string "那么告诉我，你有没有\n"
	.string "任何算得上传奇的故事呢？$"

/* Unused*/
MauvilleCity_PokemonCenter_1F_Text_HearAnotherLegendaryTale:
	.string "{CHN}顺便问一下……你想听\n"
	.string "另一个传奇故事吗？$"

MauvilleCity_PokemonCenter_1F_Text_NotWorthyOfLegend:
	.string "{CHN}嗯……\n"
	.string "我不满意……\p"
	.string "希望你能带来\n"
	.string "值得被称为传奇的消息。$"

MauvilleCity_PokemonCenter_1F_Text_IWishMorePeopleWereInterested:
	.string "{CHN}我希望有更多人愿意听\n"
	.string "我讲述传奇训练家\l"
	.string "的史诗故事。$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameTitle::
	.string "{CHN}爱存档的训练家$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameAction::
	.string "{CHN}存档了$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家存档了\n"
	.string "{STR_VAR_1}次！\p"
	.string "再也找不到比{STR_VAR_3}\n"
	.string "更谨慎的训练家了！$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedTitle::
	.string "{CHN}引领潮流的训练家$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedAction::
	.string "{CHN}引领了潮流$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家引领了新潮流\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}正在为整个丰缘地区\n"
	.string "树立潮流！$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedTitle::
	.string "{CHN}种果子的训练家$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedAction::
	.string "{CHN}种了果子$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家种了果子\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}是一个传奇的\n"
	.string "果子爱好者！$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesTitle::
	.string "{CHN}爱自行车的训练家$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesAction::
	.string "{CHN}交换了自行车$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家交换了自行车\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}一定是非常\n"
	.string "热爱自行车！$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsTitle::
	.string "{CHN}接受采访的训练家$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsAction::
	.string "{CHN}接受了采访$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家接受了采访\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}一定是一个\n"
	.string "非常引人注目的训练家！$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesTitle::
	.string "{CHN}爱战斗的训练家$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesAction::
	.string "{CHN}战斗了$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家战斗了{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}一定是一个\n"
	.string "从不放弃战斗机会的训练家！$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtTitle::
	.string "{CHN}捕捉宝可梦的训练家$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtAction::
	.string "{CHN}捕捉了宝可梦$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家捕捉了\n"
	.string "{STR_VAR_1}只宝可梦！\p"
	.string "{STR_VAR_3}是一个传奇的\n"
	.string "野生宝可梦捕捉者！$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtTitle::
	.string "{CHN}钓鱼的训练家$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtAction::
	.string "{CHN}用钓竿钓到了宝可梦$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家钓鱼时\n"
	.string "钓到了{STR_VAR_1}只宝可梦！\p"
	.string "{STR_VAR_3}是一个传奇的\n"
	.string "钓鱼专家！$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedTitle::
	.string "{CHN}孵蛋的训练家$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedAction::
	.string "{CHN}孵化了蛋$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家从蛋中孵化了\n"
	.string "{STR_VAR_1}只宝可梦！\p"
	.string "{STR_VAR_3}是一个传奇的\n"
	.string "孵蛋者！$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedTitle::
	.string "{CHN}进化大师训练家$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedAction::
	.string "{CHN}让宝可梦进化了$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家让{STR_VAR_1}只宝可梦\n"
	.string "进化了！\p"
	.string "{STR_VAR_3}是终极的\n"
	.string "宝可梦进化大师！$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterTitle::
	.string "{CHN}爱宝可梦中心的训练家$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterAction::
	.string "{CHN}使用了宝可梦中心$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家在宝可梦中心\n"
	.string "治疗了{STR_VAR_1}次宝可梦！\p"
	.string "再没有人比{STR_VAR_3}\n"
	.string "更爱宝可梦中心了！$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeTitle::
	.string "{CHN}居家的训练家$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeAction::
	.string "{CHN}在家治疗了宝可梦$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家在家治疗了\n"
	.string "{STR_VAR_1}次宝可梦！\p"
	.string "再没有人比{STR_VAR_3}\n"
	.string "更居家了！$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesTitle::
	.string "{CHN}爱野生原野区的训练家$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesAction::
	.string "{CHN}进入了野生原野区$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家进入了野生原野区\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}是一个在野生原野区\n"
	.string "会展现野性的训练家！$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutTitle::
	.string "{CHN}居合斩狂热的训练家$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutAction::
	.string "{CHN}使用了居合斩$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家使用了居合斩\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}是一个\n"
	.string "就是爱用居合斩的训练家！$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashTitle::
	.string "{CHN}碎岩的训练家$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashAction::
	.string "{CHN}击碎了岩石$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家使用了碎岩\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}一定是一个\n"
	.string "见石头就要碎的训练家！$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesTitle::
	.string "{CHN}爱搬家的训练家$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesAction::
	.string "{CHN}搬迁了秘密基地$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家搬迁了秘密基地\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}是一个\n"
	.string "爱搬家的训练家！$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashTitle::
	.string "{CHN}爱水花溅起的训练家$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashAction::
	.string "{CHN}使用了水花溅起$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家使用了水花溅起\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}一定是一个\n"
	.string "爱用水花溅起的训练家！$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleTitle::
	.string "{CHN}顽强的训练家$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleAction::
	.string "{CHN}只能使用挣扎了$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家不得不依靠挣扎\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}是一个顽强的训练家，\n"
	.string "从不向逆境低头！$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsTitle::
	.string "{CHN}老虎机冠军$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsAction::
	.string "{CHN}在老虎机上中了头奖$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家在老虎机上中了\n"
	.string "{STR_VAR_1}次头奖。\p"
	.string "{STR_VAR_3}是一个在老虎机上\n"
	.string "很幸运的训练家！$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsTitle::
	.string "{CHN}轮盘赌冠军$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsAction::
	.string "{CHN}在轮盘赌上连续赢了$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家在轮盘赌中\n"
	.string "连续赢了{STR_VAR_1}次。\p"
	.string "{STR_VAR_3}在轮盘赌的球\n"
	.string "弹跳时很幸运！$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesTitle::
	.string "{CHN}对战塔挑战者$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesAction::
	.string "{CHN}接受了对战塔挑战$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家接受了对战塔\n"
	.string "挑战{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}是一个在对战塔中\n"
	.string "追求卓越的训练家！$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksTitle::
	.string "{CHN}爱制作方块糖的训练家$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksAction::
	.string "{CHN}制作了{POKEBLOCK}S$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家制作了{POKEBLOCK}S\n"
	.string "{STR_VAR_1}次！\p"
	.string "再没有人比{STR_VAR_3}\n"
	.string "更擅长使用果实搅拌机了！$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsTitle::
	.string "{CHN}爱华丽赛的训练家$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsAction::
	.string "{CHN}参加了华丽赛$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家参加了华丽赛\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}一定是一个\n"
	.string "爱向别人炫耀宝可梦的训练家！$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsTitle::
	.string "{CHN}华丽赛大师$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsAction::
	.string "{CHN}赢得了华丽赛$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家赢得了华丽赛\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}一定是一个\n"
	.string "出色的华丽赛大师！$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedTitle::
	.string "{CHN}快乐的购物者$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedAction::
	.string "{CHN}购物了$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家在商店购物了\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}一定是那种\n"
	.string "天生爱购物的人。$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderTitle::
	.string "{CHN}寻宝训练家$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderAction::
	.string "{CHN}使用了寻宝器$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家使用了寻宝器\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}一定是一个\n"
	.string "爱在地上搜寻隐藏物品的人！$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedTitle::
	.string "{CHN}被雨淋透的训练家$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedAction::
	.string "{CHN}被雨淋了$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家被雨淋了\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}的魅力一定\n"
	.string "连雨水都能吸引！$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexTitle::
	.string "{CHN}宝可梦图鉴爱好者$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexAction::
	.string "{CHN}查看宝可梦图鉴了$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家查看了宝可梦图鉴\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}一定是一个\n"
	.string "爱在宝可梦图鉴里研究宝可梦的人！$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsTitle::
	.string "{CHN}奖章收藏家$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsAction::
	.string "{CHN}获得了奖章$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家获得了奖章\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}一定是一个\n"
	.string "爱收藏奖章的训练家！$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedTitle::
	.string "{CHN}爱跳崖的训练家$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedAction::
	.string "{CHN}跳下了悬崖$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家跳下了悬崖\n"
	.string "{STR_VAR_1}次！\p"
	.string "如果有悬崖可以跳，\n"
	.string "{STR_VAR_3}就忍不住！$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedTitle::
	.string "{CHN}传奇的电视观众$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedAction::
	.string "{CHN}看电视了$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家看了电视\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}一定是一个\n"
	.string "爱看电视的训练家！$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockTitle::
	.string "{CHN}时间观念强的训练家$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockAction::
	.string "{CHN}查看时间了$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家查看了时间\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}一定是一个守时的训练家，\n"
	.string "非常有时间观念。$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryTitle::
	.string "{CHN}宝可梦抽奖大师$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryAction::
	.string "{CHN}赢得了宝可梦抽奖$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家赢得了宝可梦抽奖\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}一定有很多\n"
	.string "可以交换宝可梦的朋友！$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareTitle::
	.string "{CHN}使用寄养屋的训练家$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareAction::
	.string "{CHN}把宝可梦寄养在寄养屋了$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家把宝可梦寄养在\n"
	.string "寄养屋{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}一定是一个\n"
	.string "积极培育宝可梦的人！$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarTitle::
	.string "{CHN}爱缆车的训练家$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarAction::
	.string "{CHN}乘坐了缆车$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家乘坐了缆车\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}一定是一个\n"
	.string "忙上忙下的训练家！$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsTitle::
	.string "{CHN}爱温泉的训练家$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsAction::
	.string "{CHN}泡了温泉$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsStory::
	.string "{CHN}这是一个关于名为\n"
	.string "{STR_VAR_3}的训练家的故事。\p"
	.string "这位训练家泡了温泉\n"
	.string "{STR_VAR_1}次！\p"
	.string "{STR_VAR_3}一定是一个\n"
	.string "皮肤像婴儿般光滑的训练家！$"


MauvilleCity_PokemonCenter_1F_EventScript_Storyteller::
	lock
	faceplayer
	setvar VAR_0x8008, 0
	setvar VAR_0x8009, 0
	setvar VAR_0x800A, 0
	setvar VAR_0x800B, 0
	msgbox MauvilleCity_PokemonCenter_1F_Text_WillYouHearMyTale, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	specialvar VAR_RESULT, StorytellerGetFreeStorySlot
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_KnowNoTales
	message MauvilleCity_PokemonCenter_1F_Text_WhichTaleToTell
	waitmessage
	special StorytellerStoryListMenu
	waitstate
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_CancelStorySelection
	setvar VAR_0x8008, 1
	special Script_StorytellerDisplayStory
	waitmessage
	waitbuttonpress
	specialvar VAR_RESULT, StorytellerUpdateStat
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_AreThereOtherTales
	goto MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale

MauvilleCity_PokemonCenter_1F_EventScript_CancelStorySelection::
	goto MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	end

MauvilleCity_PokemonCenter_1F_EventScript_AreThereOtherTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_CouldThereBeOtherLegends, MSGBOX_DEFAULT
	specialvar VAR_RESULT, HasStorytellerAlreadyRecorded
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_StorytellerEnd
	goto MauvilleCity_PokemonCenter_1F_EventScript_DoYouHaveAnyTales

MauvilleCity_PokemonCenter_1F_EventScript_KnowNoTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_IKnowNoTales, MSGBOX_DEFAULT
MauvilleCity_PokemonCenter_1F_EventScript_DoYouHaveAnyTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_HaveYouAnyLegendaryTales, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	specialvar VAR_RESULT, Script_StorytellerInitializeRandomStat
	goto_if_eq VAR_RESULT, 1, MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale
	msgbox MauvilleCity_PokemonCenter_1F_Text_NotWorthyOfLegend, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDidStatXTimes, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller::
	msgbox MauvilleCity_PokemonCenter_1F_Text_StorytellerFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

/* Unused*/
MauvilleCity_PokemonCenter_1F_EventScript_WaitingForRecordMix::
	msgbox MauvilleCity_PokemonCenter_1F_Text_IWishMorePeopleWereInterested, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_StorytellerEnd::
	release
	end

/* Giddy*/
MauvilleCity_PokemonCenter_1F_Text_HearMyStory:
	.string "{CHN}我是吉迪！\n"
	.string "我有一个精彩的故事要告诉你！\p"
	.string "你想听我的故事吗？$"

MauvilleCity_PokemonCenter_1F_Text_GiddyFeelingTheBlues:
	.string "{CHN}哦……\n"
	.string "你让我感到忧伤……$"

MauvilleCity_PokemonCenter_1F_Text_AlsoIWasThinking:
	.string "{CHN}还有，我在想……$"

MauvilleCity_PokemonCenter_1F_Text_WeShouldChatAgain:
	.string "{CHN}差不多就这些了，我想……\p"
	.string "我们下次再聊吧！\n"
	.string "再见！$"

MauvilleCity_PokemonCenter_1F_EventScript_Giddy::
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_HearMyStory, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_TryTellTale
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineGiddy
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTellTale::
	special GiddyShouldTellAnotherTale
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale::
	special GiddyShouldTellAnotherTale
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_GiddyStartNewTale
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales
	end

MauvilleCity_PokemonCenter_1F_EventScript_GiddyStartNewTale::
	msgbox MauvilleCity_PokemonCenter_1F_Text_AlsoIWasThinking, MSGBOX_DEFAULT
	goto MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale
	end

/* Giddy will continue to tell stories regardless of whether yes or no is selected below.*/
/* Each story there is a 10% chance it will be his last. Otherwise he will stop at 10 stories.*/
MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale::
	special GenerateGiddyLine
	special ShowFieldMessageStringVar4
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineGiddy::
	msgbox MauvilleCity_PokemonCenter_1F_Text_GiddyFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_WeShouldChatAgain, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToHearMySong:
	.string "{CHN}嗨，我是吟游诗人。\n"
	.string "你想听我唱歌吗？$"

MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues1:
	.string "{CHN}哦……\n"
	.string "你让我感到忧伤……$"

MauvilleCity_PokemonCenter_1F_Text_WishICouldPlaySongForOthers:
	.string "{CHN}哦，真是一首动人的歌……\n"
	.string "希望我能演奏给别人听……$"

MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToWriteSomeLyrics:
	.string "{CHN}怎么样？\n"
	.string "你喜欢我的歌吗？\p"
	.string "但是我对手\n"
	.string "歌词不太满意。\p"
	.string "你愿意为我写一些\n"
	.string "新歌词吗？$"

MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues2:
	.string "{CHN}哦……\n"
	.string "你让我感到忧伤……$"

MauvilleCity_PokemonCenter_1F_Text_LetMeSingItForYou:
	.string "{CHN}非常感谢！\n"
	.string "让我为你唱一遍。$"

MauvilleCity_PokemonCenter_1F_Text_ThatHowYouWantedSongToGo:
	.string "{CHN}你的歌就是要这样\n"
	.string "唱的吗？$"

MauvilleCity_PokemonCenter_1F_Text_IllSingThisSongForAWhile:
	.string "{CHN}好的！那就这样定了。\n"
	.string "我近期就唱这首歌了。$"

MauvilleCity_PokemonCenter_1F_Text_TeachWhatsHipAndHappening:
	.string "{CHN}嘿，哟！他们叫我潮人。\n"
	.string "我会教你什么是时髦流行。$"

MauvilleCity_PokemonCenter_1F_Text_IAlreadyTaughtYou:
	.string "{CHN}但是，嘿，我已经教过你\n"
	.string "什么是时髦流行了。\p"
	.string "我想把好消息\n"
	.string "告诉其他人。$"

MauvilleCity_PokemonCenter_1F_Text_IveGotNothingNewToTeach:
	.string "{CHN}但是，嘿，你早就知道\n"
	.string "什么是时髦流行了。\p"
	.string "我已经没有什么新东西\n"
	.string "可以教你了！$"

MauvilleCity_PokemonCenter_1F_Text_HaveYouHeardOfWord:
	.string "{CHN}嘿，你听说过\n"
	.string "“{STR_VAR_1}”吗？\p"
	.string "这是什么意思？嗯……\n"
	.string "去问问你的爸爸或妈妈吧，好吗？$"
