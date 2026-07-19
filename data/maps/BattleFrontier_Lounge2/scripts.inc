BattleFrontier_Lounge2_MapScripts::
	.byte 0

/* This NPC gives hints about a random facility or battle mode.*/
/* For battle modes he gives generic advice*/
/* For facilities, depending on how far the player has progressed he will say either*/
/*    The name of the Frontier Brain there*/
/*    The type and description of the 3 pokemon they use in their silver battle*/
/*    The type and description of the 3 pokemon they use in their gold battle*/
BattleFrontier_Lounge2_EventScript_FrontierManiac::
	lock
	faceplayer
	goto_if_set FLAG_MET_BATTLE_FRONTIER_MANIAC, BattleFrontier_Lounge2_EventScript_AlreadyMetManiac
	setflag FLAG_MET_BATTLE_FRONTIER_MANIAC
	msgbox BattleFrontier_Lounge2_Text_FrontierManiacIntro, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge2_EventScript_GiveAdvice
	end

BattleFrontier_Lounge2_EventScript_AlreadyMetManiac::
	msgbox BattleFrontier_Lounge2_Text_SwingByForTheLatestWord, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge2_EventScript_GiveAdvice
	end

BattleFrontier_Lounge2_EventScript_GiveAdvice::
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_SINGLES, BattleFrontier_Lounge2_EventScript_BufferSingle
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_DOUBLES, BattleFrontier_Lounge2_EventScript_BufferDouble
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_MULTIS, BattleFrontier_Lounge2_EventScript_BufferMulti
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_LINK, BattleFrontier_Lounge2_EventScript_BufferMultiLink
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_DOME, BattleFrontier_Lounge2_EventScript_BufferBattleDome
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_FACTORY, BattleFrontier_Lounge2_EventScript_BufferBattleFactory
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PALACE, BattleFrontier_Lounge2_EventScript_BufferBattlePalace
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_ARENA, BattleFrontier_Lounge2_EventScript_BufferBattleArena
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PIKE, BattleFrontier_Lounge2_EventScript_BufferBattlePike
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PYRAMID, BattleFrontier_Lounge2_EventScript_BufferBattlePyramid
@ <= FRONTIER_MANIAC_TOWER_LINK is any Battle Tower mode
	call_if_le VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_LINK, BattleFrontier_Lounge2_EventScript_BattleTowerNews
@ >= FRONTIER_MANIAC_DOME is any facility other than Battle Tower
	call_if_ge VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_DOME, BattleFrontier_Lounge2_EventScript_FacilityNews
	special ShowFrontierManiacMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge2_EventScript_BattleTowerNews::
	msgbox BattleFrontier_Lounge2_Text_BattleTowerIsHottest, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge2_EventScript_FacilityNews::
	msgbox BattleFrontier_Lounge2_Text_FacilityIsHottest, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge2_EventScript_BufferSingle::
	bufferstdstring STR_VAR_1, STDSTRING_SINGLE
	return

BattleFrontier_Lounge2_EventScript_BufferDouble::
	bufferstdstring STR_VAR_1, STDSTRING_DOUBLE
	return

BattleFrontier_Lounge2_EventScript_BufferMulti::
	bufferstdstring STR_VAR_1, STDSTRING_MULTI
	return

BattleFrontier_Lounge2_EventScript_BufferMultiLink::
	bufferstdstring STR_VAR_1, STDSTRING_MULTI_LINK
	return

BattleFrontier_Lounge2_EventScript_BufferBattleDome::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_DOME
	return

BattleFrontier_Lounge2_EventScript_BufferBattleFactory::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_FACTORY
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePalace::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PALACE
	return

BattleFrontier_Lounge2_EventScript_BufferBattleArena::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_ARENA
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePike::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PIKE
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePyramid::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PYRAMID
	return

BattleFrontier_Lounge2_EventScript_Maniac1::
	lock
	msgbox BattleFrontier_Lounge2_Text_NewsGatheringPower, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_Maniac2::
	lock
	msgbox BattleFrontier_Lounge2_Text_AmazingPowersOfObservation, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_Maniac3::
	lock
	msgbox BattleFrontier_Lounge2_Text_AmazingPowerOfPersuasion, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_TriathleteF::
	msgbox BattleFrontier_Lounge2_Text_ThisPlaceIsScaringMe, MSGBOX_NPC
	end

BattleFrontier_Lounge2_Text_FrontierManiacIntro::
	.string "{CHN}嘿！说到对战开拓区的新闻，\n"
	.string "我可是第一名。\p"
	.string "你可以把我当作\n"
	.string "开拓区狂人。\p"
	.string "确认一下，你是个训练家，\n"
	.string "对吧？\p"
	.string "我很乐意分享我收集到的\n"
	.string "关于对战开拓区的最新消息。$"

BattleFrontier_Lounge2_Text_SwingByForTheLatestWord::
	.string "{CHN}嘿！你是来向我打听\n"
	.string "最新消息的吗？哦，好的！$"

/* Unused*/
BattleFrontier_Lounge2_Text_MyInformationsBeenUsefulRight::
	.string "{CHN}怎么样？怎么样？怎么样？\p"
	.string "我确信我的情报\n"
	.string "对你很有用，对吧？$"

BattleFrontier_Lounge2_Text_FacilityIsHottest::
	.string "{CHN}让我想想……\p"
	.string "听起来{STR_VAR_1}\n"
	.string "是最热门的地方。$"

BattleFrontier_Lounge2_Text_BattleTowerIsHottest::
	.string "{CHN}让我想想……\p"
	.string "听起来对战塔\n"
	.string "{STR_VAR_1}是最热门的。$"

BattleFrontier_Lounge2_Text_SalonMaidenIsThere::
	.string "{CHN}你肯定不知道这个！\p"
	.string "亚希达称为开拓区首领的\n"
	.string "顶级训练家之一就在那里。\p"
	.string "是一个叫沙龙少女的\n"
	.string "神秘训练家在管理那里。$"

BattleFrontier_Lounge2_Text_SalonMaidenSilverMons::
	.string "{CHN}你和沙龙少女对战过了吗？\p"
	.string "当她衡量对手时，\n"
	.string "据说会使用这些宝可梦：\p"
	.string "一只超能力属性的意念宝可梦，\n"
	.string "一只火属性的火山宝可梦，\l"
	.string "和一只普通属性的贪睡宝可梦。$"

BattleFrontier_Lounge2_Text_SalonMaidenGoldMons::
	.string "{CHN}你和认真的沙龙少女\n"
	.string "对战过了吗？\p"
	.string "当她全力以赴时，\n"
	.string "据说会使用这些宝可梦：\p"
	.string "一只龙和超能力属性的无限宝可梦，\n"
	.string "一只电属性的雷电宝可梦，\l"
	.string "和一只普通属性的贪睡宝可梦。$"

BattleFrontier_Lounge2_Text_DomeAceIsThere::
	.string "{CHN}你肯定不知道这个！\p"
	.string "亚希达称为开拓区首领的\n"
	.string "顶级训练家之一就在那里。\p"
	.string "是一个叫巨蛋王牌的\n"
	.string "华丽训练家在管理那里。$"

BattleFrontier_Lounge2_Text_DomeAceSilverMons::
	.string "{CHN}你和巨蛋王牌对战过了吗？\p"
	.string "当他轻视对手时，\n"
	.string "会使用这三只宝可梦：\p"
	.string "一只龙和飞行属性的龙宝可梦，\n"
	.string "一只水和地面属性的泥鱼宝可梦，\l"
	.string "和一只火和飞行属性的火焰宝可梦。$"

BattleFrontier_Lounge2_Text_DomeAceGoldMons::
	.string "{CHN}你和认真的巨蛋王牌\n"
	.string "对战过了吗？\p"
	.string "当他展示策略时，\n"
	.string "会使用这三只宝可梦：\p"
	.string "一只龙和飞行属性的无限宝可梦，\n"
	.string "一只水和地面属性的泥鱼宝可梦，\l"
	.string "和一只钢和超能力属性的\l"
	.string "铁足宝可梦。$"

BattleFrontier_Lounge2_Text_FactoryHeadIsThere::
	.string "{CHN}你肯定不知道这个！\p"
	.string "亚希达称为开拓区首领的\n"
	.string "顶级训练家之一就在那里。\p"
	.string "是一个叫工厂首领的\n"
	.string "怪异训练家在管理那里。$"

BattleFrontier_Lounge2_Text_FactoryHeadSilverMons::
	.string "{CHN}你已经和工厂首领\n"
	.string "对战过了吗？\p"
	.string "让我想想……当他去对战时，\n"
	.string "他只是租三只宝可梦。\p"
	.string "他在几乎和你相同的\n"
	.string "条件下对战。$"

BattleFrontier_Lounge2_Text_FactoryHeadGoldMons::
	.string "{CHN}你和认真的工厂首领\n"
	.string "对战过了吗？\p"
	.string "当他认真去对战时，\n"
	.string "他还是租三只宝可梦。\p"
	.string "他在几乎和你相同的\n"
	.string "条件下对战。$"

BattleFrontier_Lounge2_Text_PikeQueenIsThere::
	.string "{CHN}你肯定不知道这个！\p"
	.string "亚希达称为开拓区首领的\n"
	.string "顶级训练家之一就在那里。\p"
	.string "是一个叫管道女王的\n"
	.string "可怕训练家在管理那里。$"

BattleFrontier_Lounge2_Text_PikeQueenSilverMons::
	.string "{CHN}你以前和管道女王\n"
	.string "对战过了吗？\p"
	.string "当她心情好时，据说\n"
	.string "会使用这三只宝可梦：\p"
	.string "一只毒属性的毒牙蛇宝可梦，\n"
	.string "一只虫和岩石属性的霉菌宝可梦，\l"
	.string "和一只水属性的温柔宝可梦。$"

BattleFrontier_Lounge2_Text_PikeQueenGoldMons::
	.string "{CHN}你和认真的管道女王\n"
	.string "对战过了吗？\p"
	.string "当她真的恼怒时，据说\n"
	.string "会使用这三只宝可梦：\p"
	.string "一只毒属性的毒牙蛇宝可梦，\n"
	.string "一只钢和地面属性的铁蛇宝可梦，\l"
	.string "和一只水和飞行属性的\l"
	.string "凶恶宝可梦。$"

BattleFrontier_Lounge2_Text_ArenaTycoonIsThere::
	.string "{CHN}你肯定不知道这个！\p"
	.string "亚希达称为开拓区首领的\n"
	.string "顶级训练家之一就在那里。\p"
	.string "是一个叫竞技场大亨的\n"
	.string "可爱训练家在管理那里。$"

BattleFrontier_Lounge2_Text_ArenaTycoonSilverMons::
	.string "{CHN}你以前和竞技场大亨\n"
	.string "对战过了吗？\p"
	.string "当她评估对手实力时，\n"
	.string "据说会使用这些宝可梦：\p"
	.string "一只虫和格斗属性的独角宝可梦，\n"
	.string "一只恶属性的月光宝可梦，\l"
	.string "和一只虫和幽灵属性的蜕壳宝可梦。$"

BattleFrontier_Lounge2_Text_ArenaTycoonGoldMons::
	.string "{CHN}你和认真的竞技场大亨\n"
	.string "对战过了吗？\p"
	.string "当她动真格时，\n"
	.string "据说会使用这些宝可梦：\p"
	.string "一只恶属性的月光宝可梦，\n"
	.string "一只幽灵和毒属性的影子宝可梦，\l"
	.string "和一只草和格斗属性的\l"
	.string "蘑菇宝可梦。$"

BattleFrontier_Lounge2_Text_PalaceMavenIsThere::
	.string "{CHN}你肯定不知道这个！\p"
	.string "亚希达称为开拓区首领的\n"
	.string "顶级训练家之一就在那里。\p"
	.string "是一个叫宫殿守护者的\n"
	.string "阴森训练家在管理那里。$"

BattleFrontier_Lounge2_Text_PalaceMavenSilverMons::
	.string "{CHN}你以前和宫殿守护者\n"
	.string "对战过了吗？\p"
	.string "当他测试对手的精神时，\n"
	.string "据说会使用这些宝可梦：\p"
	.string "一只毒和飞行属性的蝙蝠宝可梦，\n"
	.string "一只普通属性的懒散宝可梦，和一只\l"
	.string "水和冰属性的渡运宝可梦。$"

BattleFrontier_Lounge2_Text_PalaceMavenGoldMons::
	.string "{CHN}你和认真的宫殿守护者\n"
	.string "对战过了吗？\p"
	.string "当他倾尽全力投入战斗时，\n"
	.string "据说会使用这些宝可梦：\p"
	.string "一只火属性的传说宝可梦，\n"
	.string "一只普通属性的懒散宝可梦，\l"
	.string "和一只水属性的极光宝可梦。$"

BattleFrontier_Lounge2_Text_PyramidKingIsThere::
	.string "{CHN}你肯定不知道这个！\p"
	.string "亚希达称为开拓区首领的\n"
	.string "顶级训练家之一就在那里。\p"
	.string "是一个叫金字塔之王的\n"
	.string "火热训练家在管理那里。$"

BattleFrontier_Lounge2_Text_PyramidKingSilverMons::
	.string "{CHN}你以前和金字塔之王\n"
	.string "对战过了吗？\p"
	.string "当他检验对手的力量时，\n"
	.string "据说会使用这些宝可梦：\p"
	.string "一只岩石属性的岩峰宝可梦，\n"
	.string "一只冰属性的冰山宝可梦，\l"
	.string "和一只钢属性的铁宝可梦。$"

BattleFrontier_Lounge2_Text_PyramidKingGoldMons::
	.string "{CHN}你和认真的金字塔之王\n"
	.string "对战过了吗？\p"
	.string "当他充满炽热力量时，\n"
	.string "据说会使用这些宝可梦：\p"
	.string "一只冰和飞行属性的冰冻宝可梦，一只\n"
	.string "电和飞行属性的电气宝可梦，\l"
	.string "和一只火和飞行属性的\l"
	.string "火焰宝可梦。$"

BattleFrontier_Lounge2_Text_DoubleBattleAdvice1::
	.string "{CHN}当然，有几个地方\n"
	.string "可以参加双打对战。\p"
	.string "但对战塔的双打对战房\n"
	.string "算是基础！\p"
	.string "你应该在那里学习\n"
	.string "对战开拓区双打对战的\l"
	.string "玩法。$"

BattleFrontier_Lounge2_Text_DoubleBattleAdvice2::
	.string "{CHN}在这里对战要小心。\p"
	.string "我听说有些训练家\n"
	.string "专门为双打对战\l"
	.string "开发了策略。$"

BattleFrontier_Lounge2_Text_DoubleBattleAdvice3::
	.string "{CHN}一旦你对这里的双打对战\n"
	.string "有了信心和适应，\l"
	.string "你应该考虑挑战其他\l"
	.string "提供双打对战的地方。$"

BattleFrontier_Lounge2_Text_MultiBattleAdvice::
	.string "{CHN}各种训练家都会聚集在\n"
	.string "对战沙龙。\p"
	.string "想想看——你可能会遇到\n"
	.string "你的朋友或追随者！\l"
	.string "你应该仔细看看！$"

BattleFrontier_Lounge2_Text_LinkMultiBattleAdvice::
	.string "{CHN}如果你和朋友在一起，\n"
	.string "就去联机多人对战房。\p"
	.string "如果你和强大的朋友一起玩，\n"
	.string "你会遇到强劲的对手！$"

BattleFrontier_Lounge2_Text_NewsGatheringPower::
	.string "{CHN}多么惊人的新闻收集能力！\n"
	.string "我的导师无人能比！$"

BattleFrontier_Lounge2_Text_AmazingPowersOfObservation::
	.string "{CHN}多么惊人的观察力！\n"
	.string "我的导师无人能比！$"

BattleFrontier_Lounge2_Text_AmazingPowerOfPersuasion::
	.string "{CHN}多么惊人的说服力！\n"
	.string "我的导师无人能比！$"

BattleFrontier_Lounge2_Text_ThisPlaceIsScaringMe::
	.string "{CHN}……这是什么地方？\n"
	.string "好吓人……$"

