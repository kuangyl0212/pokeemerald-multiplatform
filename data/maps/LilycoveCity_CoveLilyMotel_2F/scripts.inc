LilycoveCity_CoveLilyMotel_2F_MapScripts::
	.byte 0

LilycoveCity_CoveLilyMotel_2F_EventScript_GameDesigner::
	lock
	faceplayer
	call_if_unset FLAG_TEMP_2, LilycoveCity_CoveLilyMotel_2F_EventScript_ShowMeCompletedDex
	call_if_set FLAG_TEMP_2, LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma
	specialvar VAR_RESULT, HasAllHoennMons
	goto_if_eq VAR_RESULT, TRUE, LilycoveCity_CoveLilyMotel_2F_EventScript_AllHoennMonsFanfare
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_ShowMeCompletedDex::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ShowMeCompletedDex, MSGBOX_DEFAULT
	return

LilycoveCity_CoveLilyMotel_2F_EventScript_AllHoennMonsFanfare::
	setflag FLAG_TEMP_2
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	goto LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma::
	message LilycoveCity_CoveLilyMotel_2F_Text_FilledPokedexGiveYouThis
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	special Special_ShowDiploma
	waitstate
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Programmer::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ImTheProgrammer, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_GraphicArtist::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ImTheGraphicArtist, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_FatMan::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_GirlsAreCute, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Woman::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_SeaBreezeTicklesHeart, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_GameBoyKid::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_NeverLeaveWithoutGameBoy, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Scott::
	lock
	faceplayer
	goto_if_set FLAG_MET_SCOTT_IN_LILYCOVE, LilycoveCity_CoveLilyMotel_2F_EventScript_MetScott
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_SnoozingPreferBattles, MSGBOX_DEFAULT
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_IN_LILYCOVE
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_MetScott::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ContestsDoTakeStrategy, MSGBOX_DEFAULT
	release
	end

LilycoveCity_CoveLilyMotel_2F_Text_ShowMeCompletedDex:
	.string "{CHN}我是游戏设计师。\p"
	.string "哦，是吗？\n"
	.string "你正在做宝可梦图鉴？\p"
	.string "完成它确实很辛苦，\n"
	.string "但不要放弃。\p"
	.string "如果你完成了，请来\n"
	.string "给我看看。$"

LilycoveCity_CoveLilyMotel_2F_Text_FilledPokedexGiveYouThis:
	.string "{CHN}哇！太厉害了！\n"
	.string "嗯，真是太厉害了！\p"
	.string "这本宝可梦图鉴已经完全填满了！\n"
	.string "你一定很喜欢宝可梦！\p"
	.string "我太感动了！\p"
	.string "让我送你点什么\n"
	.string "来表彰你的功绩！$"

LilycoveCity_CoveLilyMotel_2F_Text_ImTheProgrammer:
	.string "{CHN}我？你在跟我说话？\n"
	.string "我是程序员。\p"
	.string "不知道这里的拉霸机\n"
	.string "是怎么样的。$"

LilycoveCity_CoveLilyMotel_2F_Text_ImTheGraphicArtist:
	.string "{CHN}我是图形设计师！丰缘的\n"
	.string "宝可梦是不是很有趣？$"

LilycoveCity_CoveLilyMotel_2F_Text_GirlsAreCute:
	.string "{CHN}那些玩水家小女孩，真可爱，\n"
	.string "对吧？\p"
	.string "和可爱的玩水家对战…\p"
	.string "哇，太棒了！\p"
	.string "还有双胞胎！是不是很可爱？\n"
	.string "和双胞胎进行2对2对战…\p"
	.string "哇，好玩得不得了！$"

LilycoveCity_CoveLilyMotel_2F_Text_SeaBreezeTicklesHeart:
	.string "{CHN}海风轻抚着我的心。\n"
	.string "在这里感觉真舒服！$"

LilycoveCity_CoveLilyMotel_2F_Text_NeverLeaveWithoutGameBoy:
	.string "{CHN}你永远不知道何时何地\n"
	.string "会有人向你发起挑战。\p"
	.string "这就是为什么我出门从不\n"
	.string "落下我的GAME BOY ADVANCE。$"

LilycoveCity_CoveLilyMotel_2F_Text_SnoozingPreferBattles:
	.string "{CHN}水木：… … … … …\n"
	.string "… … … … … 呼…\p"
	.string "… … … … … 哎？！\n"
	.string "哦，对不起，对不起！我打瞌睡了！\p"
	.string "我来考察这个宝可梦\n"
	.string "选拔赛什么的。\p"
	.string "我不得不承认，看起来确实挺\n"
	.string "有趣的，但是…\p"
	.string "算我是个老古板吧——我更喜欢\n"
	.string "对战和强硬的训练家。\p"
	.string "不过那只是我。\p"
	.string "{PLAYER}{KUN}，希望你能享受所有的东西，\n"
	.string "比如道馆、选拔赛、对战帐篷，\l"
	.string "全部都来一遍！$"

LilycoveCity_CoveLilyMotel_2F_Text_ContestsDoTakeStrategy:
	.string "{CHN}水木：我认为在选拔赛中获胜\n"
	.string "确实需要策略。\p"
	.string "制定选拔赛策略是成为\n"
	.string "更厉害的训练家的一种方式，我觉得。$"
