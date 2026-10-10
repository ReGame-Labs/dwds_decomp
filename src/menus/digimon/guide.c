#include "menus/digimon/guide.h"
#include "battle/characters/chr.h"
#include "battle/characters/chr_draw.h"
#include "battle/characters/data.h"
#include "engine/bg/bg_screen.h"
#include "engine/data.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_draw.h"
#include "engine/system/display_modes.h"
#include "menus/digimon/data.h"

/* Once the cursor's Digimon changed, makes it battle character 0 of each
 * screen, above sub screen sprite 1 and main screen sprite 5 (see
 * func_ov006_0229ca38), or removes the character for an empty entry. */
void func_ov006_0229cb68(struct DigimonGuide *guide) {
    u16 id;
    s32 chr;
    struct SpriteOffset *offset;
    struct Sprite *sprite;

    if (guide->chrChanged == 0) {
        return;
    }
    guide->chrChanged = 0;
    id                = data_ov006_0229f548[guide->scroll + guide->cursor];
    if (id == 0xFFFE || id == 0xFFFF) {
        removeSubBattleChr(0);
        return;
    }
    chr    = func_020a31d8(id);
    offset = getSpriteOffset(chr);
    sprite = getSubSprite(1);
    startSubBattleChrPlaceTask(chr, sprite->x + offset->x, sprite->y + offset->y, 0, 0, 0, 0, 0, 4, guide->task.priority, 1);
    sprite = getMainSprite(5);
    startMainBattleChrPlaceTask(chr, sprite->x + offset->x, sprite->y + offset->y, 0, 0, 0, 0, 0, 8, guide->task.priority);
}

/* Has func_ov006_0229cb68 show the Digimon of the cursor's row. */
void func_ov006_0229ccc0(void) {
    if (DIGIMON_GUIDE != NULL) {
        DIGIMON_GUIDE->chrChanged = 1;
    }
}

/* Places the Digimon's battle character on each screen above its sprite, sub
 * screen sprite 1 and main screen sprite 5, which follow the screens' scroll
 * (data_ov006_0229f530 and data_ov006_0229f534). */
void func_ov006_0229ca38(void) {
    struct Sprite *subSprite;
    struct Sprite *mainSprite;
    struct BattleChr *subChr;
    struct BattleChr *mainChr;
    struct SpriteOffset *offset;

    subChr     = getSubBattleChr(0);
    mainChr    = getMainBattleChr(0);
    subSprite  = getSubSprite(1);
    mainSprite = getMainSprite(5);
    if (subSprite != NULL) {
        subSprite->x = data_ov006_0229f530 + 0x48;
        subSprite->y = data_ov006_0229f534 + 0x90;
    }
    if (subChr != NULL) {
        offset    = getSpriteOffset(subChr->chr);
        subChr->x = subSprite->x + offset->x;
        subChr->y = subSprite->y - 0x60 + offset->y;
    }
    if (mainSprite != NULL) {
        mainSprite->x = data_ov006_0229f530 + 0x48;
        mainSprite->y = data_ov006_0229f534 - 0x90;
    }
    if (mainChr != NULL) {
        offset     = getSpriteOffset(mainChr->chr);
        mainChr->x = mainSprite->x + offset->x;
        mainChr->y = mainSprite->y - 0x60 + offset->y;
    }
    setSubSpriteBgPriority(1, 3);
    setMainSpriteBgPriority(5, 3);
    setSubBattleChrPriority(0, 3);
    setMainBattleChrPriority(0, 3);
}

/* Has func_ov006_0229c7bc walk the cursor's Digimon in. */
void func_ov006_0229ca1c(void) {
    if (DIGIMON_GUIDE != NULL) {
        DIGIMON_GUIDE->actorState = 1;
    }
}

/* Has func_ov006_0229c7bc walk it out. */
void func_ov006_0229c9fc(void) {
    if (DIGIMON_GUIDE != NULL) {
        DIGIMON_GUIDE->actorState = 1001;
    }
}
