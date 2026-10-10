#ifndef LINK_WIFI_FRIEND_ROSTER_H
#define LINK_WIFI_FRIEND_ROSTER_H

/* The Wi-Fi menus' task (script programs 101 and 102, one at a time), the
 * friend roster's list on it, and the helpers they share. */

#include "engine/data.h"
#include "types.h"

/* The work block of a Wi-Fi menu: its backgrounds. */
struct WifiMenuWork {
    /* 0x00 */ struct BgGraphics bgs[3];
};

/* A Wi-Fi menu, a task: the friend roster (runFriendRosterMenu) or the own Friend
 * Code (runFriendCodeMenu). */
struct WifiMenu {
    /* 0x00 */ struct Task task;
    /* 0x1C */ struct WifiMenuWork *work;
    /* 0x20 */ s32 buttons; /* a button group's task id, or -1 */
    /* 0x24 */ s16 state;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 unk2A[0xE];
    /* 0x38 */ s32 sprite; /* freed by freeMainSprite */
    /* 0x3C */ struct TextWindow message;
    /* 0x64 */ s32 unk64[2]; /* freed by stopSubPaletteEffectsButFades */
    /* 0x6C */ s32 unk6C[2]; /* freed by stopMainPaletteEffectsButFades */
};

/* The list of the friend roster on the Wi-Fi menu, a task of its own. */
struct FriendRosterList {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 top;    /* the row at the top */
    /* 0x22 */ s16 cursor; /* from top */
    /* 0x24 */ u8 unk24[8];
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s16 result; /* 0 open, 1 a friend picked; getFriendRosterListResult */
    /* 0x32 */ u8 unk32[0x1A];
    /* 0x4C */ struct TextWindow window;
    /* 0x74 */ u8 unk74[4];
    /* 0x78 */ s16 unk78;
    /* 0x7A */ s16 unk7A;
    /* 0x7C */ u16 unk7C;
};

extern struct WifiMenu *WIFI_MENU;
extern s32 WIFI_MENU_TASK_ID; /* the Wi-Fi menu's task id */
extern s32 FRIEND_ROSTER_LIST_TASK_ID; /* the friend roster list's task id */
extern struct FriendRosterList *FRIEND_ROSTER_LIST;

void onFriendRosterListEnd(void);
void freeWifiMenuFonts(void);
void loadWifiMenuFonts(void);
void clearWifiMenuScreens(void);
void runFriendRosterList();
void openFriendRosterList(s16 top, s16 cursor, s16 c, s16 d, u16 e);
void runFriendRosterMenu();

#endif /* LINK_WIFI_FRIEND_ROSTER_H */
