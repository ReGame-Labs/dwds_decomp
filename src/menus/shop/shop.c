#include "menus/shop/shop.h"
#include "battle/sprite_slots.h"
#include "engine/data.h"
#include "engine/system/display.h"
#include "engine/system/system.h"
#include "engine/text/font.h"

/* Opens the shop: starts its task with nothing loaded yet. */
void openShop(void) {
    struct Shop *shop = createTask(runShop, 0x117);
    s32 i;
    s32 j;

    shop->unk1C   = 0;
    shop->opening = 0;
    shop->state   = 0;
    shop->step    = 0;
    shop->unk27   = 0;
    for (i = 0; i <= 7; i++) {
        data_021f5cd4[i] = 0;
        for (j = 0; j < 10; j++) {
            data_021f7128[i][j][0] = 0xFFFF;
            data_021f6c28[i][j][0] = 0xFFFF;
        }
    }
    initSpriteSlots();
    func_020a9c40(2, 0xE, 0xF);
    func_020a9ae0(2, 0xF, 0xF);
    for (i = 0; i < SHOP_BG_COUNT; i++) {
        SHOP_BGS[i].chars = 0xFFFF;
    }
    data_021f5d08.chars = 0xFFFF;
    hideMainLayers(0x1F);
}
