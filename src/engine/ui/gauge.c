#include "engine/ui/gauge.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/save/game_state.h"
#include "engine/save/progress.h"
#include "engine/system/display.h"
#include "engine/system/system.h"
#include "engine/ui/digimon_list.h"
#include "engine/window/window.h"
#include "engine/window/window_draw.h"

#define NUMBER_IN_USE 1 /* NumberSprite flags */
#define NUMBER_UNK2 2
#define MAIN_SCREEN_BGS 4 /* the backgrounds below 4 are the main screen's */
#define ID_RESERVED 0xFFFFFF00 /* ids from here on are not handed out */
#define FLAGS_CLEARED_END 0x45 /* func_020a45c0 clears 0 to 0x45 */
#define FLAGS2_START 1000 /* and 1000 to 1099 */
#define FLAGS2_END 1100

void func_020a472c(void) {}

/* Gives back the tiles of a number drawn with sprites, when it is in use. */
s32 func_020a4c9c(void *sprite) {
    struct NumberSprite *number = sprite;
    s32 inUse;
    u8 screen;
    u8 flags;

    flags = number->flags;
    inUse = flags & NUMBER_IN_USE;
    if (inUse == 0) {
        return inUse;
    }
    if (flags & NUMBER_UNK2) {
        screen = number->unk01;
        if (screen < MAIN_SCREEN_BGS) {
            return func_02085710(screen, number->unk02);
        }
        return func_02085520(screen, number->unk02);
    }
    screen = number->unk01;
    if (screen < MAIN_SCREEN_BGS) {
        return func_0208577c(screen, number->unk02);
    }
    return func_0208558c(screen, number->unk02);
}

/* Draws a number into a window at (x, y), and redraws the window. */
void func_020a4bf4(struct NumberSprite *number, s16 x, s16 y, u8 index) {
    struct Window *window;

    window = getWindow(index);
    func_020a4d18(number);
    func_020a8c40(index, x, y, number->digits, 1, number->unk1C);
    /* match depends on the s32 cast of the s8 digits: the binary narrows the
     * count to s16 again (lsl, asr) before each call. */
    if (window->flags & 1) {
        putSubBgChars((u8) window->unk2, number->unk02, (s32) number->digits, number->unkA0);
    } else {
        putMainBgChars((u8) window->unk2, number->unk02, (s32) number->digits, number->unkA0);
    }
    redrawWindow(index);
}

/* Sets a UI flag (UI_FLAGS). */
void setUiFlag(s32 flag) {
    setBit(flag, UI_FLAGS);
}

/* Clears a UI flag. */
void clearUiFlag(s32 flag) {
    clearBit(flag, UI_FLAGS);
}

/* Returns a UI flag. */
s32 getUiFlag(s32 flag) {
    return testBit(flag, UI_FLAGS);
}

/* Sets up a new game: counts the listed species, clears the save,
 * and starts the play time at 0 and the save's day at 1. */
void initNewGame(void) {
    s32 i;
    s32 count;
    struct SpeciesData *species;

    data_021da780 = 0xFFFF;
    data_021da784 = 0xFFFF;
    data_021da77c = 0xFFFF;
    data_021da778 = 0xFFFF;
    data_021da788 = 0xFFFF;
    count         = 0;
    for (i = 0; i < 426; i++) {
        species = loadSpeciesData(i);
        if (species->listed != 0) {
            count++;
        }
    }
    data_021da774 = count;
    func_020a4694(SAVE);
    setPlayTime(0, 0, 0);
    func_020a07e8(1);
}

/* Returns the product of two random numbers below 0xFFFF. */
s32 func_020a4670(void) {
    s32 random;

    random = getRandom(0xFFFF);
    return random * getRandom(0xFFFF);
}

/* Hands out the next id for a Digimon or a group: never 0 nor one of the
 * last 0x100. */
u32 takeNextId(void) {
    u32 id;

    id = SAVE->lastId;
    do {
        id++;
    } while (id == 0 || id >= ID_RESERVED);
    SAVE->lastId = id;
    return id;
}

/* Sets a game flag (GAME_FLAGS). */
void setGameFlag(s32 flag) {
    setBit(flag, GAME_FLAGS);
}

/* Clears a game flag. */
void clearGameFlag(s32 flag) {
    clearBit(flag, GAME_FLAGS);
}

/* Returns a game flag. */
s32 getGameFlag(s32 flag) {
    return testBit(flag, GAME_FLAGS);
}

/* Clears the game flags 0 to 0x45 and 1000 to 1099. */
void func_020a45c0(void) {
    s32 flag;
    s32 flag2;

    flag = 0;
    do {
        clearGameFlag(flag);
        flag++;
    } while (flag <= FLAGS_CLEARED_END);
    flag2 = FLAGS2_START;
    do {
        clearGameFlag(flag2);
        flag2++;
    } while (flag2 < FLAGS2_END);
}
