#ifndef BATTLE_BATTLE_MODE_OV002_0224D15C_H
#define BATTLE_BATTLE_MODE_OV002_0224D15C_H

/* The battle's rewards: the Bits and EXP that the enemies beaten give. The
 * rest of this part is not in C yet. */

#include "types.h"

struct Battle;

void addEnemyExp(struct Battle *battle);
void addEnemyBits(struct Battle *battle);

#endif /* BATTLE_BATTLE_MODE_OV002_0224D15C_H */
