#ifndef ENGINE_SAVE_SAVE_DATA_H
#define ENGINE_SAVE_SAVE_DATA_H

/* Saving the game: the requests to write the save to the card, the task that
 * saves from a script, and the save menu's Yes/No window. */

#include "engine/data.h"
#include "types.h"

/* The bytes of the save that are written to the card. */
#define SAVE_SIZE 0x7DC0

/* What the save writer (runSaveWriter) has to do: four kinds of request, each
 * with its count of tries, and the copy of the save it writes. */
struct SaveWriter {
    /* 0x0 */ u16 state;      /* 0 idle, 1 writing, 9999 failed */
    /* 0x2 */ u8 unk2[2];
    /* 0x4 */ u8 requests[4]; /* set by func_02062654, func_0206267c and func_0206262c */
    /* 0x8 */ u8 tries[4];
    /* 0xC */ void *buffer;   /* SAVE_SIZE rounded up to the card's pages */
};

/* The task that saves the game for a script (startSaveTask makes it). */
struct SaveTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
};

/* The save menu's work block: its backgrounds and its message. */
struct SaveMenuWork {
    /* 0x00 */ struct BgGraphics bgs[4];
    /* 0x60 */ struct TextWindow message;
};

/* The save menu, a task (openSaveMenu makes it, runSaveMenu runs it). */
struct SaveMenu {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ u8 unk1E[2];
    /* 0x20 */ struct SaveMenuWork *work;
    /* 0x24 */ s16 *choice; /* the Yes/No window's, in a 4-byte block */
    /* 0x28 */ s32 buttons; /* the Yes/No window's */
    /* 0x2C */ u8 unk2C[0xC];
    /* 0x38 */ s16 chars[6]; /* allocMainVram's, for 0x80, 10, 0xE4, 16, 0x80 and 0x80 tiles */
    /* 0x44 */ s32 hours;    /* the play time shown */
    /* 0x48 */ s32 minutes;
    /* 0x4C */ s32 seconds;
    /* 0x50 */ s32 unk50; /* freed by stopSubPaletteEffectsButFades */
    /* 0x54 */ s32 unk54; /* freed by stopMainPaletteEffectsButFades */
    /* 0x58 */ s32 unk58;
};

extern struct SaveWriter SAVE_WRITER;
extern s32 SAVE_TASK_RESULT; /* the save task's result: 1 saved, -1 failed */
extern struct Task *SAVE_TASK;
extern struct SaveMenu *SAVE_MENU;
extern s32 SAVE_MENU_TASK_ID; /* the save menu's task id */
/* The Yes/No buttons' rects: x, y, width and height, read as a flat array. */
extern s16 SAVE_CHOICE_RECTS[];

void func_0206262c(void);
void func_02062654(void);
u8 getSaveTaskResult(void);
void func_02062888();
void onSaveTaskEnd(void);
void func_02062b28(void);
void func_02062b48(void);
void clearSaveMenuScreens(void);
void func_02062ea4(void);
s32 runSaveTask();
void startSaveTask(void);
void freeSaveMenuBgs(struct SaveMenu *menu);
BOOL isSaveWriterIdle(void);
void resetSaveWriter(void);
void func_0206267c(void);
void func_02062c60();
void createSaveChoiceButtons(struct SaveMenu *menu);

#endif /* ENGINE_SAVE_SAVE_DATA_H */
