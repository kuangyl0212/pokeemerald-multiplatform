LilycoveCity_DepartmentStore_5F_MapScripts::
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LilycoveCity_DepartmentStore_5F_OnWarp
	.byte 0

/* During the abnormal weather from Kyogre/Groudon awakening the dept store rooftop is inaccessible*/
/* Likely done to avoid dealing with showing the weather. Technically the rooftop is indoors*/
LilycoveCity_DepartmentStore_5F_OnWarp:
	map_script_2 VAR_SOOTOPOLIS_CITY_STATE, 1, LilycoveCity_DepartmentStore_5F_EventScript_BlockRoofStairs
	map_script_2 VAR_SOOTOPOLIS_CITY_STATE, 2, LilycoveCity_DepartmentStore_5F_EventScript_BlockRoofStairs
	map_script_2 VAR_SOOTOPOLIS_CITY_STATE, 3, LilycoveCity_DepartmentStore_5F_EventScript_BlockRoofStairs
	.short 0

LilycoveCity_DepartmentStore_5F_EventScript_BlockRoofStairs::
	setobjectxy LOCALID_DEPARTMENT_STORE_STAIRS_WOMAN, 16, 2
	turnobject LOCALID_DEPARTMENT_STORE_STAIRS_WOMAN, DIR_NORTH
	end

LilycoveCity_DepartmentStore_5F_EventScript_ClerkFarLeft::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration2 LilycoveCity_DepartmentStore_5F_Pokemart_Dolls
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_5F_Pokemart_Dolls:
	.short DECOR_PICHU_DOLL
	.short DECOR_PIKACHU_DOLL
	.short DECOR_MARILL_DOLL
	.short DECOR_JIGGLYPUFF_DOLL
	.short DECOR_DUSKULL_DOLL
	.short DECOR_WYNAUT_DOLL
	.short DECOR_BALTOY_DOLL
	.short DECOR_KECLEON_DOLL
	.short DECOR_AZURILL_DOLL
	.short DECOR_SKITTY_DOLL
	.short DECOR_SWABLU_DOLL
	.short DECOR_GULPIN_DOLL
	pokemartlistend

LilycoveCity_DepartmentStore_5F_EventScript_ClerkMidLeft::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration2 LilycoveCity_DepartmentStore_5F_Pokemart_Cushions
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_5F_Pokemart_Cushions:
	.short DECOR_PIKA_CUSHION
	.short DECOR_ROUND_CUSHION
	.short DECOR_ZIGZAG_CUSHION
	.short DECOR_SPIN_CUSHION
	.short DECOR_DIAMOND_CUSHION
	.short DECOR_BALL_CUSHION
	.short DECOR_GRASS_CUSHION
	.short DECOR_FIRE_CUSHION
	.short DECOR_WATER_CUSHION
	pokemartlistend

LilycoveCity_DepartmentStore_5F_EventScript_ClerkMidRight::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration2 LilycoveCity_DepartmentStore_5F_Pokemart_Posters
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_5F_Pokemart_Posters:
	.short DECOR_BALL_POSTER
	.short DECOR_GREEN_POSTER
	.short DECOR_RED_POSTER
	.short DECOR_BLUE_POSTER
	.short DECOR_CUTE_POSTER
	.short DECOR_PIKA_POSTER
	.short DECOR_LONG_POSTER
	.short DECOR_SEA_POSTER
	.short DECOR_SKY_POSTER
	pokemartlistend

LilycoveCity_DepartmentStore_5F_EventScript_ClerkFarRight::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration2 LilycoveCity_DepartmentStore_5F_Pokemart_Mats
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_5F_Pokemart_Mats:
	.short DECOR_SURF_MAT
	.short DECOR_THUNDER_MAT
	.short DECOR_FIRE_BLAST_MAT
	.short DECOR_POWDER_SNOW_MAT
	.short DECOR_ATTRACT_MAT
	.short DECOR_FISSURE_MAT
	.short DECOR_SPIKES_MAT
	.short DECOR_GLITTER_MAT
	.short DECOR_JUMP_MAT
	.short DECOR_SPIN_MAT
	pokemartlistend

LilycoveCity_DepartmentStore_5F_EventScript_PokefanF::
	msgbox LilycoveCity_DepartmentStore_5F_Text_PlaceFullOfCuteDolls, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_5F_EventScript_Woman::
	lockall
	applymovement LOCALID_DEPARTMENT_STORE_STAIRS_WOMAN, Common_Movement_FacePlayer
	waitmovement 0
	goto_if_eq VAR_SOOTOPOLIS_CITY_STATE, 0, LilycoveCity_DepartmentStore_5F_EventScript_WomanNormal
	goto_if_ge VAR_SOOTOPOLIS_CITY_STATE, 4, LilycoveCity_DepartmentStore_5F_EventScript_WomanNormal
	goto LilycoveCity_DepartmentStore_5F_EventScript_WomanLegendaryWeather
	end

LilycoveCity_DepartmentStore_5F_EventScript_WomanNormal::
	msgbox LilycoveCity_DepartmentStore_5F_Text_SellManyCuteMatsHere, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

LilycoveCity_DepartmentStore_5F_EventScript_WomanLegendaryWeather::
	msgbox LilycoveCity_DepartmentStore_5F_Text_ClosedRooftopForWeather, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEPARTMENT_STORE_STAIRS_WOMAN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	releaseall
	end

LilycoveCity_DepartmentStore_5F_EventScript_LittleGirl::
	msgbox LilycoveCity_DepartmentStore_5F_Text_GettingDollInsteadOfPokemon, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_5F_Text_PlaceFullOfCuteDolls:
	.string "{CHN}这里到处都是可爱的布偶。\p"
	.string "我也该给自己买些，\n"
	.string "而不是只给孩子们买。$"

LilycoveCity_DepartmentStore_5F_Text_GettingDollInsteadOfPokemon:
	.string "{CHN}我还太小，还不能养宝可梦，\n"
	.string "所以我要一个可爱的布偶代替。$"

LilycoveCity_DepartmentStore_5F_Text_SellManyCuteMatsHere:
	.string "{CHN}这里卖很多可爱的地垫。\p"
	.string "我该选哪个好呢？\n"
	.string "要不全部买下来吧……$"

LilycoveCity_DepartmentStore_5F_Text_ClosedRooftopForWeather:
	.string "{CHN}我想他们关闭了屋顶\n"
	.string "是因为今天天气太糟了。$"
