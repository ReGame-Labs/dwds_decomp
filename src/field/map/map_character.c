#include "field/map/map_character.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/system/system.h"
#include "field/map/data.h"
#include "field/map/map_sprite.h"
#include "field/map/map_sprite_draw.h"

/* Stops the main screen's map scrolling where it is. */
void stopMainMapScroll(void) {
    MAIN_MAP_STATE.targetX.value      = 0;
    MAIN_MAP_STATE.targetY.value      = 0;
    MAIN_MAP_STATE.targetX.part.whole = MAIN_MAP_STATE.x.part.whole;
    MAIN_MAP_STATE.targetY.part.whole = MAIN_MAP_STATE.y.part.whole;
    MAIN_MAP_STATE.distanceX          = 0;
    MAIN_MAP_STATE.distanceY          = 0;
    MAIN_MAP_STATE.stepX              = 0;
    MAIN_MAP_STATE.stepY              = 0;
    MAIN_MAP_STATE.directionX         = 0;
    MAIN_MAP_STATE.directionY         = 0;
}

/* Whether the main screen's map has stopped scrolling. */
BOOL isMainMapScrollDone(void) {
    if (MAIN_MAP_STATE.distanceX == 0 && MAIN_MAP_STATE.distanceY == 0) {
        return TRUE;
    }
    return FALSE;
}

/* Whether the sub screen's map has stopped scrolling. */
BOOL isSubMapScrollDone(void) {
    if (SUB_MAP_STATE.distanceX == 0 && SUB_MAP_STATE.distanceY == 0) {
        return TRUE;
    }
    return FALSE;
}

/* Clears both screens' map sprites, and the record of their graphics' VRAM. */
void initMapSprites(void) {
    s32 i;

    CLEAR(MAIN_MAP_SPRITES, sizeof(MAIN_MAP_SPRITES));
    for (i = 0; i < MAP_SPRITE_COUNT; i++) {
        MAIN_MAP_SPRITE_ORDER[i] = &MAIN_MAP_SPRITES[i];
    }
    func_02030f18(MAIN_MAP_SPRITES_ENDING, 0, sizeof(MAIN_MAP_SPRITES_ENDING));
    CLEAR(SUB_MAP_SPRITES, sizeof(SUB_MAP_SPRITES));
    for (i = 0; i < MAP_SPRITE_COUNT; i++) {
        SUB_MAP_SPRITE_ORDER[i] = &SUB_MAP_SPRITES[i];
    }
    func_02030f18(SUB_MAP_SPRITES_ENDING, 0, sizeof(SUB_MAP_SPRITES_ENDING));
    func_02030f18(MAIN_MAP_CHARACTER_VRAM, 0xFF, sizeof(MAIN_MAP_CHARACTER_VRAM));
    func_02030f18(SUB_MAP_CHARACTER_VRAM, 0xFF, sizeof(SUB_MAP_CHARACTER_VRAM));
    MAIN_MAP_SPRITE_TASK_ID   = -1;
    SUB_MAP_SPRITE_TASK_ID    = -1;
    MAIN_MAP_SPRITE_VRAM_USED = 0;
    SUB_MAP_SPRITE_VRAM_USED  = 0;
    MAIN_MAP_SPRITE_VRAM_BASE = -1;
    SUB_MAP_SPRITE_VRAM_BASE  = -1;
    MAIN_MAP_SPRITE_VRAM_SIZE = 0x80;
    SUB_MAP_SPRITE_VRAM_SIZE  = 0x80;
}

/* Starts the main screen's map sprites: the task that draws them, and the part
 * of the screen's sprite VRAM their graphics go to. */
void startMainMapSpriteTask(void) {
    struct Task *task = createTask(tickMainMapSprites, 0x11E);

    MAIN_MAP_SPRITE_TASK_ID   = getTaskId(task);
    task->onEnd               = NULL;
    MAIN_MAP_SPRITE_VRAM_BASE = allocMainVram(4, MAIN_MAP_SPRITE_VRAM_SIZE);
}

/* The same for the sub screen. */
void startSubMapSpriteTask(void) {
    struct Task *task = createTask(tickSubMapSprites, 0x11E);

    SUB_MAP_SPRITE_TASK_ID   = getTaskId(task);
    task->onEnd              = NULL;
    SUB_MAP_SPRITE_VRAM_BASE = allocSubVram(4, SUB_MAP_SPRITE_VRAM_SIZE);
}

/* Stops the main screen's map sprites' task and gives their VRAM back. */
void stopMainMapSpriteTask(void) {
    if (MAIN_MAP_SPRITE_TASK_ID == -1) {
        return;
    }
    endTaskById(MAIN_MAP_SPRITE_TASK_ID);
    MAIN_MAP_SPRITE_TASK_ID = -1;
    func_0208577c(4, (u16) MAIN_MAP_SPRITE_VRAM_BASE);
}

/* The same for the sub screen. */
void stopSubMapSpriteTask(void) {
    if (SUB_MAP_SPRITE_TASK_ID == -1) {
        return;
    }
    endTaskById(SUB_MAP_SPRITE_TASK_ID);
    SUB_MAP_SPRITE_TASK_ID = -1;
    func_02085710(4, (u16) SUB_MAP_SPRITE_VRAM_BASE);
}

/* Loads a map character for the sub screen's sprites: its graphics, into
 * VRAM, its animation and its palette. */
void loadSubMapCharacter(u16 character, s32 slot) {
    s32 palette = slot + 0x30;

    func_ov000_021fa780(character, palette);
    loadMapCharacterAnim(character);
    func_ov000_021fa628(character, palette);
}

/* Drops a map character's files and, once no sprite uses its graphics, their
 * VRAM on the main screen. */
void releaseMainMapCharacter(s32 character) {
    u16 graphics;
    u16 block;

    func_ov000_021fa444(character);
    graphics = data_02107f34[character].graphics;
    if (data_021ea308[graphics] != 0) {
        return;
    }
    block = MAIN_MAP_CHARACTER_VRAM[graphics];
    if (block == 0xFFFF) {
        return;
    }
    freeMainMapSpriteVram(block);
    MAIN_MAP_CHARACTER_VRAM[graphics] = 0xFFFF;
}

/* The same on the sub screen. */
void releaseSubMapCharacter(s32 character) {
    u16 graphics;
    u16 block;

    func_ov000_021fa444(character);
    graphics = data_02107f34[character].graphics;
    if (data_021ea308[graphics] != 0) {
        return;
    }
    block = SUB_MAP_CHARACTER_VRAM[graphics];
    if (block == 0xFFFF) {
        return;
    }
    freeSubMapSpriteVram(block);
    SUB_MAP_CHARACTER_VRAM[graphics] = 0xFFFF;
}
