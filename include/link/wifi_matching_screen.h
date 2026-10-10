#ifndef LINK_WIFI_MATCHING_SCREEN_H
#define LINK_WIFI_MATCHING_SCREEN_H

/* The Wi-Fi matching session's screen ("Searching for player"). */

#include "engine/data.h"
#include "types.h"

/* The Wi-Fi matching session's work block, only the part read in C. */
struct WifiMatchingWork {
    /* 0x00 */ struct BgGraphics bgs[3];
    /* 0x48 */ s32 unk48; /* a sub screen sprite, freed with the buttons */
    /* 0x4C */ u8 unk4C[4];
    /* 0x50 */ s32 sprites[4]; /* sub screen sprites, or -1 */
};

/* The Wi-Fi matching session, a task (runWifiMatching), only the part read in
 * C. */
struct WifiMatching {
    /* 0x00 */ struct Task task;
    /* 0x1C */ struct WifiMatchingWork *work;
    /* 0x20 */ u8 unk20[4];
    /* 0x24 */ s32 buttons; /* a button group's task id, or -1 */
    /* 0x28 */ u8 unk28[0xA];
    /* 0x32 */ s16 unk32; /* set to 0x1C20 by func_02079390 */
    /* 0x34 */ s32 unk34;
    /* 0x38 */ u8 unk38[4];
    /* 0x3C */ s32 unk3C[2]; /* freed by stopSubPaletteEffectsButFades */
    /* 0x44 */ s32 unk44[2]; /* freed by stopMainPaletteEffectsButFades */
    /* 0x4C */ u8 unk4C[0x23];
    /* 0x6F */ u8 unk6F;
};

extern struct WifiMatching *WIFI_MATCHING;
extern s32 WIFI_MATCHING_TASK_ID; /* the Wi-Fi matching session's task id */

void freeWifiMatchingButtons(struct WifiMatching *matching);
void clearWifiMatchingScreen(struct WifiMatching *matching);

#endif /* LINK_WIFI_MATCHING_SCREEN_H */
