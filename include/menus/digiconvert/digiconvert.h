#ifndef MENUS_DIGICONVERT_DIGICONVERT_H
#define MENUS_DIGICONVERT_DIGICONVERT_H

/* The Digiconvert screen's task and backgrounds. */

#include "types.h"

struct Digiconvert;

void clearDigiconvertScreens(void);
void freeDigiconvertBgs(struct Digiconvert *digiconvert);
void loadDigiconvertBgs(struct Digiconvert *digiconvert);
void func_0205f6cc(void);
void func_0205f6b0(void);

#endif /* MENUS_DIGICONVERT_DIGICONVERT_H */
