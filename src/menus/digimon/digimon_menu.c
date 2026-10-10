#include "menus/digimon/digimon_menu.h"
#include "engine/bg/bg_affine.h"
#include "engine/data.h"
#include "engine/system/system.h"
#include "menus/digimon/data.h"

/* Loads the graphics of the Digimon menu's four backgrounds: entries 0xF, 0xF,
 * 4 and 0x63 of data_0213537c (/dat/bg/m_bg02 twice, md_flame00, and b_hani01
 * with b_dwaku's palette), as loadItemMenuBgs does for the item menu. */
void loadDigimonMenuBgs(struct DigimonMenu *menu) {
    const char **files;

    files                         = func_0204871c(0xF);
    menu->work->bg[0].paletteFile = loadPaletteFile(&menu->work->bg[0].palette, files[0]);
    menu->work->bg[0].charFile    = loadCharFile(&menu->work->bg[0].chars, files[1]);
    menu->work->bg[0].screenFile  = loadScreenFile(&menu->work->bg[0].screen, files[2]);
    files                         = func_0204871c(0xF);
    menu->work->bg[1].paletteFile = loadPaletteFile(&menu->work->bg[1].palette, files[0]);
    menu->work->bg[1].charFile    = loadCharFile(&menu->work->bg[1].chars, files[1]);
    menu->work->bg[1].screenFile  = loadScreenFile(&menu->work->bg[1].screen, files[2]);
    files                         = func_0204871c(4);
    menu->work->bg[2].paletteFile = loadPaletteFile(&menu->work->bg[2].palette, files[0]);
    menu->work->bg[2].charFile    = loadCharFile(&menu->work->bg[2].chars, files[1]);
    menu->work->bg[2].screenFile  = loadScreenFile(&menu->work->bg[2].screen, files[2]);
    files                         = func_0204871c(0x63);
    menu->work->bg[3].paletteFile = loadPaletteFile(&menu->work->bg[3].palette, files[0]);
    menu->work->bg[3].charFile    = loadCharFile(&menu->work->bg[3].chars, files[1]);
    menu->work->bg[3].screenFile  = loadScreenFile(&menu->work->bg[3].screen, files[2]);
}
