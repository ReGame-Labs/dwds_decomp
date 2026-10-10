#ifndef ENGINE_UI_DIAL_H
#define ENGINE_UI_DIAL_H

#include "engine/data.h"
#include "types.h"

/* A dial: a ring of positions turned by touch, run by a task of its own
 * (tickDial). Up to DIAL_COUNT are open at once, by the ids that
 * openDial returns. The Digimon guide picks its order with one. */

#define DIAL_COUNT 4

/* What openDial opens a dial with. */
struct DialParams {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 count; /* of positions */
    /* 0x0C */ s16 value; /* the position at the start */
};

struct DialTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ u16 unk1C; /* the task does nothing while it is set */
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A; /* the params' unk0 to unk6 */
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 angle; /* in 256ths of a turn */
    /* 0x34 */ s16 count;
    /* 0x36 */ s16 step;  /* the angle between two positions */
    /* 0x38 */ s16 unk38; /* the params' unk8 */
    /* 0x3A */ s16 value; /* the position */
    /* 0x3C */ s16 unk3C; /* added to the angle */
    /* 0x3E */ u8 unk3E;
    /* 0x3F */ u8 unk3F;
};

void getSubMapView(s32 *x, s32 *y, u16 *width, u16 *height);
void getMainMapView(s32 *x, s32 *y, u16 *width, u16 *height);
void endDialTask(s32 id);
struct DialTask *findDial(s32 id);
s16 getDialValue(s32 id);
void func_02043558(s32 id);
void closeDial(s32 id);
void setDialValue(s32 id, s16 value);
void updateDial(struct DialTask *dial);
void tickDial(void);
s16 getDialAngle(s32 id);
s32 openDial(); /* (struct DialParams *params) */

#endif /* ENGINE_UI_DIAL_H */
