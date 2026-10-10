#include "menus/field_menu/party_panel.h"
#include "engine/bg/bg_affine.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite_create.h"
#include "engine/text/font.h"
#include "engine/text/text_object.h"
#include "engine/window/window_draw.h"
#include "menus/field_menu/panel.h"

/* Frees every panel of both kinds. */
void closePanels(void) {
    freePartyPanelSprites(0);
    closePartyPanel(0);
    freePartyPanelSprites(1);
    closePartyPanel(1);
    freePartyPanelSprites(2);
    closePartyPanel(2);
    freePanelSprite(0);
    closePanel(0);
    freePanelSprite(1);
    closePanel(1);
    freePanelSprite(2);
    closePanel(2);
}

/* Sets up slot `slot` of func_020aa29c with the files of background 0x61. */
void func_02049f18(s8 slot, s32 unk1) {
    data_021b4a08 = slot;
    func_020aa29c(func_0204871c(0x61), slot, -1, unk1);
}

/* Frees that slot, if one is set up (func_020a9610). */
void func_02049edc(void) {
    if (data_021b4a08 == -1) {
        return;
    }
    func_020a9610(data_021b4a08);
    data_021b4a08 = -1;
}

/* Clears a party panel's area of its window, frees its images and empties
 * it. */
void closePartyPanel(s16 index) {
    struct PartyPanel *panel = &PARTY_PANELS[index];

    if (!(panel->flags & PANEL_IN_USE)) {
        return;
    }
    func_020a8a98(panel->window, panel->x, panel->y, PARTY_PANEL_WIDTH, PARTY_PANEL_HEIGHT, 0);
    redrawWindow(panel->window);
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
    if (panel->images[3].width != 0 && panel->images[3].height != 0) {
        freeWindowImage(&panel->images[3]);
        func_02030f18(&panel->images[3], 0, sizeof(struct WindowImage));
    }
    func_02030f18(panel, 0, sizeof(struct PartyPanel));
}

/* Frees a party panel's sprites. */
void freePartyPanelSprites(s16 index) {
    struct PartyPanel *panel = &PARTY_PANELS[index];

    if (!(panel->flags & PANEL_IN_USE)) {
        return;
    }
    if (panel->screenFlags & PANEL_ON_SUB_SCREEN) {
        freeSubSprite(panel->sprite);
        freeSubSprite(panel->sprite1);
        freeSubSprite(panel->sprite2);
    } else {
        freeMainSprite(panel->sprite);
        freeMainSprite(panel->sprite1);
        freeMainSprite(panel->sprite2);
    }
}
