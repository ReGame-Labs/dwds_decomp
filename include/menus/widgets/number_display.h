#ifndef MENUS_WIDGETS_NUMBER_DISPLAY_H
#define MENUS_WIDGETS_NUMBER_DISPLAY_H

#include "types.h"

/* The number displays (struct NumberDisplay) of the status window. */

/* What openNumberDisplay opens a number display with. */
struct NumberDisplayParams {
    /* 0x00 */ u8 window;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 values[4];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u16 unk12;
    /* 0x14 */ u16 unk14;
};

s32 drawNumberDisplays();
void setNumberDisplayValues(s16 index, s16 value0, s16 value1, s16 value2, s16 value3);
void closeNumberDisplay(s16 index);
void openNumberDisplay(s16 index, struct NumberDisplayParams *params);

#endif /* MENUS_WIDGETS_NUMBER_DISPLAY_H */
