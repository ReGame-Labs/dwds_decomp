#include "farm/event_script.h"
#include "engine/script/cmd_core.h"
#include "engine/script/interpreter.h"
#include "engine/sprite/sprite.h"
#include "engine/text/text_banks.h"
#include "engine/text/window_text.h"
#include "engine/window/window.h"

/* Starts script 0x1B5 with its first two variables set to x and y. */
void func_ov005_0228f82c(s16 x, s16 y) {
    s32 thread = startEventScript(0x1B5);

    func_02094e14(thread, 0, x);
    func_02094e14(thread, 1, y);
    func_02094e14(thread, 2, 10);
    func_02094e14(thread, 3, 0);
    func_02094e14(thread, 4, 60);
    func_02094e14(thread, 5, 540);
}

/* Puts a menu's cursor on row: the window beside the row, showing the entry's
 * text of data_0211809c, and the cursor's sprite. */
void func_ov005_0228f048(u8 window, s16 text, s16 row, s16 sprite) {
    s32 y = row * 32 + 0x30;

    func_020a8e3c(window, 0x13, y / 8);
    func_020a6990(window, 0, 0, 8, 2, func_0209d320(text), 0, 2, 0x80);
    setSubSpritePos(sprite, 0xE8, y);
}
