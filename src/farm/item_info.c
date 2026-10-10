#include "farm/item_info.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/text/text_banks.h"
#include "engine/window/window.h"
#include "farm/data.h"

/* Opens the window that describes an item. */
void func_ov005_0227c4c4(s32 item, s8 palette, s16 unk2A) {
    struct ItemInfo *info;

    info                = createTask(&func_ov005_0227c364, 0x10C);
    data_ov005_022a1d18 = getTaskId(info);
    info->state         = 0;
    info->wait          = 0;
    info->item          = item;
    info->palette       = palette;
    info->unk2A         = unk2A;
}

/* Turns the item's window to another item. */
void func_ov005_0227c184(s32 item) {
    struct ItemInfo *info;

    info       = findTask(data_ov005_022a1d18);
    info->item = item;
    func_ov005_0227c23c(info->window, info->item);
    freeTextBank();
}

/* Closes the item's window. */
void func_ov005_0227c140(void) {
    struct ItemInfo *info;

    info = findTask(data_ov005_022a1d18);
    closeWindow(info->window);
    releaseGfxSlot(info->gfxSlot);
    endTaskById(data_ov005_022a1d18);
    data_ov005_022a1d18 = 0;
}

/* Opens the list of the items given to the digimon of the farm with the id
 * owner, from the given entry and row on. */
void func_ov005_0227c0c4(s32 owner, s16 scroll, s16 cursor, s8 palette, s8 unk2D, u16 unk2E) {
    struct ItemList *list;

    list                = createTask(&func_ov005_0227bcec, 0x10D);
    data_ov005_022a1d30 = getTaskId(list);
    list->state         = 0;
    list->wait          = 0;
    list->owner         = owner;
    list->scroll        = scroll;
    list->cursor        = cursor;
    list->palette       = palette;
    list->unk2D         = unk2D;
    list->unk2E         = unk2E;
    list->count         = func_ov005_0227c1bc(owner, list->entries);
}
