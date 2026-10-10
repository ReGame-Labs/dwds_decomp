#include "link/link_start.h"
#include "engine/bg/bg_screen_task.h"
#include "engine/data.h"
#include "engine/palette/palette_buffers.h"
#include "engine/sprite/sprite_create.h"
#include "link/link_session.h"
#include "link/wifi.h"
#include "link/wifi_friend_roster.h"

/* Frees the program 104 task's pictures, backgrounds, sprites and fonts. */
void freeProgram104(struct Program104 *task) {
    stopSubPaletteEffectsButFades(task->unk24);
    stopMainPaletteEffectsButFades(task->unk28);
    freeBgGraphics(&task->work->bgs[0]);
    freeBgGraphics(&task->work->bgs[1]);
    freeMainSprites();
    freeSubSprites();
    clearWifiMenuScreens();
}

/* Whether script program 104 has ended. */
u8 isProgram104Ended(void) {
    u8 ended;

    if (PROGRAM_104 == NULL) {
        ended = TRUE;
    } else {
        ended = FALSE;
    }
    return ended;
}

/* Gives the save's Wi-Fi user data the 64-bit key from func_020727c8. */
void func_0207279c(void) {
    s64 key;

    key = func_020727c8();
    func_020b50ac((s32) data_021db618, (s32) key, (s32) (key >> 32));
}

/* Calls func_020b59a8. */
void func_0207270c(s32 mode, s32 unk) {
    func_020b59a8(mode, unk);
}

/* Resets the link session's globals and its icon sprites' slots. */
void resetLinkGlobals(void) {
    LINK_SESSION_TASK_ID = -1;
    LINK_SESSION         = NULL;
    SUB_LINK_ICON        = -1;
    MAIN_LINK_ICON       = -1;
}
