#ifndef MENUS_FARM_STATS_ABILITY_PAGES_H
#define MENUS_FARM_STATS_ABILITY_PAGES_H

/* The View Stats screen's button pages: the five ability pages (openAbilityPages)
 * and the six buttons of func_020ca0a8. */

#include "engine/data.h"
#include "types.h"

struct StatsScreen;

/* The ability pages: one for each of a Digimon's four abilities and one for its
 * species'. Their tabs are colors 0x37 to 0x3B, which func_020846bc lights. */
#define ABILITY_PAGE_COUNT 5
#define ABILITY_TAB_COLORS 0x37

/* The six buttons of func_020ca0a8, colors 0x31 to 0x36. */
#define MENU_TAB_COUNT 6
#define MENU_TAB_COLORS 0x31

/* How much func_020846bc brightens a lit tab's colors. */
#define TAB_LIGHT 8

void func_020c9b88(s16 touched, s16 cursor, struct ButtonGroup *group);
void closeAbilityPages(struct StatsScreen *screen);
void func_020ca070(struct StatsScreen *screen);
void openAbilityPages(struct StatsScreen *screen);

#endif /* MENUS_FARM_STATS_ABILITY_PAGES_H */
