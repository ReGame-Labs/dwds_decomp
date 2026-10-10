#include "field/map/map_sprite_draw.h"
#include "engine/data.h"
#include "engine/system/setup.h"
#include "field/map/data.h"
#include "field/map/map_sprite.h"
#include "nitro/g2.h"

/* Finds the frame of animation that shows frameTime frames into it, from the
 * animation file's first frame in *frame: leaves it in *frame and returns its
 * cell. Past the animation's end, frameTime goes back to 0 and the first frame
 * shows. */
s16 findMapAnimFrame(struct MapAnimFrame **frame, u16 animation, s16 *frameTime) {
    u16 i;
    u16 total   = 0;
    u16 skipped = 0;

    for (;;) {
        if (skipped == animation) {
            break;
        }
        if ((*frame)->cell == 0xFFFF && (*frame)->duration == 0xFFFF) {
            skipped++;
        }
        (*frame)++;
    }
    i = 0;
    do {
        total += (*frame)[i].duration;
        if (total > *frameTime) {
            *frame += i;
            return (*frame)->cell;
        }
        i++;
    } while ((*frame)[i].x != -1 || (*frame)[i].y != -1 || (*frame)[i].cell != 0xFFFF || (*frame)[i].duration != 0xFFFF);
    *frameTime = 0;
    return (*frame)->cell;
}

/* The task of the main screen's map sprites: each frame it steps their
 * animations, draws those within reach of the screen where the map has
 * scrolled, in order of y, and then ends the sprites asked to end. */
void tickMainMapSprites(void) {
    s32 i;
    u32 effect = GX_OAM_EFFECT_NONE;
    struct MapSprite *sprite;
    u16 character;
    struct MapAnimFrame *frame;
    s16 x;
    s16 y;
    union OamAttr attr;

    sortMainMapSprites();
    for (i = 0; i < MAP_SPRITE_COUNT; i++) {
        sprite = MAIN_MAP_SPRITE_ORDER[i];
        /* The sort put the unused sprites last. */
        if (!(sprite->flags & MAP_SPRITE_IN_USE)) {
            break;
        }
        if (sprite->flags & MAP_SPRITE_HIDDEN) {
            continue;
        }
        character         = sprite->character;
        sprite->graphics  = data_021ebe58[data_02107f34[character].graphics];
        sprite->animFile  = data_021eb4bc[data_02107f34[character].anim];
        sprite->animFrame = sprite->animFile->frames;
        sprite->cell      = findMapAnimFrame(&sprite->animFrame, sprite->animation, &sprite->frameTime);
        if (sprite->frameTime == 0) {
            sprite->starts++;
            if (sprite->starts >= 2) {
                sprite->starts = 0;
                requestEndMainMapSprite(sprite->index);
            }
        }
        sprite->halfWidth  = sprite->animFrame->width >> 1;
        sprite->halfHeight = sprite->animFrame->height >> 1;
        sprite->frameTime++;
        frame = sprite->animFrame;
        x     = sprite->x - MAIN_MAP_STATE.x.part.whole - frame->x;
        y     = sprite->y - MAIN_MAP_STATE.y.part.whole - frame->y;
        if (x < -64 || x > 256 || y < -64 || y > 192) {
            continue;
        }
        switch (frame->flip) {
            case 0:
                effect = GX_OAM_EFFECT_NONE;
                break;
            case 1:
                effect = GX_OAM_EFFECT_FLIP_H;
                break;
            case 2:
                effect = GX_OAM_EFFECT_FLIP_V;
                break;
            case 3:
                effect = GX_OAM_EFFECT_FLIP_HV;
                break;
        }
        G2_SetOBJAttr(
            &attr, x, y, sprite->priority, GX_OAM_MODE_NORMAL, FALSE, effect, sprite->shapeSize, GX_OAM_COLORMODE_256,
            sprite->cell * sprite->charsPerCell + sprite->vramBlock + MAIN_MAP_SPRITE_VRAM_BASE, sprite->unk42 >> 4, 0);
        addSubOamEntry(&attr, sprite->unk3A);
        sprite->drawnCell = sprite->cell;
    }
    for (i = 0; i < MAP_SPRITE_COUNT; i++) {
        if (MAIN_MAP_SPRITES_ENDING[i] != 0) {
            MAIN_MAP_SPRITES_ENDING[i] = 0;
            endMainMapSprite(i);
        }
    }
}

/* The task of the sub screen's map sprites: each frame it steps their
 * animations, draws those within reach of the screen where the map has
 * scrolled, in order of y, and then ends the sprites asked to end. */
void tickSubMapSprites(void) {
    s32 i;
    u32 effect = GX_OAM_EFFECT_NONE;
    struct MapSprite *sprite;
    u16 character;
    struct MapAnimFrame *frame;
    s16 x;
    s16 y;
    union OamAttr attr;

    sortSubMapSprites();
    for (i = 0; i < MAP_SPRITE_COUNT; i++) {
        sprite = SUB_MAP_SPRITE_ORDER[i];
        if (!(sprite->flags & MAP_SPRITE_IN_USE) || (sprite->flags & MAP_SPRITE_HIDDEN)) {
            continue;
        }
        character         = sprite->character;
        sprite->graphics  = data_021ebe58[data_02107f34[character].graphics];
        sprite->animFile  = data_021eb4bc[data_02107f34[character].anim];
        sprite->animFrame = sprite->animFile->frames;
        sprite->cell      = findMapAnimFrame(&sprite->animFrame, sprite->animation, &sprite->frameTime);
        if (sprite->frameTime == 0) {
            sprite->starts++;
            if (sprite->starts >= 2) {
                sprite->starts = 0;
                requestEndSubMapSprite(sprite->index);
            }
        }
        sprite->halfWidth  = sprite->animFrame->width >> 1;
        sprite->halfHeight = sprite->animFrame->height >> 1;
        sprite->frameTime++;
        frame = sprite->animFrame;
        x     = sprite->x - SUB_MAP_STATE.x.part.whole - frame->x;
        y     = sprite->y - SUB_MAP_STATE.y.part.whole - frame->y;
        if (x < -64 || x > 256 || y < -64 || y > 192) {
            continue;
        }
        switch (frame->flip) {
            case 0:
                effect = GX_OAM_EFFECT_NONE;
                break;
            case 1:
                effect = GX_OAM_EFFECT_FLIP_H;
                break;
            case 2:
                effect = GX_OAM_EFFECT_FLIP_V;
                break;
            case 3:
                effect = GX_OAM_EFFECT_FLIP_HV;
                break;
        }
        G2_SetOBJAttr(&attr, x, y, sprite->priority, GX_OAM_MODE_NORMAL, FALSE, effect, sprite->shapeSize,
                      GX_OAM_COLORMODE_256, sprite->cell * sprite->charsPerCell + sprite->vramBlock + SUB_MAP_SPRITE_VRAM_BASE,
                      sprite->unk42 >> 4, 0);
        addSubOamEntry(&attr, sprite->unk3A);
        sprite->drawnCell = sprite->cell;
    }
    for (i = 0; i < MAP_SPRITE_COUNT; i++) {
        if (SUB_MAP_SPRITES_ENDING[i] != 0) {
            SUB_MAP_SPRITES_ENDING[i] = 0;
            endSubMapSprite(i);
        }
    }
}

/* Sorts the main screen's map sprites for drawing: those in use first, by y. */
void sortMainMapSprites(void) {
    s16 i;
    s16 j;
    BOOL swap;
    struct MapSprite *sprite;

    for (i = 0; i < MAP_SPRITE_COUNT - 1; i++) {
        for (j = MAP_SPRITE_COUNT - 1; j > i; j--) {
            swap = FALSE;
            if (!(MAIN_MAP_SPRITE_ORDER[j - 1]->flags & MAP_SPRITE_IN_USE)) {
                swap = TRUE;
            } else if ((MAIN_MAP_SPRITE_ORDER[j]->flags & MAP_SPRITE_IN_USE) &&
                       MAIN_MAP_SPRITE_ORDER[j]->y < MAIN_MAP_SPRITE_ORDER[j - 1]->y) {
                swap = TRUE;
            }
            if (swap) {
                sprite                       = MAIN_MAP_SPRITE_ORDER[j];
                MAIN_MAP_SPRITE_ORDER[j]     = MAIN_MAP_SPRITE_ORDER[j - 1];
                MAIN_MAP_SPRITE_ORDER[j - 1] = sprite;
            }
        }
    }
}

/* Sorts the sub screen's map sprites for drawing: those in use first, by y. */
void sortSubMapSprites(void) {
    s16 i;
    s16 j;
    BOOL swap;
    struct MapSprite *sprite;

    for (i = 0; i < MAP_SPRITE_COUNT - 1; i++) {
        for (j = MAP_SPRITE_COUNT - 1; j > i; j--) {
            swap = FALSE;
            if (!(SUB_MAP_SPRITE_ORDER[j - 1]->flags & MAP_SPRITE_IN_USE)) {
                swap = TRUE;
            } else if ((SUB_MAP_SPRITE_ORDER[j]->flags & MAP_SPRITE_IN_USE) &&
                       SUB_MAP_SPRITE_ORDER[j]->y < SUB_MAP_SPRITE_ORDER[j - 1]->y) {
                swap = TRUE;
            }
            if (swap) {
                sprite                      = SUB_MAP_SPRITE_ORDER[j];
                SUB_MAP_SPRITE_ORDER[j]     = SUB_MAP_SPRITE_ORDER[j - 1];
                SUB_MAP_SPRITE_ORDER[j - 1] = sprite;
            }
        }
    }
}

/* Takes count blocks of 128 bytes of the main screen's sprite VRAM for the map
 * sprites' graphics, from the top of a stack: -1 if they don't fit. */
s16 allocMainMapSpriteVram(s16 count) {
    s16 block = MAIN_MAP_SPRITE_VRAM_USED;

    MAIN_MAP_SPRITE_VRAM_USED = block + count;
    if (MAIN_MAP_SPRITE_VRAM_USED > MAIN_MAP_SPRITE_VRAM_SIZE) {
        MAIN_MAP_SPRITE_VRAM_USED -= count;
        return -1;
    }
    return block;
}

/* Frees the main screen's sprite VRAM from block on, and with it everything
 * taken after it. */
void freeMainMapSpriteVram(s16 block) {
    if (MAIN_MAP_SPRITE_VRAM_USED > block) {
        MAIN_MAP_SPRITE_VRAM_USED = block;
    }
}

/* The same for the sub screen. */
s16 allocSubMapSpriteVram(s16 count) {
    s16 block = SUB_MAP_SPRITE_VRAM_USED;

    SUB_MAP_SPRITE_VRAM_USED = block + count;
    if (SUB_MAP_SPRITE_VRAM_USED > SUB_MAP_SPRITE_VRAM_SIZE) {
        SUB_MAP_SPRITE_VRAM_USED -= count;
        return -1;
    }
    return block;
}

/* The same for the sub screen. */
void freeSubMapSpriteVram(s16 block) {
    if (SUB_MAP_SPRITE_VRAM_USED > block) {
        SUB_MAP_SPRITE_VRAM_USED = block;
    }
}
