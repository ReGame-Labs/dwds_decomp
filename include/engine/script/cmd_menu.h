#ifndef ENGINE_SCRIPT_CMD_MENU_H
#define ENGINE_SCRIPT_CMD_MENU_H

/* The script engine's menu commands: the list menu of command 0x110 and the
 * two-answer question of command 0x10E. */

#include "engine/data.h"
#include "types.h"

struct ScriptThread;

#define LIST_MENU_ENTRY_COUNT 17

/* The list menu func_0208a948 runs. */
struct ListMenuTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ u8 unk20[0x44];
    /* 0x64 */ s8 unk64;
    /* 0x65 */ u8 unk65;
    /* 0x66 */ s16 unk66;
    /* 0x68 */ s16 count;
    /* 0x6A */ s16 entries[LIST_MENU_ENTRY_COUNT];
    /* 0x8C */ u8 unk8C;
    /* 0x8D */ u8 unk8D;
    /* 0x8E */ s16 thread; /* woken when the menu is done */
};

/* func_0208ae40's task, set up by command 0x10E (func_0208af6c). */
struct QuestionTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ u8 unk20[0x44];
    /* 0x64 */ u16 text;
    /* 0x66 */ s16 unk66;
    /* 0x68 */ u16 unk68;
    /* 0x6A */ s16 thread;
};

s32 func_0208ae28(struct ScriptThread *thread);
void func_0208a948(void);
s32 func_0208ade0(struct ScriptThread *thread);
void func_0208ae40(void);
void func_0208a8b0(struct ListMenuTask *task);

#endif /* ENGINE_SCRIPT_CMD_MENU_H */
