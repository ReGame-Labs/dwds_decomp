#ifndef MENUS_WIDGETS_TEXT_LIST_H
#define MENUS_WIDGETS_TEXT_LIST_H

#include "engine/data.h"
#include "types.h"

/* The text lists: 4 slots of tasks, each drawing rows of text into a window's
 * images. */

#define TEXT_LIST_COUNT 4
#define TEXT_LIST_ROWS 8

/* A text list's states. */
#define TEXT_LIST_ACTIVE 0
#define TEXT_LIST_PAUSED 1

/* A text list's task (tickTextList), created by createTextList. */
struct TextListTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ u16 state;
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ u16 unk22;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 imageCount;
    /* 0x30 */ s16 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ u16 unk38;
    /* 0x3A */ u16 unk3A;
    /* 0x3C */ s16 position;
    /* 0x3E */ s16 drawnPosition; /* the position it was last drawn at */
    /* 0x40 */ s16 unk40;
    /* 0x44 */ struct WindowImage *images;
    /* 0x48 */ u8 unk48;
    /* 0x49 */ u8 redraw;
    /* 0x4A */ s8 unk4A[TEXT_LIST_ROWS];
};

struct TextListTask *findTextList(s32 id);
void redrawTextList(s32 id);
s32 closeTextList();
void func_0204c58c(s32 kind);
void func_0204c5e0(s32 kind);
void func_0204bfd8(s32 id, s32 value);
void setTextListPos(s32 id, s16 position);
void func_0204bff8(s32 id, s32 row, s8 value);
void drawTextList(struct TextListTask *task);
void freeTextListImages(struct TextListTask *task);
void tickTextList(void);
void initTextLists(void);
void setTextListPreset(s32 index, s32 value, s16 x, s16 y);
s32 createTextList();

#endif /* MENUS_WIDGETS_TEXT_LIST_H */
