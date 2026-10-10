#include "battle/characters/fade_sprite_slot.h"
#include "battle/characters/chr_system.h"
#include "battle/characters/data.h"
#include "engine/palette/palette_fade.h"
#include "engine/palette/palette_upload.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_create.h"
#include "engine/sprite/sprite_draw.h"
#include "engine/system/system.h"

/* Whether no move script runs. */
u8 isMoveScriptDone(void) {
    return MOVE_SCRIPT_TASK == NULL;
}

/* Fades the count colours from start a step a frame to level, unless a fade
 * is already running. */
void startFadeTask(s16 start, s16 count, s16 level) {
    struct FadeTask *fade;

    if (FADE_TASK != NULL) {
        return;
    }
    fade             = createTask(tickFadeTask, EFFECT_TASK_PRIORITY);
    FADE_TASK        = fade;
    fade->level      = level;
    fade->start      = start;
    fade->count      = count;
    fade->step       = level < 0 ? -1 : 1;
    fade->task.onEnd = clearFadeTask;
}

/* The fade task. It ends only once the level has gone past its target. */
void tickFadeTask(void) {
    struct FadeTask *fade;

    fade = (struct FadeTask *) getCurrentTask();
    FADE_LEVEL += fade->step;
    if ((FADE_LEVEL < fade->level && fade->step < 0) || (FADE_LEVEL > fade->level && fade->step > 0)) {
        FADE_LEVEL = fade->level;
        func_020846bc(fade->start, fade->count, FADE_LEVEL);
        markMainPalettesDirty();
        endTask(fade);
    } else {
        func_020846bc(fade->start, fade->count, FADE_LEVEL);
        markMainPalettesDirty();
    }
}

/* The fade task's end: forgets the task. */
void clearFadeTask(void) {
    FADE_TASK = NULL;
}

/* Whether no fade runs. */
u8 isFadeDone(void) {
    return FADE_TASK == NULL;
}

/* Clears both screens' list sprites and forgets the list task. */
void clearListSprites(void) {
    CLEAR(MAIN_LIST_SPRITES, sizeof(MAIN_LIST_SPRITES));
    CLEAR(SUB_LIST_SPRITES, sizeof(SUB_LIST_SPRITES));
    LIST_SPRITE_TASK    = NULL;
    data_ov001_0222aff4 = 0;
}

/* Starts the list task, with the lists cleared. */
void startListSpriteTask(void) {
    struct Task *task;

    clearListSprites();
    task             = createTask(tickListSprites, EFFECT_TASK_PRIORITY);
    LIST_SPRITE_TASK = task;
    task->onEnd      = freeListSprites;
}

/* Ends the list task. */
void stopListSpriteTask(void) {
    endTask(LIST_SPRITE_TASK);
}

/* Puts a sprite of the given kind, its colours in palette, in slot index of
 * the main screen's list, playing sequence seq at x, y. The move script's
 * command 6. */
void startMainListSprite(s32 kind, s32 palette, s16 x, s16 y, s16 seq, u32 index) {
    struct ListSprite *slot;

    if (index >= LIST_SPRITE_COUNT) {
        return;
    }
    if (MAIN_LIST_SPRITES[index].flags & EFFECT_IN_USE) {
        endMainListSprite(index);
    }
    slot         = &MAIN_LIST_SPRITES[index];
    slot->sprite = createMainSprite(kind, x, y, palette, 0);
    slot->flags |= EFFECT_IN_USE;
    slot->slot = index;
    slot->x    = x;
    slot->y    = y;
    restartMainSpriteAnim(slot->sprite, seq);
    setMainSpritePos(slot->sprite, slot->x + (EFFECT_TILE_OFFSET_OFF ? 0 : EFFECT_TILE_OFFSET_X * 8),
                     slot->y + (EFFECT_TILE_OFFSET_OFF ? 0 : EFFECT_TILE_OFFSET_Y * 8));
}

/* Ends the sprite in slot index of the main screen's list. */
void endMainListSprite(s32 index) {
    if (!(MAIN_LIST_SPRITES[index].flags & EFFECT_IN_USE)) {
        return;
    }
    freeMainSprite(MAIN_LIST_SPRITES[index].sprite);
    CLEAR(&MAIN_LIST_SPRITES[index], sizeof(struct ListSprite));
}

/* Ends the sprite in slot index of the sub screen's list. */
void endSubListSprite(s32 index) {
    if (!(SUB_LIST_SPRITES[index].flags & EFFECT_IN_USE)) {
        return;
    }
    freeSubSprite(SUB_LIST_SPRITES[index].sprite);
    CLEAR(&SUB_LIST_SPRITES[index], sizeof(struct ListSprite));
}

/* Ends all the main screen list's sprites. */
void endAllMainListSprites(void) {
    s32 index;

    index = 0;
    do {
        endMainListSprite(index);
        index++;
    } while (index < LIST_SPRITE_COUNT);
}

/* The list task's end: ends all the main screen list's sprites. */
void freeListSprites(void) {
    endAllMainListSprites();
}

/* The list task: ends the main screen list's sprites asked to end or done
 * playing, and moves the others with the tile offset. */
void tickListSprites(void) {
    s32 i;
    struct ListSprite *slot;

    slot = MAIN_LIST_SPRITES;
    for (i = 0; i < LIST_SPRITE_COUNT; i++, slot++) {
        if (!(slot->flags & EFFECT_IN_USE)) {
            continue;
        }
        if (slot->flags & EFFECT_ENDING) {
            endMainListSprite(slot->slot);
        } else if (isMainSpriteAnimDone(slot->sprite) != 0) {
            endMainListSprite(slot->slot);
        } else {
            setMainSpritePos(slot->sprite, slot->x + (EFFECT_TILE_OFFSET_OFF ? 0 : EFFECT_TILE_OFFSET_X * 8),
                             slot->y + (EFFECT_TILE_OFFSET_OFF ? 0 : EFFECT_TILE_OFFSET_Y * 8));
        }
    }
}

/* Whether the sprite in slot index of the main screen's list is done, or there
 * is none. */
u8 isMainListSpriteDone(u32 index) {
    struct ListSprite *slot;

    if (index >= LIST_SPRITE_COUNT) {
        return 1;
    }
    slot = &MAIN_LIST_SPRITES[index];
    if (!(slot->flags & EFFECT_IN_USE)) {
        return 1;
    }
    return isMainSpriteAnimDone(slot->sprite) != 0 ? 1 : 0;
}

/* Starts the main screen's effects task, setting the effects up first, and the
 * list task. */
void startMainBgEffectTask(void) {
    struct Task *task;

    initBgEffects();
    task                = createTask(tickMainBgEffects, EFFECT_TASK_PRIORITY);
    MAIN_BG_EFFECT_TASK = task;
    task->onEnd         = freeMainBgEffects;
    startListSpriteTask();
}

/* Starts the sub screen's effects task, setting the effects up first. */
void startSubBgEffectTask(void) {
    struct Task *task;

    initBgEffects();
    task               = createTask(tickSubBgEffects, EFFECT_TASK_PRIORITY);
    SUB_BG_EFFECT_TASK = task;
    task->onEnd        = freeSubBgEffects;
}

/* Ends the main screen's effects task and the list task. */
void stopMainBgEffectTask(void) {
    endTask(MAIN_BG_EFFECT_TASK);
    stopListSpriteTask();
}
