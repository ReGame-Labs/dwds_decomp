#include "menus/digimon/guide_orders.h"
#include "battle/characters/chr.h"
#include "battle/characters/chr_draw.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/digimon/species_flags.h"
#include "engine/libs.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "menus/digimon/data.h"
#include "menus/digimon/guide_data.h"
#include "nitro/pad.h"

/* Makes the battle character's touch button, data_ov006_0229f2c8's
 * rectangle, run by func_ov006_02299c34. */
void func_ov006_02299cd0(struct DigimonGuide *guide) {
    struct ButtonGroup *group;

    guide->chrButton = createButtonGroup(0x34, 0, func_ov006_02299c34);
    addRectButton(data_ov006_0229f2c8.x, data_ov006_0229f2c8.y, data_ov006_0229f2c8.width, data_ov006_0229f2c8.height, 0,
                  guide->chrButton);
    group          = findTask(guide->chrButton);
    group->work[0] = 0;
    group->work[7] = 0;
}

/* Closes the battle character's button and loops its sequence 0 again. */
void func_ov006_02299c98(struct DigimonGuide *guide) {
    if (guide->chrButton != -1) {
        closeButtonGroup(guide->chrButton);
        guide->chrButton = -1;
    }
    playMainBattleChrSeq(0, 0, -1);
}

/* Plays sequence 1 of the guide's battle character once when its button is
 * tapped or Y pressed, and sequence 0 again once it has played. */
void func_ov006_02299c34(s16 touched, s16 cursor, struct ButtonGroup *group) {
    if (isButtonGroupTapped(getTaskId(group)) != 0 || (getPadPressed() & PAD_BUTTON_Y) != 0) {
        playMainBattleChrSeq(0, 1, 1);
    }
    if (isMainBattleChrSeqDone(0) == 0) {
        return;
    }
    playMainBattleChrSeq(0, 0, -1);
}

/* How many species the guide lists. */
s16 func_ov006_02299b24(void) {
    s32 i;
    s32 count;

    count = 0;
    for (i = 0; i < SPECIES_COUNT; i++) {
        if (func_ov006_02299818(i)->listed != 0) {
            count++;
        }
    }
    return count;
}

/* The guide's species in id order, 0xFFFE for one whose game flags 0x640 (by
 * its kind, func_020a0f98) and 0x7D0 (func_020a0f0c) are both clear. */
void func_ov006_02299a90(u16 *list) {
    s32 i;
    s32 count;
    s32 flag640;
    s32 flag7D0;

    func_02030f18(list, -1, SPECIES_COUNT * sizeof(u16));
    count = 0;
    for (i = 0; i < SPECIES_COUNT; i++) {
        if (func_ov006_02299818(i)->listed != 0) {
            flag640 = func_020a0f98(i);
            flag7D0 = func_020a0f0c(i);
            if (flag640 != 0 || flag7D0 != 0) {
                list[count] = i;
            } else {
                list[count] = 0xFFFE;
            }
            count++;
        }
    }
}

/* func_ov006_02299a90 in the order of func_020a1244's table. */
void func_ov006_022999f8(u16 *list) {
    s32 i;
    s32 count;
    s32 *order;
    s32 flag640;
    s32 flag7D0;

    func_02030f18(list, -1, SPECIES_COUNT * sizeof(u16));
    order = func_020a1244();
    count = 0;
    for (i = 0; i < SPECIES_COUNT; i++) {
        if (func_ov006_02299818(order[i])->listed != 0) {
            flag640 = func_020a0f98(order[i]);
            flag7D0 = func_020a0f0c(order[i]);
            if (flag640 != 0 || flag7D0 != 0) {
                list[count] = order[i];
            } else {
                list[count] = 0xFFFE;
            }
            count++;
        }
    }
}
