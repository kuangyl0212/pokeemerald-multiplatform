RustboroCity_House3_MapScripts::
	.byte 0

RustboroCity_House3_EventScript_OldMan::
	msgbox RustboroCity_House3_Text_IGivePerfectlySuitedNicknames, MSGBOX_NPC
	end

RustboroCity_House3_EventScript_OldWoman::
	msgbox RustboroCity_House3_Text_NamingPikachuPekachu, MSGBOX_NPC
	end

/* Misspelling on purpose, see nickname*/
RustboroCity_House3_EventScript_Pekachu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
	msgbox RustboroCity_House3_Text_Pekachu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RustboroCity_House3_Text_IGivePerfectlySuitedNicknames:
	.string "{CHN}我给自己的宝可梦起了\n"
	.string "非常适合它们的绰号！\p"
	.string "这是我表达，嗯……\n"
	.string "创意的方式，对，就是这样！$"

RustboroCity_House3_Text_NamingPikachuPekachu:
	.string "{CHN}但是给皮卡丘\n"
	.string "起名叫PEKACHU？似乎毫无意义。\p"
	.string "我觉得用容易理解的名字\n"
	.string "是好事，不过……$"

RustboroCity_House3_Text_Pekachu:
	.string "{CHN}PEKACHU：皮卡！$"

