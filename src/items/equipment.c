#include "items/equipment.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/sprite/sprite.h"
#include "items/inventory.h"

/* Whether the Digimon can equip the piece of equipment of the stock: it needs
 * the piece's level, and the piece has to be for anyone (10) or for its unk1A. */
BOOL canEquip(s32 digimonId, s32 id) {
    struct Digimon *digimon;
    struct EquipSlot *slot;
    u16 item;
    struct ItemData *data;
    u8 kind;

    digimon = getDigimon(digimonId);
    if (digimon == NULL) {
        return FALSE;
    }
    slot = findWeapon(id);
    if (slot == NULL) {
        slot = findArmor(id);
        if (slot == NULL) {
            slot = findAccessory(id);
            if (slot == NULL) {
                return FALSE;
            }
            item = slot->item;
        } else {
            item = slot->item;
        }
    } else {
        item = slot->item;
    }
    data = (struct ItemData *) func_020a142c(item); /* declared u8 * */
    if (digimon->level >= data->minLevel) {
        kind = data->unk3;
        if (kind == 10 || digimon->unk1A == kind) {
            return TRUE;
        }
    }
    return FALSE;
}

/* Places three sprites in a row, 14 pixels apart, on the main screen or on
 * the sub screen: the digits func_0205b8ac sets. */
void placeDigitSprites(s16 x, s16 y, s32 left, s32 middle, s32 right, u8 subScreen) {
    struct Sprite *sprite0;
    struct Sprite *sprite1;
    struct Sprite *sprite2;

    if (subScreen == FALSE) {
        sprite0 = getMainSprite(left);
        sprite1 = getMainSprite(middle);
        sprite2 = getMainSprite(right);
    } else {
        sprite0 = getSubSprite(left);
        sprite1 = getSubSprite(middle);
        sprite2 = getSubSprite(right);
    }
    sprite0->x = x;
    sprite0->y = y;
    sprite1->x = x + 14;
    sprite1->y = y;
    sprite2->x = x + 28;
    sprite2->y = y;
}
