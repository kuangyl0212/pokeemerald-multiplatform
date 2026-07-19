SootopolisCity_House2_MapScripts::
	.byte 0

SootopolisCity_House2_EventScript_ExpertF::
	lock
	faceplayer
	msgbox SootopolisCity_House2_Text_DidYouKnowAboutMtPyreOrbs, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, SootopolisCity_House2_EventScript_KnowAboutOrbs
	call_if_eq VAR_RESULT, NO, SootopolisCity_House2_EventScript_DontKnowAboutOrbs
	release
	end

SootopolisCity_House2_EventScript_KnowAboutOrbs::
	msgbox SootopolisCity_House2_Text_YesTwoOrbsSideBySide, MSGBOX_DEFAULT
	return

SootopolisCity_House2_EventScript_DontKnowAboutOrbs::
	msgbox SootopolisCity_House2_Text_OughtToVisitAndSee, MSGBOX_DEFAULT
	return

SootopolisCity_House2_Text_DidYouKnowAboutMtPyreOrbs:
	.string "{CHN}送神山……\p"
	.string "在山顶有两颗宝珠并排\n"
	.string "摆放着。你知道吗？$"

SootopolisCity_House2_Text_YesTwoOrbsSideBySide:
	.string "{CHN}是的，两颗宝珠并排摆放……\p"
	.string "看到它们在一起的样子……\n"
	.string "总觉得令人心安……$"

SootopolisCity_House2_Text_OughtToVisitAndSee:
	.string "{CHN}是吗？\n"
	.string "你或许应该去看看……$"
