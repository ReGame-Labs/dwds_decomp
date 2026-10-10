#include "menus/digimon/status_screen_open.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/system/system.h"
#include "engine/text/text_args.h"
#include "engine/text/text_banks.h"
#include "engine/ui/digimon_list.h"
#include "engine/window/message_box.h"
#include "menus/digimon/data.h"

/* Asks FARM_TEXTS's 0x74, "Unable to learn more traits. Delete a
 * trait?". */
void func_ov006_0228e690(void) {
    openFarmMessage(0x74, 1, 8, 0xB, 0xD, 4);
}

/* Asks 0x75, "Unable to learn <trait>. Is this OK?", of the trait offered. */
void func_ov006_0228e648(struct LearnTraitMenu *menu) {
    setTextArg(0, getAbilityName(menu->id));
    openFarmMessage(0x75, 1, 8, 0xB, 0xD, 4);
}

/* Asks 0x76, "Delete <slot's trait> and learn <trait>?", of the slot the
 * cursor is on. */
void func_ov006_0228e5d8(struct LearnTraitMenu *menu) {
    setTextArg(0, getAbilityName(menu->id));
    setTextArg(1, getAbilityName(menu->digimon->unk22[menu->list->cursor]));
    openFarmMessage(0x76, 1, 8, 0xB, 0xD, 4);
}

/* Asks 0x77, "Cancel learning <trait>?". */
void func_ov006_0228e590(struct LearnTraitMenu *menu) {
    setTextArg(0, getAbilityName(menu->id));
    openFarmMessage(0x77, 1, 8, 0xB, 0xD, 4);
}

/* Once the message window has an answer, closes it and goes on to the state
 * for the first choice or for the second. */
void func_ov006_0228e550(struct LearnTraitMenu *menu, s16 state0, s16 state1) {
    switch (func_020ac6b8()) {
        case 0:
            func_020ac6f8();
            menu->state = state0;
            break;
        case 1:
            func_020ac6f8();
            menu->state = state1;
            break;
    }
}

/* The status screen's onEnd: frees its work and forgets its task. */
void onStatusScreenEnd(void) {
    struct StatusScreen *screen = (struct StatusScreen *) getCurrentTask();

    heapFree(screen->work);
    STATUS_SCREEN_TASK_ID = -1;
    STATUS_SCREEN         = NULL;
}

/* Whether the status screen has closed. */
u8 isStatusScreenClosed(void) {
    return STATUS_SCREEN == NULL;
}
