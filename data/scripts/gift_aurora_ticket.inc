MysteryGiftScript_AuroraTicket::
	setvaddress MysteryGiftScript_AuroraTicket
	lock
	faceplayer
	vgoto_if_set FLAG_RECEIVED_AURORA_TICKET, AuroraTicket_Obtained
	vgoto_if_set FLAG_BATTLED_DEOXYS, AuroraTicket_Obtained
	checkitem ITEM_AURORA_TICKET
	vgoto_if_eq VAR_RESULT, TRUE, AuroraTicket_Obtained
	vmessage sText_AuroraTicketForYou
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_AURORA_TICKET
	vgoto_if_eq VAR_RESULT, FALSE, AuroraTicket_NoBagSpace
	giveitem ITEM_AURORA_TICKET
	setflag FLAG_ENABLE_SHIP_BIRTH_ISLAND
	setflag FLAG_RECEIVED_AURORA_TICKET
	vmessage sText_AuroraTicketUseAtPort
	waitmessage
	waitbuttonpress
	release
	end

AuroraTicket_NoBagSpace:
	vmessage sText_AuroraTicketBagFull
	waitmessage
	waitbuttonpress
	release
	end

AuroraTicket_Obtained:
	vmessage sText_AuroraTicketThankYou
	waitmessage
	waitbuttonpress
	release
	end

sText_AuroraTicketForYou:
	.string "{CHN}感谢你使用神秘\n"
	.string "礼物系统。\p"
	.string "你就是{PLAYER}吧。\n"
	.string "这里有一张给你的票。$"

sText_AuroraTicketUseAtPort:
	.string "{CHN}这似乎是在\n"
	.string "水静市港口使用的。\p"
	.string "何不去试一试，\n"
	.string "看看到底是什么呢？$"

sText_AuroraTicketThankYou:
	.string "{CHN}感谢你使用神秘\n"
	.string "礼物系统。$"

sText_AuroraTicketBagFull:
	.string "{CHN}哦，抱歉，{PLAYER}。\n"
	.string "你的背包重要物品口袋已满。\p"
	.string "请先把一些东西存到电脑里，\n"
	.string "然后再来取吧。$"
