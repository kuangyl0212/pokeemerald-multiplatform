MysteryGiftScript_AlteringCave::
	setvaddress MysteryGiftScript_AlteringCave
	addvar VAR_ALTERING_CAVE_WILD_SET, 1
	vgoto_if_ne VAR_ALTERING_CAVE_WILD_SET, (NUM_ALTERING_CAVE_TABLES + 1), MysteryGiftScript_AlteringCave_
	setvar VAR_ALTERING_CAVE_WILD_SET, 0
MysteryGiftScript_AlteringCave_:
	lock
	faceplayer
	vmessage sText_MysteryGiftAlteringCave
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftAlteringCave:
	.string "{CHN}感谢你使用神秘礼物系统。\n"
	.string "\p"
	.string "似乎有传言说\n"
	.string "有人目击到稀有的宝可梦。\p"
	.string "据说目击地点在\n"
	.string "103号道路的变化洞窟。\p"
	.string "也许你去调查一下\n"
	.string "这个传言是值得的。$"
