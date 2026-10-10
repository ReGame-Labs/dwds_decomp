#include "menus/digimon/digivolve_screen.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/display_modes.h"
#include "engine/text/text_args.h"
#include "engine/text/text_banks.h"
#include "engine/ui/buttons.h"
#include "engine/ui/digimon_list.h"
#include "engine/window/message_box.h"
#include "engine/window/window.h"
#include "menus/digimon/data.h"

/* Closes the tree's button group. */
void func_ov006_02295404(struct DigivolveScreen *screen) {
    if (screen->treeButtons != -1) {
        closeButtonGroup(screen->treeButtons);
        screen->treeButtons = -1;
    }
}

/* Pauses the tree's buttons. */
void func_ov006_022953f4(struct DigivolveScreen *screen) {
    pauseButtonGroup(screen->treeButtons);
}

/* Resumes the tree's buttons. */
void func_ov006_022953e4(struct DigivolveScreen *screen) {
    resumeButtonGroup(screen->treeButtons);
}

/* Frees the sprites of the menu's four choices. */
void func_ov006_02295034(struct DigivolveScreen *screen) {
    s32 i;

    for (i = 0; i < 4; i++) {
        freeMainSprite(screen->work->menuSprites[i]);
    }
}

/* Lines the menu's four choices up in the menu window, two tiles in and a
 * row of 16 pixels each. */
void func_ov006_02294fb8(struct DigivolveScreen *screen) {
    struct Window *window;
    s32 i;
    struct Sprite *sprite;

    if (screen->menuWindow == 0xFF) {
        return;
    }
    window = getWindow(screen->menuWindow);
    for (i = 0; i < 4; i++) {
        sprite = getMainSprite(screen->work->menuSprites[i]);
        if (sprite != NULL) {
            sprite->x = (window->x + 2) * 8;
            sprite->y = i * 16 + (window->y + 1) * 8;
        }
    }
}

/* Closes the menu's button group. */
void func_ov006_02294d78(struct DigivolveScreen *screen) {
    if (screen->menuButtons != -1) {
        closeButtonGroup(screen->menuButtons);
        screen->menuButtons = -1;
    }
}

/* Asks FARM_TEXTS's 0x72, "Digivolve <digimon's form> into <form
 * selected>?". */
void askDigivolve(struct DigivolveScreen *screen) {
    setTextArg(0, getSpeciesShortName(screen->digimon->unk4));
    setTextArg(1, getSpeciesShortName(screen->species));
    openFarmMessage(0x72, 1, 11, 12, 6, 4);
}

/* Waits for the answer to 0x72, and goes on to the state for
 * the first answer or for the second. */
void func_ov006_022949ac(struct DigivolveScreen *screen) {
    switch (func_020ac6b8()) {
        case 0:
            func_020ac6f8();
            screen->state = 0x47E;
            return;
        case 1:
            func_020ac6f8();
            screen->state = 0x23BE;
            return;
    }
}

/* Asks 0x73, "Degenerate <digimon's form> into <form selected>?". */
void askDegenerate(struct DigivolveScreen *screen) {
    setTextArg(0, getSpeciesShortName(screen->digimon->unk4));
    setTextArg(1, getSpeciesShortName(screen->species));
    openFarmMessage(0x73, 1, 11, 12, 6, 4);
}

/* Waits for the answer to 0x73, and goes on to the state for
 * the first answer or for the second. */
void func_ov006_022948f4(struct DigivolveScreen *screen) {
    switch (func_020ac6b8()) {
        case 0:
            func_020ac6f8();
            screen->state = 0x4B0;
            return;
        case 1:
            func_020ac6f8();
            screen->state = 0x23F0;
            return;
    }
}

/* Copies the three forms the species can take next into next. */
void func_ov006_022948c8(s32 *next, s32 species) {
    s32 *forms;
    s32 i;

    /* The record starts with the three forms the species can take next. */
    forms = (s32 *) func_020a137c(species);
    for (i = 0; i < 3; i++) {
        next[i] = forms[i];
    }
}

/* Copies the forms the digimon has had, from its record, into the tree. */
void func_ov006_02294894(struct DigivolveScreen *screen) {
    struct DigimonHistory *history;
    s32 i;

    history = func_ov006_02294684(screen);
    for (i = 0; i < 5; i++) {
        screen->work->history[i] = history->forms[i];
    }
}

/* Shows only the next forms of the form selected, in the column after its
 * stage. */
void func_ov006_02294830(struct DigivolveScreen *screen) {
    s32 stage;
    s32 column;

    stage = func_020a30d4(getSpeciesStage(screen->species));
    func_02030f18(screen->work->next, -1, sizeof(screen->work->next));
    column = stage + 1;
    if (column >= 5) {
        return;
    }
    func_ov006_022948c8(&screen->work->next[column * 3], screen->species);
}

/* The digimon's record of the forms it has had. */
struct DigimonHistory *func_ov006_02294684(struct DigivolveScreen *screen) {
    return &screen->digimon->history;
}

/* Makes the links drawn between each form the digimon has had and the one
 * before, hidden. */
void func_ov006_02294614(struct DigivolveScreen *screen) {
    s32 i;

    for (i = 1; i < 5; i++) {
        screen->work->historyLinks[i] = createMainSprite(0x1FE, 0, 0, 10, 0);
        addMainSpriteFlags(screen->work->historyLinks[i], SPRITE_HIDDEN);
    }
}
