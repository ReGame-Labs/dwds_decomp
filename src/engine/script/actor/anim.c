#include "engine/script/actor/anim.h"
#include "engine/data.h"
#include "engine/script/operand.h"
#include "engine/ui/gauge.h"
#include "field/actors/actor_save_flash.h"
#include "field/actors/route_commands.h"
#include "field/actors/route_run.h"
#include "field/map/map_character.h"

/* Command 0xD1: func_ov000_021fb95c with three operands, unless event flag
 * 0x3E9 is set. */
s32 func_02091f58(struct ScriptThread *thread) {
    s16 x;
    s16 y;

    if (getGameFlag(0x3E9) == 0) {
        x = (u16) resolveOperand(thread, thread->pc[0]);
        y = (u16) resolveOperand(thread, thread->pc[1]);
        func_ov000_021fb95c(x, y, resolveOperand(thread, thread->pc[2]));
    }
    thread->pc += 3;
    return 1;
}

/* Command 0xD2: func_ov000_021fb830 with three operands. */
s32 func_02091ee0(struct ScriptThread *thread) {
    s16 x;
    s16 y;
    s32 z;

    x = (u16) resolveOperand(thread, thread->pc[0]);
    y = (u16) resolveOperand(thread, thread->pc[1]);
    z = resolveOperand(thread, thread->pc[2]);
    func_ov000_021fb830(x, y, z);
    thread->pc += 3;
    return 1;
}

/* Command 0xD3: scrollSubMap with three operands, unless event flag
 * 0x3E9 is set. */
s32 func_02091e50(struct ScriptThread *thread) {
    s16 x;
    s16 y;

    if (getGameFlag(0x3E9) == 0) {
        x = (u16) resolveOperand(thread, thread->pc[0]);
        y = (u16) resolveOperand(thread, thread->pc[1]);
        scrollSubMap(x, y, resolveOperand(thread, thread->pc[2]));
    }
    thread->pc += 3;
    return 1;
}

/* Command 0xD4: waits until isMainMapScrollDone says done. */
s32 func_02091e28(struct ScriptThread *thread) {
    if (isMainMapScrollDone() != 0) {
        return 1;
    }
    thread->pc--;
    return 0;
}

/* Command 0xD5: waits until isSubMapScrollDone says done, unless event flag
 * 0x3E9 is set. */
s32 func_02091de8(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) != 0) {
        return 1;
    }
    if (isSubMapScrollDone() != 0) {
        return 1;
    }
    thread->pc -= 1;
    return 0;
}

/* Command 0x4C: startMainActorRoute on a sub actor with two values. */
s32 func_02091d84(struct ScriptThread *thread) {
    u16 id = resolveOperand(thread, thread->pc[0]);
    s32 b  = resolveOperand(thread, thread->pc[1]);
    u8 c   = resolveOperand(thread, thread->pc[2]);

    startMainActorRoute(id, b, c);
    thread->pc += 3;
    return 1;
}

/* Command 0x4D: startSubActorRoute on a main actor with two values. */
s32 func_02091d08(struct ScriptThread *thread) {
    u16 id;
    s32 b;
    u8 c;

    if (getGameFlag(0x3E9) == 0) {
        id = resolveOperand(thread, thread->pc[0]);
        b  = resolveOperand(thread, thread->pc[1]);
        c  = resolveOperand(thread, thread->pc[2]);
        startSubActorRoute(id, b, c);
    }
    thread->pc += 3;
    return 1;
}

/* Command 0xA6: stopMainActorRoute on a sub actor. */
s32 func_02091cd4(struct ScriptThread *thread) {
    stopMainActorRoute(resolveOperand(thread, *thread->pc));
    thread->pc += 1;
    return 1;
}

/* Command 0xA7: stopSubActorRoute on a main actor. */
s32 func_02091c88(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        stopSubActorRoute(resolveOperand(thread, *thread->pc));
    }
    thread->pc += 1;
    return 1;
}

/* Command 0x4E: waits until isMainActorRouteDone says a sub actor is done. */
s32 func_02091c40(struct ScriptThread *thread) {
    if (isMainActorRouteDone(resolveOperand(thread, *thread->pc)) != 0) {
        thread->pc += 1;
        return 1;
    }
    thread->pc -= 1;
    return 0;
}

/* Command 0x4F: waits until isSubActorRouteDone says a main actor is done. */
s32 func_02091bd0(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) != 0) {
        thread->pc++;
        return 1;
    }
    if (isSubActorRouteDone(resolveOperand(thread, *thread->pc))) {
        thread->pc++;
        return 1;
    }
    thread->pc--;
    return 0;
}

/* Command 0x50: endMainRoute on the current sub actor. */
s32 func_02091bb8(struct ScriptThread *thread) {
    endMainRoute();
    return 1;
}

/* Command 0x51: endSubRoute on the current main actor. */
s32 func_02091b8c(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        endSubRoute();
    }
    return 1;
}

/* Command 0x52: func_020c3704 with four operands (sub actors). */
s32 func_02091b00(struct ScriptThread *thread) {
    u8 a  = (u16) resolveOperand(thread, thread->pc[0]);
    s32 b = resolveOperand(thread, thread->pc[1]);
    s32 c = resolveOperand(thread, thread->pc[2]);
    s8 d  = resolveOperand(thread, thread->pc[3]);

    func_020c3704(a, b, c, d);
    thread->pc += 4;
    return 1;
}

/* Command 0x53: func_020c3644 with four operands (main actors). */
s32 func_02091a5c(struct ScriptThread *thread) {
    u8 a;
    s32 b;
    s32 c;
    s8 d;

    if (getGameFlag(0x3E9) == 0) {
        a = (u16) resolveOperand(thread, thread->pc[0]);
        b = resolveOperand(thread, thread->pc[1]);
        c = resolveOperand(thread, thread->pc[2]);
        d = resolveOperand(thread, thread->pc[3]);
        func_020c3644(a, b, c, d);
    }
    thread->pc += 4;
    return 1;
}

/* Command 0x54: func_020c3574 with four operands (sub actors). */
s32 func_020919d0(struct ScriptThread *thread) {
    u8 a  = (u16) resolveOperand(thread, thread->pc[0]);
    s32 b = resolveOperand(thread, thread->pc[1]);
    s32 c = resolveOperand(thread, thread->pc[2]);
    s8 d  = resolveOperand(thread, thread->pc[3]);

    func_020c3574(a, b, c, d);
    thread->pc += 4;
    return 1;
}

/* Command 0x55: func_020c34a4 with four operands (main actors). */
s32 func_0209192c(struct ScriptThread *thread) {
    u8 a;
    s32 b;
    s32 c;
    s8 d;

    if (getGameFlag(0x3E9) == 0) {
        a = (u16) resolveOperand(thread, thread->pc[0]);
        b = resolveOperand(thread, thread->pc[1]);
        c = resolveOperand(thread, thread->pc[2]);
        d = resolveOperand(thread, thread->pc[3]);
        func_020c34a4(a, b, c, d);
    }
    thread->pc += 4;
    return 1;
}

/* Command 0x56: addMainRouteWaitArrival on the current sub actor. */
s32 func_02091914(struct ScriptThread *thread) {
    addMainRouteWaitArrival();
    return 1;
}

/* Command 0x57: addSubRouteWaitArrival on the current main actor. */
s32 func_020918e8(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        addSubRouteWaitArrival();
    }
    return 1;
}

/* Command 0x58: func_020c3388 with the operand. */
s32 func_020918ac(struct ScriptThread *thread) {
    func_020c3388((s16) (u16) resolveOperand(thread, *thread->pc));
    thread->pc++;
    return 1;
}

/* Command 0x5A: func_020c32c0 with the operand. */
s32 func_02091828(struct ScriptThread *thread) {
    func_020c32c0((u8) resolveOperand(thread, *thread->pc));
    thread->pc++;
    return 1;
}
