RustboroCity_Flat1_2F_MapScripts::
	.byte 0

RustboroCity_Flat1_2F_EventScript_WaldasDad::
	lock
	faceplayer
	specialvar VAR_RESULT, TryBufferWaldaPhrase
	goto_if_eq VAR_RESULT, FALSE, RustboroCity_Flat1_2F_EventScript_WaldasDadFirstPhrase
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Flat1_2F_EventScript_WaldasDadNewPhrase

RustboroCity_Flat1_2F_EventScript_GivePhrase::
	special DoWaldaNamingScreen
	waitstate
	goto_if_eq VAR_0x8004, 1, RustboroCity_Flat1_2F_EventScript_CancelGivePhrase
	goto_if_eq VAR_0x8004, 2, RustboroCity_Flat1_2F_EventScript_CancelGiveFirstPhrase
	specialvar VAR_RESULT, TryGetWallpaperWithWaldaPhrase
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Flat1_2F_EventScript_WaldaLikesPhrase
	goto_if_eq VAR_RESULT, FALSE, RustboroCity_Flat1_2F_EventScript_WaldaDoesntLikePhrase
	end

RustboroCity_Flat1_2F_EventScript_WaldasDadFirstPhrase::
	msgbox RustboroCity_Flat1_2F_Text_HelloDoYouKnowFunnyPhrase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase
	msgbox RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion, MSGBOX_DEFAULT
	goto RustboroCity_Flat1_2F_EventScript_GivePhrase

RustboroCity_Flat1_2F_EventScript_WaldasDadNewPhrase::
	msgbox RustboroCity_Flat1_2F_Text_BeenSayingXDoYouKnowBetterPhrase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase
	msgbox RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion, MSGBOX_DEFAULT
	goto RustboroCity_Flat1_2F_EventScript_GivePhrase

RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase::
	msgbox RustboroCity_Flat1_2F_Text_OhIsThatRight, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_CancelGivePhrase::
	msgbox RustboroCity_Flat1_2F_Text_OhYouDontKnowAny, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_CancelGiveFirstPhrase::
	msgbox RustboroCity_Flat1_2F_Text_ThinkOfMyOwnPhrase, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll2, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldaLikesPhrase::
	msgbox RustboroCity_Flat1_2F_Text_LetsGiveItATry2, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_OhShesLaughing, MSGBOX_DEFAULT
	applymovement LOCALID_WALDAS_DAD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox RustboroCity_Flat1_2F_Text_ThankYouIllGiveYouWallpaper, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldaDoesntLikePhrase::
	msgbox RustboroCity_Flat1_2F_Text_LetsGiveItATry, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda::
	turnobject LOCALID_WALDAS_DAD, DIR_EAST
	return

RustboroCity_Flat1_2F_EventScript_WaldasMom::
	msgbox RustboroCity_Flat1_2F_Text_ComingUpWithMealsIsHard, MSGBOX_NPC
	end

RustboroCity_Flat1_2F_EventScript_PokeDoll::
	msgbox RustboroCity_Flat1_2F_Text_ItsAPokemonPlushDoll, MSGBOX_SIGN
	end

RustboroCity_Flat1_2F_Text_ComingUpWithMealsIsHard:
	.string "{CHN}哦，每天真是辛苦…\p"
	.string "什么辛苦？\n"
	.string "你还用问吗？\p"
	.string "就是每天要想做什么菜\n"
	.string "给家人吃.\p"
	.string "每天想菜单\n"
	.string "真不是件容易的事.$"

RustboroCity_Flat1_2F_Text_HelloDoYouKnowFunnyPhrase:
	.string "{CHN}哦，你好！\n"
	.string "欢迎来到佩珀家.\p"
	.string "我有个问题想问你.\n"
	.string "你带过孩子吗？\p"
	.string "你看，我是新手爸爸，所以养育\n"
	.string "孩子对我来说是全新的体验.\p"
	.string "而我有个问题. 我的女儿\n"
	.string "小娃笑得不够多.\p"
	.string "我想如果我说些有趣的事，\n"
	.string "她就会笑的.\p"
	.string "你知道什么有趣的词语\n"
	.string "或短语可以告诉我吗?$"

RustboroCity_Flat1_2F_Text_BeenSayingXDoYouKnowBetterPhrase:
	.string "{CHN}我最近一直在说“{STR_VAR_1}”\n"
	.string "来逗她.\p"
	.string "你知道有没有更好的词\n"
	.string "或短语可以用的吗?$"

RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion:
	.string "{CHN}哦，太好了.\n"
	.string "那么，让我们听听你的建议吧.$"

RustboroCity_Flat1_2F_Text_OhIsThatRight:
	.string "{CHN}哦，是吗？\p"
	.string "好吧，如果你有什么好的\n"
	.string "建议，我洗耳恭听.$"

RustboroCity_Flat1_2F_Text_LetsGiveItATry2:
	.string "{CHN}啊，我明白了.\n"
	.string "那我们就试一试吧，好吗?$"

RustboroCity_Flat1_2F_Text_OhShesLaughing:
	.string "{CHN}{STR_VAR_1}.\n"
	.string "{STR_VAR_1}.\p"
	.string "哦，对了！她笑了！\n"
	.string "哦，我和她一样高兴！$"

RustboroCity_Flat1_2F_Text_LetsGiveItATry:
	.string "{CHN}啊，我明白了.\n"
	.string "那我们就试一试吧，好吗?$"

RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll:
	.string "{CHN}{STR_VAR_1}.\n"
	.string "{STR_VAR_1}.\p"
	.string "嗯…她完全没笑.\n"
	.string "也许小娃是个严肃的孩子…$"

RustboroCity_Flat1_2F_Text_ThinkOfMyOwnPhrase:
	.string "{CHN}哦，你不知道什么好词啊.\n"
	.string "那我得自己想了.\p"
	.string "嗯…\n"
	.string "“{STR_VAR_1}”怎么样？\l"
	.string "让我们看看行不行.$"

RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll2:
	.string "{CHN}{STR_VAR_1}.\n"
	.string "{STR_VAR_1}.\p"
	.string "嗯…她完全没笑.\n"
	.string "也许小娃是个严肃的孩子…$"

RustboroCity_Flat1_2F_Text_OhYouDontKnowAny:
	.string "{CHN}哦，你不知道什么好词啊.\n"
	.string "我想我就用之前\l"
	.string "说过的来逗她吧.\p"
	.string "不管怎样，如果你有什么好建议，\n"
	.string "请务必告诉我，好吗?$"

RustboroCity_Flat1_2F_Text_ThankYouIllGiveYouWallpaper:
	.string "{CHN}谢谢你！\p"
	.string "多亏了你，我心爱的小娃\n"
	.string "对我笑了！\p"
	.string "其实，我看起来可能没什么\n"
	.string "特别，但我是得文\l"
	.string "公司顶尖的研究员之一.\p"
	.string "所以，我能不能为你做点什么\n"
	.string "作为回报呢？\p"
	.string "对了，我给电脑里宝可梦\n"
	.string "存放系统的箱子\l"
	.string "添加一些新的壁纸图案.\p"
	.string "在壁纸图案菜单中，\n"
	.string "选择“朋友.”\p"
	.string "这样你就可以使用新的\n"
	.string "壁纸图案了.$"

RustboroCity_Flat1_2F_Text_ItsAPokemonPlushDoll:
	.string "{CHN}是宝可梦毛绒玩偶！$"

