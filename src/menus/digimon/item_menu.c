#include "menus/digimon/item_menu.h"
#include "engine/bg/bg_affine.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/system/system.h"
#include "menus/digimon/data.h"

/* Loads the graphics of the item menu's four backgrounds: entries 0xF, 0xF, 4
 * and 0x63 of data_0213537c (/dat/bg/m_bg02 twice, md_flame00, and b_hani01
 * with b_dwaku's palette). */
void loadItemMenuBgs(struct ItemMenu *menu) {
    const char **files;

    files                             = func_0204871c(0xF);
    menu->graphics->bg[0].paletteFile = loadPaletteFile(&menu->graphics->bg[0].palette, files[0]);
    menu->graphics->bg[0].charFile    = loadCharFile(&menu->graphics->bg[0].chars, files[1]);
    menu->graphics->bg[0].screenFile  = loadScreenFile(&menu->graphics->bg[0].screen, files[2]);

    files                             = func_0204871c(0xF);
    menu->graphics->bg[1].paletteFile = loadPaletteFile(&menu->graphics->bg[1].palette, files[0]);
    menu->graphics->bg[1].charFile    = loadCharFile(&menu->graphics->bg[1].chars, files[1]);
    menu->graphics->bg[1].screenFile  = loadScreenFile(&menu->graphics->bg[1].screen, files[2]);

    files                             = func_0204871c(4);
    menu->graphics->bg[2].paletteFile = loadPaletteFile(&menu->graphics->bg[2].palette, files[0]);
    menu->graphics->bg[2].charFile    = loadCharFile(&menu->graphics->bg[2].chars, files[1]);
    menu->graphics->bg[2].screenFile  = loadScreenFile(&menu->graphics->bg[2].screen, files[2]);

    files                             = func_0204871c(0x63);
    menu->graphics->bg[3].paletteFile = loadPaletteFile(&menu->graphics->bg[3].palette, files[0]);
    menu->graphics->bg[3].charFile    = loadCharFile(&menu->graphics->bg[3].chars, files[1]);
    menu->graphics->bg[3].screenFile  = loadScreenFile(&menu->graphics->bg[3].screen, files[2]);
}

/* Frees the item menu's backgrounds. */
void freeItemMenuBgs(struct ItemMenu *menu) {
    stopSubPaletteEffectsButFades(menu->subPaletteEffect);
    stopMainPaletteEffectsButFades(menu->mainPaletteEffect);
    if (menu->graphics->bg[0].paletteFile != NULL) {
        heapFree(menu->graphics->bg[0].paletteFile);
        menu->graphics->bg[0].paletteFile = NULL;
    }
    if (menu->graphics->bg[0].charFile != NULL) {
        heapFree(menu->graphics->bg[0].charFile);
        menu->graphics->bg[0].charFile = NULL;
    }
    if (menu->graphics->bg[0].screenFile != NULL) {
        heapFree(menu->graphics->bg[0].screenFile);
        menu->graphics->bg[0].screenFile = NULL;
    }
    if (menu->graphics->bg[1].paletteFile != NULL) {
        heapFree(menu->graphics->bg[1].paletteFile);
        menu->graphics->bg[1].paletteFile = NULL;
    }
    if (menu->graphics->bg[1].charFile != NULL) {
        heapFree(menu->graphics->bg[1].charFile);
        menu->graphics->bg[1].charFile = NULL;
    }
    if (menu->graphics->bg[1].screenFile != NULL) {
        heapFree(menu->graphics->bg[1].screenFile);
        menu->graphics->bg[1].screenFile = NULL;
    }
    if (menu->graphics->bg[2].paletteFile != NULL) {
        heapFree(menu->graphics->bg[2].paletteFile);
        menu->graphics->bg[2].paletteFile = NULL;
    }
    if (menu->graphics->bg[2].charFile != NULL) {
        heapFree(menu->graphics->bg[2].charFile);
        menu->graphics->bg[2].charFile = NULL;
    }
    if (menu->graphics->bg[2].screenFile != NULL) {
        heapFree(menu->graphics->bg[2].screenFile);
        menu->graphics->bg[2].screenFile = NULL;
    }
    if (menu->graphics->bg[3].paletteFile != NULL) {
        heapFree(menu->graphics->bg[3].paletteFile);
        menu->graphics->bg[3].paletteFile = NULL;
    }
    if (menu->graphics->bg[3].charFile != NULL) {
        heapFree(menu->graphics->bg[3].charFile);
        menu->graphics->bg[3].charFile = NULL;
    }
    if (menu->graphics->bg[3].screenFile != NULL) {
        heapFree(menu->graphics->bg[3].screenFile);
        menu->graphics->bg[3].screenFile = NULL;
    }
}
