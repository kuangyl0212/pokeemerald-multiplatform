PacifidlogTown_House4_MapScripts::
	.byte 0

PacifidlogTown_House4_EventScript_LittleGirl::
	msgbox PacifidlogTown_House4_Text_SkyPokemon, MSGBOX_NPC
	end

PacifidlogTown_House4_EventScript_Woman::
	msgbox PacifidlogTown_House4_Text_PeopleSawHighFlyingPokemon, MSGBOX_NPC
	end

PacifidlogTown_House4_EventScript_Boy::
	lock
	faceplayer
	msgbox PacifidlogTown_House4_Text_WhereDidYouComeFrom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PacifidlogTown_House4_EventScript_Yes
	goto_if_eq VAR_RESULT, NO, PacifidlogTown_House4_EventScript_No
	end

PacifidlogTown_House4_EventScript_Yes::
	msgbox PacifidlogTown_House4_Text_YesTown, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House4_EventScript_No::
	msgbox PacifidlogTown_House4_Text_YouHaveToComeFromSomewhere, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House4_Text_PeopleSawHighFlyingPokemon:
	.string "{CHN}人们说他们看到一只宝可梦\n"
	.string "在丰缘上空高高飞翔。\p"
	.string "它一直都在飞吗？\n"
	.string "难道它不需要在哪里休息一下吗？$"

PacifidlogTown_House4_Text_SkyPokemon:
	.string "{CHN}天空宝可梦！\n"
	.string "天空宝可梦！$"

PacifidlogTown_House4_Text_WhereDidYouComeFrom:
	.string "{CHN}你从哪里来的？$"

PacifidlogTown_House4_Text_YesTown:
	.string "{CHN}是吗？\n"
	.string "“是”镇？\p"
	.string "我从没听说过这种地方。$"

PacifidlogTown_House4_Text_YouHaveToComeFromSomewhere:
	.string "{CHN}不是？那说不通啊。\n"
	.string "你总得从某个地方来吧。\p"
	.string "哦！等等！你该不会想说\n"
	.string "你出生在海底吧？$"
