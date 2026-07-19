@ All the LOCALID constants used in this file are essentially redundant.
@ They're all used to have the NPC the player talked to turn back so they're facing
@ their original direction (because they're watching/participating in the contests).
@ They could all be substituted for VAR_LAST_TALKED.
LilycoveCity_ContestHall_MapScripts::
	.byte 0

LilycoveCity_ContestHall_EventScript_Boy1::
	msgbox LilycoveCity_ContestHall_Text_TodayWonSmartnessContest, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Boy2::
	msgbox LilycoveCity_ContestHall_Text_EnteredBunchOfContests, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Girl::
	msgbox LilycoveCity_ContestHall_Text_ManWhoWonEarlierHadPokeblocks, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Sailor::
	msgbox LilycoveCity_ContestHall_Text_IsntThisPlaceHumongous, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_SmartContestMC::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_GiveItBestSmartAppeal, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestJudge::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AreYouEnjoyingThisContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EnteredWrongContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_RaisedMonToBeSmart, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_IfMonPullsSmartMoveNext, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_DontAppreciateCuteLeechLife, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience1::
	msgbox LilycoveCity_ContestHall_Text_YoureBeautifulGrandpa, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AllSeemToUseDifferentMoves, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PokemonSmarterThanTrainers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_StillLoveSmartnessContests, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestMC::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AreYouEnteringBeautyContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestJudge::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EveryPokemonPristineBeauty, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EyesWillBeGluedToMyBeauty, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_OverdidGrooming, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_JudgeWontSeeAuroraBeam, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PokemonLooksLikeYoungerMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_WinBeautyContestMakesMeHappy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_GanderAtAllThosePrettyPokemon, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_CantWinOnBeautyAlone, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestMC::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_InTheMiddleOfContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestJudge::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_SuchCharmingCuteAppeals, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_MyAzurillWasDistracted, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_NeverWonBattleButContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PetalDanceIsMarvel, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_MyMonAppealSoMuchCuter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience1::
	lockall
	applymovement LOCALID_CUTE_AUDIENCE_1, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_ContestHall_Text_MyChildIsInContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	delay 25
	msgbox LilycoveCity_ContestHall_Text_ComeOnDear, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_WantCuteMonOfMyOwn, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_ThatGirlThereIsCutest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyStageSign::
	msgbox LilycoveCity_ContestHall_Text_BeautyContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_CuteStageSign::
	msgbox LilycoveCity_ContestHall_Text_CuteContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_SmartStageSign::
	msgbox LilycoveCity_ContestHall_Text_SmartContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_Text_TodayWonSmartnessContest:
	.string "{CHN}这只宝可梦以前在这里\n"
	.string "赢得过美丽选拔赛。\p"
	.string "你猜怎么着？今天我让它\n"
	.string "赢得了聪明选拔赛！\p"
	.string "我的本事连我自己都害怕…$"

LilycoveCity_ContestHall_Text_EnteredBunchOfContests:
	.string "{CHN}我参加了一堆选拔赛，\n"
	.string "所以正在研究怎么回事。\p"
	.string "如果是帅气选拔赛，\n"
	.string "帅气的招式作为演出会受欢迎。\p"
	.string "不过聪明招式和可爱招式\n"
	.string "就不太行了，举个例子。$"

LilycoveCity_ContestHall_Text_ManWhoWonEarlierHadPokeblocks:
	.string "{CHN}刚才获胜的那个小伙子\n"
	.string "有好多不同种类的{POKEBLOCK}。\p"
	.string "如果你也有那么多的话，\n"
	.string "是不是也能赢呢？$"

LilycoveCity_ContestHall_Text_IsntThisPlaceHumongous:
	.string "{CHN}哇，这地方也太大了！\p"
	.string "空气中的紧张感…\n"
	.string "这可不像乡下的选拔赛会堂。$"

LilycoveCity_ContestHall_Text_GiveItBestSmartAppeal:
	.string "{CHN}主持人：好了，聪明的宝可梦和\n"
	.string "训练家们，准备好了吗？！\p"
	.string "拿出最好的表现！\n"
	.string "开始演出吧！$"

LilycoveCity_ContestHall_Text_AreYouEnjoyingThisContest:
	.string "{CHN}裁判：你享受这场选拔赛吗？\p"
	.string "带上三个朋友一起来，\n"
	.string "你们全部人都能参加选拔赛！$"

LilycoveCity_ContestHall_Text_EnteredWrongContest:
	.string "{CHN}哎呀呀呀…\n"
	.string "我参加错了选拔赛。\p"
	.string "我让这只强壮的宝可梦参加了\n"
	.string "聪明选拔赛…\p"
	.string "拜托，用看起来聪明的碎岩\n"
	.string "让他们刮目相看吧。$"

LilycoveCity_ContestHall_Text_RaisedMonToBeSmart:
	.string "{CHN}我花了许多年时间，用尽了\n"
	.string "所有的智慧，把这只宝可梦\l"
	.string "培养成聪明的样子。\p"
	.string "它可不会轻易输给某个\n"
	.string "小毛孩的宝可梦。\p"
	.string "老伴，你看到了吗？$"

LilycoveCity_ContestHall_Text_IfMonPullsSmartMoveNext:
	.string "{CHN}就是这个！\p"
	.string "如果我的宝可梦接下来使出聪明的招式，\n"
	.string "观众们的兴奋度就要达到顶点了！$"

LilycoveCity_ContestHall_Text_DontAppreciateCuteLeechLife:
	.string "{CHN}哎呀，不行！\p"
	.string "我的宝贝超音蝠的吸血太\n"
	.string "可爱了，我一直在用！\p"
	.string "可是这些坏人们\n"
	.string "一点都不懂得欣赏！$"

LilycoveCity_ContestHall_Text_YoureBeautifulGrandpa:
	.string "{CHN}哇啊！爷爷你好帅！$"

LilycoveCity_ContestHall_Text_AllSeemToUseDifferentMoves:
	.string "{CHN}即使训练家们让相同的\n"
	.string "宝可梦参加，他们似乎都使用\l"
	.string "不同的招式来演出。\p"
	.string "这就跟人对战时\n"
	.string "有不同风格是一样的。$"

LilycoveCity_ContestHall_Text_PokemonSmarterThanTrainers:
	.string "{CHN}我觉得宝可梦看起来比\n"
	.string "它们的训练家更聪明。聪明多了。$"

LilycoveCity_ContestHall_Text_StillLoveSmartnessContests:
	.string "{CHN}说到底，我还是喜欢\n"
	.string "聪明选拔赛。\p"
	.string "那充满知性的绿色…\n"
	.string "真是太…太…酷了。$"

LilycoveCity_ContestHall_Text_AreYouEnteringBeautyContest:
	.string "{CHN}主持人：你也要参加\n"
	.string "美丽选拔赛吗？加油！$"

LilycoveCity_ContestHall_Text_EveryPokemonPristineBeauty:
	.string "{CHN}裁判：啊，这里的每只宝可梦\n"
	.string "都是纯洁美丽的典范！\p"
	.string "哎呀，我差点忘了给它们打分！$"

LilycoveCity_ContestHall_Text_EyesWillBeGluedToMyBeauty:
	.string "{CHN}这么美丽的宝可梦…\n"
	.string "再没有第二只了。\p"
	.string "所有人的目光都会\n"
	.string "被我的美丽所吸引。$"

LilycoveCity_ContestHall_Text_OverdidGrooming:
	.string "{CHN}哇啊啊！\p"
	.string "我为了这场选拔赛\n"
	.string "仔细地刷洗打扮了我的宝可梦…\p"
	.string "可是我做过头了…\n"
	.string "我的宝可梦的毛都变得乱糟糟的…\p"
	.string "我该怎么办？$"

LilycoveCity_ContestHall_Text_JudgeWontSeeAuroraBeam:
	.string "{CHN}这招极光束太耀眼了，\n"
	.string "裁判都看不清了。\p"
	.string "呃，等一下…\n"
	.string "那就没意义了啊！$"

LilycoveCity_ContestHall_Text_PokemonLooksLikeYoungerMe:
	.string "{CHN}这只漂亮的宝可梦\n"
	.string "就像我年轻时的样子。\p"
	.string "我刚说完，我丈夫\n"
	.string "就把嘴里喝的咖啡喷了出来。\p"
	.string "我说了什么好笑的吗？$"

LilycoveCity_ContestHall_Text_WinBeautyContestMakesMeHappy:
	.string "{CHN}你知道吗，如果在美丽\n"
	.string "选拔赛中获胜，我确实会\l"
	.string "很高兴。比平时更开心就是了。$"

LilycoveCity_ContestHall_Text_GanderAtAllThosePrettyPokemon:
	.string "{CHN}哇哈哈哈哈！\p"
	.string "你瞧瞧那些\n"
	.string "漂亮的宝可梦！\l"
	.string "我就爱这种花哨劲儿！$"

LilycoveCity_ContestHall_Text_CantWinOnBeautyAlone:
	.string "{CHN}你不能光靠美丽\n"
	.string "就总是获胜。\p"
	.string "你得好好打理你的宝可梦，\n"
	.string "让它像我的一样光滑亮泽。$"

LilycoveCity_ContestHall_Text_InTheMiddleOfContest:
	.string "{CHN}主持人：哎呀！你好！\n"
	.string "我们正在进行选拔赛！\p"
	.string "请到我们的接待柜台\n"
	.string "登记入场，好吗？$"

LilycoveCity_ContestHall_Text_SuchCharmingCuteAppeals:
	.string "{CHN}裁判：哦，多么迷人可爱的\n"
	.string "演出啊！\p"
	.string "天哪！多么\n"
	.string "完美的玩水演出啊！$"

LilycoveCity_ContestHall_Text_MyAzurillWasDistracted:
	.string "{CHN}糟糕…我可爱的露力丽\n"
	.string "被另一只宝可梦分散了注意力。$"

LilycoveCity_ContestHall_Text_NeverWonBattleButContest:
	.string "{CHN}我的宝可梦从来没在对战中赢过，\n"
	.string "但参加选拔赛可就不得了了！$"

LilycoveCity_ContestHall_Text_PetalDanceIsMarvel:
	.string "{CHN}我的宝可梦的花瓣舞是\n"
	.string "优雅的奇迹。\p"
	.string "我不会让任何人打扰\n"
	.string "它的表演。$"

LilycoveCity_ContestHall_Text_MyMonAppealSoMuchCuter:
	.string "{CHN}大家的宝可梦都很可爱。\p"
	.string "不过，如果我的宝可梦进行\n"
	.string "可爱的演出…\p"
	.string "我确信它会比其他\n"
	.string "宝可梦可爱得多。$"

LilycoveCity_ContestHall_Text_MyChildIsInContest:
	.string "{CHN}我的孩子正在参加这场选拔赛。$"

LilycoveCity_ContestHall_Text_ComeOnDear:
	.string "{CHN}加油，宝贝。冲啊！\n"
	.string "你的宝可梦是最棒的！$"

LilycoveCity_ContestHall_Text_ThatGirlThereIsCutest:
	.string "{CHN}我觉得那边那个女孩\n"
	.string "是所有人里最可爱的。\p"
	.string "什么？他们不是\n"
	.string "按长相评判宝可梦的吗？$"

LilycoveCity_ContestHall_Text_WantCuteMonOfMyOwn:
	.string "{CHN}哦哦，看到这么多可爱的宝可梦，\n"
	.string "让我也想自己拥有一只！\p"
	.string "我要去抓一些！$"

LilycoveCity_ContestHall_Text_BeautyContestStage:
	.string "{CHN}美丽选拔赛舞台\n"
	.string "被美丽的宝可梦所倾倒！$"

LilycoveCity_ContestHall_Text_CuteContestStage:
	.string "{CHN}可爱选拔赛舞台\n"
	.string "被可爱的宝可梦所迷住！$"

LilycoveCity_ContestHall_Text_SmartContestStage:
	.string "{CHN}聪明选拔赛舞台\n"
	.string "被聪明的宝可梦所折服！$"
