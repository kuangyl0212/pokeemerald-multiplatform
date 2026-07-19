MtPyre_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CaveHole_CheckFallDownHole
	map_script MAP_SCRIPT_ON_TRANSITION, CaveHole_FixCrackedGround
	map_script MAP_SCRIPT_ON_RESUME, MtPyre_2F_SetHoleWarp
	.byte 0

MtPyre_2F_SetHoleWarp:
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp MAP_MT_PYRE_1F
	end

MtPyre_2F_EventScript_Woman::
	msgbox MtPyre_2F_Text_MemoriesOfSkitty, MSGBOX_NPC
	end

MtPyre_2F_EventScript_PokefanM::
	msgbox MtPyre_2F_Text_TumbledFromFloorAbove, MSGBOX_NPC
	end

MtPyre_2F_EventScript_Mark::
	trainerbattle_single TRAINER_MARK, MtPyre_2F_Text_MarkIntro, MtPyre_2F_Text_MarkDefeat
	msgbox MtPyre_2F_Text_MarkPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Luke::
	trainerbattle_double TRAINER_DEZ_AND_LUKE, MtPyre_2F_Text_LukeIntro, MtPyre_2F_Text_LukeDefeat, MtPyre_2F_Text_LukeNotEnoughMons
	msgbox MtPyre_2F_Text_LukePostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Dez::
	trainerbattle_double TRAINER_DEZ_AND_LUKE, MtPyre_2F_Text_DezIntro, MtPyre_2F_Text_DezDefeat, MtPyre_2F_Text_DezNotEnoughMons
	msgbox MtPyre_2F_Text_DezPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Leah::
	trainerbattle_single TRAINER_LEAH, MtPyre_2F_Text_LeahIntro, MtPyre_2F_Text_LeahDefeat
	msgbox MtPyre_2F_Text_LeahPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Zander::
	trainerbattle_single TRAINER_ZANDER, MtPyre_2F_Text_ZanderIntro, MtPyre_2F_Text_ZanderDefeat
	msgbox MtPyre_2F_Text_ZanderPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_Text_MemoriesOfSkitty:
	.string "{CHN}我亲爱的向尾喵的回忆……\n"
	.string "一想到它，眼泪就止不住。$"

MtPyre_2F_Text_TumbledFromFloorAbove:
	.string "{CHN}哎哟，疼……这里到处都是\n"
	.string "地上的洞。\p"
	.string "我没注意，结果从上一层\n"
	.string "摔下来了。$"

MtPyre_2F_Text_MarkIntro:
	.string "{CHN}嘿！你在找宝可梦吗？\n"
	.string "你跟在我后面来的！你太没礼貌了！$"

MtPyre_2F_Text_MarkDefeat:
	.string "{CHN}呀啊啊啊！\n"
	.string "对不起，请原谅我！$"

MtPyre_2F_Text_MarkPostBattle:
	.string "{CHN}这里很少有人来，所以我\n"
	.string "以为会有稀有的宝可梦。$"

MtPyre_2F_Text_LukeIntro:
	.string "{CHN}卢克：我们是来打赌的。\p"
	.string "嘿嘿，如果我让她看到我多帅，\n"
	.string "她就会爱上我。我知道！\p"
	.string "对了！我打败你，让她\n"
	.string "看看我有多帅！$"

MtPyre_2F_Text_LukeDefeat:
	.string "{CHN}卢克：糟糕！$"

MtPyre_2F_Text_LukePostBattle:
	.string "{CHN}卢克：嗯，我们输了，但没关系！\n"
	.string "我就陪在你身边。\l"
	.string "我们会一起挺过这个考验的！$"

MtPyre_2F_Text_LukeNotEnoughMons:
	.string "{CHN}卢克：如果你想跟我对战，\n"
	.string "再多带几只宝可梦来吧。\p"
	.string "不然的话，我就没法在我女朋友\n"
	.string "面前耍帅了！$"

MtPyre_2F_Text_DezIntro:
	.string "{CHN}迪兹：我和男朋友打赌\n"
	.string "来到这里。\p"
	.string "虽然很可怕，但我跟男朋友\n"
	.string "在一起。没事的。\p"
	.string "对了！我让我男朋友打败你，\n"
	.string "好让他耍耍帅！$"

MtPyre_2F_Text_DezDefeat:
	.string "{CHN}迪兹：哇啊啊！我好害怕！$"

MtPyre_2F_Text_DezPostBattle:
	.string "{CHN}迪兹：我们俩恩爱得很，\n"
	.string "输了也不在乎！$"

MtPyre_2F_Text_DezNotEnoughMons:
	.string "{CHN}迪兹：如果你想挑战我们，\n"
	.string "至少要带两只宝可梦来。\p"
	.string "我男朋友很强。\n"
	.string "只有一只宝可梦可不行。$"

MtPyre_2F_Text_LeahIntro:
	.string "{CHN}你是个生面孔……\n"
	.string "趁还没出事，赶紧离开吧！$"

MtPyre_2F_Text_LeahDefeat:
	.string "{CHN}嗯……\n"
	.string "你挺耐打的。$"

MtPyre_2F_Text_LeahPostBattle:
	.string "{CHN}从我曾祖母那一代起，\n"
	.string "我们家族就一直在这里当训练家……\p"
	.string "守护这座山\n"
	.string "是我的使命……$"

MtPyre_2F_Text_ZanderIntro:
	.string "{CHN}呀啊啊啊！\n"
	.string "我好害怕！$"

MtPyre_2F_Text_ZanderDefeat:
	.string "{CHN}不不不不！\n"
	.string "我吓傻了！$"

MtPyre_2F_Text_ZanderPostBattle:
	.string "{CHN}我每次看到什么东西动\n"
	.string "都会被吓到……\p"
	.string "我不该来这里修行的……$"

