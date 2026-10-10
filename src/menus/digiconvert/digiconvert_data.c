#include "menus/digiconvert/digiconvert_data.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/libs.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"

/* Makes the prompt's two buttons. */
void createDigiconvertChoice(struct Digiconvert *digiconvert) {
    s32 i;
    struct ButtonGroup *group;

    digiconvert->choiceButtons = createButtonGroup(0x32, 1, onDigiconvertChoice);
    for (i = 0; i < 2; i++) {
        addRectButton(data_02116880[i * 4], data_02116880[i * 4 + 1], data_02116880[i * 4 + 2], data_02116880[i * 4 + 3], 0,
                      digiconvert->choiceButtons);
    }
    group          = findTask(digiconvert->choiceButtons);
    group->work[0] = 1;
    group->work[7] = 0;
}

/* Frees the Digiconvert screen's Yes/No buttons, if it has them. */
void freeDigiconvertChoice(struct Digiconvert *digiconvert) {
    if (digiconvert->choiceButtons == -1) {
        return;
    }
    closeButtonGroup(digiconvert->choiceButtons);
    digiconvert->choiceButtons = -1;
}

/* How many species are listed. */
s16 countListedSpecies(void) {
    s32 i;
    s32 count;

    for (count = 0, i = 0; i < SPECIES_COUNT; i++) {
        if (getDigiconvertSpecies(i)->listed != 0) {
            count++;
        }
    }
    return count;
}

/* Fills a list with 0xFFFF. */
void clearSpeciesList(u16 *list) {
    func_02030f18(list, -1, sizeof(DIGICONVERT->work->lists[0]));
}

/* Sets the Digiconvert screen's unk9E, if it is open. */
void func_0205d8f0(void) {
    if (DIGICONVERT != NULL) {
        DIGICONVERT->unk9E = 1;
    }
}

/* The screen's copy of a species' data. */
struct SpeciesData *getDigiconvertSpecies(s32 index) {
    return &DIGICONVERT->work->species[index];
}

/* Copies every species' data into the work block. */
void loadDigiconvertSpecies(struct Digiconvert *digiconvert) {
    s32 i;

    for (i = 0; i < SPECIES_COUNT; i++) {
        func_020e2454(loadSpeciesData(i), &digiconvert->work->species[i], sizeof(struct SpeciesData));
    }
}
