#ifndef ENDING_STAFF_ROLL_H
#define ENDING_STAFF_ROLL_H

/* The staff roll: a text task that shows /dat/msg/staff.sdb, and two picture
 * tasks. */

#include "engine/data.h"
#include "types.h"

/* The state that ends a staff roll task. */
#define STAFF_ROLL_END 10000

/* The staff roll's text task, func_020c8e7c. */
struct StaffRoll {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 wait;
    /* 0x20 */ u8 unk20[2];
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s8 unk28;  /* func_020aa1a4's, freed by func_020a9610 */
    /* 0x29 */ u8 unk29;
    /* 0x2A */ u16 unk2A; /* func_02085eac's, freed by func_02085710 */
    /* 0x2C */ s8 unk2C;  /* func_02083e78's, freed by stopSubPaletteEffectsButFades */
    /* 0x2D */ u8 window; /* func_020a91c4's */
};

/* One of the staff roll's picture tasks, func_020c94e4 and func_020c9738. */
struct StaffRollPictures {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state; /* STAFF_ROLL_END ends it */
    /* 0x1E */ s16 wait;
    /* 0x20 */ u8 unk20[0x20];
    /* 0x40 */ s32 otherId; /* func_020c94e4's: the task id of func_020c9738 */
};

s32 isStaffRollTextRunning(void);
s32 isStaffRollDone(void);
void startStaffRoll(void);
void func_020c9954(s32 id);
void func_020c8e7c(void);
s32 startStaffRollText(void);
void func_020c94e4(void);
void func_020c9738(void);
s32 startStaffRollPictures(void);
void endStaffRollText(void);

#endif /* ENDING_STAFF_ROLL_H */
