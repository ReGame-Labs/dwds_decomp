#include "engine/script/actor/walk.h"
#include "engine/data.h"
#include "engine/script/operand.h"
#include "engine/ui/gauge.h"
#include "field/actors/actor_files.h"
#include "field/actors/actor_walk.h"
#include "field/map/map_files.h"

/* Command 0x42: standMainActor on a sub actor. */
s32 func_02092fe8(struct ScriptThread *thread) {
    standMainActor(resolveOperand(thread, *thread->pc));
    thread->pc += 1;
    return 1;
}

/* Command 0x43: standSubActor on a main actor, unless event flag 0x3E9 is set. */
s32 func_02092f9c(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        standSubActor(resolveOperand(thread, *thread->pc));
    }
    thread->pc += 1;
    return 1;
}

/* Command 0x44: moves a sub actor to a point (func_020c45f0). */
s32 func_02092ef8(struct ScriptThread *thread) {
    s32 y;
    s32 x;
    u16 id;
    u8 unk1;

    id   = resolveOperand(thread, thread->pc[0]);
    unk1 = resolveOperand(thread, thread->pc[1]);
    x    = resolveOperand(thread, thread->pc[2]);
    y    = resolveOperand(thread, thread->pc[3]);
    func_020c45f0(id, unk1, x, y, (s8) resolveOperand(thread, thread->pc[4]));
    thread->pc += 5;
    return 1;
}

/* Command 0x80: func_020c44e4 on a sub actor with a point. */
s32 func_02092d98(struct ScriptThread *thread) {
    s32 y;
    s32 x;
    u16 id;
    u8 unk1;

    id   = resolveOperand(thread, thread->pc[0]);
    unk1 = resolveOperand(thread, thread->pc[1]);
    x    = resolveOperand(thread, thread->pc[2]);
    y    = resolveOperand(thread, thread->pc[3]);
    func_020c44e4(id, unk1, x, y, (s8) resolveOperand(thread, thread->pc[4]));
    thread->pc += 5;
    return 1;
}

/* Command 0x82: moves a sub actor to another one's place. */
s32 func_02092c38(struct ScriptThread *thread) {
    u16 id;
    u8 unk1;
    u16 target;
    s8 mode;
    struct Actor *actor;

    id     = resolveOperand(thread, thread->pc[0]);
    unk1   = resolveOperand(thread, thread->pc[1]);
    target = resolveOperand(thread, thread->pc[2]);
    mode   = resolveOperand(thread, thread->pc[3]);
    actor  = getMainActor(target);
    if (actor != NULL) {
        func_020c45f0(id, unk1, actor->x, actor->y, mode);
    }
    thread->pc += 4;
    return 1;
}

/* Command 0x83: moves a main actor to another one's place (walkSubActorTo), unless event flag 0x3E9 is set. */
s32 func_02092b7c(struct ScriptThread *thread) {
    u16 id;
    u8 unk1;
    u16 target;
    s8 mode;
    struct Actor *actor;

    if (getGameFlag(0x3E9) == 0) {
        id     = resolveOperand(thread, thread->pc[0]);
        unk1   = resolveOperand(thread, thread->pc[1]);
        target = resolveOperand(thread, thread->pc[2]);
        mode   = resolveOperand(thread, thread->pc[3]);
        actor  = getSubActor(target);
        if (actor != NULL) {
            walkSubActorTo(id, unk1, actor->x, actor->y, mode);
        }
    }
    thread->pc += 4;
    return 1;
}

/* Command 0x9C: moves a sub actor to the middle of one of the map's rectangles (getMainMapRect, in tiles). */
s32 func_02092a54(struct ScriptThread *thread) {
    u16 id;
    u8 unk1;
    u16 rect;
    s8 mode;
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;

    id   = resolveOperand(thread, thread->pc[0]);
    unk1 = resolveOperand(thread, thread->pc[1]);
    rect = resolveOperand(thread, thread->pc[2]);
    mode = resolveOperand(thread, thread->pc[3]);
    getMainMapRect(rect, &left, &top, &right, &bottom, 0);
    left *= 8;
    top *= 8;
    right *= 8;
    bottom *= 8;
    right += 8;
    bottom += 8;
    func_020c45f0(id, unk1, (s16) ((right + left) / 2), (s16) ((bottom + top) / 2), mode);
    thread->pc += 4;
    return 1;
}

/* Command 0x9E: moves a sub actor across to the middle of one of the map's rectangles, keeping its y. */
s32 func_020927f0(struct ScriptThread *thread) {
    u16 id;
    u8 unk1;
    u16 rect;
    s8 mode;
    struct Actor *actor;
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;

    id    = resolveOperand(thread, thread->pc[0]);
    unk1  = resolveOperand(thread, thread->pc[1]);
    rect  = resolveOperand(thread, thread->pc[2]);
    mode  = resolveOperand(thread, thread->pc[3]);
    actor = getMainActor(id);
    if (actor != NULL) {
        getMainMapRect(rect, &left, &top, &right, &bottom, 0);
        left *= 8;
        top *= 8;
        right *= 8;
        bottom *= 8;
        right += 8;
        bottom += 8;
        func_020c45f0(id, unk1, (s16) ((right + left) / 2), actor->y, mode);
    }
    thread->pc += 4;
    return 1;
}
