#include "farm/panel_status.h"
#include "engine/data.h"
#include "engine/window/window.h"
#include "farm/data.h"
#include "menus/widgets/status_window.h"

/* Shows the digimon's status in the panel's window with the status display of
 * slot 0, made the first time and refreshed after; removes it for NULL. */
void func_ov005_022805e0(struct DigimonPanel *panel, struct Digimon *digimon) {
    struct StatusParams params;
    struct Window *window;

    window = getWindow(panel->window);
    if (digimon == NULL) {
        if (panel->statusUp == 0) {
            return;
        }
        freeStatusWindowSprites(0);
        func_020587fc(0);
        panel->statusUp = 0;
        return;
    }
    if (panel->statusUp != 0) {
        func_02058590(0, digimon);
        return;
    }
    if (panel->mode == 0) {
        params.y    = 7;
        params.unk8 = 3;
    } else {
        params.y    = 6;
        params.unk8 = 2;
    }
    params.window   = panel->window;
    params.x        = 2;
    params.unk6     = 2;
    params.digimon  = digimon;
    params.unk10    = 3;
    params.unk12    = 4;
    params.unk14    = 5;
    params.unk16    = 5;
    params.unk18[0] = 0;
    params.unk18[1] = 0;
    params.unk18[2] = 0;
    params.unk18[3] = 0;
    params.unk18[4] = 0;
    params.unk22    = 1;
    params.unk24    = window->unk2;
    params.unk26    = window->unk8;
    params.unk28    = 2;
    params.unk2A    = 0;
    params.unk2C    = 1;
    drawStatusWindow(0, &params);
    panel->statusUp = 1;
}

/* The same for panel 0xA, with slot 1. */
void func_ov005_022804c0(struct DigimonPanel *panel, struct Digimon *digimon) {
    struct StatusParams params;
    struct Window *window;

    window = getWindow(panel->window);
    if (digimon == NULL) {
        if (panel->statusUp == 0) {
            return;
        }
        freeStatusWindowSprites(1);
        func_020587fc(1);
        panel->statusUp = 0;
        return;
    }
    if (panel->statusUp != 0) {
        func_02058590(1, digimon);
        return;
    }
    if (panel->mode == 0) {
        params.y    = 7;
        params.unk8 = 3;
    } else {
        params.y    = 6;
        params.unk8 = 2;
    }
    params.window   = panel->window;
    params.x        = 2;
    params.unk6     = 2;
    params.digimon  = digimon;
    params.unk10    = 3;
    params.unk12    = 4;
    params.unk14    = 5;
    params.unk16    = 5;
    params.unk18[0] = 0;
    params.unk18[1] = 0;
    params.unk18[2] = 0;
    params.unk18[3] = 0;
    params.unk18[4] = 0;
    params.unk22    = 2;
    params.unk24    = window->unk2;
    params.unk26    = window->unk8;
    params.unk28    = 2;
    params.unk2A    = 1;
    params.unk2C    = 1;
    drawStatusWindow(1, &params);
    panel->statusUp = 1;
}
