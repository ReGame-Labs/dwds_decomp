#ifndef MENUS_DIGIMON_MENU_DIGIVOLVE_H
#define MENUS_DIGIMON_MENU_DIGIVOLVE_H

#include "engine/data.h"
#include "types.h"

/* The start of the conversion scene (startConvert), and the digivolution
 * scene the Digimon menu starts (startMenuDigivolve and func_0204801c) with its
 * task. */

#define MENU_DIGIVOLVE_TASK_PRIORITY 0x120

/* The scene's task (tickMenuDigivolve) when the Digimon menu starts it. */
struct MenuDigivolveTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26; /* from the target's stage */
    /* 0x28 */ s32 unk28; /* func_020a31d8's, of the species */
    /* 0x2C */ s32 unk2C; /* and of the target */
    /* 0x30 */ s32 species;
    /* 0x34 */ s32 target; /* the species it digivolves into */
    /* 0x38 */ u8 unk38[0x18];
    /* 0x50 */ u8 unk50;
};

void startConvert(s32 species);
u8 isMenuDigivolveDone(void);
s32 tickMenuDigivolve();

#endif /* MENUS_DIGIMON_MENU_DIGIVOLVE_H */
