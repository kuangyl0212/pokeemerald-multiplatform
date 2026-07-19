MysteryGiftScript_OldSeaMap::
	setvaddress MysteryGiftScript_OldSeaMap
	lock
	faceplayer
	vgoto_if_set FLAG_RECEIVED_OLD_SEA_MAP, OldSeaMap_Obtained
	vgoto_if_set FLAG_CAUGHT_MEW, OldSeaMap_Obtained
	checkitem ITEM_OLD_SEA_MAP
	vgoto_if_eq VAR_RESULT, TRUE, OldSeaMap_Obtained
	vmessage sText_MysteryGiftOldSeaMapForYou
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_OLD_SEA_MAP
	vgoto_if_eq VAR_RESULT, FALSE, OldSeaMap_NoBagSpace
	giveitem ITEM_OLD_SEA_MAP
	setflag FLAG_ENABLE_SHIP_FARAWAY_ISLAND
	setflag FLAG_RECEIVED_OLD_SEA_MAP
	vmessage sText_MysteryGiftOldSeaMapUseAtPort
	waitmessage
	waitbuttonpress
	release
	end

OldSeaMap_NoBagSpace:
	vmessage sText_MysteryGiftOldSeaMapBagFull
	waitmessage
	waitbuttonpress
	release
	end

OldSeaMap_Obtained:
	vmessage sText_MysteryGiftOldSeaMapThankYou
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftOldSeaMapForYou:
	.string "{CHN}感谢你使用神秘\n"
	.string "礼物系统。\p"
	.string "让我确认一下——你就是{PLAYER}吧？\p"
	.string "我们收到了\n"
	.string "这张寄给你的古老地图。$"

sText_MysteryGiftOldSeaMapUseAtPort:
	.string "{CHN}这似乎是在\n"
	.string "水静市港口使用的。\p"
	.string "何不去试一试，\n"
	.string "看看到底是什么呢？$"

sText_MysteryGiftOldSeaMapThankYou:
	.string "{CHN}感谢你使用神秘\n"
	.string "礼物系统。$"

sText_MysteryGiftOldSeaMapBagFull:
	.string "{CHN}哦，抱歉，{PLAYER}。\n"
	.string "你的背包重要物品口袋已满。\p"
	.string "请先把一些东西存到电脑里，\n"
	.string "然后再来取吧。$"
