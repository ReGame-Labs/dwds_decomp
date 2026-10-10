#ifndef FIELD_MAP_DATA_H
#define FIELD_MAP_DATA_H

/* The field map overlay's (ov000) types and data: the map sprites, their
 * animations, the layers' files and the map rectangles. */

#include "types.h"

/* Each screen has 48 map sprites. */
#define MAP_SPRITE_COUNT 48

/* MapSprite.flags */
#define MAP_SPRITE_IN_USE 0x1
#define MAP_SPRITE_HIDDEN 0x1000

/* A frame of a map character's animation: a cell of its graphics and how long
 * it shows. An animation ends with a frame of -1s, though skipping animations
 * looks only at the cell and the duration. */
struct MapAnimFrame {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ u16 width;
    /* 0x6 */ u16 height;
    /* 0x8 */ u16 flip; /* 1 horizontal, 2 vertical, 3 both */
    /* 0xA */ u16 cell;
    /* 0xC */ u16 duration; /* in frames */
};

/* A map character's animation file, /dat/mchr/%xa. */
struct MapAnimFile {
    /* 0x0 */ u16 shape; /* the OAM shape and size of its cells, 0-11 */
    /* 0x2 */ u8 unk2[8];
    /* 0xA */ struct MapAnimFrame frames[1];
};

/* A sprite of a map character, one of MAP_SPRITE_COUNT a screen has, drawn
 * over that screen's map by its task (tickSubMapSprites for the sub screen,
 * tickMainMapSprites for the main one). */
struct MapSprite {
    /* 0x00 */ u8 unk0[2];
    /* 0x02 */ s16 x;
    /* 0x04 */ u8 unk4[2];
    /* 0x06 */ s16 y;
    /* 0x08 */ u8 unk8[0x10];
    /* 0x18 */ s32 index; /* in its screen's array */
    /* 0x1C */ u8 unk1C[2];
    /* 0x1E */ u16 character; /* in the table of map characters, data_02107f34 */
    /* 0x20 */ u32 flags;     /* MAP_SPRITE_* */
    /* 0x24 */ u8 unk24[2];
    /* 0x26 */ s16 halfWidth; /* of the frame showing */
    /* 0x28 */ s16 halfHeight;
    /* 0x2A */ s16 cell; /* of the frame showing */
    /* 0x2C */ s16 drawnCell;
    /* 0x2E */ s16 frameTime; /* frames since the animation started */
    /* 0x30 */ s16 starts;    /* times the animation started: the sprite ends at the second */
    /* 0x32 */ u16 animation; /* in the character's animation file */
    /* 0x34 */ u32 shapeSize; /* the OAM shape (attribute 0) and size (attribute 1 << 16) */
    /* 0x38 */ u16 priority;  /* the sprite's OAM priority */
    /* 0x3A */ u16 unk3A;
    /* 0x3C */ u16 charsPerCell; /* in OAM character names */
    /* 0x3E */ u16 vramBlock;    /* where its graphics are in the sprite VRAM */
    /* 0x40 */ u16 unk40;
    /* 0x42 */ u16 unk42;
    /* 0x44 */ u16 unk44;
    /* 0x46 */ u8 unk46[2];
    /* 0x48 */ void *graphics; /* the character's graphics file, /dat/mchr/%xc */
    /* 0x4C */ struct MapAnimFile *animFile;
    /* 0x50 */ struct MapAnimFrame *animFrame; /* the frame showing */
    /* 0x54 */ u8 unk54[4];
};

/* The files of a map's background layer, from /dat/map/: the palette and the
 * characters are freed once they are in VRAM, the screen is kept. */
struct MapLayerFiles {
    /* 0x0 */ void *palette;
    /* 0x4 */ void *chars;
    /* 0x8 */ void *screen;
};

/* A rectangle of a map's tiles, its edges included, as script commands place
 * actors in them (func_020927f0). Each screen has 32. */
struct MapRect {
    /* 0x0 */ s16 left;
    /* 0x2 */ s16 top;
    /* 0x4 */ s16 right;
    /* 0x6 */ s16 bottom;
    /* 0x8 */ u16 unk8;
};

extern s16 SUB_MAP_SPRITE_VRAM_SIZE;
extern s16 SUB_MAP_SPRITE_VRAM_USED;
extern s16 MAIN_MAP_SPRITE_VRAM_USED;
extern s16 MAIN_MAP_SPRITE_VRAM_SIZE;
extern struct MapLayerFiles data_ov000_0220d8b8;
extern struct MapLayerFiles data_ov000_0220d8c4;
extern struct MapLayerFiles data_ov000_0220d8d0;
extern struct MapLayerFiles data_ov000_0220d8dc;
extern struct MapLayerFiles data_ov000_0220d8e8;
extern struct MapLayerFiles data_ov000_0220d8f4;
extern s8 data_ov000_0220d950;
extern s8 data_ov000_0220d954;
extern s16 MAIN_MAP_SPRITE_VRAM_BASE;
extern s16 SUB_MAP_SPRITE_VRAM_BASE;
extern s32 MAIN_MAP_SPRITE_TASK_ID;
extern s32 SUB_MAP_SPRITE_TASK_ID;
extern u8 MAIN_MAP_SPRITES_ENDING[MAP_SPRITE_COUNT];
extern u8 SUB_MAP_SPRITES_ENDING[MAP_SPRITE_COUNT];
extern struct MapSprite *SUB_MAP_SPRITE_ORDER[MAP_SPRITE_COUNT];
extern struct MapSprite *MAIN_MAP_SPRITE_ORDER[MAP_SPRITE_COUNT];
extern struct MapSprite SUB_MAP_SPRITES[MAP_SPRITE_COUNT];
extern struct MapSprite MAIN_MAP_SPRITES[MAP_SPRITE_COUNT];
extern u16 data_ov000_0220d958;
extern u16 data_ov000_0220d95c;
extern u16 SUB_MAP_CHARACTER_SLOTS[16];
extern struct MapRect SUB_MAP_RECTS[32];
extern char *data_ov000_0220a860[];
extern char data_ov000_0220aba8[];
extern char data_ov000_0220abb4[];
extern u16 SUB_MAP_CHARACTER_VRAM[615];
extern u16 MAIN_MAP_CHARACTER_VRAM[615];
extern s32 data_ov000_0220d960;
extern s32 data_ov000_0220d964;
extern u16 data_ov000_0220d968[16];
extern struct MapRect MAIN_MAP_RECTS[32];
extern s16 data_ov000_0220d860;
extern s16 data_ov000_0220d864;
extern s16 data_ov000_0220d868;
extern s16 data_ov000_0220d86c;
extern char data_ov000_02206790[];
extern char data_ov000_02206794[];
extern void *data_ov000_0220d908;
extern void *data_ov000_0220d90c;
extern void *data_ov000_0220d910[8];
extern void *data_ov000_0220d930[8];

#endif /* FIELD_MAP_DATA_H */
