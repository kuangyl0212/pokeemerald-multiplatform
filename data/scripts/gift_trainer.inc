MysteryGiftScript_VisitingTrainer::
	setvaddress MysteryGiftScript_VisitingTrainer
	special ValidateEReaderTrainer
	vgoto_if_eq VAR_RESULT, 0, MysteryGiftScript_VisitingTrainerArrived
	lock
	faceplayer
	vmessage sText_MysteryGiftVisitingTrainerInstructions
	waitmessage
	waitbuttonpress
	release
	end

MysteryGiftScript_VisitingTrainerArrived:
	lock
	faceplayer
	vmessage sText_MysteryGiftVisitingTrainerArrived
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftVisitingTrainerInstructions:
	.string "{CHN}感谢你使用神秘\n"
	.string "礼物系统。\p"
	.string "持有这张神奇卡，\n"
	.string "你就可以在宝可梦商店参加\l"
	.string "问卷调查。\p"
	.string "通过这些问卷，\n"
	.string "你可以邀请训练家来到琉璃市。\p"
	.string "……让我告诉你一个\n"
	.string "用于问卷的秘密暗号：\p"
	.string "“给我\n"
	.string "超厉害的训练家”\p"
	.string "将这个写在问卷上，\n"
	.string "并发送到无线\l"
	.string "通信系统吧。$"

sText_MysteryGiftVisitingTrainerArrived:
	.string "{CHN}感谢你使用神秘\n"
	.string "礼物系统。\p"
	.string "一位训练家\n"
	.string "已经来到琉璃市找你了。\p"
	.string "希望你能享受\n"
	.string "与这位来访训练家的对战。\p"
	.string "你可以输入其他暗号\n"
	.string "来邀请其他训练家。\p"
	.string "试试寻找其他\n"
	.string "可能有效的暗号吧。$"
