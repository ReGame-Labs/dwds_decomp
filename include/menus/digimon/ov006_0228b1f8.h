#ifndef MENUS_DIGIMON_OV006_0228B1F8_H
#define MENUS_DIGIMON_OV006_0228B1F8_H

/* Whether the Digimon menu has closed, a tap in a rectangle, and the buttons
 * of the status screen's techniques. */

#include "types.h"

struct ButtonGroup;
struct StatusScreen;

u8 isDigimonMenuClosed(void);
BOOL isRectTappedInclusive(s32 x, s32 y, s32 width, s32 height);
void closeStatusTechniqueButtons(struct StatusScreen *screen);
void func_ov006_0228b468(s16 touched, s16 cursor, struct ButtonGroup *group);
void openStatusTechniqueButtons(struct StatusScreen *screen);

#endif /* MENUS_DIGIMON_OV006_0228B1F8_H */
