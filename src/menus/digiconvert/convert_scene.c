#include "menus/digiconvert/convert_scene.h"
#include "battle/characters/chr.h"
#include "engine/bg/bg_affine.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/movie/movie_player.h"
#include "engine/palette/palette_buffers.h"
#include "engine/save/game_state.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/window/window.h"
#include "menus/digiconvert/convert_captions.h"
#include "menus/widgets/digimon_detail.h"
#include "menus/widgets/status_window.h"
#include "menus/widgets/window_anim.h"

/* The end of the conversion scene's task. */
void endConvertTask(void) {
    CONVERT_TASK_ID = -1;
    CONVERT_TASK    = NULL;
}

/* Tears the conversion scene down: its sprites, ov001's characters, the
 * movie, its windows, text slots and background. */
void closeConvert(struct ConvertTask *task) {
    void *work;

    stopSubPaletteEffectsButFades(task->unk4C);
    removeAllMainBattleChrs();
    endBattleChrs();
    freeMainSprites();
    freeSubSprites();
    freeCaptionText();
    stopMovie();
    closeConvertStatus();
    if (task->windows[0] != 0xFF) {
        closeWindow(task->windows[0]);
        task->windows[0] = 0xFF;
    }
    if (task->windows[1] != 0xFF) {
        closeWindow(task->windows[1]);
        task->windows[1] = 0xFF;
    }
    if (task->windows[2] != 0xFF) {
        closeWindow(task->windows[2]);
        task->windows[2] = 0xFF;
    }
    freeSubWindowFrame();
    freeConvertText();
    freeConvertBg(task);
    work = task->work;
    heapFree(work);
}

/* Loads the scene's background, the table's 0xF ("m_bg02"). */
void loadConvertBg(struct ConvertTask *task) {
    const char **paths;

    paths                      = func_0204871c(0xF);
    task->work->bg.paletteFile = loadPaletteFile(&task->work->bg.palette, paths[0]);
    task->work->bg.charFile    = loadCharFile(&task->work->bg.chars, paths[1]);
    task->work->bg.screenFile  = loadScreenFile(&task->work->bg.screen, paths[2]);
}

/* Frees the scene's background, as freeBgGraphics does. */
void freeConvertBg(struct ConvertTask *task) {
    void *file;

    file = task->work->bg.paletteFile;
    if (file != NULL) {
        heapFree(file);
        task->work->bg.paletteFile = NULL;
    }
    file = task->work->bg.charFile;
    if (file != NULL) {
        heapFree(file);
        task->work->bg.charFile = NULL;
    }
    file = task->work->bg.screenFile;
    if (file == NULL) {
        return;
    }
    heapFree(file);
    task->work->bg.screenFile = NULL;
}

/* Loads the sub screen's window frame, the "m_win" background. */
void loadSubWindowFrame(void) {
    loadSubWindowFrameInSlot(0, 2);
}

/* Unloads it. */
void freeSubWindowFrame(void) {
    unloadSubWindowFrame();
}

/* Sets up the main screen's text slots 1, 2, 4 and 5. */
void initConvertText(void) {
    func_020a9ae0(2, 1, 0xE);
    func_020a9ae0(1, 2, 0xE);
    func_020a9ae0(4, 3, 0xE);
    func_020a9ae0(5, 4, 0xE);
}

/* Frees them. */
void freeConvertText(void) {
    func_020a9844(1);
    func_020a9844(2);
    func_020a9844(4);
    func_020a9844(5);
}

/* Closes the status displays the scene opened. */
void closeConvertStatus(void) {
    freeDigimonDetailSprites(0);
    func_02059c50(0);
    freeStatusWindowSprites(0);
    func_020587fc(0);
}

/* Clears a species' scan percentage, bits 20-29 of its state. */
void clearScanPercent(s32 species) {
    s32 *state;

    state = func_020a0470(species);
    *state &= 0xC00FFFFF;
}
