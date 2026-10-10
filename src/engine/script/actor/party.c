#include "engine/script/actor/party.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/script/message.h"
#include "engine/script/operand.h"
#include "engine/system/display_modes.h"
#include "engine/ui/gauge.h"
#include "field/actors/actor_create.h"
#include "field/actors/actor_create_sub.h"
#include "field/actors/actor_files.h"
#include "field/actors/actor_tasks.h"
#include "field/map/map_files.h"

/* Command 0x1F: calls startMainActorTask. */
s32 func_020940d0(struct ScriptThread *thread) {
    startMainActorTask();
    return 1;
}

/* Command 0xA4: calls startSubActorTask, unless event flag 0x3E9 is set. */
s32 func_020940a4(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        startSubActorTask();
    }
    return 1;
}

/* Command 0x20: func_ov000_02201890 with six operands. */
s32 func_02093fe8(struct ScriptThread *thread) {
    s32 d;
    s32 c;
    s32 b;
    s32 e;
    u16 a;

    a = resolveOperand(thread, thread->pc[0]);
    b = resolveOperand(thread, thread->pc[1]);
    c = resolveOperand(thread, thread->pc[2]);
    d = resolveOperand(thread, thread->pc[3]);
    e = resolveOperand(thread, thread->pc[4]);
    func_ov000_02201890(a, b, c, d, e, (u16) resolveOperand(thread, thread->pc[5]));
    thread->pc += 6;
    return 1;
}

/* Command 0x22: makes a sub actor (func_020c8410) of a kind at x, y and z and sets its flags (addMainActorFlags) to a 32-bit
 * operand; from SCRIPT_DIGIMON_FIRST on, the kind is the unk4 of that party Digimon (getDigimonAt). */
s32 func_02093e44(struct ScriptThread *thread) {
    u16 id;
    u16 z;
    s32 flags;
    s32 x;
    s32 y;

    id    = resolveOperand(thread, thread->pc[0]);
    x     = resolveOperand(thread, thread->pc[1]);
    y     = resolveOperand(thread, thread->pc[2]);
    z     = resolveOperand(thread, thread->pc[3]);
    flags = peekScriptWord(thread, 4);
    if (id >= SCRIPT_DIGIMON_FIRST) {
        id = ((struct Digimon *) getDigimonAt(id - SCRIPT_DIGIMON_FIRST))->unk4;
    }
    addMainActorFlags(func_020c8410(id, x, y, z), flags);
    thread->pc += 6;
    return 1;
}

/* Command 0x23: the same for a main actor (func_020c7ed8, addSubActorFlags), unless event flag 0x3E9 is set. */
s32 func_02093d5c(struct ScriptThread *thread) {
    u16 id;
    u16 z;
    s32 flags;
    s32 x;
    s32 y;

    if (getGameFlag(0x3E9) == 0) {
        id    = resolveOperand(thread, thread->pc[0]);
        x     = resolveOperand(thread, thread->pc[1]);
        y     = resolveOperand(thread, thread->pc[2]);
        z     = resolveOperand(thread, thread->pc[3]);
        flags = peekScriptWord(thread, 4);
        if (id >= SCRIPT_DIGIMON_FIRST) {
            id = ((struct Digimon *) getDigimonAt(id - SCRIPT_DIGIMON_FIRST))->unk4;
        }
        addSubActorFlags(func_020c7ed8(id, x, y, z), flags);
    }
    thread->pc += 6;
    return 1;
}

/* Command 0x25: makes main actor slot (func_020c7520) of a kind at x, y and z and sets its flags; from SCRIPT_DIGIMON_FIRST
 * on, the kind is func_020a3224's for that party Digimon's unk4. */
s32 func_02093b5c(struct ScriptThread *thread) {
    u16 id;
    u16 z;
    u16 slot;
    s32 flags;
    s32 x;
    s32 y;

    if (getGameFlag(0x3E9) == 0) {
        id    = resolveOperand(thread, thread->pc[0]);
        x     = resolveOperand(thread, thread->pc[1]);
        y     = resolveOperand(thread, thread->pc[2]);
        z     = resolveOperand(thread, thread->pc[3]);
        flags = peekScriptWord(thread, 4);
        slot  = resolveOperand(thread, thread->pc[6]);
        if (id >= SCRIPT_DIGIMON_FIRST) {
            id = func_020a3224(((struct Digimon *) getDigimonAt(id - SCRIPT_DIGIMON_FIRST))->unk4);
        }
        func_020c7520(id, x, y, z, slot);
        addSubActorFlags(slot, flags);
    }
    thread->pc += 7;
    return 1;
}

/* Command 0x84: func_020c7060 on a sub actor. */
s32 func_02093b28(struct ScriptThread *thread) {
    func_020c7060((u16) resolveOperand(thread, *thread->pc));
    thread->pc += 1;
    return 1;
}

/* Command 0x85: func_020c6fb8 on a main actor, unless event flag 0x3E9 is set. */
s32 func_02093adc(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        func_020c6fb8((u16) resolveOperand(thread, *thread->pc));
    }
    thread->pc++;
    return 1;
}

/* Command 0x26: sets data_ov000_0220d950. */
s32 func_02093ac4(struct ScriptThread *thread) {
    func_ov000_022016e0();
    return 1;
}

/* Command 0x27: sets data_ov000_0220d954 and clears event flag 0x5F. */
s32 func_02093aac(struct ScriptThread *thread) {
    func_ov000_022016c0();
    return 1;
}

/* Command 0x3A: clears data_ov000_0220d950. */
s32 func_02093a94(struct ScriptThread *thread) {
    func_ov000_022016ac();
    return 1;
}

/* Command 0x3B: clears data_ov000_0220d954 and sets event flag 0x5F. */
s32 func_02093a7c(struct ScriptThread *thread) {
    func_ov000_0220168c();
    return 1;
}
