#include "engine/bg/bg_affine.h"
#include "engine/data.h"
#include "engine/gfx/gfx_files.h"
#include "engine/libs.h"
#include "engine/system/display.h"
#include "engine/system/display_modes.h"
#include "engine/system/system.h"
#include "menus/digiconvert/convert_captions.h"
#include "menus/digimon/menu_digivolve.h"

/* Starts the two tasks that hand the affine parameters to the hardware at the
 * next VBlank, and resets them and the dials. */
void initBgAffine(void) {
    s32 i;

    ((struct Task *) createTask(tickMainBgAffine, BG_AFFINE_TASK_PRIORITY))->onEnd = NULL;
    ((struct Task *) createTask(tickSubBgAffine, BG_AFFINE_TASK_PRIORITY))->onEnd  = NULL;
    for (i = 0; i < BG_AFFINE_COUNT; i++) {
        MAIN_BG_AFFINE_CHANGED[i] = FALSE;
        SUB_BG_AFFINE_CHANGED[i]  = FALSE;
        CLEAR(&MAIN_BG_AFFINE[i], sizeof(struct BgAffine));
        CLEAR(&SUB_BG_AFFINE[i], sizeof(struct BgAffine));
    }
    initDials();
}

/* Whether the main screen's mode makes BG2 an affine background (modes 2, 4
 * and 5). */
s32 isMainBg2Affine(void) {
    struct {
        u32 bgMode : 3;
        u32 rest : 29;
    } dispcnt;
    u32 raw;

    raw     = *(vu32 *) REG_DISPCNT_ADDR;
    dispcnt = *(typeof(dispcnt) *) &raw;
    if (dispcnt.bgMode == 2 || dispcnt.bgMode == 4 || dispcnt.bgMode == 5) {
        return 1;
    }
    return 0;
}

/* Whether the main screen's mode makes BG3 an affine background (modes 1 to
 * 5). */
s32 isMainBg3Affine(void) {
    struct DispCnt {
        u32 bgMode : 3;
        u32 rest : 29;
    } dispcnt, temp;

    temp    = *(volatile struct DispCnt *) REG_DISPCNT_ADDR;
    dispcnt = temp;
    if (dispcnt.bgMode - 1 <= 4U) {
        return 1;
    }
    return 0;
}

/* The same for the sub screen's BG2. */
s32 isSubBg2Affine(void) {
    struct {
        u32 bgMode : 3;
        u32 rest : 29;
    } dispcnt;
    u32 raw;

    raw     = *(vu32 *) REG_DB_DISPCNT_ADDR;
    dispcnt = *(typeof(dispcnt) *) &raw;
    if (dispcnt.bgMode == 2 || dispcnt.bgMode == 4 || dispcnt.bgMode == 5) {
        return 1;
    }
    return 0;
}

/* The same for the sub screen's BG3. */
s32 isSubBg3Affine(void) {
    struct DispCnt {
        u32 bgMode : 3;
        u32 rest : 29;
    } dispcnt, temp;

    temp    = *(volatile struct DispCnt *) REG_DB_DISPCNT_ADDR;
    dispcnt = temp;
    if (dispcnt.bgMode - 1 <= 4U) {
        return 1;
    }
    return 0;
}

/* The VBlank callback: writes the main screen's changed affine parameters.
 * The 8.8 matrix becomes the hardware's 20.12. */
void flushMainBgAffine(void) {
    s32 matrix[4];

    if (MAIN_BG_AFFINE_CHANGED[0] != FALSE) {
        MAIN_BG_AFFINE_CHANGED[0] = FALSE;
        matrix[0]                 = MAIN_BG_AFFINE[0].matrix[0] * 0x10;
        matrix[1]                 = MAIN_BG_AFFINE[0].matrix[1] * 0x10;
        matrix[2]                 = MAIN_BG_AFFINE[0].matrix[2] * 0x10;
        matrix[3]                 = MAIN_BG_AFFINE[0].matrix[3] * 0x10;
        func_020db8e8(REG_BG2PA_ADDR, matrix, MAIN_BG_AFFINE[0].centerX, MAIN_BG_AFFINE[0].centerY, MAIN_BG_AFFINE[0].x,
                      MAIN_BG_AFFINE[0].y);
    }
    if (MAIN_BG_AFFINE_CHANGED[1] != FALSE) {
        MAIN_BG_AFFINE_CHANGED[1] = FALSE;
        matrix[0]                 = MAIN_BG_AFFINE[1].matrix[0] * 0x10;
        matrix[1]                 = MAIN_BG_AFFINE[1].matrix[1] * 0x10;
        matrix[2]                 = MAIN_BG_AFFINE[1].matrix[2] * 0x10;
        matrix[3]                 = MAIN_BG_AFFINE[1].matrix[3] * 0x10;
        func_020db8e8(REG_BG3PA_ADDR, matrix, MAIN_BG_AFFINE[1].centerX, MAIN_BG_AFFINE[1].centerY, MAIN_BG_AFFINE[1].x,
                      MAIN_BG_AFFINE[1].y);
    }
}

/* The main screen's affine task: queues flushMainBgAffine for the next VBlank. */
void tickMainBgAffine(void) {
    addVBlankCallback(&flushMainBgAffine);
}

/* The VBlank callback of the sub screen. Its BG2 parameters go to the BG3
 * registers too, as the original does. */
void flushSubBgAffine(void) {
    s32 matrix[4];

    if (SUB_BG_AFFINE_CHANGED[0] != FALSE) {
        SUB_BG_AFFINE_CHANGED[0] = FALSE;
        matrix[0]                = SUB_BG_AFFINE[0].matrix[0] * 0x10;
        matrix[1]                = SUB_BG_AFFINE[0].matrix[1] * 0x10;
        matrix[2]                = SUB_BG_AFFINE[0].matrix[2] * 0x10;
        matrix[3]                = SUB_BG_AFFINE[0].matrix[3] * 0x10;
        func_020db8e8(REG_DB_BG3PA_ADDR, matrix, SUB_BG_AFFINE[0].centerX, SUB_BG_AFFINE[0].centerY, SUB_BG_AFFINE[0].x,
                      SUB_BG_AFFINE[0].y);
    }
    if (SUB_BG_AFFINE_CHANGED[1] != FALSE) {
        SUB_BG_AFFINE_CHANGED[1] = FALSE;
        matrix[0]                = SUB_BG_AFFINE[1].matrix[0] * 0x10;
        matrix[1]                = SUB_BG_AFFINE[1].matrix[1] * 0x10;
        matrix[2]                = SUB_BG_AFFINE[1].matrix[2] * 0x10;
        matrix[3]                = SUB_BG_AFFINE[1].matrix[3] * 0x10;
        func_020db8e8(REG_DB_BG3PA_ADDR, matrix, SUB_BG_AFFINE[1].centerX, SUB_BG_AFFINE[1].centerY, SUB_BG_AFFINE[1].x,
                      SUB_BG_AFFINE[1].y);
    }
}

/* The sub screen's affine task: queues flushSubBgAffine for the next VBlank. */
void tickSubBgAffine(void) {
    addVBlankCallback(&flushSubBgAffine);
}

/* Scrolls the main screen's BG3 to (x, y). */
void scrollMainBg3(s32 x, s32 y) {
    MAIN_BG_AFFINE_CHANGED[1] = TRUE;
    MAIN_BG_AFFINE[1].x       = (s32) (0 - x);
    MAIN_BG_AFFINE[1].y       = (s32) (0 - y);
}

/* Scrolls the sub screen's BG3 to (x, y). */
void scrollSubBg3(s32 x, s32 y) {
    SUB_BG_AFFINE_CHANGED[1] = TRUE;
    SUB_BG_AFFINE[1].x       = x;
    SUB_BG_AFFINE[1].y       = y;
}

/* Sets the center of the main screen's BG3's rotation. */
void setMainBg3Center(s32 x, s32 y) {
    MAIN_BG_AFFINE_CHANGED[1] = TRUE;
    MAIN_BG_AFFINE[1].centerX = x;
    MAIN_BG_AFFINE[1].centerY = y;
}

/* Sets the center of the sub screen's BG3's rotation. */
void setSubBg3Center(s32 x, s32 y) {
    SUB_BG_AFFINE_CHANGED[1] = TRUE;
    SUB_BG_AFFINE[1].centerX = x;
    SUB_BG_AFFINE[1].centerY = y;
}

/* Rotates the main screen's BG3 by an angle (256 to a turn). */
void rotateMainBg3(s32 angle) {
    MAIN_BG_AFFINE_CHANGED[1]   = TRUE;
    MAIN_BG_AFFINE[1].matrix[3] = COSINE_TABLE[angle];
    MAIN_BG_AFFINE[1].matrix[0] = MAIN_BG_AFFINE[1].matrix[3];
    MAIN_BG_AFFINE[1].matrix[2] = SINE_TABLE[angle];
    MAIN_BG_AFFINE[1].matrix[1] = -SINE_TABLE[angle];
}

/* Rotates the sub screen's BG3 by an angle and scales it by divisor (in 8.8,
 * 0x100 for none). */
void rotateSubBg3(s32 divisor, s32 angle) {
    SUB_BG_AFFINE_CHANGED[1]   = TRUE;
    SUB_BG_AFFINE[1].matrix[3] = (COSINE_TABLE[angle] << 8) / divisor;
    SUB_BG_AFFINE[1].matrix[0] = SUB_BG_AFFINE[1].matrix[3];
    SUB_BG_AFFINE[1].matrix[1] = (SINE_TABLE[angle] << 8) / divisor;
    SUB_BG_AFFINE[1].matrix[2] = -SUB_BG_AFFINE[1].matrix[1];
}

/* The end of the scene's task. */
void endMenuDigivolveTask(void) {
    MENU_DIGIVOLVE_TASK_ID = -1;
    MENU_DIGIVOLVE_TASK    = NULL;
}

/* Starts the digivolution of a species into a target species, from the
 * Digimon menu (ov006). The target's stage picks unk26. */
void startMenuDigivolveTask(s32 species, s32 target) {
    struct MenuDigivolveTask *task;

    if (MENU_DIGIVOLVE_TASK != NULL) {
        return;
    }
    initCaptions();
    task                   = createTask(&tickMenuDigivolve, MENU_DIGIVOLVE_TASK_PRIORITY);
    MENU_DIGIVOLVE_TASK_ID = getTaskId(task);
    MENU_DIGIVOLVE_TASK    = task;
    task->unk1C            = 0;
    task->unk1E            = 0;
    task->unk20            = 0;
    task->unk22            = 0;
    task->unk24            = 1;
    task->species          = species;
    task->target           = target;
    task->unk28            = func_020a31d8(species);
    task->unk2C            = func_020a31d8(target);
    switch ((u32) getSpeciesStage(target)) {
        default:
            break;
        case 0:
            task->unk26 = 4;
            break;
        case 1:
            task->unk26 = 0;
            break;
        case 2:
            task->unk26 = 1;
            break;
        case 3:
        case 5:
            task->unk26 = 2;
            break;
        case 4:
            task->unk26 = 3;
            break;
    }
    task->unk50      = 0;
    task->task.onEnd = endMenuDigivolveTask;
}

/* The same, with unk50 set. */
void func_02048034(s32 species, s32 target) {
    struct MenuDigivolveTask *task;

    if (MENU_DIGIVOLVE_TASK != NULL) {
        return;
    }
    initCaptions();
    task                   = createTask(&tickMenuDigivolve, MENU_DIGIVOLVE_TASK_PRIORITY);
    MENU_DIGIVOLVE_TASK_ID = getTaskId(task);
    MENU_DIGIVOLVE_TASK    = task;
    task->unk1C            = 0;
    task->unk1E            = 0;
    task->unk20            = 0;
    task->unk22            = 0;
    task->unk24            = 1;
    task->species          = species;
    task->target           = target;
    task->unk28            = func_020a31d8(species);
    task->unk2C            = func_020a31d8(target);
    switch ((u32) getSpeciesStage(target)) {
        default:
            break;
        case 0:
            task->unk26 = 4;
            break;
        case 1:
            task->unk26 = 0;
            break;
        case 2:
            task->unk26 = 1;
            break;
        case 3:
        case 5:
            task->unk26 = 2;
            break;
        case 4:
            task->unk26 = 3;
            break;
    }
    task->unk50      = 1;
    task->task.onEnd = endMenuDigivolveTask;
}

/* Starts the scene from the Digimon menu (ov006). */
void startMenuDigivolve(s32 species, s32 target) {
    startMenuDigivolveTask(species, target);
}

/* Starts the scene from the Digimon menu (ov006), with unk50 set. */
void func_0204801c(s32 species, s32 target) {
    func_02048034(species, target);
}
