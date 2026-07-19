MysteryGiftScript_BattleCard::
	setvaddress MysteryGiftScript_BattleCard
	vgoto_if_set FLAG_MYSTERY_GIFT_DONE, MysteryGiftScript_BattleCardInfo
	setorcopyvar VAR_RESULT, GET_CARD_BATTLES_WON
	specialvar VAR_0x8008, GetMysteryGiftCardStat
	vgoto_if_ne VAR_0x8008, REQUIRED_CARD_BATTLES, MysteryGiftScript_BattleCardInfo
	lock
	faceplayer
	vmessage sText_MysteryGiftBattleCountCard_WonPrize
	waitmessage
	waitbuttonpress
	giveitem ITEM_POTION
	release
	setflag FLAG_MYSTERY_GIFT_DONE
	end

MysteryGiftScript_BattleCardInfo:
	lock
	faceplayer
	vmessage sText_MysteryGiftBattleCountCard
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftBattleCountCard:
	.string "{CHN}感谢你使用神秘\n"
	.string "礼物系统。\p"
	.string "你的对战计数卡可以记录\n"
	.string "你与持有相同卡的\l"
	.string "训练家的对战成绩。\p"
	.string "去寻找并挑战\n"
	.string "和你持有相同卡的训练家吧。\p"
	.string "你可以通过阅读新闻\n"
	.string "来查看总排名。\p"
	.string "请务必试一试！$"

sText_MysteryGiftBattleCountCard_WonPrize:
	.string "{CHN}感谢你使用神秘\n"
	.string "礼物系统。\p"
	.string "恭喜你！\p"
	.string "你赢得了三场对战的胜利，\n"
	.string "获得了奖品！\p"
	.string "希望你能再接再厉，\n"
	.string "继续挑战更多对战。$"
