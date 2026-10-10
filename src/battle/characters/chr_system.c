#include "battle/characters/chr_system.h"
#include "battle/characters/chr_draw.h"
#include "battle/characters/data.h"
#include "engine/bg/bg_layers.h"
#include "engine/bg/bg_screen.h"
#include "engine/system/setup.h"
#include "engine/system/system.h"

/* The palette a main screen effect's colours were loaded to, 0xFFFF before. */
u16 getMainBgEffectPalette(s32 effect) {
    return MAIN_BG_EFFECT_PALETTES[effect];
}

/* The palette a sub screen effect's colours were loaded to, 0xFFFF before. */
u16 getSubBgEffectPalette(s32 effect) {
    return SUB_BG_EFFECT_PALETTES[effect];
}

/* Asks a main screen effect in use to end; its task ends it. */
void requestEndMainBgEffect(u32 slot) {
    struct BgEffect *effect;

    if (slot >= BG_EFFECT_COUNT) {
        return;
    }
    effect = &MAIN_BG_EFFECTS[slot];
    if (effect->flags & EFFECT_IN_USE) {
        effect->flags |= EFFECT_ENDING;
    }
}

/* Asks a sub screen effect in use to end; its task ends it. */
void requestEndSubBgEffect(u32 slot) {
    struct BgEffect *effect;

    if (slot >= BG_EFFECT_COUNT) {
        return;
    }
    effect = &SUB_BG_EFFECTS[slot];
    if (effect->flags & EFFECT_IN_USE) {
        effect->flags |= EFFECT_ENDING;
    }
}

/* Ends all the main screen's effects. */
void endAllMainBgEffects(void) {
    s32 slot;

    slot = 0;
    do {
        endMainBgEffect(slot);
        slot++;
    } while (slot < BG_EFFECT_COUNT);
}

/* Ends all the sub screen's effects. */
void endAllSubBgEffects(void) {
    s32 slot;

    slot = 0;
    do {
        endSubBgEffect(slot);
        slot++;
    } while (slot < BG_EFFECT_COUNT);
}

/* The main screen effects task's end: ends its effects and clears the flag 6
 * that initBgEffects sets. */
void freeMainBgEffects(void) {
    endAllMainBgEffects();
    clearSystemSetUp(6);
}

/* The sub screen effects task's end: ends its effects and clears the flag 6
 * that initBgEffects sets. */
void freeSubBgEffects(void) {
    endAllSubBgEffects();
    clearSystemSetUp(6);
}

/* Whether a main screen effect is over; BG_EFFECT_COUNT stands for no effect. */
u8 isMainBgEffectDone(s32 slot) {
    if (slot == BG_EFFECT_COUNT) {
        return 1;
    }
    return !(MAIN_BG_EFFECTS[slot].flags & EFFECT_IN_USE);
}

/* Whether a sub screen effect is over; BG_EFFECT_COUNT stands for no effect. */
u8 isSubBgEffectDone(s32 slot) {
    if (slot == BG_EFFECT_COUNT) {
        return 1;
    }
    return !(SUB_BG_EFFECTS[slot].flags & EFFECT_IN_USE);
}

/* Sets the offset, in tiles, by which the main screen's effects and list
 * sprites are drawn. */
void setEffectTileOffset(s16 x, s16 y) {
    EFFECT_TILE_OFFSET_X = x;
    EFFECT_TILE_OFFSET_Y = y;
}

/* Draws the main screen's effects and list sprites at the tile offset. */
void enableEffectTileOffset(void) {
    EFFECT_TILE_OFFSET_OFF = 0;
}

/* Draws the main screen's effects and list sprites without the tile offset. */
void disableEffectTileOffset(void) {
    EFFECT_TILE_OFFSET_OFF = 1;
}

/* Starts the main screen's characters: clears the state of both screens,
 * starts the draw task, reserves sprite VRAM (BATTLE_CHR_POOL_TILES for a size
 * of 0) and creates the sprites 0x80 to 0x82. */
void initMainBattleChrs(s32 size) {
    struct Task *task;

    clearBattleChrState();
    task        = createTask(tickMainBattleChrs, BATTLE_CHR_TASK_PRIORITY);
    task->onEnd = NULL;
    if (size == 0) {
        MAIN_BATTLE_CHR_VRAM = allocMainVram(4, BATTLE_CHR_POOL_TILES);
    } else {
        MAIN_BATTLE_CHR_VRAM = allocMainVram(4, size);
    }
    createMainSpriteAt(0, 0x130, 0xC0, 0xF, 0, 0x80);
    createMainSpriteAt(1, 0x130, 0xC0, 0xF, 0, 0x81);
    createMainSpriteAt(2, 0x130, 0xC0, 0xF, 0, 0x82);
}

/* The same for the sub screen's characters. */
void initSubBattleChrs(s32 size) {
    struct Task *task;

    clearBattleChrState();
    task        = createTask(tickSubBattleChrs, BATTLE_CHR_TASK_PRIORITY);
    task->onEnd = NULL;
    if (size == 0) {
        SUB_BATTLE_CHR_VRAM = allocSubVram(4, BATTLE_CHR_POOL_TILES);
    } else {
        SUB_BATTLE_CHR_VRAM = allocSubVram(4, size);
    }
    createSubSpriteAt(0, 0x130, 0xC0, 0xF, 0, 0x80);
    createSubSpriteAt(1, 0x130, 0xC0, 0xF, 0, 0x81);
    createSubSpriteAt(2, 0x130, 0xC0, 0xF, 0, 0x82);
}
