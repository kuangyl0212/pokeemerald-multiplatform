SafariZone_EventScript_OutOfBallsMidBattle::
	setvar VAR_SAFARI_ZONE_STATE, 1
	special ExitSafariMode
	setwarp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 2, 5
	end

SafariZone_EventScript_Exit::
	setvar VAR_SAFARI_ZONE_STATE, 1
	special ExitSafariMode
	warp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 2, 5
	waitstate
	end

SafariZone_EventScript_RetirePrompt::
	lockall
	msgbox SafariZone_Text_WouldYouLikeToExit, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SafariZone_EventScript_Retire
	releaseall
	end

SafariZone_EventScript_Retire::
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_TimesUp::
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_TimesUp
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_OutOfBalls::
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_OutOfBalls
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

EventScript_PokeBlockFeeder::
	lockall
	special GetPokeblockFeederInFront
	goto_if_ne VAR_RESULT, 0xFFFF, SafariZone_EventScript_PokeblockPresent
	msgbox SafariZone_Text_PlacePokeblockOnFeeder, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SafariZone_EventScript_ChoosePokeblock
	releaseall
	end

SafariZone_EventScript_ChoosePokeblock::
	fadescreen FADE_TO_BLACK
	special OpenPokeblockCaseOnFeeder
	waitstate
	goto_if_ne VAR_RESULT, 0xFFFF, SafariZone_EventScript_PokeblockPlaced
#ifdef BUGFIX
	releaseall  @ Only gets called from EventScript_PokeBlockFeeder which uses lockall.
#endif
	end

SafariZone_EventScript_PokeblockPlaced::
	message SafariZone_Text_PokeblockWasPlaced
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_EventScript_PokeblockPresent::
	message SafariZone_Text_PokeblockStillHere
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_Text_WouldYouLikeToExit:
	.string "{CHN}你现在要离开\n"
	.string "野生原野区吗？$"

SafariZone_Text_TimesUp:
	.string "{CHN}叮咚！时间到！\n"
	.string "你的野生原野区游戏结束了。$"

SafariZone_Text_OutOfBalls:
	.string "{CHN}你的野生原野区球用完了。\n"
	.string "你的野生原野区游戏结束了。$"

SafariZone_Text_PlacePokeblockOnFeeder:
	.string "{CHN}你要把方块放在\n"
	.string "方块投放器上吗？$"

SafariZone_Text_PokeblockStillHere:
	.string "{CHN}你之前留下的{STR_VAR_1}\n"
	.string "还在这里。$"

SafariZone_Text_PokeblockWasPlaced:
	.string "{CHN}{STR_VAR_1}被放在了\n"
	.string "方块投放器上。$"

Route121_SafariZoneEntrance_Text_WelcomeToSafariZone:
	.string "{CHN}欢迎来到野生原野区！\p"
	.string "在这里，你可以看到许多\n"
	.string "在丰缘难得一见的宝可梦。\p"
	.string "而且，你能在自然栖息地中\n"
	.string "看到它们野性未驯的状态。\p"
	.string "更重要的是，我们已经向\n"
	.string "宝可梦训练家们敞开了大门。\p"
	.string "我们鼓励你捕捉宝可梦\n"
	.string "带回去！\p"
	.string "进来享受野生原野区吧！$"

Route121_SafariZoneEntrance_Text_WelcomeFirstTime:
	.string "{CHN}欢迎来到野生原野区！\n"
	.string "你是第一次来吗？$"

Route121_SafariZoneEntrance_Text_ComeInAndEnjoy:
	.string "{CHN}进来享受野生原野区吧！$"

Route121_SafariZoneEntrance_Text_FirstTimeInfo:
	.string "{CHN}进入野生原野区时，\n"
	.string "你会带着30个野生原野区球\l"
	.string "用来捕捉宝可梦。\p"
	.string "当你的野生原野区球用完，\n"
	.string "或者走了500步时，\l"
	.string "野生原野区游戏就结束了。\p"
	.string "进来享受野生原野区吧！$"

Route121_SafariZoneEntrance_Text_WouldYouLikeToPlay:
	.string "{CHN}欢迎来到野生原野区！\p"
	.string "只需¥500就能尽情捕捉！\n"
	.string "你要玩野生原野区游戏吗？$"

Route121_SafariZoneEntrance_Text_PlayAnotherTime:
	.string "{CHN}好的。\n"
	.string "下次再来玩吧！$"

Route121_SafariZoneEntrance_Text_NotEnoughMoney:
	.string "{CHN}你的钱不够。\n"
	.string "抱歉。$"

Route121_SafariZoneEntrance_Text_ThatWillBe500Please:
	.string "{CHN}请付¥500。$"

Route121_SafariZoneEntrance_Text_HereAreYourSafariBalls:
	.string "{CHN}这是你的野生原野区球。$"

Route121_SafariZoneEntrance_Text_Received30SafariBalls:
	.string "{CHN}{PLAYER}得到了30个野生原野区球。$"

Route121_SafariZoneEntrance_Text_PleaseEnjoyYourself:
	.string "{CHN}游戏结束时\n"
	.string "我们会通知你。\p"
	.string "在那之前，请尽情享受吧！\n"
	.string "出发去你的野外探险吧！$"

Route121_SafariZoneEntrance_Text_PCIsFull:
	.string "{CHN}打扰一下！\n"
	.string "你的电脑箱子已满。$"

Route121_SafariZoneEntrance_Text_YouNeedPokeblockCase:
	.string "{CHN}打扰一下！\n"
	.string "你好像没有方块盒子。\p"
	.string "如果使用方块，\n"
	.string "你的野生原野区游戏会更加丰收。\p"
	.string "请带着方块盒子再来。\p"
	.string "你可以从凯那市选拔赛会场\n"
	.string "获得方块盒子。$"

SafariZone_South_Text_StillHaveTimeExit:
	.string "{CHN}你还剩下时间。你现在\n"
	.string "要离开野生原野区吗？$"

SafariZone_South_Text_EnjoyTheRestOfYourAdventure:
	.string "{CHN}请享受你接下来的\n"
	.string "野外探险吧！$"

SafariZone_South_Text_ExitEarlyThankYouForPlaying:
	.string "{CHN}好的。\p"
	.string "我会收回你剩下的\n"
	.string "野生原野区球。\p"
	.string "感谢你的参与。\n"
	.string "希望下次再来。$"

SafariZone_South_Text_GoodLuck:
	.string "{CHN}祝你好运！\p"
	.string "如果需要什么，\n"
	.string "请尽管告诉我！$"

SafariZone_South_Text_Boy:
	.string "{CHN}你知道吗？\p"
	.string "如果你把方块放在那个方盒子里，\n"
	.string "宝可梦就会聚集过来。$"

SafariZone_South_Text_Man:
	.string "{CHN}我想继续深入，但我\n"
	.string "忘了带自行车。\p"
	.string "我总觉得稀有的宝可梦\n"
	.string "住在偏远的地区。$"

SafariZone_Southwest_Text_Woman:
	.string "{CHN}有时候，我把方块扔给\n"
	.string "宝可梦，它们却理都不理。\p"
	.string "宝可梦对食物\n"
	.string "也有好恶之分吗？$"

SafariZone_Northwest_Text_Man:
	.string "{CHN}呼……呼……\n"
	.string "我……走到了这里……但是……\p"
	.string "我累坏了……我没有\n"
	.string "力气去抓宝可梦了……$"

SafariZone_North_Text_Fisherman:
	.string "{CHN}我在寻找丰缘\n"
	.string "看不到的水系宝可梦。\p"
	.string "你知道湖在哪里吗？$"

SafariZone_North_Text_Man:
	.string "{CHN}我要在这里抓很多稀有宝可梦，\n"
	.string "然后和朋友们交换！$"

SafariZone_South_Text_Youngster:
	.string "{CHN}我把方块放在了方块投放器上。\n"
	.string "但它好像不见了。\p"
	.string "我猜是宝可梦趁我没注意\n"
	.string "把它吃掉了吧。$"

Route121_SafariZoneEntrance_Text_TrainerTip:
	.string "{CHN}野生原野区训练家小贴士！\p"
	.string "把方块扔向野生宝可梦\n"
	.string "可以降低它们逃跑的几率。$"

SafariZone_Southwest_Text_RestHouseSign:
	.string "{CHN}“缓解你疲惫的双脚。”\n"
	.string "休息小屋$"

SafariZone_RestHouse_Text_Youngster:
	.string "{CHN}我没有方块，但我抓到了\n"
	.string "不少宝可梦。\p"
	.string "你可以通过靠近宝可梦\n"
	.string "来提高捕捉成功率，\l"
	.string "然后再扔野生原野区球。$"

SafariZone_RestHouse_Text_PsychicM:
	.string "{CHN}如果你使用方块，野生宝可梦\n"
	.string "就不会那么快逃跑了。\p"
	.string "但是把方块给\n"
	.string "不容易逃跑的宝可梦没什么用。$"

SafariZone_RestHouse_Text_FatMan:
	.string "{CHN}如果你把方块放在投放器上，\n"
	.string "宝可梦就会被吸引过来。\p"
	.string "我觉得相同性格的宝可梦\n"
	.string "会被特定的方块所吸引。$"

SafariZone_South_Text_AreaOffLimits1:
	.string "{CHN}这片区域还在施工中。\n"
	.string "禁止入内，抱歉！$"

SafariZone_Southeast_Text_ExpansionIsFinished:
	.string "{CHN}野生原野区的扩建工程\n"
	.string "现在已经完成了。\p"
	.string "希望你能在新区玩得开心。$"

SafariZone_South_Text_AreaOffLimits2:
	.string "{CHN}这片区域还在施工中。\n"
	.string "禁止入内，抱歉！$"

SafariZone_Southeast_Text_LittleGirl:
	.string "{CHN}哇！哇！我从没见过\n"
	.string "这些宝可梦！$"

SafariZone_Southeast_Text_FatMan:
	.string "{CHN}这片区域的宝可梦\n"
	.string "我都是第一次见。\p"
	.string "而且我可以抓这些稀有\n"
	.string "宝可梦！太酷了！$"

SafariZone_Southeast_Text_RichBoy:
	.string "{CHN}这里的宝可梦好像\n"
	.string "是从丰缘以外的地方来的。$"

SafariZone_Northeast_Text_Boy:
	.string "{CHN}我只剩几个野生原野区球了。\p"
	.string "我正在苦恼\n"
	.string "该抓什么好呢。$"

SafariZone_Northeast_Text_Woman:
	.string "{CHN}我听说在这里能看到皮卡丘。\n"
	.string "哪里能找到呢？$"

SafariZone_Northeast_Text_Girl:
	.string "{CHN}哎呀，哼！\n"
	.string "我什么都抓不到！\p"
	.string "如果我再抓不到什么，\n"
	.string "入场费就白花了！$"
