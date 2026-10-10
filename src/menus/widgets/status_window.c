#include "menus/widgets/status_window.h"
#include "engine/data.h"
#include "engine/sprite/sprite_create.h"

/* Returns 0x7C: the callers add an offset to it and put it in their params. */
s32 func_02058a24(void) {
    return 0x7C;
}

/* Frees a status window's sprites. */
void freeStatusWindowSprites(s16 index) {
    struct StatusWindow *window = &STATUS_WINDOWS[index];
    s32 i;

    if (!(window->flags & PANEL_IN_USE)) {
        return;
    }
    if (window->screenFlags & PANEL_ON_SUB_SCREEN) {
        for (i = 0; i < 3; i++) {
            freeSubSprite(window->sprites[i]);
        }
    } else {
        for (i = 0; i < 3; i++) {
            freeMainSprite(window->sprites[i]);
        }
    }
}
