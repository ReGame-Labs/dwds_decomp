#include "farm/goods_panel.h"
#include "engine/bg/bg_affine.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/window/window.h"
#include "farm/data.h"
#include "farm/farm_screen.h"
#include "farm/farm_task.h"
#include "field/actors/actor_files.h"

/* Keeps the window's first sprite by its right side. */
void func_ov005_0228c950(u16 flags, struct Window *window) {
    if (window->sprites[0] == 0xFF) {
        return;
    }
    setMainSpritePos(window->sprites[0], (window->x + 17) * 8, (window->y + 2) * 8);
}

/* Turns the goods panel to other goods, once its task gets to them. */
void setGoodsPanelGoods(s32 goodsId) {
    struct GoodsPanel *panel = findTask(data_021e5cb8);

    if (panel != NULL) {
        panel->next = goodsId;
    }
}

/* Switches the goods panel to its other text. */
void toggleGoodsPanelText(void) {
    struct GoodsPanel *panel = findTask(data_021e5cb8);

    if (panel == NULL) {
        return;
    }
    if (panel->state != 300) {
        return;
    }
    if (panel->view) {
        panel->view = 0;
    } else {
        panel->view = 1;
    }
    panel->state = 700;
}

/* Sorts the goods list the next of its three ways. */
void sortGoodsList(void) {
    struct Task0228e23c *list = findTask(data_021e5cb4);
    struct GoodsPanel *panel  = findTask(data_021e5cb8);

    if (list == NULL) {
        return;
    }
    list->sort++;
    if (list->sort > 2) {
        list->sort = 0;
    }
    panel->state = 800;
}

/* Frees a main screen sprite, if there is one, and marks it none. */
void func_ov005_0228c7c4(u16 *sprite) {
    if (*sprite != 0xFFFF) {
        freeMainSprite(*sprite);
    }
    *sprite = 0xFFFF;
}

/* Frees a sub screen sprite, if there is one, and marks it none. */
void func_ov005_0228c798(u16 *sprite) {
    if (*sprite != 0xFFFF) {
        freeSubSprite(*sprite);
    }
    *sprite = 0xFFFF;
}

/* Moves the window to the bottom of the screen when the goods' icon is at the
 * top, and to the top when the icon is at the bottom. */
void func_ov005_0228afd8(u16 flags, struct Window *window) {
    struct FarmTask *task = findTask(FARM_TASK_ID);
    struct Sprite *icon   = getSubSprite(task->icon);
    s16 y;

    if (task == NULL || icon == NULL) {
        return;
    }
    y = icon->y;
    if (y < 0x48) {
        func_020a8e3c(window->index, 4, 0x15);
    } else if (y > 0x78) {
        func_020a8e3c(window->index, 4, 1);
    }
}

/* Frees the actors of data_ov005_022a1d4c. */
void func_ov005_0228accc(void) {
    s32 i;

    for (i = 0; i < FARM_SLOT_COUNT; i++) {
        if (data_ov005_022a1d4c[i] != 0xFFFF) {
            func_020c7060(data_ov005_022a1d4c[i]);
            data_ov005_022a1d4c[i] = 0xFFFF;
        }
    }
}

/* Frees the actors of the farm's digimon. */
void func_ov005_0228ac88(void) {
    s32 i;

    for (i = 0; i < FARM_SLOT_COUNT; i++) {
        if (FARM_DIGIMON_ACTORS[i] != 0xFFFF) {
            func_020c6fb8(FARM_DIGIMON_ACTORS[i]);
            FARM_DIGIMON_ACTORS[i] = 0xFFFF;
        }
    }
}

/* Releases the graphics of BGs 1, 2, 4 and 5 (func_020a98a8) and of 0 to 2, 4
 * and 5 (func_020a9844). */
void func_ov005_02289b28(void) {
    func_020a98a8(4);
    func_020a98a8(5);
    func_020a98a8(1);
    func_020a98a8(2);
    func_020a9844(4);
    func_020a9844(5);
    func_020a9844(0);
    func_020a9844(1);
    func_020a9844(2);
}

/* Loads the background of entry 0x39 of data_0213537c. */
void func_ov005_02289a78(void) {
    s32 *files = func_0204871c(0x39);

    data_021e5cd8.paletteFile = (void *) loadTempPaletteFile(&data_021e5cd8.palette, files[0]);
    data_021e5cd8.charFile    = (void *) loadTempCharFile(&data_021e5cd8.chars, files[1]);
    data_021e5cd8.screenFile  = (void *) loadTempScreenFile(&data_021e5cd8.screen, files[2]);
    data_021e5c9c             = func_02085f34(&data_021e5cd8, 3, 0xFFFF, 2, 0, 0, 0x20, 0x18, 0, 0);
}

/* Frees the background of func_ov005_02289a78. */
void func_ov005_02289a34(void) {
    if (data_021e5c9c != 0xFFFF) {
        func_0208577c(3, data_021e5c9c);
        data_021e5c9c = 0xFFFF;
    }
}

/* Opens the status window of the farm in a slot. */
void openFarmStatusBySlot(s32 slot, s8 gfxSlot) {
    openFarmStatus(0, getGroupId(slot), gfxSlot, 0, 3);
}

/* The same in mode 1. */
void func_ov005_022899cc(s32 slot, s8 gfxSlot) {
    openFarmStatus(1, getGroupId(slot), gfxSlot, 0, 3);
}

/* Opens the status window of the farm with an id. */
void openFarmStatusById(s32 farm, s8 gfxSlot) {
    openFarmStatus(0, farm, gfxSlot, 0, 3);
}

/* Opens the status window of the farm makeTempFarm made in a buffer
 * (id -2), at its address. */
void func_ov005_02289964(s32 value, s8 gfxSlot) {
    TEMP_FARM = value;
    openFarmStatus(0, -2, gfxSlot, 0, 3);
}

/* Draws the status of the farm in a slot in its window. */
void drawFarmStatusBySlot(s32 slot) {
    drawFarmStatus(getGroupId(slot));
}

/* Opens the window of func_ov005_02288e40, unless it is open, and has that
 * function fill it for index. */
void func_ov005_02289044(s32 index, s8 gfxSlot) {
    struct WindowParams params;

    if (data_021e5c8c == 0xFF) {
        params.flags    = 0;
        params.x        = 8;
        params.y        = 4;
        params.gfxSlot  = gfxSlot;
        params.unk8     = 0;
        params.unkA     = 0x15;
        params.width    = 0xF;
        params.height   = 0x10;
        params.unk10    = 0;
        params.unk12    = 0;
        params.unk14    = 0x72;
        params.unk16    = 0xFFFF;
        params.unk18    = 0xFFFF;
        params.callback = func_ov005_02289004;
        data_021e5c8c   = func_020a91c4(&params);
        getWindow(data_021e5c8c);
    }
    func_ov005_02288e40(index);
}

/* Keeps the window's first sprite by its top left corner. */
void func_ov005_02289004(u16 flags, struct Window *window) {
    setMainSpritePos(window->sprites[0], (window->x + 3) * 8 - 4, (window->y + 4) * 8 - 0x10);
}
