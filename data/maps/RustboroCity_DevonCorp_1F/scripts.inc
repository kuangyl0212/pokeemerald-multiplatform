RustboroCity_DevonCorp_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_1F_OnTransition
	.byte 0

RustboroCity_DevonCorp_1F_OnTransition:
	call_if_unset FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_BlockStairs
	end

RustboroCity_DevonCorp_1F_EventScript_BlockStairs::
	setobjectxyperm LOCALID_DEVON_CORP_STAIR_GUARD, 14, 2
	setobjectmovementtype LOCALID_DEVON_CORP_STAIR_GUARD, MOVEMENT_TYPE_FACE_DOWN
	return

RustboroCity_DevonCorp_1F_EventScript_Employee::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright
	msgbox RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright::
	msgbox RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered::
	msgbox RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_StairGuard::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
	msgbox RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome::
	msgbox RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_GotRobbed::
	msgbox RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_Greeter::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp::
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed::
	msgbox RustboroCity_DevonCorp_1F_Text_StaffGotRobbed, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_RocksMetalDisplay::
	msgbox RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_1F_EventScript_ProductsDisplay::
	msgbox RustboroCity_DevonCorp_1F_Text_ProductDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp:
	.string "{CHN}你好，欢迎来到\n"
	.string "得文公司.\p"
	.string "我们自豪地生产各种道具和\n"
	.string "药品来提升您的生活.$"

RustboroCity_DevonCorp_1F_Text_StaffGotRobbed:
	.string "{CHN}我们的一位研究员愚蠢地\n"
	.string "被抢走了一个重要的包裹.$"

RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct:
	.string "{CHN}嘿，那双跑步鞋！\n"
	.string "那是我们的产品！\p"
	.string "看到有人使用我们制作的东西，\n"
	.string "我真的很开心.$"

RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright:
	.string "{CHN}那个被抢走的包裹…\p"
	.string "嗯，当然很重要，但它不是\n"
	.string "任何人都能使用的东西.\p"
	.string "据我估计，那个强盗\n"
	.string "一定不太聪明.$"

RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered:
	.string "{CHN}听起来他们已经找回了\n"
	.string "被抢走的得文货物.$"

RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter:
	.string "{CHN}很抱歉，只有授权人员\n"
	.string "才能进入这里.$"

RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed:
	.string "{CHN}真是太蠢了.\n"
	.string "我们怎么会被抢呢?$"

RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere:
	.string "{CHN}嗨，你好！\n"
	.string "这里随时欢迎你！$"

RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay:
	.string "{CHN}玻璃柜里展示着岩石和\n"
	.string "金属的样品.\p"
	.string "那里有一块写着\n"
	.string "文字的说明板…\p"
	.string "“得文公司最初是从采石场\n"
	.string "生产石头起家的.\p"
	.string "“公司还从沙中的铁屑\n"
	.string "提炼铁.\p"
	.string "“从作为原材料生产商的卑微起点开始，\n"
	.string "得文逐步发展.\p"
	.string "“得文现在是一家生产各种\n"
	.string "工业产品的制造商.”$"

RustboroCity_DevonCorp_1F_Text_ProductDisplay:
	.string "{CHN}玻璃展示柜里装满了\n"
	.string "原型和测试产品.\p"
	.string "那里有一块描述性的说明板…\p"
	.string "“除了工业产品外，\n"
	.string "得文现在还销售日用品和\l"
	.string "药品以改善生活.\p"
	.string "“最近，得文开始销售\n"
	.string "宝可梦训练家的工具，包括\l"
	.string "精灵球和宝可梦导航器系统.”$"

