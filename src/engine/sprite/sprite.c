#include "engine/sprite/sprite.h"
#include "engine/data.h"
#include "engine/gfx/gfx_files.h"
#include "engine/libs.h"
#include "engine/palette/palette_fade.h"
#include "engine/sprite/sprite_create.h"
#include "engine/sprite/sprite_resources.h"
#include "engine/system/system.h"
#include "nitro/g2d.h"

/* Loads the palette of a main screen sprite into a slot of the extended
 * palettes. The casts are those of loadMainPalette's u16 parameters, which its
 * header doesn't give yet. */
void loadMainSpritePalette(u32 index, s32 slot) {
    struct Sprite *sprite;
    u16 paletteId;
    struct SpritePalette *palette;
    struct NNSG2dPaletteData *data;

    sprite = getMainSprite(index);
    if (sprite == NULL) {
        return;
    }
    paletteId = getSpriteKindPalette(sprite->kind);
    palette   = getSpritePalette(findSpritePalette(paletteId));
    data      = palette->data;
    loadMainPalette((u16) (slot * 16 + 0x900), (u16) (getPaletteSize((s32) palette->file, data) >> 1), (s32) data->pRawData);
}

/* The same for a sub screen sprite. */
void loadSubSpritePalette(u32 index, s32 slot) {
    struct Sprite *sprite;
    u16 paletteId;
    struct SpritePalette *palette;
    struct NNSG2dPaletteData *data;

    sprite = getSubSprite(index);
    if (sprite == NULL) {
        return;
    }
    paletteId = getSpriteKindPalette(sprite->kind);
    palette   = getSpritePalette(findSpritePalette(paletteId));
    data      = palette->data;
    loadSubPalette((u16) (slot * 16 + 0x900), (u16) (getPaletteSize((s32) palette->file, data) >> 1), (s32) data->pRawData);
}

/* A main screen sprite of a kind stops using its set of characters, its cells
 * and its palette: each is freed once nothing uses it. A set of characters
 * freed frees its whole SpriteChars. */
void releaseMainSpriteKind(u16 kind, u16 set) {
    u16 charsId;
    u16 cellsId;
    u16 paletteId;
    struct SpriteChars *chars;
    struct SpriteCells *cells;
    struct SpritePalette *palette;

    charsId   = getSpriteKindChars(kind);
    cellsId   = getSpriteKindCells(kind);
    paletteId = getSpriteKindPalette(kind);
    chars     = getSpriteChars(findSpriteChars(charsId));
    cells     = getSpriteCells(findSpriteCells(cellsId));
    palette   = getSpritePalette(findSpritePalette(paletteId));

    chars->mainUsers[set]--;
    if (chars->mainUsers[set] <= 0) {
        chars->mainUsers[set] = 0;
        if (chars->mainUsers[set] == 0 && chars->subUsers[set] == 0) {
            if (chars->files[set] != NULL) {
                heapFree(chars->files[set]);
                chars->files[set] = NULL;
                chars->data[set]  = NULL;
                chars->unk74[set] = 0xFF;
            }
            chars->id = -1;
        }
    }
    cells->users--;
    if (cells->users <= 0) {
        cells->users = 0;
        if (cells->unk4 != NULL) {
            heapFree(cells->unk4);
            cells->unk4 = NULL;
            cells->unkC = NULL;
            heapFree(cells->unk8);
            cells->unk8  = NULL;
            cells->unk10 = NULL;
            heapFree(cells->unk14);
            cells->unk14 = NULL;
        }
        cells->id = -1;
    }
    palette->users--;
    if (palette->users <= 0) {
        palette->users = 0;
        if (palette->file != NULL) {
            heapFree(palette->file);
            palette->file = NULL;
            palette->data = NULL;
        }
        palette->id = -1;
    }
}

/* The same for a sub screen sprite. */
void releaseSubSpriteKind(u16 kind, u16 set) {
    u16 charsId;
    u16 cellsId;
    u16 paletteId;
    struct SpriteChars *chars;
    struct SpriteCells *cells;
    struct SpritePalette *palette;

    charsId   = getSpriteKindChars(kind);
    cellsId   = getSpriteKindCells(kind);
    paletteId = getSpriteKindPalette(kind);
    chars     = getSpriteChars(findSpriteChars(charsId));
    cells     = getSpriteCells(findSpriteCells(cellsId));
    palette   = getSpritePalette(findSpritePalette(paletteId));

    chars->subUsers[set]--;
    if (chars->subUsers[set] <= 0) {
        chars->subUsers[set] = 0;
        if (chars->mainUsers[set] == 0 && chars->subUsers[set] == 0) {
            if (chars->files[set] != NULL) {
                heapFree(chars->files[set]);
                chars->files[set] = NULL;
                chars->data[set]  = NULL;
                chars->unk74[set] = 0xFF;
            }
            chars->id = -1;
        }
    }
    cells->users--;
    if (cells->users <= 0) {
        cells->users = 0;
        if (cells->unk4 != NULL) {
            heapFree(cells->unk4);
            cells->unk4 = NULL;
            cells->unkC = NULL;
            heapFree(cells->unk8);
            cells->unk8  = NULL;
            cells->unk10 = NULL;
            heapFree(cells->unk14);
            cells->unk14 = NULL;
        }
        cells->id = -1;
    }
    palette->users--;
    if (palette->users <= 0) {
        palette->users = 0;
        if (palette->file != NULL) {
            heapFree(palette->file);
            palette->file = NULL;
            palette->data = NULL;
        }
        palette->id = -1;
    }
}

/* Starts an animation of a main screen sprite in use, played loops times (-1 for
 * ever). */
void setMainSpriteAnim(u32 index, s16 anim, s16 loops) {
    struct Sprite *sprite;

    if (index >= SPRITE_COUNT) {
        return;
    }
    sprite = &MAIN_SPRITES[index];
    if (sprite->flags & SPRITE_IN_USE) {
        sprite->anim          = anim;
        sprite->animLoops     = loops;
        sprite->animLoopsDone = 0;
        sprite->unk2C         = 0;
    }
}

/* The same for a sub screen sprite. */
void setSubSpriteAnim(u32 index, s16 anim, s16 loops) {
    struct Sprite *sprite;

    if (index >= SPRITE_COUNT) {
        return;
    }
    sprite = &SUB_SPRITES[index];
    if (sprite->flags & SPRITE_IN_USE) {
        sprite->anim          = anim;
        sprite->animLoops     = loops;
        sprite->animLoopsDone = 0;
        sprite->unk2C         = 0;
    }
}

/* The animation of a main screen sprite. */
u8 getMainSpriteAnim(u32 index) {
    struct Sprite *sprite;

    if (index >= SPRITE_COUNT) {
        return 0;
    }
    sprite = &MAIN_SPRITES[index];
    if (sprite->flags & SPRITE_IN_USE) {
        return sprite->anim;
    }
    return 0;
}

/* Plays a main screen sprite's animation again, loops times. */
void restartMainSpriteAnim(u32 index, s16 loops) {
    struct Sprite *sprite;

    if (index >= SPRITE_COUNT) {
        return;
    }
    sprite = &MAIN_SPRITES[index];
    if (sprite->flags & SPRITE_IN_USE) {
        sprite->animLoops     = loops;
        sprite->animLoopsDone = 0;
        sprite->unk2C         = 0;
    }
}

/* The same for a sub screen sprite. */
void restartSubSpriteAnim(u32 index, s16 loops) {
    struct Sprite *sprite;

    if (index >= SPRITE_COUNT) {
        return;
    }
    sprite = &SUB_SPRITES[index];
    if (sprite->flags & SPRITE_IN_USE) {
        sprite->animLoops     = loops;
        sprite->animLoopsDone = 0;
        sprite->unk2C         = 0;
    }
}

/* Replaces the flags of a main screen sprite in use. */
void setMainSpriteFlags(u32 index, u16 flags) {
    struct Sprite *sprite;

    if (index >= SPRITE_COUNT) {
        return;
    }
    sprite = &MAIN_SPRITES[index];
    if (sprite->flags & SPRITE_IN_USE) {
        sprite->flags = flags | SPRITE_IN_USE;
    }
}

/* The same for a sub screen sprite. */
void setSubSpriteFlags(u32 index, u16 flags) {
    struct Sprite *sprite;

    if (index >= SPRITE_COUNT) {
        return;
    }
    sprite = &SUB_SPRITES[index];
    if (sprite->flags & SPRITE_IN_USE) {
        sprite->flags = flags | SPRITE_IN_USE;
    }
}

/* Sets flags of a main screen sprite in use. */
void addMainSpriteFlags(u32 index, u16 flags) {
    struct Sprite *sprite;

    if (index >= SPRITE_COUNT) {
        return;
    }
    sprite = &MAIN_SPRITES[index];
    if (sprite->flags & SPRITE_IN_USE) {
        sprite->flags |= flags;
    }
}

/* The same for a sub screen sprite. */
void addSubSpriteFlags(u32 index, u16 flags) {
    struct Sprite *sprite;

    if (index >= SPRITE_COUNT) {
        return;
    }
    sprite = &SUB_SPRITES[index];
    if (sprite->flags & SPRITE_IN_USE) {
        sprite->flags |= flags;
    }
}

/* Clears flags of a main screen sprite in use. */
void clearMainSpriteFlags(u32 index, u16 flags) {
    struct Sprite *sprite;

    if (index >= SPRITE_COUNT) {
        return;
    }
    sprite = &MAIN_SPRITES[index];
    if (sprite->flags & SPRITE_IN_USE) {
        sprite->flags &= ~flags;
    }
}

/* The same for a sub screen sprite. */
void clearSubSpriteFlags(u32 index, u16 flags) {
    struct Sprite *sprite;

    if (index >= SPRITE_COUNT) {
        return;
    }
    sprite = &SUB_SPRITES[index];
    if (sprite->flags & SPRITE_IN_USE) {
        sprite->flags &= ~flags;
    }
}

/* A main screen sprite, if in use. */
struct Sprite *getMainSprite(u32 index) {
    if (index >= SPRITE_COUNT) {
        return NULL;
    }
    if (MAIN_SPRITES[index].flags & SPRITE_IN_USE) {
        return &MAIN_SPRITES[index];
    }
    return NULL;
}

/* A sub screen sprite, if in use. */
struct Sprite *getSubSprite(u32 index) {
    if (index >= SPRITE_COUNT) {
        return NULL;
    }
    if (SUB_SPRITES[index].flags & SPRITE_IN_USE) {
        return &SUB_SPRITES[index];
    }
    return NULL;
}

/* Moves a main screen sprite. */
struct Sprite *setMainSpritePos(u32 index, u16 x, u16 y) {
    if (index >= SPRITE_COUNT) {
        return NULL;
    }
    MAIN_SPRITES[index].x = x;
    MAIN_SPRITES[index].y = y;
    return &MAIN_SPRITES[index];
}

/* Moves a sub screen sprite. */
struct Sprite *setSubSpritePos(u32 index, u16 x, u16 y) {
    if (index >= SPRITE_COUNT) {
        return NULL;
    }
    SUB_SPRITES[index].x = x;
    SUB_SPRITES[index].y = y;
    return &SUB_SPRITES[index];
}
