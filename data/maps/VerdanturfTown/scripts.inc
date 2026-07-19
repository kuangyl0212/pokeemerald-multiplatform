VerdanturfTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_OnTransition
	.byte 0

VerdanturfTown_OnTransition:
	setflag FLAG_VISITED_VERDANTURF_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	end

VerdanturfTown_EventScript_Twin::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_TwinTunnelOpen
	msgbox VerdanturfTown_Text_ManTryingToDigTunnel, MSGBOX_DEFAULT
	applymovement LOCALID_VERDANTURF_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_TwinTunnelOpen::
	msgbox VerdanturfTown_Text_ManDugTunnelForLove, MSGBOX_DEFAULT
	applymovement LOCALID_VERDANTURF_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_Man::
	msgbox VerdanturfTown_Text_AirCleanHere, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Camper::
	msgbox VerdanturfTown_Text_MakeBattleTentDebut, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_BoyTunnelOpen
	msgbox VerdanturfTown_Text_GuyTryingToBustThroughCave, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_BoyTunnelOpen::
	msgbox VerdanturfTown_Text_EasyToGetToRustboroNow, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_TownSign::
	msgbox VerdanturfTown_Text_TownSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_WandasHouseSign::
	msgbox VerdanturfTown_Text_WandasHouse, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_BattleTentSign::
	msgbox VerdanturfTown_Text_BattleTentSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_RusturfTunnelSign::
	msgbox VerdanturfTown_Text_RusturfTunnelSign, MSGBOX_SIGN
	end

VerdanturfTown_Text_ManTryingToDigTunnel:
	.string "{CHN}我爸爸告诉过我。\p"
	.string "他说这条隧道里满是\n"
	.string "胆小的宝可梦。\p"
	.string "它们一听到大的响声就会害怕，\n"
	.string "并引起大骚动。\p"
	.string "所以他们不得不停止大型隧道\n"
	.string "工程。\p"
	.string "但有一个人，他正试图独自\n"
	.string "挖通这条隧道！$"

VerdanturfTown_Text_ManDugTunnelForLove:
	.string "{CHN}有个男人为了他爱的女士\n"
	.string "挖了一条隧道。\p"
	.string "我不太懂，但是，嘿！$"

VerdanturfTown_Text_AirCleanHere:
	.string "{CHN}由于风吹的方向，火山灰\n"
	.string "从不会被吹到这边来。\p"
	.string "这里的空气清新怡人。\n"
	.string "住在这里即使对体弱多病的人\l"
	.string "也会有奇效。$"

VerdanturfTown_Text_MakeBattleTentDebut:
	.string "{CHN}我的宝可梦和我，我们正保持着\n"
	.string "连胜的势头。\p"
	.string "所以我决定在这个镇上的对战帐篷\n"
	.string "初次登场。$"

VerdanturfTown_Text_GuyTryingToBustThroughCave:
	.string "{CHN}你看到宝可梦商店旁边的\n"
	.string "那个洞穴了吗？\p"
	.string "里面有个人正试图\n"
	.string "砸碎石块，好冲到\l"
	.string "另一边去。\p"
	.string "如果我们能穿过去就好了…\n"
	.string "那样去橙华市就方便了。$"

VerdanturfTown_Text_EasyToGetToRustboroNow:
	.string "{CHN}宝可梦商店旁边的那个洞穴\n"
	.string "现在变成了通往另一边的隧道。\p"
	.string "太棒了——现在去橙华市\n"
	.string "购买新的得文产品很方便。$"

VerdanturfTown_Text_TownSign:
	.string "{CHN}绿荫镇\p"
	.string "“风吹拂的高地，\n"
	.string "飘荡着青草的甜蜜芬芳。”$"

VerdanturfTown_Text_WandasHouse:
	.string "{CHN}琳达的家$"

VerdanturfTown_Text_BattleTentSign:
	.string "{CHN}对战帐篷 绿荫镇会场\n"
	.string "“大饱眼福的对战！”$"

VerdanturfTown_Text_RusturfTunnelSign:
	.string "{CHN}橙华隧道\n"
	.string "“连接橙华市和绿荫镇”\p"
	.string "“隧道工程已\n"
	.string "取消。”$"

