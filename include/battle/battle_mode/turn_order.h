#ifndef BATTLE_BATTLE_MODE_TURN_ORDER_H
#define BATTLE_BATTLE_MODE_TURN_ORDER_H

/* The turn order, the message window, the unit panels' units and icons, the
 * delayed values and the display settings changed at the vblank. */

#include "nitro/gx.h"
#include "types.h"

struct BattleTask;
struct TextWindow;
struct Turn;
struct WindowLayout;

s8 getUnitPanelUnit(s32 index);
void copyWindowLayout(struct WindowLayout *layout, struct TextWindow *window);
void disableBattleSubBlend(void);
void disableBattleMainBlend(void);
void changeBattleSubBlendWeights(s32 ev1, s32 ev2);
void setBattleSubBlend(s32 plane1, s32 plane2, s32 ev1, s32 ev2);
void setBattleMainBlend(s32 plane1, s32 plane2, s32 ev1, s32 ev2);
void func_ov002_02249e10(s8 value, s8 subBg3Setup);
void setBattleDispSelect(enum GXDispSelect sel);
void refreshUnitPanel(s32 index);
BOOL func_ov002_02247b34(s16 value, s16 frames);
void func_ov002_02247b94(void);
void setUnitPanelUnit(s32 index, u8 unit);
void setFirstUnitPanelUnit(u8 unit);
void func_ov002_02247bf4(void);
void func_ov002_022474e0();
void func_ov002_02249a2c();
void rebuildTurnOrder(struct BattleTask *task);
void func_ov002_02249f64(struct Turn *turn);
void func_ov002_0224a0c8(s32 reset);
void refreshFirstUnitPanel(void);

#endif /* BATTLE_BATTLE_MODE_TURN_ORDER_H */
