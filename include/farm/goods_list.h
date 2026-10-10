#ifndef FARM_GOODS_LIST_H
#define FARM_GOODS_LIST_H

/* The list of the items given to the digimon of a farm, 6 rows at a time. */

#include "types.h"

struct ItemList;

void func_ov005_0227b5f0(struct ItemList *list);
void func_ov005_0227b480(void);
void func_ov005_0227b4e4(s32 owner, s16 scroll, s16 cursor);
void func_ov005_0227b69c(struct ItemList *list);

#endif /* FARM_GOODS_LIST_H */
