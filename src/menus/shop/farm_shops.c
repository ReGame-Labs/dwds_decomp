#include "menus/shop/farm_shops.h"
#include "battle/sprite_slots.h"
#include "battle/unit_panels.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/palette/palette_fade.h"
#include "engine/save/game_state.h"
#include "engine/script/interpreter.h"
#include "engine/system/display.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/text/text_banks.h"
#include "engine/text/window_text.h"
#include "engine/window/window.h"
#include "engine/window/window_draw.h"
#include "farm/data.h"
#include "farm/farms.h"
#include "farm/goods_panel.h"
#include "field/actors/actor_create.h"
#include "field/actors/actor_tasks.h"
#include "items/inventory.h"
#include "items/inventory_queries.h"
#include "menus/experience/experience_screen.h"
#include "menus/shop/item_equipment_shop.h"
#include "menus/shop/shop.h"
#include "menus/shop/shop_ui.h"
#include "menus/widgets/item_displays.h"
#include "menus/widgets/menu_displays.h"
#include "menus/widgets/window_anim.h"

/* The item shop's last state: fades out over SHOP_FADE_FRAMES, then takes the
 * shop down and ends its task. */
void func_020d12dc(struct Shop *shop) {
    s32 i;
    struct ShopBg *bg;

    switch (shop->step) {
        case 0:
            shop->timer = SHOP_FADE_FRAMES;
            fadeOutMainPalette(0, 0x100, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            fadeOutMainPalette(0x900, 0x100, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            fadeOutMainPalette(0xA00, 0x800, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            shop->step++;
            break;
        case 1:
            shop->timer--;
            if (shop->timer > 0) {
                break;
            }
            deleteMainActors();
            endMainActorTask();
            unloadMainWindowFrame();
            closeWindow(shop->unk25);
            releaseMenuDisplays();
            releaseGfxSlot(shop->unk22);
            closeWindow(shop->window);
            if (data_021f5d08.chars != 0xFFFF) {
                freeShopBg(&data_021f5d08);
            }
            bg = &SHOP_BGS[SHOP_BG_COUNT - 1];
            for (i = SHOP_BG_COUNT - 1; i >= 0; i--) {
                if (bg->chars != 0xFFFF) {
                    freeShopBg(bg);
                }
                bg--;
            }
            for (i = 0xFF; i >= 0; i--) {
                releaseSlotSprite(i);
            }
            func_020a98a8(2);
            func_020a9844(2);
            func_0207e6bc(1);
            endTask(getCurrentTask());
            shop->state = 7;
            break;
    }
}

/* Fills the item shops' catalogs from their id lists (data_0213857c and
 * data_021384c0) with each item's price. */
void loadItemCatalogs(void) {
    struct ShopEntry *entry = ITEM_CATALOG;
    struct ShopItem *item;
    u32 i;

    for (i = 0; i < SHOP_ITEM_COUNT; i++, entry++) {
        item         = (struct ShopItem *) func_020a1410(data_0213857c[i]);
        entry->id    = data_0213857c[i];
        entry->unk2  = item->unk4;
        entry->price = item->price;
    }
    for (i = 0; i < SHOP_ITEM_COUNT_2; i++, entry++) {
        item         = (struct ShopItem *) func_020a1410(data_021384c0[i]);
        entry->id    = data_021384c0[i];
        entry->unk2  = item->unk4;
        entry->price = item->price;
    }
}

/* Puts the item shop's catalog, the first or the second (loadItemCatalogs), in
 * the shop's list and returns its count. */
s32 fillItemShopList(void) {
    s32 i;
    struct ShopEntryBytes *dst, *src;
    s32 count;

    dst = (struct ShopEntryBytes *) SHOP_LIST;
    if (func_0207e694() == 0) {
        src   = (struct ShopEntryBytes *) ITEM_CATALOG;
        count = SHOP_ITEM_COUNT;
    } else {
        src   = (struct ShopEntryBytes *) ITEM_CATALOG_2;
        count = SHOP_ITEM_COUNT_2;
    }
    for (i = 0; i < count; i++) {
        *dst = *src;
        dst++;
        src++;
    }
    return count;
}

/* How many of an item the stock holds, 0 for none. */
u8 getStockCount(u32 item) {
    if (hasItem(item) != 1) {
        return 0;
    }
    return ((struct ShopStock *) func_0205c728(item, 0))->count;
}

/* How many more of an item the stock takes. */
u8 getStockRoom(u32 item) {
    u8 count;

    count = getStockCount(item);
    if (count != 0) {
        return SHOP_STOCK_MAX - count;
    }
    return SHOP_STOCK_MAX;
}

/* Shows func_02050ffc's display of an item in window unk25. */
void func_020d107c(u16 item, struct Shop *shop) {
    struct Params02050ffc params;

    params.item   = item;
    params.window = shop->unk25;
    params.x      = 1;
    params.y      = 7;
    params.unk6   = 3;
    params.unk8   = 1;
    params.unkC   = 2;
    params.unkE   = 1;
    params.unk10  = 3;
    params.unk12  = 0;
    params.unk14  = SHOP_BGS[1].chars + 0x50;
    params.unk16  = 2;
    params.unk18  = 0;
    func_02050ffc(0, &params);
}

/* Takes down func_020d107c's display and clears its window. */
void func_020d1014(struct Shop *shop) {
    freeItemRecordDisplaySprites(0);
    closeItemRecordDisplay(0);
    freeTextBank();
    func_020a8a98(shop->unk25, 0, 0, 0xD, 0x10, 0);
    func_020867fc(0, 0x12, 7, 0xD, 0x10, 0);
}

/* Writes label 0x1B and how many of an item the stock holds in the shop's
 * window. */
void func_020d0f30(struct Shop *shop, u32 item) {
    u16 text[16];
    s32 count;

    func_020a68cc(shop->window, 6, 0x11, 6, 2, func_0209ec68(0x1B), 0x11C, 0xB, 3, 2, 0);
    count   = getStockCount(item);
    text[0] = TEXT_UNKE9;
    text[1] = 0x81;
    formatNumber(count, 2, &text[2], 0);
    text[4] = TEXT_UNKE9;
    text[5] = TEXT_END;
    func_020a68cc(shop->window, 0x10, 0x11, 3, 2, text, 0x128, 0xB, 3, 2, 2);
}

/* Clears what func_020d0f30 wrote. */
void func_020d0ef8(struct Shop *shop) {
    func_020a8a98(shop->window, 6, 0x11, 0xD, 2, 0xFFFF);
}

/* The farm upgrade shop (mode 4): runs its state. */
void runFarmUpgradeShop(struct Shop *shop) {
    switch (shop->state) {
        case 0:
            func_020d0bf4(shop);
            break;
        case 1:
            func_020d0af8(shop);
            break;
        case 2:
            func_020d0858(shop);
            break;
        case 3:
            func_020d06a8(shop);
            break;
        case 4:
            func_020d0148(shop);
            break;
        case 5:
            func_020cfe28(shop);
            break;
        case 6:
            func_020cfbdc(shop);
            break;
        case 7:
            func_020cfa2c(shop);
            break;
    }
}

/* The farm upgrade shop's fade in, then its menu (state 2). */
void func_020d0af8(struct Shop *shop) {
    switch (shop->step) {
        case 0:
            shop->timer = SHOP_FADE_FRAMES;
            showMainLayers(0x1F);
            fadeInMainPalette(0, 0x100, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            fadeInMainPalette(0x900, 0x100, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            fadeInMainPalette(0xA00, 0x800, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            shop->step++;
            return;
        case 1:
            shop->timer--;
            if (shop->timer <= 0) {
                shop->choice = 0;
                shop->state  = 2;
            }
            return;
    }
}

/* The farm upgrade shop's list of farms: A picks the one under the cursor and
 * shows its upgrades (state 4), B goes back to the menu (state 2), and moving
 * the cursor shows the farm it is on. */
void func_020d06a8(struct Shop *shop) {
    s32 action;
    u8 cursor;
    u8 oldEntry;
    u8 newEntry;

    cursor   = shop->cursor;
    action   = 0;
    oldEntry = cursor + shop->scroll;
    if (isShopBackPressed() == 1) {
        action = 2;
    } else if (func_020d5340(shop) == 1) {
        action = 1;
    }
    newEntry = shop->cursor + shop->scroll;
    if (action == 1) {
        playSound(1);
        shop->unk2A  = shop->cursor;
        shop->cursor = 0;
        restoreSubPalette((u8) (cursor + SHOP_ROW_COLORS), 1);
        stopSubPaletteEffects(shop->cursorFlash);
        shop->cursorFlash = func_020839c8((u8) (shop->cursor + SHOP_ROW_COLORS), 1, 0x7FFF, 0x4B, 0, 1, 10000);
        shop->count       = fillFarmUpgrades(shop->unk2A);
        func_020cf558(shop);
        shop->state = 4;
        return;
    }
    if (action == 2) {
        playSound(3);
        func_020cf464(shop);
        restoreSubPalette((u8) (cursor + SHOP_ROW_COLORS), 1);
        stopSubPaletteEffects(shop->cursorFlash);
        drawFarmStatus(0);
        showSlotSprite(0x81);
        shop->state = 2;
        return;
    }
    if (newEntry == oldEntry) {
        return;
    }
    playSound(0);
    restoreSubPalette((u8) (cursor + SHOP_ROW_COLORS), 1);
    stopSubPaletteEffects(shop->cursorFlash);
    shop->cursorFlash = func_020839c8((u8) (shop->cursor + SHOP_ROW_COLORS), 1, 0x7FFF, 0x4B, 0, 1, 10000);
    getFarmSlotAt(newEntry);
    drawFarmStatusBySlot();
}

/* The farm upgrade shop's last state: fades out, takes the shop down and ends
 * its task. */
void func_020cfa2c(struct Shop *shop) {
    s32 i;
    struct ShopBg *bg;

    switch (shop->step) {
        case 0:
            shop->timer = SHOP_FADE_FRAMES;
            fadeOutMainPalette(0, 0x100, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            fadeOutMainPalette(0x900, 0x100, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            fadeOutMainPalette(0xA00, 0x800, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            shop->step++;
            break;
        case 1:
            shop->timer--;
            if (shop->timer > 0) {
                break;
            }
            func_ov005_02289a34();
            func_ov005_022890f0();
            releaseGfxSlot((s8) shop->unk25);
            releaseGfxSlot(shop->unk22);
            closeWindow(shop->window);
            if (data_021f5d08.chars != 0xFFFF) {
                freeShopBg(&data_021f5d08);
            }
            bg = &SHOP_BGS[SHOP_BG_COUNT - 1];
            for (i = SHOP_BG_COUNT - 1; i >= 0; i--) {
                if (bg->chars != 0xFFFF) {
                    freeShopBg(bg);
                }
                bg--;
            }
            for (i = 0xFF; i >= 0; i--) {
                releaseSlotSprite(i);
            }
            func_020a98a8(2);
            func_020a9844(2);
            func_0207e6bc(1);
            if (!(shop->unk1C & 1)) {
                setScriptGlobal(0xFFFF8025, -1);
            }
            endTask(getCurrentTask());
            shop->state = 8;
            break;
    }
}

/* An entry of data_0213854c. */
s32 func_020cf364(s32 index) {
    return data_0213854c[index];
}

/* Fills the three upgrades of a farm with their prices (func_020cf284) and
 * returns their count. */
u8 fillFarmUpgrades(s32 farm) {
    u8 i;
    struct ShopUpgrade *upgrade;

    upgrade = FARM_UPGRADES;
    for (i = 0; i <= SHOP_UPGRADE_COUNT - 1; i++) {
        upgrade->unk0  = i + 12;
        upgrade->price = func_020cf284(farm, i, 0);
        upgrade++;
    }
    return i;
}

/* Writes label 0x1C and the food the player has in the shop's window. */
void func_020cf0d8(struct Shop *shop) {
    u16 text[18];
    s32 food;

    func_020a68cc(shop->window, 6, 0x11, 6, 2, func_0209ec68(0x1C), 0x11C, 0xB, 3, 2, 0);
    food    = addFood(0);
    text[0] = TEXT_UNKE9;
    formatNumber(food, 6, &text[1], 0);
    text[7] = TEXT_UNKE9;
    text[8] = 0x35;
    text[9] = TEXT_END;
    func_020a68cc(shop->window, 0xC, 0x11, 7, 2, text, 0x128, 0xB, 3, 2, 2);
}

/* The farm goods shop (mode 5): runs its state. */
void runFarmGoodsShop(struct Shop *shop) {
    switch (shop->state) {
        case 0:
            func_020cedc0(shop);
            break;
        case 1:
            func_020cecc4(shop);
            break;
        case 2:
            func_020cea44(shop);
            break;
        case 4:
            func_020ce610(shop);
            break;
        case 5:
            func_020ce478(shop);
            break;
        case 6:
            func_020ce1d8(shop);
            break;
        case 7:
            func_020ce044(shop);
            break;
    }
}

/* The farm goods shop's fade in, then its menu (state 2). */
void func_020cecc4(struct Shop *shop) {
    switch (shop->step) {
        case 0:
            shop->timer = SHOP_FADE_FRAMES;
            showMainLayers(0x1F);
            fadeInMainPalette(0, 0x100, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            fadeInMainPalette(0x900, 0x100, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            fadeInMainPalette(0xA00, 0x800, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            shop->step++;
            return;
        case 1:
            shop->timer--;
            if (shop->timer <= 0) {
                shop->choice = 0;
                shop->state  = 2;
            }
            return;
    }
}

/* The farm goods shop's last state: fades out, takes the shop down and ends
 * its task. */
void func_020ce044(struct Shop *shop) {
    s32 i;
    struct ShopBg *bg;

    switch (shop->step) {
        case 0:
            shop->timer = SHOP_FADE_FRAMES;
            fadeOutMainPalette(0, 0x100, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            fadeOutMainPalette(0x900, 0x100, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            fadeOutMainPalette(0xA00, 0x800, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            shop->step++;
            break;
        case 1:
            shop->timer--;
            if (shop->timer > 0) {
                break;
            }
            deleteMainActors();
            endMainActorTask();
            func_ov005_02289a34();
            func_ov005_0228c7f0();
            releaseGfxSlot(shop->unk22);
            closeWindow(shop->window);
            if (data_021f5d08.chars != 0xFFFF) {
                freeShopBg(&data_021f5d08);
            }
            bg = &SHOP_BGS[SHOP_BG_COUNT - 1];
            for (i = SHOP_BG_COUNT - 1; i >= 0; i--) {
                if (bg->chars != 0xFFFF) {
                    freeShopBg(bg);
                }
                bg--;
            }
            for (i = 0xFF; i >= 0; i--) {
                releaseSlotSprite(i);
            }
            func_020a98a8(2);
            func_020a9844(2);
            func_0207e6bc(1);
            endTask(getCurrentTask());
            shop->state = 8;
            break;
    }
}

/* Fills the farm goods for sale from the ids func_0207e5a0 holds, with each
 * one's price. */
void loadFarmGoods(void) {
    s32 i;
    struct ShopEntry *entry;
    u16 *ids;

    entry = FARM_GOODS;
    ids   = func_0207e5a0();
    for (i = 0; i < SHOP_FARM_GOODS_COUNT; i++) {
        entry->id    = *ids;
        entry->price = getFarmGoodsData(entry->id)->price;
        entry++;
        ids++;
    }
}

/* Puts the farm goods for sale in the shop's list and returns their count. */
s32 fillFarmGoodsBuyList(void) {
    s32 i;
    struct ShopEntryBytes *dst, *src;

    dst = (struct ShopEntryBytes *) SHOP_LIST;
    src = (struct ShopEntryBytes *) FARM_GOODS;
    for (i = 0; i < SHOP_FARM_GOODS_COUNT; i++) {
        *dst = *src;
        dst++;
        src++;
    }
    return SHOP_FARM_GOODS_COUNT;
}

/* Puts the farm's goods in the shop's list, at their selling prices, and
 * returns their count. */
s16 fillFarmGoodsSellList(void) {
    s32 i;
    s16 count;
    struct ShopEntry *entry;
    struct FarmGoods *goods;

    count = countPlayerGoods();
    entry = SHOP_LIST;
    for (i = 0; i < count; i++) {
        goods        = getFarmGoodsAt((s8) i);
        entry->id    = goods->dataIndex;
        entry->unk8  = goods->id;
        entry->unkC  = goods->unk8;
        entry->price = getFarmGoodsData(entry->id)->sellPrice;
        entry++;
    }
    return count;
}
