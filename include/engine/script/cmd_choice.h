#ifndef ENGINE_SCRIPT_CMD_CHOICE_H
#define ENGINE_SCRIPT_CMD_CHOICE_H

/* The script engine's choice commands: the touch-button choice, jumps on
 * values, and the clearing of a few actor flags. */

#include "types.h"

#include "engine/data.h"

struct ScriptThread;

/* The touch-button choice menu func_0208b7a0 runs, started by command 0x125;
 * CHOICE_MENU_TASK holds its task id. */
struct ChoiceMenuTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ u8 unk20[0x44];
    /* 0x64 */ s16 kind; /* 5 calls func_020878d4 */
    /* 0x66 */ s16 unk66;
    /* 0x68 */ s16 unk68;
    /* 0x6A */ s16 unk6A;
    /* 0x6C */ u16 unk6C; /* a row of data_02116b7c; with bit 0x8 the B button
                           * picks nothing */
    /* 0x6E */ u16 unk6E;
    /* 0x70 */ s16 unk70;
    /* 0x72 */ s16 thread; /* woken when the menu is done */
    /* 0x74 */ u8 unk74;
    /* 0x75 */ s8 unk75;
    /* 0x76 */ u8 window;
    /* 0x77 */ s8 count;
    /* 0x78 */ struct ButtonGroup *buttons;
    /* 0x7C */ s8 choice; /* -1 until one is picked */
    /* 0x7D */ s8 sprite; /* the cursor's */
};

s32 func_0208be30(struct ScriptThread *thread);
s32 func_0208bee4(struct ScriptThread *thread);
s32 func_0208bf2c(struct ScriptThread *thread);
s32 func_0208bf80(struct ScriptThread *thread);

#endif /* ENGINE_SCRIPT_CMD_CHOICE_H */
