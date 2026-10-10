#include "menus/digimon/digivolve_tree_sprites.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/display_modes.h"
#include "menus/digimon/data.h"

/* Makes the tree's stage sprites, one for each column: the look of 0x1FA for
 * the digimon's own stage, that of 0x1FB for the others. */
void func_ov006_02294440(struct DigivolveScreen *screen) {
    s32 i;
    s32 stage;

    stage = func_020a30d4(getSpeciesStage(screen->digimon->unk4));
    for (i = 0; i < 5; i++) {
        if (stage == i) {
            screen->work->stageSprites[i] = createMainSprite(0x1FA, 0, 0, 11, 0);
            addMainSpriteFlags(screen->work->stageSprites[i], SPRITE_HIDDEN);
        } else {
            screen->work->stageSprites[i] = createMainSprite(0x1FB, 0, 0, 11, 0);
            addMainSpriteFlags(screen->work->stageSprites[i], SPRITE_HIDDEN);
        }
    }
}
