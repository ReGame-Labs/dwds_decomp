#include "farm/goods_list.h"
#include "engine/palette/palette_buffers.h"
#include "engine/palette/palette_fade.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/text/text_banks.h"
#include "engine/ui/buttons.h"
#include "engine/window/window.h"
#include "farm/data.h"
#include "farm/farm_groups.h"
#include "farm/item_info.h"

/* Moves the color cycling to the cursor's row: each row is drawn in a color of
 * its own, the 10th of the palette after the list's. */
void func_ov005_0227b5f0(struct ItemList *list) {
    if (list->cursorEffect != -1) {
        restoreSubPalette((s16) ((list->palette + 1) * 16), 16);
        stopSubPaletteEffects(list->cursorEffect);
        list->cursorEffect = -1;
    }
    if (list->count == 0) {
        return;
    }
    list->cursorEffect = func_020839c8((s16) (list->cursor + ((list->palette + 1) * 16 + 10)), 1, 0x7FFF, 0x50, 1, 2, 10000);
}

/* Shows the items of another farm, from the given entry and row on. */
void func_ov005_0227b4e4(s32 owner, s16 scroll, s16 cursor) {
    struct ItemList *list;
    s32 i;
    struct Window *window;
    struct DigimonItem *entry;

    list         = findTask(data_ov005_022a1d30);
    window       = getWindow(list->window);
    list->owner  = owner;
    list->scroll = scroll;
    list->cursor = cursor;
    list->count  = func_ov005_0227c1bc(owner, list->entries);
    entry        = getDigimonItem(list->entries[scroll + cursor]);
    func_ov005_0227c184(entry == NULL ? -1 : entry->item);
    func_ov005_0227b69c(list);
    func_ov005_0227b5f0(list);
    func_020b1168(-1, list->inputTask);
    for (i = 0; i < 6 && i < list->count; i++) {
        list->rowButtons[i] =
            addRectButton((s16) (window->x * 8), (s16) ((window->y + i * 2 + 1) * 8), 0xE0, 0x10, 0, list->inputTask);
    }
}

/* Closes the item list. */
void func_ov005_0227b480(void) {
    struct ItemList *list;

    list = findTask(data_ov005_022a1d30);
    stopSubPaletteEffects(list->cursorEffect);
    closeButtonGroup(list->inputTask);
    closeWindow(list->window);
    func_020a9844(2);
    func_020a9844(1);
    releaseGfxSlot(list->gfxSlot);
    endTask(list);
    freeTextBank();
    data_ov005_022a1d30 = 0;
}
