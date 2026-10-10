#include "engine/digimon/game_data.h"
#include "engine/data.h"
#include "engine/gfx/gfx_files.h"
#include "engine/libs.h"

/* Returns the index of a Digimon's record by its id, or -1. */
s32 findDigimonIndex(s32 id) {
    s32 i;

    if (id == 0) {
        return -1;
    }
    for (i = 0; i < 40; i++) {
        if (id == SAVE->digimon[i].id) {
            return i;
        }
    }
    return -1;
}

/* Returns one of the 40 Digimon records, or NULL. */
void *getDigimonAt(s32 index) {
    if (index < 0) {
        return NULL;
    }
    if (index >= 40) {
        return NULL;
    }
    return &data_021db82c[index];
}

/* Returns the index of the first free Digimon record, or -1. */
s32 findFreeDigimonIndex(void) {
    s32 i;

    for (i = 0; i < 40; i++) {
        if (SAVE->digimon[i].id == 0) {
            return i;
        }
    }
    return -1;
}

/* Loads the record of an id from "/dat/en/<id / 8>", whose 8 records follow
 * a table of their offsets; the last file loaded stays in data_021db278. */
u8 *func_020a14e8(s32 id) {
    char name[9];
    char path[0x1B];
    s32 file  = id / 8;
    s32 index = id % 8;

    if (file != data_021da77c) {
        func_020e3a68(name, data_02137688, file);
        joinPath(path, data_0213768c, name);
        if (func_020440ec(path, data_021db278) == 0) {
            func_020e6250();
        }
        data_021da77c = file;
    }
    return data_021db278 + ((s32 *) data_021db278)[index];
}

/* Loads the record of an equipment item (0x32 to 0x1AC) from
 * "/dat/eq/<(id - 0x32) / 8>", or returns NULL for another item. */
u8 *func_020a142c(u32 id) {
    char name[9];
    char path[0x1B];
    s32 offset;
    s32 file;
    s32 index;

    if (id < 50 || id >= 429) {
        return NULL;
    }
    offset = id - 50;
    file   = offset / 8;
    index  = offset % 8;
    if (file != data_021da778) {
        func_020e3a68(name, data_02137678, file);
        joinPath(path, data_0213767c, name);
        if (func_020440ec(path, data_021da998) == 0) {
            func_020e6250();
        }
        data_021da778 = file;
    }
    return data_021da998 + ((s32 *) data_021da998)[index];
}

/* Returns the record of one of the 50 items that are not equipment, or NULL. */
void *func_020a1410(u32 item) {
    if (item < 50) {
        return data_0210bc6c[item];
    }
    return NULL;
}

/* Loads the digivolution record of a species from "/dat/sk/<id / 8>" (sk:
 * shinka, evolution); the last file loaded stays in data_021dac48. */
u8 *func_020a137c(s32 id) {
    char name[9];
    char path[0x1B];
    s32 file  = id / 8;
    s32 index = id % 8;

    if (file != data_021da788) {
        func_020e3a68(name, data_02137668, file);
        joinPath(path, data_0213766c, name);
        if (func_020440ec(path, data_021dac48) == 0) {
            func_020e6250();
        }
        data_021da788 = file;
    }
    return data_021dac48 + ((s32 *) data_021dac48)[index];
}

/* Returns the category of an item: 0 for the first 50 and 1 to 3 for the
 * three ranges of equipment, as the item_* help files split them. */
s32 func_020a1318(u32 item) {
    if (item < 50) {
        return 0;
    }
    if (item >= 50 && item < 187) {
        return 1;
    }
    if (item >= 187 && item < 355) {
        return 2;
    }
    if (item >= 355 && item < 429) {
        return 3;
    }
    return 0;
}

/* Loads the record of an id from "/dat/ec/<id / 8>"; it hangs when the file
 * can't be read. */
u8 *func_020a128c(u32 id) {
    char name[9];
    char path[0x43];
    u32 file  = id / 8;
    s32 index = (s32) id % 8;

    if (file != data_021da780) {
        func_020e3a68(name, data_02137658, file);
        joinPath(path, data_0213765c, name);
        if (func_020440ec(path, data_021daf28) == 0) {
            while (1) {
            }
        }
        data_021da780 = file;
    }
    return data_021daf28 + ((s32 *) data_021daf28)[index];
}

/* Returns one of the 0x1B3 records of data_02113698, or NULL. */
void *func_020a1268(u32 index) {
    if (index >= 0x1B3) {
        return NULL;
    }
    return data_02113698[index];
}

/* Returns one of the 0xB1 records of data_0210c11c, or NULL. */
void *func_020a1250(u32 index) {
    if (index >= 0xB1) {
        return NULL;
    }
    return data_0210c11c[index];
}

/* Returns the table of data_0210c6a4. */
s32 *func_020a1244(void) {
    return &data_0210c6a4;
}

/* Returns the 10 party slots. */
s32 *func_020a1238(void) {
    return data_021db804;
}

/* Returns the id of the index-th (0 to 2) Digimon of the first 5 party
 * slots, or 0. */
s32 func_020a11e0(s32 index) {
    s32 i;
    s16 count;
    s32 id;

    if (index > 2) {
        return 0;
    }
    for (i = 0, count = 0; i < 5; i++) {
        id = SAVE->party[i];
        if (id != 0) {
            if (index == count) {
                return id;
            }
            count++;
        }
    }
    return 0;
}
