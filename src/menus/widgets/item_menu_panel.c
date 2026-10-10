#include "menus/widgets/item_menu_panel.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite_create.h"
#include "engine/text/text_object.h"

/* Frees an item panel's images and empties it. */
void closeItemMenuPanel(s16 index) {
    struct ItemMenuPanel *panel = &ITEM_MENU_PANELS[index];

    if (!(panel->flags & PANEL_IN_USE)) {
        return;
    }
    if (panel->images[0].width != 0 && panel->images[0].height != 0) {
        freeWindowImage(&panel->images[0]);
        func_02030f18(&panel->images[0], 0, sizeof(struct WindowImage));
    }
    if (panel->images[1].width != 0 && panel->images[1].height != 0) {
        freeWindowImage(&panel->images[1]);
        func_02030f18(&panel->images[1], 0, sizeof(struct WindowImage));
    }
    if (panel->images[2].width != 0 && panel->images[2].height != 0) {
        freeWindowImage(&panel->images[2]);
        func_02030f18(&panel->images[2], 0, sizeof(struct WindowImage));
    }
    func_02030f18(panel, 0, sizeof(struct ItemMenuPanel));
}

/* Frees an item panel's sprites. */
void freeItemMenuPanelSprites(s16 index) {
    struct ItemMenuPanel *panel = &ITEM_MENU_PANELS[index];

    if (!(panel->flags & PANEL_IN_USE)) {
        return;
    }
    if (panel->screenFlags & PANEL_ON_SUB_SCREEN) {
        freeSubSprite(panel->sprite);
        freeSubSprite(panel->sprite2);
    } else {
        freeMainSprite(panel->sprite);
        freeMainSprite(panel->sprite2);
    }
}
