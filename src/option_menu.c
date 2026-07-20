#include "global.h"
#include "option_menu.h"
#include "bg.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "main.h"
#include "menu.h"
#include "palette.h"
#include "platform.h"
#include "scanline_effect.h"
#include "sprite.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "gba/m4a_internal.h"
#include "constants/rgb.h"

#define tMenuSelection data[0]
#define tTextSpeed data[1]
#define tBattleSceneOff data[2]
#define tBattleStyle data[3]
#define tSound data[4]
#define tButtonMode data[5]
#define tWindowFrameType data[6]
#define tBorderBackground data[7]
#define tPlatformPage data[8]
#define tFullscreen data[9]
#define tWindowScale data[10]
#define tIntegerScale data[11]
#define tVSync data[12]
#define tBorderFrame data[13]
#define tVolume data[14]
#define tDisplayMode data[15]

#define OPTION_ROW_HEIGHT 14

enum
{
    MENUITEM_TEXTSPEED,
    MENUITEM_BATTLESCENE,
    MENUITEM_BATTLESTYLE,
    MENUITEM_SOUND,
    MENUITEM_BUTTONMODE,
    MENUITEM_FRAMETYPE,
    MENUITEM_DISPLAY,
    MENUITEM_CANCEL,
    MENUITEM_COUNT,
};

enum
{
    WIN_HEADER,
    WIN_OPTIONS
};

#define YPOS_TEXTSPEED       (MENUITEM_TEXTSPEED * OPTION_ROW_HEIGHT)
#define YPOS_BATTLESCENE     (MENUITEM_BATTLESCENE * OPTION_ROW_HEIGHT)
#define YPOS_BATTLESTYLE     (MENUITEM_BATTLESTYLE * OPTION_ROW_HEIGHT)
#define YPOS_SOUND           (MENUITEM_SOUND * OPTION_ROW_HEIGHT)
#define YPOS_BUTTONMODE      (MENUITEM_BUTTONMODE * OPTION_ROW_HEIGHT)
#define YPOS_FRAMETYPE       (MENUITEM_FRAMETYPE * OPTION_ROW_HEIGHT)
#define YPOS_DISPLAY          (MENUITEM_DISPLAY * OPTION_ROW_HEIGHT)

enum
{
#ifndef __ANDROID__
    DISPLAY_FULLSCREEN,
    DISPLAY_WINDOW_SCALE,
    DISPLAY_INTEGER_SCALE,
    DISPLAY_VSYNC,
#else
    DISPLAY_DISPLAY_MODE, // Android：显示模式（最大化/点对点）
#endif
    DISPLAY_BORDER_FRAME,
    DISPLAY_BACKGROUND,
    DISPLAY_VOLUME,
    DISPLAY_BACK,
    DISPLAY_COUNT,
};

static void Task_OptionMenuFadeIn(u8 taskId);
static void Task_OptionMenuProcessInput(u8 taskId);
static void Task_OptionMenuSave(u8 taskId);
static void Task_OptionMenuFadeOut(u8 taskId);
static void HighlightOptionMenuItem(u8 selection);
static u8 TextSpeed_ProcessInput(u8 selection);
static void TextSpeed_DrawChoices(u8 selection);
static u8 BattleScene_ProcessInput(u8 selection);
static void BattleScene_DrawChoices(u8 selection);
static u8 BattleStyle_ProcessInput(u8 selection);
static void BattleStyle_DrawChoices(u8 selection);
static u8 Sound_ProcessInput(u8 selection);
static void Sound_DrawChoices(u8 selection);
static u8 FrameType_ProcessInput(u8 selection);
static void FrameType_DrawChoices(u8 selection);
static u8 ButtonMode_ProcessInput(u8 selection);
static void ButtonMode_DrawChoices(u8 selection);
static u8 BorderBackground_ProcessInput(u8 selection);
static void BorderBackground_DrawChoices(u8 selection);
static u8 GetBorderBackgroundCount(void);
static u8 GetBorderBackground(void);
static void SetBorderBackground(u8 selection);
static void OpenDisplaySettings(u8 taskId);
static void CloseDisplaySettings(u8 taskId);
static void ProcessDisplaySettingsInput(u8 taskId);
static void DrawDisplaySettings(u8 taskId);
static void DrawDisplaySettingChoice(u8 row, const u8 *text);
static void DrawHeaderText(void);
static void DrawOptionMenuTexts(void);
static void DrawBgWindowFrames(void);

EWRAM_DATA static bool8 sArrowPressed = FALSE;

static const u16 sOptionMenuText_Pal[] = INCBIN_U16("graphics/interface/option_menu_text.gbapal");
// note: this is only used in the Japanese release
static const u8 sEqualSignGfx[] = INCBIN_U8("graphics/interface/option_menu_equals_sign.4bpp");

static const u8 *const sOptionMenuItemsNames[MENUITEM_COUNT] =
{
    [MENUITEM_TEXTSPEED]   = gText_TextSpeed,
    [MENUITEM_BATTLESCENE] = gText_BattleScene,
    [MENUITEM_BATTLESTYLE] = gText_BattleStyle,
    [MENUITEM_SOUND]       = gText_Sound,
    [MENUITEM_BUTTONMODE]  = gText_ButtonMode,
    [MENUITEM_FRAMETYPE]   = gText_Frame,
    [MENUITEM_DISPLAY]       = gText_DisplaySettings,
    [MENUITEM_CANCEL]      = gText_OptionMenuCancel,
};

static const struct WindowTemplate sOptionMenuWinTemplates[] =
{
    [WIN_HEADER] = {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 1,
        .width = 26,
        .height = 2,
        .paletteNum = 1,
        .baseBlock = 2
    },
    [WIN_OPTIONS] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 5,
        .width = 26,
        .height = 14,
        .paletteNum = 1,
        .baseBlock = 0x36
    },
    DUMMY_WIN_TEMPLATE
};

static const struct BgTemplate sOptionMenuBgTemplates[] =
{
    {
        .bg = 1,
        .charBaseIndex = 1,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 0,
        .charBaseIndex = 1,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    }
};

static const u16 sOptionMenuBg_Pal[] = {RGB(17, 18, 31)};

static void MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_InitOptionMenu(void)
{
    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        gMain.state++;
        break;
    case 1:
        DmaClearLarge16(3, (void *)(VRAM), VRAM_SIZE, 0x1000);
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sOptionMenuBgTemplates, ARRAY_COUNT(sOptionMenuBgTemplates));
        ChangeBgX(0, 0, BG_COORD_SET);
        ChangeBgY(0, 0, BG_COORD_SET);
        ChangeBgX(1, 0, BG_COORD_SET);
        ChangeBgY(1, 0, BG_COORD_SET);
        ChangeBgX(2, 0, BG_COORD_SET);
        ChangeBgY(2, 0, BG_COORD_SET);
        ChangeBgX(3, 0, BG_COORD_SET);
        ChangeBgY(3, 0, BG_COORD_SET);
        InitWindows(sOptionMenuWinTemplates);
        DeactivateAllTextPrinters();
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG0);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG1 | WINOUT_WIN01_CLR);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_DARKEN);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 4);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        gMain.state++;
        break;
    case 2:
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        gMain.state++;
        break;
    case 3:
        LoadBgTiles(1, GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->tiles, 0x120, 0x1A2);
        gMain.state++;
        break;
    case 4:
        LoadPalette(sOptionMenuBg_Pal, BG_PLTT_ID(0), sizeof(sOptionMenuBg_Pal));
        LoadPalette(GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->pal, BG_PLTT_ID(7), PLTT_SIZE_4BPP);
        gMain.state++;
        break;
    case 5:
        LoadPalette(sOptionMenuText_Pal, BG_PLTT_ID(1), sizeof(sOptionMenuText_Pal));
        gMain.state++;
        break;
    case 6:
        PutWindowTilemap(WIN_HEADER);
        DrawHeaderText();
        gMain.state++;
        break;
    case 7:
        gMain.state++;
        break;
    case 8:
        PutWindowTilemap(WIN_OPTIONS);
        DrawOptionMenuTexts();
        gMain.state++;
    case 9:
        DrawBgWindowFrames();
        gMain.state++;
        break;
    case 10:
    {
        u8 taskId = CreateTask(Task_OptionMenuFadeIn, 0);

        gTasks[taskId].tMenuSelection = 0;
        gTasks[taskId].tTextSpeed = gSaveBlock2Ptr->optionsTextSpeed;
        gTasks[taskId].tBattleSceneOff = gSaveBlock2Ptr->optionsBattleSceneOff;
        gTasks[taskId].tBattleStyle = gSaveBlock2Ptr->optionsBattleStyle;
        gTasks[taskId].tSound = gSaveBlock2Ptr->optionsSound;
        gTasks[taskId].tButtonMode = gSaveBlock2Ptr->optionsButtonMode;
        gTasks[taskId].tWindowFrameType = gSaveBlock2Ptr->optionsWindowFrameType;
        gTasks[taskId].tBorderBackground = GetBorderBackground();
        if (gTasks[taskId].tBorderBackground >= GetBorderBackgroundCount())
            gTasks[taskId].tBorderBackground = 0;
#ifdef PLATFORM_SDL2
        gTasks[taskId].tFullscreen = Platform_GetSetting(PLATFORM_SETTING_FULLSCREEN);
        gTasks[taskId].tWindowScale = Platform_GetSetting(PLATFORM_SETTING_WINDOW_SCALE);
        gTasks[taskId].tIntegerScale = Platform_GetSetting(PLATFORM_SETTING_INTEGER_SCALE);
        gTasks[taskId].tVSync = Platform_GetSetting(PLATFORM_SETTING_VSYNC);
        gTasks[taskId].tBorderFrame = Platform_GetSetting(PLATFORM_SETTING_BORDER);
        gTasks[taskId].tVolume = Platform_GetSetting(PLATFORM_SETTING_VOLUME);
#ifdef __ANDROID__
        gTasks[taskId].tDisplayMode = Platform_GetSetting(PLATFORM_SETTING_DISPLAY_MODE);
#endif
#else
        gTasks[taskId].tWindowScale = 4;
        gTasks[taskId].tBorderFrame = 1;
        gTasks[taskId].tVolume = 10;
#endif

        TextSpeed_DrawChoices(gTasks[taskId].tTextSpeed);
        BattleScene_DrawChoices(gTasks[taskId].tBattleSceneOff);
        BattleStyle_DrawChoices(gTasks[taskId].tBattleStyle);
        Sound_DrawChoices(gTasks[taskId].tSound);
        ButtonMode_DrawChoices(gTasks[taskId].tButtonMode);
        FrameType_DrawChoices(gTasks[taskId].tWindowFrameType);
        HighlightOptionMenuItem(gTasks[taskId].tMenuSelection);

        CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
        gMain.state++;
        break;
    }
    case 11:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        SetVBlankCallback(VBlankCB);
        SetMainCallback2(MainCB2);
        return;
    }
}

static void Task_OptionMenuFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_OptionMenuProcessInput;
}

static void Task_OptionMenuProcessInput(u8 taskId)
{
    if (gTasks[taskId].tPlatformPage)
    {
        ProcessDisplaySettingsInput(taskId);
        return;
    }

    if (JOY_NEW(A_BUTTON))
    {
        if (gTasks[taskId].tMenuSelection == MENUITEM_CANCEL)
            gTasks[taskId].func = Task_OptionMenuSave;
        else if (gTasks[taskId].tMenuSelection == MENUITEM_DISPLAY)
            OpenDisplaySettings(taskId);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        gTasks[taskId].func = Task_OptionMenuSave;
    }
    else if (JOY_NEW(DPAD_UP))
    {
        if (gTasks[taskId].tMenuSelection > 0)
            gTasks[taskId].tMenuSelection--;
        else
            gTasks[taskId].tMenuSelection = MENUITEM_CANCEL;
        HighlightOptionMenuItem(gTasks[taskId].tMenuSelection);
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        if (gTasks[taskId].tMenuSelection < MENUITEM_CANCEL)
            gTasks[taskId].tMenuSelection++;
        else
            gTasks[taskId].tMenuSelection = 0;
        HighlightOptionMenuItem(gTasks[taskId].tMenuSelection);
    }
    else
    {
        u8 previousOption;

        switch (gTasks[taskId].tMenuSelection)
        {
        case MENUITEM_TEXTSPEED:
            previousOption = gTasks[taskId].tTextSpeed;
            gTasks[taskId].tTextSpeed = TextSpeed_ProcessInput(gTasks[taskId].tTextSpeed);

            if (previousOption != gTasks[taskId].tTextSpeed)
                TextSpeed_DrawChoices(gTasks[taskId].tTextSpeed);
            break;
        case MENUITEM_BATTLESCENE:
            previousOption = gTasks[taskId].tBattleSceneOff;
            gTasks[taskId].tBattleSceneOff = BattleScene_ProcessInput(gTasks[taskId].tBattleSceneOff);

            if (previousOption != gTasks[taskId].tBattleSceneOff)
                BattleScene_DrawChoices(gTasks[taskId].tBattleSceneOff);
            break;
        case MENUITEM_BATTLESTYLE:
            previousOption = gTasks[taskId].tBattleStyle;
            gTasks[taskId].tBattleStyle = BattleStyle_ProcessInput(gTasks[taskId].tBattleStyle);

            if (previousOption != gTasks[taskId].tBattleStyle)
                BattleStyle_DrawChoices(gTasks[taskId].tBattleStyle);
            break;
        case MENUITEM_SOUND:
            previousOption = gTasks[taskId].tSound;
            gTasks[taskId].tSound = Sound_ProcessInput(gTasks[taskId].tSound);

            if (previousOption != gTasks[taskId].tSound)
                Sound_DrawChoices(gTasks[taskId].tSound);
            break;
        case MENUITEM_BUTTONMODE:
            previousOption = gTasks[taskId].tButtonMode;
            gTasks[taskId].tButtonMode = ButtonMode_ProcessInput(gTasks[taskId].tButtonMode);

            if (previousOption != gTasks[taskId].tButtonMode)
                ButtonMode_DrawChoices(gTasks[taskId].tButtonMode);
            break;
        case MENUITEM_FRAMETYPE:
            previousOption = gTasks[taskId].tWindowFrameType;
            gTasks[taskId].tWindowFrameType = FrameType_ProcessInput(gTasks[taskId].tWindowFrameType);

            if (previousOption != gTasks[taskId].tWindowFrameType)
                FrameType_DrawChoices(gTasks[taskId].tWindowFrameType);
            break;
        default:
            return;
        }

        if (sArrowPressed)
        {
            sArrowPressed = FALSE;
            CopyWindowToVram(WIN_OPTIONS, COPYWIN_GFX);
        }
    }
}

static void Task_OptionMenuSave(u8 taskId)
{
    gSaveBlock2Ptr->optionsTextSpeed = gTasks[taskId].tTextSpeed;
    gSaveBlock2Ptr->optionsBattleSceneOff = gTasks[taskId].tBattleSceneOff;
    gSaveBlock2Ptr->optionsBattleStyle = gTasks[taskId].tBattleStyle;
    gSaveBlock2Ptr->optionsSound = gTasks[taskId].tSound;
    gSaveBlock2Ptr->optionsButtonMode = gTasks[taskId].tButtonMode;
    gSaveBlock2Ptr->optionsWindowFrameType = gTasks[taskId].tWindowFrameType;
    gSaveBlock2Ptr->optionsBorderBackground = gTasks[taskId].tBorderBackground;
    SetBorderBackground(gTasks[taskId].tBorderBackground);

    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    gTasks[taskId].func = Task_OptionMenuFadeOut;
}

static void Task_OptionMenuFadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        FreeAllWindowBuffers();
        SetMainCallback2(gMain.savedCallback);
    }
}

static void HighlightOptionMenuItem(u8 index)
{
    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(16, DISPLAY_WIDTH - 16));
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(index * OPTION_ROW_HEIGHT + 40, index * OPTION_ROW_HEIGHT + 54));
}

static void DrawOptionMenuChoice(const u8 *text, u8 x, u8 y, u8 style)
{
    u8 dst[16];
    u16 i;

    for (i = 0; *text != EOS && i < ARRAY_COUNT(dst) - 1; i++)
        dst[i] = *(text++);

    if (style != 0)
    {
        dst[2] = TEXT_COLOR_RED;
        dst[5] = TEXT_COLOR_LIGHT_RED;
    }

    dst[i] = EOS;
    AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, dst, x, y + 1, TEXT_SKIP_DRAW, NULL);
}

static u8 TextSpeed_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (selection <= 1)
            selection++;
        else
            selection = 0;

        sArrowPressed = TRUE;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (selection != 0)
            selection--;
        else
            selection = 2;

        sArrowPressed = TRUE;
    }
    return selection;
}

static void TextSpeed_DrawChoices(u8 selection)
{
    u8 styles[3];
    s32 widthSlow, widthMid, widthFast, xMid;

    styles[0] = 0;
    styles[1] = 0;
    styles[2] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_TextSpeedSlow, 104, YPOS_TEXTSPEED, styles[0]);

    widthSlow = GetStringWidth(FONT_NORMAL, gText_TextSpeedSlow, 0);
    widthMid = GetStringWidth(FONT_NORMAL, gText_TextSpeedMid, 0);
    widthFast = GetStringWidth(FONT_NORMAL, gText_TextSpeedFast, 0);

    widthMid -= 94;
    xMid = (widthSlow - widthMid - widthFast) / 2 + 104;
    DrawOptionMenuChoice(gText_TextSpeedMid, xMid, YPOS_TEXTSPEED, styles[1]);

    DrawOptionMenuChoice(gText_TextSpeedFast, GetStringRightAlignXOffset(FONT_NORMAL, gText_TextSpeedFast, 198), YPOS_TEXTSPEED, styles[2]);
}

static u8 BattleScene_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }

    return selection;
}

static void BattleScene_DrawChoices(u8 selection)
{
    u8 styles[2];

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_BattleSceneOn, 104, YPOS_BATTLESCENE, styles[0]);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(FONT_NORMAL, gText_BattleSceneOff, 198), YPOS_BATTLESCENE, styles[1]);
}

static u8 BattleStyle_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }

    return selection;
}

static void BattleStyle_DrawChoices(u8 selection)
{
    u8 styles[2];

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_BattleStyleShift, 104, YPOS_BATTLESTYLE, styles[0]);
    DrawOptionMenuChoice(gText_BattleStyleSet, GetStringRightAlignXOffset(FONT_NORMAL, gText_BattleStyleSet, 198), YPOS_BATTLESTYLE, styles[1]);
}

static u8 Sound_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        SetPokemonCryStereo(selection);
        sArrowPressed = TRUE;
    }

    return selection;
}

static void Sound_DrawChoices(u8 selection)
{
    u8 styles[2];

    styles[0] = 0;
    styles[1] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_SoundMono, 104, YPOS_SOUND, styles[0]);
    DrawOptionMenuChoice(gText_SoundStereo, GetStringRightAlignXOffset(FONT_NORMAL, gText_SoundStereo, 198), YPOS_SOUND, styles[1]);
}

static u8 FrameType_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (selection < WINDOW_FRAMES_COUNT - 1)
            selection++;
        else
            selection = 0;

        LoadBgTiles(1, GetWindowFrameTilesPal(selection)->tiles, 0x120, 0x1A2);
        LoadPalette(GetWindowFrameTilesPal(selection)->pal, BG_PLTT_ID(7), PLTT_SIZE_4BPP);
        sArrowPressed = TRUE;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (selection != 0)
            selection--;
        else
            selection = WINDOW_FRAMES_COUNT - 1;

        LoadBgTiles(1, GetWindowFrameTilesPal(selection)->tiles, 0x120, 0x1A2);
        LoadPalette(GetWindowFrameTilesPal(selection)->pal, BG_PLTT_ID(7), PLTT_SIZE_4BPP);
        sArrowPressed = TRUE;
    }
    return selection;
}

static void FrameType_DrawChoices(u8 selection)
{
    u8 text[16];
    u8 n = selection + 1;
    u16 i;

    for (i = 0; gText_FrameTypeNumber[i] != EOS && i <= 5; i++)
        text[i] = gText_FrameTypeNumber[i];

    // Convert a number to decimal string
    if (n / 10 != 0)
    {
        text[i] = n / 10 + CHAR_0;
        i++;
        text[i] = n % 10 + CHAR_0;
        i++;
    }
    else
    {
        text[i] = n % 10 + CHAR_0;
        i++;
        text[i] = CHAR_SPACER;
        i++;
    }

    text[i] = EOS;

    DrawOptionMenuChoice(gText_FrameType, 104, YPOS_FRAMETYPE, 0);
    DrawOptionMenuChoice(text, 128, YPOS_FRAMETYPE, 1);
}

static u8 ButtonMode_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (selection <= 1)
            selection++;
        else
            selection = 0;

        sArrowPressed = TRUE;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (selection != 0)
            selection--;
        else
            selection = 2;

        sArrowPressed = TRUE;
    }
    return selection;
}

static void ButtonMode_DrawChoices(u8 selection)
{
    s32 widthNormal, widthLR, widthLA, xLR;
    u8 styles[3];

    styles[0] = 0;
    styles[1] = 0;
    styles[2] = 0;
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_ButtonTypeNormal, 104, YPOS_BUTTONMODE, styles[0]);

    widthNormal = GetStringWidth(FONT_NORMAL, gText_ButtonTypeNormal, 0);
    widthLR = GetStringWidth(FONT_NORMAL, gText_ButtonTypeLR, 0);
    widthLA = GetStringWidth(FONT_NORMAL, gText_ButtonTypeLEqualsA, 0);

    widthLR -= 94;
    xLR = (widthNormal - widthLR - widthLA) / 2 + 104;
    DrawOptionMenuChoice(gText_ButtonTypeLR, xLR, YPOS_BUTTONMODE, styles[1]);

    DrawOptionMenuChoice(gText_ButtonTypeLEqualsA, GetStringRightAlignXOffset(FONT_NORMAL, gText_ButtonTypeLEqualsA, 198), YPOS_BUTTONMODE, styles[2]);
}

static u8 BorderBackground_ProcessInput(u8 selection)
{
    u8 count = GetBorderBackgroundCount();

    if (JOY_NEW(DPAD_RIGHT))
    {
        selection = (selection + 1) % count;
        sArrowPressed = TRUE;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        selection = selection == 0 ? count - 1 : selection - 1;
        sArrowPressed = TRUE;
    }
    return selection;
}

static u8 GetBorderBackgroundCount(void)
{
#ifdef PLATFORM_SDL2
    return Platform_GetBorderBackgroundCount();
#else
    return 2;
#endif
}

static u8 GetBorderBackground(void)
{
#ifdef PLATFORM_SDL2
    return Platform_GetBorderBackground();
#else
    return gSaveBlock2Ptr->optionsBorderBackground;
#endif
}

static void SetBorderBackground(u8 selection)
{
#ifdef PLATFORM_SDL2
    Platform_SetBorderBackground(selection);
#endif
}

static void OpenDisplaySettings(u8 taskId)
{
    gTasks[taskId].tPlatformPage = TRUE;
    gTasks[taskId].tMenuSelection = 0;
    DrawDisplaySettings(taskId);
    HighlightOptionMenuItem(0);
}

static void CloseDisplaySettings(u8 taskId)
{
    gTasks[taskId].tPlatformPage = FALSE;
    gTasks[taskId].tMenuSelection = MENUITEM_DISPLAY;
    DrawOptionMenuTexts();
    TextSpeed_DrawChoices(gTasks[taskId].tTextSpeed);
    BattleScene_DrawChoices(gTasks[taskId].tBattleSceneOff);
    BattleStyle_DrawChoices(gTasks[taskId].tBattleStyle);
    Sound_DrawChoices(gTasks[taskId].tSound);
    ButtonMode_DrawChoices(gTasks[taskId].tButtonMode);
    FrameType_DrawChoices(gTasks[taskId].tWindowFrameType);
    HighlightOptionMenuItem(MENUITEM_DISPLAY);
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
}

static void DrawDisplaySettingChoice(u8 row, const u8 *text)
{
    FillWindowPixelRect(WIN_OPTIONS, PIXEL_FILL(1), 100, row * OPTION_ROW_HEIGHT, 108, OPTION_ROW_HEIGHT);
    DrawOptionMenuChoice(text, 104, row * OPTION_ROW_HEIGHT, 1);
}

static void DrawDisplayNumberChoice(u8 row, u8 value, bool8 percent)
{
    u8 text[16];
    u8 i;

    for (i = 0; gText_FrameTypeNumber[i] != EOS; i++)
        text[i] = gText_FrameTypeNumber[i];
    if (value >= 100)
        text[i++] = value / 100 + CHAR_0;
    if (value >= 10)
        text[i++] = (value / 10) % 10 + CHAR_0;
    text[i++] = value % 10 + CHAR_0;
    text[i++] = percent ? CHAR_PERCENT : CHAR_X;
    text[i] = EOS;
    DrawDisplaySettingChoice(row, text);
}

static void DrawDisplaySettings(u8 taskId)
{
    u8 row = 0;

    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(1));
#ifndef __ANDROID__
    AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, gText_Fullscreen, 8, row * OPTION_ROW_HEIGHT + 1, TEXT_SKIP_DRAW, NULL);
    DrawDisplaySettingChoice(row++, gTasks[taskId].tFullscreen ? gText_BattleSceneOn : gText_BattleSceneOff);
    AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, gText_WindowScale, 8, row * OPTION_ROW_HEIGHT + 1, TEXT_SKIP_DRAW, NULL);
    DrawDisplayNumberChoice(row++, gTasks[taskId].tWindowScale, FALSE);
    AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, gText_IntegerScale, 8, row * OPTION_ROW_HEIGHT + 1, TEXT_SKIP_DRAW, NULL);
    DrawDisplaySettingChoice(row++, gTasks[taskId].tIntegerScale ? gText_BattleSceneOn : gText_BattleSceneOff);
    AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, gText_VSync, 8, row * OPTION_ROW_HEIGHT + 1, TEXT_SKIP_DRAW, NULL);
    DrawDisplaySettingChoice(row++, gTasks[taskId].tVSync ? gText_BattleSceneOn : gText_BattleSceneOff);
#else
    AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, gText_DisplayMode, 8, row * OPTION_ROW_HEIGHT + 1, TEXT_SKIP_DRAW, NULL);
    DrawDisplaySettingChoice(row++, gTasks[taskId].tDisplayMode ? gText_DisplayModeInteger : gText_DisplayModeMax);
#endif
    AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, gText_BorderFrame, 8, row * OPTION_ROW_HEIGHT + 1, TEXT_SKIP_DRAW, NULL);
    DrawDisplaySettingChoice(row++, gTasks[taskId].tBorderFrame ? gText_BattleSceneOn : gText_BattleSceneOff);
    AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, gText_BorderBackground, 8, row * OPTION_ROW_HEIGHT + 1, TEXT_SKIP_DRAW, NULL);
    BorderBackground_DrawChoices(gTasks[taskId].tBorderBackground);
    row++;
    AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, gText_Volume, 8, row * OPTION_ROW_HEIGHT + 1, TEXT_SKIP_DRAW, NULL);
    DrawDisplayNumberChoice(row++, gTasks[taskId].tVolume * 10, TRUE);
    AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, gText_Back, 8, row * OPTION_ROW_HEIGHT + 1, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
}

static void ProcessDisplaySettingsInput(u8 taskId)
{
    u8 selection = gTasks[taskId].tMenuSelection;
    bool8 changed = FALSE;

    if (JOY_NEW(B_BUTTON) || (JOY_NEW(A_BUTTON) && selection == DISPLAY_BACK))
    {
        CloseDisplaySettings(taskId);
        return;
    }
    if (JOY_NEW(DPAD_UP))
        selection = selection == 0 ? DISPLAY_COUNT - 1 : selection - 1;
    else if (JOY_NEW(DPAD_DOWN))
        selection = selection == DISPLAY_COUNT - 1 ? 0 : selection + 1;
    else if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        bool8 right = JOY_NEW(DPAD_RIGHT);
        switch (selection)
        {
#ifndef __ANDROID__
        case DISPLAY_FULLSCREEN:
            gTasks[taskId].tFullscreen ^= 1;
            Platform_SetSetting(PLATFORM_SETTING_FULLSCREEN, gTasks[taskId].tFullscreen);
            break;
        case DISPLAY_WINDOW_SCALE:
            if (right)
                gTasks[taskId].tWindowScale = gTasks[taskId].tWindowScale == 5 ? 2 : gTasks[taskId].tWindowScale + 1;
            else
                gTasks[taskId].tWindowScale = gTasks[taskId].tWindowScale == 2 ? 5 : gTasks[taskId].tWindowScale - 1;
            Platform_SetSetting(PLATFORM_SETTING_WINDOW_SCALE, gTasks[taskId].tWindowScale);
            break;
        case DISPLAY_INTEGER_SCALE:
            gTasks[taskId].tIntegerScale ^= 1;
            Platform_SetSetting(PLATFORM_SETTING_INTEGER_SCALE, gTasks[taskId].tIntegerScale);
            break;
        case DISPLAY_VSYNC:
            gTasks[taskId].tVSync ^= 1;
            Platform_SetSetting(PLATFORM_SETTING_VSYNC, gTasks[taskId].tVSync);
            break;
#else
        case DISPLAY_DISPLAY_MODE:
            gTasks[taskId].tDisplayMode ^= 1;
            Platform_SetSetting(PLATFORM_SETTING_DISPLAY_MODE, gTasks[taskId].tDisplayMode);
            break;
#endif
        case DISPLAY_BORDER_FRAME:
            gTasks[taskId].tBorderFrame ^= 1;
#ifdef PLATFORM_SDL2
            Platform_SetSetting(PLATFORM_SETTING_BORDER, gTasks[taskId].tBorderFrame);
#endif
            break;
        case DISPLAY_BACKGROUND:
            gTasks[taskId].tBorderBackground = BorderBackground_ProcessInput(gTasks[taskId].tBorderBackground);
            gSaveBlock2Ptr->optionsBorderBackground = gTasks[taskId].tBorderBackground;
            SetBorderBackground(gTasks[taskId].tBorderBackground);
            break;
        case DISPLAY_VOLUME:
            if (right)
                gTasks[taskId].tVolume = gTasks[taskId].tVolume == 10 ? 0 : gTasks[taskId].tVolume + 1;
            else
                gTasks[taskId].tVolume = gTasks[taskId].tVolume == 0 ? 10 : gTasks[taskId].tVolume - 1;
#ifdef PLATFORM_SDL2
            Platform_SetSetting(PLATFORM_SETTING_VOLUME, gTasks[taskId].tVolume);
#endif
            break;
        default:
            return;
        }
        changed = TRUE;
    }

    if (selection != gTasks[taskId].tMenuSelection)
    {
        gTasks[taskId].tMenuSelection = selection;
        HighlightOptionMenuItem(selection);
    }
    if (changed)
    {
        DrawDisplaySettings(taskId);
        HighlightOptionMenuItem(selection);
    }
}

static void BorderBackground_DrawChoices(u8 selection)
{
    u8 text[16];
    u8 i;

    if (selection == GetBorderBackgroundCount() - 1)
    {
        DrawDisplaySettingChoice(DISPLAY_BACKGROUND, gText_BorderBackgroundOff);
        return;
    }

    for (i = 0; gText_BorderBackgroundName[i] != EOS; i++)
        text[i] = gText_BorderBackgroundName[i];

    if (selection >= 1)
    {
        text[i++] = CHAR_SPACE;
        if (selection >= 10)
            text[i++] = selection / 10 + CHAR_0;
        text[i++] = selection % 10 + CHAR_0;
    }
    text[i] = EOS;
    DrawDisplaySettingChoice(DISPLAY_BACKGROUND, text);
}

static void DrawHeaderText(void)
{
    FillWindowPixelBuffer(WIN_HEADER, PIXEL_FILL(1));
    AddTextPrinterParameterized(WIN_HEADER, FONT_NORMAL, gText_Option, 8, 1, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(WIN_HEADER, COPYWIN_FULL);
}

static void DrawOptionMenuTexts(void)
{
    u8 i;

    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(1));
    for (i = 0; i < MENUITEM_COUNT; i++)
        AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, sOptionMenuItemsNames[i], 8, (i * OPTION_ROW_HEIGHT) + 1, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
}

#define TILE_TOP_CORNER_L 0x1A2
#define TILE_TOP_EDGE     0x1A3
#define TILE_TOP_CORNER_R 0x1A4
#define TILE_LEFT_EDGE    0x1A5
#define TILE_RIGHT_EDGE   0x1A7
#define TILE_BOT_CORNER_L 0x1A8
#define TILE_BOT_EDGE     0x1A9
#define TILE_BOT_CORNER_R 0x1AA

static void DrawBgWindowFrames(void)
{
    //                     bg, tile,              x, y, width, height, palNum
    // Draw title window frame
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_L,  1,  0,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_EDGE,      2,  0, 27,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_R, 28,  0,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_LEFT_EDGE,     1,  1,  1,  2,  7);
    FillBgTilemapBufferRect(1, TILE_RIGHT_EDGE,   28,  1,  1,  2,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_L,  1,  3,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_EDGE,      2,  3, 27,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_R, 28,  3,  1,  1,  7);

    // Draw options list window frame
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_L,  1,  4,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_EDGE,      2,  4, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_R, 28,  4,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_LEFT_EDGE,     1,  5,  1, 18,  7);
    FillBgTilemapBufferRect(1, TILE_RIGHT_EDGE,   28,  5,  1, 18,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_L,  1, 19,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_EDGE,      2, 19, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_R, 28, 19,  1,  1,  7);

    CopyBgTilemapBufferToVram(1);
}
