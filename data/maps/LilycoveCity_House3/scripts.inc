LilycoveCity_House3_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_House3_OnTransition
	.byte 0

LilycoveCity_House3_OnTransition:
	random 4
	copyvar VAR_TEMP_1, VAR_RESULT
	end

LilycoveCity_House3_EventScript_PokefanF::
	lock
	faceplayer
	msgbox LilycoveCity_House3_Text_LearnFromMasterOfPokeblocks, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LilycoveCity_House3_EventScript_DeclinePokeblockLearn
	msgbox LilycoveCity_House3_Text_ExplainPokeblocks, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_DeclinePokeblockLearn::
	msgbox LilycoveCity_House3_Text_OhAreYouSure, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_Man::
	lock
	faceplayer
	msgbox LilycoveCity_House3_Text_HappyToHaveQuadruplets, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_GameBoyKid1::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid2::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid3::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid4::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_WereDoingMultiBattle::
	msgbox LilycoveCity_House3_Text_GoingToWinMultiBattles, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereMixingRecords::
	msgbox LilycoveCity_House3_Text_LikeMixingAtRecordCorner, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereBlendingBerries::
	msgbox LilycoveCity_House3_Text_MakePokeblocksWithBerryBlender, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereDoingContest::
	msgbox LilycoveCity_House3_Text_GoingToEnterContest, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_Text_LearnFromMasterOfPokeblocks:
	.string "{CHN}哎呀呀！你一个人在旅行吗？\n"
	.string "可你还这么小！真了不起！\p"
	.string "我的孩子们一定能从你身上\n"
	.string "学到一两手呢！\p"
	.string "我吗？我可是{POKEBLOCK}的大师哦。\p"
	.string "只要我稍微认真一点，\n"
	.string "就能做出超棒的{POKEBLOCK}。\p"
	.string "想不想跟着我这{POKEBLOCK}大师\n"
	.string "学两手呢？$"

LilycoveCity_House3_Text_OhAreYouSure:
	.string "{CHN}哦？你确定吗？\p"
	.string "你不能什么事都想着\n"
	.string "自己一个人扛呀，孩子！$"

LilycoveCity_House3_Text_ExplainPokeblocks:
	.string "{CHN}哎呀，真乖！你真是个聪明的孩子！\n"
	.string "话有点长，你要认真听好哦！\p"
	.string "准备好了吗？\p"
	.string "你看看{POKEBLOCK}，就会发现\n"
	.string "它有触感度的评级。\p"
	.string "触感度越低，\n"
	.string "品质就越好。可别忘了哦！\p"
	.string "好的{POKEBLOCK}触感度低，\n"
	.string "等级却很高。\p"
	.string "宝可梦也能吃下更多\n"
	.string "优质的{POKEBLOCK}。\p"
	.string "还有一点很重要。\p"
	.string "想做出顺滑的{POKEBLOCK}，\n"
	.string "就要用不同种类的树果。\p"
	.string "别小气——树果的种类\n"
	.string "会影响{POKEBLOCK}的顺滑度。\p"
	.string "还有一件事。\p"
	.string "一起搅拌树果的人越多，\n"
	.string "做出来的{POKEBLOCK}就越顺滑。\p"
	.string "所以要和其他人多交流，\n"
	.string "一起做{POKEBLOCK}。\p"
	.string "要做好的{POKEBLOCK}，\n"
	.string "知道这些就够了。\p"
	.string "如果每个人都有心爱的宝可梦，\n"
	.string "顺滑的{POKEBLOCK}，还有温暖的家，\l"
	.string "这个世界一定会更美好。\p"
	.string "别放弃，孩子！$"

LilycoveCity_House3_Text_HappyToHaveQuadruplets:
	.string "{CHN}妻子生下四胞胎的时候，\n"
	.string "我真是吓了一跳。\p"
	.string "不过现在看着他们一起玩耍，\n"
	.string "我就觉得很幸福。$"

LilycoveCity_House3_Text_GoingToWinMultiBattles:
	.string "{CHN}我们在打多人对战，\n"
	.string "但我知道我一定会赢。$"

LilycoveCity_House3_Text_LikeMixingAtRecordCorner:
	.string "{CHN}我们喜欢在记录角落\n"
	.string "混合各种东西。\p"
	.string "可是混的到底是什么呢？$"

LilycoveCity_House3_Text_MakePokeblocksWithBerryBlender:
	.string "{CHN}我们要用树果搅拌机，\n"
	.string "做出超棒的{POKEBLOCK}！$"

LilycoveCity_House3_Text_GoingToEnterContest:
	.string "{CHN}我想炫耀我家宝可梦有多厉害，\n"
	.string "所以我们要一起去参加\l"
	.string "选拔赛。$"
