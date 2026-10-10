#ifndef ENGINE_SCRIPT_INTERPRETER_H
#define ENGINE_SCRIPT_INTERPRETER_H

/* The script interpreter: its threads, its task and the event scripts' table.
 * From func_02095728 on, the field's popup of func_02095c4c. */

#include "engine/data.h"
#include "types.h"

/* An operand that names global variable n. */
#define SCRIPT_GLOBAL(n) (SCRIPT_GLOBAL_VAR_FIRST + (n))

/* The interpreter's task, tickScripts, whose id is SCRIPT_TASK. */
struct ScriptTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state; /* 0x12C running, 0x1F4 paused */
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
};

/* func_02095c4c's popup on the field, whose id is data_021da400. */
struct FieldPopupTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s8 unk20[4];
    /* 0x24 */ u16 unk24;
    /* 0x26 */ s8 font;    /* releaseGfxSlot's */
    /* 0x27 */ u8 unk27;
    /* 0x28 */ u8 window;  /* closeWindow's */
    /* 0x2C */ s32 buttons; /* closeButtonGroup's */
    /* 0x30 */ s16 sprites[16]; /* -1 where none */
};

void setScriptGlobal(s32 var, s16 value);
void endScriptThread(u8 index);
u8 startScriptThread(u16 *pc, s32 first);
void resumeScripts(void);
void pauseScripts(void);
void func_02095798(s32 id);
struct ScriptThread *getScriptThread(u32 index);
/* Returns the new thread's index as an int: startEventScript, above it in the
 * source, masks the result to a u8 as for an implicit declaration. */
s32 startEventScriptFrom(s32 script, s32 first);
u8 startEventScript(s32 script);
s32 func_020957b0();
void func_020957f0(void);
BOOL func_0209585c(void);
s32 getEventScriptOffset(s32 index);
s32 func_02095728(s32 id);
void func_02095c4c();
s32 findEventScript(s32 offset);

#endif /* ENGINE_SCRIPT_INTERPRETER_H */
