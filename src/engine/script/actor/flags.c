#include "engine/script/actor/flags.h"
#include "engine/data.h"
#include "engine/script/operand.h"
#include "engine/ui/gauge.h"
#include "field/actors/actor_commands.h"
#include "field/actors/actor_facing.h"
#include "field/actors/actor_files.h"
#include "field/actors/actor_save_flash.h"
#include "field/actors/route_commands.h"

/* Command 0x5C: addMainRouteFreeFacing on the current sub actor. */
s32 func_020917c8(struct ScriptThread *thread) {
    addMainRouteFreeFacing();
    return 1;
}

/* Command 0x5D: addSubRouteFreeFacing on the current main actor. */
s32 func_0209179c(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        addSubRouteFreeFacing();
    }
    return 1;
}

/* Command 0x5E: addMainRouteFixFacing on the current sub actor. */
s32 func_02091784(struct ScriptThread *thread) {
    addMainRouteFixFacing();
    return 1;
}

/* Command 0x5F: addSubRouteFixFacing on the current main actor. */
s32 func_02091758(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        addSubRouteFixFacing();
    }
    return 1;
}

/* Command 0x60: func_020c3088 on the current sub actor with the operand. */
s32 func_0209172c(struct ScriptThread *thread) {
    func_020c3088(resolveOperand(thread, *thread->pc));
    thread->pc++;
    return 1;
}

/* Command 0x61: func_020c3024 on the current main actor with the operand. */
s32 func_020916e8(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        func_020c3024(resolveOperand(thread, *thread->pc));
    }
    thread->pc += 1;
    return 1;
}

/* Command 0x62: addMainRouteResumeAnimation on the current sub actor. */
s32 func_020916d0(struct ScriptThread *thread) {
    addMainRouteResumeAnimation();
    return 1;
}

/* Command 0x63: addSubRouteResumeAnimation on the current main actor. */
s32 func_020916a4(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        addSubRouteResumeAnimation();
    }
    return 1;
}

/* Command 0x64: addMainRoutePauseAnimation on the current sub actor. */
s32 func_0209168c(struct ScriptThread *thread) {
    addMainRoutePauseAnimation();
    return 1;
}

/* Command 0x65: addSubRoutePauseAnimation on the current main actor. */
s32 func_02091660(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        addSubRoutePauseAnimation();
    }
    return 1;
}

/* Command 0x66: func_020c2e50 on the current sub actor with the operand. */
s32 func_02091634(struct ScriptThread *thread) {
    func_020c2e50(resolveOperand(thread, *thread->pc));
    thread->pc++;
    return 1;
}

/* Command 0x67: func_020c2dec on the current main actor with the operand. */
s32 func_020915f0(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        func_020c2dec(resolveOperand(thread, *thread->pc));
    }
    thread->pc += 1;
    return 1;
}

/* Command 0x68: clears flag 0x4000 of a sub actor. */
s32 func_020915bc(struct ScriptThread *thread) {
    freeMainActorFacing((u16) resolveOperand(thread, *thread->pc));
    thread->pc++;
    return 1;
}

/* Command 0x69: clears flag 0x4000 of a main actor. */
s32 func_02091570(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        freeSubActorFacing((u16) resolveOperand(thread, *thread->pc));
    }
    thread->pc += 1;
    return 1;
}

/* Command 0x6A: sets flag 0x4000 of a sub actor. */
s32 func_0209153c(struct ScriptThread *thread) {
    fixMainActorFacing((u16) resolveOperand(thread, *thread->pc));
    thread->pc++;
    return 1;
}

/* Command 0x6B: sets flag 0x4000 of a main actor. */
s32 func_020914f0(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        fixSubActorFacing((u16) resolveOperand(thread, *thread->pc));
    }
    thread->pc += 1;
    return 1;
}

/* Command 0x6C: setActorAnimation on a sub actor with a value. */
s32 func_02091494(struct ScriptThread *thread) {
    u16 id;
    s16 value;
    void *obj;

    id    = resolveOperand(thread, thread->pc[0]);
    value = resolveOperand(thread, thread->pc[1]);
    obj   = getMainActor(id);
    if (obj != NULL) {
        setActorAnimation(obj, value);
    }
    thread->pc += 2;
    return 1;
}

/* Command 0x6D: setActorAnimation on a main actor with a value. */
s32 func_02091420(struct ScriptThread *thread) {
    u16 id;
    s16 value;
    void *obj;

    if (getGameFlag(0x3E9) == 0) {
        id    = resolveOperand(thread, thread->pc[0]);
        value = resolveOperand(thread, thread->pc[1]);
        obj   = getSubActor(id);
        if (obj != NULL) {
            setActorAnimation(obj, value);
        }
    }
    thread->pc += 2;
    return 1;
}

/* Command 0x6E: clears flag 0x8000 of a sub actor. */
s32 func_020913ec(struct ScriptThread *thread) {
    resumeMainActorAnimation((u16) resolveOperand(thread, *thread->pc));
    thread->pc++;
    return 1;
}

/* Command 0x6F: clears flag 0x8000 of a main actor. */
s32 func_020913a0(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        resumeSubActorAnimation((u16) resolveOperand(thread, *thread->pc));
    }
    thread->pc += 1;
    return 1;
}

/* Command 0x70: sets flag 0x8000 of a sub actor. */
s32 func_0209136c(struct ScriptThread *thread) {
    pauseMainActorAnimation((u16) resolveOperand(thread, *thread->pc));
    thread->pc++;
    return 1;
}

/* Command 0x71: sets flag 0x8000 of a main actor. */
s32 func_02091320(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        pauseSubActorAnimation((u16) resolveOperand(thread, *thread->pc));
    }
    thread->pc += 1;
    return 1;
}

/* Command 0x72: setActorCell on a sub actor with a value. */
s32 func_020912c4(struct ScriptThread *thread) {
    u16 id;
    s16 value;
    void *obj;

    id    = resolveOperand(thread, thread->pc[0]);
    value = resolveOperand(thread, thread->pc[1]);
    obj   = getMainActor(id);
    if (obj != NULL) {
        setActorCell(obj, value);
    }
    thread->pc += 2;
    return 1;
}

/* Command 0x73: setActorCell on a main actor with a value. */
s32 func_02091250(struct ScriptThread *thread) {
    u16 id;
    s16 value;
    void *obj;

    if (getGameFlag(0x3E9) == 0) {
        id    = resolveOperand(thread, thread->pc[0]);
        value = resolveOperand(thread, thread->pc[1]);
        obj   = getSubActor(id);
        if (obj != NULL) {
            setActorCell(obj, value);
        }
    }
    thread->pc += 2;
    return 1;
}

/* Command 0x74: clears flag 0x10000 of a sub actor. */
s32 func_0209121c(struct ScriptThread *thread) {
    unfreezeMainActor((u16) resolveOperand(thread, *thread->pc));
    thread->pc++;
    return 1;
}

/* Command 0x75: clears flag 0x10000 of a main actor. */
s32 func_020911d0(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        unfreezeSubActor((u16) resolveOperand(thread, *thread->pc));
    }
    thread->pc += 1;
    return 1;
}

/* Command 0x76: sets flag 0x10000 of a sub actor. */
s32 func_0209119c(struct ScriptThread *thread) {
    freezeMainActor((u16) resolveOperand(thread, *thread->pc));
    thread->pc++;
    return 1;
}

/* Command 0x77: sets flag 0x10000 of a main actor. */
s32 func_02091150(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        freezeSubActor((u16) resolveOperand(thread, *thread->pc));
    }
    thread->pc += 1;
    return 1;
}

/* Command 0x78: clears flag 0x1000 of a sub actor. */
s32 func_0209111c(struct ScriptThread *thread) {
    showMainActor((u16) resolveOperand(thread, *thread->pc));
    thread->pc++;
    return 1;
}

/* Command 0x79: clears flag 0x1000 of a main actor. */
s32 func_020910d0(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        showSubActor((u16) resolveOperand(thread, *thread->pc));
    }
    thread->pc += 1;
    return 1;
}

/* Command 0x7A: sets flag 0x1000 of a sub actor. */
s32 func_0209109c(struct ScriptThread *thread) {
    hideMainActor((u16) resolveOperand(thread, *thread->pc));
    thread->pc++;
    return 1;
}

/* Command 0x7B: sets flag 0x1000 of a main actor. */
s32 func_02091050(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        hideSubActor((u16) resolveOperand(thread, *thread->pc));
    }
    thread->pc += 1;
    return 1;
}

/* Command 0x7C: clears flag 0x20000 of a sub actor. */
s32 func_0209101c(struct ScriptThread *thread) {
    func_020c22b8((u16) resolveOperand(thread, *thread->pc));
    thread->pc++;
    return 1;
}

/* Command 0x7D: clears flag 0x20000 of a main actor. */
s32 func_02090fd0(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        func_020c22a8((u16) resolveOperand(thread, *thread->pc));
    }
    thread->pc += 1;
    return 1;
}
