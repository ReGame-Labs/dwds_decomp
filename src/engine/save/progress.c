#include "engine/save/progress.h"
#include "engine/data.h"
#include "engine/save/game_state.h"
#include "engine/system/system.h"
#include "engine/text/text_args.h"
#include "engine/ui/gauge.h"
#include "menus/experience/experience_screen.h"

/* Sets the play time, up to 99:59:59. It counts 64 a second. */
void setPlayTime(s32 hours, s32 minutes, s32 seconds) {
    if (hours > 99) {
        hours = 99;
    }
    if (minutes > 59) {
        minutes = 59;
    }
    if (seconds > 59) {
        seconds = 59;
    }
    SAVE->playTime = hours * (3600 * 64) + minutes * (60 * 64) + seconds * 64;
}

/* Returns how many species count in the Digimon guide, as initNewGame
 * counted them. */
s16 func_020a000c(void) {
    return data_021da774;
}

/* Counts the Digimon records with status bit 0x2 or 0x4. */
s32 func_0209ff28(void) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 40; i++) {
        s32 id = data_021db82c[i].id;
        if (id != 0 && id != -1) {
            u16 status = data_021db82c[i].unk108;
            if ((status & 2) || (status & 4)) {
                count++;
            }
        }
    }
    return count;
}

/* Counts link battle wins, up to 999. */
s16 addLinkWins(s32 count) {
    data_021e0af8.linkWins += count;
    if (data_021e0af8.linkWins < 0) {
        data_021e0af8.linkWins = 0;
    } else if (data_021e0af8.linkWins > 999) {
        data_021e0af8.linkWins = 999;
    }
    return data_021e0af8.linkWins;
}

/* Counts link battle losses, up to 999. */
s16 addLinkLosses(s32 count) {
    data_021e0af8.linkLosses += count;
    if (data_021e0af8.linkLosses < 0) {
        data_021e0af8.linkLosses = 0;
    } else if (data_021e0af8.linkLosses > 999) {
        data_021e0af8.linkLosses = 999;
    }
    return data_021e0af8.linkLosses;
}

/* Clears a Digimon's family tree (func_0209fdf0 on its ancestors). */
void func_0209fe44(struct Digimon *digimon) {
    func_0209fdf0(digimon->parents);
}

/* Returns the name of the area of an id, from 1, through data_02127030. */
void *func_0209fc30(s32 id) {
    return getAreaName(data_02127030[id - 1]);
}

/* Sets event flag 0x251 when flag 330 is the first of the quest flags
 * 301-360 set (func_020a020c). */
void func_0209f9c4(s32 flag) {
    if (flag - 301 != func_020a020c()) {
        return;
    }
    if (flag != 330) {
        return;
    }
    setGameFlag(0x251);
}

/* Opens the screen of the experience gained (func_0209f2b0). */
void func_0209f980(s32 unk20) {
    struct ExpScreen *screen;

    screen        = createTask(func_0209f2b0, 0x108);
    data_021da770 = getTaskId(screen);
    screen->state = 0;
    screen->unk20 = unk20;
}
