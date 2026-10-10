#include "engine/window/message_box.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/palette/palette_upload.h"
#include "engine/system/display.h"
#include "engine/system/system.h"
#include "engine/text/window_text.h"
#include "engine/ui/digimon_list.h"
#include "engine/ui/gauge.h"
#include "engine/window/window.h"
#include "farm/farm_groups.h"
#include "title/title_menu.h"

/* The DS's memory and registers. */
#define HW_BG_PLTT 0x05000000
#define HW_DB_BG_PLTT 0x05000400 /* the sub screen's; "DB" as NitroSDK names it */
#define PALETTES_SIZE 0x400
#define HW_BG_VRAM 0x06000000
#define HW_DB_BG_VRAM 0x06200000
#define HW_OBJ_VRAM 0x06400000
#define HW_DB_OBJ_VRAM 0x06600000
#define HW_OAM 0x07000000
#define HW_DB_OAM 0x07000400
#define REG_BLDCNT 0x04000050
#define REG_DB_BLDCNT 0x04001050

#define UI_FLAG_MESSAGE 1
#define UI_FLAG_TITLE_MENU 3
#define FLAG_UNK400 0x400 /* clear while the title menu runs */
#define RESULT_NONE 9999

/* Returns the result of the message window (struct Menu), or 9999 when none
 * is open. */
s32 func_020ac6b8(void) {
    struct Menu *menu;

    if (getUiFlag(UI_FLAG_MESSAGE) == 0) {
        return RESULT_NONE;
    }
    menu = findTask(MENU_TASK_ID);
    return menu->result;
}

/* Returns whether the message window's window has flag 0x200
 * (func_020a8dcc). */
s32 func_020ac678(void) {
    struct Menu *menu;

    if (getUiFlag(UI_FLAG_MESSAGE) == 0) {
        return FALSE;
    }
    menu = findTask(MENU_TASK_ID);
    return func_020a8dcc(menu->window);
}

/* Shows one of getFarmText's texts in the message window (func_020ac2ec). */
s32 func_020ac650(s32 index, s32 value, s32 value2) {
    return func_020ac2ec(getFarmText(index), value, value2);
}

/* Prints two texts into the message window: the first in its text rect, the
 * second at (4, 13), 0x78 pixels in, with the next palette. */
void func_020ac220(s32 text0, s32 text1) {
    struct Menu *menu;

    if (getUiFlag(UI_FLAG_MESSAGE) == 0) {
        return;
    }
    menu = findTask(MENU_TASK_ID);
    func_020a68cc(menu->window, menu->textX, menu->textY, menu->textWidth, menu->textHeight, text0, 0, (u8) menu->palette, 3,
                  2, 0);
    func_020a68cc(menu->window, 4, 0xD, 7, 2, text1, 0x78, (u8) (menu->palette + 1), 5, 2, 2);
}

/* Clears the main screen's palettes and graphics (func_020ac11c). */
void func_020ac1f8(void) {
    func_020e233c(0, HW_BG_PLTT, PALETTES_SIZE);
    clearMainPalettesDirty();
    func_020ac11c();
}

/* The same for the sub screen (func_020ac068). */
void func_020ac1cc(void) {
    func_020e233c(0, HW_DB_BG_PLTT, PALETTES_SIZE);
    clearSubPalettesDirty();
    func_020ac068();
}

/* Clears the main screen's background and object graphics and its OAM, and
 * resets its backgrounds and blending. */
void func_020ac11c(void) {
    func_020e233c(0, HW_BG_VRAM, 0x80000);
    func_020e233c(0, HW_OBJ_VRAM, 0x40000);
    func_020e233c(0, HW_OAM, 0x400);
    func_020da564();
    func_020da550();
    func_020da52c();
    func_020da508();
    *(s16 *) REG_BLDCNT = 0;
    setMainBgOffset(0, 0, 0);
    setMainBgOffset(1, 0, 0);
    setMainBgOffset(2, 0, 0);
    setMainBgOffset(3, 0, 0);
    setMainBgPriorities(0, 1, 2, 3);
}

/* The same for the sub screen. */
void func_020ac068(void) {
    func_020e233c(0, HW_DB_BG_VRAM, 0x20000);
    func_020e233c(0, HW_DB_OBJ_VRAM, 0x20000);
    func_020e233c(0, HW_DB_OAM, 0x400);
    func_020da4b8();
    func_020da4a4();
    func_020da47c();
    func_020da454();
    *(s16 *) REG_DB_BLDCNT = 0;
    setSubBgOffset(0, 0, 0);
    setSubBgOffset(1, 0, 0);
    setSubBgOffset(2, 0, 0);
    setSubBgOffset(3, 0, 0);
    setSubBgPriorities(0, 1, 2, 3);
}

/* Opens the title menu. */
void openTitleMenu(void) {
    struct TitleMenu *menu;

    menu          = createTask(&func_020aab34, 0x10A);
    data_021e5ae0 = getTaskId(menu);
    menu->state   = 0;
    menu->wait    = 0;
    clearGameFlag(FLAG_UNK400);
    setUiFlag(UI_FLAG_TITLE_MENU);
}
