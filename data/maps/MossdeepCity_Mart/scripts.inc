MossdeepCity_Mart_MapScripts::
	.byte 0

MossdeepCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MossdeepCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MossdeepCity_Mart_Pokemart:
	.short ITEM_ULTRA_BALL
	.short ITEM_NET_BALL
	.short ITEM_DIVE_BALL
	.short ITEM_HYPER_POTION
	.short ITEM_FULL_HEAL
	.short ITEM_REVIVE
	.short ITEM_MAX_REPEL
	.short ITEM_X_ATTACK
	.short ITEM_X_DEFEND
	pokemartlistend

MossdeepCity_Mart_EventScript_Woman::
	msgbox MossdeepCity_Mart_Text_ReviveIsFantastic, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_Boy::
	msgbox MossdeepCity_Mart_Text_MaxRepelLastsLongest, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_Sailor::
	msgbox MossdeepCity_Mart_Text_NetAndDiveBallsRare, MSGBOX_NPC
	end

MossdeepCity_Mart_Text_ReviveIsFantastic:
	.string "{CHN}活力碎片太棒了！\p"
	.string "把它给昏倒的宝可梦，\n"
	.string "宝可梦就会苏醒。\p"
	.string "不过要注意，活力碎片无法恢复\n"
	.string "招式已经消耗的PP。$"

MossdeepCity_Mart_Text_MaxRepelLastsLongest:
	.string "{CHN}强效喷雾剂能让所有弱小的宝可梦远离。\p"
	.string "在所有喷雾剂中，它的\n"
	.string "持续时间最长。$"

MossdeepCity_Mart_Text_NetAndDiveBallsRare:
	.string "{CHN}网纹球和深水球是只有在琉璃市\n"
	.string "才能制作的稀有精灵球。\p"
	.string "网纹球对虫属性和\n"
	.string "水属性的宝可梦很有效。\p"
	.string "深水球对海底的\n"
	.string "宝可梦效果最好。$"
