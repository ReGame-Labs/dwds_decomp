#include "engine/debug/debug_print.h"
#include "engine/data.h"
#include "engine/input/touch.h"
#include "engine/libs.h"
#include "engine/movie/movie_player.h"
#include "engine/system/system.h"
#include "nitro/mi.h"
#include "nitro/mmap.h"

/* Clears the BG VRAM of the debug console's screen. */
void clearDebugPrintBg(void) {
    if (((s32) DEBUG_PRINT_BG >= 0) && ((s32) DEBUG_PRINT_BG <= 3)) {
        MI_CpuClearFast((void *) HW_BG_VRAM, HW_BG_VRAM_SIZE);
    }
    if (((s32) DEBUG_PRINT_BG >= 4) && ((s32) DEBUG_PRINT_BG <= 7)) {
        MI_CpuClearFast((void *) HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
    }
    func_020da564();
}

/* Clears the debug console's text screen. */
void clearDebugPrintScreen(void) {
    MI_CpuClearFast(DEBUG_PRINT_SCREEN, sizeof(DEBUG_PRINT_SCREEN));
}

/* The debug console's task: copies its text screen into the map of its BG
 * (0-3 the main screen's BG0-BG3, 4-7 the sub screen's), then clears it for
 * the next frame's prints. */
void tickDebugPrint(void) {
    func_020e4f58(DEBUG_PRINT_SCREEN, sizeof(DEBUG_PRINT_SCREEN));
    switch (DEBUG_PRINT_BG) {
        default:
            break;
        case 0:
            func_020dc4a0(DEBUG_PRINT_SCREEN, 0, sizeof(DEBUG_PRINT_SCREEN));
            break;
        case 1:
            func_020dc3d0(DEBUG_PRINT_SCREEN, 0, sizeof(DEBUG_PRINT_SCREEN));
            break;
        case 2:
            func_020dc300(DEBUG_PRINT_SCREEN, 0, sizeof(DEBUG_PRINT_SCREEN));
            break;
        case 3:
            func_020dc230(DEBUG_PRINT_SCREEN, 0, sizeof(DEBUG_PRINT_SCREEN));
            break;
        case 4:
            func_020dc438(DEBUG_PRINT_SCREEN, 0, sizeof(DEBUG_PRINT_SCREEN));
            break;
        case 5:
            func_020dc368(DEBUG_PRINT_SCREEN, 0, sizeof(DEBUG_PRINT_SCREEN));
            break;
        case 6:
            func_020dc298(DEBUG_PRINT_SCREEN, 0, sizeof(DEBUG_PRINT_SCREEN));
            break;
        case 7:
            func_020dc1c8(DEBUG_PRINT_SCREEN, 0, sizeof(DEBUG_PRINT_SCREEN));
            break;
    }
    clearDebugPrintScreen();
}

/* Sets the attribute of the text printed next: its palette in the low bits,
 * DEBUG_PRINT_BLINK to blink. A fixed attribute, while set, wins. */
void setDebugPrintAttr(s16 attr) {
    if ((s32) DEBUG_PRINT_FIXED_ATTR >= 0) {
        DEBUG_PRINT_ATTR = DEBUG_PRINT_FIXED_ATTR;
        return;
    }
    DEBUG_PRINT_ATTR = attr;
}

/* The attribute the debug console prints with. */
u16 getDebugPrintAttr(void) {
    return DEBUG_PRINT_ATTR;
}

/* Prints formatted text on the debug console at the given column and row.
 * Blinking text is left out every other half second. */
s32 printDebugf(s32 x, s32 y, const char *fmt, ...) {
    char text[DEBUG_PRINT_COLUMNS + 1];
    char *args;
    s32 hidden;

    if (getDebugPrintAttr() & DEBUG_PRINT_BLINK) {
        hidden = (getFrameCount() / 30) & 1;
        if (hidden != 0) {
            return hidden;
        }
    }
    /* MSL's va_start: the arguments after fmt. */
    args = (char *) (((u32) &fmt & ~3) + 4);
    func_020310ac(text, sizeof(text), fmt, args);
    return printDebug(x, y, text);
}

/* Opens the debug console on a BG (0-3 the main screen's BG0-BG3, 4-7 the
 * sub screen's) and starts its task. */
void openDebugPrint(s32 bg) {
    DEBUG_PRINT_BG = bg;
    initDebugPrintBg();
    createTask(&tickDebugPrint, DEBUG_PRINT_TASK_PRIORITY);
}

/* Closes the debug console and clears its BG's VRAM. */
void closeDebugPrint(void) {
    endTasksOfPriority(DEBUG_PRINT_TASK_PRIORITY);
    clearDebugPrintBg();
}

/* Closes the debug console and unsets the fixed attribute. */
void stopDebugPrint(void) {
    endTasksOfPriority(DEBUG_PRINT_TASK_PRIORITY);
    DEBUG_PRINT_FIXED_ATTR = -1;
}

/* Starts the touch panel with the calibration of the user's settings (TP_Init,
 * TP_GetUserInfo, TP_SetCalibrateParam); the game stops if there is none. */
void initTouchPanel(void) {
    s32 calibration[3];

    func_020e78fc();
    if (func_020e7850(calibration) == 0) {
        func_020e6250();
    }
    func_020e7708(calibration);
    clearTouch();
}
