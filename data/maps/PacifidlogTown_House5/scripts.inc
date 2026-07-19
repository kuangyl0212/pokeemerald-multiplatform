PacifidlogTown_House5_MapScripts::
	.byte 0

PacifidlogTown_House5_EventScript_MirageIslandWatcher::
	lock
	faceplayer
	specialvar VAR_RESULT, IsMirageIslandPresent
	goto_if_eq VAR_RESULT, TRUE, PacifidlogTown_House5_EventScript_MirageIslandPresent
	msgbox PacifidlogTown_House5_Text_CantSeeMirageIslandToday, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House5_EventScript_MirageIslandPresent::
	msgbox PacifidlogTown_House5_Text_CanSeeMirageIslandToday, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House5_EventScript_Gentleman::
	msgbox PacifidlogTown_House5_Text_MirageIslandAppearDependingOnWeather, MSGBOX_NPC
	end

PacifidlogTown_House5_Text_CantSeeMirageIslandToday:
	.string "{CHN}今天我看不到幻之岛……$"

PacifidlogTown_House5_Text_CanSeeMirageIslandToday:
	.string "{CHN}哦！天哪！\n"
	.string "今天我能看到幻之岛了！$"

PacifidlogTown_House5_Text_MirageIslandAppearDependingOnWeather:
	.string "{CHN}幻之岛……\p"
	.string "它一定是根据产生海市蜃楼的\n"
	.string "天气条件\l"
	.string "而时隐时现的。\p"
	.string "还是说它真的在出现和\n"
	.string "消失？$"
