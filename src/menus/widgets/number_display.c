#include "menus/widgets/number_display.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/text/text_object.h"

/* Opens a number display, unless it is open, from its parameters. */
void openNumberDisplay(s16 index, struct NumberDisplayParams *params) {
    struct NumberDisplay *display = &NUMBER_DISPLAYS[index];

    if (display->flags & PANEL_IN_USE) {
        return;
    }
    display->window    = params->window;
    display->flags     = PANEL_IN_USE | PANEL_CHANGED;
    display->x         = params->x;
    display->y         = params->y;
    display->values[0] = params->values[0];
    display->values[1] = params->values[1];
    display->values[2] = params->values[2];
    display->values[3] = params->values[3];
    display->unkE      = params->unkE;
    display->unk10     = params->unk10;
    display->unk12     = params->unk12;
    display->unk14     = params->unk14;
    display->unk16     = 50;
    func_02030f18(&display->images[0], 0, sizeof(struct WindowImage));
    func_02030f18(&display->images[1], 0, sizeof(struct WindowImage));
    func_02030f18(&display->images[2], 0, sizeof(struct WindowImage));
    func_02030f18(&display->images[3], 0, sizeof(struct WindowImage));
}

/* Frees a number display's images and empties it. */
void closeNumberDisplay(s16 index) {
    struct NumberDisplay *display = &NUMBER_DISPLAYS[index];

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
    func_02030f18(display, 0, sizeof(struct NumberDisplay));
}

/* Sets a number display's numbers and has it drawn again. */
void setNumberDisplayValues(s16 index, s16 value0, s16 value1, s16 value2, s16 value3) {
    struct NumberDisplay *display = &NUMBER_DISPLAYS[index];

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    display->flags |= PANEL_CHANGED;
    display->values[0] = value0;
    display->values[1] = value1;
    display->values[2] = value2;
    display->values[3] = value3;
}
