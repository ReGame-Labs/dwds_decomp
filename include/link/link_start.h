#ifndef LINK_LINK_START_H
#define LINK_LINK_START_H

/* Starting a link session, and script program 104, which saves the game. */

#include "engine/data.h"
#include "types.h"

/* Program 104's work block. */
struct Program104Work {
    /* 0x00 */ struct BgGraphics bgs[2];
    /* 0x30 */ u16 unk30;
    /* 0x32 */ u8 unk32[0x1E];
    /* 0x50 */ s64 unk50;
};

/* The task of script program 104 (runProgram104): it saves the game with
 * func_0206267c and runSaveWriter. */
struct Program104 {
    /* 0x00 */ struct Task task;
    /* 0x1C */ struct Program104Work *work;
    /* 0x20 */ s16 state;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s32 unk24; /* from func_02083e78, freed by stopSubPaletteEffectsButFades */
    /* 0x28 */ s32 unk28; /* from func_02083ea8, freed by stopMainPaletteEffectsButFades */
};

extern s32 PROGRAM_104_TASK_ID; /* program 104's task id */
extern struct Program104 *PROGRAM_104;

void resetLinkGlobals(void);
s32 func_02072718();
u8 isProgram104Ended(void);
void func_0207270c(s32 mode, s32 unk);
void freeProgram104(struct Program104 *task);
void func_0207279c(void);
s64 func_020727c8();
void runProgram104();
void func_020722f0(s32 mode);

#endif /* LINK_LINK_START_H */
