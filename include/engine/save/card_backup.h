#ifndef ENGINE_SAVE_CARD_BACKUP_H
#define ENGINE_SAVE_CARD_BACKUP_H

/* The quest screens (runQuestScreen, opened from the field menu, and the quest
 * list) and the DS card's backup memory, which the save is read from and
 * written to. */

#include "engine/data.h"
#include "types.h"

/* The UI flags (getUiFlag) of the open quest screen and quest list. */
#define UI_FLAG_QUEST_SCREEN 0x10
#define UI_FLAG_QUEST_LIST 0x11

/* What func_020ec31c says the backup memory is, as NitroSDK numbers it. */
#define CARD_BACKUP_EEPROM 1
#define CARD_BACKUP_FLASH 2

/* NitroSDK's request types and modes, as func_020ec330 takes them. */
#define CARD_REQ_READ_BACKUP 6
#define CARD_REQ_WRITE_BACKUP 7
#define CARD_REQ_PROGRAM_BACKUP 8
#define CARD_REQUEST_MODE_RECV 0
#define CARD_REQUEST_MODE_SEND_VERIFY 2

/* The state of the reads and writes of the backup memory. */
struct CardBackup {
    /* 0x00 */ s32 state;  /* 1 ready, 2 done, -1 failed */
    /* 0x04 */ s32 result; /* the last request's, 0 for success */
    /* 0x08 */ s32 unk8;   /* func_020ebc34's */
    /* 0x0C */ u8 unkC[4];
    /* 0x10 */ s32 lockId; /* from func_020e2d7c, 0 for none */
    /* 0x14 */ s32 (*request)(s32 offset, s32 buffer, s32 size);
    /* 0x18 */ u8 unk18[4];
    /* 0x1C */ s32 buffer;
    /* 0x20 */ s32 stride; /* the offset of a chunk is its index times this */
    /* 0x24 */ u8 unk24[0x10];
    /* 0x34 */ u32 chunkCount;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ u32 chunk; /* the next one */
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 offset;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
};

/* The quest screen, a task. */
struct QuestScreen {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u8 unk20[4];
    /* 0x24 */ u8 unk24; /* characters on background 3, freed by func_0208577c */
    /* 0x25 */ u8 unk25; /* freed by func_02085710 */
    /* 0x26 */ u8 unk26; /* freed by stopMainPaletteEffects */
    /* 0x27 */ u8 unk27; /* freed by stopSubPaletteEffects */
};

/* The quest list, a task. */
struct QuestList {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s8 unk20;
    /* 0x21 */ s8 unk21;
    /* 0x22 */ s8 unk22;
    /* 0x23 */ s8 fonts[2]; /* font slots, freed by releaseGfxSlot */
    /* 0x25 */ u8 windows[3];
    /* 0x28 */ u8 unk28[8];
    /* 0x30 */ u8 unk30; /* 0xFF for none; else stopSubPaletteEffects is called */
    /* 0x31 */ u8 unk31[0x3F];
    /* 0x70 */ s32 buttons;
};

extern struct CardBackup CARD_BACKUP;
extern s32 QUEST_SCREEN_TASK_ID; /* the quest screen's task id, 0 for none */
extern s32 QUEST_LIST_TASK_ID; /* the quest list's task id, 0 for none */

s32 func_0207b82c(void);
s32 requestNextBackupChunk(void);
void startBackupRequests(void);
s32 func_0207bdf4(void);
u16 getCardLockId(void);
void releaseCardLock(void);
s32 takeCardLock(void);
s32 isBackupDone(void);
s32 getBackupResult(void);
s32 getBackupPageSize(void);
void closeQuestScreen(void);
void openQuestList(s8 unk21, s8 unk22);
s32 runQuestScreen();
void openQuestScreen(void);
void writeSaveSignature(s32 save, u8 *signature);
s32 isQuestScreenOpen(void);
void func_0207bec8();
s32 isBackupFinished(void);
s32 writeFlash(s32 offset, s32 buffer, s32 size);
s32 readFlash(s32 offset, s32 buffer, s32 size);
s32 writeEeprom(s32 offset, s32 buffer, s32 size);
s32 readEeprom(s32 offset, s32 buffer, s32 size);
s32 func_0207c0f0();
s32 func_0207c290();

#endif /* ENGINE_SAVE_CARD_BACKUP_H */
