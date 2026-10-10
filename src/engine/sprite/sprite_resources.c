#include "engine/sprite/sprite_resources.h"
#include "engine/data.h"

/* The index of the set of characters of an id in its table, or -1. */
s16 findSpriteChars(s16 id) {
    s32 i;

    for (i = 0; i < SPRITE_RESOURCE_COUNT; i++) {
        if (id == SPRITE_CHARS[i].id) {
            return i;
        }
    }
    return -1;
}

/* The same for the cells. */
s16 findSpriteCells(s16 id) {
    s32 i;

    for (i = 0; i < SPRITE_RESOURCE_COUNT; i++) {
        if (id == SPRITE_CELLS[i].id) {
            return i;
        }
    }
    return -1;
}

/* A free entry of the palettes' table, or -1. */
s16 findFreeSpritePalette(void) {
    s32 i;

    for (i = 0; i < SPRITE_RESOURCE_COUNT; i++) {
        if (SPRITE_PALETTES[i].id == -1) {
            return i;
        }
    }
    return -1;
}

/* The index of the palette of an id in its table, or -1. */
s16 findSpritePalette(s16 id) {
    s32 i;

    for (i = 0; i < SPRITE_RESOURCE_COUNT; i++) {
        if (id == SPRITE_PALETTES[i].id) {
            return i;
        }
    }
    return -1;
}
