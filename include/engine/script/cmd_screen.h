#ifndef ENGINE_SCRIPT_CMD_SCREEN_H
#define ENGINE_SCRIPT_CMD_SCREEN_H

/* The script engine's screen commands: palette fades of the threads' slots
 * and of the screens, background scrolls, the name entry, programs, the
 * party and touch jumps, and the story flags. */

#include "types.h"

struct ScriptThread;

s32 func_02087adc(struct ScriptThread *thread);
s32 cmdResetGame(struct ScriptThread *thread);
s32 cmdSuspend(struct ScriptThread *thread);
s32 func_02087ed4(struct ScriptThread *thread);
s32 func_02087f00(struct ScriptThread *thread);
s32 func_02089130(struct ScriptThread *thread);
s32 func_02089188(struct ScriptThread *thread);
s32 func_02089280(struct ScriptThread *thread);
void func_020892a0(void);
void func_02087b74(void);
s32 func_02087ca0(struct ScriptThread *thread);
s32 cmdWakeParent(struct ScriptThread *thread);
s32 func_0208909c(struct ScriptThread *thread);
s32 func_020890d0(struct ScriptThread *thread);
s32 cmdEnterPlayerName(struct ScriptThread *thread);
s32 func_02087b14(struct ScriptThread *thread);
s32 func_02087e74(struct ScriptThread *thread);
s32 func_02087e04(struct ScriptThread *thread);
s32 cmdJumpUnlessTouchedIn(struct ScriptThread *thread);
s32 func_02087f20(struct ScriptThread *thread);
s32 cmdFadeMainScreenOut(struct ScriptThread *thread);
s32 cmdFadeSubScreenOut(struct ScriptThread *thread);
s32 cmdFadeMainScreenIn(struct ScriptThread *thread);
s32 cmdFadeSubScreenIn(struct ScriptThread *thread);
s32 cmdSetSubBgScroll(struct ScriptThread *thread);
s32 cmdSetMainBgScroll(struct ScriptThread *thread);
void func_02088414(void);
void func_02088610(void);
s32 func_0208880c(struct ScriptThread *thread);
s32 func_020888b8(struct ScriptThread *thread);
void func_02088964(void);
void func_02088b8c(void);
s32 func_02088db4(struct ScriptThread *thread);
s32 func_02088e60(struct ScriptThread *thread);
s32 func_02087f5c(struct ScriptThread *thread);
s32 cmdScrollSubBg(struct ScriptThread *thread);
s32 cmdScrollMainBg(struct ScriptThread *thread);
s32 func_0208924c(struct ScriptThread *thread);

#endif /* ENGINE_SCRIPT_CMD_SCREEN_H */
