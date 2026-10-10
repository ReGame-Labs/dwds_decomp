#include "battle/characters/chr.h"
#include "battle/characters/chr_draw.h"
#include "battle/characters/data.h"
#include "engine/bg/bg_layers.h"
#include "engine/gfx/gfx_files.h"
#include "engine/libs.h"
#include "engine/palette/palette_fade.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"

/* Puts a character in a slot of the main screen after delay frames, by
 * placeMainBattleChr, and shows it. A different character in the slot is
 * removed at once. */
void startMainBattleChrPlaceTask(u16 chr, s16 x, s16 y, u16 palette, u32 slot, u16 place, u8 unk2E, u8 withSprite, s32 delay,
                                 u16 priority) {
    struct BattleChr *placed;
    struct ChrPlaceTask *task;

    if (slot >= BATTLE_CHR_COUNT) {
        return;
    }
    if (MAIN_BATTLE_CHR_PLACE_TASKS[slot] != NULL) {
        endTask(MAIN_BATTLE_CHR_PLACE_TASKS[slot]);
        MAIN_BATTLE_CHR_PLACE_TASKS[slot] = NULL;
    }
    placed = &MAIN_BATTLE_CHRS[slot];
    if (!(placed->flags & BATTLE_CHR_IN_USE) || placed->chr != chr) {
        removeMainBattleChr(slot);
    }
    task                              = createTask(tickMainBattleChrPlaceTask, priority);
    task->task.onEnd                  = NULL;
    MAIN_BATTLE_CHR_PLACE_TASKS[slot] = task;
    task->state                       = CHR_PLACE_TASK_NEW;
    task->timer                       = 0;
    task->chr                         = chr;
    task->x                           = x;
    task->y                           = y;
    task->palette                     = palette;
    task->slot                        = slot;
    task->place                       = place;
    task->unk2E                       = unk2E;
    task->withSprite                  = withSprite;
    task->delay                       = delay;
}

/* The same on the sub screen, by placeSubBattleChr, showing the character
 * only if show is set. */
void startSubBattleChrPlaceTask(u16 chr, s16 x, s16 y, u16 palette, u32 slot, u16 place, u8 unk2E, u8 withSprite, s32 delay,
                                u16 priority, u8 show) {
    struct BattleChr *placed;
    struct ChrPlaceTask *task;

    if (slot >= BATTLE_CHR_COUNT) {
        return;
    }
    if (SUB_BATTLE_CHR_PLACE_TASKS[slot] != NULL) {
        endTask(SUB_BATTLE_CHR_PLACE_TASKS[slot]);
        SUB_BATTLE_CHR_PLACE_TASKS[slot] = NULL;
    }
    placed = &SUB_BATTLE_CHRS[slot];
    if (!(placed->flags & BATTLE_CHR_IN_USE) || placed->chr != chr) {
        removeSubBattleChr(slot);
    }
    task                             = createTask(tickSubBattleChrPlaceTask, priority);
    task->task.onEnd                 = NULL;
    SUB_BATTLE_CHR_PLACE_TASKS[slot] = task;
    task->state                      = CHR_PLACE_TASK_NEW;
    task->timer                      = 0;
    task->chr                        = chr;
    task->x                          = x;
    task->y                          = y;
    task->palette                    = palette;
    task->slot                       = slot;
    task->place                      = place;
    task->unk2E                      = unk2E;
    task->withSprite                 = withSprite;
    task->delay                      = delay;
    task->show                       = show;
}

/* The main screen's placing task: waits its delay, places and shows the
 * character, then ends itself. */
void tickMainBattleChrPlaceTask(void) {
    struct ChrPlaceTask *task;

    task = (struct ChrPlaceTask *) getCurrentTask();
    switch (task->state) {
        case 0:
            task->timer++;
            if (task->delay > task->timer) {
                break;
            }
            task->timer = 0;
            task->state++;
            break;
        case 1:
            placeMainBattleChr(task->chr, task->x, task->y, task->palette, task->slot, task->place, task->unk2E,
                               task->withSprite);
            clearMainBattleChrFlags(task->slot, BATTLE_CHR_HIDDEN);
            task->state++;
            break;
        case 2:
            endTask(MAIN_BATTLE_CHR_PLACE_TASKS[task->slot]);
            MAIN_BATTLE_CHR_PLACE_TASKS[task->slot] = NULL;
            break;
        case CHR_PLACE_TASK_NEW:
            task->state = 0;
            break;
    }
}

/* The sub screen's placing task: waits its delay, places the character, shows
 * it if asked, then ends itself. */
void tickSubBattleChrPlaceTask(void) {
    struct ChrPlaceTask *task;

    task = (struct ChrPlaceTask *) getCurrentTask();
    switch (task->state) {
        case 0:
            task->timer++;
            if (task->delay > task->timer) {
                break;
            }
            task->timer = 0;
            task->state++;
            break;
        case 1:
            placeSubBattleChr(task->chr, task->x, task->y, task->palette, task->slot, task->place, task->unk2E,
                              task->withSprite);
            if (task->show) {
                clearSubBattleChrFlags(task->slot, BATTLE_CHR_HIDDEN);
            }
            task->state++;
            break;
        case 2:
            endTask(SUB_BATTLE_CHR_PLACE_TASKS[task->slot]);
            SUB_BATTLE_CHR_PLACE_TASKS[task->slot] = NULL;
            break;
        case CHR_PLACE_TASK_NEW:
            task->state = 0;
            break;
    }
}

/* Removes all the main screen's characters. */
void removeAllMainBattleChrs(void) {
    s32 slot;

    slot = 0;
    do {
        removeMainBattleChr(slot);
        slot++;
    } while (slot < BATTLE_CHR_COUNT);
}

/* Removes all the sub screen's characters. */
void removeAllSubBattleChrs(void) {
    s32 slot;

    slot = 0;
    do {
        removeSubBattleChr(slot);
        slot++;
    } while (slot < BATTLE_CHR_COUNT);
}

/* Takes the tiles of the main screen's characters above offset again, once a
 * character below them has given its own back, and marks them to be loaded
 * again. */
void reallocMainBattleChrTiles(u32 offset) {
    s32 i;
    struct BattleChr *chr;
    u8 *reload;

    chr    = MAIN_BATTLE_CHRS;
    reload = MAIN_BATTLE_CHR_RELOAD;
    for (i = 0; i < BATTLE_CHR_COUNT; i++) {
        if ((chr->flags & BATTLE_CHR_IN_USE) && chr->tileOffset > offset) {
            chr->tileOffset = allocMainBattleChrTiles(chr->anim->size >> 1);
            *reload         = 1;
        }
        chr++;
        reload++;
    }
}

/* The same for the sub screen's characters. */
void reallocSubBattleChrTiles(u32 offset) {
    s32 i;
    struct BattleChr *chr;
    u8 *reload;

    chr    = SUB_BATTLE_CHRS;
    reload = SUB_BATTLE_CHR_RELOAD;
    for (i = 0; i < BATTLE_CHR_COUNT; i++) {
        if ((chr->flags & BATTLE_CHR_IN_USE) && chr->tileOffset > offset) {
            chr->tileOffset = allocSubBattleChrTiles(chr->anim->size >> 1);
            *reload         = 1;
        }
        chr++;
        reload++;
    }
}

/* Ends the characters of both screens: their draw tasks, their sprite VRAM and
 * the sprites 0x80 to 0x82. */
void endBattleChrs(void) {
    endTasksOfPriority(BATTLE_CHR_TASK_PRIORITY);
    func_0208577c(4, 1);
    func_02085710(4, 1);
    MAIN_BATTLE_CHR_VRAM = 0;
    SUB_BATTLE_CHR_VRAM  = 0;
    freeSubSprite(0x80);
    freeSubSprite(0x81);
    freeSubSprite(0x82);
    freeMainSprite(0x80);
    freeMainSprite(0x81);
    freeMainSprite(0x82);
}

/* Removes a main screen character: gives back its tiles, its files and its
 * sprite. */
void removeMainBattleChr(u32 slot) {
    struct BattleChr *chr;

    if (slot >= BATTLE_CHR_COUNT) {
        return;
    }
    chr = &MAIN_BATTLE_CHRS[slot];
    if (!(chr->flags & BATTLE_CHR_IN_USE)) {
        return;
    }
    if (chr->tileOffset != BATTLE_CHR_NO_TILES) {
        freeMainBattleChrTiles(chr->tileOffset);
    }
    reallocMainBattleChrTiles(chr->tileOffset);
    freeBattleChrFiles(chr->chr);
    freeMainSprite(chr->sprite);
    func_02030f18(chr, 0, sizeof(struct BattleChr));
}

/* Removes a sub screen character: gives back its tiles, its files and its
 * sprite. */
void removeSubBattleChr(u32 slot) {
    struct BattleChr *chr;

    if (slot >= BATTLE_CHR_COUNT) {
        return;
    }
    chr = &SUB_BATTLE_CHRS[slot];
    if (!(chr->flags & BATTLE_CHR_IN_USE)) {
        return;
    }
    if (chr->tileOffset != BATTLE_CHR_NO_TILES) {
        freeSubBattleChrTiles(chr->tileOffset);
    }
    reallocSubBattleChrTiles(chr->tileOffset);
    freeBattleChrFiles(chr->chr);
    freeSubSprite(chr->sprite);
    func_02030f18(chr, 0, sizeof(struct BattleChr));
}

/* Loads a character's "%d.c" file, its characters, unless it is in, and counts
 * one more user. */
void loadBattleChrChars(s32 chr) {
    char name[8];
    char path[64];
    u16 file;

    file = BATTLE_CHR_FILES[chr].cFile;
    if (BTCHR_CHAR_DATA[file] == NULL && BTCHR_C_USERS[file] == 0) {
        func_020e3a68(name, data_ov001_02201364, file);
        joinPath(path, data_ov001_0220136c, name);
        func_02043fc4(&BTCHR_C_FILES[file], path);
        func_020b9cc0(BTCHR_C_FILES[file], &BTCHR_CHAR_DATA[file]);
    }
    BTCHR_C_USERS[file]++;
}

/* Loads a character's "%d.a" file, its sequences, unless it is in, and counts
 * one more user. */
void loadBattleChrAnim(s32 chr) {
    char name[8];
    char path[64];
    u16 file;

    file = BATTLE_CHR_FILES[chr].aFile;
    if (BTCHR_A_FILES[file] == NULL && BTCHR_A_USERS[file] == 0) {
        func_020e3a68(name, data_ov001_02201350, file);
        joinPath(path, data_ov001_02201358, name);
        func_02043fc4(&BTCHR_A_FILES[file], path);
    }
    BTCHR_A_USERS[file]++;
}

/* Loads a character's "%d.p" file unless it is in, counts one more user, and
 * copies its 256 colours to the main screen's sprite palette. */
void loadMainBattleChrPalette(s32 chr, s32 palette) {
    char name[8];
    char path[68];
    u16 file;

    file = BATTLE_CHR_FILES[chr].pFile;
    if (BTCHR_PALETTES[file] == NULL && BTCHR_P_USERS[file] == 0) {
        func_020e3a68(name, data_ov001_02201314, file);
        joinPath(path, data_ov001_0220131c, name);
        func_02043fc4(&BTCHR_P_FILES[file], path);
        func_020b9d80(BTCHR_P_FILES[file], &BTCHR_PALETTES[file]);
    }
    loadMainPalette((u16) ((palette << 8) + 0xA00), 0x100, (s32) BTCHR_PALETTES[file]->pRawData);
    BTCHR_P_USERS[file]++;
}

/* The same for the sub screen's sprite palette. */
void loadSubBattleChrPalette(s32 chr, s32 palette) {
    char name[8];
    char path[68];
    u16 file;

    file = BATTLE_CHR_FILES[chr].pFile;
    if (BTCHR_PALETTES[file] == NULL && BTCHR_P_USERS[file] == 0) {
        func_020e3a68(name, data_ov001_02201300, file);
        joinPath(path, data_ov001_02201308, name);
        func_02043fc4(&BTCHR_P_FILES[file], path);
        func_020b9d80(BTCHR_P_FILES[file], &BTCHR_PALETTES[file]);
    }
    loadSubPalette((u16) ((palette << 8) + 0xA00), 0x100, (s32) BTCHR_PALETTES[file]->pRawData);
    BTCHR_P_USERS[file]++;
}

/* Sets flags of a main screen character in use. */
void setMainBattleChrFlags(u32 slot, s32 flags) {
    struct BattleChr *chr;

    if (slot >= BATTLE_CHR_COUNT) {
        return;
    }
    chr = &MAIN_BATTLE_CHRS[slot];
    if (chr->flags & BATTLE_CHR_IN_USE) {
        chr->flags |= flags;
    }
}

/* Sets flags of a sub screen character in use. */
void setSubBattleChrFlags(u32 slot, s32 flags) {
    struct BattleChr *chr;

    if (slot >= BATTLE_CHR_COUNT) {
        return;
    }
    chr = &SUB_BATTLE_CHRS[slot];
    if (chr->flags & BATTLE_CHR_IN_USE) {
        chr->flags |= flags;
    }
}

/* Clears flags of a main screen character in use. */
void clearMainBattleChrFlags(u32 slot, s32 flags) {
    struct BattleChr *chr;

    if (slot >= BATTLE_CHR_COUNT) {
        return;
    }
    chr = &MAIN_BATTLE_CHRS[slot];
    if (chr->flags & BATTLE_CHR_IN_USE) {
        chr->flags &= ~flags;
    }
}

/* Clears flags of a sub screen character in use. */
void clearSubBattleChrFlags(u32 slot, s32 flags) {
    struct BattleChr *chr;

    if (slot >= BATTLE_CHR_COUNT) {
        return;
    }
    chr = &SUB_BATTLE_CHRS[slot];
    if (chr->flags & BATTLE_CHR_IN_USE) {
        chr->flags &= ~flags;
    }
}

/* Returns a main screen character, NULL when its slot is empty or past the
 * last. */
void *getMainBattleChr(u32 slot) {
    if (slot >= BATTLE_CHR_COUNT) {
        return NULL;
    }
    if (MAIN_BATTLE_CHRS[slot].flags & BATTLE_CHR_IN_USE) {
        return &MAIN_BATTLE_CHRS[slot];
    }
    return NULL;
}

/* Returns a sub screen character, NULL when its slot is empty or past the
 * last. */
void *getSubBattleChr(u32 slot) {
    if (slot >= BATTLE_CHR_COUNT) {
        return NULL;
    }
    if (SUB_BATTLE_CHRS[slot].flags & BATTLE_CHR_IN_USE) {
        return &SUB_BATTLE_CHRS[slot];
    }
    return NULL;
}

/* Starts a main screen character's sequence seq over, to play loopLimit times. */
void playMainBattleChrSeq(u32 slot, s16 seq, s16 loopLimit) {
    if (slot >= BATTLE_CHR_COUNT) {
        return;
    }
    MAIN_BATTLE_CHRS[slot].seq       = seq;
    MAIN_BATTLE_CHRS[slot].time      = 0;
    MAIN_BATTLE_CHRS[slot].loopLimit = loopLimit;
    MAIN_BATTLE_CHRS[slot].loops     = 0;
    MAIN_BATTLE_CHRS[slot].animDone  = 0;
}

/* Starts a sub screen character's sequence seq over, to play loopLimit times. */
void playSubBattleChrSeq(u32 slot, s16 seq, s16 loopLimit) {
    if (slot >= BATTLE_CHR_COUNT) {
        return;
    }
    SUB_BATTLE_CHRS[slot].seq       = seq;
    SUB_BATTLE_CHRS[slot].time      = 0;
    SUB_BATTLE_CHRS[slot].loopLimit = loopLimit;
    SUB_BATTLE_CHRS[slot].loops     = 0;
    SUB_BATTLE_CHRS[slot].animDone  = 0;
}

/* Moves frames past seq sequences. */
void skipBattleChrSeqs(struct BtchrFrame **frames, u16 seq) {
    u16 n;

    if (seq == 0) {
        return;
    }
    for (n = 0;; (*frames)++) {
        if (n == seq) {
            return;
        }
        if ((*frames)->duration == BTCHR_SEQ_END) {
            n++;
        }
    }
}

/* The cell a character's sequence shows at its time, keeping the frame it is
 * at, or -1 once the time is past the sequence. */
s16 getBattleChrCell(struct BattleChr *chr) {
    struct BtchrFrame *frames;
    s16 time;
    u16 frame;
    u16 end;

    frames = chr->frames;
    time   = chr->time;
    skipBattleChrSeqs(&frames, chr->seq);
    for (frame = 0, end = 0;; frame++) {
        if (frames[frame].duration == BTCHR_SEQ_END) {
            return -1;
        }
        end += frames[frame].duration;
        if (end >= time) {
            chr->frame = frame;
            return frames[frame].cell;
        }
    }
}
