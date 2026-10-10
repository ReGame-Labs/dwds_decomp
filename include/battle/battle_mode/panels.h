#ifndef BATTLE_BATTLE_MODE_PANELS_H
#define BATTLE_BATTLE_MODE_PANELS_H

/* The panels of the battle's screens about the party's units, and the packets
 * from the other DS in a link battle. */

#include "types.h"

struct BattlePanel;
struct BattleTask;

void receiveBattlePacket(struct BattleTask *task);
BOOL func_ov002_022466fc(s32 index);
void func_ov002_02245cb0(struct BattlePanel *panel);
void func_ov002_02245f60();
void closeUnitPanel(s32 index);
void closeFirstUnitPanel(void);

#endif /* BATTLE_BATTLE_MODE_PANELS_H */
