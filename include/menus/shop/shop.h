#ifndef MENUS_SHOP_SHOP_H
#define MENUS_SHOP_SHOP_H

/* The shop: its task runShop, which openShop starts (script command
 * 0x124), and what its modes share. The mode (func_0207e6ac) picks the shop:
 * 0 and 1 equipment, 2 and 3 items, 4 farm upgrades, 5 farm goods; the odd
 * ones sell from a second catalog (func_0207e694). */

#include "engine/data.h"
#include "types.h"

enum ShopMode {
    SHOP_EQUIPMENT     = 0,
    SHOP_EQUIPMENT_2   = 1,
    SHOP_ITEMS         = 2,
    SHOP_ITEMS_2       = 3,
    SHOP_FARM_UPGRADES = 4,
    SHOP_FARM_GOODS    = 5,
};

/* How many frames the shop fades in and out over. */
#define SHOP_FADE_FRAMES 0x20

/* The shop's task. Each mode's screens run by state, each state by step. */
struct Shop {
    /* 0x00 */ struct Task task;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 opening; /* runShop's own steps, 4 once the shop is open */
    /* 0x1E */ u8 state;
    /* 0x1F */ u8 step;
    /* 0x20 */ u8 unk20[2];
    /* 0x22 */ s8 unk22; /* releaseGfxSlot frees it */
    /* 0x23 */ u8 window; /* closeWindow frees it */
    /* 0x24 */ u8 count;  /* of entries in the list */
    /* 0x25 */ u8 unk25; /* a window in modes 0 to 3 (closeWindow), a
                          * releaseGfxSlot id in mode 4 */
    /* 0x26 */ u8 choice; /* on the shop's menu (state 2), from the top */
    /* 0x27 */ u8 unk27;
    /* 0x28 */ u8 cursor; /* the row of the list the cursor is on */
    /* 0x29 */ u8 scroll; /* the entry of the list on the first row */
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 unk2B;
    /* 0x2C */ u8 unk2C;
    /* 0x2D */ u8 cursorFlash; /* func_020839c8's, stopped by stopSubPaletteEffects */
    /* 0x2E */ u8 unk2E;       /* 1 while func_020d2980's display is up */
    /* 0x2F */ u8 unk2F;
    /* 0x30 */ s32 actors[6]; /* main-screen actors, one for each set entry of
                               * data_021f5cf0 */
    /* 0x48 */ s32 timer;
};

/* A background the shop loads (func_020d5d44) and frees (freeShopBg). */
struct ShopBg {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 bg;
    /* 0x02 */ u8 unk2[2];
    /* 0x04 */ u16 chars; /* loadSubBgChars's or loadMainBgChars's, 0xFFFF for none */
    /* 0x08 */ s32 index; /* its entry of data_0213537c */
    /* 0x0C */ struct BgGraphics graphics;
};

#define SHOP_BG_COUNT 8

/* An entry of a shop's list: what it sells or buys, and the price. */
struct ShopEntry {
    /* 0x00 */ u16 id;
    /* 0x02 */ u8 unk2;
    /* 0x04 */ s32 price;
    /* 0x08 */ s32 unk8; /* the farm goods' FarmGoods id */
    /* 0x0C */ s32 unkC; /* the farm goods' FarmGoods unk8 */
};

/* The copies between the lists (fillFarmGoodsBuyList, fillItemShopList, func_020d3114,
 * func_020d3188 and func_020d31ec) move entries as blocks of bytes, one byte
 * at a time. */
struct ShopEntryBytes {
    u8 bytes[sizeof(struct ShopEntry)];
};

/* The most entries a shop's list holds. */
#define SHOP_LIST_SIZE 50

/* An entry of data_0210bc6c (func_020a1410), 0x18 bytes, as the item shop
 * reads it. */
struct ShopItem {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 price;
    /* 0x08 */ u8 unk8[0x10];
};

/* The upgrades of a farm in the farm upgrade shop (fillFarmUpgrades). */
#define SHOP_UPGRADE_COUNT 3

/* One of the upgrades of the farm upgrade shop. */
struct ShopUpgrade {
    /* 0x00 */ u8 unk0; /* 12 to 14 */
    /* 0x04 */ s32 price;
};

/* An entry of the stock of consumable items (ITEM_STOCK), as
 * func_0205c728 returns it. */
struct ShopStock {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u16 item;
    /* 0x06 */ s16 count;
};

/* The most of a consumable item the stock holds. */
#define SHOP_STOCK_MAX 99

/* What func_02050ffc needs to show an item in a window, at a place in tiles
 * from the window's corner. */
struct Params02050ffc {
    u8 window;
    s16 x;
    s16 y;
    s16 unk6;
    s16 unk8;
    u16 item; /* an id of data_0210bc6c (func_020a1410) */
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
};

/* The color of the list's first row; each row has its own, which
 * func_020839c8 flashes under the cursor. */
#define SHOP_ROW_COLORS 0xBA

/* Text codes: TEXT_END ends a text; 0xFFE9, whose meaning is not known,
 * brackets the numbers the shop writes. */
#define TEXT_END 0xFFFF
#define TEXT_UNKE9 0xFFE9

/* What func_02052c00 needs to show a piece of equipment in a window. */
struct Params02052c00 {
    u8 window;
    s16 x;
    s16 y;
    s16 item; /* an id for func_020a142c */
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
};

/* Bytes of a piece of equipment's record (func_020a142c): the level a Digimon
 * needs to equip it, and the unk1A a Digimon needs, EQUIPMENT_ANY_KIND for
 * any. */
#define EQUIPMENT_LEVEL 2
#define EQUIPMENT_KIND 3
#define EQUIPMENT_ANY_KIND 10

/* The pose of a Digimon in the equipment shop that can equip what the cursor
 * is on (showWhoCanEquip); the others face down. */
#define SHOP_CAN_EQUIP_ANIMATION 0x11

/* The Digimon shown in the shop, ids of data_021f5cf0. */
#define SHOP_DIGIMON_COUNT 6

/* The equipment shop's lists. */
#define SHOP_EQUIPMENT_LIST_A 19
#define SHOP_EQUIPMENT_LIST_B 23
#define SHOP_EQUIPMENT_LIST_C 21
#define SHOP_EQUIPMENT_LIST_D 33

#define SHOP_FARM_GOODS_COUNT 16
#define SHOP_ITEM_COUNT 25
#define SHOP_ITEM_COUNT_2 22

extern u8 data_021f5cd4[8];
extern s32 data_021f5cf0[SHOP_DIGIMON_COUNT]; /* ids of Digimon (getDigimon) shown in the shop */
extern struct ShopBg data_021f5d08;
extern struct ShopUpgrade FARM_UPGRADES[SHOP_UPGRADE_COUNT];
extern struct ShopEntry FARM_GOODS[SHOP_FARM_GOODS_COUNT]; /* the farm goods for sale */
extern struct ShopBg SHOP_BGS[SHOP_BG_COUNT];
extern struct ShopEntry data_021f6018[SHOP_EQUIPMENT_LIST_A]; /* func_020d324c's */
extern struct ShopEntry data_021f6148[SHOP_EQUIPMENT_LIST_B]; /* func_020d324c's */
extern struct ShopEntry ITEM_CATALOG[SHOP_ITEM_COUNT];   /* the item shop's catalog */
extern struct ShopEntry ITEM_CATALOG_2[SHOP_ITEM_COUNT_2]; /* the second item shop's */
extern struct ShopEntry SHOP_LIST[SHOP_LIST_SIZE];    /* the list the shop shows */
extern struct ShopEntry data_021f68c8[SHOP_EQUIPMENT_LIST_C]; /* the first equipment shop's */
extern struct ShopEntry data_021f6a18[SHOP_EQUIPMENT_LIST_D]; /* the second equipment shop's */
extern u16 data_021f6c28[][10][8];
extern u16 data_021f7128[][10][8];

void runShop(void);
void openShop(void);

#endif /* MENUS_SHOP_SHOP_H */
