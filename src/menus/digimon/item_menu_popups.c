#include "menus/digimon/item_menu_popups.h"
#include "engine/data.h"
#include "engine/sprite/sprite_create.h"
#include "engine/sprite/sprite_draw.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "menus/digimon/data.h"
#include "menus/digimon/item_menu_icons.h"
#include "menus/widgets/icon_display.h"
#include "menus/widgets/item_menu_panel.h"

/* Opens the menu of three options beside the row of list0's cursor. */
void func_ov006_0227ec68(struct ItemMenu *menu) {
    s32 i;

    menu->popupSprite = createMainSprite(0x3CE, 0x30, (s16) ((menu->list0->cursor * 2 + 5) * 8), 0xA, 0);
    func_0203e878(menu->popupSprite, 0x3F);
    menu->popup->cursor = menu->popup->prevCursor = 0;
    menu->popupButtons                            = createButtonGroup(0x10, 0, func_ov006_0227eac4);
    for (i = 0; i < 3; i++) {
        addRectButton((s16) (data_ov006_0229efb8[i * 4] + 0x30),
                      (s16) (data_ov006_0229efb8[i * 4 + 1] + (menu->list0->cursor * 2 + 5) * 8 + 0x10),
                      data_ov006_0229efb8[i * 4 + 2], data_ov006_0229efb8[i * 4 + 3], 0, menu->popupButtons);
    }
}

/* Closes the menu of three options. */
void func_ov006_0227ec34(struct ItemMenu *menu) {
    freeMainSprite(menu->popupSprite);
    menu->popupSprite = -1;
    if (menu->popupButtons != -1) {
        closeButtonGroup(menu->popupButtons);
        menu->popupButtons = -1;
    }
}

/* Opens a dialog of two choices, answered through func_ov006_0227e804. */
void func_ov006_0227e9dc(struct ItemMenu *menu) {
    s32 i;
    struct ButtonGroup *group;

    menu->dialogSprite = createMainSprite(0x3DE, 0, 0, 0xA, 0);
    func_0203e878(menu->dialogSprite, 0x3F);
    menu->popup->cursor = menu->popup->prevCursor = 0;
    menu->popupButtons                            = createButtonGroup(0x10, 0, func_ov006_0227e804);
    for (i = 0; i < 2; i++) {
        addRectButton(data_ov006_0229ef78[i * 4], data_ov006_0229ef78[i * 4 + 1], data_ov006_0229ef78[i * 4 + 2],
                      data_ov006_0229ef78[i * 4 + 3], 0, menu->popupButtons);
    }
    group = findTask(menu->popupButtons);
    /* func_ov006_0227e804 keeps its step in the first byte of the work. */
    *(u8 *) group->work = 0;
}

/* Closes the dialog of two choices. */
void func_ov006_0227e9a8(struct ItemMenu *menu) {
    freeMainSprite(menu->dialogSprite);
    menu->dialogSprite = -1;
    if (menu->popupButtons != -1) {
        closeButtonGroup(menu->popupButtons);
        menu->popupButtons = -1;
    }
}

/* Clears the icons of both sets, closes the three displays of ITEM_MENU_PANELS
 * and the one of ICON_DISPLAY (closeIconDisplay), and removes the unk50
 * buttons. */
void func_ov006_0227e520(struct ItemMenu *menu) {
    func_ov006_0227d600(0, 0, 0, 0, 0, 0);
    func_ov006_0227d600(0, 0, 0, 0, 0, 1);
    freeItemMenuPanelSprites(0);
    freeItemMenuPanelSprites(1);
    freeItemMenuPanelSprites(2);
    closeItemMenuPanel(0);
    closeItemMenuPanel(1);
    closeItemMenuPanel(2);
    closeIconDisplay();
    if (menu->unk50 != -1) {
        closeButtonGroup(menu->unk50);
        menu->unk50 = -1;
    }
}
