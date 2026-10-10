#ifndef MENUS_SHOP_ITEM_EQUIPMENT_SHOP_H
#define MENUS_SHOP_ITEM_EQUIPMENT_SHOP_H

/* The item shop (modes 2 and 3, run by runItemShop) and the equipment shop
 * (modes 0 and 1, run by runEquipmentShop). */

#include "types.h"

struct Shop;

void func_020d2910(struct Shop *shop);
s32 isShopBackPressed(void);
void func_020d27cc(struct Shop *shop);
void func_020d2258(struct Shop *shop);
void func_020d4b1c(struct Shop *shop);
s32 func_020d5340(struct Shop *shop);
void func_020d2980(s16 item, struct Shop *shop);
u8 func_020d2a68(s32 item);
u8 func_020d2ac4(s32 item);
u8 func_020d2b20(s32 item);
void setShopDigimonAnimation(s16 animation, struct Shop *shop);
s32 func_020d3114(void);
s32 func_020d3188(void);
s32 func_020d31ec(void);
void func_020d3e64(struct Shop *shop);
void func_020d5108(s32 index);
void func_020d1ffc(struct Shop *shop);
void func_020d2354(struct Shop *shop);
void runItemShop(struct Shop *shop);
void showWhoCanEquip(s32 item, struct Shop *shop);
void func_020d4000(struct Shop *shop);
void func_020d4314(struct Shop *shop);
void func_020d44e4(struct Shop *shop);
void func_020d4990(struct Shop *shop);
void func_020d4c18(struct Shop *shop);
void runEquipmentShop(struct Shop *shop);

#endif /* MENUS_SHOP_ITEM_EQUIPMENT_SHOP_H */
