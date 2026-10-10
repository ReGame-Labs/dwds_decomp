#include "engine/script/actor/move.h"
#include "engine/data.h"
#include "engine/script/operand.h"
#include "engine/ui/gauge.h"
#include "field/actors/actor_commands.h"
#include "field/actors/actor_files.h"
#include "field/actors/actor_walk.h"
#include "field/actors/route_run.h"
#include "field/map/map_files.h"
#include "field/map/ov000_021fbb2c.h"

/* Command 0xA0: moves a sub actor (func_020c45f0) to its own x and the middle
 * of the y range of one of the map's rectangles (getMainMapRect). */
s32 func_02092590(struct ScriptThread *thread) {
    u16 id;
    u8 unk1;
    u16 index;
    s8 mode;
    struct Actor *actor;
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;

    id    = resolveOperand(thread, thread->pc[0]);
    unk1  = resolveOperand(thread, thread->pc[1]);
    index = resolveOperand(thread, thread->pc[2]);
    mode  = resolveOperand(thread, thread->pc[3]);
    actor = getMainActor(id);
    if (actor != NULL) {
        getMainMapRect(index, &left, &top, &right, &bottom, NULL);
        right *= 8;
        bottom *= 8;
        left *= 8;
        top *= 8;
        right += 8;
        bottom += 8;
        func_020c45f0(id, unk1, actor->x, (s16) ((bottom + top) / 2), mode);
    }
    thread->pc += 4;
    return 1;
}

/* Command 0xC6: moves a sub actor (func_020c45f0) to another one's place plus
 * an offset. */
s32 func_0209235c(struct ScriptThread *thread) {
    u16 id;
    u8 unk1;
    u16 target;
    s32 dx;
    s32 dy;
    s8 mode;
    struct Actor *actor;

    id     = resolveOperand(thread, thread->pc[0]);
    unk1   = resolveOperand(thread, thread->pc[1]);
    target = resolveOperand(thread, thread->pc[2]);
    dx     = resolveOperand(thread, thread->pc[3]);
    dy     = resolveOperand(thread, thread->pc[4]);
    mode   = resolveOperand(thread, thread->pc[5]);
    actor  = getMainActor(target);
    if (actor == NULL) {
        thread->pc += 6;
        return 1;
    }
    func_020c45f0(id, unk1, (s16) (actor->x + dx), (s16) (actor->y + dy), mode);
    thread->pc += 6;
    return 1;
}

/* Command 0x46: waits until isMainActorWalkDone says a sub actor is done. */
s32 func_02092204(struct ScriptThread *thread) {
    u16 id;

    id = resolveOperand(thread, *thread->pc);
    if (isMainActorWalkDone(id) == 0) {
        thread->pc -= 1;
        return 0;
    }
    thread->pc += 1;
    return 1;
}

/* Command 0x47: waits until isSubActorWalkDone says a main actor is done, unless
 * event flag 0x3E9 is set. */
s32 func_020921a0(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        if (isSubActorWalkDone((u16) resolveOperand(thread, thread->pc[0])) == 0) {
            thread->pc -= 1;
            return 0;
        }
    }
    thread->pc += 1;
    return 1;
}

/* Command 0x48: func_020c257c on a sub actor with a value. */
s32 func_0209214c(struct ScriptThread *thread) {
    u16 id;

    id = resolveOperand(thread, thread->pc[0]);
    func_020c257c(id, resolveOperand(thread, thread->pc[1]));
    thread->pc += 2;
    return 1;
}

/* Command 0x49: func_020c2440 on a main actor with a value. */
s32 func_020920e0(struct ScriptThread *thread) {
    u16 first;

    if (getGameFlag(0x3E9) == 0) {
        first = resolveOperand(thread, thread->pc[0]);
        func_020c2440(first, resolveOperand(thread, thread->pc[1]));
    }
    thread->pc += 2;
    return 1;
}

/* Command 0x4A: clears flag 0x2 of a sub actor and MAIN_MAP_STATE's words at
 * 0x3C-0x4E (func_020c2404). */
s32 func_020920ac(struct ScriptThread *thread) {
    func_020c2404((u16) resolveOperand(thread, *thread->pc));
    thread->pc += 1;
    return 1;
}

/* Command 0x4B: the same for a main actor and SUB_MAP_STATE (func_020c23c8). */
s32 func_02092060(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        func_020c23c8((u16) resolveOperand(thread, thread->pc[0]));
    }
    thread->pc += 1;
    return 1;
}

/* Command 0xD0: func_ov000_021fbb2c with three operands. */
s32 func_02091fe8(struct ScriptThread *thread) {
    s16 x;
    s16 y;

    x = (u16) resolveOperand(thread, thread->pc[0]);
    y = (u16) resolveOperand(thread, thread->pc[1]);
    func_ov000_021fbb2c(x, y, resolveOperand(thread, thread->pc[2]));
    thread->pc += 3;
    return 1;
}
