#ifndef MENUS_DIGICONVERT_DIGICONVERT_VIEW_H
#define MENUS_DIGICONVERT_DIGICONVERT_VIEW_H

/* The Digiconvert screen's windows, scroll bar and lists. */

#include "types.h"

struct Digiconvert;

void freeDigiconvertLists(struct Digiconvert *digiconvert);
void freeDigiconvertScrollBar(struct Digiconvert *digiconvert);
void func_0205f5e8(void);
void func_0205f630(void);
void func_0205f348(struct Digiconvert *digiconvert);
void createDigiconvertScrollBar(struct Digiconvert *digiconvert);
void func_0205f364(struct Digiconvert *digiconvert);
void func_0205f4b0(s16 x, s16 y);
void func_0205f51c(s16 x, s16 y);
void func_0205f588(s16 x, s16 y);
void createDigiconvertLists(struct Digiconvert *digiconvert);

#endif /* MENUS_DIGICONVERT_DIGICONVERT_VIEW_H */
