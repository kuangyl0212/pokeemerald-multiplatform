ProfileMan_EventScript_Man::
	lock
	faceplayer
	goto_if_set FLAG_SYS_CHAT_USED, ProfileMan_EventScript_GivenProfileBefore
	msgbox ProfileMan_Text_CollectTrainerProfiles, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeProfile
	end

ProfileMan_EventScript_AskToSeeProfile::
	msgbox ProfileMan_Text_MayISeeYourProfile, MSGBOX_DEFAULT
	multichoice 17, 6, MULTI_YESNOINFO_2, FALSE
	switch VAR_RESULT
	case 0, ProfileMan_EventScript_CreateProfile
	case 1, ProfileMan_EventScript_DeclineShowProfile
	case 2, ProfileMan_EventScript_Info
	case MULTI_B_PRESSED, ProfileMan_EventScript_DeclineShowProfile
	end

ProfileMan_EventScript_Info::
	msgbox ProfileMan_Text_EasyChatExplanation, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeProfile
	end

ProfileMan_EventScript_CreateProfile::
	msgbox ProfileMan_Text_LetsSeeItThen, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, EASY_CHAT_TYPE_PROFILE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, 0, ProfileMan_EventScript_CancelShowProfile
	goto_if_eq VAR_RESULT, 1, ProfileMan_EventScript_ShowProfile
	end

ProfileMan_EventScript_CancelShowProfile::
	msgbox ProfileMan_Text_NotIntoItRightNow, MSGBOX_DEFAULT
	release
	end

ProfileMan_EventScript_ShowProfile::
	setvar VAR_0x8004, 0
	special ShowEasyChatProfile
	waitmessage
	delay 80
	msgbox ProfileMan_Text_FantasticProfile, MSGBOX_DEFAULT
	release
	end

ProfileMan_EventScript_DeclineShowProfile::
	msgbox ProfileMan_Text_ImagineYouWouldHaveWonderfulProfile, MSGBOX_DEFAULT
	release
	end

ProfileMan_EventScript_GivenProfileBefore::
	msgbox ProfileMan_Text_YouHaveWonderfulSmile, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeNewProfile
	end

ProfileMan_EventScript_AskToSeeNewProfile::
	msgbox ProfileMan_Text_MayISeeYourNewProfile, MSGBOX_DEFAULT
	multichoice 17, 6, MULTI_YESNOINFO_2, FALSE
	switch VAR_RESULT
	case 0, ProfileMan_EventScript_CreateNewProfile
	case 1, ProfileMan_EventScript_DeclineNewProfile
	case 2, ProfileMan_EventScript_InfoNewProfile
	case MULTI_B_PRESSED, ProfileMan_EventScript_DeclineNewProfile
	end

ProfileMan_EventScript_InfoNewProfile::
	msgbox ProfileMan_Text_EasyChatExplanation, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeNewProfile
	end

ProfileMan_EventScript_CreateNewProfile::
	msgbox ProfileMan_Text_EvenBetterThanLastProfile, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, EASY_CHAT_TYPE_PROFILE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, 0, ProfileMan_EventScript_CancelShowProfile
	goto_if_eq VAR_RESULT, 1, ProfileMan_EventScript_ShowProfile
	end

ProfileMan_EventScript_DeclineNewProfile::
	msgbox ProfileMan_Text_LikeProfileWayItIs, MSGBOX_DEFAULT
	release
	end

/* Unused*/
ProfileMan_EventScript_Ret::
	return

ProfileMan_Text_CollectTrainerProfiles:
	.string "{CHN}你好啊，训练家！\n"
	.string "你的笑容真棒。\p"
	.string "我有一个爱好——收集\n"
	.string "宝可梦训练家的个人档案。$"

ProfileMan_Text_MayISeeYourProfile:
	.string "{CHN}那么，怎么样？\n"
	.string "我可以看看你的个人档案吗？$"

ProfileMan_Text_EasyChatExplanation:
	.string "{CHN}你可以通过组合四个词语或短语\n"
	.string "来制作自己的个人档案。\p"
	.string "来，我用一个\n"
	.string "由四个文字片段组成的个人档案示例展示给你看。\p"
	.string "你可以用其他文字片段\n"
	.string "替换这四个文字片段，\l"
	.string "随心所欲地制作你自己的个人档案。\p"
	.string "有很多文字片段\n"
	.string "可以使用。\p"
	.string "它们按照宝可梦、\n"
	.string "生活方式和爱好等分组，\l"
	.string "便于查找。\p"
	.string "那么，首先选择一个文字片段组\n"
	.string "来显示选择列表。\p"
	.string "然后，选择你想要的选项。\p"
	.string "对剩余的文字选择重复此操作，\n"
	.string "你就拥有了自己的个人档案。$"

ProfileMan_Text_LetsSeeItThen:
	.string "{CHN}好的！谢谢你！\n"
	.string "那么，让我看看吧。$"

ProfileMan_Text_ImagineYouWouldHaveWonderfulProfile:
	.string "{CHN}哦，真的吗？\p"
	.string "我想像你这样的人应该有\n"
	.string "很棒的个人档案……$"

ProfileMan_Text_NotIntoItRightNow:
	.string "{CHN}哦？你现在没兴趣？\p"
	.string "那么，任何时候我都可以！$"

ProfileMan_Text_YouHaveWonderfulSmile:
	.string "{CHN}你好啊，训练家！\n"
	.string "你的笑容真棒。$"

ProfileMan_Text_MayISeeYourNewProfile:
	.string "{CHN}我可以看看你的新个人档案吗？$"

ProfileMan_Text_EvenBetterThanLastProfile:
	.string "{CHN}好的！谢谢你！\p"
	.string "希望它比你之前\n"
	.string "给我看的个人档案更好。$"

ProfileMan_Text_LikeProfileWayItIs:
	.string "{CHN}哦，你喜欢你的个人档案现在的样子。\p"
	.string "我不怪你——它现在\n"
	.string "就是一个很棒的个人档案。$"

ProfileMan_Text_FantasticProfile:
	.string "{CHN}太……太棒了！\p"
	.string "你的个人档案，真精彩！\n"
	.string "它真的表达了你的特点。\p"
	.string "哎呀，任何听到这个个人档案的人\n"
	.string "都会被你迷住！\p"
	.string "谢谢你！$"

/* Unused*/
ProfileMan_Text_YouKnowSecretSaying:
	.string "{CHN}哦？\n"
	.string "你知道秘密暗语！\p"
	.string "这意味着你现在是我的了神秘事件俱乐部\n"
	.string "的会员了！$"
