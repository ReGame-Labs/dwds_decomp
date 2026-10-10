#include "menus/digimon/guide_slides.h"
#include "engine/bg/bg_screen.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_create.h"
#include "menus/digimon/data.h"

/* Frees main screen sprites 6 to 9, those of func_ov006_02298598. */
void func_ov006_02298568(void) {
    freeMainSprite(6);
    freeMainSprite(7);
    freeMainSprite(8);
    freeMainSprite(9);
}

/* Makes sub screen sprites 3 to 11 (0x3B1 to 0x3B7), hidden. */
void func_ov006_02298390(void) {
    createSubSpriteAt(0x3B1, 0x80, 0x38, 2, 0, 3);
    createSubSpriteAt(0x3B2, 0x80, 0x58, 2, 0, 4);
    createSubSpriteAt(0x3B3, 0x80, 0x78, 2, 0, 5);
    createSubSpriteAt(0x3B4, 0x80, 0x88, 2, 0, 6);
    createSubSpriteAt(0x3B5, 0x58, 0xA0, 2, 0, 7);
    createSubSpriteAt(0x3B7, 0xC6, 0x98, 3, 0, 8);
    createSubSpriteAt(0x3B7, 0xB0, 0x98, 3, 0, 9);
    createSubSpriteAt(0x3B7, 0x9A, 0x98, 3, 0, 0xA);
    createSubSpriteAt(0x3B6, 0xDC, 0x98, 3, 0, 0xB);
    addSubSpriteFlags(3, SPRITE_HIDDEN);
    addSubSpriteFlags(4, SPRITE_HIDDEN);
    addSubSpriteFlags(5, SPRITE_HIDDEN);
    addSubSpriteFlags(6, SPRITE_HIDDEN);
    addSubSpriteFlags(7, SPRITE_HIDDEN);
    addSubSpriteFlags(8, SPRITE_HIDDEN);
    addSubSpriteFlags(9, SPRITE_HIDDEN);
    addSubSpriteFlags(0xA, SPRITE_HIDDEN);
    addSubSpriteFlags(0xB, SPRITE_HIDDEN);
}

/* Shows sub screen sprites 3 to 11. */
void func_ov006_02298314(void) {
    clearSubSpriteFlags(3, SPRITE_HIDDEN);
    clearSubSpriteFlags(4, SPRITE_HIDDEN);
    clearSubSpriteFlags(5, SPRITE_HIDDEN);
    clearSubSpriteFlags(6, SPRITE_HIDDEN);
    clearSubSpriteFlags(7, SPRITE_HIDDEN);
    clearSubSpriteFlags(8, SPRITE_HIDDEN);
    clearSubSpriteFlags(9, SPRITE_HIDDEN);
    clearSubSpriteFlags(0xA, SPRITE_HIDDEN);
    clearSubSpriteFlags(0xB, SPRITE_HIDDEN);
}

/* Hides sub screen sprites 3 to 11. */
void func_ov006_02298298(void) {
    addSubSpriteFlags(3, SPRITE_HIDDEN);
    addSubSpriteFlags(4, SPRITE_HIDDEN);
    addSubSpriteFlags(5, SPRITE_HIDDEN);
    addSubSpriteFlags(6, SPRITE_HIDDEN);
    addSubSpriteFlags(7, SPRITE_HIDDEN);
    addSubSpriteFlags(8, SPRITE_HIDDEN);
    addSubSpriteFlags(9, SPRITE_HIDDEN);
    addSubSpriteFlags(0xA, SPRITE_HIDDEN);
    addSubSpriteFlags(0xB, SPRITE_HIDDEN);
}

/* Slides main screen sprites 6 to 9 left, 16 pixels a frame, each once the
 * one before has reached x 0x98; whether all four have. */
u8 func_ov006_02298054(void) {
    u8 arrived;
    u8 done;
    struct Sprite *sprite;

    arrived = 0;
    done    = 0;
    sprite  = getMainSprite(6);
    sprite->x -= 16;
    if (sprite->x <= 0x98) {
        sprite->x = 0x98;
        done |= 1;
    }
    if (done == 1) {
        arrived |= 1;
    }
    if (arrived & 1) {
        done   = 0;
        sprite = getMainSprite(7);
        sprite->x -= 16;
        if (sprite->x <= 0x98) {
            sprite->x = 0x98;
            done |= 1;
        }
        if (done == 1) {
            arrived |= 2;
        }
    }
    if (arrived & 2) {
        done   = 0;
        sprite = getMainSprite(8);
        sprite->x -= 16;
        if (sprite->x <= 0x98) {
            sprite->x = 0x98;
            done |= 1;
        }
        if (done == 1) {
            arrived |= 4;
        }
    }
    if (arrived & 4) {
        done   = 0;
        sprite = getMainSprite(9);
        sprite->x -= 16;
        if (sprite->x <= 0x98) {
            sprite->x = 0x98;
            done |= 1;
        }
        if (done == 1) {
            arrived |= 8;
        }
    }
    return arrived == 0xF;
}

/* Sets slide index to move *value by step each time func_ov006_02297f58 runs
 * it, until it reaches end. */
void func_ov006_0229801c(s32 index, s16 *value, s16 end, s16 step) {
    data_ov006_0229f5d0[index] = value;
    data_ov006_0229f550[index] = end;
    data_ov006_0229f560[index] = step;
}
