#include "farm/goods_placing.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "farm/data.h"
#include "farm/farm_queries.h"
#include "farm/goods_panel.h"
#include "field/actors/actor_files.h"
#include "nitro/pad.h"

/* Frees the actors of the goods being placed. */
void func_ov005_0228d8f8(struct GoodsPlacement *placement) {
    s32 i;

    for (i = 0; i < 2; i++) {
        u16 actor = placement->actors[i];

        if (actor == 0xFFFF) {
            return;
        }
        func_020c6fb8(actor);
    }
}

/* The handler of the placing's touch buttons: B or button 0 cancels, A or a
 * touch picks the spot under the stylus. Plays sound 3 to cancel and 1 to
 * pick. */
void func_ov005_0228d830(s16 touched, s16 cursor, struct ButtonGroup *buttons) {
    struct GoodsPlacement *placement;
    u16 keys;

    findTask(FARM_TASK_ID);
    findTask(data_021e5cb4);
    placement = findTask(data_021e5cc4);
    getFarmLayout((s8) placement->layout);
    keys = getPadPressed();
    if ((keys & PAD_BUTTON_B) || touched == 0) {
        playSound(3);
        placement->result = 9999;
        return;
    }
    if (takeButtonGroupTap(data_021e5cac) == 0 && !(keys & PAD_BUTTON_A)) {
        return;
    }
    playSound(1);
    if (touched == 0) {
        placement->result = 9999;
        return;
    }
    if (placement->spot != -1) {
        placement->result = placement->spot;
    }
}

/* Opens the panel of the goods, or turns it to them if it is open. */
void openGoodsPanel(s32 goodsId, s8 view, s8 palette) {
    struct GoodsPanel *panel;
    s32 i;

    if (data_021e5cb8 != 0) {
        setGoodsPanelGoods(goodsId);
        return;
    }
    panel         = createTask(func_ov005_0228d164, 0x10F);
    data_021e5cb8 = getTaskId(panel);
    panel->state  = 0;
    panel->wait   = 0;
    panel->view   = view;
    for (i = 0; i < 2; i++) {
        panel->actors[i] = 0xFFFF;
    }
    panel->actorWindow = 0xFF;
    panel->infoWindow  = 0xFF;
    panel->nameWindow  = 0xFF;
    panel->palette     = palette;
    panel->goodsId     = goodsId;
    panel->next        = -1;
}
