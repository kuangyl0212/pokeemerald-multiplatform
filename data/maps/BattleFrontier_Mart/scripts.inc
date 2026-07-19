BattleFrontier_Mart_MapScripts::
	.byte 0

BattleFrontier_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart BattleFrontier_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
BattleFrontier_Mart_Pokemart:
	.short ITEM_ULTRA_BALL
	.short ITEM_HYPER_POTION
	.short ITEM_MAX_POTION
	.short ITEM_FULL_RESTORE
	.short ITEM_FULL_HEAL
	.short ITEM_REVIVE
	.short ITEM_MAX_REPEL
	.short ITEM_PROTEIN
	.short ITEM_CALCIUM
	.short ITEM_IRON
	.short ITEM_ZINC
	.short ITEM_CARBOS
	.short ITEM_HP_UP
	pokemartlistend

BattleFrontier_Mart_EventScript_OldMan::
	msgbox BattleFrontier_Mart_Text_ChaperonGrandson, MSGBOX_NPC
	end

BattleFrontier_Mart_EventScript_OldWoman::
	lock
	applymovement LOCALID_FRONTIER_MART_OLD_WOMAN, Common_Movement_FaceDown
	waitmovement 0
	msgbox BattleFrontier_Mart_Text_ProteinMakeNiceGift, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Mart_EventScript_Boy::
	msgbox BattleFrontier_Mart_Text_FacilitiesDontAllowItems, MSGBOX_NPC
	end

BattleFrontier_Mart_Text_ChaperonGrandson:
	.string "{CHN}我们是来这里陪\n"
	.string "我们孙子的。\p"
	.string "不过既然来了，\n"
	.string "我们就想买点纪念品。$"

BattleFrontier_Mart_Text_ProteinMakeNiceGift:
	.string "{CHN}亲爱的，你觉得这个怎么样？\n"
	.string "这个作为礼物不错吧？\p"
	.string "这是……蛋……白……质？\n"
	.string "听起来好像很好吃呢。$"

BattleFrontier_Mart_Text_FacilitiesDontAllowItems:
	.string "{CHN}对战开拓区的很多设施\n"
	.string "在对战中都不允许\l"
	.string "使用道具。\p"
	.string "这条规则让本来就艰难的挑战\n"
	.string "变得更加困难！$"
