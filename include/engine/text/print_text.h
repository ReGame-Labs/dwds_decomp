#ifndef ENGINE_TEXT_PRINT_TEXT_H
#define ENGINE_TEXT_PRINT_TEXT_H

/* Printing texts into text canvases, the text flags, and setting up numbers drawn
 * with sprites. */

#include "types.h"

void func_020a57e0(s16 value);
void func_020a57f0(s16 flags);
void func_020a5800(void);
void func_020a5818(void);
void func_020a5830(void);
u16 func_020a522c(void *canvas, s32 text);
u16 func_020a5268(void *canvas, void *text, s32 value);
u16 func_020a52c0(void *canvas, void *text);
u16 func_020a5304(void *canvas, void *text);
s32 func_020a5338();
void func_020a503c(void *number); /* a struct NumberSprite */
void func_020a5134(void *number); /* a struct NumberSprite */

#endif /* ENGINE_TEXT_PRINT_TEXT_H */
