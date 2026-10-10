#ifndef ENGINE_UI_DIGIMON_LIST_H
#define ENGINE_UI_DIGIMON_LIST_H

/* The message window, the menus of MENU_LAYOUTS and the Digimon list (Party,
 * Digibank, All Digimon), with the touch tests and the curve moves they use. */

#include "engine/data.h"
#include "types.h"

struct ButtonGroup;
struct Sprite;

/* The result of a menu or the Digimon list while the player chooses, and when
 * the choice is cancelled (B, the last choice, or the window closed). */
enum MenuResult {
    MENU_RESULT_CHOOSING  = -1,
    MENU_RESULT_CANCELLED = 9999,
};

/* The window of text of MENU_TASK_ID, a task of priority 0x10A: a message
 * (openMessage, run by func_020ac884, UI kind 1) or a menu of a
 * MenuLayout (startMenuTask, run by tickMenu, UI kind 3). */
struct Menu {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 wait; /* frames left to wait before the state runs */
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ u16 flags;
    /* 0x2A */ s16 layout; /* the index of MENU_LAYOUTS */
    /* 0x2C */ s16 cursor;
    /* 0x2E */ s16 count;
    /* 0x30 */ s16 result; /* a MenuResult or the choice */
    /* 0x32 */ u8 unk32[2];
    /* 0x34 */ s32 buttons; /* the button group's id, 0xFFFF for none */
    /* 0x38 */ u8 unk38[2];
    /* 0x3A */ s16 gfxSlot;
    /* 0x3C */ s8 palette;
    /* 0x3D */ s8 unk3D;
    /* 0x3E */ s8 unk3E;
    /* 0x3F */ u8 window;
    /* 0x40 */ u8 unk40[0xC]; /* tickMenu keeps its choices' buttons here */
    /* 0x4C */ void *text;
    /* 0x50 */ s8 unk50[4];
    /* 0x54 */ s8 textX; /* the rect of its first text, in tiles (func_020ac220) */
    /* 0x55 */ s8 textY;
    /* 0x56 */ s8 textWidth;
    /* 0x57 */ s8 textHeight;
    /* 0x58 */ s8 unk58[2];
    /* 0x5A */ s8 unk5A;
    /* 0x5B */ s8 unk5B;
};

/* The list of Digimon of DIGIMON_LIST_TASK_ID (UI kind 2), a task of priority 0x119
 * run by tickDigimonList. It shows six rows of ids from scroll on, with the
 * cursor on one of them. */
struct DigimonList {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 wait;
    /* 0x20 */ u8 unk20[8];
    /* 0x28 */ u16 sort;   /* 0 to 3, sortDigimonList's order */
    /* 0x2A */ s16 page;   /* getDigimonListIds's: -1 the free Digimon, 0 all, or a group */
    /* 0x2C */ s16 scroll; /* the index of ids in the first row */
    /* 0x2E */ s16 cursor; /* the row */
    /* 0x30 */ s16 count;  /* of ids */
    /* 0x32 */ s16 maxCount;
    /* 0x34 */ s32 *ids;
    /* 0x38 */ s16 tabPages[8]; /* func_020ad8a0's page for each tab, less one */
    /* 0x48 */ s32 chosen;      /* the id picked, 0 when cancelled */
    /* 0x4C */ u8 window;
    /* 0x4D */ u8 unk4D; /* a second window, closed with the list */
    /* 0x4E */ u8 unk4E[2];
    /* 0x50 */ s16 gfxSlot;
    /* 0x52 */ s8 palette;
    /* 0x53 */ u8 unk53[2];
    /* 0x55 */ u8 rowButtons[6]; /* in the button group of data_021e5cac */
    /* 0x5B */ u8 unk5B[0xB];
    /* 0x66 */ u16 unk66[6]; /* sub screen sprites, freed with the list */
    /* 0x72 */ u16 unk72[6]; /* sub screen sprites, freed with the list */
    /* 0x7E */ u16 flags;
    /* 0x80 */ s32 scrollBarY; /* in pixels, set from scroll in func_020ad8a0 */
    /* 0x84 */ s32 unk84;
    /* 0x88 */ s16 result;        /* a MenuResult */
    /* 0x8A */ s8 cursorBlink[2]; /* func_020839c8's effects on the cursor's colors */
};

/* (u16 textId, s16 cursor, s32 unused, s8 palette, s8 unk3D, u16 flags), left
 * open: func_0208ae40 passes the flags in an s32. */
void openFarmMessage();
void func_020ad1bc(u16 textId, s8 palette, s8 unk3D, u16 flags);
void nextDigimonListSort(struct DigimonList *list);
void blinkDigimonListCursor(struct DigimonList *list);
void func_020afc1c(void);
BOOL stepCurve(struct Curve *curve);
s32 testBit(s32 index, u16 *bits);
void clearBit(s32 index, u16 *bits);
void setBit(s32 index, u16 *bits);
void func_020b0a78(u32 index);
s32 closeDigimonList();
BOOL isRectTapped(s16 x, s16 y, s16 width, s16 height);
void closeMenu(void);
void setMenuChoices(s32 index, s32 cursor);
s16 getMenuResult(void);
void openMenu(s32 index, s32 cursor, s32 palette, s32 unk3D, u16 flags);
void startMenuTask();
void refreshDigimonList();
void restartDigimonList(void);
void setDigimonListPage(s16 page);
s16 func_020adb8c(void);
s16 getDigimonListSort(void);
s32 getChosenDigimon(void);
s16 getDigimonListScroll(void);
s16 getDigimonListCursor(void);
s16 getDigimonListIds();
BOOL isPointOnSubSprite(s32 sprite, s32 x, s32 y);
BOOL isPointOnMainSprite(s32 sprite, s32 x, s32 y);
void func_020afbdc(s32 id);
void openMessage(void *text, s16 cursor, s8 palette, s8 unk3D, u16 flags);
s32 createLoopingMainSprite(s32 kind, s32 x, s32 y, s32 unk3, u16 unk4, s16 unk1D, u16 unk1C, s16 anim);
u32 createLoopingSubSprite(s32 kind, s32 x, s32 y, s32 unk3, u16 unk4, s16 unk1D, u16 unk1C, s16 anim);
BOOL isSpriteRepeatTapped(s32 sprite);
BOOL isSpriteFastRepeatTapped(s32 sprite);
BOOL isSpriteTapped(s32 sprite);
void updateMenuChoice(s16 touched, s16 cursor, struct ButtonGroup *group);
BOOL isPointOnSprite(struct Sprite *sprite, s32 px, s32 py);

#endif /* ENGINE_UI_DIGIMON_LIST_H */
