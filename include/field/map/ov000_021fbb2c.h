#ifndef FIELD_MAP_OV000_021FBB2C_H
#define FIELD_MAP_OV000_021FBB2C_H

/* Stopping and restoring the screens' maps, and their tasks. */

#include "types.h"

struct ScriptThread;

void func_ov000_021fbd2c(void);
void func_ov000_021fbe30(s32 offset);
void stopSubMap(void);
void stopMainMap(void);
s32 func_ov000_021fc028();
s32 tickSubMap();
s32 func_ov000_021fbdf8();
s32 func_ov000_021fbef8();
void func_ov000_021fbb2c(s16 x, s16 y, s32 arg2);
void func_ov000_021fbcfc(s32 index, s16 value);
void func_ov000_021fbd14(s32 index, s16 value);
void func_ov000_021fbd40(struct ScriptThread *thread);
void restoreSubMap(void);
void func_ov000_021fbe88(void);
void func_ov000_021fbec0(void);

#endif /* FIELD_MAP_OV000_021FBB2C_H */
