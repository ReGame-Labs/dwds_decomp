#include "link/wifi_connect.h"
#include "engine/bg/bg_layers.h"
#include "engine/bg/bg_screen_task.h"
#include "engine/data.h"
#include "engine/input/touch.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_create.h"
#include "engine/sprite/sprite_draw.h"
#include "engine/system/display_modes.h"
#include "engine/system/system.h"
#include "engine/text/text_args.h"
#include "engine/text/text_object.h"
#include "engine/ui/buttons.h"
#include "engine/ui/digimon_list.h"
#include "engine/window/message_box.h"
#include "field/actors/actor_create.h"
#include "field/actors/actor_tasks.h"
#include "link/link_session.h"
#include "link/wifi.h"
#include "link/wifi_friend_roster.h"

/* Shows the Wi-Fi connection's error, getWifiErrorKind's kind with
 * getWifiErrorCode's code, and waits for a button or a touch. */
void showWifiError(struct WifiConnect *connect) {
    s32 code;
    u16 step;
    u32 kind;
    u8 unk6E;

    step = connect->step;
    switch ((s32) step) {
        case 0:
            func_020ac6f8();
            connect->step = (u16) (connect->step + 1);
            return;
        case 1:
            code = getWifiErrorCode();
            kind = (u32) getWifiErrorKind();
            switch (kind) {
                default:
                    break;
                case 2:
                    func_0209cfc4(0, code, 5);
                    openFarmMessage(0xB6, 1, 8, 0xA, 0xF, 0x806);
                    break;
                case 3:
                    func_0209cfc4(0, code, 5);
                    openFarmMessage(0xB7, 1, 8, 0xA, 0xF, 0x806);
                    break;
                case 4:
                    func_0209cfc4(0, code, 5);
                    openFarmMessage(0xB8, 1, 8, 0xA, 0xF, 0x806);
                    break;
                case 5:
                    func_0209cfc4(0, code, 5);
                    openFarmMessage(0xB9, 1, 8, 0xA, 0xF, 0x806);
                    break;
                case 6:
                    func_0209cfc4(0, code, 5);
                    openFarmMessage(0xBA, 1, 8, 0xA, 0xF, 0x806);
                    break;
                case 7:
                    func_0209cfc4(0, code, 5);
                    openFarmMessage(0xBB, 1, 8, 0xA, 0xF, 0x806);
                    break;
                case 8:
                    func_0209cfc4(0, code, 5);
                    openFarmMessage(0xBC, 1, 8, 0xA, 0xF, 0x806);
                    break;
                case 9:
                    func_0209cfc4(0, code, 5);
                    openFarmMessage(0xBD, 1, 8, 0xA, 0xF, 0x806);
                    break;
                case 10:
                    func_0209cfc4(0, code, 5);
                    openFarmMessage(0xBE, 1, 8, 0xA, 0xF, 0x806);
                    break;
                case 1:
                    func_0209cfc4(0, code, 5);
                    if (code != 0) {
                        openFarmMessage(0xBF, 1, 8, 0xA, 0xF, 0x806);
                    } else {
                        unk6E = connect->unk6E;
                        if (unk6E == 0) {
                            openFarmMessage(0xC0, 1, 8, 0xA, 0xF, 0x806);
                        } else if (unk6E == 1) {
                            openFarmMessage(0xC1, 1, 8, 0xA, 0xF, 6);
                        }
                    }
                    break;
            }
            connect->step = (u16) (connect->step + 1);
            return;
        case 2:
            if (!(getPadPressed() & 1) && (getTouchPressed() == 0)) {
                return;
            }
            connect->step = 10;
            func_020ac6f8();
            return;
        case 10:
            connect->state = (u16) (connect->state + 1);
            return;
        case 11:
            if (!(getPadPressed() & 1) && (getTouchPressed() == 0)) {
                return;
            }
            connect->state = (u16) (connect->state + 1);
            func_020ac6f8();
            return;
    }
}

/* Starts script program 100: the task that connects to Nintendo Wi-Fi. */
void startWifiConnect(void) {
    struct WifiConnect *connect;

    connect             = createTask(&runWifiConnect, 0x103);
    connect->task.onEnd = NULL;
    connect->state      = 0;
}

/* Shows the signal icon at the top right corner, freeing the other one
 * first. */
void showWifiLinkIcon(s32 palette, s32 unk12) {
    s32 sprite;

    if (MAIN_LINK_ICON == -1) {
        sprite         = createSubSprite(0x3F4, 0xF0, 0, palette, unk12);
        MAIN_LINK_ICON = sprite;
        setSubSpriteBgPriority(sprite, 0);
        func_0203e848(MAIN_LINK_ICON, 0);
        return;
    }
    freeSubSprite(SUB_LINK_ICON);
    sprite         = createSubSprite(0x3F4, 0xF0, 0, palette, unk12);
    MAIN_LINK_ICON = sprite;
    setSubSpriteBgPriority(sprite, 0);
    func_0203e848(MAIN_LINK_ICON, 0);
}

/* Frees the signal icon. */
void freeWifiLinkIcon(void) {
    if (MAIN_LINK_ICON != -1) {
        freeSubSprite(MAIN_LINK_ICON);
        MAIN_LINK_ICON = -1;
    }
}

/* Shows the link level (0 to 3) of func_020f9b1c on the signal icons. */
void updateWifiLinkIcons(void) {
    s32 level;

    switch (func_020f9b1c()) {
        default:
        case 0:
            level = 0;
            break;
        case 1:
            level = 1;
            break;
        case 2:
            level = 2;
            break;
        case 3:
            level = 3;
            break;
    }
    if (SUB_LINK_ICON != -1) {
        setMainSpriteAnim(SUB_LINK_ICON, level, -1);
    }
    if (MAIN_LINK_ICON != -1) {
        setSubSpriteAnim(MAIN_LINK_ICON, level, -1);
    }
}

/* The index of a friend in the roster of a Wi-Fi block, or -1. */
s32 findRosterFriend(struct WifiData *wifi, s32 friendData) {
    s32 index;
    s32 entry;

    if (friendData == 0) {
        return -1;
    }
    for (entry = (s32) wifi->friends, index = 0; index < WIFI_FRIEND_COUNT; index++, entry += sizeof(wifi->friends[0])) {
        if (func_020ff144(entry) != 0 && func_020fec48(friendData, entry) != 0) {
            return index;
        }
    }
    return -1;
}

/* Copies the friend's row of data_021db718 to dest, if it is in the roster. */
void copyRosterFriendRow(struct WifiData *wifi, s32 friendData, void *dest) {
    s32 index;

    index = findRosterFriend(wifi, friendData);
    if (index != -1) {
        func_020e2454(dest, data_021db718[index], sizeof(data_021db718[0]));
    }
}

/* Resets the Wi-Fi menu's and the friend roster list's globals. */
void resetWifiMenuGlobals(void) {
    WIFI_MENU_TASK_ID          = -1;
    WIFI_MENU                  = NULL;
    FRIEND_ROSTER_LIST_TASK_ID = -1;
    FRIEND_ROSTER_LIST         = NULL;
}

/* Starts script program 101: the Wi-Fi menu of the friend roster. */
void startFriendRosterMenu(void) {
    struct WifiMenu *menu;
    struct WifiMenuWork *work;

    func_020a3454(9);
    menu              = createTask(runFriendRosterMenu, 0x11B);
    menu->task.onEnd  = onFriendRosterMenuEnd;
    WIFI_MENU_TASK_ID = getTaskId(menu);
    WIFI_MENU         = menu;
    work              = heapAlloc(sizeof(struct WifiMenuWork), 4);
    menu->work        = work;
    func_02030f18(menu->work, 0, sizeof(struct WifiMenuWork));
    menu->state = 0;
    menu->unk26 = 0;
    menu->unk28 = 0;
}

/* The friend roster menu's onEnd. */
void onFriendRosterMenuEnd(void) {
    struct WifiMenu *menu;
    void *work;

    menu = (struct WifiMenu *) getCurrentTask();
    work = menu->work;
    heapFree(work);
    menu->work        = NULL;
    WIFI_MENU_TASK_ID = -1;
    WIFI_MENU         = NULL;
}

/* Frees the friend roster menu's message, buttons, sprite, backgrounds,
 * pictures and fonts. */
void freeFriendRosterMenu(void) {
    struct WifiMenu *menu;

    if (WIFI_MENU == NULL) {
        return;
    }
    menu = findTask(WIFI_MENU_TASK_ID);
    func_0208577c((u8) menu->message.unk4, menu->message.unkA);
    if (menu->message.width != 0 && menu->message.height != 0) {
        freeWindowImage(&menu->message);
        func_02030f18(&menu->message, 0, sizeof(struct TextWindow));
    }
    if (menu->buttons != -1) {
        closeButtonGroup(menu->buttons);
        menu->buttons = -1;
    }
    freeMainSprite(menu->sprite);
    freeMainSprites();
    freeSubSprites();
    deleteMainActors();
    deleteSubActors();
    endMainActorTask();
    endSubActorTask();
    freeBgGraphics(&menu->work->bgs[1]);
    freeBgGraphics(&menu->work->bgs[0]);
    freeBgGraphics(&menu->work->bgs[2]);
    stopSubPaletteEffectsButFades(menu->unk64[0]);
    stopSubPaletteEffectsButFades(menu->unk64[1]);
    stopMainPaletteEffectsButFades(menu->unk6C[0]);
    stopMainPaletteEffectsButFades(menu->unk6C[1]);
    freeWifiMenuFonts();
    clearWifiMenuScreens();
}

/* Whether the Wi-Fi menu has ended. */
u8 isFriendRosterMenuEnded(void) {
    u8 ended;

    if (WIFI_MENU == NULL) {
        ended = TRUE;
    } else {
        ended = FALSE;
    }
    return ended;
}
