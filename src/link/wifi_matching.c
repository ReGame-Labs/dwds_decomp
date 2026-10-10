#include "link/wifi_matching.h"
#include "engine/bg/bg_screen_task.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/text/text_banks.h"
#include "engine/ui/buttons.h"
#include "engine/ui/gauge.h"
#include "engine/window/window.h"
#include "field/actors/actor_create.h"
#include "field/actors/actor_tasks.h"
#include "link/wifi.h"
#include "link/wifi_connect.h"
#include "nitro/g2.h"
#include "nitro/mi.h"
#include "nitro/mmap.h"

/* Shows a quest in the quest window, if it is open. */
void showQuestWindowQuest(s32 quest, s16 unk24) {
    struct QuestWindow *window;

    if (getUiFlag(UI_FLAG_QUEST_WINDOW) == 0) {
        return;
    }
    window        = findTask(QUEST_WINDOW_TASK_ID);
    window->unk24 = unk24;
    drawQuest(window->window, quest, unk24);
}

/* Closes the quest window, if it is open. */
void closeQuestWindow(void) {
    struct QuestWindow *window;

    if (getUiFlag(UI_FLAG_QUEST_WINDOW) == 0) {
        return;
    }
    window = findTask(QUEST_WINDOW_TASK_ID);
    closeWindow(window->window);
    closeWindow(window->unk27);
    releaseGfxSlot(window->font);
    endTask(window);
    QUEST_WINDOW_TASK_ID = 0;
    clearUiFlag(UI_FLAG_QUEST_WINDOW);
    freeTextBank();
}

/* Calls func_020b59a8; for mode 2, first gives func_020b63ac's buffer the
 * save's Wi-Fi block. */
void func_020798f4(s32 mode, s32 unk) {
    s32 dest;

    if (mode == 2 && func_020b599c() != 0) {
        dest = func_020b63ac();
        if (dest != 0) {
            func_020e2454(dest, data_021db618, sizeof(struct WifiData));
        }
    }
    func_020b59a8(mode, unk);
}

/* Frees the Wi-Fi matching session's buttons, icons, sprites, backgrounds,
 * pictures and fonts, then clears both screens. */
void freeWifiMatching(void) {
    struct WifiMatching *matching;

    if (WIFI_MATCHING == NULL) {
        return;
    }
    matching = findTask(WIFI_MATCHING_TASK_ID);
    if (matching->buttons != -1) {
        closeButtonGroup(matching->buttons);
        matching->buttons = -1;
    }
    freeWifiLinkIcon();
    freeMainSprites();
    freeSubSprites();
    deleteMainActors();
    deleteSubActors();
    endMainActorTask();
    endSubActorTask();
    freeBgGraphics(&matching->work->bgs[1]);
    freeBgGraphics(&matching->work->bgs[0]);
    freeBgGraphics(&matching->work->bgs[2]);
    stopSubPaletteEffectsButFades(matching->unk3C[0]);
    stopSubPaletteEffectsButFades(matching->unk3C[1]);
    stopMainPaletteEffectsButFades(matching->unk44[0]);
    stopMainPaletteEffectsButFades(matching->unk44[1]);
    freeWifiMatchingFonts();
    clearWifiMatchingScreens();
}

/* Whether the Wi-Fi matching session has ended. */
u8 isWifiMatchingEnded(void) {
    u8 ended;

    if (WIFI_MATCHING == NULL) {
        ended = TRUE;
    } else {
        ended = FALSE;
    }
    return ended;
}

/* Whether the Wi-Fi matching session's unk6F is set; TRUE with no session. */
u8 func_020793c0(void) {
    u8 set;
    struct WifiMatching *matching;

    matching = findTask(WIFI_MATCHING_TASK_ID);
    if (matching != NULL) {
        if (matching->unk6F != 0) {
            set = TRUE;
        } else {
            set = FALSE;
        }
        return set;
    }
    return TRUE;
}

/* Sets the Wi-Fi matching session's unk32 to 0x1C20. */
void func_02079390(void) {
    struct WifiMatching *matching;

    matching = findTask(WIFI_MATCHING_TASK_ID);
    if (matching != NULL) {
        matching->unk32 = 0x1C20;
    }
}

/* The Wi-Fi matching session's unk34, or 0 with no session. */
s32 func_02079364(void) {
    struct WifiMatching *matching;

    matching = findTask(WIFI_MATCHING_TASK_ID);
    if (matching != NULL) {
        return matching->unk34;
    }
    return 0;
}

/* Clears the Wi-Fi matching session's unk34. */
void func_02079354(void) {
    func_02079330(0);
}

/* Sets the Wi-Fi matching session's unk34. */
void func_02079330(s32 value) {
    struct WifiMatching *matching;

    matching = findTask(WIFI_MATCHING_TASK_ID);
    if (matching != NULL) {
        matching->unk34 = value;
    }
}

/* Loads the Wi-Fi matching session's fonts. */
void loadWifiMatchingFonts(void) {
    func_020a9ae0(2, 0, 0xF);
    func_020a9ae0(1, 1, 0xF);
    func_020a9ae0(4, 2, 0xF);
    func_020a9ae0(5, 3, 0xF);
    func_020a9ae0(3, 4, 0xF);
    func_020a9c40(2, 5, 0xF);
    func_020a9c40(0, 7, 0xE);
}

/* Frees the Wi-Fi matching session's fonts. */
void freeWifiMatchingFonts(void) {
    func_020a9844(2);
    func_020a9844(1);
    func_020a9844(4);
    func_020a9844(5);
    func_020a9844(3);
    func_020a98a8(2);
    func_020a98a8(0);
}

/* Clears both screens' backgrounds, sprites and blending. */
void clearWifiMatchingScreens(void) {
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
