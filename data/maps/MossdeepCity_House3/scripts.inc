MossdeepCity_House3_MapScripts::
	.byte 0

MossdeepCity_House3_EventScript_SuperRodFisherman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SUPER_ROD, MossdeepCity_House3_EventScript_ReceivedSuperRod
	msgbox MossdeepCity_House3_Text_YouWantSuperRod, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MossdeepCity_House3_EventScript_DeclineSuperRod
	msgbox MossdeepCity_House3_Text_SuperRodIsSuper, MSGBOX_DEFAULT
	giveitem ITEM_SUPER_ROD
	setflag FLAG_RECEIVED_SUPER_ROD
	msgbox MossdeepCity_House3_Text_TryDroppingRodInWater, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_EventScript_ReceivedSuperRod::
	msgbox MossdeepCity_House3_Text_GoAfterSeafloorPokemon, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_EventScript_DeclineSuperRod::
	msgbox MossdeepCity_House3_Text_DontYouLikeToFish, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_Text_YouWantSuperRod:
	.string "{CHN}嘿，训练家！\n"
	.string "厉害钓竿真的很厉害！\p"
	.string "不管你怎么说，这宝贝能从\n"
	.string "海底钓上宝可梦！\p"
	.string "你觉得怎么样？\n"
	.string "你想要吧？$"

MossdeepCity_House3_Text_SuperRodIsSuper:
	.string "{CHN}当然，当然！\n"
	.string "毕竟，厉害钓竿真的很厉害！$"

MossdeepCity_House3_Text_TryDroppingRodInWater:
	.string "{CHN}如果有水的话，把钓竿\n"
	.string "放进去试试，看看有什么会上钩！$"

MossdeepCity_House3_Text_DontYouLikeToFish:
	.string "{CHN}咦？\n"
	.string "你不喜欢钓鱼吗？$"

MossdeepCity_House3_Text_GoAfterSeafloorPokemon:
	.string "{CHN}用你的厉害钓竿去\n"
	.string "钓海底的宝可梦吧。$"
