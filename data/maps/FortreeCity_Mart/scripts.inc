FortreeCity_Mart_MapScripts::
	.byte 0

FortreeCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart FortreeCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
FortreeCity_Mart_Pokemart:
	.short ITEM_GREAT_BALL
	.short ITEM_ULTRA_BALL
	.short ITEM_SUPER_POTION
	.short ITEM_HYPER_POTION
	.short ITEM_ANTIDOTE
	.short ITEM_PARALYZE_HEAL
	.short ITEM_AWAKENING
	.short ITEM_REVIVE
	.short ITEM_SUPER_REPEL
	.short ITEM_WOOD_MAIL
	pokemartlistend

FortreeCity_Mart_EventScript_Woman::
	msgbox FortreeCity_Mart_Text_SuperRepelBetter, MSGBOX_NPC
	end

FortreeCity_Mart_EventScript_Girl::
	msgbox FortreeCity_Mart_Text_StockUpOnItems, MSGBOX_NPC
	end

FortreeCity_Mart_EventScript_Boy::
	msgbox FortreeCity_Mart_Text_RareCandyMakesMonGrow, MSGBOX_NPC
	end

FortreeCity_Mart_Text_SuperRepelBetter:
	.string "{CHN}超级喷雾剂持续时间长，\n"
	.string "效果也好。\p"
	.string "比普通的\n"
	.string "喷雾剂好多了。$"

FortreeCity_Mart_Text_StockUpOnItems:
	.string "{CHN}我总是准备超出\n"
	.string "需求的道具。\p"
	.string "世事难料啊。\n"
	.string "有备无患嘛！$"

FortreeCity_Mart_Text_RareCandyMakesMonGrow:
	.string "{CHN}神奇糖果能让宝可梦\n"
	.string "立即提升一级。$"
