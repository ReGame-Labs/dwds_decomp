#include "link/wifi_friend_code.h"
#include "engine/bg/bg_screen_task.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/display_modes.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "field/actors/actor_create.h"
#include "field/actors/actor_tasks.h"
#include "link/link_start.h"
#include "link/wifi_friend_roster.h"

/* Starts script program 102: the Wi-Fi menu that shows the own Friend Code. */
void startFriendCodeMenu(void) {
    struct WifiMenu *menu;
    struct WifiMenuWork *work;

    func_020a3454(9);
    menu              = createTask(runFriendCodeMenu, 0x11B);
    menu->task.onEnd  = onFriendCodeMenuEnd;
    WIFI_MENU_TASK_ID = getTaskId(menu);
    WIFI_MENU         = menu;
    work              = heapAlloc(sizeof(struct WifiMenuWork), 4);
    menu->work        = work;
    func_02030f18(menu->work, 0, sizeof(struct WifiMenuWork));
    menu->state = 0;
    menu->unk26 = 0;
    menu->unk28 = 0;
}

/* The Friend Code menu's onEnd. */
void onFriendCodeMenuEnd(void) {
    struct WifiMenu *menu;
    void *work;

    menu = (struct WifiMenu *) getCurrentTask();
    work = menu->work;
    heapFree(work);
    menu->work        = NULL;
    WIFI_MENU_TASK_ID = -1;
    WIFI_MENU         = NULL;
}

/* Frees the Friend Code menu's sprite, backgrounds, pictures and fonts. */
void freeFriendCodeMenu(void) {
    struct WifiMenu *menu;

    if (WIFI_MENU == NULL) {
        return;
    }
    menu = findTask(WIFI_MENU_TASK_ID);
    freeMainSprite(menu->sprite);
    freeMainSprites();
    freeSubSprites();
    deleteMainActors();
    deleteSubActors();
    endMainActorTask();
    endSubActorTask();
    freeBgGraphics(&menu->work->bgs[1]);
    freeBgGraphics(&menu->work->bgs[0]);
    stopSubPaletteEffectsButFades(menu->unk64[0]);
    stopSubPaletteEffectsButFades(menu->unk64[1]);
    stopMainPaletteEffectsButFades(menu->unk6C[0]);
    stopMainPaletteEffectsButFades(menu->unk6C[1]);
    freeWifiMenuFonts();
    clearWifiMenuScreens();
}

/* Whether the Wi-Fi menu has ended. */
u8 isFriendCodeMenuEnded(void) {
    u8 ended;

    if (WIFI_MENU == NULL) {
        ended = TRUE;
    } else {
        ended = FALSE;
    }
    return ended;
}

/* Starts script program 104, which saves the game. */
void startProgram104(void) {
    struct Program104 *task;
    struct Program104Work *work;

    func_02072f68();
    task                = createTask(runProgram104, 0x11B);
    PROGRAM_104_TASK_ID = getTaskId(task);
    PROGRAM_104         = task;
    task->task.onEnd    = onProgram104End;
    task->state         = 0;
    task->unk22         = 0;
    work                = heapAlloc(sizeof(struct Program104Work), 4);
    task->work          = work;
    func_02030f18(task->work, 0, sizeof(struct Program104Work));
    task->work->unk30 = 0xFFFF;
    task->work->unk50 = 0;
}

/* Program 104's onEnd. */
void onProgram104End(void) {
    void *work;

    work = ((struct Program104 *) getCurrentTask())->work;
    heapFree(work);
    PROGRAM_104_TASK_ID = -1;
    PROGRAM_104         = NULL;
}
