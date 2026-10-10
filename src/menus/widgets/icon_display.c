#include "menus/widgets/icon_display.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_create.h"
#include "engine/text/text_object.h"
#include "engine/window/window.h"
#include "engine/window/window_draw.h"

/* Places the icon display's sprite at its place in its window, a tile to the
 * left of it. */
void placeIconDisplaySprite(void) {
    struct IconDisplay *display = &ICON_DISPLAY;
    struct Window *window;
    struct Sprite *sprite;

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    window = getWindow(display->window);
    if (display->screenFlags & PANEL_ON_SUB_SCREEN) {
        sprite = getSubSprite(display->sprite);
    } else {
        sprite = getMainSprite(display->sprite);
    }
    if (sprite == NULL) {
        return;
    }
    sprite->x = (window->x + (display->x - 2)) * TILE_SIZE;
    sprite->y = (window->y + display->y) * TILE_SIZE;
}

/* Frees the icon display's sprite, clears its window and frees its images. */
void closeIconDisplay(void) {
    struct IconDisplay *display = &ICON_DISPLAY;
    struct Window *window;

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    if (display->screenFlags & PANEL_ON_SUB_SCREEN) {
        if (display->sprite != -1) {
            freeSubSprite(display->sprite);
        }
    } else if (display->sprite != -1) {
        freeMainSprite(display->sprite);
    }
    window = getWindow(display->window);
    func_020a8a98(display->window, 0, 0, window->width, window->height, 0);
    if (display->images[0].width != 0 && display->images[0].height != 0) {
        freeWindowImage(&display->images[0]);
        func_02030f18(&display->images[0], 0, sizeof(struct WindowImage));
    }
    if (display->unkE != -1 && display->images[1].width != 0 && display->images[1].height != 0) {
        freeWindowImage(&display->images[1]);
        func_02030f18(&display->images[1], 0, sizeof(struct WindowImage));
    }
    func_02030f18(display, 0, sizeof(struct IconDisplay));
}
