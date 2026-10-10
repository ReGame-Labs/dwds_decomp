#ifndef ENGINE_SCRIPT_CMD_FADE_H
#define ENGINE_SCRIPT_CMD_FADE_H

/* The script engine's palette fade out and map fade commands, and the
 * commands that show and close messages. */

#include "types.h"

struct ScriptThread;

s32 func_0208f6d8(struct ScriptThread *thread);
s32 func_0208f6fc(struct ScriptThread *thread);
s32 func_0208ef20(struct ScriptThread *thread);
s32 func_0208ef8c(struct ScriptThread *thread);
s32 func_0208f2e0(struct ScriptThread *thread);
s32 func_0208f338(struct ScriptThread *thread);
s32 func_0208f390(struct ScriptThread *thread);
s32 func_0208f3ec(struct ScriptThread *thread);
void func_0208eff8(void);
void func_0208f030(void);
void func_0208f5f8(s16 interval, s16 step);
void func_0208f668(s16 interval, s16 step);
s32 func_0208f068();
s32 func_0208f448(struct ScriptThread *thread);
s32 func_0208f4e4(struct ScriptThread *thread);
s32 func_0208f580(struct ScriptThread *thread);
s32 func_0208f5bc(struct ScriptThread *thread);
void func_0208ee58(void);
void func_0208eebc(void);
s32 func_0208f238(struct ScriptThread *thread);
s32 func_0208f28c(struct ScriptThread *thread);

#endif /* ENGINE_SCRIPT_CMD_FADE_H */
