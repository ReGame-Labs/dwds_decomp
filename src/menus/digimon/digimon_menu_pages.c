#include "menus/digimon/digimon_menu_pages.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "menus/digimon/data.h"
#include "menus/digimon/item_menu_open.h"
#include "menus/digimon/ov006_02281f70.h"
#include "menus/digimon/ov006_0228666c.h"
#include "menus/widgets/item_displays.h"
#include "menus/widgets/skill_displays.h"
#include "menus/widgets/status_window.h"
#include "nitro/g2.h"

/* Shows the Digimon in three displays: func_02054e00's, func_02056940's of its
 * first technique once it has its species' level for it, and its status. */
void func_ov006_02287af4(struct DigimonMenu *menu) {
    struct StatusParams status;
    struct Params02056940 second;
    struct Params02054e00 first;
    struct SpeciesData *species;
    struct Digimon *digimon;

    species        = loadSpeciesData(menu->work->digimon->unk4);
    first.digimon  = menu->work->digimon;
    first.window   = menu->windows[3];
    first.unk10    = 3;
    first.x        = 1;
    first.y        = 0;
    first.unkC     = 2;
    first.unkE     = 4;
    first.unk12    = 5;
    first.unk14[0] = 6;
    first.unk14[1] = 7;
    first.unk14[2] = 8;
    first.unk14[3] = 9;
    first.unk14[4] = 0xA;
    first.unk14[5] = 0xB;
    first.unk20    = 2;
    first.unk22    = 1;
    first.unk24    = 2;
    first.unk26    = 0;
    func_02054e00(0, &first);
    digimon = menu->work->digimon;
    if (digimon->level >= species->unk34) {
        second.item = digimon->unk54[0];
    } else {
        second.item = 0xFFFF;
    }
    second.window = menu->windows[2];
    second.x      = 0;
    second.y      = 4;
    second.unk6   = 1;
    second.unk8   = 1;
    second.unkC   = 0;
    second.unk10  = 1;
    second.unkE   = 2;
    second.unk12  = 2;
    second.unk14  = 0x50;
    second.unk16  = 2;
    second.unk18  = 1;
    func_02056940(0, &second);
    func_020e23c0(&status, 0, sizeof(status));
    status.digimon = menu->work->digimon;
    status.window  = menu->windows[1];
    status.x       = 1;
    status.y       = 5;
    status.unk10   = 3;
    status.unk6    = 1;
    status.unk8    = 1;
    status.unk12   = 4;
    status.unk14   = 5;
    status.unk16   = 0xE;
    status.unk24   = 2;
    status.unk26   = 0xDA;
    status.unk28   = 2;
    status.unk2A   = 1;
    status.unk22   = 2;
    status.unk2C   = 1;
    drawStatusWindow(0, &status);
}

/* Closes the displays of func_ov006_02287af4. */
void func_ov006_02287ab4(void) {
    freeStatusWindowSprites(0);
    func_020587fc(0);
    freeAbilityDisplaySprites(0);
    closeAbilityDisplay(0);
    func_02054cb8(0);
    closeAbilityListDisplay(0);
}

/* Shows the Digimon in func_02053200's display, its first learned trait in
 * func_020539ac's, its species' trait in the sixth window and its status. */
void func_ov006_022877cc(struct DigimonMenu *menu) {
    struct Params020539ac second;
    struct Params02053200 first;
    struct StatusParams status;
    struct SpeciesData *species;

    species       = loadSpeciesData(menu->work->digimon->unk4);
    first.digimon = menu->work->digimon;
    first.window  = menu->windows[4];
    first.x       = 0;
    first.y       = 0;
    first.unkC    = 2;
    first.unkE    = 2;
    first.unk10   = 1;
    first.unk12   = 2;
    first.unk14   = 0;
    func_02053200(0, &first);
    second.unkA   = menu->work->digimon->unk22[0];
    second.unkC   = menu->work->digimon->unk2C[0];
    second.window = menu->windows[3];
    second.x      = 1;
    second.unk6   = 1;
    second.unk8   = 1;
    second.unk12  = 1;
    second.y      = 4;
    second.unk10  = 3;
    second.unk14  = 2;
    second.unk18  = 2;
    second.unk16  = 0xC1;
    second.unk1A  = 0;
    func_020539ac(0, &second);
    func_ov006_02287954(species->unk28, menu->windows[5], 1, 1, 0x177, 2, 0);
    func_020e23c0(&status, 0, sizeof(status));
    status.digimon = menu->work->digimon;
    status.window  = menu->windows[1];
    status.x       = 1;
    status.y       = 5;
    status.unk6    = 1;
    status.unk8    = 1;
    status.unk10   = 0;
    status.unk12   = 1;
    status.unk14   = 2;
    status.unk16   = 0xE;
    status.unk24   = 2;
    status.unk26   = 0x50;
    status.unk28   = 2;
    status.unk2A   = 1;
    status.unk22   = 2;
    status.unk2C   = 1;
    drawStatusWindow(0, &status);
}

/* Closes the displays of func_ov006_022877cc. */
void func_ov006_0228778c(void) {
    freeStatusWindowSprites(0);
    func_020587fc(0);
    freeMoveListDisplaySprite(0);
    closeMoveListDisplay(0);
    freeMoveDisplaySprite(0);
    closeMoveDisplay(0);
}

/* Shows the Digimon in func_02051edc's display, in the fifth window. */
void func_ov006_02287728(struct DigimonMenu *menu) {
    struct Params02051edc params;

    params.window  = menu->windows[4];
    params.x       = 0;
    params.y       = 0;
    params.digimon = menu->work->digimon;
    params.unkC    = 5;
    params.unkE    = 6;
    params.unk10   = 2;
    params.unk12   = 0xB9;
    params.unk14   = 2;
    params.unk16   = 0;
    func_02051edc(0, &params);
}

/* Shows the Digimon in func_02051dd8's display. */
void func_ov006_02287710(struct DigimonMenu *menu) {
    func_02051dd8(0, (s32) menu->work->digimon);
}

/* Redraws the Digimon's status. */
void func_ov006_022876f8(struct DigimonMenu *menu) {
    func_02058590(0, menu->work->digimon);
}

/* Closes the status display, func_02051edc's and the item display of
 * freeEquipmentDisplaySprites and closeEquipmentDisplay. */
void func_ov006_02287574(void) {
    freeStatusWindowSprites(0);
    func_020587fc(0);
    freeEquippedDisplaySprites(0);
    closeEquippedDisplay(0);
    freeEquipmentDisplaySprites(0);
    closeEquipmentDisplay(0);
}

/* Puts the icons' characters and palette in place, makes the eight unk58
 * buttons with the cursor of unk28, blends background 3 over the others and
 * shows the sprite 0x3DC. */
void func_ov006_02287458(struct DigimonMenu *menu) {
    s32 i;
    struct ButtonGroup *group;
    struct Ov006Unk58Work *work;

    func_ov006_02281f70();
    menu->unk58 = createButtonGroup(0x30, menu->unk28->cursor, func_ov006_022869cc);
    for (i = 0; i < 8; i++) {
        addRectButton(data_ov006_0229f1a8[i * 4], data_ov006_0229f1a8[i * 4 + 1], data_ov006_0229f1a8[i * 4 + 2],
                      data_ov006_0229f1a8[i * 4 + 3], 0, menu->unk58);
    }
    group      = findTask(menu->unk58);
    work       = (struct Ov006Unk58Work *) group->work;
    work->unk0 = 0;
    work->unk4 = 0x10;
    work->unk5 = 0;
    work->unk6 = 1;
    work->unk7 = 0;
    work->unk8 = 0;
    work->unk9 = 0;
    work->unkA = 1;
    /* Background 3 over backgrounds 0 to 2 and the sprites. */
    G2_SetBlendAlpha(8, 0x17, 0xA, 0xC);
    menu->work->unk364 = createMainSprite(0x3DC, 0xB8, 0x98, 0xC, 0);
}

/* Removes what func_ov006_02287458 shows and clears the icons of both sets. */
void func_ov006_022873d0(struct DigimonMenu *menu) {
    freeMainSprite(menu->work->unk364);
    menu->work->unk364 = -1;
    func_ov006_02281dd8(0, 0, 0, 0, 0, 0);
    func_ov006_02281dd8(0, 0, 0, 0, 0, 1);
    if (menu->unk58 != -1) {
        closeButtonGroup(menu->unk58);
        menu->unk58 = -1;
    }
}
