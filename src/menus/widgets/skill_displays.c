#include "menus/widgets/skill_displays.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite_create.h"
#include "engine/text/text_object.h"
#include "menus/widgets/text_list.h"

/* Frees the ability display's images and empties it. */
void closeAbilityDisplay(s16 index) {
    struct AbilityDisplay *display = &ABILITY_DISPLAY[index];

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    if (display->images[0].width != 0 && display->images[0].height != 0) {
        freeWindowImage(&display->images[0]);
        func_02030f18(&display->images[0], 0, sizeof(struct WindowImage));
    }
    if (display->images[1].width != 0 && display->images[1].height != 0) {
        freeWindowImage(&display->images[1]);
        func_02030f18(&display->images[1], 0, sizeof(struct WindowImage));
    }
    if (display->images[2].width != 0 && display->images[2].height != 0) {
        freeWindowImage(&display->images[2]);
        func_02030f18(&display->images[2], 0, sizeof(struct WindowImage));
    }
    if (display->images[3].width != 0 && display->images[3].height != 0) {
        freeWindowImage(&display->images[3]);
        func_02030f18(&display->images[3], 0, sizeof(struct WindowImage));
    }
    func_02030f18(display, 0, sizeof(struct AbilityDisplay));
}

/* Frees the ability display's sprites. */
void freeAbilityDisplaySprites(s16 index) {
    struct AbilityDisplay *display = &ABILITY_DISPLAY[index];
    s32 i;

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    if (display->screenFlags & PANEL_ON_SUB_SCREEN) {
        for (i = 0; i < 4; i++) {
            freeSubSprite(display->sprites[i]);
        }
        freeSubSprite(display->sprite);
        freeSubSprite(display->sprite2);
    } else {
        for (i = 0; i < 4; i++) {
            freeMainSprite(display->sprites[i]);
        }
        freeMainSprite(display->sprite);
        freeMainSprite(display->sprite2);
    }
}

/* Sets the ability display's unkA and has it drawn again. */
void func_02056788(s16 index, s16 value) {
    struct AbilityDisplay *display = &ABILITY_DISPLAY[index];

    if (display->flags & PANEL_IN_USE) {
        display->flags |= PANEL_CHANGED;
        display->unkA = value;
    }
}

/* Closes the ability list display's text lists and empties it. */
void closeAbilityListDisplay(s16 index) {
    struct AbilityListDisplay *display = &ABILITY_LIST_DISPLAY[index];

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    closeTextList(display->textLists[0]);
    closeTextList(display->textLists[1]);
    closeTextList(display->textLists[2]);
    closeTextList(display->textLists[3]);
    func_02030f18(display, 0, sizeof(struct AbilityListDisplay));
}

/* Frees the move display's images and empties it. */
void closeMoveDisplay(s16 index) {
    struct MoveDisplay *display = &MOVE_DISPLAY[index];

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    if (display->images[0].width != 0 && display->images[0].height != 0) {
        freeWindowImage(&display->images[0]);
        func_02030f18(&display->images[0], 0, sizeof(struct WindowImage));
    }
    if (display->images[1].width != 0 && display->images[1].height != 0) {
        freeWindowImage(&display->images[1]);
        func_02030f18(&display->images[1], 0, sizeof(struct WindowImage));
    }
    if (display->images[2].width != 0 && display->images[2].height != 0) {
        freeWindowImage(&display->images[2]);
        func_02030f18(&display->images[2], 0, sizeof(struct WindowImage));
    }
    func_02030f18(display, 0, sizeof(struct MoveDisplay));
}

/* Frees the move display's sprite. */
void freeMoveDisplaySprite(s16 index) {
    struct MoveDisplay *display = &MOVE_DISPLAY[index];

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    if (display->screenFlags & PANEL_ON_SUB_SCREEN) {
        freeSubSprite(display->sprite);
    } else {
        freeMainSprite(display->sprite);
    }
}

/* Closes the move list display's text list and empties it. */
void closeMoveListDisplay(s16 index) {
    struct MoveListDisplay *display = &MOVE_LIST_DISPLAY[index];

    if (display->flags & PANEL_IN_USE) {
        closeTextList(display->textList);
        func_02030f18(display, 0, sizeof(struct MoveListDisplay));
    }
}

/* Frees the move list display's sprite. */
void freeMoveListDisplaySprite(s16 index) {
    struct MoveListDisplay *display = &MOVE_LIST_DISPLAY[index];

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    if (display->screenFlags & PANEL_ON_SUB_SCREEN) {
        freeSubSprite(display->sprite);
    } else {
        freeMainSprite(display->sprite);
    }
}
