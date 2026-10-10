#ifndef MENUS_DIGIMON_DATA_H
#define MENUS_DIGIMON_DATA_H

/* The Digimon menus overlay's (ov006) types and data: the Tamer screen, the
 * item menu, the Digimon menu, the status screen, the trait learning menu, the
 * digivolution screen and the Digimon guide. */

#include "engine/data.h"
#include "types.h"

/* The Tamer screen, the field menu's "Check info for <name>": its task,
 * TAMER_SCREEN, is made by openTamerScreen and run by
 * tickTamerScreen. It shows the Tamer's rank, location, Tamer points and
 * play time (text 0x4A of data_0210e960), on the backgrounds of /dat/bg/mtm_*,
 * with three buttons. */
struct TamerScreen {
    /* 0x00 */ struct Task task;
    /* 0x1C */ u16 state;
    /* 0x1E */ u8 unk1E[2];
    /* 0x20 */ s32 subPaletteEffect;  /* from func_02083e78, stopped by stopSubPaletteEffectsButFades */
    /* 0x24 */ s32 mainPaletteEffect; /* from func_02083ea8, stopped by stopMainPaletteEffectsButFades */
    /* 0x28 */ u32 unk28; /* sprites */
    /* 0x2C */ u32 unk2C;
    /* 0x30 */ s32 buttons;
    /* 0x34 */ s16 choice;
    /* 0x36 */ u8 unk36[2];
    /* 0x38 */ s32 unk38; /* func_0202de00(func_020a101c() * 1000, func_020a000c()) */
    /* 0x3C */ s32 unk3C; /* func_020a02b0() * 1000 / 60 */
    /* 0x40 */ s32 unk40; /* func_020a0570() */
    /* 0x44 */ s16 unk44; /* getHighestLevel() */
    /* 0x46 */ s16 unk46; /* func_020a0428(0) */
    /* 0x48 */ s16 friendCount;
    /* 0x4A */ u16 unk4A; /* from allocMainVram, given back to func_0208577c */
    /* 0x4C */ u16 unk4C; /* from allocSubVram, given back to func_02085710 */
    /* 0x4E */ u8 unk4E[2];
    /* 0x50 */ s32 hours; /* the play time drawn */
    /* 0x54 */ s32 minutes;
    /* 0x58 */ s32 seconds;
    /* 0x5C */ s16 playTimeChar; /* the first character of the play time's text, -1 for none */
};

/* A list shown a few rows at a time, scrolled by the arrows, the d-pad and
 * the scroll bar. */
struct ScrollList {
    /* 0x0 */ s16 count;
    /* 0x2 */ s16 scroll; /* the entry in the first row */
    /* 0x4 */ s16 prevScroll;
    /* 0x6 */ s16 maxScroll;
    /* 0x8 */ s16 cursor; /* the row of the cursor */
    /* 0xA */ s16 prevCursor;
    /* 0xC */ s16 rows; /* shown: the count, up to 6 */
};

/* The backgrounds of the item menu, freed by freeItemMenuBgs, and a text
 * window. */
struct ItemMenuGraphics {
    /* 0x00 */ struct BgGraphics bg[4];
    /* 0x60 */ u8 unk60[4];
    /* 0x64 */ struct TextWindow text;
    /* 0x8C */ u8 unk8C[0x18];
};

/* The item menu, the field menu's "Check inventory": its task,
 * ITEM_MENU, is made by openItemMenu and run by
 * tickItemMenu. A choice between two lists of items, the first of item
 * ids and the second of item ids less 0x1AD. */
struct ItemMenu {
    /* 0x00 */ struct Task task;
    /* 0x1C */ u16 state;
    /* 0x1E */ s16 timer;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ void *unk24;
    /* 0x28 */ s16 choice;
    /* 0x2A */ s16 prevChoice;
    /* 0x2C */ struct ScrollList *list0;
    /* 0x30 */ struct ScrollList *list1;
    /* 0x34 */ struct ScrollList *popup; /* the cursor of the popup menu and of the dialog */
    /* 0x38 */ struct ScrollList *unk38;
    /* 0x3C */ s32 scrollBar;
    /* 0x40 */ s32 choiceButtons;
    /* 0x44 */ s32 list0Buttons;
    /* 0x48 */ s32 arrowButtons;
    /* 0x4C */ s32 popupButtons;
    /* 0x50 */ s32 unk50; /* a button group */
    /* 0x54 */ s32 list1Buttons;
    /* 0x58 */ u32 unk58; /* sprites */
    /* 0x5C */ u32 unk5C;
    /* 0x60 */ u32 unk60;
    /* 0x64 */ u32 scrollBarSprite;
    /* 0x68 */ u32 choiceSprite;
    /* 0x6C */ u32 upArrow;
    /* 0x70 */ u32 downArrow;
    /* 0x74 */ u32 popupSprite;
    /* 0x78 */ u32 dialogSprite;
    /* 0x7C */ s16 *list0Items;
    /* 0x80 */ s16 *list1Items;
    /* 0x84 */ u8 windows[5];
    /* 0x89 */ u8 unk89[3];
    /* 0x8C */ s32 subPaletteEffect;  /* from func_02083e78, stopped by stopSubPaletteEffectsButFades */
    /* 0x90 */ s32 mainPaletteEffect; /* from func_02083ea8, stopped by stopMainPaletteEffectsButFades */
    /* 0x94 */ struct ItemMenuGraphics *graphics;
    /* 0x98 */ s16 itemId;
    /* 0x9A */ s16 unk9A;
};

/* The work of func_ov006_022869cc, the callback of the Digimon menu's unk58
 * buttons. */
struct Ov006Unk58Work {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ u8 unk4; /* func_ov006_022869cc shifts it left until bit 0x10 */
    /* 0x5 */ u8 unk5;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
    /* 0x8 */ u8 unk8;
    /* 0x9 */ u8 unk9;
    /* 0xA */ u8 unkA;
};

/* The block of the heap of the Digimon menu, 0x978 bytes (made by
 * openDigimonMenu). */
struct DigimonMenuWork {
    /* 0x000 */ struct BgGraphics bg[4]; /* loaded by loadDigimonMenuBgs */
    /* 0x060 */ u8 unk60[0x180];
    /* 0x1E0 */ struct Digimon *digimon; /* the one the menu shows */
    /* 0x1E4 */ u8 unk1E4[0x140];      /* at its start, the help text's window */
    /* 0x324 */ u32 unk324;            /* sprites */
    /* 0x328 */ s32 unk328;
    /* 0x32C */ u32 unk32C;
    /* 0x330 */ u32 scrollBarSprite;
    /* 0x334 */ u8 unk334[0xC];
    /* 0x340 */ u32 unk340[5];
    /* 0x354 */ u8 unk354[4];
    /* 0x358 */ u32 popupSprite;
    /* 0x35C */ u32 tabSprite;
    /* 0x360 */ u32 unk360;
    /* 0x364 */ u32 unk364;
    /* 0x368 */ u32 unk368;
    /* 0x36C */ s16 unk36C;
    /* 0x36E */ u8 unk36E[0x4AA];
    /* 0x818 */ struct EquipSlot *equipment[82]; /* the list's, the row's at its scroll plus the row; NULL for none */
    /* 0x960 */ u32 rowSprites[6];               /* one for each row of the list, -1 for none */
};

/* The Digimon menu, the field menu's "Check digimon progress": its task, whose
 * id is DIGIMON_MENU_TASK_ID, is made by openDigimonMenu and run by
 * tickDigimonMenu. Its help texts (data_0210e960's 0x14 "Select a
 * digimon", 0x15 "Check Digimon stats", 0xC techniques, 0xD characteristics,
 * 0xE equipment) give its pages: a Digimon's stats, its techniques, its traits
 * and its equipment. */
struct DigimonMenu {
    /* 0x00 */ struct Task task;
    /* 0x1C */ u16 state;
    /* 0x1E */ u8 unk1E[2];
    /* 0x20 */ void *unk20;
    /* 0x24 */ struct DigimonMenuWork *work;
    /* 0x28 */ struct ScrollList *unk28; /* the cursor of the unk58 buttons */
    /* 0x2C */ struct ScrollList *unk2C;
    /* 0x30 */ struct ScrollList *techniques; /* the cursor of the techniques' rows */
    /* 0x34 */ struct ScrollList *traits;     /* the cursor of the traits' rows */
    /* 0x38 */ struct ScrollList *equipSlots; /* the cursor of the equipment's rows */
    /* 0x3C */ struct ScrollList *popup;      /* the cursor of the menu of three by a row */
    /* 0x40 */ struct ScrollList *tab;   /* the cursor of the three tabs */
    /* 0x44 */ struct ScrollList *list0; /* the lists of the tabs */
    /* 0x48 */ struct ScrollList *list1;
    /* 0x4C */ struct ScrollList *list2;
    /* 0x50 */ struct ScrollList *unk50;
    /* 0x54 */ s32 scrollBar;
    /* 0x58 */ s32 unk58; /* button groups, -1 for none */
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 rowButtons; /* the techniques' or the traits' rows */
    /* 0x64 */ s32 equipSlotButtons;
    /* 0x68 */ s32 popupButtons;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 unk70; /* findTextList's */
    /* 0x74 */ s32 tabButtons;
    /* 0x78 */ s32 list0Buttons;
    /* 0x7C */ s32 list1Buttons;
    /* 0x80 */ s32 list2Buttons;
    /* 0x84 */ s16 timer;
    /* 0x86 */ u8 windows[7]; /* 0xFF for none */
    /* 0x8D */ u8 redraw;     /* read and cleared by func_ov006_02281cd8 */
    /* 0x8E */ u8 hidden;     /* func_ov006_02281cd8 hides what it draws while set */
    /* 0x90 */ s32 subPaletteEffect;  /* from func_02083e78, stopped by stopSubPaletteEffectsButFades */
    /* 0x94 */ s32 mainPaletteEffect; /* from func_02083ea8, stopped by stopMainPaletteEffectsButFades */
};

/* The block of the status screen's task: two text windows, and the record
 * func_020a29c4 builds of the kind of Digimon shown. */
struct StatusScreenWork {
    /* 0x00 */ struct TextWindow text[2];
    /* 0x50 */ struct Digimon digimon;
};

/* The status screen of a kind of Digimon, which the digivolution screen opens
 * for the form selected and the Digimon guide for the Digimon of its cursor:
 * its task, STATUS_SCREEN, whose id is STATUS_SCREEN_TASK_ID, is made by
 * openStatusScreen and run by tickStatusScreen. Its pages are those
 * that main's func_020cad30 shows of a Digimon of the save. */
struct StatusScreen {
    /* 0x00 */ struct Task task;
    /* 0x1C */ u16 state;
    /* 0x1E */ u8 unk1E[2];
    /* 0x20 */ u32 unk20; /* sprites */
    /* 0x24 */ u32 unk24;
    /* 0x28 */ u32 unk28;
    /* 0x2C */ u8 unk2C[4];
    /* 0x30 */ s32 species;  /* func_020a29c4's id, the record's unk4 */
    /* 0x34 */ u8 windows[9]; /* 0xFF for none */
    /* 0x3D */ u8 unk3D[3];
    /* 0x40 */ s32 subPaletteEffect;  /* from func_02083e78, stopped by stopSubPaletteEffectsButFades */
    /* 0x44 */ s32 mainPaletteEffect; /* from func_02083ea8, stopped by stopMainPaletteEffectsButFades */
    /* 0x48 */ s32 buttons;           /* the button group of the page shown, -1 for none */
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ s16 cursor; /* the button of openStatusTechniqueButtons's group */
    /* 0x50 */ u32 flags;  /* 0x1: func_ov006_0228cbc0 draws, and clears it */
    /* 0x54 */ struct StatusScreenWork *work;
};

/* The block of the trait learning menu's task. */
struct LearnTraitGraphics {
    /* 0x00 */ struct BgGraphics bg[2];
    /* 0x30 */ u8 unk30[0xC];
    /* 0x3C */ struct TextWindow text; /* drawn by func_ov006_0228e418 */
};

/* The menu a Digimon whose four traits are set learns a new one in: it puts
 * the trait id into the slot of the Digimon's unk22 the cursor is on, or lets
 * it go (cursor 4). Its messages are FARM_TEXTS's 0x74 to 0x77 ("Unable to
 * learn more traits. Delete a trait?", "Unable to learn <id>. Is this OK?",
 * "Delete <slot> and learn <id>?", "Cancel learning <id>?"). Its task,
 * LEARN_TRAIT_MENU, is made by openLearnTraitMenu and run by
 * tickLearnTraitMenu. */
struct LearnTraitMenu {
    /* 0x00 */ struct Task task;
    /* 0x1C */ struct LearnTraitGraphics *graphics;
    /* 0x20 */ struct ScrollList *list;
    /* 0x24 */ struct Digimon *digimon;
    /* 0x28 */ s16 id; /* of the traits, data_0210c11c */
    /* 0x2A */ u16 state;
    /* 0x2C */ u8 windows[6]; /* 0xFF for none */
    /* 0x32 */ u8 unk32[2];
    /* 0x34 */ s32 buttons;
    /* 0x38 */ s32 subPaletteEffect;  /* from func_02083e78, stopped by stopSubPaletteEffectsButFades */
    /* 0x3C */ s32 mainPaletteEffect; /* from func_02083ea8, stopped by stopMainPaletteEffectsButFades */
    /* 0x40 */ u8 unk40;
};

/* Moves the digivolution screen's tree until the actor followed is in the
 * middle of the screen, 6 pixels a frame across and 4 down. */
struct TreeScroll {
    /* 0x0 */ u16 state; /* 0 waiting for another actor, 1 starting, 10 moving */
    /* 0x4 */ s32 actor;
    /* 0x8 */ s16 stepX;
    /* 0xA */ s16 stepY;
    /* 0xC */ s16 endX;
    /* 0xE */ s16 endY;
};

/* The block of the digivolution screen. The tree has a column for each of the
 * five stages (func_020a30d4's): the forms the digimon has had, from its
 * record, and the three forms each of them can take next. Actors are 0xFFFF
 * where there is none. */
struct DigivolveWork {
    /* 0x000 */ struct BgGraphics bg[3];
    /* 0x048 */ u8 unk48[0x18];
    /* 0x060 */ u32 historyLinks[5]; /* between each form and the one before; [0] unused */
    /* 0x074 */ u32 unk74[15];       /* a sprite for each next form */
    /* 0x0B0 */ u32 stageSprites[5]; /* one look for the digimon's stage, one for the others */
    /* 0x0C4 */ u32 unkC4[15];       /* a sprite for each next form */
    /* 0x100 */ u8 unk100[8];
    /* 0x108 */ u32 unk108[5];
    /* 0x11C */ s16 bgX; /* the tree's scroll, copied for the background */
    /* 0x11E */ s16 bgY;
    /* 0x120 */ u32 cursorSprite;   /* the name of the form selected is drawn next to it */
    /* 0x124 */ s32 nameLabel;      /* func_0209df00's, -1 for none */
    /* 0x128 */ u16 nameLabelState; /* 10 draws it again, 0 idle */
    /* 0x12A */ u8 unk12A[2];
    /* 0x12C */ u32 unk12C;
    /* 0x130 */ u32 menuSprite; /* touching it opens the menu, as the X button does */
    /* 0x134 */ u32 unk134;
    /* 0x138 */ u32 unk138;
    /* 0x13C */ u32 unk13C; /* sprites of the status windows */
    /* 0x140 */ u32 unk140;
    /* 0x144 */ u32 unk144;
    /* 0x148 */ u32 unk148;
    /* 0x14C */ u32 actor;       /* of the digimon, in the first status window */
    /* 0x150 */ u32 targetActor; /* of the form selected, in the second */
    /* 0x154 */ u32 unk154;
    /* 0x158 */ u32 unk158;
    /* 0x15C */ u32 menuSprites[4]; /* of the menu's four choices */
    /* 0x16C */ u8 unk16C[0xC];
    /* 0x178 */ s32 historyActors[5];
    /* 0x18C */ s32 nextActors[15]; /* [stage * 3 + i] */
    /* 0x1C8 */ s32 nextFrom[5];    /* the actor whose next forms the column shows */
    /* 0x1DC */ s16 scrollX;        /* from -0x100 to 0 */
    /* 0x1DE */ s16 scrollY;        /* up to 0 */
    /* 0x1E0 */ s16 historyX[5];
    /* 0x1EA */ s16 historyY[5];
    /* 0x1F4 */ s16 nextX[15];
    /* 0x212 */ s16 nextY[15];
    /* 0x230 */ s32 history[5]; /* species, -1 for none */
    /* 0x244 */ s32 next[15];   /* species, [stage * 3 + i], -1 for none */
    /* 0x280 */ u8 unk280[0x600];
    /* 0x880 */ struct TextWindow texts[3];
    /* 0x8F8 */ struct Digimon preview; /* the digimon as the form selected would make it */
};

/* The digivolution screen, opened from the Digimon menu and by main's
 * func_020cb538, whose help line is text 0xF of data_0210e960, "Check Digimon
 * that can Digivolve or Degenerate": the digimon's tree of forms, its status
 * and that of the form selected, and a menu of four choices for the form. It
 * asks FARM_TEXTS's 0x72 "Digivolve <form> into <form>?" or 0x73
 * "Degenerate <form> into <form>?". Its task, DIGIVOLVE_SCREEN, is made by
 * openDigivolveScreen for a digimon. */
struct DigivolveScreen {
    /* 0x00 */ struct Task task;
    /* 0x1C */ struct DigivolveWork *work;
    /* 0x20 */ struct TreeScroll *scroll;
    /* 0x24 */ struct ScrollList *tree; /* the cursor is the tree's button picked */
    /* 0x28 */ struct ScrollList *menu; /* the cursor is the menu's choice */
    /* 0x2C */ struct Digimon *digimon;
    /* 0x30 */ u16 unk30; /* given to func_020a23e4 or func_020a1f30 */
    /* 0x32 */ u8 unk32[2];
    /* 0x34 */ s32 currentActor; /* the tree's actor of the digimon's own form */
    /* 0x38 */ s32 species;      /* of the actor selected */
    /* 0x3C */ s32 selected;     /* the actor selected */
    /* 0x40 */ s32 chosen;
    /* 0x44 */ u16 state;
    /* 0x46 */ u8 unk46[6];
    /* 0x4C */ s32 treeButtons;
    /* 0x50 */ s32 menuButtons;
    /* 0x54 */ u8 statusWindow;  /* the digimon's */
    /* 0x55 */ u8 previewWindow; /* the form selected's */
    /* 0x56 */ u8 unk56;
    /* 0x57 */ u8 menuWindow;
    /* 0x58 */ u8 unk58;
    /* 0x59 */ u8 unk59[3];
    /* 0x5C */ s32 subPaletteEffect;  /* from func_02083e78, stopped by stopSubPaletteEffectsButFades */
    /* 0x60 */ s32 mainPaletteEffect; /* from func_02083ea8, stopped by stopMainPaletteEffectsButFades */
};

/* The Digimon guide's work block: the ids in each order (0xFFFE for one shown
 * without its name, 0xFFFF past the end) and a copy of each species' data. */
struct DigimonGuideWork {
    /* 0x0000 */ u16 lists[5][SPECIES_COUNT];
    /* 0x10A4 */ struct SpeciesData species[SPECIES_COUNT];
    /* 0x747C */ u8 unk747C[4];
};

/* The Digimon guide (its help texts are /dat/msg/DigZknHelp.sdb's), the task
 * DIGIMON_GUIDE points to (made by openDigimonGuide, run by
 * tickDigimonGuide): a list of the SPECIES_COUNT Digimon ids in one of four
 * orders, scrolled eight rows at a time, a row's sprite shown only where the
 * Digimon's flag of func_020a0f98 is set, and the Digimon of the cursor's row
 * as a battle character on each screen. Four tabs pick what the tab window
 * shows of it. */
struct DigimonGuide {
    /* 0x00 */ struct Task task;
    /* 0x1C */ struct DigimonGuideWork *work; /* data_ov006_0229f548 points to the order shown */
    /* 0x20 */ u16 state;
    /* 0x22 */ u8 unk22[2];
    /* 0x24 */ u32 scrollBarSprite;
    /* 0x28 */ s32 scrollBar;
    /* 0x2C */ s32 list; /* the rows' text, createTextList's */
    /* 0x30 */ s32 rowButtons;
    /* 0x34 */ s32 arrowButtons; /* scroll by a row */
    /* 0x38 */ s32 pageButtons;  /* scroll by seven rows, as left and right do */
    /* 0x3C */ s32 tabButtons;
    /* 0x40 */ s32 unk40;     /* the buttons of sprites 12 and 13 */
    /* 0x44 */ s32 chrButton; /* tapping it, or Y, plays the battle character's sequence 1 */
    /* 0x48 */ s32 orderDial; /* turned to pick the order, openDial's */
    /* 0x4C */ u32 orderSprites[4]; /* placed around the dial */
    /* 0x5C */ s16 dialAngle;       /* 0 to 255 */
    /* 0x5E */ u8 listWindow;       /* the rows are drawn in it */
    /* 0x5F */ u8 unk5F;            /* windows */
    /* 0x60 */ u8 tabWindow;        /* what the tab picked shows */
    /* 0x61 */ u8 unk61;
    /* 0x62 */ u8 nameWindow; /* the cursor's Digimon's name */
    /* 0x63 */ s8 cursor;     /* the row of the cursor */
    /* 0x64 */ s8 rows;
    /* 0x65 */ u8 unk65;
    /* 0x66 */ s16 scroll; /* the entry in the first row */
    /* 0x68 */ s16 prevScroll;
    /* 0x6A */ s16 maxScroll;
    /* 0x6C */ s16 tab; /* 0 to 3 */
    /* 0x6E */ s16 prevTab;
    /* 0x70 */ void *unk70; /* from func_0204bef8 */
    /* 0x74 */ void *unk74; /* from func_0204be5c */
    /* 0x78 */ s16 order;       /* the dial's, -1 to 3 */
    /* 0x7A */ u8 chrChanged;   /* func_ov006_0229cb68 shows the cursor's Digimon again */
    /* 0x7B */ u8 dialTurn;     /* 1 while L turns the dial, 2 while R does */
    /* 0x7C */ u16 actorState;  /* func_ov006_0229c7bc's: 1 walks the cursor's Digimon in, 1001 out */
    /* 0x7E */ s16 slide;
    /* 0x80 */ s16 unk80; /* func_020a0f58's count */
    /* 0x82 */ s16 seenCount;
    /* 0x84 */ s32 wait;
};

extern struct TamerScreen *TAMER_SCREEN;
extern struct BgGraphics data_ov006_0229f428;
extern struct BgGraphics data_ov006_0229f440;
extern struct BgGraphics data_ov006_0229f458;
extern struct BgGraphics data_ov006_0229f470;
extern struct BgGraphics data_ov006_0229f488;
extern struct BgGraphics data_ov006_0229f4a0;
extern struct ItemMenu *ITEM_MENU;
extern struct DigimonMenu *DIGIMON_MENU;
extern s32 DIGIMON_MENU_TASK_ID;
extern s32 STATUS_SCREEN_TASK_ID;
extern struct StatusScreen *STATUS_SCREEN;
extern struct BgGraphics data_ov006_0229f4cc;
extern struct BgGraphics data_ov006_0229f4e4;
extern struct BgGraphics data_ov006_0229f4fc;
extern s8 SUB_WINDOW_FRAME00_SLOT; /* the slot of the sub screen's m_win00 window frame, -1 for none */
extern s8 MAIN_WINDOW_FRAME00_SLOT; /* and the main screen's */
extern struct DigivolveScreen *DIGIVOLVE_SCREEN;
extern struct LearnTraitMenu *LEARN_TRAIT_MENU;
extern s32 data_ov006_0229f540; /* a sub screen sprite of func_ov006_0229be94, -1 for none */
extern struct DigimonGuide *DIGIMON_GUIDE;
extern struct BgGraphics data_ov006_0229f588;
extern struct BgGraphics data_ov006_0229f5a0;
extern struct BgGraphics data_ov006_0229f5b8;
extern struct Rect data_ov006_0229f2c8;
extern s16 data_ov006_0229ef98[2 * 4]; /* x, y, width and height of each button */
extern s16 data_ov006_0229efa8[2 * 4]; /* x, y, width and height of each button */
extern s16 data_ov006_0229f2ec[2 * 4]; /* x, y, width and height of each button */
extern s16 data_ov006_0229f2fc[2 * 4]; /* x, y, width and height of each button */
extern s16 data_ov006_0229f550[8]; /* the slides of func_ov006_0229801c: where each ends */
extern s16 data_ov006_0229f560[8]; /* and its step */
extern s16 *data_ov006_0229f5d0[8]; /* and the value it moves */
extern s16 data_ov006_0229f400[4 * 4]; /* x, y, width and height of each button */
extern s32 GUIDE_MAIN_PALETTE_EFFECT; /* the guide's main screen palette effect */
extern s32 GUIDE_SUB_PALETTE_EFFECT; /* and its sub screen one */
extern u32 data_ov006_0229f610[8]; /* the sprites of the guide's rows */
extern struct TextWindow data_ov006_0229f770[4];
extern s16 data_ov006_0229f528; /* positions the guide places sprites by, slid by func_ov006_0229801c */
extern s16 data_ov006_0229f530;
extern s16 data_ov006_0229f534;
extern s16 data_ov006_0229f538;
extern u16 *data_ov006_0229f548;
extern s16 data_ov006_0229ef78[2 * 4]; /* x, y, width and height of each button */
extern s16 data_ov006_0229ef88[2 * 4]; /* x, y, width and height of each button */
extern s16 data_ov006_0229efb8[3 * 4]; /* x, y, width and height of each button, from the menu's corner */
extern s16 data_ov006_0229efd0[8 * 2]; /* x and y of each icon, in tiles */
extern s16 data_ov006_0229f090[3 * 4]; /* x, y, width and height of each button */
extern s16 data_ov006_0229f0c0[];
extern s16 data_ov006_0229f120[5 * 4]; /* x, y, width and height of each button */
extern s16 data_ov006_0229f178[6 * 4]; /* x, y, width and height of each button */
extern s16 data_ov006_0229f210[6 * 4]; /* x, y, width and height of each button */
extern s16 data_ov006_0229f30c[2 * 4]; /* x, y, width and height of each button */
extern u32 data_ov006_0229f31c[4]; /* the sprites of the guide's tabs */
extern s16 data_ov006_0229f34c[4 * 4]; /* x, y, width and height of each button */
extern s16 data_ov006_0229f3ac[8 * 4]; /* x, y, width and height of each button */
extern s16 data_ov006_0229f0d8[8 * 2]; /* x and y of each icon, in tiles */
extern s16 data_ov006_0229f1a8[8 * 4]; /* x, y, width and height of each button */
extern struct TextWindow data_ov006_0229f630;
extern struct TextWindow data_ov006_0229f658;
extern struct TextWindow data_ov006_0229f680;

#endif /* MENUS_DIGIMON_DATA_H */
