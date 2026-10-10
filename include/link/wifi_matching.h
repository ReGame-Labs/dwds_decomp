#ifndef LINK_WIFI_MATCHING_H
#define LINK_WIFI_MATCHING_H

/* The Wi-Fi matching session: its globals, its end and its fonts; then the
 * quest window. */

#include "link/wifi_matching_screen.h"
#include "types.h"

/* The UI flag (getUiFlag) of an open quest window. */
#define UI_FLAG_QUEST_WINDOW 0x12

/* The quest window, a task. */
struct QuestWindow {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 unk21;
    /* 0x22 */ s16 quest; /* the one shown */
    /* 0x24 */ s16 unk24; /* 0 when it opens */
    /* 0x26 */ s8 font;   /* a font slot, freed by releaseGfxSlot */
    /* 0x27 */ u8 unk27;  /* a window slot */
    /* 0x28 */ u8 window; /* the window the quest is drawn in */
};

extern s32 QUEST_WINDOW_TASK_ID; /* the quest window's task id, 0 for none */

void clearWifiMatchingScreens(void);
void freeWifiMatchingFonts(void);
void loadWifiMatchingFonts(void);
void func_02079330(s32 value);
void func_02079354(void);
s32 func_02079364(void);
void func_02079390(void);
u8 func_020793c0(void);
u8 isWifiMatchingEnded(void);
void freeWifiMatching(void);
void func_020798f4(s32 mode, s32 unk);
void closeQuestWindow(void);
void showQuestWindowQuest(s32 quest, s16 unk24);
s32 drawQuest();
void runQuestWindow();

#endif /* LINK_WIFI_MATCHING_H */
