#include "menus/digimon/digivolve_tree.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/sprite/sprite.h"
#include "engine/system/display.h"
#include "engine/system/display_modes.h"
#include "engine/text/text_banks.h"
#include "engine/text/text_labels.h"
#include "engine/ui/gauge.h"
#include "field/actors/actor_files.h"
#include "menus/digimon/data.h"

/* Has the name of the form selected drawn again, unless it is being drawn. */
void func_ov006_02293920(struct DigivolveScreen *screen) {
    struct DigivolveWork *work = screen->work;

    if (work->nameLabelState == 0) {
        work->nameLabelState = 10;
    }
}

/* Takes the name of the form selected down, if it is up. */
void func_ov006_022938f0(struct DigivolveScreen *screen) {
    s32 label = screen->work->nameLabel;

    if (label == -1) {
        return;
    }
    func_0209d954(label);
    screen->work->nameLabel = -1;
}

/* Draws the name of the form selected next to the cursor, a frame after
 * taking the old one down. */
void func_ov006_022937ec(struct DigivolveScreen *screen) {
    void *name;
    struct Sprite *cursor;
    struct DigivolveWork *work;

    switch (screen->work->nameLabelState) {
        case 0:
            return;
        case 10:
            func_ov006_022938f0(screen);
            work = screen->work;
            work->nameLabelState++;
            return;
        case 11:
            name   = getSpeciesShortName(screen->species);
            cursor = getMainSprite(screen->work->cursorSprite);
            if (cursor == NULL) {
                screen->work->nameLabelState = 0;
                return;
            }
            screen->work->nameLabel = func_0209df00(name, cursor->x + 8, cursor->y, 8, cursor->unk1D - 1, cursor->unk1C, 1, 0);
            screen->work->nameLabelState = 0;
            return;
    }
}

/* Where the actor selected is in the tree: 0 among the forms the digimon has
 * had, 1 among the next forms, -1 neither. */
s32 func_ov006_0229376c(struct DigivolveScreen *screen) {
    s32 i;
    s32 j;
    s32 actor;

    actor = screen->selected;
    if (actor == 0xFFFF) {
        return -1;
    }
    for (i = 0; i < 5; i++) {
        if (actor == screen->work->historyActors[i]) {
            return 0;
        }
        for (j = 0; j < 3; j++) {
            if (actor == screen->work->nextActors[i * 3 + j]) {
                return 1;
            }
        }
    }
    return -1;
}

/* Scrolls the tree toward the actor selected, until it is in the middle of
 * the screen or the tree's edge is reached. */
void func_ov006_022934ec(struct DigivolveScreen *screen) {
    struct Actor *actor;
    s32 doneX;
    s32 doneY;

    doneX = 0;
    doneY = 0;
    switch (screen->scroll->state) {
        case 0:
            if (screen->scroll->actor != screen->selected) {
                screen->scroll->actor = screen->selected;
                screen->scroll->state++;
            }
            break;
        case 1:
            actor                = getMainActor(screen->scroll->actor);
            screen->scroll->endX = screen->work->scrollX - (actor->x - 128);
            screen->scroll->endY = screen->work->scrollY - (actor->y - 96);
            if (screen->work->scrollX >= screen->scroll->endX) {
                screen->scroll->stepX = -6;
            } else {
                screen->scroll->stepX = 6;
            }
            if (screen->work->scrollY >= screen->scroll->endY) {
                screen->scroll->stepY = -4;
            } else {
                screen->scroll->stepY = 4;
            }
            screen->scroll->state = 10;
            break;
        case 10:
            screen->work->scrollX += screen->scroll->stepX;
            screen->work->scrollY += screen->scroll->stepY;
            if (screen->scroll->stepX < 0 &&
                (screen->work->scrollX <= screen->scroll->endX || screen->work->scrollX <= -0x100)) {
                if (screen->work->scrollX <= -0x100) {
                    screen->work->scrollX = -0x100;
                } else {
                    screen->work->scrollX = screen->scroll->endX;
                }
                doneX = 1;
            } else if (screen->scroll->stepX > 0 &&
                       (screen->work->scrollX >= screen->scroll->endX || screen->work->scrollX >= 0)) {
                if (screen->work->scrollX >= 0) {
                    screen->work->scrollX = 0;
                } else {
                    screen->work->scrollX = screen->scroll->endX;
                }
                doneX = 1;
            }
            if (screen->scroll->stepY < 0 && screen->work->scrollY <= screen->scroll->endY) {
                screen->work->scrollY = screen->scroll->endY;
                doneY                 = 1;
            } else if (screen->scroll->stepY > 0 &&
                       (screen->work->scrollY >= screen->scroll->endY || screen->work->scrollY >= 0)) {
                if (screen->work->scrollY >= 0) {
                    screen->work->scrollY = 0;
                } else {
                    screen->work->scrollY = screen->scroll->endY;
                }
                doneY = 1;
            }
            if (doneX != 0 && doneY != 0) {
                screen->scroll->state = 0;
            }
            break;
    }
    screen->work->bgX = screen->work->scrollX;
    screen->work->bgY = 0;
}

/* Whether the form selected is one the digimon itself can take next: a stage
 * up, in the column that hangs from the digimon's form. */
u8 func_ov006_02293484(struct DigivolveScreen *screen) {
    s32 stage;
    s32 targetStage;

    stage       = func_020a30d4(getSpeciesStage(screen->digimon->unk4));
    targetStage = func_020a30d4(getSpeciesStage(screen->species));
    /* Allocated and never used. */
    allocVramTransferData(12);
    if (stage != targetStage - 1) {
        return 0;
    }
    return screen->currentActor == screen->work->nextFrom[targetStage];
}

/* Whether the digimon meets all three conditions of the form selected. */
s32 func_ov006_02293418(struct DigivolveScreen *screen) {
    u8 met[3];
    s32 i;

    for (i = 0; i < 3; i++) {
        met[i] = func_ov006_022933fc(screen, i);
    }
    if (met[0] != 0 && met[1] != 0 && met[2] != 0) {
        return 1;
    }
    return 0;
}

/* Whether the digimon meets condition index (0 to 2) of digivolving into the
 * form selected: func_020a1bac reads the three conditions after each next
 * form in the record of func_020a137c for the digimon's species. */
s32 func_ov006_022933fc(struct DigivolveScreen *screen, s16 index) {
    return func_020a1bac(screen->digimon, screen->species, index);
}

/* Whether the digimon can go back to the form selected: one of the forms it
 * has had, a stage below its own, once game flag 0x84 is set. */
s32 func_ov006_0229336c(struct DigivolveScreen *screen) {
    s32 stage;
    s32 i;

    if (getGameFlag(0x84) == 0) {
        return 0;
    }
    stage = func_020a30d4(getSpeciesStage(screen->digimon->unk4));
    if (stage <= func_020a30d4(getSpeciesStage(screen->species))) {
        return 0;
    }
    for (i = 0; i < 5; i++) {
        if (screen->selected == screen->work->historyActors[i]) {
            return 1;
        }
    }
    return 0;
}
