#include "menus/digimon/ov006_02281f70.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/gfx/gfx_files.h"
#include "engine/libs.h"
#include "engine/palette/palette_fade.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_create.h"
#include "engine/sprite/sprite_draw.h"
#include "engine/system/display.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "menus/digimon/data.h"
#include "nitro/g2d.h"
#include "nitro/pad.h"

/* Closes the menu of three by a row. */
void func_ov006_02282620(struct DigimonMenu *menu) {
    freeMainSprite(menu->work->popupSprite);
    if (menu->popupButtons != -1) {
        closeButtonGroup(menu->popupButtons);
        menu->popupButtons = -1;
    }
}

/* Shows the two choices of unk50 with the cursor on the first, and makes
 * their touch buttons. */
void func_ov006_02282140(struct DigimonMenu *menu) {
    s32 i;

    menu->work->unk360 = createMainSprite(0x3DE, 0, 0, 0xA, 0);
    func_0203e878(menu->work->unk360, 0x3F);
    menu->unk50->cursor = 0;
    menu->unk6C         = createButtonGroup(0x30, menu->unk50->cursor, func_ov006_02282018);
    for (i = 0; i < 2; i++) {
        addRectButton(data_ov006_0229f400[i * 4], data_ov006_0229f400[i * 4 + 1], data_ov006_0229f400[i * 4 + 2],
                      data_ov006_0229f400[i * 4 + 3], 0, menu->unk6C);
    }
}

/* Closes the two choices of unk50. */
void func_ov006_0228210c(struct DigimonMenu *menu) {
    freeMainSprite(menu->work->unk360);
    if (menu->unk6C != -1) {
        closeButtonGroup(menu->unk6C);
        menu->unk6C = -1;
    }
}

/* The two choices' callback: a touch moves the cursor, and A or a tap goes on
 * to the next state for the first and the one after for the second. */
void func_ov006_02282018(s16 button, s16 cursor, struct ButtonGroup *group) {
    s32 id;
    struct DigimonMenu *menu;
    s32 changed;

    menu    = findTask(DIGIMON_MENU_TASK_ID);
    changed = FALSE;
    id      = getTaskId(group);
    if (button != -1 && menu->unk50->cursor != button) {
        menu->unk50->cursor = button;
        changed             = TRUE;
    }
    if (changed == TRUE) {
        setMainSpriteAnim(menu->work->unk360, menu->unk50->cursor, -1);
    }
    if ((getPadPressed() & PAD_BUTTON_A) || takeButtonGroupTap(id) != 0) {
        playSound(1);
        switch (menu->unk50->cursor) {
            case 0:
                func_ov006_0228210c(menu);
                menu->state += 1;
                break;
            case 1:
                func_ov006_0228210c(menu);
                menu->state += 2;
                break;
        }
    }
}

/* Queues the copy of background 3's characters to their VRAM, past 0x3000,
 * and loads its palette. */
void func_ov006_02281f70(void) {
    struct DigimonMenu *menu = findTask(DIGIMON_MENU_TASK_ID);
    struct VramCopy copy     = {0};
    struct CharacterData *chars;
    struct NNSG2dPaletteData *palette;

    chars     = menu->work->bg[3].chars;
    copy.src  = chars->data;
    copy.dest = (void *) (func_020db3f8() + 0x3000);
    copy.size = chars->size;
    if (copy.size >= 0x1000) {
        copy.size = 0x1000;
    }
    queueVramTransfer(&copy);
    palette = menu->work->bg[3].palette;
    loadMainPalette(0x60, (u16) (getPaletteSize((s32) menu->work->bg[3].paletteFile, palette) >> 1), (s32) palette->pRawData);
}
