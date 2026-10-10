#include "eggs/family_tree_sprites.h"
#include "eggs/egg_list.h"
#include "eggs/family_tree.h"
#include "engine/data.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/ui/buttons.h"
#include "engine/ui/gauge.h"
#include "engine/window/window.h"
#include "field/actors/actor_files.h"
#include "field/actors/actor_save_flash.h"

#define UI_FLAG_EGG_LIST 0xD
#define KEEP_GRAPHICS 1 /* a FamilyTree flag */

/* Returns whether the family tree, or the menu around the DigiEgg panel
 * (both kept in data_021da400), is open. */
BOOL func_02097ef0(void) {
    if (data_021da400 != 0) {
        return TRUE;
    }
    return FALSE;
}

/* Closes the family tree. */
void closeFamilyTree(void) {
    struct FamilyTree *tree;
    s32 i;

    tree = findTask(data_021da400);
    closeButtonGroup(tree->buttons);
    for (i = 0; i < FAMILY_TREE_SPRITES; i++) {
        if (tree->sprites[i] != 0xFFFF) {
            func_020c6fb8(tree->sprites[i]);
        }
    }
    func_020c2b64(tree->sprites[tree->selected]);
    closeWindow(tree->windows[0]);
    closeWindow(tree->windows[1]);
    closeWindow(tree->windows[2]);
    releaseGfxSlot(tree->gfxSlots[0]);
    releaseGfxSlot(tree->gfxSlots[1]);
    releaseGfxSlot(tree->gfxSlots[2]);
    if (!(tree->flags & KEEP_GRAPHICS)) {
        func_02097d2c();
    }
    endTask(tree);
    data_021da400 = 0;
}

/* Sets up the graphics of slots 4, 5, 0, 1 and 2 for the family tree. */
void func_02097d8c(void) {
    func_020a9c40(4, -1, 0x1F);
    func_020a9c40(5, -1, 0xF);
    func_020a9c40(0, -1, 0xF);
    func_020a9c40(1, -1, 0xF);
    func_020a9c40(2, -1, 0xF);
    func_020a9ae0(4, -1, 0x1F);
    func_020a9ae0(5, -1, 0xF);
    func_020a9ae0(0, -1, 0xF);
    func_020a9ae0(1, -1, 0xF);
    func_020a9ae0(2, -1, 0xF);
}

/* Undoes func_02097d8c. */
void func_02097d2c(void) {
    func_020a98a8(4);
    func_020a98a8(5);
    func_020a98a8(0);
    func_020a98a8(1);
    func_020a98a8(2);
    func_020a9844(4);
    func_020a9844(5);
    func_020a9844(0);
    func_020a9844(1);
    func_020a9844(2);
}

/* Opens the list of DigiEggs, unless it is open. */
void openEggList(s8 palette, s8 unk28, s16 unk2A) {
    struct EggList *list;

    if (getUiFlag(UI_FLAG_EGG_LIST) == TRUE) {
        return;
    }
    list          = createTask(func_02097810, 0x113);
    list->state   = 0;
    list->wait    = 0;
    list->palette = palette;
    list->unk28   = unk28;
    list->unk2A   = unk2A;
    data_021da404 = getTaskId(list);
    setUiFlag(UI_FLAG_EGG_LIST);
}
