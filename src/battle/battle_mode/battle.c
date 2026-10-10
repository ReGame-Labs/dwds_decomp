#include "battle/battle_mode/battle.h"
#include "battle/battle_mode/data.h"
#include "engine/bg/bg_affine.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/system/system.h"
#include "nitro/gx.h"

/* The battle's state. */
struct Battle *getBattle(void) {
    return &data_ov002_0225b488;
}

/* A number below range from the battle's table of random numbers, which both
 * DS of a link battle share. */
u32 getBattleRandom(u32 range) {
    u32 value = BATTLE->randomTable[BATTLE->randomIndex] % range;

    BATTLE->randomIndex++;
    if (BATTLE->randomIndex >= BATTLE_RANDOM_COUNT) {
        BATTLE->randomIndex = 0;
    }
    return value;
}

/* Loads the palette, characters and screen of entry index of data_0213537c. */
void loadBattleBgGraphics(s32 index, struct BgGraphics *gfx) {
    const char **files = func_0204871c(index);

    gfx->paletteFile = loadPaletteFile(&gfx->palette, files[0]);
    gfx->charFile    = loadCharFile(&gfx->chars, files[1]);
    gfx->screenFile  = loadScreenFile(&gfx->screen, files[2]);
}

/* Frees the files that loadBattleBgGraphics loaded. */
void freeBattleBgGraphics(struct BgGraphics *gfx) {
    void *file;

    file = gfx->paletteFile;
    heapFree(file);
    file = gfx->charFile;
    heapFree(file);
    file = gfx->screenFile;
    heapFree(file);
}

/* Sets the display that setBattleDispSelect picked, at the vblank. */
void applyBattleDispSelect(void) {
    GX_SetDispSelect(BATTLE->dispSelect);
}
