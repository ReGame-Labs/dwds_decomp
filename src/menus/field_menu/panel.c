#include "menus/field_menu/panel.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite_create.h"
#include "engine/text/text_object.h"
#include "engine/window/window_draw.h"

/* Clears a panel's area of its window, frees its images and empties it. */
void closePanel(s16 index) {
    struct Panel *panel = &PANELS[index];

    if (!(panel->flags & PANEL_IN_USE)) {
        return;
    }
    func_020a8a98(panel->window, panel->x, panel->y, PANEL_WIDTH, PANEL_HEIGHT, 0);
    redrawWindow(panel->window);
    if (panel->images[0].width != 0 && panel->images[0].height != 0) {
        freeWindowImage(&panel->images[0]);
        func_02030f18(&panel->images[0], 0, sizeof(struct WindowImage));
    }
    if (panel->images[1].width != 0 && panel->images[1].height != 0) {
        freeWindowImage(&panel->images[1]);
        func_02030f18(&panel->images[1], 0, sizeof(struct WindowImage));
    }
    func_02030f18(panel, 0, sizeof(struct Panel));
}

/* Frees a panel's sprite. */
void freePanelSprite(s16 index) {
    struct Panel *panel;

    panel = &PANELS[index];
    if (!(panel->flags & PANEL_IN_USE)) {
        return;
    }
    if (panel->screenFlags & PANEL_ON_SUB_SCREEN) {
        freeSubSprite(panel->sprite);
    } else {
        freeMainSprite(panel->sprite);
    }
}
