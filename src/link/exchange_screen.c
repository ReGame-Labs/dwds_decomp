#include "link/exchange_screen.h"
#include "engine/data.h"
#include "engine/save/save_data.h"
#include "engine/system/display.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/window/window.h"

/* Loads the exchange's four font slots, two with each loader. */
void loadExchangeFontSlots(struct Exchange *exchange) {
    exchange->fonts[0] = func_020aa220(0x60, -1, 7);
    exchange->fonts[1] = func_020aa220(0xC, -1, 8);
    exchange->fonts[2] = func_020aa1a4(0x60, -1, 6);
    exchange->fonts[3] = func_020aa1a4(0xC, -1, 7);
}

/* Frees the exchange's four font slots. */
void freeExchangeFontSlots(struct Exchange *exchange) {
    func_020a9610(exchange->fonts[0]);
    func_020a9610(exchange->fonts[1]);
    func_020a9610(exchange->fonts[2]);
    func_020a9610(exchange->fonts[3]);
}

/* Closes the exchange's open windows. */
void closeExchangeWindows(struct Exchange *exchange) {
    if (exchange->windows[0] != NO_WINDOW) {
        closeWindow(exchange->windows[0]);
        exchange->windows[0] = NO_WINDOW;
    }
    if (exchange->windows[1] != NO_WINDOW) {
        closeWindow(exchange->windows[1]);
        exchange->windows[1] = NO_WINDOW;
    }
    if (exchange->windows[2] != NO_WINDOW) {
        closeWindow(exchange->windows[2]);
        exchange->windows[2] = NO_WINDOW;
    }
    if (exchange->windows[3] == NO_WINDOW) {
        return;
    }
    closeWindow(exchange->windows[3]);
    exchange->windows[3] = NO_WINDOW;
}

/* The save menu's onEnd. */
void onSaveMenuEnd(void) {
    getCurrentTask();
    SAVE_MENU_TASK_ID = -1;
    SAVE_MENU         = NULL;
    func_020878ec();
}
