#ifndef TITLE_TITLE_MENU_H
#define TITLE_TITLE_MENU_H

/* The window system's start (func_020aa6a0), the title menu, and the
 * defaults windows load their graphics with. */

#include "engine/data.h"
#include "types.h"

/* The title menu (func_020aab34), started by openTitleMenu under UI flag 3:
 * it starts a new game (initNewGame) and the name entry. */
struct TitleMenu {
    struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 wait;
    /* 0x20 */ s8 gfxSlot;
    u8 unk21[2];
    /* 0x23 */ u8 window;  /* 0xFF for none */
    /* 0x24 */ s32 buttons; /* touch buttons (createButtonGroup) */
    /* 0x28 */ s8 unk28;
    /* 0x29 */ s8 unk29;
    /* 0x2A */ s8 unk2A;
    u8 unk2B;
    /* 0x2C */ s8 buttonIds[4];
    /* 0x30 */ s8 choice;  /* -1 while choosing, 99 cancelled */
    /* 0x32 */ s16 shown;  /* the choice under the stylus */
    /* 0x34 */ s32 sprites[2];
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 unk3E;
};

void func_020aa2e4(s8 *value, s8 *value2);
void func_020aa308(s8 value, s8 value2);
void func_020aa340(s8 value, s8 value2);
s32 func_020aa6a0();
s32 func_020aab34();
void closeTitleMenu(void);
void func_020aaa34(s32 button, s16 index, struct ButtonGroup *group);
void func_020aa968(s32 button, s16 index, struct ButtonGroup *group);
void func_020aa894(s32 button, s16 index, struct ButtonGroup *group);
void func_020aa7bc(s32 planes, s32 percent);

#endif /* TITLE_TITLE_MENU_H */
