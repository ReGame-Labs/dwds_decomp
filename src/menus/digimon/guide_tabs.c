#include "menus/digimon/guide_tabs.h"
#include "engine/bg/bg_screen.h"
#include "engine/data.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_create.h"
#include "engine/sprite/sprite_draw.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "menus/digimon/data.h"
#include "menus/digimon/guide_orders.h"

/* Makes the four tab buttons, over the sprites of data_ov006_0229f31c, with
 * tab 0 picked (its sprite plays animation 1). */
void func_ov006_0229a600(struct DigimonGuide *guide) {
    s32 i;
    struct ButtonGroup *group;

    guide->tabButtons = createButtonGroup(0x32, 0, func_ov006_0229a3b0);
    for (i = 0; i < 4; i++) {
        addRectButton(data_ov006_0229f34c[i * 4], data_ov006_0229f34c[i * 4 + 1], data_ov006_0229f34c[i * 4 + 2],
                      data_ov006_0229f34c[i * 4 + 3], 0, guide->tabButtons);
    }
    guide->prevTab = guide->tab = 0;
    group                       = findTask(guide->tabButtons);
    group->work[7]              = 0;
    setMainSpriteAnim(data_ov006_0229f31c[guide->tab], 1, -1);
}

/* Closes the tab buttons. */
void func_ov006_0229a5d8(struct DigimonGuide *guide) {
    if (guide->tabButtons == -1) {
        return;
    }
    closeButtonGroup(guide->tabButtons);
    guide->tabButtons = -1;
}

/* Makes two buttons, with main screen sprites 12 and 13 (0x3BA and 0x3B9),
 * which work[0] and work[1] time the holding of; both start disabled. */
void func_ov006_0229a260(struct DigimonGuide *guide) {
    s32 i;
    struct ButtonGroup *group;
    s32 id;

    guide->unk40 = createButtonGroup(0x34, 0, func_ov006_02299d3c);
    createMainSpriteAt(0x3BA, 0, 0x4E, 9, 0, 12);
    setMainSpriteBgPriority(12, 2);
    createMainSpriteAt(0x3B9, 0x72, 0x5C, 9, 0, 13);
    setMainSpriteBgPriority(12, 2);
    addMainSpriteFlags(12, SPRITE_HIDDEN);
    addMainSpriteFlags(13, SPRITE_HIDDEN);
    for (i = 0; i < 2; i++) {
        addRectButton(data_ov006_0229f30c[i * 4], data_ov006_0229f30c[i * 4 + 1], data_ov006_0229f30c[i * 4 + 2],
                      data_ov006_0229f30c[i * 4 + 3], 0, guide->unk40);
    }
    group          = findTask(guide->unk40);
    group->work[0] = 32;
    group->work[1] = 32;
    group->work[7] = 0;
    id             = getTaskId(group);
    disableButton(0, id);
    disableButton(1, id);
}

/* Closes the buttons of sprites 12 and 13 and frees the sprites. */
void func_ov006_0229a228(struct DigimonGuide *guide) {
    if (guide->unk40 != -1) {
        closeButtonGroup(guide->unk40);
        guide->unk40 = -1;
    }
    freeMainSprite(12);
    freeMainSprite(13);
}
