FortreeCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, FortreeCity_OnResume
	.byte 0

FortreeCity_OnTransition:
	setflag FLAG_VISITED_FORTREE_CITY
	end

FortreeCity_OnResume:
	setstepcallback STEP_CB_FORTREE_BRIDGE
	end

FortreeCity_EventScript_Man::
	msgbox FortreeCity_Text_SawGiganticPokemonInSky, MSGBOX_NPC
	end

FortreeCity_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_KECLEON_FLED_FORTREE, FortreeCity_EventScript_WomanGymAccessible
	msgbox FortreeCity_Text_SomethingBlockingGym, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_WomanGymAccessible::
	msgbox FortreeCity_Text_ThisTimeIllBeatWinona, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_Girl::
	msgbox FortreeCity_Text_TreesGrowByDrinkingRainwater, MSGBOX_NPC
	end

FortreeCity_EventScript_OldMan::
	msgbox FortreeCity_Text_EveryoneHealthyAndLively, MSGBOX_NPC
	end

FortreeCity_EventScript_Boy::
	msgbox FortreeCity_Text_BugPokemonComeThroughWindow, MSGBOX_NPC
	end

FortreeCity_EventScript_GameboyKid::
	msgbox FortreeCity_Text_PokemonThatEvolveWhenTraded, MSGBOX_NPC
	end

FortreeCity_EventScript_CitySign::
	msgbox FortreeCity_Text_CitySign, MSGBOX_SIGN
	end

FortreeCity_EventScript_GymSign::
	msgbox FortreeCity_Text_GymSign, MSGBOX_SIGN
	end

FortreeCity_EventScript_Kecleon::
	lock
	faceplayer
	checkitem ITEM_DEVON_SCOPE
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_EventScript_AskUseDevonScope
	msgbox FortreeCity_Text_SomethingUnseeable, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_AskUseDevonScope::
	msgbox FortreeCity_Text_UnseeableUseDevonScope, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FortreeCity_EventScript_UseDevonScope
	release
	end

FortreeCity_EventScript_UseDevonScope::
	msgbox FortreeCity_Text_UsedDevonScopePokemonFled, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Movement_KecleonAppears
	waitmovement 0
	waitse
	playmoncry SPECIES_KECLEON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	applymovement VAR_LAST_TALKED, FortreeCity_Movement_KecleonFlee
	waitmovement 0
	removeobject VAR_LAST_TALKED
	setflag FLAG_KECLEON_FLED_FORTREE
	release
	end

FortreeCity_Movement_KecleonFlee:
	walk_right
	step_end

FortreeCity_Text_SawGiganticPokemonInSky:
	.string "{CHN}没人相信我，但我确实在天空中\n"
	.string "看到了巨大的宝可梦。\p"
	.string "它一边扭动一边\n"
	.string "飞向131号道路。\p"
	.string "对了……嗅嗅……\n"
	.string "嗯……你，呃……身上有股烧焦味。\p"
	.string "你是不是去了火山之类的地方？$"

FortreeCity_Text_SomethingBlockingGym:
	.string "{CHN}我想去宝可梦道馆，\n"
	.string "但有什么东西挡住了路。\p"
	.string "我费了那么大劲\n"
	.string "在120号道路上特训……$"

FortreeCity_Text_ThisTimeIllBeatWinona:
	.string "{CHN}我带上了最引以为豪的宝可梦。\n"
	.string "这次，我一定能打败娜琪。$"

FortreeCity_Text_TreesGrowByDrinkingRainwater:
	.string "{CHN}大地吸收雨水，\n"
	.string "树木通过吸收水分而生长……\p"
	.string "我们的茵郁市之所以存在，\n"
	.string "就是因为有水和土壤。$"

FortreeCity_Text_EveryoneHealthyAndLively:
	.string "{CHN}这座城市由建在\n"
	.string "树上的房屋组成。\p"
	.string "也许正是因为这种生活方式，\n"
	.string "每个人都健康活泼。\p"
	.string "哎呀，连我自己都觉得\n"
	.string "年轻了三十岁。$"

FortreeCity_Text_BugPokemonComeThroughWindow:
	.string "{CHN}住在树上也挺好。\p"
	.string "但有时虫属性宝可梦\n"
	.string "会从窗户飞进来。\l"
	.string "有时真的很吓人。$"

FortreeCity_Text_PokemonThatEvolveWhenTraded:
	.string "{CHN}有些宝可梦在\n"
	.string "交换之后会进化！我是这么听说的。$"

FortreeCity_Text_SomethingUnseeable:
	.string "{CHN}有什么看不见的东西挡住了路。$"

FortreeCity_Text_UnseeableUseDevonScope:
	.string "{CHN}有什么看不见的东西挡住了路。\p"
	.string "要使用得文观测镜吗？$"

FortreeCity_Text_UsedDevonScopePokemonFled:
	.string "{CHN}{PLAYER}使用了得文观测镜。\p"
	.string "原本看不见的宝可梦\n"
	.string "完全显现出来了！\p"
	.string "受惊的宝可梦逃走了！$"

FortreeCity_Text_CitySign:
	.string "{CHN}茵郁市\n"
	.string "“在自然中嬉戏的\l"
	.string "树梢之城。”$"

FortreeCity_Text_GymSign:
	.string "{CHN}茵郁市宝可梦道馆\n"
	.string "馆主：娜琪\p"
	.string "“展翅飞向\n"
	.string "世界的鸟类使者。”$"
