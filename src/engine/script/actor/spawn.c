#include "engine/script/actor/spawn.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/script/interpreter.h"
#include "engine/script/operand.h"
#include "engine/ui/gauge.h"
#include "field/actors/actor_files.h"
#include "field/actors/actor_walk.h"
#include "field/event_scripts/data.h"
#include "field/map/ov000_021fbb2c.h"
#include "m2c_macros.h"

/* Command 0x139: puts sub actors 1-3 at the place of the first sub actor with flag 0x10 (findMainActor), one for each of the
 * party's slots 0-2 that func_020a11e0 says is filled. */
s32 func_0209339c(struct ScriptThread *thread) {
    void *leader;
    void *member;

    leader = findMainActor(0x10);
    if (leader == NULL) {
        return 1;
    }
    if (func_020a11e0(0) == 0) {
        return 1;
    }
    member                      = getMainActor(1);
    M2C_FIELD(member, s32 *, 0) = M2C_FIELD(leader, s32 *, 0);
    M2C_FIELD(member, s32 *, 4) = M2C_FIELD(leader, s32 *, 4);
    if (func_020a11e0(1) == 0) {
        return 1;
    }
    member                      = getMainActor(2);
    M2C_FIELD(member, s32 *, 0) = M2C_FIELD(leader, s32 *, 0);
    M2C_FIELD(member, s32 *, 4) = M2C_FIELD(leader, s32 *, 4);
    if (func_020a11e0(2) == 0) {
        return 1;
    }
    member                      = getMainActor(3);
    M2C_FIELD(member, s32 *, 0) = M2C_FIELD(leader, s32 *, 0);
    M2C_FIELD(member, s32 *, 4) = M2C_FIELD(leader, s32 *, 4);
    return 1;
}

/* Command 0x13A: the same with main actors (findSubActor). */
s32 func_020932f8(struct ScriptThread *thread) {
    void *leader;
    void *member;

    leader = findSubActor(0x10);
    if (leader == NULL) {
        return 1;
    }
    if (func_020a11e0(0) == 0) {
        return 1;
    }
    member                      = getSubActor(1);
    M2C_FIELD(member, s32 *, 0) = M2C_FIELD(leader, s32 *, 0);
    M2C_FIELD(member, s32 *, 4) = M2C_FIELD(leader, s32 *, 4);
    if (func_020a11e0(1) == 0) {
        return 1;
    }
    member                      = getSubActor(2);
    M2C_FIELD(member, s32 *, 0) = M2C_FIELD(leader, s32 *, 0);
    M2C_FIELD(member, s32 *, 4) = M2C_FIELD(leader, s32 *, 4);
    if (func_020a11e0(2) == 0) {
        return 1;
    }
    member                      = getSubActor(3);
    M2C_FIELD(member, s32 *, 0) = M2C_FIELD(leader, s32 *, 0);
    M2C_FIELD(member, s32 *, 4) = M2C_FIELD(leader, s32 *, 4);
    return 1;
}

/* Command 0x36: calls stopMainMap. */
s32 func_020932e0(struct ScriptThread *thread) {
    stopMainMap();
    return 1;
}

/* Command 0x37: calls stopSubMap. */
s32 func_020932c8(struct ScriptThread *thread) {
    stopSubMap();
    return 1;
}

/* Command 0x38: goes on at an offset of the event scripts and sets global variable 3 to the third operand. */
s32 func_02093270(struct ScriptThread *thread) {
    s16 value;
    u16 *pc;

    value      = (u16) resolveOperand(thread, thread->pc[2]);
    pc         = thread->pc;
    thread->pc = (u16 *) &EVENT_SCRIPTS[pc[0] + (pc[1] << 16)];
    setScriptGlobal(SCRIPT_GLOBAL(3), value);
    return 1;
}

/* Command 0x39: keeps the index of the script at an offset (func_ov000_021fbe30), goes on there and sets global variable 4 to
 * the third operand. */
s32 func_020931fc(struct ScriptThread *thread) {
    u16 value;
    u16 *pc;

    value = resolveOperand(thread, thread->pc[2]);
    pc    = thread->pc;
    func_ov000_021fbe30(pc[0] + (pc[1] << 16));
    pc         = thread->pc;
    thread->pc = (u16 *) &EVENT_SCRIPTS[pc[0] + (pc[1] << 16)];
    setScriptGlobal(SCRIPT_GLOBAL(4), (s16) value);
    return 1;
}

/* Command 0x3C: startMainActorWander on a sub actor with two values. */
s32 func_02093198(struct ScriptThread *thread) {
    s32 b;
    u16 id;

    id = resolveOperand(thread, thread->pc[0]);
    b  = resolveOperand(thread, thread->pc[1]);
    startMainActorWander(id, b, resolveOperand(thread, thread->pc[2]));
    thread->pc += 3;
    return 1;
}

/* Command 0x3D: startSubActorWander on a main actor with two values, unless event flag 0x3E9 is set. */
s32 func_0209311c(struct ScriptThread *thread) {
    u16 id;
    s32 b;

    if (getGameFlag(0x3E9) == 0) {
        id = resolveOperand(thread, thread->pc[0]);
        b  = resolveOperand(thread, thread->pc[1]);
        startSubActorWander(id, b, resolveOperand(thread, thread->pc[2]));
    }
    thread->pc += 3;
    return 1;
}

/* Command 0x3E: pauseMainActorWander on a sub actor. */
s32 func_020930e8(struct ScriptThread *thread) {
    pauseMainActorWander(resolveOperand(thread, *thread->pc));
    thread->pc++;
    return 1;
}

/* Command 0x3F: pauseSubActorWander on a main actor, unless event flag 0x3E9 is set. */
s32 func_0209309c(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        pauseSubActorWander(resolveOperand(thread, *thread->pc));
    }
    thread->pc++;
    return 1;
}

/* Command 0x40: resumeMainActorWander on a sub actor. */
s32 func_02093068(struct ScriptThread *thread) {
    resumeMainActorWander(resolveOperand(thread, *thread->pc));
    thread->pc++;
    return 1;
}

/* Command 0x41: resumeSubActorWander on a main actor, unless event flag 0x3E9 is set. */
s32 func_0209301c(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        resumeSubActorWander(resolveOperand(thread, *thread->pc));
    }
    thread->pc++;
    return 1;
}
