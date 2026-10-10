#ifndef MENUS_DIGICONVERT_DIGICONVERT_OPEN_H
#define MENUS_DIGICONVERT_DIGICONVERT_OPEN_H

#include "types.h"

struct Digiconvert;

s32 openDigiconvert();
void onDigiconvertEnd(void);
u8 isDigiconvertClosed(void);
void unloadDigiconvert(struct Digiconvert *digiconvert);
void closeDigiconvert(struct Digiconvert *digiconvert);
void reloadDigiconvert(void);
void freeSaveBuffer(void);
s32 allocSaveBuffer(void);

#endif /* MENUS_DIGICONVERT_DIGICONVERT_OPEN_H */
