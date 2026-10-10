#include "engine/ui/dial.h"
#include "engine/data.h"
#include "engine/system/system.h"

/* Closes a dial. */
void closeDial(s32 id) {
    endDialTask(id);
}

/* A dial's task: turns it while it is not stopped. */
void tickDial(void) {
    struct DialTask *dial = (struct DialTask *) getCurrentTask();
    if (dial->unk1C != 0) {
        return;
    }
    updateDial(dial);
}

/* Looks a dial up, and does nothing with it. */
void func_02043558(s32 id) {
    findDial(id);
}

/* The angle a dial shows. */
s16 getDialAngle(s32 id) {
    struct DialTask *dial;

    dial = findDial(id);
    if (dial != NULL) {
        return dial->angle + dial->unk3C;
    }
    return 0;
}

/* Turns a dial to a position. */
void setDialValue(s32 id, s16 value) {
    struct DialTask *dial = findDial(id);
    if (dial == NULL) {
        return;
    }
    dial->angle = (s16) (value * dial->step) % 256;
    dial->value = value;
}

/* The position of a dial. */
s16 getDialValue(s32 id) {
    return findDial(id)->value;
}

/* The main screen map's scroll and size; a NULL leaves its value out. */
void getMainMapView(s32 *x, s32 *y, u16 *width, u16 *height) {
    if (x != NULL) {
        *x = MAIN_MAP_STATE.x.value;
    }
    if (y != NULL) {
        *y = MAIN_MAP_STATE.y.value;
    }
    if (width != NULL) {
        *width = MAIN_MAP_STATE.width;
    }
    if (height != NULL) {
        *height = MAIN_MAP_STATE.height;
    }
}

/* The same for the sub screen's map. */
void getSubMapView(s32 *x, s32 *y, u16 *width, u16 *height) {
    if (x != NULL) {
        *x = SUB_MAP_STATE.x.value;
    }
    if (y != NULL) {
        *y = SUB_MAP_STATE.y.value;
    }
    if (width != NULL) {
        *width = SUB_MAP_STATE.width;
    }
    if (height != NULL) {
        *height = SUB_MAP_STATE.height;
    }
}
