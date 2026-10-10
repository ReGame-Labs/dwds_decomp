#include "menus/digiconvert/convert_captions.h"
#include "engine/data.h"
#include "engine/text/font.h"

/* The id of the Digimon the conversion scene made, once it has ended. */
s32 getConvertedDigimon(void) {
    if (CONVERT_TASK != NULL) {
        return 0;
    }
    return CONVERTED_DIGIMON;
}

/* Empties the captions' slots. */
void initCaptions(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        CAPTION_TASK_IDS[i] = -1;
    }
}

/* Sets up the sub screen's text slot 6 for the captions (func_020a9c40). */
void initCaptionText(s32 unk0, s16 unk1) {
    func_020a9c40(6, (s8) unk0, (s8) (unk1 + 0x10));
    data_021b4978 = unk1;
}

/* Frees the captions' text slot. */
void freeCaptionText(void) {
    func_020a98a8(6);
}
