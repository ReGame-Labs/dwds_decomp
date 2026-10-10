#ifndef BATTLE_CHARACTERS_DATA_H
#define BATTLE_CHARACTERS_DATA_H

/* Overlay 1, the battle characters: the Digimon drawn from /dat/btchr/ on both
 * screens, in battles and in the menus, with the effects of /dat/bgeff/, the
 * lists of effect sprites, the colour fades and the move scripts of /dat/wz/.
 * Their types, constants and data. */

#include "engine/data.h"
#include "nitro/g2d.h"
#include "types.h"

/* The battle characters: five a screen, each a sprite animated from its .a
 * file, placed at one of the screen's places. */
#define BATTLE_CHR_COUNT 5

/* struct BattleChr's flags. */
#define BATTLE_CHR_IN_USE 1
#define BATTLE_CHR_HIDDEN 0x10 /* not drawn and its sequence stopped */

/* The tiles of each screen's pool, from which every character takes its own. */
#define BATTLE_CHR_POOL_TILES 0x300

/* What a tile allocation that didn't fit leaves, and a character without a sprite. */
#define BATTLE_CHR_NO_TILES 0xFFFF
#define BATTLE_CHR_NO_SPRITE 0xFFFF

/* The duration of the frame that ends a sequence in a .a file. */
#define BTCHR_SEQ_END 0xFFFF

/* The priority of the characters' draw tasks, which endBattleChrs ends
 * by it, and the one of the effects', fades' and move scripts' tasks. */
#define BATTLE_CHR_TASK_PRIORITY 0x11F
#define EFFECT_TASK_PRIORITY 0x120

/* The effects drawn from /dat/bgeff/, sixteen a screen. */
#define BG_EFFECT_COUNT 16

/* struct BgEffect's and struct ListSprite's flags. */
#define EFFECT_IN_USE 1
#define EFFECT_ENDING 0x10000000 /* to be ended by its task */

/* The sprites of the 16-slot lists. */
#define LIST_SPRITE_COUNT 16

/* A move script's length that runs it until one of its commands ends it. */
#define MOVE_SCRIPT_UNTIL_END 0xFFFF

/* The files of a battle character in /dat/btchr/, by number: "%d.c", "%d.l",
 * "%d.n", "%d.p" and "%d.a". */
struct BtchrFiles {
    /* 0x0 */ u16 cFile;
    /* 0x2 */ u16 lFile;
    /* 0x4 */ u16 nFile;
    /* 0x6 */ u16 pFile;
    /* 0x8 */ u16 aFile;
};

/* A frame of a .a file's sequences, which end at a duration of BTCHR_SEQ_END. */
struct BtchrFrame {
    /* 0x0 */ s16 cell;
    /* 0x2 */ u16 duration;
};

/* The head of a .a file. */
struct BtchrAnim {
    /* 0x0 */ u16 size; /* twice the tiles it takes from the screen's pool */
    /* 0x2 */ u16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 unk8;
    /* 0xA */ s16 unkA;
    /* 0xC */ struct BtchrFrame frames[1];
};

/* A battle character on one screen, a sprite animated from its .a file. */
struct BattleChr {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 y; /* 0x60 above the sprite's */
    /* 0x08 */ u8 unk08[0x10];
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u16 chr;   /* the record of BATTLE_CHR_FILES */
    /* 0x22 */ u16 slot;
    /* 0x24 */ u16 place; /* the entry of the position tables data_021ab8e8 and data_021ab868 */
    /* 0x26 */ u16 unk26;
    /* 0x28 */ s32 flags; /* BATTLE_CHR_IN_USE, BATTLE_CHR_HIDDEN */
    /* 0x2C */ s16 cell;
    /* 0x2E */ s16 prevCell;
    /* 0x30 */ s16 time; /* the frames since the sequence started */
    /* 0x32 */ u16 seq;
    /* 0x34 */ u16 frame;
    /* 0x36 */ u16 tileOffset; /* in the screen's pool */
    /* 0x38 */ u16 palette;
    /* 0x3A */ u16 priority;
    /* 0x3C */ s16 loopLimit; /* -1 loops forever */
    /* 0x3E */ s16 loops;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ u16 sprite;
    /* 0x44 */ void *chrData;
    /* 0x48 */ void *unk48;
    /* 0x4C */ void *unk4C;
    /* 0x50 */ void *unk50;
    /* 0x54 */ struct BtchrAnim *anim;
    /* 0x58 */ struct BtchrFrame *frames;
    /* 0x5C */ void *paletteData;
    /* 0x60 */ u8 animDone;
};

/* The task that puts a character in a slot after a delay. */
struct ChrPlaceTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ u16 state; /* CHR_PLACE_TASK_NEW before the first frame */
    /* 0x1E */ s16 timer;
    /* 0x20 */ u16 chr;
    /* 0x22 */ s16 x;
    /* 0x24 */ s16 y;
    /* 0x26 */ u16 palette;
    /* 0x28 */ s32 slot;
    /* 0x2C */ u16 place;
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 withSprite;
    /* 0x30 */ s32 delay;
    /* 0x34 */ u8 show;
};

#define CHR_PLACE_TASK_NEW 0xFFFF

/* An effect drawn into a BG map, at a place counted in tiles. */
struct BgEffect {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s32 flags; /* EFFECT_IN_USE, EFFECT_ENDING */
    /* 0x0C */ u16 effect;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ s32 slot;
    /* 0x14 */ u8 unk14[0xD0];
    /* 0xE4 */ void *unkE4;
    /* 0xE8 */ void *unkE8;
    /* 0xEC */ void *unkEC;
};

/* A sprite of one of the 16-slot lists, drawn at x, y plus the tile offset
 * EFFECT_TILE_OFFSET_X, EFFECT_TILE_OFFSET_Y unless EFFECT_TILE_OFFSET_OFF is set. */
struct ListSprite {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s32 flags; /* EFFECT_IN_USE, EFFECT_ENDING */
    /* 0x8 */ s32 slot;
    /* 0xC */ s32 sprite;
};

/* The task that runs a move's script (/dat/wz/): a list of halfword commands. */
struct MoveScriptTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 *script;
    /* 0x20 */ u16 length; /* MOVE_SCRIPT_UNTIL_END runs it until a command ends it */
    /* 0x22 */ s16 pc;
    /* 0x24 */ s16 wait;
};

/* The task that fades a range of colours a step a frame, to a level. */
struct FadeTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 level;
    /* 0x1E */ s16 step;
    /* 0x20 */ s16 start;
    /* 0x22 */ s16 count;
};

extern s16 MAIN_BATTLE_CHR_TILES_USED;
extern s16 MAIN_BATTLE_CHR_VRAM;
extern s16 SUB_BATTLE_CHR_TILES_USED;
extern s16 SUB_BATTLE_CHR_VRAM;
extern struct BattleChr MAIN_BATTLE_CHRS[BATTLE_CHR_COUNT];
extern struct BattleChr SUB_BATTLE_CHRS[BATTLE_CHR_COUNT];
extern struct BattleChr *MAIN_BATTLE_CHR_ORDER[BATTLE_CHR_COUNT];
extern struct BattleChr *SUB_BATTLE_CHR_ORDER[BATTLE_CHR_COUNT];
extern struct ChrPlaceTask *SUB_BATTLE_CHR_PLACE_TASKS[BATTLE_CHR_COUNT];
extern struct ChrPlaceTask *MAIN_BATTLE_CHR_PLACE_TASKS[BATTLE_CHR_COUNT];
extern u8 EFFECT_TILE_OFFSET_OFF;
extern s16 EFFECT_TILE_OFFSET_Y;
extern s16 EFFECT_TILE_OFFSET_X;
extern s16 data_ov001_0222b1fc;
extern s16 data_ov001_0222b200;
extern s16 data_ov001_0222b204;
extern s16 FADE_LEVEL;
extern s16 data_ov001_0222b20c;
extern struct FadeTask *FADE_TASK;
extern void *MOVE_SCRIPT_FILE;
extern struct MoveScriptTask *MOVE_SCRIPT_TASK;
extern s32 MOVE_SCRIPT_TASK_ID;
extern struct Task *MAIN_BG_EFFECT_TASK;
extern struct Task *SUB_BG_EFFECT_TASK;
extern s32 data_ov001_0222aff4;
extern struct Task *LIST_SPRITE_TASK;
extern u16 SUB_BG_EFFECT_PALETTES[];
extern u16 MAIN_BG_EFFECT_PALETTES[];
extern struct BgEffect MAIN_BG_EFFECTS[BG_EFFECT_COUNT];
extern struct BgEffect SUB_BG_EFFECTS[BG_EFFECT_COUNT];
extern struct ListSprite MAIN_LIST_SPRITES[LIST_SPRITE_COUNT];
extern s16 SUB_BG_EFFECT_VRAM[][8];
extern s16 MAIN_BG_EFFECT_VRAM[][8];
extern u8 SUB_BATTLE_CHR_RELOAD[];
extern u8 MAIN_BATTLE_CHR_RELOAD[];
/* The effects' names in /dat/bgeff/ are a table at data_ov001_02200564, four
 * an effect: two lists, then its "<n>p" and "<n>d" files. This symbol starts at
 * the table's fourth column, the "d" files. */
extern char *data_ov001_02200570[][4];
extern char data_ov001_02201390[];
extern s16 BG_EFFECT_PALETTE_USERS[];
extern s16 BG_EFFECT_CHAR_USERS[];
extern s16 data_ov001_022123c0[];
extern s16 data_ov001_02212574[];
extern void *data_ov001_02212df0[];
extern struct BtchrFiles BATTLE_CHR_FILES[];
extern char data_ov001_02201300[];
extern char data_ov001_02201308[];
extern char data_ov001_02201314[];
extern char data_ov001_0220131c[];
extern char data_ov001_02201350[];
extern char data_ov001_02201358[];
extern char data_ov001_02201364[];
extern char data_ov001_0220136c[];
extern s8 BTCHR_P_USERS[];
extern s8 BTCHR_A_USERS[];
extern s8 BTCHR_C_USERS[];
extern void *BTCHR_C_FILES[];
extern struct NNSG2dPaletteData *BTCHR_PALETTES[];
extern void *BTCHR_P_FILES[];
extern void *BTCHR_A_FILES[];
extern struct CharacterData *BTCHR_CHAR_DATA[];
extern struct ListSprite SUB_LIST_SPRITES[LIST_SPRITE_COUNT];

#endif /* BATTLE_CHARACTERS_DATA_H */
