#ifndef ENGINE_TEXT_TEXT_ARGS_H
#define ENGINE_TEXT_TEXT_ARGS_H

/* Texts: the names of stages, exp curves, tamer ranks and areas, the text
 * arguments, and the start of the link exchange. */

#include "types.h"

s32 func_0209caf0();
void *getAreaName(s32 index);
void *func_0209cf94(s16 index, s32 value, s32 digits, s32 flags);
void *func_0209cfc4(s16 index, s32 value, s32 digits);
void *setTextArg(s16 index, void *text);
void func_0209d080(void *text, void *picture);
/* Writes a 64-bit number as text in digits digits; flags: 1 leading zeros,
 * 2, 4 and 8 add the characters 0xC, 0x35 and 0x34 after it. */
u16 *func_0209d168(s32 valueLow, s32 valueHigh, s32 digits, u16 *buffer, s32 flags);
void func_0209ca70(void);
void func_0209cab0(void);
void *func_0209cd08(s32 index);
void *getTextArg(s16 index);
s32 func_0209d02c();
void *getTamerRankName(u32 index);
void *getExpCurveName(u32 index);
void *getStageName(u32 index);
u16 *func_0209d0ec();

#endif /* ENGINE_TEXT_TEXT_ARGS_H */
