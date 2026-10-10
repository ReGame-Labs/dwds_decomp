#include "field/map/ov000_021fbb2c.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/palette/palette_fade.h"
#include "engine/script/interpreter.h"
#include "engine/ui/gauge.h"
#include "field/actors/actor_commands.h"
#include "field/actors/actor_tasks.h"
#include "field/event_scripts/data.h"
#include "field/map/map.h"
#include "field/map/map_character.h"
#include "field/map/map_files.h"
#include "m2c_macros.h"
#include "nitro/gx.h"

/* Frees the main screen map's eight slots of data_021ab808 (from
 * func_02083ea8) and marks them empty. */
void func_ov000_021fbec0(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (data_021ab808[i] != -1) {
            stopMainPaletteEffectsButFades(data_021ab808[i]);
            data_021ab808[i] = -1;
        }
    }
}

/* The same for the sub screen's, data_021ab848 (from func_02083e78). */
void func_ov000_021fbe88(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (data_021ab848[i] != -1) {
            stopSubPaletteEffectsButFades(data_021ab848[i]);
            data_021ab848[i] = -1;
        }
    }
}

/* Stops the main screen's map: its sprites' task and its own task. */
void stopMainMap(void) {
    endMainActorTask();
    stopMainMapSpriteTask();
    stopMainMapTask();
}

/* Stops the sub screen's map: its sprites' task and its own task. */
void stopSubMap(void) {
    endSubActorTask();
    stopSubMapSpriteTask();
    stopSubMapTask();
}

/* Keeps an event script's offset (a script command's argument) at 0xD0 of
 * data_021e0bf8, for func_ov000_021fbd40. */
void func_ov000_021fbe30(s32 offset) {
    M2C_FIELD(&data_021e0bf8, s16 *, 0xD0) = findEventScript(offset);
}

/* Starts the sub screen's map anew from the copy of its state in
 * data_021e31f8, the task id aside, with its sprites, its colour and its
 * rectangles. */
void restoreSubMap(void) {
    /* The copy is a block of the save data, data_021e0cc8 + 0x2530. */
    struct MapState *saved = (struct MapState *) data_021e31f8;
    s32 taskId;

    REG_POWCNT1 |= REG_POWCNT1_DSEL_MASK; /* the main screen on the top LCD */
    startSubMap();
    startSubActorTask();
    startSubMapSpriteTask();
    loadSubMap(saved->id, 0, 0);
    taskId = SUB_MAP_STATE.taskId;
    loadSubPalette(0x4000, 1, (s32) &saved->color);
    func_02030f78(&SUB_MAP_STATE, saved, sizeof(struct MapState));
    SUB_MAP_STATE.taskId = taskId;
    restoreSubMapRects();
    func_020c26f8();
    func_020c26b8();
}

/* Restores the sub screen's map and sends the script thread to the event
 * script kept by func_ov000_021fbe30. */
void func_ov000_021fbd40(struct ScriptThread *thread) {
    s32 offset;

    restoreSubMap();
    offset     = getEventScriptOffset(M2C_FIELD(&data_021e0bf8, u16 *, 0xD0));
    thread->pc = (u16 *) (offset + (s32) EVENT_SCRIPTS);
}

/* Clears event flag 0x3E9. */
void func_ov000_021fbd2c(void) {
    clearGameFlag(0x3E9);
}

/* Sets one of the 16 values at 0x50 of the main screen's map state. */
void func_ov000_021fbd14(s32 index, s16 value) {
    if (index < 0x10) {
        MAIN_MAP_STATE.unk50[index] = value;
    }
}

/* The same for the sub screen's. */
void func_ov000_021fbcfc(s32 index, s16 value) {
    if (index < 0x10) {
        SUB_MAP_STATE.unk50[index] = value;
    }
}
