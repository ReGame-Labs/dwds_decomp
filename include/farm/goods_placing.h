#ifndef FARM_GOODS_PLACING_H
#define FARM_GOODS_PLACING_H

/* Placing goods on a spot of the farm's layout, and opening the goods panel. */

#include "types.h"

struct ButtonGroup;
struct GoodsPlacement;

void func_ov005_0228d8f8(struct GoodsPlacement *placement);
void func_ov005_0228d830(s16 touched, s16 cursor, struct ButtonGroup *buttons);
void openGoodsPanel(s32 goodsId, s8 view, s8 palette);

#endif /* FARM_GOODS_PLACING_H */
