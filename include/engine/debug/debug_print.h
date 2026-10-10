#ifndef ENGINE_DEBUG_DEBUG_PRINT_H
#define ENGINE_DEBUG_DEBUG_PRINT_H

#include "types.h"

/* The debug console: text printed on a BG of either screen, 32 columns by
 * 24 rows, redrawn each frame by a task. */

#define DEBUG_PRINT_COLUMNS 32
#define DEBUG_PRINT_ROWS 24
#define DEBUG_PRINT_BLINK 0x100 /* an attribute bit */
#define DEBUG_PRINT_TASK_PRIORITY 0xF00A

void stopDebugPrint(void);
void closeDebugPrint(void);
u16 getDebugPrintAttr(void);
void setDebugPrintAttr(s16 attr);
void tickDebugPrint(void);
void clearDebugPrintBg(void);
void openDebugPrint(s32 bg);
s32 initDebugPrintBg();
void clearDebugPrintScreen(void);
void initTouchPanel(void);
s32 printDebug(); /* (x, y, text) */
s32 printDebugf(s32 x, s32 y, const char *fmt, ...);

#endif /* ENGINE_DEBUG_DEBUG_PRINT_H */
