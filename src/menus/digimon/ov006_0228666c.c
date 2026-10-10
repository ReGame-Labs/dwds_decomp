#include "menus/digimon/ov006_0228666c.h"
#include "engine/data.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "menus/digimon/data.h"
#include "menus/widgets/menu_displays.h"

/* Calls func_0205b5b4(2, 0) and puts the callback of the unk5C buttons at
 * its step 20. */
void func_ov006_022866dc(struct DigimonMenu *menu) {
    struct ButtonGroup *group;

    func_0205b5b4(2, 0);
    group = findTask(menu->unk5C);
    /* Its callback, func_ov006_022859a4, keeps its state in work's first byte. */
    *(u8 *) group->work = 20;
}

/* Removes the five unk340 sprites and the unk5C buttons. */
void func_ov006_02286688(struct DigimonMenu *menu) {
    s32 i;

    for (i = 0; i < 5; i++) {
        freeMainSprite(menu->work->unk340[i]);
    }
    if (menu->unk5C != -1) {
        closeButtonGroup(menu->unk5C);
        menu->unk5C = -1;
    }
}

/* Whether the buttons of unk5C are gone. */
u8 func_ov006_0228666c(struct DigimonMenu *menu) {
    return menu->unk5C == -1;
}
