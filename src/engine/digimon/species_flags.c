#include "engine/digimon/species_flags.h"
#include "engine/bg/bg_screen.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/display_modes.h"
#include "engine/ui/gauge.h"

/* Returns the id of the index-th (0 to 2) Digimon of party slots 5 to 7, or
 * 0. */
s32 func_020a1188(s32 index) {
    s32 i;
    s16 count;
    s32 id;

    if (index > 2) {
        return 0;
    }
    for (i = 5, count = 0; i < 8; i++) {
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

/* Returns a free party slot, or -1: one of 0 to 4 while fewer than 3 of them
 * are in use, else one of 5 to 7. */
s32 func_020a10d4(void) {
    s32 used;
    s32 i;

    for (i = 0, used = 0; i < 5; i++) {
        if (SAVE->party[i] != 0) {
            used++;
        }
    }
    if (used >= 3) {
        for (; i < 8; i++) {
            if (SAVE->party[i] == 0) {
                return i;
            }
        }
    } else {
        for (i = 0; i < 5; i++) {
            if (SAVE->party[i] == 0) {
                return i;
            }
        }
    }
    return -1;
}

/* Puts a Digimon in a free party slot (func_020a10d4) and returns the slot,
 * or -1. */
s32 func_020a10ac(s32 id) {
    s32 slot;

    slot = func_020a10d4();
    if (slot == -1) {
        return -1;
    }
    data_021db804[slot] = id;
    return slot;
}

/* Swaps the Digimon of two of party slots 0 to 7. */
void func_020a1070(s32 a, s32 b) {
    s32 id;

    if (a < 0 || a > 7 || b < 0 || b > 7) {
        return;
    }
    id               = data_021db804[a];
    data_021db804[a] = data_021db804[b];
    data_021db804[b] = id;
}

/* Counts the listed species whose flag of the 0x640 range is set. */
s16 func_020a101c(void) {
    s32 flag;
    s16 count;

    for (flag = 0x640, count = 0; flag < 0x640 + 426; flag++) {
        if (((struct SpeciesData *) loadSpeciesData(flag - 0x640))->listed != 0 && getGameFlag(flag) != 0) {
            count++;
        }
    }
    return count;
}

/* Sets the flags of the 0x640 and 0x7D0 ranges of the first species with a
 * species' func_020a3224 key; never for the DigiEggs (378 to 425). */
void func_020a0fd8(s32 species) {
    s32 kind;

    kind = func_020a31e8(func_020a3224(species));
    if (species >= 378 && species <= 425) {
        return;
    }
    setGameFlag(kind + 0x640);
    func_020a0f1c(species);
}

/* Sets the flag of the 0x7D0 range of the first species with a species'
 * func_020a3224 key; never for the DigiEggs. */
void func_020a0f1c(s32 species) {
    s32 kind;

    kind = func_020a31e8(func_020a3224(species));
    if (species >= 378 && species <= 425) {
        return;
    }
    setGameFlag(kind + 0x7D0);
}

/* Returns the flag of the 0x7D0 range of a species. */
s32 func_020a0f0c(s32 species) {
    return getGameFlag(species + 0x7D0);
}

/* Sets the flag of the 0x4B0 range of a species unless func_020a0f98 says
 * it is set. */
void func_020a0ee0(s32 species) {
    if (func_020a0f98(species) != 0) {
        return;
    }
    setGameFlag(func_020a31e8(func_020a3224(species)) + 0x4B0);
}

/* Returns the flag of the 0x4B0 range of a species, by the first species
 * with the same func_020a3224 key. */
s32 func_020a0ec0(s32 species) {
    return getGameFlag(func_020a31e8(func_020a3224(species)) + 0x4B0);
}

/* Returns the save's unk3E34. */
u8 func_020a0eb0(void) {
    return SAVE->unk3E34;
}

/* Shows icon index (0 to 7) of data_02126ff8 as a sub-screen sprite through
 * createMainSprite, or moves sprite id to it. */
s32 func_020a0d88(u32 index, s32 x, s32 y, s32 palette, u16 id) {
    s32 handle;

    if (index >= 8) {
        return -1;
    }
    handle = id;
    if (handle == 0xFFFF) {
        handle = createMainSprite(data_02126ff8[index], x, y, palette, 0);
    } else {
        createMainSpriteAt(data_02126ff8[index], x, y, palette, 0, handle);
    }
    return handle;
}

/* The same as func_020a0d88 through createSubSprite. */
s32 func_020a0d10(u32 index, s32 x, s32 y, s32 palette, u16 id) {
    s32 handle;

    if (index >= 8) {
        return -1;
    }
    handle = id;
    if (handle == 0xFFFF) {
        handle = createSubSprite(data_02126ff8[index], x, y, palette, 0);
    } else {
        createSubSpriteAt(data_02126ff8[index], x, y, palette, 0, handle);
    }
    return handle;
}

/* Shows sprite kind 0x157 at animation index (0 to 8) of data_02127008,
 * through createMainSprite. */
s32 func_020a0c88(u32 index, s32 x, s32 y, s32 palette, u16 id) {
    s32 handle;

    if (index >= 9) {
        return -1;
    }
    handle = id;
    if (handle == 0xFFFF) {
        handle = createMainSprite(0x157, x, y, palette, 0);
    } else {
        createMainSpriteAt(0x157, x, y, palette, 0, handle);
    }
    setMainSpriteAnim(handle, data_02127008[index], -1);
    return handle;
}

/* The same as func_020a0c88 through createSubSprite. */
s32 func_020a0c00(u32 index, s32 x, s32 y, s32 palette, u16 id) {
    s32 handle;

    if (index >= 9) {
        return -1;
    }
    handle = id;
    if (handle == 0xFFFF) {
        handle = createSubSprite(0x157, x, y, palette, 0);
    } else {
        createSubSpriteAt(0x157, x, y, palette, 0, handle);
    }
    setSubSpriteAnim(handle, data_02127008[index], -1);
    return handle;
}

/* Shows icon index (0 to 9) of data_0212701c through createMainSprite. */
s32 func_020a0b20(u32 index, s32 x, s32 y, s32 palette, u16 id) {
    s32 handle = id;

    if (index >= 9) {
        index = 9;
    }
    if (handle == 0xFFFF) {
        handle = createMainSprite(data_0212701c[index], x, y, palette, 0);
    } else {
        createMainSpriteAt(data_0212701c[index], x, y, palette, 0, handle);
    }
    return handle;
}

/* The same as func_020a0b20 through createSubSprite. */
s32 func_020a0ab0(u32 index, s32 x, s32 y, s32 palette, u16 id) {
    s32 handle = id;

    if (index >= 9) {
        index = 9;
    }
    if (handle == 0xFFFF) {
        handle = createSubSprite(data_0212701c[index], x, y, palette, 0);
    } else {
        createSubSpriteAt(data_0212701c[index], x, y, palette, 0, handle);
    }
    return handle;
}

/* Changes sprite id to icon index of data_0212701c, in its place. */
void func_020a0a58(u32 index, s32 id) {
    struct Sprite *sprite = getMainSprite(id);

    if (index >= 9) {
        index = 9;
    }
    createMainSpriteAt(data_0212701c[index], sprite->x, sprite->y, sprite->palette, 0, id);
}

/* The same as func_020a0a58 on the other screen. */
void func_020a0a00(u32 index, s32 id) {
    struct Sprite *sprite = getSubSprite(id);

    if (index >= 9) {
        index = 9;
    }
    createSubSpriteAt(data_0212701c[index], sprite->x, sprite->y, sprite->palette, 0, id);
}

/* Adds to a Digimon's unk72, kept within 0 to 100. */
s16 func_020a09c0(s32 id, s32 amount) {
    struct Digimon *digimon;

    digimon = getDigimon(id);
    digimon->unk72 += amount;
    if (digimon->unk72 > 100) {
        digimon->unk72 = 100;
    }
    if (digimon->unk72 < 0) {
        digimon->unk72 = 0;
    }
    return digimon->unk72;
}
