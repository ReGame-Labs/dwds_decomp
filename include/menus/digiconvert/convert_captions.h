#ifndef MENUS_DIGICONVERT_CONVERT_CAPTIONS_H
#define MENUS_DIGICONVERT_CONVERT_CAPTIONS_H

#include "types.h"

/* The captions' text slot and slots, and the result of the conversion
 * scene. */

void freeCaptionText(void);
s32 getConvertedDigimon(void);
void initCaptionText(s32 unk0, s16 unk1);
void initCaptions(void);

#endif /* MENUS_DIGICONVERT_CONVERT_CAPTIONS_H */
