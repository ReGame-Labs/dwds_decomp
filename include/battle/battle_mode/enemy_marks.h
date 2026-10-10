#ifndef BATTLE_BATTLE_MODE_ENEMY_MARKS_H
#define BATTLE_BATTLE_MODE_ENEMY_MARKS_H

/* The numbers over the enemies, the five marks of a skill's or an item's
 * range, and the clearing of parts of the battle's screens. */

#include "types.h"

struct UnitNumber;

void func_ov002_02239d04(void);
void func_ov002_0223a454(void);
void func_ov002_0223af00(void);
void func_ov002_02239a9c(struct UnitNumber *number);
void func_ov002_02239b28(void);
void func_ov002_0223a6f0(void);
void func_ov002_0223a840(void);
void setItemRangeColors(u32 id);
void setSkillRangeColors(u32 id);

#endif /* BATTLE_BATTLE_MODE_ENEMY_MARKS_H */
