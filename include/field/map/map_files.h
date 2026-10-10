#ifndef FIELD_MAP_MAP_FILES_H
#define FIELD_MAP_MAP_FILES_H

/* A map's files from /dat/map/: its .a file and its rectangles. */

#include "types.h"

void func_ov000_0220168c(void);
void func_ov000_022016ac(void);
void func_ov000_022016c0(void);
void func_ov000_022016e0(void);
s32 func_ov000_02201890();
s32 func_ov000_02201e40();
s32 func_ov000_02201f00();
u16 *func_ov000_0220150c(void);
u16 *func_ov000_02201524(void);
void restoreSubMapRects(void);
void saveSubMapRects(void);
void getSubMapRect(s32 index, s16 *left, s16 *top, s16 *right, s16 *bottom, u16 *value);
void getMainMapRect(s32 index, s16 *left, s16 *top, s16 *right, s16 *bottom, u16 *value);
void setSubMapRect(s32 index, s16 left, s16 top, s16 right, s16 bottom, u16 value);
void func_ov000_02201fc0(s32 map);
void func_ov000_02202048(s32 map);

#endif /* FIELD_MAP_MAP_FILES_H */
