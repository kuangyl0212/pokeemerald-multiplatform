MauvilleCity_House1_MapScripts::
	.byte 0

MauvilleCity_House1_EventScript_RockSmashDude::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_ROCK_SMASH, MauvilleCity_House1_EventScript_ReceivedRockSmash
	msgbox MauvilleCity_House1_Text_ImRockSmashDudeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_HM_ROCK_SMASH
	setflag FLAG_RECEIVED_HM_ROCK_SMASH
	setflag FLAG_HIDE_ROUTE_111_ROCK_SMASH_TIP_GUY
	msgbox MauvilleCity_House1_Text_ExplainRockSmash, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_EventScript_ReceivedRockSmash::
	msgbox MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_Text_ImRockSmashDudeTakeThis:
	.string "{CHN}呜呼！\p"
	.string "我听人们叫我碎岩男，\n"
	.string "但我觉得那有点贬低人。\p"
	.string "我觉得我应该得到更多尊重，\n"
	.string "比如叫碎岩大哥之类的。\p"
	.string "呜呼！\p"
	.string "总之，你的宝可梦看起来\n"
	.string "相当强。\p"
	.string "我喜欢这样！\n"
	.string "给，拿着这个秘传学习器！$"

MauvilleCity_House1_Text_ExplainRockSmash:
	.string "{CHN}那个秘传学习器里装有碎岩。\p"
	.string "如果你遇到挡路的大石头，\n"
	.string "……\p"
	.string "嗯，用那个秘传招式把它们\n"
	.string "击碎让开路吧！\p"
	.string "是的，先生！我说把石头击碎！\n"
	.string "呜呼！$"

MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock:
	.string "{CHN}哦，对了，如果你击碎一块石头，\n"
	.string "可能会有宝可梦从藏身处飞出来。\p"
	.string "呜呼！$"
