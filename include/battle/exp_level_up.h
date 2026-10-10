#ifndef BATTLE_EXP_LEVEL_UP_H
#define BATTLE_EXP_LEVEL_UP_H

#include "types.h"

/* What the equipment adds to the four main stats, experience and level ups,
 * and touch rectangles. */

#define LEVEL_CAP 99
#define EXP_CAP 99999 /* for each of a Digimon's kinds of experience */
#define EXP_KIND_COUNT 8
#define HP_MP_CAP 9999
#define STAT_CAP 999

/* getTouchedRects's result for no rectangle. */
#define NO_RECT 0xFF

struct Digimon;
struct TouchRect;

s32 getExpToNextById(s32 id);
void func_0207f9b8(s32 start, s32 end);
s32 func_0207f9d0(s32 start, s32 end);
s32 gainExp(struct Digimon *digimon, const s32 *exp);
void addLevelUpStatGains(s32 id, s16 *stats);
void rollLevelUpStats(struct Digimon *digimon, s16 *stats);
s32 getEquipSpeed(s32 kind, s32 id);
s32 getEquipSpirit(s32 kind, s32 id);
s32 getEquipDefense(s32 kind, s32 id);
s32 getEquipAttack(s32 kind, s32 id);
s32 func_0207f6c0(s32 kind, s32 id);
s32 countLevelUpsById(s32 id, u32 exp);
s32 getLevelUpExpById(s32 id, s16 level);
void addExpById(s32 id, const s32 *exp);
s32 countLevelUps(struct Digimon *digimon, u32 exp);
s32 getLevelUpExp(struct Digimon *digimon, s16 level);
s32 addExp(struct Digimon *digimon, const s32 *exp);
u16 getTouchedRects(const struct TouchRect *rects, s32 count);
s32 func_0207f8d0(s32 id);
s32 func_0207f930(s32 id);
s32 getEquipHitRate(s32 kind, s32 id);

#endif /* BATTLE_EXP_LEVEL_UP_H */
