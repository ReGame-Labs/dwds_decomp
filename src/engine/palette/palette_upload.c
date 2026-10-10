#include "engine/palette/palette_upload.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/palette/palette_fade.h"
#include "engine/system/system.h"

/* Sets the palettes up: starts the effect task and clears the buffers and the
 * effects. */
s32 initPalettes(void) {
    struct PaletteTask *task;
    s32 i;
    struct PaletteEffect *mainEffect;
    struct PaletteEffect *subEffect;

    task = createTask(runPaletteEffects, 0xF002);
    clearMainPalettes();
    clearSubPalettes();
    task->running = TRUE;
    task->unk20   = 0;
    mainEffect    = MAIN_PALETTE_EFFECTS;
    subEffect     = SUB_PALETTE_EFFECTS;
    for (i = 0; i < PALETTE_EFFECT_COUNT; i++) {
        mainEffect->kind = PALETTE_EFFECT_NONE;
        subEffect->kind  = PALETTE_EFFECT_NONE;
        mainEffect++;
        subEffect++;
    }
    return 0;
}

/* Clears the main screen's palette buffers. */
void clearMainPalettes(void) {
    func_020e22dc(0, MAIN_PALETTE_COLORS, sizeof(MAIN_PALETTE_COLORS));
    func_020e22dc(0, MAIN_PALETTE_TARGET, sizeof(MAIN_PALETTE_TARGET));
    func_020e22dc(0, MAIN_PALETTE_BASE, sizeof(MAIN_PALETTE_BASE));
}

/* Clears the sub screen's palette buffers. */
void clearSubPalettes(void) {
    func_020e22dc(0, SUB_PALETTE_COLORS, sizeof(SUB_PALETTE_COLORS));
    func_020e22dc(0, SUB_PALETTE_TARGET, sizeof(SUB_PALETTE_TARGET));
    func_020e22dc(0, SUB_PALETTE_BASE, sizeof(SUB_PALETTE_BASE));
}

/* Stops the main screen's palettes uploading. */
void lockMainPalettes(void) {
    MAIN_PALETTE_DIRTY |= PALETTE_LOCKED;
}

/* Stops the sub screen's palettes uploading. */
void lockSubPalettes(void) {
    SUB_PALETTE_DIRTY |= PALETTE_LOCKED;
}

/* Lets the main screen's palettes upload again. */
void unlockMainPalettes(void) {
    MAIN_PALETTE_DIRTY &= ~PALETTE_LOCKED;
}

/* Lets the sub screen's palettes upload again. */
void unlockSubPalettes(void) {
    SUB_PALETTE_DIRTY &= ~PALETTE_LOCKED;
}

/* Marks all of the main screen's palettes as changed. */
void markMainPalettesDirty(void) {
    MAIN_PALETTE_DIRTY |= PALETTE_DIRTY_STANDARD | PALETTE_DIRTY_EXTENDED;
}

/* Marks all of the sub screen's palettes as changed. */
void markSubPalettesDirty(void) {
    SUB_PALETTE_DIRTY |= PALETTE_DIRTY_STANDARD | PALETTE_DIRTY_EXTENDED;
}

/* Marks the main screen's palettes as unchanged. */
void clearMainPalettesDirty(void) {
    MAIN_PALETTE_DIRTY &= ~(PALETTE_DIRTY_STANDARD | PALETTE_DIRTY_EXTENDED);
}

/* Marks the sub screen's palettes as unchanged. */
void clearSubPalettesDirty(void) {
    SUB_PALETTE_DIRTY &= ~(PALETTE_DIRTY_STANDARD | PALETTE_DIRTY_EXTENDED);
}

/* Marks the sub screen's BG and OBJ palettes as changed. */
void markSubStandardPalettesDirty(void) {
    SUB_PALETTE_DIRTY |= PALETTE_DIRTY_STANDARD;
}

/* The palette effects' task: steps both screens' effects while it runs. */
void runPaletteEffects(void) {
    s32 running;

    running = ((struct PaletteTask *) getCurrentTask())->running;
    switch (running) { /* irregular */
        case FALSE:
            return;
        case TRUE:
            stepPaletteEffects(MAIN_PALETTES, MAIN_PALETTE_EFFECTS);
            stepPaletteEffects(SUB_PALETTES, SUB_PALETTE_EFFECTS);
            return;
    }
}

/* Steps every running effect of a screen whose wait is over. */
void stepPaletteEffects(struct PaletteSet *palettes, struct PaletteEffect *effects) {
    s32 i;
    struct PaletteEffect *effect;

    for (effect = effects, i = 0; i < PALETTE_EFFECT_COUNT; effect++, i++) {
        if (effect->kind != PALETTE_EFFECT_NONE) {
            if (--effect->wait < 0) {
                effect->wait = effect->interval;
                switch (effect->kind) {
                    case PALETTE_FADE:
                        if (stepPaletteFade(palettes, effect) == 0) {
                            effect->kind = PALETTE_EFFECT_NONE;
                        } else {
                            markPaletteDirty(effect->start, palettes);
                        }
                        break;
                    case PALETTE_BLINK:
                        if (stepPaletteFade(palettes, effect) != 0) {
                            markPaletteDirty(effect->start, palettes);
                        } else {
                            reversePaletteBlink(palettes, effect);
                            if (--effect->times < 1) {
                                effect->kind = PALETTE_EFFECT_NONE;
                            }
                        }
                        break;
                    case PALETTE_BLINK_FOREVER:
                        if (stepPaletteFade(palettes, effect) != 0) {
                            markPaletteDirty(effect->start, palettes);
                        } else {
                            reversePaletteBlink(palettes, effect);
                        }
                        break;
                    case PALETTE_EFFECT_2:
                        func_02083cd0(palettes, effect);
                        if (--effect->times < 1) {
                            effect->kind = PALETTE_EFFECT_NONE;
                        }
                        break;
                    case PALETTE_EFFECT_4:
                        func_02083c0c(palettes, effect);
                        if (--effect->times < 1) {
                            effect->kind = PALETTE_EFFECT_NONE;
                        }
                        break;
                    case PALETTE_EFFECT_3:
                        func_02083cd0(palettes, effect);
                        break;
                    case PALETTE_EFFECT_5:
                        func_02083c0c(palettes, effect);
                        break;
                    case PALETTE_EFFECT_8:
                        func_02083cd0(palettes, effect);
                        if (++effect->stepG >= effect->stepB) {
                            effect->kind  = PALETTE_EFFECT_10;
                            effect->stepG = 0;
                            if (--effect->times < 1) {
                                effect->kind = PALETTE_EFFECT_NONE;
                            }
                        }
                        break;
                    case PALETTE_EFFECT_10:
                        func_02083c0c(palettes, effect);
                        if (++effect->stepG >= effect->stepB) {
                            effect->kind  = PALETTE_EFFECT_8;
                            effect->stepG = 0;
                            if (--effect->times < 1) {
                                effect->kind = PALETTE_EFFECT_NONE;
                            }
                        }
                        break;
                    case PALETTE_EFFECT_9:
                        func_02083cd0(palettes, effect);
                        if (++effect->stepG >= effect->stepB) {
                            effect->kind  = PALETTE_EFFECT_11;
                            effect->stepG = 0;
                        }
                        break;
                    case PALETTE_EFFECT_11:
                        func_02083c0c(palettes, effect);
                        if (++effect->stepG >= effect->stepB) {
                            effect->kind  = PALETTE_EFFECT_9;
                            effect->stepG = 0;
                        }
                        break;
                }
            }
        }
    }
}

/* Sends the palettes that changed to VRAM, at VBlank. The extended BG
 * palettes go to all four slots. */
void uploadPalettes(void) {
    if (!(MAIN_PALETTE_DIRTY & PALETTE_LOCKED)) {
        if (MAIN_PALETTE_DIRTY & PALETTE_DIRTY_STANDARD) {
            func_020e4f58(&MAIN_PALETTE_COLORS[PALETTE_BG], 0x200);
            func_020dc7c4(&MAIN_PALETTE_COLORS[PALETTE_BG], 0, 0x200);
            func_020e4f58(&MAIN_PALETTE_COLORS[PALETTE_OBJ], 0x200);
            func_020dc6f4(&MAIN_PALETTE_COLORS[PALETTE_OBJ], 0, 0x200);
        }
        if (MAIN_PALETTE_DIRTY & PALETTE_DIRTY_EXTENDED) {
            if (func_020da214() != 0) {
                func_020dbd84();
                func_020dbd04(&MAIN_PALETTE_COLORS[PALETTE_BG_EXT], 0, 0x1000);
                func_020dbd04(&MAIN_PALETTE_COLORS[PALETTE_BG_EXT], 0x2000, 0x1000);
                func_020dbd04(&MAIN_PALETTE_COLORS[PALETTE_BG_EXT], 0x4000, 0x1000);
                func_020dbd04(&MAIN_PALETTE_COLORS[PALETTE_BG_EXT], 0x6000, 0x1000);
                func_020dbca0();
            }
            if (func_020da204() != 0) {
                func_020dbc30();
                func_020dbbbc(&MAIN_PALETTE_COLORS[PALETTE_OBJ_EXT], 0, 0x1000);
                func_020dbb64();
            }
        }
        MAIN_PALETTE_DIRTY &= ~(PALETTE_DIRTY_STANDARD | PALETTE_DIRTY_EXTENDED);
    }
    if (SUB_PALETTE_DIRTY & PALETTE_LOCKED) {
        return;
    }
    if (SUB_PALETTE_DIRTY & PALETTE_DIRTY_STANDARD) {
        func_020e4f58(&SUB_PALETTE_COLORS[PALETTE_BG], 0x200);
        func_020dc75c(&SUB_PALETTE_COLORS[PALETTE_BG], 0, 0x200);
        func_020e4f58(&SUB_PALETTE_COLORS[PALETTE_OBJ], 0x200);
        func_020dc68c(&SUB_PALETTE_COLORS[PALETTE_OBJ], 0, 0x200);
    }
    if (SUB_PALETTE_DIRTY & PALETTE_DIRTY_EXTENDED) {
        if (func_020da1f4() != 0) {
            func_020dbb40();
            func_020dbacc(&SUB_PALETTE_COLORS[PALETTE_BG_EXT], 0, 0x1000);
            func_020dbacc(&SUB_PALETTE_COLORS[PALETTE_BG_EXT], 0x2000, 0x1000);
            func_020dbacc(&SUB_PALETTE_COLORS[PALETTE_BG_EXT], 0x4000, 0x1000);
            func_020dbacc(&SUB_PALETTE_COLORS[PALETTE_BG_EXT], 0x6000, 0x1000);
            func_020dba80();
        }
        if (func_020da1e4() != 0) {
            func_020dba5c();
            func_020db9e8(&SUB_PALETTE_COLORS[PALETTE_OBJ_EXT], 0, 0x1000);
            func_020db99c();
        }
    }
    SUB_PALETTE_DIRTY &= ~(PALETTE_DIRTY_STANDARD | PALETTE_DIRTY_EXTENDED);
}
