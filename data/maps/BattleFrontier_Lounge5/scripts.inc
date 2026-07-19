BattleFrontier_Lounge5_MapScripts::
	.byte 0

BattleFrontier_Lounge5_EventScript_NatureGirl::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge5_Text_NatureGirlGreeting, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown
	special ChoosePartyMon
	waitstate
	lock
	faceplayer
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, BattleFrontier_Lounge5_EventScript_NatureGirlEgg
	special ShowNatureGirlMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirlEgg::
	msgbox BattleFrontier_Lounge5_Text_NatureGirlEgg, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown::
	msgbox BattleFrontier_Lounge5_Text_NatureGirlNoneShown, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_Gentleman::
	msgbox BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_BlackBelt::
	msgbox BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_LittleBoy::
	msgbox BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot, MSGBOX_NPC
	end

BattleFrontier_Lounge5_Text_NatureGirlGreeting::
	.string "{CHN}嘿嘿！\n"
	.string "我能听懂宝可梦在想什么！\p"
	.string "拜托！\n"
	.string "能让我看看你的宝可梦吗？$"

BattleFrontier_Lounge5_Text_NatureGirlNoneShown::
	.string "{CHN}啵！\n"
	.string "小气鬼！$"

BattleFrontier_Lounge5_Text_NatureGirlHardy::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它喜欢对战！\n"
	.string "即使受了很多伤，\l"
	.string "它也会继续战斗！$"

BattleFrontier_Lounge5_Text_NatureGirlLonely::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它喜欢偷偷摸摸！\n"
	.string "但如果受了足够的伤，\l"
	.string "它就会反击！$"

BattleFrontier_Lounge5_Text_NatureGirlBrave::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它喜欢对战！\n"
	.string "但如果受了足够的伤，\l"
	.string "它就会为自己担心！$"

BattleFrontier_Lounge5_Text_NatureGirlAdamant::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它喜欢对战！\n"
	.string "即使受了很多伤，\l"
	.string "它也会继续战斗！$"

BattleFrontier_Lounge5_Text_NatureGirlNaughty::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它会照顾自己！\n"
	.string "但如果受了足够的伤，\l"
	.string "它就会反击！$"

BattleFrontier_Lounge5_Text_NatureGirlBold::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它喜欢偷偷摸摸！\n"
	.string "但如果受了足够的伤，\l"
	.string "它就会为自己担心！$"

BattleFrontier_Lounge5_Text_NatureGirlDocileNaiveQuietQuirky::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它喜欢对战！\n"
	.string "即使受了很多伤，\l"
	.string "它也会继续战斗！$"

BattleFrontier_Lounge5_Text_NatureGirlRelaxed::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它喜欢偷偷摸摸！\n"
	.string "但如果受了足够的伤，\l"
	.string "它就会反击！$"

BattleFrontier_Lounge5_Text_NatureGirlImpish::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它喜欢对战！\n"
	.string "但如果受了足够的伤，\l"
	.string "它就会为自己担心！$"

BattleFrontier_Lounge5_Text_NatureGirlLax::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它喜欢偷偷摸摸！\n"
	.string "它说即使受了很多伤，\l"
	.string "它也喜欢偷偷摸摸！$"

BattleFrontier_Lounge5_Text_NatureGirlTimid::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它喜欢对战！\n"
	.string "但如果受了足够的伤，\l"
	.string "它就会变得偷偷摸摸！$"

BattleFrontier_Lounge5_Text_NatureGirlHasty::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它喜欢对战！\n"
	.string "即使受了很多伤，\l"
	.string "它也会继续战斗！$"

BattleFrontier_Lounge5_Text_NatureGirlSerious::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它喜欢偷偷摸摸！\n"
	.string "它说即使受了很多伤，\l"
	.string "它也喜欢偷偷摸摸！$"

BattleFrontier_Lounge5_Text_NatureGirlJolly::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它喜欢偷偷摸摸！\n"
	.string "但如果受了足够的伤，\l"
	.string "它就会为自己担心！$"

BattleFrontier_Lounge5_Text_NatureGirlModest::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它会照顾自己！\n"
	.string "它说不管有没有受很多伤，\l"
	.string "它都会为自己担心！$"

BattleFrontier_Lounge5_Text_NatureGirlMild::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它会照顾自己！\n"
	.string "但如果受了足够的伤，\l"
	.string "它就会变得偷偷摸摸！$"

BattleFrontier_Lounge5_Text_NatureGirlBashful::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它会照顾自己！\n"
	.string "它说即使受了很多伤，\l"
	.string "它也会为自己担心！$"

BattleFrontier_Lounge5_Text_NatureGirlRash::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它喜欢偷偷摸摸！\n"
	.string "它说即使受了很多伤，\l"
	.string "它也喜欢偷偷摸摸！$"

BattleFrontier_Lounge5_Text_NatureGirlCalm::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它会照顾自己！\n"
	.string "它说即使受了很多伤，\l"
	.string "它也会为自己担心！$"

BattleFrontier_Lounge5_Text_NatureGirlGentle::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它会照顾自己！\n"
	.string "但如果受了足够的伤，\l"
	.string "它就会反击！$"

BattleFrontier_Lounge5_Text_NatureGirlSassy::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它喜欢对战！\n"
	.string "但如果受了足够的伤，\l"
	.string "它就会变得偷偷摸摸！$"

BattleFrontier_Lounge5_Text_NatureGirlCareful::
	.string "{CHN}嗯嗯……\p"
	.string "这一只说它会照顾自己！\n"
	.string "但如果受了足够的伤，\l"
	.string "它就会变得偷偷摸摸！$"

BattleFrontier_Lounge5_Text_NatureGirlEgg::
	.string "{CHN}真傻！蛋还在睡觉呢！\n"
	.string "我没法和它说话！$"

BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon::
	.string "{CHN}真迷人！\n"
	.string "那位小女士声称她能\l"
	.string "听懂宝可梦的话！$"

BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound::
	.string "{CHN}我有一种感觉，\n"
	.string "那个小女孩正在说一些深奥的话。$"

BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot::
	.string "{CHN}我知道一件事！\p"
	.string "那个小女孩经常在\n"
	.string "那栋红房子那里玩！$"

