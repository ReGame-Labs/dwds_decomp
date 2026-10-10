#include "menus/digiconvert/digiconvert_open.h"
#include "battle/characters/chr.h"
#include "battle/characters/chr_system.h"
#include "engine/data.h"
#include "engine/debug/debug_print.h"
#include "engine/libs.h"
#include "engine/save/card_backup.h"
#include "engine/save/save_data.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/display.h"
#include "engine/system/display_modes.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "engine/window/window.h"
#include "menus/digiconvert/digiconvert.h"
#include "menus/digiconvert/digiconvert_data.h"
#include "menus/digiconvert/digiconvert_view.h"
#include "menus/widgets/menu_displays.h"
#include "title/title_menu.h"

/* Opens the card's backup and gives the save writer a buffer of SAVE_SIZE
 * rounded up to the card's page size: 1 done, 0 no buffer, -1 no card. */
s32 allocSaveBuffer(void) {
    struct SaveWriter *writer = &SAVE_WRITER;
    s32 pageSize;
    s32 size;

    if (func_0207c290(0x1001, &data_021db5f8) == 0) {
        func_02087884();
        func_020878ec();
        return -1;
    }
    pageSize       = getBackupPageSize();
    size           = (~(pageSize - 1) & SAVE_SIZE) + (((pageSize - 1) & SAVE_SIZE) ? pageSize : 0);
    writer->buffer = heapAlloc(size, 4);
    if (func_0207c0f0(writer->buffer, size) != 0) {
        return 1;
    }
    func_02087884();
    func_020878ec();
    return 0;
}

/* Frees the save writer's buffer. */
void freeSaveBuffer(void) {
    struct SaveWriter *writer = &SAVE_WRITER;
    void *buffer;

    if (writer->buffer == NULL) {
        return;
    }
    buffer = writer->buffer;
    heapFree(buffer);
    writer->buffer = NULL;
}

/* Whether the Digiconvert screen is closed. */
u8 isDigiconvertClosed(void) {
    u8 closed;

    if (DIGICONVERT == NULL) {
        closed = TRUE;
    } else {
        closed = FALSE;
    }
    return closed;
}

/* Ends the screen: frees what unloadDigiconvert does, then the task's blocks. */
void closeDigiconvert(struct Digiconvert *digiconvert) {
    void *block;

    freeMainSprites();
    freeSubSprites();
    removeAllMainBattleChrs();
    removeAllSubBattleChrs();
    endBattleChrs();
    freeDigiconvertBgs(digiconvert);
    func_0205f6b0();
    func_0205f5e8();
    if (digiconvert->windows[0] != 0xFF) {
        closeWindow(digiconvert->windows[0]);
        digiconvert->windows[0] = 0xFF;
    }
    if (digiconvert->windows[1] != 0xFF) {
        closeWindow(digiconvert->windows[1]);
        digiconvert->windows[1] = 0xFF;
    }
    if (digiconvert->windows[2] != 0xFF) {
        closeWindow(digiconvert->windows[2]);
        digiconvert->windows[2] = 0xFF;
    }
    if (digiconvert->windows[3] != 0xFF) {
        closeWindow(digiconvert->windows[3]);
        digiconvert->windows[3] = 0xFF;
    }
    if (digiconvert->windows[4] != 0xFF) {
        closeWindow(digiconvert->windows[4]);
        digiconvert->windows[4] = 0xFF;
    }
    if (digiconvert->buttons != -1) {
        closeButtonGroup(digiconvert->buttons);
        digiconvert->buttons = -1;
    }
    releaseMenuDisplays();
    block = digiconvert->work;
    heapFree(block);
    block = digiconvert->order;
    heapFree(block);
    block = digiconvert->scroll;
    heapFree(block);
    block = digiconvert->unk34;
    heapFree(block);
}

/* Frees the screen's graphics, windows and buttons, keeping its blocks. */
void unloadDigiconvert(struct Digiconvert *digiconvert) {
    freeMainSprites();
    freeSubSprites();
    removeAllMainBattleChrs();
    removeAllSubBattleChrs();
    endBattleChrs();
    freeDigiconvertBgs(digiconvert);
    func_0205f6b0();
    func_0205f5e8();
    if (digiconvert->windows[0] != 0xFF) {
        closeWindow(digiconvert->windows[0]);
        digiconvert->windows[0] = 0xFF;
    }
    if (digiconvert->windows[1] != 0xFF) {
        closeWindow(digiconvert->windows[1]);
        digiconvert->windows[1] = 0xFF;
    }
    if (digiconvert->windows[2] != 0xFF) {
        closeWindow(digiconvert->windows[2]);
        digiconvert->windows[2] = 0xFF;
    }
    if (digiconvert->windows[3] != 0xFF) {
        closeWindow(digiconvert->windows[3]);
        digiconvert->windows[3] = 0xFF;
    }
    if (digiconvert->windows[4] != 0xFF) {
        closeWindow(digiconvert->windows[4]);
        digiconvert->windows[4] = 0xFF;
    }
    if (digiconvert->buttons != -1) {
        closeButtonGroup(digiconvert->buttons);
        digiconvert->buttons = -1;
    }
}

/* The task's onEnd: forgets the screen. */
void onDigiconvertEnd(void) {
    DIGICONVERT = NULL;
}

/* Comes back to the screen: as openDigiconvert makes it, keeping the lists and
 * the species' data. */
void reloadDigiconvert(void) {
    struct Digiconvert *digiconvert;
    struct DigiconvertWork *work;

    closeDebugPrint();
    stopDebugPrint();
    func_020a3454(8);
    digiconvert             = DIGICONVERT;
    digiconvert->task.onEnd = onDigiconvertEnd;
    func_0205d9e0(digiconvert->work->lists[3]);
    initMainBattleChrs(0x200);
    initSubBattleChrs(0x200);
    digiconvert->species       = -1;
    work                       = digiconvert->work;
    work->list                 = work->lists[3];
    digiconvert->order->order  = 1;
    digiconvert->scrollBar     = -1;
    digiconvert->buttons       = -1;
    digiconvert->unk40         = -1;
    digiconvert->choiceButtons = -1;
    digiconvert->windows[0]    = 0xFF;
    digiconvert->windows[1]    = 0xFF;
    digiconvert->windows[2]    = 0xFF;
    digiconvert->windows[3]    = 0xFF;
    digiconvert->windows[4]    = 0xFF;
    digiconvert->unk9E         = 0;
    loadDigiconvertBgs(digiconvert);
    func_020aa340(2, 1);
    func_020aa308(2, 1);
    func_0205f630();
    func_0205f6cc();
}
