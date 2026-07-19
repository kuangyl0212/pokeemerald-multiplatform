MysteryGiftScript_MysticTicket::
	setvaddress MysteryGiftScript_MysticTicket
	lock
	faceplayer
	vgoto_if_set FLAG_RECEIVED_MYSTIC_TICKET, MysticTicket_Obtained
	vgoto_if_set FLAG_CAUGHT_LUGIA, MysticTicket_Obtained
	vgoto_if_set FLAG_CAUGHT_HO_OH, MysticTicket_Obtained
	checkitem ITEM_MYSTIC_TICKET
	vgoto_if_eq VAR_RESULT, TRUE, MysticTicket_Obtained
	vmessage sText_MysticTicketForYou
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_MYSTIC_TICKET
	vgoto_if_eq VAR_RESULT, FALSE, MysticTicket_NoBagSpace
	giveitem ITEM_MYSTIC_TICKET
	setflag FLAG_ENABLE_SHIP_NAVEL_ROCK
	setflag FLAG_RECEIVED_MYSTIC_TICKET
	vmessage sText_MysticTicketUseAtPort
	waitmessage
	waitbuttonpress
	release
	end

MysticTicket_NoBagSpace:
	vmessage sText_MysticTicketBagFull
	waitmessage
	waitbuttonpress
	release
	end

MysticTicket_Obtained:
	vmessage sText_MysticTicketThankYou
	waitmessage
	waitbuttonpress
	release
	end

sText_MysticTicketForYou:
	.string "{CHN}感谢你使用神秘\n"
	.string "礼物系统。\p"
	.string "你就是{PLAYER}吧。\n"
	.string "这里有一张给你的票。$"

sText_MysticTicketUseAtPort:
	.string "{CHN}这似乎是在\n"
	.string "水静市港口使用的。\p"
	.string "何不去试一试，\n"
	.string "看看到底是什么呢？$"

sText_MysticTicketThankYou:
	.string "{CHN}感谢你使用神秘\n"
	.string "礼物系统。$"

sText_MysticTicketBagFull:
	.string "{CHN}哦，抱歉，{PLAYER}。\n"
	.string "你的背包重要物品口袋已满。\p"
	.string "请先把一些东西存到电脑里，\n"
	.string "然后再来取吧。$"
