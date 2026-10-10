#include "eggs/family_tree.h"
#include "engine/data.h"
#include "engine/system/system.h"

/* Opens a Digimon's family tree. */
void openFamilyTree(struct Digimon *digimon, s8 palette, s8 palette2, s8 unk2C, u8 unk2D, u16 flags) {
    struct FamilyTree *tree;

    tree           = createTask(&func_02098914, 0x113);
    tree->state    = 0;
    tree->wait     = 0;
    tree->digimon  = digimon;
    tree->palette  = palette;
    tree->palette2 = palette2;
    tree->unk2C    = unk2C;
    tree->unk2D    = unk2D;
    tree->flags    = flags;
    data_021da400  = getTaskId(tree);
}
