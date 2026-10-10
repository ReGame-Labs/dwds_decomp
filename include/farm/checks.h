#ifndef FARM_CHECKS_H
#define FARM_CHECKS_H

/* The checks of a digimon id that give 1 when it can be used or a negative
 * reason, and the freeing and remaking of the actors of the farm's digimon. */

#include "types.h"

void func_ov005_02291ee0(void);
void func_ov005_02291f08(void);
s32 func_ov005_02291cd0(s32 id);
s32 func_ov005_02291d18(s32 id);
s32 func_ov005_02291d70(s32 id);
s32 func_ov005_02291dd4(s32 id);
s32 func_ov005_02291e50(s32 id);
void func_ov005_02291a34(void);
void func_ov005_02291f0c(s32 id, s32 keepPicked);

#endif /* FARM_CHECKS_H */
