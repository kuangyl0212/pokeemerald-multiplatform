SlateportCity_OceanicMuseum_1F_MapScripts::
	.byte 0

SlateportCity_OceanicMuseum_1F_EventScript_EntranceAttendant::
	msgbox SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFeeLeft::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFeeRight::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee::
	showmoneybox 0, 0
	msgbox SlateportCity_OceanicMuseum_1F_Text_WouldYouLikeToEnter, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_OceanicMuseum_1F_EventScript_CheckMoneyForFee
	closemessage
	hidemoneybox
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_CheckMoneyForFee::
	checkmoney 50
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_OceanicMuseum_1F_EventScript_NotEnoughMoney
	playse SE_SHOP
	removemoney 50
	updatemoneybox
	msgbox SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 1
	hidemoneybox
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_NotEnoughMoney::
	goto_if_unset FLAG_DELIVERED_DEVON_GOODS, SlateportCity_OceanicMuseum_1F_EventScript_AllowEntranceAnyway
	msgbox SlateportCity_OceanicMuseum_1F_Text_NotEnoughMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_AllowEntranceAnyway::
	msgbox SlateportCity_OceanicMuseum_1F_Text_CatchUpWithYourGroup, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 1
	hidemoneybox
	releaseall
	end

SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter:
	walk_down
	step_end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt1::
	msgbox SlateportCity_OceanicMuseum_1F_Text_AquaExistForGoodOfAll, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt2::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OurBossIsntHere, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt3::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WouldStuffHereMakeMeRich, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt4::
	msgbox SlateportCity_OceanicMuseum_1F_Text_CanLearnForNefariousDeeds, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt5::
	msgbox SlateportCity_OceanicMuseum_1F_Text_RustboroBungled, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt6::
	msgbox SlateportCity_OceanicMuseum_1F_Text_DidntHaveMoney, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_WhirlpoolExperiment::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WhirlpoolExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_WaterfallExperiment::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WaterfallExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanSoilDisplay::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanSoilDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_BeachSandDisplay::
	msgbox SlateportCity_OceanicMuseum_1F_Text_BeachSandDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact1::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact1, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact2::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact2, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact3::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact3, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_FossilDisplay::
	msgbox SlateportCity_OceanicMuseum_1F_Text_FossilDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_DepthMeasuringMachine::
	msgbox SlateportCity_OceanicMuseum_1F_Text_DepthMeasuringMachine, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron1::
	msgbox SlateportCity_OceanicMuseum_1F_Text_LearnAboutSeaForBattling, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron2::
	msgbox SlateportCity_OceanicMuseum_1F_Text_SternIsRoleModel, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron3::
	msgbox SlateportCity_OceanicMuseum_1F_Text_MustBePokemonWeDontKnow, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron4::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WantSeaPokemon, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGrunt::
	lock
	faceplayer
	delay 8
	playse SE_PIN
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, Common_Movement_Delay48
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_1F_Text_RememberMeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_THIEF
	goto_if_eq VAR_RESULT, 0, SlateportCity_OceanicMuseum_1F_EventScript_NoRoomForThief
	setflag FLAG_RECEIVED_TM_THIEF
	msgbox SlateportCity_OceanicMuseum_1F_Text_HopeINeverSeeYouAgain, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_FACING, DIR_NORTH, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitNorth
	goto_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitSouth
	goto_if_eq VAR_FACING, DIR_WEST, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast
	goto_if_eq VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitNorth::
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitNorth
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExitNorth
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitSouth::
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast::
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitWestEast
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited::
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_FAMILIAR_AQUA_GRUNT
	playse SE_EXIT
	removeobject LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT
	release
	end

SlateportCity_OceanicMuseum_1F_EventScript_NoRoomForThief::
	msgbox SlateportCity_OceanicMuseum_1F_Text_YouHaveToTakeThis, MSGBOX_DEFAULT
	release
	end

SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitNorth:
	delay_16
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitWestEast:
	delay_16
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit:
	face_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	delay_8
	step_end

SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExitNorth:
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	delay_8
	step_end

SlateportCity_OceanicMuseum_1F_Text_WouldYouLikeToEnter:
	.string "{CHN}欢迎来到海洋博物馆。\p"
	.string "入场费是¥50。\n"
	.string "你要进来吗？$"

SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself:
	.string "{CHN}请慢慢参观。$"

SlateportCity_OceanicMuseum_1F_Text_NotEnoughMoney:
	.string "{CHN}哦？很抱歉，你身上的钱\n"
	.string "好像不够。$"

SlateportCity_OceanicMuseum_1F_Text_CatchUpWithYourGroup:
	.string "{CHN}哦？你是和刚才进去的\n"
	.string "那群人一起的吗？\p"
	.string "只有你一个人迟到了。\n"
	.string "你最好快去追上他们！$"

SlateportCity_OceanicMuseum_1F_Text_AquaExistForGoodOfAll:
	.string "{CHN}我们水舰队是为了\n"
	.string "所有人的利益而存在的！$"

SlateportCity_OceanicMuseum_1F_Text_OurBossIsntHere:
	.string "{CHN}我们被告知要在这里集合，\n"
	.string "所以我们就来了，但是…\p"
	.string "我们的老大，核心人物，不在这里。$"

SlateportCity_OceanicMuseum_1F_Text_WouldStuffHereMakeMeRich:
	.string "{CHN}如果我偷了这里的东西，\n"
	.string "会不会变得很有钱？$"

SlateportCity_OceanicMuseum_1F_Text_CanLearnForNefariousDeeds:
	.string "{CHN}我在这里学到的东西，可以用在\n"
	.string "坏事上…$"

SlateportCity_OceanicMuseum_1F_Text_RustboroBungled:
	.string "{CHN}如果不是我们在橙华市\n"
	.string "搞砸了，我们也不会在这里！$"

SlateportCity_OceanicMuseum_1F_Text_DidntHaveMoney:
	.string "{CHN}我没有¥50，所以花了很长\n"
	.string "时间才从接待员那里混过来。$"

SlateportCity_OceanicMuseum_1F_Text_LearnAboutSeaForBattling:
	.string "{CHN}我想学习关于大海的知识，\n"
	.string "并把它用在战斗中。$"

SlateportCity_OceanicMuseum_1F_Text_SternIsRoleModel:
	.string "{CHN}我一看到大海\n"
	.string "就浑身起鸡皮疙瘩！\p"
	.string "对我来说，帅哥船长是\n"
	.string "第一榜样！$"

SlateportCity_OceanicMuseum_1F_Text_MustBePokemonWeDontKnow:
	.string "{CHN}大海无边无际，\n"
	.string "深不可测…\p"
	.string "一定还有很多我们\n"
	.string "不知道的宝可梦。$"

SlateportCity_OceanicMuseum_1F_Text_WantSeaPokemon:
	.string "{CHN}我想要一只海里的宝可梦。\p"
	.string "我觉得抱起来一定\n"
	.string "又凉又舒服。$"

SlateportCity_OceanicMuseum_1F_Text_RememberMeTakeThis:
	.string "{CHN}哎呀！\n"
	.string "你怎么会在这里？\p"
	.string "我？我是之前被你揍过的\n"
	.string "水舰队成员，记得吗？\l"
	.string "在卡绿隧道里？\p"
	.string "来，拿着这个！\n"
	.string "你一定要原谅我！$"

SlateportCity_OceanicMuseum_1F_Text_HopeINeverSeeYouAgain:
	.string "{CHN}那个招式学习器，比起我\n"
	.string "它更适合你。\p"
	.string "希望以后再也不要见到你了！\n"
	.string "哇哈哈哈！$"

SlateportCity_OceanicMuseum_1F_Text_YouHaveToTakeThis:
	.string "{CHN}哎呀，拜托！\n"
	.string "你一定要收下这个，然后放我走！$"

SlateportCity_OceanicMuseum_1F_Text_WhirlpoolExperiment:
	.string "{CHN}玻璃容器中，蓝色的液体\n"
	.string "正在旋转。\p"
	.string "“这是利用风力人工制造\n"
	.string "漩涡的实验。”$"

SlateportCity_OceanicMuseum_1F_Text_WaterfallExperiment:
	.string "{CHN}红色的小球在玻璃容器里\n"
	.string "上下浮动着。\p"
	.string "“这是利用小球的浮力\n"
	.string "模拟瀑布的实验。”$"

SlateportCity_OceanicMuseum_1F_Text_OceanSoilDisplay:
	.string "{CHN}这是来自海底的\n"
	.string "土壤样本。\p"
	.string "“经过漫长的岁月，生物的\n"
	.string "遗骸沉入海底，\l"
	.string "形成了沉积层。\p"
	.string "“通过分析这些地层，\n"
	.string "远古的过去得以揭晓。”$"

SlateportCity_OceanicMuseum_1F_Text_BeachSandDisplay:
	.string "{CHN}这是海滩沙子的样本。\p"
	.string "“山上的石头被河水\n"
	.string "冲刷下来，在过程中\l"
	.string "被磨损和粉碎。\p"
	.string "“它们最终变成细小的颗粒，\n"
	.string "成为海滩上的沙子。”$"

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact1:
	.string "{CHN}“海洋小知识1\n"
	.string "海水为什么是蓝色的？\p"
	.string "“光是由多种颜色组成的。\p"
	.string "“当光穿过水时，\n"
	.string "大多数颜色的光会失去色彩。\p"
	.string "“但是，蓝光保留了它的颜色，\n"
	.string "使大海看起来是蓝色的。”$"

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact2:
	.string "{CHN}“海洋小知识2\n"
	.string "大海为什么是咸的？\p"
	.string "“海水中含有溶解的盐，\n"
	.string "以钠离子和氯离子的形式存在。\p"
	.string "“这些离子从岩石中渗出，\n"
	.string "被雨水带入大海。\p"
	.string "“溶解盐的浓度\n"
	.string "使大海变咸。”$"

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact3:
	.string "{CHN}“海洋小知识3\n"
	.string "大海和陆地，哪个更大？\p"
	.string "“大海覆盖了地球约70%\n"
	.string "的面积，其余是陆地。\p"
	.string "“因此，大海的面积\n"
	.string "是陆地的两倍多。”$"

SlateportCity_OceanicMuseum_1F_Text_FossilDisplay:
	.string "{CHN}这是一块带有波纹的化石。\p"
	.string "“海底的土壤被潮水\n"
	.string "冲刷着。\p"
	.string "“流动的海水在土壤上\n"
	.string "留下了小小的脊和谷。\p"
	.string "“如果这种土壤变成化石，\n"
	.string "就被称为波痕。”$"

SlateportCity_OceanicMuseum_1F_Text_DepthMeasuringMachine:
	.string "{CHN}玻璃罩下，一台奇怪的机器\n"
	.string "正在旋转。\p"
	.string "也许它是用来测量\n"
	.string "某种东西的深度的…$"

