#ifndef MENUS_SHOP_FARM_SHOPS_H
#define MENUS_SHOP_FARM_SHOPS_H

/* The farm shops: the farm goods shop (mode 5, run by runFarmGoodsShop) and the
 * farm upgrade shop (mode 4, run by runFarmUpgradeShop), then the start of the item
 * shop (func_020d1c38 to func_020d12dc). */

#include "types.h"

struct Shop;

void func_020d0ef8(struct Shop *shop);
void func_020d1014(struct Shop *shop);
u8 getStockCount(u32 item);
u8 getStockRoom(u32 item);
void func_020cecc4(struct Shop *shop);
void func_020d0af8(struct Shop *shop);
s32 func_020cf364(s32 index);
void func_020d06a8(struct Shop *shop);
void func_020cf464(struct Shop *shop);
void func_020cf558(struct Shop *shop);
u8 fillFarmUpgrades(s32 farm);
s32 func_020cf284();
void func_020d107c(u16 item, struct Shop *shop);
s16 fillFarmGoodsSellList(void);
s32 fillFarmGoodsBuyList(void);
void loadFarmGoods(void);
void func_020ce044(struct Shop *shop);
void func_020cfa2c(struct Shop *shop);
void func_020d12dc(struct Shop *shop);
s32 fillItemShopList(void);
void func_020ce1d8(struct Shop *shop);
void func_020ce478(struct Shop *shop);
void func_020ce610(struct Shop *shop);
void func_020cea44(struct Shop *shop);
void func_020cedc0(struct Shop *shop);
void runFarmGoodsShop(struct Shop *shop);
void func_020cf0d8(struct Shop *shop);
void func_020cfbdc(struct Shop *shop);
void func_020cfe28(struct Shop *shop);
void func_020d0148(struct Shop *shop);
void func_020d0858(struct Shop *shop);
void func_020d0bf4(struct Shop *shop);
void runFarmUpgradeShop(struct Shop *shop);
void func_020d0f30(struct Shop *shop, u32 item);
void loadItemCatalogs(void);
void func_020d1478(struct Shop *shop);
void func_020d1760(struct Shop *shop);
void func_020d1c38(struct Shop *shop);

#endif /* MENUS_SHOP_FARM_SHOPS_H */
