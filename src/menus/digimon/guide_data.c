#include "menus/digimon/guide_data.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/libs.h"
#include "engine/text/font.h"
#include "engine/text/text_banks.h"
#include "engine/text/text_object.h"
#include "menus/digimon/data.h"

/* Empties one of the guide's lists (0xFFFF in every entry). */
void func_ov006_02299840(u16 *list) {
    func_02030f18(list, -1, SPECIES_COUNT * sizeof(u16));
}

/* The guide's copy of the species' data. */
struct SpeciesData *func_ov006_02299818(s32 species) {
    return &DIGIMON_GUIDE->work->species[species];
}

/* Copies every species' data (loadSpeciesData's) into the guide's work. */
void func_ov006_022997bc(struct DigimonGuide *guide) {
    s32 i;

    for (i = 0; i < SPECIES_COUNT; i++) {
        func_020e2454(loadSpeciesData(i), &guide->work->species[i], sizeof(struct SpeciesData));
    }
}

/* Loads the fonts the guide writes with (data_02127184's), each into a slot
 * it empties first: font_dg and font00 on the sub screen, font_dg and font_n
 * on the main screen. */
void loadGuideFonts(void) {
    func_020a9610(4);
    func_020a9ae0(1, 4, 14);
    func_020a9610(3);
    func_020a9ae0(2, 3, 14);
    func_020a9610(5);
    func_020a9c40(1, 5, 14);
    func_020a9610(6);
    func_020a9c40(3, 6, 14);
}

/* Empties slots 3 and 6, two of loadGuideFonts's fonts. */
void func_ov006_0229972c(void) {
    func_020a9610(3);
    func_020a9610(6);
}

/* Frees the text window of data_ov006_0229f680, if it has one. */
void func_ov006_02299548(void) {
    if (data_ov006_0229f680.width == 0 || data_ov006_0229f680.height == 0) {
        return;
    }
    freeWindowImage(&data_ov006_0229f680);
    CLEAR(&data_ov006_0229f680, sizeof(struct TextWindow));
}

/* Frees the text window of data_ov006_0229f658, if it has one. */
void func_ov006_02299364(void) {
    if (data_ov006_0229f658.width == 0 || data_ov006_0229f658.height == 0) {
        return;
    }
    freeWindowImage(&data_ov006_0229f658);
    CLEAR(&data_ov006_0229f658, sizeof(struct TextWindow));
}

/* Loads the guide's texts, text bank 0 (/dat/msg/DigZknHelp.sdb). */
void loadGuideTexts(void) {
    loadTextBank(0);
}

/* Frees the text bank. */
void freeGuideTexts(void) {
    freeTextBank();
}

/* Frees the text window of data_ov006_0229f630, if it has one. */
void func_ov006_0229914c(void) {
    if (data_ov006_0229f630.width == 0 || data_ov006_0229f630.height == 0) {
        return;
    }
    freeWindowImage(&data_ov006_0229f630);
    CLEAR(&data_ov006_0229f630, sizeof(struct TextWindow));
}
