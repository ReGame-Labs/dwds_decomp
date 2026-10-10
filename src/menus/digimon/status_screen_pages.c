#include "menus/digimon/status_screen_pages.h"
#include "engine/data.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "menus/digimon/data.h"
#include "menus/widgets/skill_displays.h"
#include "menus/widgets/status_window.h"

/* Closes the status window of func_ov006_0228ca34. */
void func_ov006_0228ca14(void) {
    freeStatusWindowSprites(0);
    func_020587fc(0);
}

/* Closes the status window of func_ov006_0228c960. */
void func_ov006_0228c940(void) {
    freeStatusWindowSprites(0);
    func_020587fc(0);
}

/* Closes the status window and the trait displays of func_ov006_0228c780. */
void func_ov006_0228c740(void) {
    freeStatusWindowSprites(0);
    func_020587fc(0);
    freeAbilityDisplaySprites(0);
    closeAbilityDisplay(0);
    func_02054cb8(0);
    closeAbilityListDisplay(0);
}

/* Closes the technique displays of func_ov006_0228c660. */
void func_ov006_0228c630(void) {
    freeMoveListDisplaySprite(0);
    closeMoveListDisplay(0);
    freeMoveDisplaySprite(0);
    closeMoveDisplay(0);
}

/* Sets work[6] of the page's button group to 20. */
void func_ov006_0228c358(struct StatusScreen *screen) {
    struct ButtonGroup *group = findTask(screen->buttons);

    group->work[6] = 20;
}

/* Frees main screen sprites 1 to 5 and closes the button group of
 * func_ov006_0228c378. */
void func_ov006_0228c308(struct StatusScreen *screen) {
    freeMainSprite(1);
    freeMainSprite(2);
    freeMainSprite(3);
    freeMainSprite(4);
    freeMainSprite(5);
    if (screen->buttons == -1) {
        return;
    }
    closeButtonGroup(screen->buttons);
    screen->buttons = -1;
}

/* Whether the page has no button group. */
u8 func_ov006_0228c2ec(struct StatusScreen *screen) {
    return screen->buttons == -1;
}
