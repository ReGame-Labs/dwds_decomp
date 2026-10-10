#include "battle/exp_level_up.h"
#include "battle/battle_state.h"
#include "battle/equip_bonus.h"
#include "battle/link_party.h"
#include "battle/unit_panels.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/input/touch.h"
#include "engine/save/game_state.h"
#include "engine/system/system.h"
#include "items/inventory.h"

/* Adds the experience of each kind to the Digimon's and counts down the
 * experience to the next level, a level at a time, until the level cap. The
 * level itself is left alone. Returns the experience added. */
s32 addExp(struct Digimon *digimon, const s32 *exp) {
    s32 i;
    s32 capped;
    s16 level;
    s32 gain;
    s32 total;
    s32 toNext;

    toNext = digimon->expToNext;
    capped = 0;
    level  = digimon->level;
    total  = 0;
    if (toNext == 0) {
        capped = 1;
    }
    for (i = 0; i < EXP_KIND_COUNT; i++) {
        gain = exp[i];
        total += gain;
        digimon->exp[i] += gain;
        if (digimon->exp[i] > EXP_CAP) {
            digimon->exp[i] = EXP_CAP;
        }
        if (!capped) {
            for (;;) {
                if (toNext <= gain) {
                    level++;
                    gain -= toNext;
                    toNext = getLevelUpExp(digimon, level);
                    if (toNext == 0) {
                        capped = 1;
                        break;
                    }
                } else {
                    toNext -= gain;
                    break;
                }
            }
        }
    }
    digimon->expToNext = toNext;
    return total;
}

/* addExp for the player's Digimon with the id. */
void addExpById(s32 id, const s32 *exp) {
    addExp(getDigimon(id), exp);
}

/* The experience the player's Digimon with the id still needs for its next
 * level. */
s32 getExpToNextById(s32 id) {
    struct Digimon *digimon = getDigimon(id);

    return digimon->expToNext;
}

/* The experience from the level to the next one, 0 at the level cap. */
s32 getLevelUpExp(struct Digimon *digimon, s16 level) {
    if (level >= LEVEL_CAP) {
        return 0;
    }
    if (digimon->maxLevel <= level) {
        return 0;
    }
    return EXP_CURVES[digimon->expCurve][level];
}

/* getLevelUpExp for the player's Digimon with the id. */
s32 getLevelUpExpById(s32 id, s16 level) {
    return getLevelUpExp(getDigimon(id), level);
}

/* How many levels the experience would raise the Digimon. */
s32 countLevelUps(struct Digimon *digimon, u32 exp) {
    s32 level;
    s32 toNext;
    s32 levels;

    level  = digimon->level;
    toNext = digimon->expToNext;
    levels = 0;
    if (digimon->maxLevel <= level) {
        return 0;
    }
    while (level < LEVEL_CAP) {
        if (exp < toNext) {
            break;
        }
        exp -= toNext;
        levels++;
        toNext = getLevelUpExp(digimon, level + 1);
        if (toNext == 0) {
            break;
        }
        level++;
    }
    return levels;
}

/* The stats a level up would give: each grows by a tenth of its growth, up to
 * HP_MP_CAP for HP and MP and STAT_CAP for the others. */
void rollLevelUpStats(struct Digimon *digimon, s16 *stats) {
    struct StatGrowth *growth;
    s16 gain;

    growth = &STAT_GROWTHS[digimon->growth][0];
    gain   = (growth->base + getRandom(growth->random)) / 10;
    if (gain < 0) {
        gain = 0;
    }
    stats[0] = digimon->maxHp + gain;
    if (stats[0] > HP_MP_CAP) {
        stats[0] = HP_MP_CAP;
    }
    growth = &STAT_GROWTHS[digimon->growth][1];
    gain   = (growth->base + getRandom(growth->random)) / 10;
    if (gain < 0) {
        gain = 0;
    }
    stats[1] = digimon->maxMp + gain;
    if (stats[1] > HP_MP_CAP) {
        stats[1] = HP_MP_CAP;
    }
    growth = &STAT_GROWTHS[digimon->growth][2];
    gain   = (growth->base + getRandom(growth->random)) / 10;
    if (gain < 0) {
        gain = 0;
    }
    stats[2] = digimon->unk48 + gain;
    if (stats[2] > STAT_CAP) {
        stats[2] = STAT_CAP;
    }
    growth = &STAT_GROWTHS[digimon->growth][3];
    gain   = (growth->base + getRandom(growth->random)) / 10;
    if (gain < 0) {
        gain = 0;
    }
    stats[3] = digimon->unk4A + gain;
    if (stats[3] > STAT_CAP) {
        stats[3] = STAT_CAP;
    }
    growth = &STAT_GROWTHS[digimon->growth][4];
    gain   = (growth->base + getRandom(growth->random)) / 10;
    if (gain < 0) {
        gain = 0;
    }
    stats[4] = digimon->unk4C + gain;
    if (stats[4] > STAT_CAP) {
        stats[4] = STAT_CAP;
    }
    growth = &STAT_GROWTHS[digimon->growth][5];
    gain   = (growth->base + getRandom(growth->random)) / 10;
    if (gain < 0) {
        gain = 0;
    }
    stats[5] = digimon->unk4E + gain;
    if (stats[5] > STAT_CAP) {
        stats[5] = STAT_CAP;
    }
}

/* Adds to the stats what a level up would add to the Digimon's. */
void addLevelUpStatGains(s32 id, s16 *stats) {
    struct Digimon *digimon = getDigimon(id);
    s16 next[6];

    rollLevelUpStats(digimon, next);
    stats[0] += next[0] - digimon->maxHp;
    stats[1] += next[1] - digimon->maxMp;
    stats[2] += next[2] - digimon->unk48;
    stats[3] += next[3] - digimon->unk4A;
    stats[4] += next[4] - digimon->unk4C;
    stats[5] += next[5] - digimon->unk4E;
}

/* Gives the Digimon the experience, and the stats of each level it gains,
 * which fill its HP and MP. Returns the levels gained. */
s32 gainExp(struct Digimon *digimon, const s32 *exp) {
    s32 total;
    s32 i;
    s32 levels;
    s16 stats[6];

    total = 0;
    for (i = 0; i < EXP_KIND_COUNT; i++) {
        total += exp[i];
    }
    levels = countLevelUps(digimon, total);
    addExp(digimon, exp);
    if (levels > 0) {
        for (i = 0; i < levels; i++) {
            rollLevelUpStats(digimon, stats);
            digimon->hp = digimon->maxHp = stats[0];
            digimon->mp = digimon->maxMp = stats[1];
            digimon->unk48               = stats[2];
            digimon->unk4A               = stats[3];
            digimon->unk4C               = stats[4];
            digimon->unk4E               = stats[5];
        }
    }
    return levels;
}

/* countLevelUps for the player's Digimon with the id. */
s32 countLevelUpsById(s32 id, u32 exp) {
    return countLevelUps(getDigimon(id), exp);
}

/* The sum of (i + 2) / 2 for i from start up to end. */
s32 func_0207f9d0(s32 start, s32 end) {
    s32 i;
    s32 total = 0;

    for (i = start; i < end; i++) {
        total += (i + 2) / 2;
    }
    return total;
}

/* Adds func_0207f9d0's sum to the counter of func_020a0864. */
void func_0207f9b8(s32 start, s32 end) {
    func_020a0864(func_0207f9d0(start, end));
}

/* How many ids the group of data_02135834 the id is in has, or -1. */
s32 func_0207f930(s32 id) {
    u32 row;
    s32 i;
    s32 count;

    for (row = 0; row < 39; row++) {
        for (i = 0; i < 5; i++) {
            if (id == data_02135834[row][i]) {
                for (count = 0; count < 5; count++) {
                    if (data_02135834[row][count] == -1) {
                        break;
                    }
                }
                return count;
            }
        }
    }
    return -1;
}

/* The first id of the group of data_02135834 the id is in, or the id itself. */
s32 func_0207f8d0(s32 id) {
    u32 row;
    s32 i;

    for (row = 0; row < 39; row++) {
        for (i = 0; i < 5; i++) {
            if (id == data_02135834[row][i]) {
                return data_02135834[row][0];
            }
        }
    }
    return id;
}

/* Which of the rectangles is touched, in the low byte, and which tapped, in the
 * high one (NO_RECT for none); a tap is used up. */
u16 getTouchedRects(const struct TouchRect *rects, s32 count) {
    s32 i;
    u16 touched;
    u16 tapped;

    touched = NO_RECT;
    tapped  = NO_RECT;
    for (i = 0; i < count; i++) {
        if (getTouchHeld() != 0 && isTouchInRect(rects[i].left, rects[i].top, rects[i].right, rects[i].bottom) == 1) {
            touched = i;
        }
        if (getTouchTap() != 0 && isTouchInRect(rects[i].left, rects[i].top, rects[i].right, rects[i].bottom) == 1) {
            clearTouch();
            tapped = i;
        }
    }
    return touched | (tapped << 8);
}

/* The attack the Digimon's equipment adds, the set bonuses included when
 * func_0207f6c0 finds a full set. */
s32 getEquipAttack(s32 kind, s32 id) {
    u8 fullSet = func_0207f6c0(kind, id) == 1;
    s32 total  = 0;
    u16 item;
    struct ItemData *data;

    item = getEquippedItem0(kind, id);
    if (item != NO_ITEM) {
        data = getItemData(item);
        total += data->attack;
        if (fullSet == 1) {
            total += data->setAttack;
        }
    }
    item = getEquippedItem1(kind, id);
    if (item != NO_ITEM) {
        data = getItemData(item);
        total += data->attack;
        if (fullSet == 1) {
            total += data->setAttack;
        }
    }
    item = getEquippedItem2(kind, id);
    if (item != NO_ITEM) {
        data = getItemData(item);
        total += data->attack;
        if (fullSet == 1) {
            total += data->setAttack;
        }
    }
    return total;
}

/* The defense the Digimon's equipment adds, set bonuses included. */
s32 getEquipDefense(s32 kind, s32 id) {
    u8 fullSet = func_0207f6c0(kind, id) == 1;
    s32 total  = 0;
    u16 item;
    struct ItemData *data;

    item = getEquippedItem0(kind, id);
    if (item != NO_ITEM) {
        data = getItemData(item);
        total += data->defense;
        if (fullSet == 1) {
            total += data->setDefense;
        }
    }
    item = getEquippedItem1(kind, id);
    if (item != NO_ITEM) {
        data = getItemData(item);
        total += data->defense;
        if (fullSet == 1) {
            total += data->setDefense;
        }
    }
    item = getEquippedItem2(kind, id);
    if (item != NO_ITEM) {
        data = getItemData(item);
        total += data->defense;
        if (fullSet == 1) {
            total += data->setDefense;
        }
    }
    return total;
}

/* The spirit the Digimon's equipment adds, set bonuses included. */
s32 getEquipSpirit(s32 kind, s32 id) {
    u8 fullSet = func_0207f6c0(kind, id) == 1;
    s32 total  = 0;
    u16 item;
    struct ItemData *data;

    item = getEquippedItem0(kind, id);
    if (item != NO_ITEM) {
        data = getItemData(item);
        total += data->spirit;
        if (fullSet == 1) {
            total += data->setSpirit;
        }
    }
    item = getEquippedItem1(kind, id);
    if (item != NO_ITEM) {
        data = getItemData(item);
        total += data->spirit;
        if (fullSet == 1) {
            total += data->setSpirit;
        }
    }
    item = getEquippedItem2(kind, id);
    if (item != NO_ITEM) {
        data = getItemData(item);
        total += data->spirit;
        if (fullSet == 1) {
            total += data->setSpirit;
        }
    }
    return total;
}

/* The speed the Digimon's equipment adds, set bonuses included. */
s32 getEquipSpeed(s32 kind, s32 id) {
    u8 fullSet = func_0207f6c0(kind, id) == 1;
    s32 total  = 0;
    u16 item;
    struct ItemData *data;

    item = getEquippedItem0(kind, id);
    if (item != NO_ITEM) {
        data = getItemData(item);
        total += data->speed;
        if (fullSet == 1) {
            total += data->setSpeed;
        }
    }
    item = getEquippedItem1(kind, id);
    if (item != NO_ITEM) {
        data = getItemData(item);
        total += data->speed;
        if (fullSet == 1) {
            total += data->setSpeed;
        }
    }
    item = getEquippedItem2(kind, id);
    if (item != NO_ITEM) {
        data = getItemData(item);
        total += data->speed;
        if (fullSet == 1) {
            total += data->setSpeed;
        }
    }
    return total;
}

/* The hit rate the Digimon's equipment adds. */
s32 getEquipHitRate(s32 kind, s32 id) {
    s32 total = 0;
    u16 item;

    item = getEquippedItem0(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->hitRate;
    }
    item = getEquippedItem1(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->hitRate;
    }
    item = getEquippedItem2(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->hitRate;
    }
    return total;
}
