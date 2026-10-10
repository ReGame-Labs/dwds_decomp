#ifndef MENUS_SHOP_SHOP_UI_H
#define MENUS_SHOP_SHOP_UI_H

/* The shop's list drawing (func_020d569c) and its backgrounds (func_020d5d44
 * loads one, freeShopBg frees it). */

#include "types.h"

struct ShopBg;

void freeShopBg(struct ShopBg *bg);

#endif /* MENUS_SHOP_SHOP_UI_H */
