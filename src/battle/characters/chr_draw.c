#include "battle/characters/chr_draw.h"
#include "battle/characters/data.h"
#include "engine/sprite/sprite_draw.h"

/* Sorts the main screen's draw list by y, the characters not in use last. */
void sortMainBattleChrs(void) {
    s16 i;
    s16 j;
    struct BattleChr *chr;
    BOOL swap;

    for (i = 0; i < BATTLE_CHR_COUNT - 1; i++) {
        for (j = BATTLE_CHR_COUNT - 1; j > i; j--) {
            swap = FALSE;
            if (!(MAIN_BATTLE_CHR_ORDER[j - 1]->flags & BATTLE_CHR_IN_USE)) {
                swap = TRUE;
            } else if ((MAIN_BATTLE_CHR_ORDER[j]->flags & BATTLE_CHR_IN_USE) &&
                       MAIN_BATTLE_CHR_ORDER[j]->y < MAIN_BATTLE_CHR_ORDER[j - 1]->y) {
                swap = TRUE;
            }
            if (swap) {
                chr                          = MAIN_BATTLE_CHR_ORDER[j];
                MAIN_BATTLE_CHR_ORDER[j]     = MAIN_BATTLE_CHR_ORDER[j - 1];
                MAIN_BATTLE_CHR_ORDER[j - 1] = chr;
            }
        }
    }
}

/* Sorts the sub screen's draw list by y, the characters not in use last. */
void sortSubBattleChrs(void) {
    s16 i;
    s16 j;
    struct BattleChr *chr;
    BOOL swap;

    for (i = 0; i < BATTLE_CHR_COUNT - 1; i++) {
        for (j = BATTLE_CHR_COUNT - 1; j > i; j--) {
            swap = FALSE;
            if (!(SUB_BATTLE_CHR_ORDER[j - 1]->flags & BATTLE_CHR_IN_USE)) {
                swap = TRUE;
            } else if ((SUB_BATTLE_CHR_ORDER[j]->flags & BATTLE_CHR_IN_USE) &&
                       SUB_BATTLE_CHR_ORDER[j]->y < SUB_BATTLE_CHR_ORDER[j - 1]->y) {
                swap = TRUE;
            }
            if (swap) {
                chr                         = SUB_BATTLE_CHR_ORDER[j];
                SUB_BATTLE_CHR_ORDER[j]     = SUB_BATTLE_CHR_ORDER[j - 1];
                SUB_BATTLE_CHR_ORDER[j - 1] = chr;
            }
        }
    }
}

/* Takes size tiles from the main screen's pool, returning where they start or
 * -1 when they don't fit. */
s16 allocMainBattleChrTiles(s16 size) {
    s16 offset;

    offset                     = MAIN_BATTLE_CHR_TILES_USED;
    MAIN_BATTLE_CHR_TILES_USED = offset + size;
    if (MAIN_BATTLE_CHR_TILES_USED > BATTLE_CHR_POOL_TILES) {
        MAIN_BATTLE_CHR_TILES_USED -= size;
        return -1;
    }
    return offset;
}

/* Gives back the main screen pool's tiles from offset on. */
void freeMainBattleChrTiles(s16 offset) {
    if (MAIN_BATTLE_CHR_TILES_USED > offset) {
        MAIN_BATTLE_CHR_TILES_USED = offset;
    }
}

/* Takes size tiles from the sub screen's pool, returning where they start or
 * -1 when they don't fit. */
s16 allocSubBattleChrTiles(s16 size) {
    s16 offset;

    offset                    = SUB_BATTLE_CHR_TILES_USED;
    SUB_BATTLE_CHR_TILES_USED = offset + size;
    if (SUB_BATTLE_CHR_TILES_USED > BATTLE_CHR_POOL_TILES) {
        SUB_BATTLE_CHR_TILES_USED -= size;
        return -1;
    }
    return offset;
}

/* Gives back the sub screen pool's tiles from offset on. */
void freeSubBattleChrTiles(s16 offset) {
    if (SUB_BATTLE_CHR_TILES_USED > offset) {
        SUB_BATTLE_CHR_TILES_USED = offset;
    }
}

/* Sets a main screen character's BG priority, and its sprite's. */
void setMainBattleChrPriority(u32 slot, s16 priority) {
    if (slot >= BATTLE_CHR_COUNT) {
        return;
    }
    if (!(MAIN_BATTLE_CHRS[slot].flags & BATTLE_CHR_IN_USE)) {
        return;
    }
    MAIN_BATTLE_CHRS[slot].priority = priority;
    if (MAIN_BATTLE_CHRS[slot].sprite == BATTLE_CHR_NO_SPRITE) {
        return;
    }
    setMainSpriteBgPriority(MAIN_BATTLE_CHRS[slot].sprite, priority);
}

/* Sets a sub screen character's BG priority, and its sprite's. */
void setSubBattleChrPriority(u32 slot, s16 priority) {
    if (slot >= BATTLE_CHR_COUNT) {
        return;
    }
    if (!(SUB_BATTLE_CHRS[slot].flags & BATTLE_CHR_IN_USE)) {
        return;
    }
    SUB_BATTLE_CHRS[slot].priority = priority;
    if (SUB_BATTLE_CHRS[slot].sprite == BATTLE_CHR_NO_SPRITE) {
        return;
    }
    setSubSpriteBgPriority(SUB_BATTLE_CHRS[slot].sprite, priority);
}

/* Sets the BG priority of all the main screen's characters. */
void setMainBattleChrsPriority(s16 priority) {
    s32 slot;

    slot = 0;
    do {
        setMainBattleChrPriority(slot, priority);
        slot++;
    } while (slot < BATTLE_CHR_COUNT);
}

/* Whether a main screen character's sequence has played its loops, or there is
 * no character. */
u8 isMainBattleChrSeqDone(u32 slot) {
    if (slot >= BATTLE_CHR_COUNT) {
        return 1;
    }
    if (MAIN_BATTLE_CHRS[slot].flags & BATTLE_CHR_IN_USE) {
        return MAIN_BATTLE_CHRS[slot].animDone;
    }
    return 1;
}

/* Whether a sub screen character's sequence has played its loops, or there is
 * no character. */
u8 isSubBattleChrSeqDone(u32 slot) {
    if (slot >= BATTLE_CHR_COUNT) {
        return 1;
    }
    if (SUB_BATTLE_CHRS[slot].flags & BATTLE_CHR_IN_USE) {
        return SUB_BATTLE_CHRS[slot].animDone;
    }
    return 1;
}
