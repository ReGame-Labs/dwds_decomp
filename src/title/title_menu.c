#include "title/title_menu.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/palette/palette_fade.h"
#include "engine/palette/palette_upload.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/ui/buttons.h"
#include "engine/ui/gauge.h"
#include "engine/window/window.h"
#include "engine/window/window_draw.h"
#include "field/actors/actor_facing.h"
#include "field/actors/actor_files.h"
#include "field/actors/actor_tasks.h"
#include "nitro/pad.h"

#define REG_DB_BLDCNT 0x04001050 /* the sub screen's blending */

#define UI_FLAG_TITLE_MENU 3
#define FLAG_UNK400 0x400 /* set when the title menu closes */
#define CHOICE_NONE -1
#define CHOICE_CANCELLED 99
#define PALETTES_TITLE 0xA00 /* the palettes of the title menu's choices */
#define PALETTE_COLORS 0x10
#define BRIGHTNESS_DARK -0xF
#define SPRITE_OFF_SCREEN 999 /* x and y that put a sprite off screen */
#define SE_CHOOSE 1 /* playSound's sounds */
#define SE_CANCEL 3

/* Touch-button callback of the title menu's first page: B cancels, a touched
 * choice is taken; the choice under the stylus gets its palette lit and its
 * sprite brought forward. */
void func_020aaa34(s32 button, s16 index, struct ButtonGroup *group) {
    struct TitleMenu *menu;
    u16 held;
    s16 choice;
    s16 shown;

    held = getPadPressed();
    menu = findTask(data_021e5ae0);
    if (menu->choice != CHOICE_NONE) {
        return;
    }
    choice = getGroupChosenButton(group);
    if (held & PAD_BUTTON_B) {
        menu->choice = CHOICE_CANCELLED;
        playSound(SE_CANCEL);
    } else if (choice > -1) {
        menu->choice = choice;
        playSound(SE_CHOOSE);
    }
    shown = menu->shown;
    if (shown != index) {
        func_020845e4(shown * PALETTE_COLORS + PALETTES_TITLE, PALETTE_COLORS, BRIGHTNESS_DARK);
        func_020845e4(index * PALETTE_COLORS + PALETTES_TITLE, PALETTE_COLORS, 0);
        markSubPalettesDirty();
        setActorAnimation(getSubActor(menu->sprites[menu->shown]), 7);
        setActorAnimation(getSubActor(menu->sprites[index]), 0xF);
        menu->shown = index;
    }
}

/* Touch-button callback of a two-choice page of the title menu: B takes
 * choice 2; the window's sprite shows the choice under the stylus. */
void func_020aa968(s32 button, s16 index, struct ButtonGroup *group) {
    struct TitleMenu *menu;
    u16 held;
    s32 choice;

    held = getPadPressed();
    menu = findTask(data_021e5ae0);
    if (menu->choice != CHOICE_NONE) {
        return;
    }
    choice = getGroupChosenButton(group);
    if (choice > -1) {
        menu->choice = choice;
        func_020a869c(menu->window, 0, SPRITE_OFF_SCREEN, SPRITE_OFF_SCREEN);
        playSound(SE_CHOOSE);
    } else if (held & PAD_BUTTON_B) {
        menu->choice = 2;
        func_020a869c(menu->window, 0, SPRITE_OFF_SCREEN, SPRITE_OFF_SCREEN);
    }
    if (menu->shown != index) {
        func_020a8638(menu->window, 0, index);
        menu->shown = index;
    }
}

/* The same, for a three-choice page: B takes choice 3, and the sprite's
 * animations start at 3. */
void func_020aa894(s32 button, s16 index, struct ButtonGroup *group) {
    struct TitleMenu *menu;
    u16 held;
    s32 choice;

    menu = findTask(data_021e5ae0);
    held = getPadPressed();
    if (menu->choice != CHOICE_NONE) {
        return;
    }
    choice = getGroupChosenButton(group);
    if (choice > -1) {
        menu->choice = choice;
        playSound(SE_CHOOSE);
        func_020a869c(menu->window, 0, SPRITE_OFF_SCREEN, SPRITE_OFF_SCREEN);
    } else if (held & PAD_BUTTON_B) {
        menu->choice = 3;
        func_020a869c(menu->window, 0, SPRITE_OFF_SCREEN, SPRITE_OFF_SCREEN);
    }
    if (menu->shown != index) {
        func_020a8638(menu->window, 0, index + 3);
        menu->shown = index;
    }
}

/* Closes the title menu and sets flag 0x400. */
void closeTitleMenu(void) {
    struct TitleMenu *menu;

    if (getUiFlag(UI_FLAG_TITLE_MENU) == 0) {
        return;
    }
    menu = findTask(data_021e5ae0);
    if (menu->window != 0xFF) {
        closeWindow(menu->window);
    }
    releaseGfxSlot(menu->gfxSlot);
    func_020a9844(0);
    endSubActorTask();
    endTask(menu);
    setGameFlag(FLAG_UNK400);
    clearUiFlag(UI_FLAG_TITLE_MENU);
}

/* Blends planes of the sub screen over the others, percent of the way. */
void func_020aa7bc(s32 planes, s32 percent) {
    func_020db8cc(REG_DB_BLDCNT, planes, (u16) (~planes & 0x3F), percent * 31 / 100, (100 - percent) * 31 / 100);
}

/* Sets data_021e33c4 and data_021e33bc (func_020aa220 reads the latter),
 * and clears the text flags. */
void func_020aa340(s8 value, s8 value2) {
    data_021e33c4 = value;
    data_021e33bc = value2;
    data_021e33cc = 0;
}

/* Sets data_021e33b8 (func_020aa1a4 reads it) and data_021e33c0, and clears
 * the text flags. */
void func_020aa308(s8 value, s8 value2) {
    data_021e33b8 = value;
    data_021e33c0 = value2;
    data_021e33cc = 0;
}

/* Gets what func_020aa308 set. */
void func_020aa2e4(s8 *value, s8 *value2) {
    *value  = data_021e33b8;
    *value2 = data_021e33c0;
}
