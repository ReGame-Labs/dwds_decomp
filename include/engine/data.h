#ifndef ENGINE_DATA_H
#define ENGINE_DATA_H

#include "types.h"

struct MapAnimFile;
struct MapAnimFrame;
struct StatsScreen;
struct NNSG2dPaletteData;
struct NNSiFndHeapHead; /* NitroSystem's heap head; a pointer to it is an NNSFndHeapHandle */
struct ExchangeData;

/* One OAM entry, the attributes of a sprite as the hardware reads them: copied
 * a word at a time or read a halfword attribute at a time. */
union OamAttr {
    u32 words[2];
    s16 attr[4];
};

/* The OAM's entries, and its sets of affine parameters (in the fourth
 * attribute of four entries each). */
#define OAM_COUNT 128
#define OAM_AFFINE_COUNT 32

/* The state of a set of buttons, updated once a frame from the buttons held
 * down: each field a mask of PAD_Read's bits. */
struct Pad {
    /* 0x00 */ u16 held;
    /* 0x02 */ u16 pressed;    /* down this frame and up the last */
    /* 0x04 */ u16 released;   /* up this frame and down the last */
    /* 0x06 */ u16 fastRepeat; /* pressed, then every frame once held for 16 frames */
    /* 0x08 */ u16 longHeld;   /* held, once held for 60 frames */
    /* 0x0A */ u16 repeat;     /* pressed, then every 4th frame once held for 16 frames */
    /* 0x0C */ u16 doubleTap;  /* pressed twice within 20 frames, for one frame */
    /* 0x0E */ u16 prevHeld;
    /* 0x10 */ s32 holdFrames;
    /* 0x14 */ s32 longHoldFrames;
    /* 0x18 */ s32 repeatFrames;
    /* 0x1C */ s32 doubleTapFrames;
    /* 0x20 */ s32 doubleTapState; /* 0 waiting, 1 pressed once, 2 pressed twice */
    /* 0x24 */ u16 doubleTapKeys;
};

/* The head of a task: createTask takes one from a pool of 0x100-byte
 * blocks and links it in by priority, runTasks runs every task once a
 * frame and removeEndedTasks unlinks the ended ones, calling onEnd first. The
 * rest of the block is the task's own. */
/* The affine parameters of a background (G2_SetBGxAffine's). */
struct BgAffine {
    /* 0x00 */ s16 matrix[4]; /* in 8.8: a, b, c, d */
    /* 0x08 */ s32 centerX;
    /* 0x0C */ s32 centerY;
    /* 0x10 */ s32 x;
    /* 0x14 */ s32 y;
};

struct Task {
    /* 0x00 */ void (*run)(void);
    /* 0x04 */ struct Task *prev;
    /* 0x08 */ struct Task *next;
    /* 0x0C */ s32 ended;    /* set by endTask */
    /* 0x10 */ void (*onEnd)(); /* called with the task by removeEndedTasks */
    /* 0x14 */ s32 id;       /* findTask finds a task by it */
    /* 0x18 */ u16 priority; /* lowest first */
};

/* A group of touch buttons, a task of its own (createButtonGroup). Its callback
 * gets the button touched, or -1, the cursor and the group. */
struct ButtonGroup {
    struct Task task;
    s16 unk1C;
    s16 wait; /* frames before it first runs */
    s16 unk20;
    u16 flags; /* 0x8 no sound when a new button is touched, 0x80 paused */
    s16 count;
    s16 touched;     /* the button touched, -1 for none */
    s16 cursor;      /* the button the A button picks */
    s16 touchFrames; /* how long the same button has been touched */
    u8 buttons[32];  /* indexes of BUTTONS, 0xFF for none */
    void (*callback)(s16 touched, s16 cursor, struct ButtonGroup *group);
    s16 work[8]; /* the callback's own, cleared when the group is made */
};

#define TILE_SIZE 8 /* in pixels */

/* One of the 8 windows of getWindow, placed and sized in 8-pixel tiles. */
struct Window {
    u16 flags;
    s8 unk2;
    s8 unk3;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u16 unkA;
    u16 unkC;
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    void *unk20;
    void *unk24;
    u8 index;
    s8 gfxSlot;
    s16 unk2A;
    s16 unk2C;
    u8 sprites[20]; /* 0xFF when unused, freed with the window */
    void (*callback)(u16 flags, struct Window *window); /* on update and close */
};

/* What func_020a91c4 makes a window of, returning its index: it copies x, y,
 * width, height and gfxSlot to the window's own, unk8 and unkA to its unk2A
 * and unk2C, unk10 and unk12 to its unk4 and unk6, and loads unk14, unk16 and
 * unk18 unless 0xFFFF. */
struct WindowParams {
    u16 flags;
    s16 x;
    s16 y;
    s8 gfxSlot;
    s16 unk8;
    s16 unkA;
    s16 width;
    s16 height;
    u16 unk10;
    u16 unk12;
    u16 unk14;
    u16 unk16;
    u16 unk18;
    void (*callback)(u16 flags, struct Window *window);
};

/* One of the 24 graphics slots of getGfxSlot, 0x2C bytes. */
struct GfxSlot {
    u16 flags; /* bit 0: in use */
    s16 file;  /* set by func_020aa220 */
    u8 unk4[2];
    u16 unk6;
    s16 users;   /* func_020aa068 counts one in, releaseGfxSlot one out and
                * frees the slot's buffers at 0 */
    s16 palette; /* the palette row of its tiles (func_020a91c4) */
    s16 unkC;
    u16 unkE;
    u8 unk10[8];
    u16 *unk18; /* the file as loaded: a u16[4] header with the width and
                 * height of a frame in pixels at [2] and [3], then the frames,
                 * each a u16 and its tiles (func_020a5ecc) */
    u8 unk1C[0xC];
    void *unk28;
};

/* A picture of engine/text/text_object.c's that a window shows, freed by freeWindowImage:
 * a canvas texts are printed into (func_020a5338). */
struct WindowImage {
    /* 0x00 */ u32 flags;   /* 0 for none; see WINDOW_IMAGE_* in engine/text/text_object.h */
    /* 0x04 */ u16 bg;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ u16 tiles;   /* taken when WINDOW_IMAGE_TILES is set */
    /* 0x0C */ s16 file;    /* the graphics file of its slot (func_020a60bc) */
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ s16 width;   /* in tiles */
    /* 0x14 */ s16 height;  /* in tiles */
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ void *pixels; /* its tiles' data */
    /* 0x20 */ void *map;
    /* 0x24 */ s32 unk24;
};

#define PANEL_IN_USE 1 /* in a panel's flags */
#define PANEL_ON_SUB_SCREEN 1 /* in a panel's screenFlags: its sprites are */
#define PANEL_COUNT 3

/* A panel of menus/field_menu/panel.c's: a 10 by 4 tile area of a window, two images and
 * a sprite. */
struct Panel {
    /* 0x00 */ u8 window;
    /* 0x01 */ u8 flags;
    /* 0x02 */ s16 x; /* in tiles, in the window */
    /* 0x04 */ s16 y;
    /* 0x06 */ u8 unk6[6];
    /* 0x0C */ s32 sprite;
    /* 0x10 */ u8 unk10[0xA];
    /* 0x1A */ u16 screenFlags;
    /* 0x1C */ u8 unk1C[4];
    /* 0x20 */ struct WindowImage images[2];
    /* 0x70 */ u8 unk70[0xA4];
};

/* A panel of menus/field_menu/party_panel.c's, one for each Digimon of the party: a 13 by 4
 * tile area of a window, four images and three sprites. */
struct PartyPanel {
    /* 0x00 */ u8 window;
    /* 0x01 */ u8 flags;
    /* 0x02 */ s16 x; /* in tiles, in the window */
    /* 0x04 */ s16 y;
    /* 0x06 */ u8 unk6[6];
    /* 0x0C */ s32 sprite;
    /* 0x10 */ u8 unk10[4];
    /* 0x14 */ s32 sprite2;
    /* 0x18 */ u8 unk18[4];
    /* 0x1C */ s32 sprite1;
    /* 0x20 */ u8 unk20[0xA];
    /* 0x2A */ u16 screenFlags;
    /* 0x2C */ u8 unk2C[4];
    /* 0x30 */ struct WindowImage images[4];
    /* 0xD0 */ u8 unkD0[0x148];
};

/* The block of a digimon's record that func_020a23e4 (digivolving) updates:
 * forms has the species it took at each stage, which the digivolution screen
 * shows as the forms it has had. func_020a2894 sets it up for a new Digimon. */
struct DigimonHistory {
    /* 0x00 */ s32 unk0;     /* func_020a23e4: 0x18 if unk4E was 0, 0x10 if 1,
                          * else 0 */
    /* 0x04 */ s32 forms[5]; /* by stage */
    /* 0x18 */ u8 unk18[0x36];
    /* 0x4E */ u8 unk4E; /* a stage, the new one after func_020a23e4 unless it
                          * was 4 */
    /* 0x4F */ u8 unk4F;
    /* 0x50 */ s16 unk50;          /* the species' unk16 */
    /* 0x52 */ s16 resistances[7]; /* the species' (struct SpeciesData) */
};

/* A parent or a grandparent of a Digimon, as its family tree (func_020985d0)
 * shows it. */
struct DigimonAncestor {
    /* 0x0 */ s16 species;      /* as a Digimon's unk4 */
    /* 0x2 */ u8 tamerName[6]; /* of the tamer who raised it */
    /* 0x8 */ u8 name[10];
};

/* A Digimon's record, one of the 40 in the save at data_021db82c:
 * getDigimonAt returns one by index and getDigimon by its id.
 * func_020a29c4 builds a new one from its species' record; the fields it fills
 * from a known field of struct SpeciesData say so below. */
struct Digimon {
    /* 0x000 */ s32 id; /* 0 for an empty record */
    /* 0x004 */ s32 unk4; /* its species, the id loadSpeciesData takes */
    /* 0x008 */ u8 name[0x12]; /* the species' name at first, 0xFFFF-ended */
    /* 0x01A */ u8 unk1A; /* the species' unk3; also the animation of its icon
                           * on its battle panel */
    /* 0x01B */ u8 expCurve; /* its row of EXP_CURVES */
    /* 0x01C */ u8 growth;   /* its row of STAT_GROWTHS */
    /* 0x01D */ u8 unk1D;
    /* 0x01E */ u8 unk1E; /* its stage (getSpeciesStage); its row of
                           * FOOD_PER_STAGE, what it costs a group */
    /* 0x01F */ s8 eggKind; /* of an egg (flag 0x10 of unk108): its entry of DIGI_EGGS */
    /* 0x020 */ s16 eggSize; /* of an egg, by func_020994ac */
    /* 0x022 */ s16 unk22[4]; /* its abilities, ids of data_0210c11c, -1 for
                               * none; the species' ability first */
    /* 0x02A */ u8 unk2A[2];
    /* 0x02C */ s32 unk2C[4]; /* one for each of unk22: the unk4 it was set with */
    /* 0x03C */ s32 hp;
    /* 0x040 */ s32 maxHp;
    /* 0x044 */ s16 mp;
    /* 0x046 */ s16 maxMp;
    /* 0x048 */ s16 unk48; /* attack: the species' at first; stat 1 of battle/ability_bonus.c */
    /* 0x04A */ s16 unk4A; /* defense */
    /* 0x04C */ s16 unk4C; /* spirit */
    /* 0x04E */ s16 unk4E; /* speed */
    /* 0x050 */ s16 unk50; /* the species' unk12 */
    /* 0x052 */ s16 maxLevel; /* the species' aptitude */
    /* 0x054 */ u16 unk54[7]; /* its skills, ids of data_02113698 (func_020a1268);
                               * 0xFFFF, or any id from 0x1B3, ends them; the
                               * species' four first */
    /* 0x062 */ u8 unk62[0xE];
    /* 0x070 */ s16 unk70;
    /* 0x072 */ s16 unk72;
    /* 0x074 */ s16 level;
    /* 0x076 */ u8 unk76[2];
    /* 0x078 */ s32 exp[8]; /* each up to 99999 */
    /* 0x098 */ s32 unk98;
    /* 0x09C */ s32 expToNext;
    /* 0x0A0 */ struct DigimonHistory history;
    /* 0x100 */ u16 unk100; /* 0xFFFF for none */
    /* 0x102 */ u8 unk102[2];
    /* 0x104 */ s32 flags;
    /* 0x108 */ u16 unk108; /* func_020a2c9c; DIGIMON_GUEST and DIGIMON_LENT (func_020a2d34 sets,
                             * func_020a2cc0 clears); 0x10: an egg, 0x20: one of the
                             * other DS's (packExchangeData) */
    /* 0x10A */ u8 unk10A[2];
    /* 0x10C */ s32 unk10C; /* a guest's: func_020719e0's when it came */
    /* 0x110 */ s32 homeId; /* a guest's: its id in its owner's save */
    /* 0x114 */ struct DigimonAncestor parents[2];
    /* 0x138 */ struct DigimonAncestor grandparents[4];
};
/* Bits of a Digimon's unk108, set by a training exchange (receiveTrainingGuest). */
#define DIGIMON_GUEST 2 /* another player's, here to be trained */
#define DIGIMON_LENT 4  /* away at another player's */

/* What drawStatusWindow needs to draw a digimon's status in a window, at a place
 * in tiles from the window's corner. */
struct StatusParams {
    u8 window;
    s16 x;
    s16 y;
    s16 unk6;
    s16 unk8;
    struct Digimon *digimon;
    u16 unk10;
    u16 unk12;
    u16 unk14;
    u16 unk16;
    u16 unk18[5];
    s16 unk22;
    s16 unk24;
    s16 unk26;
    u16 unk28;
    u16 unk2A;
    u8 unk2C;
};

/* What func_02051edc, func_02053200, func_020539ac, func_02054e00,
 * func_02056940 and drawDigimonDetail need to show what each shows of a Digimon in
 * a window, at a place in tiles from the window's corner: one display of each
 * kind a slot, as with drawStatusWindow. */
struct Params02051edc {
    u8 window;
    s16 x;
    s16 y;
    struct Digimon *digimon;
    u16 unkC;
    u16 unkE;
    s16 unk10;
    s16 unk12;
    u16 unk14;
    u16 unk16;
};

struct Params02053200 {
    u8 window;
    s16 x;
    s16 y;
    struct Digimon *digimon;
    u16 unkC;
    s16 unkE;
    s16 unk10;
    u16 unk12;
    u16 unk14;
};

struct Params020539ac {
    u8 window;
    s16 x;
    s16 y;
    s16 unk6;
    s16 unk8;
    u16 unkA; /* an id of data_0210c11c (func_020a1250) */
    s32 unkC;
    u16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    u16 unk18;
    u16 unk1A;
};

struct Params02054e00 {
    u8 window;
    s16 x;
    s16 y;
    struct Digimon *digimon;
    u16 unkC;
    u16 unkE;
    u16 unk10;
    u16 unk12;
    u16 unk14[6];
    s16 unk20;
    s16 unk22;
    u16 unk24;
    u16 unk26;
};

struct Params02056940 {
    u8 window;
    s16 x;
    s16 y;
    s16 unk6;
    s16 unk8;
    u16 item; /* an id of data_02113698 (func_020a1268), 0xFFFF for none */
    u16 unkC;
    u16 unkE;
    u16 unk10;
    s16 unk12;
    s16 unk14;
    u16 unk16;
    u16 unk18;
};

struct Params02059d8c {
    u8 window;
    s16 x;
    s16 y;
    struct Digimon *digimon;
    u16 unkC;
    u16 unkE;
    u16 unk10;
    u16 unk12;
    u16 unk14[5];
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    u16 unk24;
    u16 unk26;
};

/* One of the 4 farms in the save at FARMS, 0x6C bytes:
 * getGroup returns one by slot and getGroupById by its id. Each of the
 * five levels starts at 1 and picks an entry of the kind's rows (struct
 * FarmKind); the farm upgrade shop raises them. */
struct Farm {
    /* 0x00 */ s32 id;   /* 0 for a free slot */
    /* 0x04 */ s32 unk4; /* the save's unk1E0 when it was made */
    /* 0x08 */ u16 name[10]; /* 0xFFFF-terminated text */
    /* 0x1C */ s8 kind;      /* its entry of FARM_KINDS */
    /* 0x1D */ s8 capacityLevel; /* how many digimon it holds; "Increase Size" */
    /* 0x1E */ s8 goodsLevel;    /* how many goods it holds; "Increase Size" */
    /* 0x1F */ s8 expLevel;      /* the EXP it gives a day; "Increase EXP" */
    /* 0x20 */ s8 foodLevel;     /* the food it makes a day; "Increase Food" */
    /* 0x21 */ s8 layoutLevel;   /* its map; "Increase Size" */
    /* 0x22 */ u8 unk22[2];
    /* 0x24 */ s32 goods[8];   /* ids of its goods, for findFarmGoods */
    /* 0x44 */ s32 digimon[8]; /* ids for getDigimon */
    /* 0x64 */ s32 unk64;      /* the digimon whose coming gave the others flag 0x20 */
    /* 0x68 */ u8 unk68[4];
};

/* Farm goods (fghelp.sdb): one of the 50 of PLAYER_GOODS, or the one
 * TEMP_FARM_GOODS points to (id -2). It grows through three entries of
 * FARM_GOODS_DATA in a row. */
struct FarmGoods {
    /* 0x00 */ s32 id;   /* 0 for a free entry */
    /* 0x04 */ u16 dataIndex; /* its entry of FARM_GOODS_DATA, the one of its stage */
    /* 0x06 */ u8 unk6[2];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s8 unkC;
    /* 0x0D */ s8 stage;     /* 1 to 3 */
    /* 0x0E */ s8 unkE;      /* counted up to 99 by ageFarmGoods */
    /* 0x0F */ s8 countdown; /* growFarmGoods calls left until the next stage */
    /* 0x10 */ u8 flags;     /* bit 0: it grew at the last growFarmGoods */
};

/* The player's name as the name entry writes it (setNameEntry with up to 5
 * characters), ended by 0xFFFF. The characters are 16-bit, but the name is
 * copied a byte at a time (packExchangeData), so it is held as bytes. */
struct PlayerName {
    /* 0x0 */ u8 text[12];
};

/* A kind of DigiEgg, one of the 48 of DIGI_EGGS: what it can hatch into
 * and what it needs to hatch. */
struct DigiEgg {
    /* 0x00 */ u8 unk0[0x10];
    /* 0x10 */ s16 species[3]; /* -1 for none */
    /* 0x16 */ s8 chance[3];   /* in percent, summed up: species[i] hatches
                              * below chance[i] */
    /* 0x19 */ s8 conditions[3]; /* for func_020995a4, the texts of tamaf.sdb */
    /* 0x1C */ s32 values[3];    /* of the conditions */
};

/* The DigiEgg gallery's record of a kind of egg, one of the 48 of
 * EGG_GALLERY. */
struct EggRecord {
    /* 0x0 */ u8 hatched; /* bit i: species[i] of the kind hatched */
    /* 0x1 */ s8 count;   /* of the eggs made, up to 99 */
    /* 0x2 */ s16 parentA; /* the species of the parents of the biggest */
    /* 0x4 */ s16 parentB;
    /* 0x6 */ s16 bestSize;
};

/* The records of the save at data_021e0af8 that the link play counts, as far
 * as the code reads them. */
struct LinkRecords {
    /* 0x00 */ u8 unk0[0x48];
    /* 0x48 */ s16 linkWins;   /* up to 999 */
    /* 0x4A */ s16 linkLosses; /* up to 999 */
    /* 0x4C */ s16 visits;     /* farm visits, up to 99 */
};

/* An item given to a Digimon of a group, one of the 8 of data_021df9d0. */
struct DigimonItem {
    s32 owner; /* 0 for a free entry */
    s32 digimon;
    s16 item;
    s8 kind;
};

/* What the game counts of a species, one of the 426 of SPECIES_RECORDS
 * (func_020a0470): three counts, each 0 to 999. */
struct SpeciesRecord {
    u32 count0 : 10; /* func_020a0684 */
    u32 count1 : 10; /* func_020a05e4, summed by func_020a0570 */
    u32 count2 : 10; /* func_020a04c0; from 100 on, the species' flags are set */
    u32 unk : 2;
};

/* The save block at data_021db5f8, as far as it is mapped. The code that
 * still reaches the block by its offsets has data_021db5f8 declared an s32, so
 * the code that uses the fields reaches it through SAVE. */
struct SaveData {
    /* 0x0000 */ u8 unk0[0x1E0];
    /* 0x01E0 */ s32 unk1E0;
    /* 0x01E4 */ struct PlayerName playerName; /* PLAYER_NAME: up to 5 characters,
                                                * from the name entry of script
                                                * command 0x13B */
    /* 0x01F0 */ u32 money; /* up to 999999 (addMoney); the equipment shop
                             * shows it under "Money" */
    /* 0x01F4 */ s32 food;  /* the farms' food, 0 to 999999 (addFood); the farm
                            * goods shop shows it under "Food", and the groups'
                            * upkeep is paid from it */
    /* 0x01F8 */ s32 playTime; /* 64 a second (PLAY_TIME_TICKS): setPlayTime sets
                                * it from hours, minutes and seconds */
    /* 0x01FC */ u32 groupTimer; /* the frames tickFarmDayTimer counts; cleared
                                  * with the farm's flags by func_020b4b80 */
    /* 0x0200 */ u8 unk200[4];   /* data_021db7f8 */
    /* 0x0204 */ s16 day; /* strongly inferred: 0 to 999, 1 in a new game
                           * (initNewGame); a script command adds 1 and the group
                           * items' "grew" flags clear (func_020a0764) */
    /* 0x0206 */ u8 unk206[2];
    /* 0x0208 */ u32 lastId; /* the last id takeNextId gave a Digimon, a group
                              * or a group's item */
    /* 0x020C */ s32 party[10]; /* data_021db804: ids of Digimon, 0 for none */
    /* 0x0234 */ struct Digimon digimon[40]; /* data_021db82c */
    /* 0x3E34 */ u8 unk3E34;
    /* 0x3E35 */ u8 unk3E35[3];
    /* 0x3E38 */ s32 unk3E38; /* up to 999999 (func_020a0864) */
    /* 0x3E3C */ s8 groupOrder[4];           /* FARM_ORDER: slots of groups,
                                    * -1 for none */
    /* 0x3E40 */ struct Farm groups[4];     /* FARMS */
    /* 0x3FF0 */ struct FarmGoods items[50]; /* PLAYER_GOODS */
    /* 0x43D8 */ struct DigimonItem digimonItems[8]; /* data_021df9d0 */
    /* 0x4438 */ s32 unk4438;
    /* 0x443C */ s32 unk443C; /* a Digimon id, or 0 (func_020a01d8) */
    /* 0x4440 */ s16 highestLevel; /* of the Digimon kept (recordHighestLevel) */
    /* 0x4442 */ u8 unk4442[2];
    /* 0x4444 */ s16 unk4444; /* up to 9999, only ever raised (func_020a0428) */
};

#define SAVE ((struct SaveData *) &data_021db5f8)

/* NitroSystem's NNSG2dScreenData: a background's map of tiles. */
struct ScreenData {
    u16 width;
    u16 height;
    u16 colorMode;
    u16 format;
    u32 size;
    u16 data[1];
};

/* A background's graphics: the palette, character and screen files as
 * loaded, and the data NitroSystem unpacked from each (loadPaletteFile,
 * loadCharFile and loadScreenFile load them). */
struct BgGraphics {
    /* 0x00 */ void *paletteFile;
    /* 0x04 */ void *charFile;
    /* 0x08 */ void *screenFile;
    /* 0x0C */ struct NNSG2dPaletteData *palette;
    /* 0x10 */ void *chars;
    /* 0x14 */ struct ScreenData *screen;
};

/* What copyMainBgScreenAndFlush copies onto a background's screen: a rect of tiles of
 * the screen data src, which is srcWidth by srcHeight tiles (32 by 32 for a
 * 256 by 256 screen). A null src clears the rect. Inferred from its callers. */
struct ScreenCopy {
    u8 bg;
    s16 unk2;
    s16 unk4;
    s16 x;
    s16 y;
    s16 srcX;
    s16 srcY;
    s16 width;
    s16 height;
    u16 *src;
    s16 srcWidth;
    s16 srcHeight;
};

/* The tasks below step through numbered states, idle while wait counts down.
 * Their first 0x1C bytes are the task list's own (see createTask). */
struct StateTask {
    struct Task task;
    s32 state;
    s32 wait;
};

/* Fades a script thread's slot's palettes in or out and wakes the thread. */
struct PaletteFadeTask {
    u8 unk0[0x1C];
    s32 state;
    s32 wait;
    u8 unk24[0x40];
    u8 thread;
    u8 unk65[3];
    s16 slot;
    u16 unk6A;
    s16 paletteRow;
    s16 paletteRowCount;
    s32 fade; /* the palette fade's handle */
};

/* Calls a start function, then an update function every frame until it
 * returns nonzero, both picked from a table by index. */
struct ProgramTask {
    u8 unk0[0x1C];
    s32 state;
    s32 wait;
    u8 unk24[0x40];
    s16 index;
    u8 thread; /* the script thread to wake when done */
};

/* Slides a window in or out and wakes a script thread. */
struct WindowSlideTask {
    u8 unk0[0x1C];
    s32 state;
    s32 wait;
    u8 unk24[0x40];
    u8 thread;
};

/* A 16.16 fixed-point number, whose halves are also read and written on their
 * own: the whole part is the pixel coordinate. */
union Fixed16 {
    s32 value;
    struct {
        u16 frac;
        s16 whole;
    } part;
};

/* A sprite of the battle's sprite table, which forwards its changes once a
 * frame to the sprite it owns in one of the two screens' sprite pools: a handle
 * below SUB_SPRITE_HANDLE is the main screen's, from it the sub screen's. */
enum SpriteSlotFlag {
    SPRITE_SLOT_USED               = 0x1,
    SPRITE_SLOT_SHOWN              = 0x2,
    SPRITE_SLOT_MOVING             = 0x4, /* by (dx, dy) a frame, after moveDelay frames */
    SPRITE_SLOT_CREATE_NEXT        = 0x10000, /* its pool sprite is made next frame, */
    SPRITE_SLOT_CREATE             = 0x20000, /* then this one */
    SPRITE_SLOT_SHOW               = 0x40000,
    SPRITE_SLOT_HIDE               = 0x80000,
    SPRITE_SLOT_MOVED              = 0x100000,
    SPRITE_SLOT_MOVE_TIMED         = 0x200000, /* moving for moveFrames frames */
    SPRITE_SLOT_RELEASE_AFTER_MOVE = 0x400000,
    SPRITE_SLOT_PALETTE_CHANGED    = 0x1000000,
    SPRITE_SLOT_PRIORITY_CHANGED   = 0x2000000,
    SPRITE_SLOT_UNK29_CHANGED      = 0x4000000,
    SPRITE_SLOT_ANIMATION_CHANGED  = 0x8000000,
    SPRITE_SLOT_SUB_SCREEN         = 0x80000000
};

#define SPRITE_SLOT_COUNT 256

struct SpriteSlot {
    /* 0x00 */ u32 flags; /* enum SpriteSlotFlag */
    /* 0x04 */ s32 index;
    /* 0x08 */ u16 spriteId;
    /* 0x0C */ u32 handle; /* before creation, -1 or -2 for any free sprite of the main or the sub pool */
    /* 0x10 */ u16 palette;
    /* 0x12 */ u16 unk12;  /* the pool sprite's unk29 */
    /* 0x14 */ union Fixed16 x;
    /* 0x18 */ union Fixed16 y;
    /* 0x1C */ union Fixed16 dx;
    /* 0x20 */ union Fixed16 dy;
    /* 0x24 */ u16 moveFrames;
    /* 0x26 */ u16 moveDelay;
    /* 0x28 */ u8 priority; /* the OAM priority */
    /* 0x29 */ u8 unk29;    /* the pool sprite's unk1D */
    /* 0x2A */ u16 animation;
};

struct FixedPos {
    union Fixed16 x;
    union Fixed16 y;
};

/* A font's metrics, as far as the text windows read them. */
struct Font {
    u8 unk0[0xA];
    s16 unkA;
    s16 unkC;
    u16 charWidth; /* in pixels */
};

/* A window that text is drawn into, its size in 8-pixel tiles. */
struct TextWindow {
    s32 flags;
    u16 unk4; /* the background func_020a5d1c draws it on */
    s16 unk6;
    s16 unk8;
    u16 unkA; /* its first character; 0xFFFF: allocated by func_020a6b10 */
    u16 font;
    s16 unkE;
    u16 unk10;
    s16 width;
    s16 height;
    s16 unk16;
    s16 unk18;
    void *unk1C; /* its characters, 32 bytes a tile */
    void *unk20; /* its map, a halfword a tile */
    s16 unk24;
    s16 unk26;
};

/* What a battle unit's panel shows of it: two numbers that roll toward a new
 * value, a step a frame for a number of frames, and a byte whose changes the
 * panel follows. */
struct UnitStatus {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 shown0;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 shown1;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ u8 rollFrames0;
    /* 0x0F */ u8 rollFrames1;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 shownUnk10;
    /* 0x12 */ u16 unk12;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ union Fixed16 roll0;
    /* 0x1C */ s32 rollStep0;
    /* 0x20 */ union Fixed16 roll1;
    /* 0x24 */ s32 rollStep1;
};

/* A number drawn with sprites, a digit per half sprite: set up by
 * func_020a503c and redrawn at (x, y) by func_020a4980 and func_020a4ad4. */
struct NumberSprite {
    u8 unk00;
    u8 unk01;
    u16 unk02; /* 0xFFFF for func_020a503c to find one */
    u8 palette;
    u8 unk05;
    s8 digits;
    s32 value;
    s32 unk0C;
    s32 unk10;
    s16 unk14;
    s16 unk16;
    s16 x;
    s16 y;
    u8 unk1C[0x80];
    u8 flags;
    u8 unk9D[3];
    s32 unkA0;
};

/* A battle unit's panel: three sprites, two numbers and a text window, which
 * move together. */
enum UnitPanelFlag {
    UNIT_PANEL_USED             = 0x1,
    UNIT_PANEL_MOVING           = 0x2, /* by velocity a frame after moveDelay frames, for moveFrames */
    UNIT_PANEL_CLOSE_AFTER_MOVE = 0x4,
    UNIT_PANEL_TEXT_AFTER_MOVE  = 0x8, /* the text window not drawn until the move ends */
    UNIT_PANEL_SKIP_DRAW        = 0x10, /* not drawn this frame */
    UNIT_PANEL_MARK_CHANGED     = 0x20, /* marks the unit changed */
    UNIT_PANEL_TIMER            = 0x40, /* timer counting down */
    UNIT_PANEL_ONE_NUMBER       = 0x80 /* numbers[1] not set up */
};

#define UNIT_COUNT 12
#define UNIT_PANEL_COUNT 8

struct UnitPanel {
    /* 0x000 */ u8 flags; /* enum UnitPanelFlag */
    /* 0x001 */ s8 unit;
    /* 0x002 */ u16 timer;
    /* 0x004 */ u8 unk4;
    /* 0x005 */ u8 sprites[3]; /* handles; the second 0xFF for none */
    /* 0x008 */ s32 unk8;      /* handed to func_0209d900 or func_0209d954 when it closes */
    /* 0x00C */ u8 unkC[0x50];
    /* 0x05C */ struct TextWindow text;
    /* 0x084 */ struct NumberSprite numbers[2]; /* the second only for the units up to 5 */
    /* 0x1CC */ u16 moveFrames;
    /* 0x1CE */ u16 moveDelay;
    /* 0x1D0 */ struct FixedPos pos; /* also the first sprite's */
    /* 0x1D8 */ struct FixedPos unk1D8;
    /* 0x1E0 */ struct FixedPos numberPos0;
    /* 0x1E8 */ struct FixedPos unk1E8;
    /* 0x1F0 */ struct FixedPos numberPos1;
    /* 0x1F8 */ struct FixedPos spritePos1;
    /* 0x200 */ struct FixedPos spritePos2;
    /* 0x208 */ struct FixedPos textPos;
    /* 0x210 */ struct FixedPos unk210;
    /* 0x218 */ struct FixedPos velocity;
};

/* An equipment item's record of /dat/eq/, as func_020a142c loads it (ids 0x32
 * to 0x1AC): the fields read here are what it adds to the stats of whoever
 * equips it, the set* ones only as part of a full set (func_0207f6c0). The
 * stats are in the order of a /dat/en/ record's (attack at 0x0A), the others
 * in the order of enum AbilityEffect's. */
struct ItemData {
    /* 0x00 */ u8 unk0[2];
    /* 0x02 */ u8 minLevel; /* the level a Digimon needs to equip it */
    /* 0x03 */ u8 unk3;     /* 10, or the unk1A of the Digimon that can equip it */
    /* 0x04 */ u8 unk4[0x12];
    /* 0x16 */ s16 attack;
    /* 0x18 */ s16 defense;
    /* 0x1A */ s16 spirit;
    /* 0x1C */ s16 speed;
    /* 0x1E */ u8 unk1E[4];
    /* 0x22 */ s16 skillResists[8]; /* probably: 8 like ABILITY_RESIST_DARK to _ALL_SKILLS */
    /* 0x32 */ s16 statusResists[5]; /* from ABILITY_RESIST_POISON on */
    /* 0x3C */ s16 hitRate;
    /* 0x3E */ s16 dodgeRate;    /* strongly inferred: between hitRate and fleeRate, as the abilities */
    /* 0x40 */ s16 criticalRate; /* strongly inferred, as dodgeRate */
    /* 0x42 */ s16 fleeRate;
    /* 0x44 */ s16 skillDamage;
    /* 0x46 */ s16 bits;
    /* 0x48 */ s16 exp;
    /* 0x4A */ s16 setAttack;
    /* 0x4C */ s16 setDefense;
    /* 0x4E */ s16 setSpirit;
    /* 0x50 */ s16 setSpeed;
};

#define ITEM_CACHE_COUNT 27

/* An entry of the cache of equipment records, NO_ITEM for free. */
struct ItemCacheEntry {
    u16 id;
    struct ItemData data;
};

/* A rectangle of the touch screen, edges included. */
struct TouchRect {
    u16 left;
    u16 top;
    u16 right;
    u16 bottom;
};

/* How much a stat grows a level: (base + a random number below random) / 10. */
struct StatGrowth {
    u8 random;
    u8 base;
};

/* An item id that is no item: an empty equipment slot, a free cache entry. */
#define NO_ITEM 0xFFFF

/* A copy to VRAM queued for the next VBlank (runVramTransfers), in units of
 * unitBits bits. The queue's entries fill VRAM_TRANSFERS from the start and the
 * data they copy fills it from the end, data_021d8c90. */
struct VramTransfer {
    /* 0x0 */ s32 src;
    /* 0x4 */ s32 dst;
    /* 0x8 */ u16 size;
    /* 0xA */ u16 unitBits;
};

#define BG_LAYER_COUNT 4

/* A BG layer's scroll, written to its BGxHOFS and BGxVOFS at VBlank
 * (applyBgOffsets). */
struct BgOffset {
    s16 x;
    s16 y;
};

#define BG_OFFSET_MASK 0x1FF

/* A stack of marks in a screen's VRAM: base is where it starts, and marks the
 * places it was taken up to, the top one last. func_02085520 and the like pop
 * it back to a mark. Each screen has a set of five whose bases its callers
 * give (the BG character loaders take from them, allocMainVram for the main
 * screen) and a set of five that start at VRAM_STACK_TOP. */
struct VramStack {
    /* 0x00 */ s16 count;
    /* 0x02 */ s16 base;
    /* 0x04 */ s16 marks[63];
};

#define VRAM_STACK_COUNT 5
#define VRAM_STACK_TOP 0x3FF /* the last tile */

/* A screen's palettes as the game keeps them, a buffer of each kind per screen:
 * the colors the screen shows, the colors a fade goes to and the colors as
 * loaded. Colors 0 to 0xFF are the BG palettes, then the BG extended ones from
 * PALETTE_BG_EXT, the OBJ palettes from PALETTE_OBJ and the OBJ extended ones
 * from PALETTE_OBJ_EXT. */
#define PALETTE_BG 0
#define PALETTE_BG_EXT 0x100
#define PALETTE_OBJ 0x900
#define PALETTE_OBJ_EXT 0xA00
#define PALETTE_COLOR_COUNT 0x1200

/* A screen's three palette buffers and the flags that say which part of them
 * the VBlank upload uploadPalettes sends. The game keeps them as separate
 * symbols, one after the other. */
struct PaletteSet {
    /* 0x0000 */ u16 colors[PALETTE_COLOR_COUNT];
    /* 0x2400 */ u16 target[PALETTE_COLOR_COUNT];
    /* 0x4800 */ u16 base[PALETTE_COLOR_COUNT];
    /* 0x6C00 */ u16 dirty; /* PALETTE_DIRTY_... */
};

#define PALETTE_DIRTY_STANDARD 0x1 /* the BG and OBJ palettes changed */
#define PALETTE_DIRTY_EXTENDED 0x2 /* the extended palettes changed */
#define PALETTE_LOCKED 0x4 /* nothing is uploaded */

/* Flags on the color index of a palette load (loadPalette). Without
 * PALETTE_LOAD_KEEP_COLOR0 the first color of the 16 the index is in is
 * cleared; with PALETTE_LOAD_QUIET the palettes are not marked changed. */
#define PALETTE_LOAD_INDEX 0x3FFF
#define PALETTE_LOAD_KEEP_COLOR0 0x4000
#define PALETTE_LOAD_QUIET 0x8000

/* A palette effect: a fade or a blink of some of a screen's colors, which the
 * task runPaletteEffects steps every interval frames. The effects of kinds 2 to 5
 * and 8 to 11 are not understood yet. */
struct PaletteEffect {
    /* 0x00 */ u8 kind;     /* enum PaletteEffectKind, PALETTE_EFFECT_PAUSED on top */
    /* 0x01 */ s8 interval; /* frames between steps */
    /* 0x02 */ s8 wait;
    /* 0x04 */ s32 times; /* for the effects that end after a number of times */
    /* 0x08 */ s16 start; /* the first color */
    /* 0x0A */ s16 count;
    /* 0x0C */ u16 *colors; /* where the colors go, a fade's target */
    /* 0x10 */ s16 stepR;   /* how much each component moves a step; kinds 8 to 11 */
    /* 0x12 */ s16 stepG;   /* count steps in stepG up to stepB */
    /* 0x14 */ s16 stepB;
};

#define PALETTE_EFFECT_COUNT 16
#define PALETTE_EFFECT_PAUSED 0x80
#define PALETTE_FOREVER 10000 /* the times of an effect that does not end */

/* The kinds of palette effect, as stepPaletteEffects steps them. Kinds 2 and 3 step
 * with func_02083cd0, 4 and 5 with func_02083c0c, the first of each pair a
 * number of times and the second forever; 8 and 10 take turns, 9 goes to 11
 * and 11 back to 9. */
enum PaletteEffectKind {
    PALETTE_EFFECT_NONE,
    PALETTE_FADE,
    PALETTE_EFFECT_2,
    PALETTE_EFFECT_3,
    PALETTE_EFFECT_4,
    PALETTE_EFFECT_5,
    PALETTE_EFFECT_8 = 8,
    PALETTE_EFFECT_9,
    PALETTE_EFFECT_10,
    PALETTE_EFFECT_11,
    PALETTE_BLINK,         /* to a color and back, a number of times */
    PALETTE_BLINK_FOREVER, /* to a color and back */
};

/* The link partner's party in a link battle: the ids of its first five slots
 * and the Digimon of them, at most three. */
#define LINK_PARTY_SLOT_COUNT 5
#define LINK_PARTY_DIGIMON_COUNT 3

/* The item a link partner's Digimon equips in one of its slots: a table per
 * slot. */
struct LinkPartyItem {
    /* 0x0 */ s32 id; /* 0 for a free entry */
    /* 0x4 */ u16 item;
};

/* An equipment item in stock, and who equips it: the stock has 50 slots for
 * each kind of equipment. */
#define EQUIP_STOCK_SIZE 50

struct EquipSlot {
    /* 0x0 */ s32 id; /* the piece's own (takeNextId), 0 or -1 for an empty slot */
    /* 0x4 */ u16 item;
    /* 0x8 */ s32 owner;
};

/* An item with an id below the weapons' in stock, with how many there are
 * (up to 99): one slot for each such item. */
struct ItemSlot {
    /* 0x0 */ s32 id;   /* the slot's own (takeNextId) */
    /* 0x4 */ u16 item; /* 0xFFFF for an empty slot */
    /* 0x6 */ s16 count;
};

/* The item ids come in ranges of one kind each, as long as item_wep_hlp.sdb
 * (137 texts), item_arm_hlp.sdb (168), item_acc_hlp.sdb (74) and
 * item_dij_hlp.sdb (70) are; func_020a1318 tells them apart. */
enum ItemId {
    ITEM_ID_WEAPONS     = 0x32,
    ITEM_ID_ARMOR       = 0xBB,
    ITEM_ID_ACCESSORIES = 0x163,
    ITEM_ID_KEY_ITEMS   = 0x1AD, /* probably: dij is daiji, "important" */
    ITEM_ID_END         = 0x1F3
};

/* The Wi-Fi block of the save at data_021db618: strongly inferred to be
 * NitroDWC's DWCUserData (0x40 bytes) and a roster of 16 friends' DWCFriendData
 * (12 bytes each), which func_020ff144 checks and func_020fef34 turns into a
 * 64-bit friend key. */
#define WIFI_FRIEND_COUNT 16
struct WifiData {
    u8 userData[0x40];
    u8 friends[WIFI_FRIEND_COUNT][12];
};

/* A rectangle on the screen, in pixels. */
struct Rect {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
};

/* One of the 32 touch buttons of BUTTONS, shared by the groups. Its
 * flags say where its rectangle comes from: 0x1 given, 0x2 the bounds of
 * sprite's cell, 0x10 those of the object getSubActor or getMainActor
 * returns for sprite. 0x20 switches it off, and with 0x8 touching it doesn't
 * make it the group's cursor. */
struct Button {
    u16 flags; /* 0 for a free button */
    u16 sprite;
    struct Rect rect;
};

/* The task startFarmTask starts, run by tickFarmTask. */
struct FarmTask {
    struct Task task;
    s16 state;
    s16 unk1E;
    s16 slot; /* the slot of the first group in FARM_ORDER's order */
    u16 unk22;
    u16 unk24;
    u8 unk26[2];
    s16 unk28;
    s16 unk2A;
    u8 unk2C[4];
    s16 iconX; /* where func_ov005_0228f954 puts the icon */
    s16 iconY;
    s16 picked; /* a slot of FARM_DIGIMON_ACTORS, -1 for none */
    u16 icon;   /* the sprite of an item's icon, 0xFFFF for none */
    u16 unk38;
    u16 unk3A;
    u16 marks[8]; /* sprites over the group's digimon, 0xFFFF for none */
    u8 unk4C[4];
    s8 gfxSlot;
    u8 unk51;
    s8 unk52;
    s8 unk53;
};

/* The task func_020b4f50 starts, run by func_ov005_02292f48. */
struct Task02292f48 {
    struct Task task;
    s32 state;
    s16 wait; /* frames left to wait before the state runs */
    s16 unk22;
    u8 unk24[6];
    s16 unk2A;
    s16 unk2C;
    u8 unk2E[2];
    u16 bg;  /* func_02085f34's, freed with func_0208577c */
    u16 unk32;
};

/* The task func_020b48b4 starts, run by func_020b3614. Its result is left in
 * data_021e5ca4, -1 until then. */
struct Task020b3614 {
    struct Task task;
    s16 state;
    s16 wait; /* frames left to wait before the state runs */
    s16 slot; /* findFarmSlot's slot of the group */
    u8 unk22[0x2E];
    s16 unk50;
    u8 unk52[6];
    s16 unk58;
    s16 unk5A;
    s16 unk5C;
    s16 unk5E;
};

/* A buffer that data handed to copyReceivedData is copied into, and whether
 * some arrived since it was last checked. */
struct RecvBuffer {
    void *dest;
    u32 size;
    u16 received;
};

/* NitroSDK's NNSG2dCellOAMAttrData: the attributes of one OAM entry. */
struct CellOamAttr {
    u16 attr0;
    u16 attr1;
    u16 attr2;
};

/* NitroSDK's NNSG2dCellData: the OAM entries that make up a cell. */
struct CellData {
    u16 numOAMAttrs;
    u16 cellAttr;
    struct CellOamAttr *oamAttrs;
};

/* What a sprite's cellAnim points to, as far as the code reads it: the cell
 * shown, after func_020ba338 picks the frame (readMovieFile's code). */
struct CellAnimation {
    u8 unk0[0x2C];
    struct CellData *cell;
};

/* A sprite of one of the screens (the layout of setSubSpritePos's module). */
struct Sprite {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ s16 x; /* the whole part of a 16.16 position, which func_0203f840 adds to as a word */
    /* 0x04 */ u16 unk4;
    /* 0x06 */ s16 y;
    /* 0x08 */ u8 unk8[0x10];
    /* 0x18 */ u16 kind;
    /* 0x1A */ u16 flags; /* SPRITE_* */
    /* 0x1C */ u8 unk1C; /* the BG priority, OAM attribute 2's */
    /* 0x1D */ u8 unk1D;       /* passed with the OAM entry to addSubOamEntry */
    /* 0x1E */ s16 charsId;   /* the id of its struct SpriteChars */
    /* 0x20 */ u8 unk20[4];
    /* 0x24 */ u16 charSlot;  /* where its characters are in the screen's sprite VRAM */
    /* 0x26 */ u16 charIndex; /* which of the SpriteChars' sets it shows */
    /* 0x28 */ u8 palette; /* the OAM palette; func_020a0a00 makes the sprite again with it */
    /* 0x29 */ u8 unk29;
    /* 0x2A */ u16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u16 unk2E;
    /* 0x30 */ u8 anim;
    /* 0x31 */ u8 unk31;
    /* 0x32 */ s16 animLoops; /* -1 for ever */
    /* 0x34 */ s16 animLoopsDone;
    /* 0x36 */ u16 unk36;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ void *unk40;
    /* 0x44 */ u8 unk44[4];
    /* 0x48 */ struct CellAnimation *cellAnim;
    /* 0x4C */ void *unk4C;
    /* 0x50 */ u8 unk50[4];
};

/* Each screen has this many sprites. */
#define SPRITE_COUNT 131

/* struct Sprite's flags. */
#define SPRITE_IN_USE 0x1
#define SPRITE_HIDDEN 0x10 /* not drawn */

/* The number of species. */
#define SPECIES_COUNT 426

/* An enemy's record of /dat/en/ (54 files of eight records each), as
 * func_020a14e8 loads it by id. The stats are where struct SpeciesData has
 * them in /dat/dm/ (the values are close). */
struct EnemyData {
    /* 0x00 */ u8 unk00[3];
    /* 0x03 */ u8 unk03; /* the icon the battle's panels show */
    /* 0x04 */ u8 unk04[6];
    /* 0x0A */ s16 attack;
    /* 0x0C */ s16 defense;
    /* 0x0E */ s16 spirit;
    /* 0x10 */ s16 speed;
    /* 0x12 */ u8 unk12[0x12];
    /* 0x24 */ s16 abilities[4]; /* ids of struct Ability, -1 for none (copyAbilities) */
    /* 0x2C */ u16 skills[5]; /* ids of data_02113698; the fifth, 0xFFFF for none, for recovery */
    /* 0x36 */ u8 unk36[0x2E];
    /* 0x64 */ s16 bits; /* given when it is beaten */
    /* 0x66 */ s16 exp;
    /* 0x68 */ s16 unk68;
};

/* SkillData.kind, from the help texts of the skills of each kind */
enum SkillKind {
    SKILL_ATTACK,
    SKILL_SUPPORT, /* raises allies' stats or lowers enemies' */
    SKILL_RECOVERY,
};

/* The skills of data_02113698 (skill_help.sdb has as many texts). */
#define SKILL_COUNT 435

/* A skill, one of the SKILL_COUNT of data_02113698, which func_020a1268
 * returns. */
struct SkillData {
    /* 0x00 */ u16 id;
    /* 0x02 */ u8 unk02[3];
    /* 0x05 */ u8 kind; /* enum SkillKind */
    /* 0x06 */ u8 unk06[0xA];
    /* 0x10 */ union {
        u32 flags;   /* bit 31: a fixed range */
        u8 bytes[4]; /* bytes[3] & 0x1F: the zones it reaches, 0x10 the first */
    } range;
    /* 0x14 */ u8 unk14[4];
};

/* A species' record, one of 426: loadSpeciesData loads it from dat/dm, 8 to a
 * file, and func_020a29c4 builds a new Digimon's record from it. The layout
 * matches the community's map of dat/dm; the names are the fields the
 * Digimon's record takes them into. */
struct SpeciesData {
    /* 0x00 */ u16 id;
    /* 0x02 */ s8 level;
    /* 0x03 */ u8 unk3; /* func_020a3098's; a Digimon's unk1A */
    /* 0x04 */ s32 hp;
    /* 0x08 */ s16 mp;
    /* 0x0A */ s16 attack;
    /* 0x0C */ s16 defense;
    /* 0x0E */ s16 spirit;
    /* 0x10 */ s16 speed;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s8 aptitude; /* the level a Digimon of it can reach, its maxLevel */
    /* 0x15 */ u8 unk15;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 resistances[7]; /* to fire, thunder, wind, water, steel, holy
                                    * and dark; 500 in most records */
    /* 0x26 */ u8 unk26; /* func_020a2f3c makes a Digimon's unk1D of it */
    /* 0x27 */ u8 ability; /* an id of data_0210c11c, the abilities (abi_help.sdb
                            * has as many texts), a Digimon's first unk22 */
    /* 0x28 */ u8 unk28;   /* another ability, offered after the Digimon's own */
    /* 0x29 */ u8 expCurve;
    /* 0x2A */ u8 growth;
    /* 0x2B */ u8 unk2B;
    /* 0x2C */ u16 skills[4]; /* ids of data_02113698, the skills (as many as
                               * their names), a Digimon's first unk54 */
    /* 0x34 */ u8 unk34; /* func_ov006_02287af4 shows the Digimon's unk54[0] from
                          * this level on */
    /* 0x35 */ u8 unk35[6];
    /* 0x3B */ u8 listed; /* 0 for a species that counts as another (func_020a3224
                           * and func_020a31e8 give which) and that ov006's lists
                           * leave out */
};

/* The last 80 positions and animations of the party's leader, newest first:
 * the followers walk spacing[0], [1] and [2] steps behind it. */
struct FollowTrail {
    /* 0x000 */ s32 x[80];
    /* 0x140 */ s32 y[80];
    /* 0x280 */ s16 animation[80];
    /* 0x320 */ u16 spacing[3];
    /* 0x326 */ u16 targetSpacing; /* the spacing grows towards it: 20 at the leader's speed 1, 10 at 2 */
    /* 0x328 */ s32 steps;
};

/* The walk of an actor to a point, set up by func_020c4668. */
struct ActorWalk {
    /* 0x00 */ struct Actor *actor;
    /* 0x04 */ struct FollowTrail *trail;
    /* 0x08 */ s16 startX;
    /* 0x0A */ s16 startY;
    /* 0x0C */ s16 targetX;
    /* 0x0E */ s16 targetY;
    /* 0x10 */ s32 velX; /* in mode 1, a straight line to the target */
    /* 0x14 */ s32 velY;
    /* 0x18 */ s16 stepX; /* -1, 0 or 1 */
    /* 0x1A */ s16 stepY;
    /* 0x1C */ s32 prevState; /* the state to go back to, or -1 */
    /* 0x20 */ u8 mode; /* 0 along the axes, 1 in a straight line */
    /* 0x21 */ s8 speed; /* in pixels a frame, -1 to be there at once */
};

/* The route an actor plays, one of the 8 routes of ACTOR_ROUTES (state 6). */
struct ActorRoute {
    /* 0x00 */ struct Actor *actor;
    /* 0x04 */ struct ActorWalk walk;
    /* 0x28 */ s16 loops; /* -1 for ever */
    /* 0x2A */ s16 loopsDone;
    /* 0x2C */ s16 pc;     /* the code played */
    /* 0x2E */ s16 length; /* where the next code is written */
    /* 0x30 */ s16 wait;   /* frames waited by a ROUTE_WAIT */
    /* 0x32 */ u8 route;
};

/* The work of a leader (ACTOR_STATE_LEAD) or a follower (ACTOR_STATE_FOLLOW). */
struct ActorFollow {
    /* 0x00 */ struct Actor *actor;
    /* 0x04 */ struct FollowTrail *trail;
};

/* The work of a wandering actor (ACTOR_STATE_WANDER): a step in a random
 * direction every 16 frames, within its rectangle. */
struct ActorWander {
    /* 0x00 */ struct Actor *actor;
    /* 0x04 */ s32 timer;
    /* 0x08 */ s16 left;
    /* 0x0A */ s16 top;
    /* 0x0C */ s16 right;
    /* 0x0E */ s16 bottom;
    /* 0x10 */ s16 paused;
};

/* The work of an actor's state: what the state's handler of ACTOR_STATE_HANDLERS
 * keeps. */
union ActorWork {
    struct ActorFollow follow;
    struct ActorWander wander;
    struct ActorWalk walk;   /* ACTOR_STATE_WALK */
    struct ActorRoute route; /* ACTOR_STATE_ROUTE */
    u8 raw[0x40];
};

/* The second sprite of an actor, drawn at its position unless its kind is
 * 0xFFFF: the character 0x26F plus a number of the actor's animation file. */
struct ActorExtra {
    /* 0x00 */ union Fixed16 x;
    /* 0x04 */ union Fixed16 y;
    /* 0x08 */ u8 unk8[0x12];
    /* 0x1A */ u16 kind;
    /* 0x1C */ s16 cell;
    /* 0x1E */ s16 drawnCell;
    /* 0x20 */ s16 frameTime;
    /* 0x22 */ s16 animation;
    /* 0x24 */ u32 shapeSize;
    /* 0x28 */ u16 priority;
    /* 0x2A */ u16 unk2A;
    /* 0x2C */ u16 vramBlock;
    /* 0x2E */ u16 unk2E;
    /* 0x30 */ u16 palette;
    /* 0x32 */ u16 unk32;
    /* 0x34 */ void *graphics;
    /* 0x38 */ struct MapAnimFile *animFile;
    /* 0x3C */ struct MapAnimFrame *animFrame;
    /* 0x40 */ void *unk40;
    /* 0x44 */ u8 unk44[4];
};

/* One of the 48 actors of each screen, the characters walking on the field:
 * MAIN_ACTORS on the main screen and SUB_ACTORS on the sub screen.
 * getMainActor and getSubActor return one by index, func_020c7520 and
 * func_020c79fc make one, and the screen's task (func_020c5a8c, func_020c5534)
 * runs its state's handler and draws it. kind is the index of its map
 * character, data_02107f34, which func_020a3224 gives for a species. */
struct Actor {
    /* 0x00 */ union {
        s32 xFixed; /* 16.16 */
        struct {
            u16 xFrac;
            s16 x;
        };
    };
    /* 0x04 */ union {
        s32 yFixed;
        struct {
            u16 yFrac;
            s16 y;
        };
    };
    /* 0x08 */ union Fixed16 prevX;
    /* 0x0C */ union Fixed16 prevY;
    /* 0x10 */ s32 velX; /* 16.16, per frame */
    /* 0x14 */ s32 velY;
    /* 0x18 */ s16 unk18; /* where its rectangle was last put in the map's collision */
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 speed; /* in pixels a frame, of the leader moved by the pad */
    /* 0x1E */ u16 kind;
    /* 0x20 */ s32 index;
    /* 0x24 */ s32 flags; /* ACTOR_* */
    /* 0x28 */ s8 unk28;
    /* 0x29 */ u8 unk29;
    /* 0x2A */ s16 halfWidth; /* of the frame showing */
    /* 0x2C */ s16 halfHeight;
    /* 0x2E */ s16 unk2E; /* half the size of the first frame */
    /* 0x30 */ s16 unk30;
    /* 0x32 */ u8 unk32[2];
    /* 0x34 */ s32 updates[16]; /* per-frame functions, run by func_02045304 */
    /* 0x74 */ s16 cell;      /* of the frame showing */
    /* 0x76 */ s16 drawnCell; /* the cell in VRAM */
    /* 0x78 */ s16 frameTime; /* frames since the animation started */
    /* 0x7A */ s16 animation; /* ACTOR_ANIM_* */
    /* 0x7C */ u32 shapeSize; /* the OAM shape (attribute 0) and size (attribute 1 << 16) */
    /* 0x80 */ u16 unk80;     /* the OAM priority, 0-3 */
    /* 0x82 */ u16 unk82;
    /* 0x84 */ u16 vramBlock; /* where its graphics are in the sprite VRAM */
    /* 0x86 */ u16 unk86;
    /* 0x88 */ u16 palette; /* the palette slot of its colors */
    /* 0x8A */ u16 unk8A;
    /* 0x8C */ void *graphics; /* the character's graphics file, /dat/mchr/%xc */
    /* 0x90 */ struct MapAnimFile *animFile;
    /* 0x94 */ struct MapAnimFrame *animFrame; /* the frame showing */
    /* 0x98 */ void *unk98;
    /* 0x9C */ u8 direction; /* DIR_* of its velocity */
    /* 0x9D */ u8 unk9D[3];
    /* 0xA0 */ struct ActorExtra extra;
    /* 0xE8 */ s32 state; /* ACTOR_STATE_* */
    /* 0xEC */ union ActorWork work;
};

/* A move along a curve through three points in initCurve's frames: the
 * velocity grows by accel every frame, and the position is start plus
 * velocity times the frame, in 20.12 fixed point. */
struct Curve {
    /* 0x00 */ s16 frame;
    /* 0x02 */ s16 frames;
    /* 0x04 */ s32 startX;
    /* 0x08 */ s32 startY;
    /* 0x0C */ s32 velX;
    /* 0x10 */ s32 velY;
    /* 0x14 */ s32 accelX;
    /* 0x18 */ s32 accelY;
    /* 0x1C */ s16 x;
    /* 0x1E */ s16 y;
    /* 0x20 */ s16 endX;
    /* 0x22 */ s16 endY;
};
/* The message window tasks that func_020a74ec (id data_021e33d8) and
 * func_020a74a0 (id data_021e33dc) start. */
struct MessageWindowTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s32 wait;
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 window; /* closeWindow's */
    /* 0x26 */ u16 unk26;
    /* 0x28 */ u8 unk28[6];
    /* 0x2E */ u16 unk2E;
    /* 0x30 */ u8 unk30[4];
    /* 0x34 */ u16 sprite; /* 0xFFFF none */
};

/* An operand in these ranges names a variable instead of giving a value: the
 * thread's own vars, or the globals of SCRIPT_GLOBALS (see resolveOperand). */
#define SCRIPT_LOCAL_VAR_FIRST (-32767)
#define SCRIPT_LOCAL_VAR_LAST (-32760)
#define SCRIPT_GLOBAL_VAR_FIRST (-32759)
#define SCRIPT_GLOBAL_VAR_LAST (-32695) /* one past the globals, see resolveOperand */

#define SCRIPT_THREAD_COUNT 45
#define SCRIPT_GLOBAL_COUNT 64

/* ScriptThread.flags */
enum ScriptThreadFlag {
    SCRIPT_THREAD_RUNNING          = 0x1,
    SCRIPT_THREAD_ASLEEP           = 0x4,
    SCRIPT_THREAD_MOVING_SPRITES   = 0x8,  /* the curve moves the sprites */
    SCRIPT_THREAD_KEEP_MAIN_SPRITE = 0x20, /* not freed with the thread */
    SCRIPT_THREAD_KEEP_SUB_SPRITE  = 0x40,
};

/* One of the 45 script threads of SCRIPT_THREADS. Every frame the interpreter
 * task (tickScripts) calls the commands of each awake thread, one after
 * another, until one returns 0. The interpreter steps pc past the opcode
 * before it calls the command, so a command finds its operands at pc. */
struct ScriptThread {
    /* 0x00 */ u16 flags;       /* SCRIPT_THREAD_* */
    /* 0x02 */ u16 index;       /* in SCRIPT_THREADS */
    /* 0x04 */ u8 parent;       /* the thread that started this one, 0xFF none */
    /* 0x05 */ u8 children[16]; /* 0xFF where none */
    /* 0x18 */ u16 *pc;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 sleepFrames;  /* while asleep: -1 until woken */
    /* 0x20 */ u16 mainSprite;   /* 0xFFFF none */
    /* 0x22 */ u16 subSprite;    /* 0xFFFF none */
    /* 0x24 */ struct Curve curve; /* moves the sprites; frame -1 when done */
    /* 0x48 */ u8 unk48[4];
    /* 0x4C */ u16 *returnStack[4]; /* where each call returns to, the latest first */
    /* 0x5C */ s16 vars[8];
    /* 0x6C */ u16 localFlags[2]; /* the thread's own flags, see cmdSetLocalFlag */
    /* 0x70 */ u16 unk70[4];       /* 0xFFFF none */
    /* 0x78 */ s8 paletteRow[4];   /* the 16-color palettes of each of four slots */
    /* 0x7C */ s8 paletteRowCount[4];
};

/* One of the 10 menus of MENU_LAYOUTS, in 8-pixel tiles. The choices are
 * two tiles apart, so height is twice count and one tile above and below. */
struct MenuLayout {
    /* 0x0 */ u8 x;
    /* 0x1 */ u8 y;
    /* 0x2 */ u8 width;
    /* 0x3 */ u8 height;
    /* 0x4 */ u8 unk4; /* the menu's unk5A */
    /* 0x5 */ u8 unk5; /* the menu's unk5B */
    /* 0x6 */ u8 count;
    /* 0x7 */ u8 text; /* getFarmText's index */
};

/* A range of a movie's frames to play, and how many times (-1 for ever). */
struct MovieRange {
    /* 0x00 */ u16 first;
    /* 0x02 */ u16 last;
    /* 0x04 */ s16 loops;
};

/* The files of a movie's frame; the first frame's also name the others the
 * movie needs. */
struct MovieFrame {
    char *image;
    char *unk4;
    char *unk8;
};

/* The task that plays a movie: one image a frame, read from its own file. */
struct MovieTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ u16 state;
    /* 0x1E */ u16 movie;
    /* 0x20 */ u16 firstFrame;
    /* 0x22 */ u16 lastFrame;
    /* 0x24 */ u16 frame;
    /* 0x26 */ u16 frameCount;
    /* 0x28 */ s16 loops;
    /* 0x2A */ s16 loopsDone;
    /* 0x2C */ struct MovieFrame *frames;
    /* 0x30 */ void *unk30;
    /* 0x34 */ void *frameDest; /* where the next frame is read */
    /* 0x38 */ void *frameBuffer;
    /* 0x3C */ struct MovieRange next;     /* played from the next frame */
    /* 0x42 */ struct MovieRange afterLoop; /* played once the range played ends */
    /* 0x48 */ struct MovieRange afterEnd;  /* played once its last loop ends */
    /* 0x4E */ u16 nextMovie;
    /* 0x50 */ u16 unk50;
    /* 0x52 */ u16 unk52;
    /* 0x54 */ s16 nextMovieLoops;
    /* 0x56 */ u8 stop;
    /* 0x57 */ u8 hasNext;
    /* 0x58 */ u8 hasAfterLoop;
    /* 0x59 */ u8 hasAfterEnd;
    /* 0x5A */ u8 hasNextMovie;
    /* 0x5B */ u8 frameShown; /* the frame read has been shown */
};

/* The scroll of the battle map, in pixels: [0] is BG3, the map, and [1] BG2,
 * which follows the map in proportion to its own size. */
struct MapScroll {
    union Fixed16 x[2];
    union Fixed16 y[2];
    u16 width[2]; /* in tiles */
    u16 height[2];
    s32 taskId; /* of the task that scrolls it */
};

/* A map character of the field: the numbers of its files in /dat/mchr/, each
 * loaded once for all its users and counted by them. */
struct MapCharacter {
    u16 graphics; /* %xc */
    u16 anim;     /* %xa */
    u16 palette;  /* %xp */
    u16 unk6;     /* %xh, 0xFFFF for none */
};

/* The state of a screen's field map: where it is scrolled to, where it is
 * scrolling and its task. MAIN_MAP_STATE is the main screen's, SUB_MAP_STATE
 * the sub screen's; data_021e31f8 is a copy of the sub screen's that the game
 * restores. Sizes are in tiles of 8 pixels. */
struct MapState {
    /* 0x00 */ u16 id; /* the map's number, its files' in /dat/map/ */
    /* 0x02 */ u8 unk2[2];
    /* 0x04 */ union Fixed16 x;
    /* 0x08 */ union Fixed16 y;
    /* 0x0C */ u16 width;
    /* 0x0E */ u16 height;
    /* 0x10 */ union Fixed16 targetX; /* where the scroll stops */
    /* 0x14 */ union Fixed16 targetY;
    /* 0x18 */ union Fixed16 layerX[3]; /* the map's three background layers */
    /* 0x24 */ union Fixed16 layerY[3];
    /* 0x30 */ u16 layerWidth[3];
    /* 0x36 */ u16 layerHeight[3];
    /* 0x3C */ s32 distanceX; /* left to scroll, 0 once it stops */
    /* 0x40 */ s32 distanceY;
    /* 0x44 */ s32 stepX; /* scrolled each frame */
    /* 0x48 */ s32 stepY;
    /* 0x4C */ s16 directionX; /* -1 to scroll right, 1 to scroll left */
    /* 0x4E */ s16 directionY;
    /* 0x50 */ s16 unk50[16];
    /* 0x70 */ u8 unk70[8];
    /* 0x78 */ u16 color; /* a BGR555 colour, given to loadSubPalette */
    /* 0x7A */ u8 unk7A[2];
    /* 0x7C */ s32 taskId;
};

/* The state of the touch screen, updated once a frame like a pad with a single
 * button, touching, and the point touched. */
struct Touch {
    /* 0x00 */ u16 held;
    /* 0x02 */ u16 pressed;
    /* 0x04 */ u16 released;
    /* 0x06 */ u16 fastRepeat;
    /* 0x08 */ u16 longHeld;
    /* 0x0A */ u16 repeat;
    /* 0x0C */ u16 doubleTap; /* touched twice within 20 frames and 8 pixels, for one frame */
    /* 0x0E */ u16 tap;       /* touched and let go within 20 frames and 8 pixels, for one frame */
    /* 0x10 */ u16 flick;     /* let go after moving more than 10 pixels in the last frame */
    /* 0x12 */ u16 prevHeld;
    /* 0x14 */ u16 x;
    /* 0x16 */ u16 y;
    /* 0x18 */ s16 offsetX; /* x + xOffset */
    /* 0x1A */ s16 offsetY; /* y + yOffset */
    /* 0x1C */ u16 flickSpeed; /* the pixels moved in the last frame, set when let go */
    /* 0x1E */ u16 flickAngle; /* the direction of that move, in degrees */
    /* 0x20 */ u16 prevX;
    /* 0x22 */ u16 prevY;
    /* 0x24 */ s16 xOffset;
    /* 0x26 */ s16 yOffset;
    /* 0x28 */ s32 holdFrames;
    /* 0x2C */ s32 longHoldFrames;
    /* 0x30 */ s32 repeatFrames;
    /* 0x34 */ s32 doubleTapFrames;
    /* 0x38 */ s32 doubleTapState; /* 0 waiting, 1 touched once, 2 touched twice */
    /* 0x3C */ u16 doubleTapX;
    /* 0x3E */ u16 doubleTapY;
    /* 0x40 */ s32 tapFrames;
    /* 0x44 */ s32 tapState; /* 0 waiting, 1 touched, 2 let go */
    /* 0x48 */ u16 tapX;
    /* 0x4A */ u16 tapY;
    /* 0x4C */ s16 tapOffsetX;
    /* 0x4E */ s16 tapOffsetY;
};

/* A task's slot of the pool. */
struct TaskSlot {
    struct Task task;
    u8 work[0x100 - sizeof(struct Task)];
};

/* What a kind of sprite is made of: the ids of its characters, its cells and
 * its palette. */
struct SpriteKind {
    s16 chars;
    s16 cells;
    s16 palette;
};

/* NitroSDK's NNSG2dCharacterData, as far as the code reads it. */
struct CharacterData {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ s32 format; /* GXTexFmt: 3 for 16 colors, 4 for 256 */
    /* 0x08 */ u8 unk8[8];
    /* 0x10 */ u32 size;
    /* 0x14 */ void *data;
};

/* Up to 8 sets of sprite characters read from files, shared by the sprites of
 * both screens, each loaded into each screen's sprite VRAM when used there. */
/* Each table of sprite resources (characters, cells, palettes) has this
 * many entries. */
#define SPRITE_RESOURCE_COUNT 64

/* A struct SpriteChars holds this many sets of characters. */
#define SPRITE_CHAR_SETS 8

struct SpriteChars {
    /* 0x00 */ s16 id;
    /* 0x04 */ void *files[SPRITE_CHAR_SETS];
    /* 0x24 */ struct CharacterData *data[SPRITE_CHAR_SETS];
    /* 0x44 */ u16 mainSlot[SPRITE_CHAR_SETS]; /* where in the main screen's sprite VRAM, 0xFFFF if not */
    /* 0x54 */ u16 subSlot[SPRITE_CHAR_SETS];
    /* 0x64 */ s8 mainUsers[SPRITE_CHAR_SETS];
    /* 0x6C */ s8 subUsers[SPRITE_CHAR_SETS];
    /* 0x74 */ u8 unk74[SPRITE_CHAR_SETS];
    /* 0x7C */ u8 mainDirty[SPRITE_CHAR_SETS]; /* to be copied to the slot */
    /* 0x84 */ u8 subDirty[SPRITE_CHAR_SETS];
};

/* A sprite kind's cells: unk4, unk8 and unk14 are blocks of the heap, which
 * releaseMainSpriteKind frees with unkC and unk10 once no sprite uses them. */
struct SpriteCells {
    /* 0x00 */ s16 id;
    /* 0x04 */ void *unk4;
    /* 0x08 */ void *unk8;
    /* 0x0C */ void *unkC;
    /* 0x10 */ void *unk10;
    /* 0x14 */ void *unk14;
    /* 0x18 */ s8 users;
};

/* A sprite kind's palette: its file and the NNSG2dPaletteData in it. */
struct SpritePalette {
    /* 0x00 */ s16 id;
    /* 0x04 */ void *file;
    /* 0x08 */ struct NNSG2dPaletteData *data;
    /* 0x0C */ s8 users;
};

/* The task of tickBgScreen, started by startBgScreenTask: it sets up two
 * backgrounds, fades them in, waits for func_02083738, fades out and tears
 * them down (closeBgScreen). */
struct BgScreenTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ struct BgGraphics *graphics; /* two, in one block of the heap */
    /* 0x20 */ u16 state;
    /* 0x24 */ void *arg; /* startBgScreenTask's */
    /* 0x28 */ s32 unk28; /* from func_02083e78, freed by stopSubPaletteEffectsButFades */
    /* 0x2C */ s32 unk2C; /* from func_02083ea8, freed by stopMainPaletteEffectsButFades */
};

/* A copy that queueVramTransfer adds to its queue of copies, in rows of unk10
 * units when flags bit 0 is set. Its callers copy into VRAM and OAM, so
 * presumably the queue runs at the V-blank. */
struct VramCopy {
    u16 flags;
    void *src;
    void *dest;
    s16 unkC;
    u16 unkE;
    u16 unk10;
    u16 unk12;
    u16 size;
};

/* Where a sprite of the given id goes from another, looked up by
 * getSpriteOffset. */
struct SpriteOffset {
    u16 id;
    s16 x;
    s16 y;
};

extern s32 data_0210b014[];
extern u8 data_0210bc6c[50][0x18];
extern s32 data_0210c6a4;
extern s32 data_02110974[];
extern s32 data_02119350[];
extern s32 data_0211cbd0[];
extern s32 FARM_TEXTS[];
extern s32 data_0212acc8;
extern s32 data_0212ad04;
extern s32 data_0212af20;
extern u16 DEBUG_PRINT_ATTR;
extern s16 DEBUG_PRINT_FIXED_ATTR;
extern u32 DEBUG_PRINT_BG;
extern char PATH_SOUND_DATA[]; /* "/dat/snd/sound_data.sdat" */
extern s32 (*data_0213e488)();
extern s32 data_0213e490;
extern s32 TOUCH_DISABLED;
extern struct Touch TOUCH;
extern u16 DEBUG_PRINT_SCREEN[24][32]; /* the debug console's text screen */
extern u16 TASK_COUNT;
extern struct Task *CURRENT_TASK;
extern struct TaskSlot TASK_SLOTS[80];
extern u16 GAME_PAD_IGNORED_KEYS;
extern s32 GAME_PAD_DISABLED;
extern struct Pad GAME_PAD;
extern struct Pad RAW_PAD;
extern s32 SOUND_HEAP;
extern s32 SOUND_ARCHIVE;
extern u8 SOUND_HEAP_MEMORY[];
extern s32 MAIN_FADE_FRAMES;
extern struct NNSiFndHeapHead *MAIN_HEAP;
extern s32 HEAP_INITIAL_FREE;
extern s32 HEAP_BLOCK_COUNT;
extern s32 FRAME_COUNT;
extern struct MovieTask *MOVIE_TASK;
extern void *MOVIE_BUFFER;
extern struct FSFile MOVIE_FILE; /* the movie's file */
extern struct Sprite SUB_SPRITES[SPRITE_COUNT];
extern struct Sprite MAIN_SPRITES[SPRITE_COUNT];
extern u8 TOUCH_SCROLL_ENABLED;
extern u16 SYSTEM_FLAGS[];
extern void *data_021ab7a8;
extern void *data_021ab7b0;
extern struct BgScreenTask *BG_SCREEN_TASK;
extern s32 BG_SCREEN_TASK_ID;
extern struct MapScroll BATTLE_MAP_SCROLL;
extern struct MapState MAIN_MAP_STATE; /* the main screen's */
extern struct MapState SUB_MAP_STATE; /* the sub screen's */
extern s8 MAIN_OAM_AFFINE_NEXT; /* the main screen's next affine parameters */
extern s8 SUB_OAM_AFFINE_NEXT; /* the sub screen's */
extern struct ConvertTask *CONVERT_TASK;
extern s32 MENU_DIGIVOLVE_TASK_ID; /* the task id of the scene from the Digimon menu */
extern s32 CONVERTED_DIGIMON; /* the id of the Digimon the conversion made */
extern s32 CONVERT_TASK_ID;
struct MenuDigivolveTask;
extern struct MenuDigivolveTask *MENU_DIGIVOLVE_TASK;
extern u8 SUB_BG_AFFINE_CHANGED[2]; /* the sub screen's BG2 and BG3 affine parameters changed */
extern u8 MAIN_BG_AFFINE_CHANGED[2]; /* the main screen's */
extern struct BgAffine MAIN_BG_AFFINE[2]; /* the main screen's BG2 and BG3 */
extern struct BgAffine SUB_BG_AFFINE[2]; /* the sub screen's */
struct FieldMenuTask;
extern struct FieldMenuTask *FIELD_MENU_TASK;
extern struct SpriteSlot SPRITE_SLOTS[SPRITE_SLOT_COUNT];
extern struct UnitStatus UNIT_STATUS[UNIT_COUNT];
extern struct UnitPanel UNIT_PANELS[UNIT_PANEL_COUNT];
extern s8 data_021bb7d4;
extern u8 data_021bb7d8;
extern s8 data_021bb7dc;
extern u16 data_021bb7e0[16];
extern u16 data_021bb800[2][19];
extern u16 data_021bb84c[2][23];
extern u8 data_021bb8a8;
extern u8 BATTLE_FLAGS;
extern s8 data_021bb8b4;
extern u8 data_021bb8b8;
extern s16 data_021bb8bc;
extern s32 data_021bb8c0[5];
extern s8 data_021bc1b0;
extern s32 LINK_PARTY_IDS[LINK_PARTY_SLOT_COUNT];
extern struct Digimon LINK_PARTY_DIGIMON[LINK_PARTY_DIGIMON_COUNT];
extern s8 NAME_ENTRY_MAX_LENGTH;
extern s8 NAME_ENTRY_MODE;
extern s8 data_021bc69c;
extern s8 data_021bc6a0;
extern s8 data_021bc6a4;
extern s8 data_021bc6a8;
extern s8 data_021bc6ac;
extern void *NAME_ENTRY_NAME;
extern s32 NAME_ENTRY_DIGIMON;
extern u8 DISPLAY_READY;
extern u8 MAIN_LAYERS_SHOWN;
extern u8 SUB_LAYERS_SHOWN;
extern u16 DISPLAY_FLAGS;
extern struct VramTransfer *VRAM_TRANSFER_END;
extern s32 SOUND_TASK_ID;
extern s32 *VRAM_TRANSFER_DATA;
extern s32 SUB_BG_PRIORITIES[BG_LAYER_COUNT];
extern s32 MAIN_BG_PRIORITIES[BG_LAYER_COUNT];
extern struct BgOffset MAIN_BG_OFFSETS[BG_LAYER_COUNT];
extern struct BgOffset SUB_BG_OFFSETS[BG_LAYER_COUNT];
extern struct PaletteEffect SUB_PALETTE_EFFECTS[PALETTE_EFFECT_COUNT];
extern struct PaletteEffect MAIN_PALETTE_EFFECTS[PALETTE_EFFECT_COUNT];
extern struct VramStack SUB_VRAM_TOP_STACKS[VRAM_STACK_COUNT];
extern struct VramStack MAIN_VRAM_TOP_STACKS[VRAM_STACK_COUNT];
extern struct VramStack SUB_VRAM_STACKS[VRAM_STACK_COUNT];
extern struct VramStack MAIN_VRAM_STACKS[VRAM_STACK_COUNT];
extern u16 SUB_PALETTE_COLORS[PALETTE_COLOR_COUNT];
extern u16 SUB_PALETTE_DIRTY;
extern u16 MAIN_PALETTE_COLORS[PALETTE_COLOR_COUNT];
extern u16 MAIN_PALETTE_DIRTY;
extern struct VramTransfer VRAM_TRANSFERS[];
extern s32 data_021d8c90;
extern s8 data_021d8c94;
extern s8 data_021d8c9c;
extern s8 data_021d8ca0;
extern s8 data_021d8ca4;
extern s8 data_021d8cb0;
extern s16 SCRIPT_SAVED_BGM;
extern s32 SCRIPT_TASK;
extern s32 data_021da400;
extern s32 data_021da408;
extern struct ExchangeData *data_021da40c;
extern s32 data_021da414;
extern s32 data_021da770;
extern s16 data_021da774;
extern s32 data_021db5f8;
extern s32 data_021db7f8;
extern s32 data_021db804[10];
extern s32 data_021de5f8;
extern s8 FARM_ORDER[];
extern struct Farm FARMS[4];
extern struct FarmGoods PLAYER_GOODS[50];
extern s32 data_021df5f8;
extern s32 data_021df9f8;
extern u16 GAME_FLAGS[];
extern struct LinkRecords data_021e0af8;
extern s32 data_021e0bf8;
extern s8 data_021e33b8;
extern s8 data_021e33bc;
extern s8 data_021e33c0;
extern s8 data_021e33c4;
extern s16 data_021e33c8;
extern u16 data_021e33cc;
extern s16 data_021e33d0;
extern s32 data_021e33d8;
extern s32 data_021e33e0;
extern u16 UI_FLAGS[];
extern u16 *data_021e33f8[16];
extern u16 *data_021e3438[16];
extern struct Window WINDOWS[8];
extern struct GfxSlot GFX_SLOTS[24];
extern u16 data_021e3ad8[0x800];
extern u16 data_021e4ad8[0x800];
extern s32 data_021e5ad8;
extern s32 data_021e5ae4;
extern s32 data_021e5ae8;
extern s32 DIGIMON_LIST_TASK_ID;
extern u8 data_021e5c70;
extern struct RecvBuffer RECEIVE_BUFFER;
extern u16 data_021e5c9c;
extern s16 data_021e5ca4;
extern s32 data_021e5cb4;
extern s32 data_021e5cb8;
extern s32 FARM_TASK_ID;
extern struct BgGraphics data_021e5cd8;
extern s32 LINK_OVER_WIFI;
extern s32 LINK_STATE;
extern void *LINK_WORK;
extern s32 data_021e5d00;
struct LinkTransfer;
extern struct LinkTransfer LINK_TRANSFER;
extern u16 data_021e9c98;
extern u16 data_021e9c9c;
extern struct Actor SUB_ACTORS[48];
extern struct Actor MAIN_ACTORS[48];
extern s32 data_021f5c7c;
extern s32 data_021f5c80;
extern s32 STATS_SCREEN_TASK_ID;                 /* the View Stats screen's task id, -1 for none */
extern struct StatsScreen *STATS_SCREEN; /* the View Stats screen, NULL for none */
extern struct BgGraphics data_021f5c8c; /* the View Stats screen's backgrounds */
extern struct BgGraphics data_021f5ca4;
extern struct BgGraphics data_021f5cbc;
extern u32 HEAP_PEAK_USE;
extern u8 ITEM_CACHE_REGISTERED;
extern s32 VBLANK_CALLBACK_COUNT;
extern u16 data_021d8cb8;
extern s32 data_021e33dc;
extern struct NNSiFndHeapHead *SMALL_HEAP;
extern s8 data_021b4a08;
extern u16 SUB_PALETTE_TARGET[PALETTE_COLOR_COUNT];
extern u16 SUB_PALETTE_BASE[PALETTE_COLOR_COUNT];
extern u16 MAIN_PALETTE_TARGET[PALETTE_COLOR_COUNT];
extern u16 MAIN_PALETTE_BASE[PALETTE_COLOR_COUNT];
extern s32 SUB_FADE_STEP;
extern s32 SUB_FADE_TARGET;
extern s32 SUB_FADE_BRIGHTNESS;
extern s32 SUB_FADE_FRAMES;
extern s32 MAIN_FADE_TASK_ID;
extern s32 MAIN_FADE_STEP;
extern s32 MAIN_FADE_TARGET;
extern s32 MAIN_FADE_BRIGHTNESS;
extern s32 SUB_FADE_TASK_ID;
extern s32 data_021da3fc;
extern void *data_021da410;
extern s32 data_021da78c;
extern struct PlayerName PLAYER_NAME;
extern s32 data_021e5ae0;
extern struct Button BUTTONS[32];
extern u8 data_021e5c8c;
extern s16 data_021e9c90;
extern s16 data_021e9c94;
extern s16 data_021e9ca8;
extern s16 data_021e9cac;
extern s32 data_021e9cb0;
extern s32 data_021e9cb4;
extern s8 MAIN_WINDOW_FRAME_SLOT;
extern s8 SUB_WINDOW_FRAME_SLOT;
extern struct SpriteKind SPRITE_KINDS[];
extern struct SpritePalette SPRITE_PALETTES[SPRITE_RESOURCE_COUNT];
extern struct SpriteCells SPRITE_CELLS[SPRITE_RESOURCE_COUNT];
extern struct SpriteChars SPRITE_CHARS[SPRITE_RESOURCE_COUNT];
extern struct ItemCacheEntry ITEM_CACHE[ITEM_CACHE_COUNT];
extern u8 data_021bc1b4[];
extern s8 data_021d8c98;
extern s8 data_021d8cac;
extern u8 data_021db618[];
extern u8 data_021db718[][12];
extern struct EquipSlot WEAPON_STOCK[EQUIP_STOCK_SIZE];
extern struct EquipSlot ARMOR_STOCK[EQUIP_STOCK_SIZE];
extern struct EquipSlot ACCESSORY_STOCK[EQUIP_STOCK_SIZE];
extern s32 data_0210e960[];
extern s32 data_02111c00[][4];
extern u16 data_02111c04[];
extern u16 data_02111c06[];
extern struct DigiEgg DIGI_EGGS[48];
extern u8 data_02127030[];
extern s16 BG_SCREEN_RIGHT_OFFSETS[];
extern s16 BG_SCREEN_LOWER_OFFSETS[];
extern u8 data_021ab9e0[];
extern s16 SCRIPT_GLOBALS[SCRIPT_GLOBAL_COUNT];
extern struct ScriptThread SCRIPT_THREADS[SCRIPT_THREAD_COUNT];
extern s32 data_021da404;
extern u16 TEXT_ARGS[8][21];
extern struct Digimon data_021db82c[40];
extern struct EggRecord EGG_GALLERY[48];
extern s32 data_021e5cc4;
extern s16 ACTOR_ROUTES[8][256];
extern u8 data_0212ad34[];
extern struct MenuLayout MENU_LAYOUTS[10];
extern s32 data_0213854c[];
#define UNIT_PANEL_SLOT_COUNT 8
#define UNIT_PANEL_SPRITES 5

/* The unit panels that ov006's item and Digimon screens show through ov002's
 * (func_ov002_0224b7b8 and the like), in slots. */
struct UnitPanelSlots {
    /* 0x00 */ u16 ids[UNIT_PANEL_SLOT_COUNT]; /* 0xFFFF for a free slot */
    /* 0x10 */ s32 unk10[UNIT_PANEL_SLOT_COUNT];
    /* 0x30 */ s16 x[UNIT_PANEL_SLOT_COUNT];
    /* 0x40 */ s16 y[UNIT_PANEL_SLOT_COUNT];
    /* 0x50 */ s16 unk50[UNIT_PANEL_SPRITES];
    /* 0x5A */ s16 unk5A[UNIT_PANEL_SPRITES];
    /* 0x64 */ s32 sprites[UNIT_PANEL_SPRITES]; /* main screen sprites, -1 for none */
    /* 0x78 */ s16 unk78;
    /* 0x7A */ s16 unk7A;
    /* 0x7C */ s32 sprite; /* a main screen sprite, -1 for none */
};
extern struct UnitPanelSlots UNIT_PANEL_SLOTS;
extern u8 UNIT_CHANGES[UNIT_COUNT];
extern s32 CHOICE_MENU_TASK;
extern u16 data_021da418;
extern void *data_021da41c;
extern struct DigimonItem data_021df9d0[8];
extern u8 data_021e0cc8[];
extern s32 MENU_TASK_ID;
extern s32 data_021e5cac;
extern s32 data_021e5cb0;
extern struct FollowTrail FOLLOW_TRAIL;
extern u8 data_0210c11c[][8];
extern s32 data_02111bfc[][4];
extern u8 data_02113698[][0x18];
extern s32 data_02117c40[];
extern s32 data_0211809c[];
extern s32 data_0211a688[];
extern s32 data_0211f4e0[];
extern u8 data_02127678[];
extern struct SpeciesRecord SPECIES_RECORDS[426];
extern u8 data_02116b7c[];
extern s32 data_02118a78[];
extern s16 data_02127644[][2];
extern struct SpriteOffset SPRITE_OFFSETS[13]; /* the 13th, all zero, when no id matches */
extern u8 data_02135714;
extern void *MOVIE_GRAPHICS[3]; /* the movie's palette, characters and screen */
extern s32 DIAL_TASK_IDS[];
extern s16 data_021b4978;
extern s32 CAPTION_TASK_IDS[4]; /* the captions' task ids, -1 for none */
extern s32 SCROLL_BAR_IDS[8]; /* the scroll bars' task ids, -1 for none */
extern s32 TEXT_LIST_IDS[];
extern s16 data_021b53dc[];
extern s16 data_021b53ec[];
extern s32 data_021b53fc[];
#define PANEL_CHANGED 0x2 /* in a display's flags: to be drawn again */

/* The item and equipment displays of menus/widgets/item_displays.c: one of each. Their draw
 * functions say what each shows. */

/* The names of items (getItemHelp). */
struct ItemNameDisplay {
    /* 0x00 */ u8 window;
    /* 0x01 */ u8 flags; /* PANEL_IN_USE, PANEL_CHANGED */
    /* 0x02 */ s16 x;    /* in tiles, in the window */
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s32 sprite;
    /* 0x0C */ u8 unkC[8];
    /* 0x14 */ u16 screenFlags; /* PANEL_ON_SUB_SCREEN */
    /* 0x16 */ u8 unk16[2];
    /* 0x18 */ struct WindowImage images[2];
};

/* An item's record (func_020a1410), in the shops too. */
struct ItemRecordDisplay {
    /* 0x00 */ u8 window;
    /* 0x01 */ u8 flags;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ u8 unk6[4];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s32 sprite;
    /* 0x10 */ u8 unk10[4];
    /* 0x14 */ s32 sprite2;
    /* 0x18 */ u8 unk18[4];
    /* 0x1C */ s32 sprite3;
    /* 0x20 */ u8 unk20[8];
    /* 0x28 */ u16 screenFlags;
    /* 0x2A */ u8 unk2A[2];
    /* 0x2C */ struct WindowImage images[2];
};

/* A piece of equipment (func_020a142c). */
struct EquipmentDisplay {
    /* 0x00 */ u8 window;
    /* 0x01 */ u8 flags;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s32 sprites[2];
    /* 0x10 */ u8 unk10[0xA];
    /* 0x1A */ u16 screenFlags;
    /* 0x1C */ u8 unk1C[4];
    /* 0x20 */ struct WindowImage images[3];
};

/* The equipment a Digimon has on (getEquippedItem). */
struct EquippedDisplay {
    /* 0x00 */ u8 window;
    /* 0x01 */ u8 flags;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ u8 unk6[2];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 sprite;
    /* 0x10 */ u8 unk10[4];
    /* 0x14 */ s32 sprites[3];
    /* 0x20 */ s32 sprites2[3];
    /* 0x2C */ u8 unk2C[8];
    /* 0x34 */ u16 screenFlags;
    /* 0x36 */ u8 unk36[0xF2];
};

/* The bag's items (ITEM_STOCK), in rows of a text list. */
struct BagDisplay {
    /* 0x000 */ u8 window;
    /* 0x001 */ u8 flags;
    /* 0x002 */ s16 x;
    /* 0x004 */ s16 y;
    /* 0x006 */ u8 unk6[2];
    /* 0x008 */ s32 sprites[6];
    /* 0x020 */ u8 unk20[4];
    /* 0x024 */ s32 sprites2[6];
    /* 0x03C */ u8 unk3C[0x12];
    /* 0x04E */ u16 screenFlags;
    /* 0x050 */ u8 unk50[0x2D4];
    /* 0x324 */ u8 unk324[0x88]; /* what func_020501f4 returns */
    /* 0x3AC */ s32 textList;
    /* 0x3B0 */ s32 textList2;
};

/* The key items (KEY_ITEMS), in rows of a text list. */
struct KeyItemDisplay {
    /* 0x000 */ u8 window;
    /* 0x001 */ u8 flags;
    /* 0x002 */ s16 x;
    /* 0x004 */ s16 y;
    /* 0x006 */ s16 count; /* func_0205c164's */
    /* 0x008 */ s32 sprites[6];
    /* 0x020 */ u8 unk20[0x2E];
    /* 0x04E */ u16 screenFlags;
    /* 0x050 */ u8 unk50[2];
    /* 0x052 */ s16 unk52;
    /* 0x054 */ u8 unk54[0x320];
    /* 0x374 */ u8 list[0x8C]; /* func_0205c164's, what getKeyItemDisplayList returns */
    /* 0x400 */ s32 textList;
};
extern struct ItemNameDisplay ITEM_NAME_DISPLAY[1];
extern struct ItemRecordDisplay ITEM_RECORD_DISPLAY[1];
extern struct EquipmentDisplay EQUIPMENT_DISPLAY[1];
/* The skill displays of menus/widgets/skill_displays.c: the moves (func_020a1250) and the
 * abilities (func_020a1268), each as a list and as one. One of each. */

struct MoveListDisplay {
    /* 0x00 */ u8 window;
    /* 0x01 */ u8 flags; /* PANEL_IN_USE */
    /* 0x02 */ s16 x;    /* in tiles, in the window */
    /* 0x04 */ s16 y;
    /* 0x06 */ u8 unk6[6];
    /* 0x0C */ s32 sprite;
    /* 0x10 */ u8 unk10[8];
    /* 0x18 */ u16 screenFlags; /* PANEL_ON_SUB_SCREEN */
    /* 0x1A */ u8 unk1A[0xBA];
    /* 0xD4 */ s32 textList;
};

struct MoveDisplay {
    /* 0x00 */ u8 window;
    /* 0x01 */ u8 flags;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ u8 unk6[0xA];
    /* 0x10 */ s32 sprite;
    /* 0x14 */ u8 unk14[0xA];
    /* 0x1E */ u16 screenFlags;
    /* 0x20 */ u8 unk20[4];
    /* 0x24 */ struct WindowImage images[3];
};

struct AbilityListDisplay {
    /* 0x000 */ u8 window;
    /* 0x001 */ u8 flags;
    /* 0x002 */ s16 x;
    /* 0x004 */ s16 y;
    /* 0x006 */ u8 unk6[0x4C2];
    /* 0x4C8 */ s32 textLists[4];
    /* 0x4D8 */ u8 unk4D8[4];
};

struct AbilityDisplay {
    /* 0x00 */ u8 window;
    /* 0x01 */ u8 flags; /* PANEL_IN_USE, PANEL_CHANGED */
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ u8 unk6[4];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s32 sprites[4];
    /* 0x1C */ u8 unk1C[4];
    /* 0x20 */ s32 sprite2;
    /* 0x24 */ u8 unk24[4];
    /* 0x28 */ s32 sprite;
    /* 0x2C */ u8 unk2C[8];
    /* 0x34 */ u16 screenFlags;
    /* 0x36 */ u8 unk36[2];
    /* 0x38 */ struct WindowImage images[4];
};
extern struct AbilityDisplay ABILITY_DISPLAY[1];
extern struct MoveListDisplay MOVE_LIST_DISPLAY[1];
extern struct EquippedDisplay EQUIPPED_DISPLAY[1];
#define DIGIMON_DETAIL_COUNT 2

/* What engine/ui/gauge.c's gauges are drawn from (value * 100 / max). */
struct GaugeParams {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u8 unk6;
    /* 0x08 */ s32 value;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 max;
};

/* A display of a Digimon's details in a window (drawDigimonDetail draws it from
 * struct Params02059d8c), with a gauge of its unk72. */
struct DigimonDetail {
    /* 0x000 */ u8 window;
    /* 0x001 */ u8 flags; /* PANEL_IN_USE, PANEL_CHANGED */
    /* 0x002 */ u8 unk2[6];
    /* 0x008 */ struct Digimon *digimon;
    /* 0x00C */ s32 sprites[2];
    /* 0x014 */ u8 unk14[4];
    /* 0x018 */ s32 sprites2[3];
    /* 0x024 */ u8 unk24[2];
    /* 0x026 */ u16 unk26;
    /* 0x028 */ struct GaugeParams gauge;
    /* 0x03C */ u8 unk3C[0x90];
    /* 0x0CC */ s16 unkCC;
    /* 0x0CE */ s16 unkCE;
    /* 0x0D0 */ s16 unkD0;
    /* 0x0D2 */ u16 unkD2;
    /* 0x0D4 */ u16 unkD4;
    /* 0x0D6 */ u8 unkD6[2];
    /* 0x0D8 */ s16 unkD8;
    /* 0x0DA */ s16 unkDA;
    /* 0x0DC */ u8 unkDC[2];
    /* 0x0DE */ u16 screenFlags; /* PANEL_ON_SUB_SCREEN */
    /* 0x0E0 */ u8 unkE0[0xCC];
};
extern struct DigimonDetail DIGIMON_DETAILS[DIGIMON_DETAIL_COUNT];
extern struct BagDisplay BAG_DISPLAY[1];
extern struct KeyItemDisplay KEY_ITEM_DISPLAY[1];
extern struct LinkPartyItem LINK_PARTY_ITEMS2[LINK_PARTY_DIGIMON_COUNT];
extern struct LinkPartyItem LINK_PARTY_ITEMS1[LINK_PARTY_DIGIMON_COUNT];
extern struct LinkPartyItem LINK_PARTY_ITEMS0[LINK_PARTY_DIGIMON_COUNT];
extern struct ItemSlot ITEM_STOCK[ITEM_ID_WEAPONS];
extern u16 KEY_ITEMS[ITEM_ID_END - ITEM_ID_KEY_ITEMS];
extern struct MapCharacter data_02107f34[];
extern u16 data_02107f3a[];
extern s32 data_0210b7f0[];
extern s16 UNIT_PANEL_OFFSETS[UNIT_PANEL_SLOT_COUNT * 2]; /* each unit panel slot's offset: x, y */
extern u16 data_02126ff8[];
extern s16 data_02127008[];
extern u16 data_0212701c[];
extern u8 data_02127144[];
extern u8 data_02127164[];
extern s16 SINE_TABLE[256]; /* the sine of 256ths of a turn, 8.8 fixed point as the OAM's affine parameters */
extern s16 COSINE_TABLE[256]; /* the cosine */
extern s32 data_02135834[][5];
extern char data_021382c8[];
extern char data_021382cc[];
extern s32 data_021ab808[];
extern s32 data_021ab848[];
extern s16 MAIN_OAM_AFFINE[OAM_AFFINE_COUNT][4]; /* the main screen's affine parameters */
extern s16 SUB_OAM_AFFINE[OAM_AFFINE_COUNT][4]; /* the sub screen's */
extern struct Panel PANELS[PANEL_COUNT];
extern struct PartyPanel PARTY_PANELS[PANEL_COUNT];
extern struct MoveDisplay MOVE_DISPLAY[1];
#define NUMBER_DISPLAY_COUNT 2

/* A display of up to four numbers in a window (drawNumberDisplays draws it), for
 * the status window. */
struct NumberDisplay {
    /* 0x00 */ u8 window;
    /* 0x01 */ u8 flags; /* PANEL_IN_USE, PANEL_CHANGED */
    /* 0x02 */ s16 x;    /* in tiles, in the window */
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 values[4];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u16 unk12;
    /* 0x14 */ u16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ struct WindowImage images[4];
};
extern struct NumberDisplay NUMBER_DISPLAYS[NUMBER_DISPLAY_COUNT];
extern struct AbilityListDisplay ABILITY_LIST_DISPLAY[1];
/* A panel of ov006's item menu (func_ov006_0227e520), one of 3: two sprites
 * and three images in a window. */
struct ItemMenuPanel {
    /* 0x00 */ u8 window;
    /* 0x01 */ u8 flags; /* PANEL_IN_USE */
    /* 0x02 */ s16 x;    /* in tiles, in the window */
    /* 0x04 */ s16 y;
    /* 0x06 */ u8 unk6[6];
    /* 0x0C */ s32 sprite;
    /* 0x10 */ u8 unk10[4];
    /* 0x14 */ s32 sprite2;
    /* 0x18 */ u8 unk18[8];
    /* 0x20 */ u16 screenFlags; /* PANEL_ON_SUB_SCREEN */
    /* 0x22 */ u8 unk22[2];
    /* 0x24 */ struct WindowImage images[3];
    /* 0x9C */ u8 unk9C[0x148];
};
extern struct ItemMenuPanel ITEM_MENU_PANELS[PANEL_COUNT];
#define STATUS_WINDOW_COUNT 2

/* A Digimon's status in a window (drawStatusWindow draws it from struct
 * StatusParams). */
struct StatusWindow {
    /* 0x000 */ u8 window;
    /* 0x001 */ u8 flags; /* PANEL_IN_USE */
    /* 0x002 */ u8 unk2[0xE];
    /* 0x010 */ s32 sprites[3];
    /* 0x01C */ u8 unk1C[0x1A];
    /* 0x036 */ u16 screenFlags; /* PANEL_ON_SUB_SCREEN */
    /* 0x038 */ u8 unk38[0x2B8];
};
extern struct StatusWindow STATUS_WINDOWS[STATUS_WINDOW_COUNT];
extern u16 data_021da778;
extern u16 data_021da77c;
extern u16 data_021da780;
extern u16 data_021da784;
extern u16 data_021da788;
extern u8 data_021e31f8[];
extern s8 data_021ea308[];
extern void *data_021eab20[];
extern u16 data_02107f36[][4];
extern u8 data_021168a0[];
extern u8 data_021168c0[];
extern u16 data_021271f4[][4];
extern u16 data_0212720c[][4];
extern s16 data_021283d4[]; /* the skill pages' tabs, 4 each: x, y, width and height */
extern char data_02137658[];
extern char data_0213765c[];
extern char data_02137668[];
extern char data_0213766c[];
extern char data_02137678[];
extern char data_0213767c[];
extern char data_02137688[];
extern char data_0213768c[];
extern s8 data_021382f8[];
extern s8 data_021382fc[];
extern u16 data_021384c0[];
extern u16 data_0213857c[];
extern s8 data_021b3d6c;
extern s8 data_021b3d74;
extern u16 MAIN_OAM_KEYS[OAM_COUNT]; /* the main screen's OAM entries' sort keys */
extern u16 SUB_OAM_KEYS[OAM_COUNT]; /* the sub screen's */
extern union OamAttr SUB_OAM[OAM_COUNT]; /* the sub screen's shadow OAM */
extern union OamAttr MAIN_OAM[OAM_COUNT]; /* the main screen's shadow OAM */
/* The display of an icon (a sprite) and two images in a window, for ov006's
 * item menu (func_ov006_0227e520). */
struct IconDisplay {
    /* 0x00 */ u8 window;
    /* 0x01 */ u8 flags; /* PANEL_IN_USE */
    /* 0x02 */ s16 x;    /* in tiles, in the window */
    /* 0x04 */ s16 y;
    /* 0x06 */ u8 unk6[2];
    /* 0x08 */ s32 sprite; /* -1 for none */
    /* 0x0C */ u8 unkC[2];
    /* 0x0E */ s16 unkE; /* -1 when there is no second image */
    /* 0x10 */ u8 unk10[4];
    /* 0x14 */ u16 screenFlags; /* PANEL_ON_SUB_SCREEN */
    /* 0x16 */ u8 unk16[6];
    /* 0x1C */ struct WindowImage images[2];
};
extern struct IconDisplay ICON_DISPLAY;
extern s8 PANEL_UNITS[UNIT_PANEL_COUNT];
extern u8 data_021bd688[];
extern u8 data_021be888[];
extern u8 data_021c428c[];
extern u8 data_021c548c[];
/* The play time, counted in ticks of 1/PLAY_TIME_TICKS s (getPlayTime). */
#define PLAY_TIME_TICKS 64
extern s32 PLAY_TIME;
extern u8 data_021da998[];
extern u8 data_021dac48[];
extern u8 data_021daf28[];
extern u8 data_021db278[];
extern s8 data_021e5c80;
extern u8 data_021e5c88;
extern u8 data_021e5c90;
extern u8 data_021e5c94;
extern s8 data_021e5c98;
extern s32 data_021e5cc0;
extern s8 data_021e9e38[];
extern void *data_021eb4bc[];
extern void *data_021ebe58[];
extern void (*data_021366a4[])(void);
extern s32 (*data_021366b8[])(void);
extern void (*data_02136684[])(void);
extern s32 (*data_02136694[])(void);
extern s32 EXP_CURVES[][99];
extern struct StatGrowth STAT_GROWTHS[][6];
extern struct Task **FREE_TASK_SLOTS_TOP; /* the free slots' top, = FREE_TASK_SLOTS */
extern u32 RANDOM_SEED;          /* the random seed */
extern u32 NEXT_TASK_ID;           /* the next task's id */
extern struct Task *FREE_TASK_SLOTS[80]; /* the free slots, NULL once taken */

#endif /* ENGINE_DATA_H */
