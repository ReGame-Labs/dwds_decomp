#include "menus/widgets/digimon_detail.h"
#include "engine/data.h"
#include "engine/sprite/sprite_create.h"

/* Returns 0x58, as func_02058a24 returns 0x7C for the status windows. */
s32 func_02059d84(void) {
    return 0x58;
}

/* Frees a details display's sprites. */
void freeDigimonDetailSprites(s16 index) {
    struct DigimonDetail *display = &DIGIMON_DETAILS[index];
    s32 i;

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    if (display->screenFlags & PANEL_ON_SUB_SCREEN) {
        for (i = 0; i < 2; i++) {
            freeSubSprite(display->sprites[i]);
        }
        for (i = 0; i < 3; i++) {
            freeSubSprite(display->sprites2[i]);
        }
    } else {
        for (i = 0; i < 2; i++) {
            freeMainSprite(display->sprites[i]);
        }
        for (i = 0; i < 3; i++) {
            freeMainSprite(display->sprites2[i]);
        }
    }
}

/* Shows another Digimon (or none) in a details display, and sets up its gauge
 * of the Digimon's unk72 out of 100. */
void setDigimonDetailDigimon(s16 index, struct Digimon *digimon) {
    struct DigimonDetail *display = &DIGIMON_DETAILS[index];
    struct GaugeParams *gauge;
    struct Digimon *shown;

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    display->flags |= PANEL_CHANGED;
    display->digimon = digimon;
    gauge            = &display->gauge;
    gauge->unk0      = 2;
    gauge->unk1      = display->unkD8;
    gauge->unk2      = display->unkDA + 0x51;
    gauge->unk4      = display->unk26;
    gauge->unk5      = 0;
    gauge->unk6      = 4;
    shown            = display->digimon;
    gauge->value     = shown != NULL ? shown->unk72 : 0;
    gauge->unkC      = 0;
    gauge->max       = 100;
}

/* Sets a details display's unkCC to unkD4. */
void func_02059acc(s16 index, s16 unkCC, s16 unkCE, s16 unkD0, u16 unkD2, u16 unkD4) {
    struct DigimonDetail *display = &DIGIMON_DETAILS[index];

    if (display->flags & PANEL_IN_USE) {
        display->unkCC = unkCC;
        display->unkCE = unkCE;
        display->unkD0 = unkD0;
        display->unkD2 = unkD2;
        display->unkD4 = unkD4;
    }
}
