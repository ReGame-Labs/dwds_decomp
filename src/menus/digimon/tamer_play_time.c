#include "menus/digimon/tamer_play_time.h"
#include "engine/bg/bg_load.h"
#include "engine/bg/bg_screen_task.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/save/progress.h"
#include "engine/system/display.h"
#include "engine/text/expand_text.h"
#include "engine/text/print_text.h"
#include "engine/text/text_args.h"
#include "engine/text/text_banks.h"
#include "engine/text/text_object.h"
#include "engine/text/window_text.h"
#include "menus/digimon/data.h"

/* Loads the backgrounds of /dat/bg/mtm_top again: entries 0x3E and 0x3F of
 * data_0213537c, for the main and the sub screen. */
void func_ov006_0227b6a0(void) {
    freeBgGraphics(&data_ov006_0229f458);
    freeBgGraphics(&data_ov006_0229f488);
    func_02042aa8(&data_ov006_0229f458, 0x3E, 1, 2);
    func_02042aa8(&data_ov006_0229f488, 0x3F, 2, 2);
}

/* Draws the play time, hours:minutes:seconds (text 0x4B), when it has changed
 * since it was last drawn. */
void drawPlayTime(struct TamerScreen *screen) {
    s32 time[3];
    struct TextWindow text;
    u16 *buffer;
    void *format;

    if (screen->playTimeChar == -1) {
        return;
    }
    func_020a001c(&time[0], &time[1], &time[2]);
    if (screen->hours == time[0] && screen->minutes == time[1] && screen->seconds == time[2]) {
        return;
    }
    screen->hours   = time[0];
    screen->minutes = time[1];
    screen->seconds = time[2];
    func_020a5848();
    buffer = (u16 *) allocVramTransferData(6);
    formatNumber(time[0], 2, buffer, 1);
    setTextArg(0, buffer);
    buffer = (u16 *) allocVramTransferData(6);
    formatNumber(time[1], 2, buffer, 1);
    setTextArg(1, buffer);
    buffer = (u16 *) allocVramTransferData(6);
    formatNumber(time[2], 2, buffer, 1);
    setTextArg(2, buffer);
    format      = func_0209cd08(0x4B);
    format      = func_0209e344(format);
    text.unk4   = 2;
    text.unkA   = screen->playTimeChar;
    text.width  = 8;
    text.font   = 2;
    text.height = 2;
    text.unk1C  = allocVramTransferData(0x200);
    text.unk20  = allocVramTransferData(0x20);
    text.flags  = 3;
    func_020a6b10(&text);
    func_020a5338(&text, format, 0, 9999);
    func_020a5d1c(0x15, 0xE, &text);
    if (text.width != 0 && text.height != 0) {
        freeWindowImage(&text);
        CLEAR(&text, sizeof(text));
    }
    func_020a5830();
}

/* Counts the friends of the Wi-Fi roster: the entries before the first that
 * func_020ff5cc finds empty. */
s16 countRosterFriends(void) {
    struct WifiData *wifi = (struct WifiData *) data_021db618;
    s32 i;

    for (i = 0; i < 16; i++) {
        if (func_020ff5cc(wifi->friends[i]) == 0) {
            return i;
        }
    }
    return i;
}
