SlateportCity_OceanicMuseum_2F_MapScripts::
	.byte 0

SlateportCity_OceanicMuseum_2F_EventScript_CaptStern::
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, TRUE
	addobject LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter
	waitmovement 0
	addobject LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter
	waitmovement 0
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach
	waitmovement 0
	call_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts
	call_if_eq VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts
	msgbox SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts, MSGBOX_DEFAULT
	call_if_ne VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_2F_EventScript_SternFaceGrunts
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou, MSGBOX_DEFAULT
	msgbox SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	call_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntSouth
	call_if_eq VAR_FACING, DIR_WEST, SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntWest
	trainerbattle_no_intro TRAINER_GRUNT_MUSEUM_1, SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat
	msgbox SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated
	waitmovement 0
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_MUSEUM_2, SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated
	waitmovement 0
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_MeddlingKid, MSGBOX_DEFAULT
	closemessage
	delay 35
	addobject LOCALID_OCEANIC_MUSEUM_2F_ARCHIE
	applymovement LOCALID_OCEANIC_MUSEUM_2F_ARCHIE, SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntMoveForArchie
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OCEANIC_MUSEUM_2F_ARCHIE, SlateportCity_OceanicMuseum_2F_Movement_ArchieApproachPlayer
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_ArchieWarning, MSGBOX_DEFAULT
	closemessage
	savebgm MUS_DUMMY
	fadedefaultbgm
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_OCEANIC_MUSEUM_2F_ARCHIE
	removeobject LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1
	removeobject LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2
	fadescreen FADE_FROM_BLACK
	delay 30
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_AQUA_GRUNTS
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs, MSGBOX_DEFAULT
	setvar VAR_0x8004, ITEM_DEVON_GOODS
	call Common_EventScript_PlayerHandedOverTheItem
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	removeobject LOCALID_OCEANIC_MUSEUM_2F_CAPT_STERN
	setflag FLAG_HIDE_ROUTE_110_TEAM_AQUA
	call_if_eq VAR_REGISTER_BIRCH_STATE, 0, SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch
	setflag FLAG_DELIVERED_DEVON_GOODS
	clearflag FLAG_HIDE_ROUTE_116_DEVON_EMPLOYEE
	setflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_EMPLOYEE
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1
	fadescreen FADE_FROM_BLACK
	release
	end

SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch::
	setvar VAR_REGISTER_BIRCH_STATE, 1
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_SternFaceGrunts::
	applymovement LOCALID_OCEANIC_MUSEUM_2F_CAPT_STERN, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntSouth::
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntWest::
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth:
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest:
	walk_up
	walk_left
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_Unused:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	delay_8
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieApproachPlayer:
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle:
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter:
	walk_down
	walk_right
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach:
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated:
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter:
	walk_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntMoveForArchie:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	walk_fast_down
	walk_in_place_faster_up
	step_end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample1::
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample2::
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_PressureExperiment::
	msgbox SlateportCity_OceanicMuseum_2F_Text_PressureExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_HoennModel::
	msgbox SlateportCity_OceanicMuseum_2F_Text_HoennModel, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_DeepSeawaterDisplay::
	msgbox SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SurfaceSeawaterDisplay::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSTidalReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmarineReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmersibleReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSAnneReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron1::
	msgbox SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron2::
	msgbox SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron3::
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts:
	.string "{CHN}嗯？如果你在找帅哥船长，\n"
	.string "那就是我了。\p"
	.string "啊！这一定是我向得文的\n"
	.string "兹伏奇社长订购的零件。\p"
	.string "谢谢你！太好了！\n"
	.string "我们现在可以准备探险了。$"

SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts:
	.string "{CHN}嘿嘿嘿，等等！\n"
	.string "那些零件我们要了！$"

SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou:
	.string "{CHN}帅哥船长：什-什么？\n"
	.string "你们是什么人？$"

SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua:
	.string "{CHN}我们是水舰队！\p"
	.string "我们的老大要那些零件！\n"
	.string "闭上嘴，乖乖交出来！$"

SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat:
	.string "{CHN}哇啊啊啊！\n"
	.string "我居然输给了一个小孩子！$"

SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious:
	.string "{CHN}哎呀，糟了…\n"
	.string "老大一定会大发雷霆的…$"

SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis:
	.string "{CHN}哼，你这个爱哭鬼！\n"
	.string "让我来收拾他！$"

SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat:
	.string "{CHN}什么？！\n"
	.string "我也输了！$"

SlateportCity_OceanicMuseum_2F_Text_MeddlingKid:
	.string "{CHN}这下怎么办？要是拿不到零件，\n"
	.string "我们可就完了！\p"
	.string "啊，我可没想到会被\n"
	.string "一个爱管闲事的小鬼搅局！$"

SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong:
	.string "{CHN}我来看看抢个零件\n"
	.string "为什么要这么久，结果你们\l"
	.string "两个笨蛋被一个小鬼给绊住了？$"

SlateportCity_OceanicMuseum_2F_Text_ArchieWarning:
	.string "{CHN}我们是水舰队，\n"
	.string "我们热爱大海！\p"
	.string "我是水舰队的首领，\n"
	.string "赤松！\p"
	.string "你为什么要妨碍我们？\p"
	.string "…不！你不会是！\n"
	.string "你不是火岩队的人吧？\p"
	.string "等等，那不可能。\n"
	.string "你穿得不像。\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "宝可梦、人类…所有的生命\n"
	.string "都依赖于大海。\p"
	.string "所以，水舰队致力于\n"
	.string "扩展大海。\p"
	.string "你不觉得吗？我们正在做的\n"
	.string "是一项伟大的事业。\p"
	.string "啊，算了…\n"
	.string "你还太年轻，无法理解\l"
	.string "我们崇高的目标。\p"
	.string "但是，我警告你，别再考虑\n"
	.string "干涉我们的计划了。\p"
	.string "否则后果将会\n"
	.string "让你付出惨重代价！\p"
	.string "你可别忘记了！$"

SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs:
	.string "{CHN}帅哥船长：你是…\n"
	.string "啊，好的，你是{PLAYER}{KUN}…\p"
	.string "总之，刚才的情况真紧张！\n"
	.string "谢谢你救了我们！\p"
	.string "哦，对了，我差点忘了你\n"
	.string "还把得文的零件送来了！$"

SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo:
	.string "{CHN}帅哥船长：哎呀！\n"
	.string "没时间了！\p"
	.string "我们必须马上出发\n"
	.string "进行海底探险。\p"
	.string "再次感谢你，但我现在\n"
	.string "得走了！\p"
	.string "不过，你可以随意逛逛，\n"
	.string "参观一下我们的设施。$"

SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip:
	.string "{CHN}我在这里看到了一艘船的模型。\p"
	.string "它让我想起了武斗镇附近\n"
	.string "那艘废弃船…$"

SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum:
	.string "{CHN}你敢在博物馆里\n"
	.string "到处乱跑试试！$"

SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine:
	.string "{CHN}哇，潜水艇太厉害了！\n"
	.string "我想坐一坐！$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1:
	.string "{CHN}“水质样本1”，\n"
	.string "标签上这样写着。\p"
	.string "大海都是相连的，但\n"
	.string "不同区域的水似乎有所不同。$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2:
	.string "{CHN}“水质样本2”，\n"
	.string "标签上这样写着。\p"
	.string "海水的咸度\n"
	.string "也因地区而异吗？$"

SlateportCity_OceanicMuseum_2F_Text_PressureExperiment:
	.string "{CHN}一个橡胶球正在膨胀和\n"
	.string "收缩。\p"
	.string "“在海洋中，水本身的重量\n"
	.string "会产生压力。\p"
	.string "“在浅水中，压力\n"
	.string "并不大。\p"
	.string "“然而，在极深的水中，\n"
	.string "压力在很小的区域上\l"
	.string "甚至可达数万吨。”$"

SlateportCity_OceanicMuseum_2F_Text_HoennModel:
	.string "{CHN}“丰缘地区模型”\p"
	.string "这是丰缘地区的\n"
	.string "微缩模型。\p"
	.string "未白镇在哪里呢？$"

SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay:
	.string "{CHN}这是一个关于海水流动的展示。\p"
	.string "“在海底附近，海水\n"
	.string "因温度和盐度等因素\l"
	.string "的差异而流动。”$"

SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay:
	.string "{CHN}这是一个关于海水流动的展示。\p"
	.string "“在接近海面处，海水\n"
	.string "形成由风驱动的洋流而流动。”$"

SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica:
	.string "{CHN}“渡轮 潮汐号\p"
	.string "“这是在帅哥造船厂\n"
	.string "建造中的船只的比例模型。”$"

SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica:
	.string "{CHN}“潜水艇 探险者1号\p"
	.string "“这是高性能海底探险\n"
	.string "潜水艇的模型。”$"

SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica:
	.string "{CHN}“潜水舱\p"
	.string "“这是用于海底探险的\n"
	.string "小型无人舱的模型。”$"

SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica:
	.string "{CHN}“圣特安号\p"
	.string "“这是环游世界的\n"
	.string "豪华客轮的模型。”$"

