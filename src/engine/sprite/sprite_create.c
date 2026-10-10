#include "engine/sprite/sprite_create.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_resources.h"
#include "engine/system/display.h"
#include "link/link_screen.h"
#include "nitro/mmap.h"

/* Frees all the main screen's sprites. */
void freeMainSprites(void) {
    s32 i;

    freeSubLinkIcon();
    i = 0;
    do {
        freeMainSprite(i);
        i++;
    } while (i < SPRITE_COUNT);
}

/* Frees all the sub screen's sprites. */
void freeSubSprites(void) {
    s32 i;

    freeMainLinkIcon();
    i = 0;
    do {
        freeSubSprite(i);
        i++;
    } while (i < SPRITE_COUNT);
}

/* Frees a main screen sprite. Once no sprite of the screen shows its set of
 * characters, their slot of the sprite VRAM is freed and the sets after it
 * move down (reslotMainSpriteChars). */
void freeMainSprite(u32 index) {
    struct Sprite *sprite;
    u16 set;
    u16 charsId;
    struct SpriteChars *chars;
    u16 slot;

    if (index >= SPRITE_COUNT) {
        return;
    }
    sprite = &MAIN_SPRITES[index];
    if (!(sprite->flags & SPRITE_IN_USE)) {
        return;
    }
    set     = sprite->charIndex;
    charsId = getSpriteKindChars(sprite->kind);
    chars   = getSpriteChars(findSpriteChars(charsId));
    if (chars == NULL) {
        return;
    }
    releaseMainSpriteKind(sprite->kind, set);
    if (chars->mainUsers[set] == 0) {
        func_0208577c(4, chars->mainSlot[set]);
        slot                  = chars->mainSlot[set];
        chars->mainSlot[set]  = 0xFFFF;
        chars->mainDirty[set] = FALSE;
        reslotMainSpriteChars(slot);
    }
    func_02030f18(sprite, 0, sizeof(struct Sprite));
}

/* The same for a sub screen sprite. */
void freeSubSprite(u32 index) {
    struct Sprite *sprite;
    u16 set;
    u16 charsId;
    struct SpriteChars *chars;
    u16 slot;

    if (index >= SPRITE_COUNT) {
        return;
    }
    sprite = &SUB_SPRITES[index];
    if (!(sprite->flags & SPRITE_IN_USE)) {
        return;
    }
    set     = sprite->charIndex;
    charsId = getSpriteKindChars(sprite->kind);
    chars   = getSpriteChars(findSpriteChars(charsId));
    if (chars == NULL) {
        return;
    }
    releaseSubSpriteKind(sprite->kind, set);
    if (chars->subUsers[set] == 0) {
        func_02085710(4, chars->subSlot[set]);
        slot                 = chars->subSlot[set];
        chars->subSlot[set]  = 0xFFFF;
        chars->subDirty[set] = FALSE;
        reslotSubSpriteChars(slot);
    }
    func_02030f18(sprite, 0, sizeof(struct Sprite));
}

/* Once the characters at slot of the main screen's sprite VRAM are freed
 * (freeMainSprite), gives every set of characters from that slot on a new slot,
 * to be copied there again, and moves the sprites that show them to it. */
void reslotMainSpriteChars(u32 slot) {
    s32 i;
    s32 j;
    s32 k;
    struct SpriteChars *chars;
    struct Sprite *sprite;

    for (i = 0; i < SPRITE_RESOURCE_COUNT; i++) {
        chars = getSpriteChars(i);
        for (j = 0; j < SPRITE_CHAR_SETS; j++) {
            if (chars->mainSlot[j] != 0xFFFF && chars->mainSlot[j] >= slot) {
                chars->mainDirty[j] = TRUE;
                chars->mainSlot[j]  = allocMainVram(4, (s16) ((chars->data[j]->size >> 7) + 1));
                for (k = 0, sprite = MAIN_SPRITES; k < SPRITE_COUNT; k++) {
                    if ((sprite->flags & SPRITE_IN_USE) && sprite->charsId == chars->id && sprite->charIndex == j) {
                        sprite->charSlot = chars->mainSlot[j];
                    }
                    sprite++;
                }
            }
        }
    }
}

/* The same for the sub screen. */
void reslotSubSpriteChars(u32 slot) {
    s32 i;
    s32 j;
    s32 k;
    struct SpriteChars *chars;
    struct Sprite *sprite;

    for (i = 0; i < SPRITE_RESOURCE_COUNT; i++) {
        chars = getSpriteChars(i);
        for (j = 0; j < SPRITE_CHAR_SETS; j++) {
            if (chars->subSlot[j] != 0xFFFF && chars->subSlot[j] >= slot) {
                chars->subDirty[j] = TRUE;
                chars->subSlot[j]  = allocSubVram(4, (s16) ((chars->data[j]->size >> 7) + 1));
                for (k = 0, sprite = SUB_SPRITES; k < SPRITE_COUNT; k++) {
                    if ((sprite->flags & SPRITE_IN_USE) && sprite->charsId == chars->id && sprite->charIndex == j) {
                        sprite->charSlot = chars->subSlot[j];
                    }
                    sprite++;
                }
            }
        }
    }
}

/* Queues the copy of the main screen's sets of characters that wait for it
 * to their slots of the sprite VRAM. */
void uploadMainSpriteChars(void) {
    struct VramCopy copy = {0};
    s32 i;
    s32 j;
    struct SpriteChars *chars;

    for (i = 0; i < SPRITE_RESOURCE_COUNT; i++) {
        chars = getSpriteChars(i);
        for (j = 0; j < SPRITE_CHAR_SETS; j++) {
            if (chars->mainDirty[j]) {
                copy.src  = chars->data[j]->data;
                copy.dest = (void *) (HW_OBJ_VRAM + chars->mainSlot[j] * 128);
                copy.size = chars->data[j]->size;
                queueVramTransfer(&copy);
                chars->mainDirty[j] = FALSE;
            }
        }
    }
}

/* The same for the sub screen. */
void uploadSubSpriteChars(void) {
    struct VramCopy copy = {0};
    s32 i;
    s32 j;
    struct SpriteChars *chars;

    for (i = 0; i < SPRITE_RESOURCE_COUNT; i++) {
        chars = getSpriteChars(i);
        for (j = 0; j < SPRITE_CHAR_SETS; j++) {
            if (chars->subDirty[j]) {
                copy.src  = chars->data[j]->data;
                copy.dest = (void *) (HW_DB_OBJ_VRAM + chars->subSlot[j] * 128);
                copy.size = chars->data[j]->size;
                queueVramTransfer(&copy);
                chars->subDirty[j] = FALSE;
            }
        }
    }
}

/* The characters, palette and cells of a kind of sprite. */
s16 getSpriteKindChars(s32 kind) {
    return SPRITE_KINDS[kind].chars;
}

/* The palette of a kind of sprite. */
s16 getSpriteKindPalette(s32 kind) {
    return SPRITE_KINDS[kind].palette;
}

/* The cells of a kind of sprite. */
s16 getSpriteKindCells(s32 kind) {
    return SPRITE_KINDS[kind].cells;
}

/* The sprite resources by their index in their tables, the slots of
 * findSpriteChars and its kin. */
struct SpriteChars *getSpriteChars(s16 index) {
    if (index == -1) {
        return NULL;
    }
    return &SPRITE_CHARS[index];
}

struct SpriteCells *getSpriteCells(s16 index) {
    if (index == -1) {
        return NULL;
    }
    return &SPRITE_CELLS[index];
}

struct SpritePalette *getSpritePalette(s32 index) {
    if (index != -1) {
        return &SPRITE_PALETTES[index];
    }
    return NULL;
}
