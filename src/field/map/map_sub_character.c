#include "field/map/map_sub_character.h"
#include "field/map/data.h"
#include "field/map/map_character.h"

/* Loads a pair of map characters, value and the next one, into the sub
 * screen's character slot index. */
void loadSubMapCharacterSlot(s32 index, u16 value) {
    SUB_MAP_CHARACTER_SLOTS[index] = value;
    loadSubMapCharacter(value, index);
    loadSubMapCharacter(value + 1, index);
}
