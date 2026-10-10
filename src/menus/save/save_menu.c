#include "menus/save/save_menu.h"
#include "engine/bg/bg_screen_task.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/save/save_data.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/display.h"
#include "engine/system/system.h"
#include "engine/text/expand_text.h"
#include "engine/text/print_text.h"
#include "engine/text/text_args.h"
#include "engine/text/text_banks.h"
#include "engine/text/text_object.h"
#include "engine/text/window_text.h"
#include "engine/ui/buttons.h"

/* Frees the save menu's pictures, buttons, backgrounds and message, then
 * clears both screens. */
void freeSaveMenu(struct SaveMenu *menu) {
    struct SaveMenuWork *work;
    void *block;

    stopSubPaletteEffectsButFades(menu->unk50);
    stopMainPaletteEffectsButFades(menu->unk54);
    freeSubSprites();
    freeMainSprites();
    if (menu->buttons != -1) {
        closeButtonGroup(menu->buttons);
        menu->buttons = -1;
    }
    freeSaveMenuBgs(menu);
    work = menu->work;
    if (work->message.width != 0 && work->message.height != 0) {
        freeWindowImage(&work->message);
        func_02030f18(&menu->work->message, 0, sizeof(struct TextWindow));
    }
    func_02062b28();
    block = menu->work;
    heapFree(block);
    block = menu->choice;
    heapFree(block);
    clearSaveMenuScreens();
}

/* Whether the save menu is closed. */
u8 isSaveMenuClosed(void) {
    u8 closed;

    if (SAVE_MENU == NULL) {
        closed = TRUE;
    } else {
        closed = FALSE;
    }
    return closed;
}

/* The play time, PLAY_TIME, in ticks of 1/64 s; also as hours, minutes
 * and seconds into any of the three that is not NULL. */
s32 getPlayTime(s32 *hours, s32 *minutes, s32 *seconds) {
    s32 time = PLAY_TIME;

    if (seconds != NULL) {
        *seconds = time % (60 * PLAY_TIME_TICKS) / PLAY_TIME_TICKS;
    }
    if (minutes != NULL) {
        *minutes = time % (60 * 60 * PLAY_TIME_TICKS) / (60 * PLAY_TIME_TICKS);
    }
    if (hours != NULL) {
        *hours = time / (60 * 60 * PLAY_TIME_TICKS);
    }
    return time;
}

/* Prints the play time on the save menu when it has changed. */
void printPlayTime(struct SaveMenu *menu) {
    s32 hours;
    s32 minutes;
    s32 seconds;
    struct TextWindow window;
    u16 *buf;
    void *text;

    getPlayTime(&hours, &minutes, &seconds);
    if (menu->hours == hours && menu->minutes == minutes && menu->seconds == seconds) {
        return;
    }
    menu->hours   = hours;
    menu->minutes = minutes;
    menu->seconds = seconds;
    func_020a5848();
    buf = (u16 *) allocVramTransferData(6);
    formatNumber(hours, 2, buf, 1);
    setTextArg(0, buf);
    buf = (u16 *) allocVramTransferData(6);
    formatNumber(minutes, 2, buf, 1);
    setTextArg(1, buf);
    buf = (u16 *) allocVramTransferData(6);
    formatNumber(seconds, 2, buf, 1);
    setTextArg(2, buf);
    text          = func_0209cd08(0x4B);
    text          = func_0209e344(text);
    window.unk4   = 2;
    window.unkA   = menu->chars[3];
    window.width  = 8;
    window.font   = 2;
    window.height = 2;
    window.unk1C  = allocVramTransferData(0x200);
    window.unk20  = allocVramTransferData(0x20);
    window.flags  = 2;
    func_020a6b10(&window);
    func_020a5338(&window, text, 0, 0x270F);
    func_020a5d1c(0x15, 0xE, &window);
    if (window.width != 0 && window.height != 0) {
        freeWindowImage(&window);
        CLEAR(&window, sizeof(window));
    }
    func_020a5830();
}

/* Draws the Yes/No window's frame with the cursor on Yes or on No. */
void drawSaveChoiceFrame(struct SaveMenu *menu) {
    if (*menu->choice == 0) {
        func_020422ac(&menu->work->bgs[3], 2, 3, 3, 0x10, 1, 0xB, 0x1A, 4, 0x40, 0x20, (s32) (s16) (menu->chars[5] + 1));
        return;
    }
    func_020422ac(&menu->work->bgs[3], 2, 3, 3, 0x10, 1, 0x10, 0x1A, 4, 0x40, 0x20, (s32) (s16) (menu->chars[5] + 1));
}
