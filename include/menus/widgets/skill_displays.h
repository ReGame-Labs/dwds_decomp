#ifndef MENUS_WIDGETS_SKILL_DISPLAYS_H
#define MENUS_WIDGETS_SKILL_DISPLAYS_H

#include "types.h"

/* The skill displays: the moves and the abilities, each as a list and as one. */

s32 func_020534b4();
s32 func_02053bf4();
s32 func_02054cb8();
s32 func_02055de4();
void func_02053868(s16 index, u16 arg1, s32 arg2);
void closeMoveListDisplay(s16 index);
void func_02053200();
void func_020539ac();
void func_02056788(s16 index, s16 value);
void func_020530ec();
void freeMoveListDisplaySprite(s16 index);
void freeMoveDisplaySprite(s16 index);
void closeAbilityListDisplay(s16 index);
void func_02054e00();
void func_02056940();
void closeMoveDisplay(s16 index);
void freeAbilityDisplaySprites(s16 index);
void closeAbilityDisplay(s16 index);

#endif /* MENUS_WIDGETS_SKILL_DISPLAYS_H */
