#ifndef NITRO_PAD_H
#define NITRO_PAD_H

#include "types.h"

/* The parts of NitroSDK's pad API that are inline functions, so that their
 * code is compiled into the game's. The ARM7 reads the X and Y buttons and the
 * lid's hinge and leaves them in shared memory, next to the ARM9's own keys. */

#define REG_KEYINPUT (*(vu16 *) 0x04000130)
#define HW_BUTTON_XY_BUF (*(vu16 *) 0x027FFFA8)

#define PAD_BUTTON_A 0x0001
#define PAD_BUTTON_B 0x0002
#define PAD_KEY_RIGHT 0x0010
#define PAD_KEY_LEFT 0x0020
#define PAD_KEY_UP 0x0040
#define PAD_KEY_DOWN 0x0080
#define PAD_BUTTON_X 0x0400
#define PAD_BUTTON_Y 0x0800

#define PAD_ALL_MASK 0x2FFF /* the buttons, the d-pad and the debug button */
#define PAD_DETECT_FOLD_MASK 0x8000

/* The buttons held down, a bit set for each: the hardware sets a bit for each
 * button that is up. */
static inline u16 PAD_Read(void) {
    return (u16) (((REG_KEYINPUT | HW_BUTTON_XY_BUF) ^ PAD_ALL_MASK) & PAD_ALL_MASK);
}

/* Whether the lid is closed. */
static inline BOOL PAD_DetectFold(void) {
    return (BOOL) ((HW_BUTTON_XY_BUF & PAD_DETECT_FOLD_MASK) >> 15);
}

#endif /* NITRO_PAD_H */
