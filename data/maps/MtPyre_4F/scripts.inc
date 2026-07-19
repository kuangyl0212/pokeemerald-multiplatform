MtPyre_4F_MapScripts::
	.byte 0

/* Seems like the scripts for the 4F and 5F were swapped*/

MtPyre_5F_EventScript_Atsushi::
	trainerbattle_single TRAINER_ATSUSHI, MtPyre_5F_Text_AtsushiIntro, MtPyre_5F_Text_AtsushiDefeat
	msgbox MtPyre_5F_Text_AtsushiPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_5F_Text_AtsushiIntro:
	.string "{CHN}老师……\n"
	.string "请见证我的成长！$"

MtPyre_5F_Text_AtsushiDefeat:
	.string "{CHN}老师……\n"
	.string "请原谅我！$"

MtPyre_5F_Text_AtsushiPostBattle:
	.string "{CHN}在我不长进之前，\n"
	.string "安息在这里的老师永远无法真正安息……$"

