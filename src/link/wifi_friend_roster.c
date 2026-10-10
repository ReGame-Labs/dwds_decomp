#include "link/wifi_friend_roster.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "nitro/g2.h"
#include "nitro/mi.h"
#include "nitro/mmap.h"

/* Clears both screens' backgrounds, sprites and blending. */
void clearWifiMenuScreens(void) {
    MI_CpuClearFast((void *) HW_BG_VRAM, HW_BG_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OAM, HW_OAM_SIZE);
    func_020da564();
    func_020da550();
    func_020da52c();
    func_020da508();
    MI_CpuClearFast((void *) HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_DB_OAM, HW_OAM_SIZE);
    func_020da4b8();
    func_020da4a4();
    func_020da47c();
    func_020da454();
    G2_BlendNone();
    G2S_BlendNone();
}

/* Loads the Wi-Fi menus' fonts. */
void loadWifiMenuFonts(void) {
    func_020a9c40(1, 0, 0xE);
    func_020a9c40(2, 1, 0xE);
    func_020a9c40(5, 2, 0xE);
    func_020a9c40(0, 3, 0xF);
}

/* Frees the Wi-Fi menus' fonts. */
void freeWifiMenuFonts(void) {
    func_020a98a8(1);
    func_020a98a8(2);
    func_020a98a8(5);
    func_020a98a8(0);
}

/* Opens the friend roster's list, unless it is open. */
void openFriendRosterList(s16 top, s16 cursor, s16 c, s16 d, u16 e) {
    struct FriendRosterList *list;

    if (FRIEND_ROSTER_LIST != NULL) {
        return;
    }
    list                       = createTask(runFriendRosterList, 0x11B);
    list->task.onEnd           = onFriendRosterListEnd;
    FRIEND_ROSTER_LIST_TASK_ID = getTaskId(list);
    FRIEND_ROSTER_LIST         = list;
    list->state                = 0;
    list->unk1E                = 0;
    list->top                  = top;
    list->cursor               = cursor;
    list->unk2C                = -1;
    list->result               = 0;
    func_02030f18(&list->window, 0, sizeof(struct TextWindow));
    list->unk78 = c;
    list->unk7A = d;
    list->unk7C = e;
}

/* The friend roster list's onEnd. */
void onFriendRosterListEnd(void) {
    FRIEND_ROSTER_LIST_TASK_ID = -1;
    FRIEND_ROSTER_LIST         = NULL;
}
