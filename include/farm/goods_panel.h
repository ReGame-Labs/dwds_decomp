#ifndef FARM_GOODS_PANEL_H
#define FARM_GOODS_PANEL_H

/* The goods panel: the window that shows goods, its texts, and the goods
 * list's sorting. */

#include "types.h"

struct Window;

s32 openFarmStatus();
void func_ov005_02289964(s32 value, s8 gfxSlot);
void openFarmStatusById(s32 farm, s8 gfxSlot);
void func_ov005_02289a78(void);
void func_ov005_02289b28(void);
s32 func_ov005_0228ad10();
void sortGoodsList(void);
void toggleGoodsPanelText(void);
void setGoodsPanelGoods(s32 goodsId);
s32 func_ov005_022890f0();
s32 func_ov005_0228a8b8();
s32 drawFarmStatus();
void drawFarmStatusBySlot(); /* (s32 slot): func_020d06a8 calls it without */
s32 func_ov005_0228bb40();
void func_ov005_0228ab04(s8 slot);
void func_ov005_0228ae74(s8 slot);
void func_ov005_022899cc(s32 slot, s8 gfxSlot);
void openFarmStatusBySlot(s32 slot, s8 gfxSlot);
void func_ov005_02289a34(void);
void func_ov005_0228afd8(u16 flags, struct Window *window);
void func_ov005_0228c798(u16 *sprite);
void func_ov005_0228c7c4(u16 *sprite);
void func_ov005_02289004(u16 flags, struct Window *window);
void func_ov005_0228ac88(void);
void func_ov005_0228accc(void);
void func_ov005_0228c7f0();
void func_ov005_0228c950(u16 flags, struct Window *window);
void func_ov005_02289044(s32 index, s8 gfxSlot);
void func_ov005_0228d164();

#endif /* FARM_GOODS_PANEL_H */
