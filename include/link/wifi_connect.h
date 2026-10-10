#ifndef LINK_WIFI_CONNECT_H
#define LINK_WIFI_CONNECT_H

/* Connecting to Nintendo Wi-Fi (script program 100), its signal icons, the
 * friend roster's lookups and the roster menu (script program 101). */

#include "engine/data.h"
#include "types.h"

/* The task that connects to Nintendo Wi-Fi (runWifiConnect). */
struct WifiConnect {
    /* 0x00 */ struct Task task;
    /* 0x1C */ u8 unk1C[0xC];
    /* 0x28 */ u16 state;
    /* 0x2A */ u16 step; /* of the error message (showWifiError) */
    /* 0x2C */ u8 unk2C[0x42];
    /* 0x6E */ u8 unk6E;
};

u8 isFriendRosterMenuEnded(void);
void resetWifiMenuGlobals(void);
void showWifiLinkIcon(s32 palette, s32 unk12);
void startWifiConnect(void);
s32 runWifiConnect();
void showWifiError(struct WifiConnect *connect);
void onFriendRosterMenuEnd(void);
void copyRosterFriendRow(struct WifiData *wifi, s32 friendData, void *dest);
void updateWifiLinkIcons(void);
void freeWifiLinkIcon(void);
s32 findRosterFriend(struct WifiData *wifi, s32 friendData);
void freeFriendRosterMenu(void);
void startFriendRosterMenu(void);

#endif /* LINK_WIFI_CONNECT_H */
