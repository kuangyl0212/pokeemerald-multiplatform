MtPyre_5F_MapScripts::
	.byte 0

/* Seems like the scripts for the 4F and 5F were swapped*/

MtPyre_4F_EventScript_Tasha::
	trainerbattle_single TRAINER_TASHA, MtPyre_4F_Text_TashaIntro, MtPyre_4F_Text_TashaDefeat
	msgbox MtPyre_4F_Text_TashaPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_4F_Text_TashaIntro:
	.string "{CHN}我喜欢一切可怕的东西……\n"
	.string "就像一种病……\p"
	.string "当我在这里时……\n"
	.string "我会因恐惧而战栗……$"

MtPyre_4F_Text_TashaDefeat:
	.string "{CHN}输了，我不喜欢……$"

MtPyre_4F_Text_TashaPostBattle:
	.string "{CHN}我想看到可怕的东西……\n"
	.string "我离不开……\p"
	.string "留下……\n"
	.string "你不愿意留下陪我吗？$"

