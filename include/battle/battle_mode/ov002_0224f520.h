#ifndef BATTLE_BATTLE_MODE_OV002_0224F520_H
#define BATTLE_BATTLE_MODE_OV002_0224F520_H

/* Checks that put a special action (0xFFFE, 0xFFFD) in place of a unit's, and
 * the enemies' support skills (func_ov002_0224f82c). */

#include "types.h"

struct Battle;

s32 func_ov002_0224f520(struct Battle *battle, s32 unit);
s32 func_ov002_0224f570(struct Battle *battle, s32 unit);
s32 func_ov002_0224f82c();

#endif /* BATTLE_BATTLE_MODE_OV002_0224F520_H */
