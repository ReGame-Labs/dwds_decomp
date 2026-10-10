#include "menus/shop/shop_ui.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/system/system.h"
#include "menus/shop/shop.h"

/* Frees a background of the shop: its characters, its files, and what it put
 * on the screen. */
void freeShopBg(struct ShopBg *bg) {
    void *file;

    func_02085710(bg->bg, bg->chars);
    file = bg->graphics.paletteFile;
    heapFree(file);
    file = bg->graphics.charFile;
    heapFree(file);
    file = bg->graphics.screenFile;
    heapFree(file);
    func_02086758(bg->bg, 0, 0, 0x20, 0x18, 0);
}
