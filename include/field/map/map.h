#ifndef FIELD_MAP_MAP_H
#define FIELD_MAP_MAP_H

/* The map of each screen: starting it, its task and clearing its state. */

#include "types.h"

void startSubMap(void);
void startMainMap(void);
void startSubMapTask(void);
void startMainMapTask(void);
void stopSubMapTask(void);
void stopMainMapTask(void);
s32 func_ov000_021ff4f4();
void loadSubMap();
void clearSubMapState(void);
void clearMainMapState(void);

#endif /* FIELD_MAP_MAP_H */
