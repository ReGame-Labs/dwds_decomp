#include "engine/script/actor/props.h"
#include "engine/data.h"
#include "engine/digimon/digimon_records.h"
#include "engine/digimon/game_data.h"
#include "engine/digimon/species_flags.h"
#include "engine/input/touch.h"
#include "engine/palette/palette_buffers.h"
#include "engine/palette/palette_fade.h"
#include "engine/save/progress.h"
#include "engine/script/operand.h"
#include "engine/system/system.h"
#include "engine/text/text_args.h"
#include "engine/text/text_banks.h"
#include "engine/ui/gauge.h"
#include "farm/farms.h"
#include "field/actors/actor_commands.h"
#include "field/actors/actor_files.h"
#include "field/map/ov000_021fbb2c.h"
#include "items/inventory.h"
#include "m2c_macros.h"

/* Command 0x7E: sets flag 0x20000 of a sub actor and its unk28. */
s32 func_02090f9c(struct ScriptThread *thread) {
    func_020c227c((u16) resolveOperand(thread, *thread->pc));
    thread->pc++;
    return 1;
}

/* Command 0x7F: sets flag 0x20000 of a main actor and its unk28. */
s32 func_02090f50(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        func_020c2250((u16) resolveOperand(thread, *thread->pc));
    }
    thread->pc++;
    return 1;
}

/* Command 0x114: clears flag 0x40000 of a sub actor. */
s32 func_02090f1c(struct ScriptThread *thread) {
    showMainActorExtra((u16) resolveOperand(thread, *thread->pc));
    thread->pc++;
    return 1;
}

/* Command 0x115: clears flag 0x40000 of a main actor. */
s32 func_02090ed0(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        showSubActorExtra((u16) resolveOperand(thread, *thread->pc));
    }
    thread->pc++;
    return 1;
}

/* Command 0x116: sets flag 0x40000 of a sub actor. */
s32 func_02090e9c(struct ScriptThread *thread) {
    hideMainActorExtra((u16) resolveOperand(thread, *thread->pc));
    thread->pc++;
    return 1;
}

/* Command 0x117: sets flag 0x40000 of a main actor. */
s32 func_02090e50(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        hideSubActorExtra((u16) resolveOperand(thread, *thread->pc));
    }
    thread->pc++;
    return 1;
}

/* Command 0x86: puts a color of red, green and blue operands (0-31 each) in
 * MAIN_MAP_STATE's halfword at 0x78 (data_021ab9e0) and loads it with
 * loadMainPalette. */
s32 func_02090dd0(struct ScriptThread *thread) {
    u16 red                                 = resolveOperand(thread, thread->pc[0]);
    u16 green                               = resolveOperand(thread, thread->pc[1]);
    u16 blue                                = resolveOperand(thread, thread->pc[2]);
    M2C_FIELD(&MAIN_MAP_STATE, u16 *, 0x78) = red | (green << 5) | (blue << 10);
    loadMainPalette(0x4000, 1, (s32) data_021ab9e0);
    thread->pc += 3;
    return 1;
}

/* Command 0x87: the same with SUB_MAP_STATE and loadSubPalette. */
s32 func_02090d38(struct ScriptThread *thread) {
    u16 red;
    u16 green;
    u16 blue;

    if (getGameFlag(0x3E9) == 0) {
        red                                    = resolveOperand(thread, thread->pc[0]);
        green                                  = resolveOperand(thread, thread->pc[1]);
        blue                                   = resolveOperand(thread, thread->pc[2]);
        M2C_FIELD(&SUB_MAP_STATE, u16 *, 0x78) = red | (green << 5) | (blue << 10);
        loadSubPalette(0x4000, 1, (s32) &SUB_MAP_STATE.color);
    }
    thread->pc += 3;
    return 1;
}

/* Command 0x88: func_020c2158 on a sub actor with a value. */
s32 func_02090ce0(struct ScriptThread *thread) {
    u16 index;

    index = resolveOperand(thread, thread->pc[0]);
    func_020c2158(index, (u16) resolveOperand(thread, thread->pc[1]));
    thread->pc += 2;
    return 1;
}

/* Command 0x89: setSubActorPriority on a main actor with a value. */
s32 func_02090c70(struct ScriptThread *thread) {
    u16 index;

    if (getGameFlag(0x3E9) == 0) {
        index = resolveOperand(thread, thread->pc[0]);
        setSubActorPriority(index, resolveOperand(thread, thread->pc[1]));
    }
    thread->pc += 2;
    return 1;
}

/* Command 0x143: sets the OAM priority of a sub actor's two sprites, at most 3. */
s32 func_02090bf4(struct ScriptThread *thread) {
    u16 index;
    u16 level;
    struct Actor *actor;

    index = resolveOperand(thread, thread->pc[0]);
    level = resolveOperand(thread, thread->pc[1]);
    actor = getMainActor(index);
    if (actor != NULL) {
        actor->unk80          = level;
        actor->extra.priority = level;
        if (actor->unk80 > 3) {
            actor->unk80          = 3;
            actor->extra.priority = 3;
        }
    }
    thread->pc += 2;
    return 1;
}

/* Command 0x144: the same for a main actor. */
s32 func_02090b60(struct ScriptThread *thread) {
    u16 index;
    u16 level;
    struct Actor *actor;

    if (getGameFlag(0x3E9) == 0) {
        index = resolveOperand(thread, thread->pc[0]);
        level = resolveOperand(thread, thread->pc[1]);
        actor = getSubActor(index);
        if (actor != NULL) {
            actor->unk80          = level;
            actor->extra.priority = level;
            if (actor->unk80 > 3) {
                actor->unk80          = 3;
                actor->extra.priority = 3;
            }
        }
    }
    thread->pc += 2;
    return 1;
}

/* Command 0x8A: func_020c2088 on a sub actor with a value. */
s32 func_02090b08(struct ScriptThread *thread) {
    u16 index;

    index = resolveOperand(thread, thread->pc[0]);
    func_020c2088(index, (u16) resolveOperand(thread, thread->pc[1]));
    thread->pc += 2;
    return 1;
}

/* Command 0x8B: func_020c2070 on a main actor with a value. */
s32 func_02090a98(struct ScriptThread *thread) {
    u16 index;

    if (getGameFlag(0x3E9) == 0) {
        index = resolveOperand(thread, thread->pc[0]);
        func_020c2070(index, resolveOperand(thread, thread->pc[1]));
    }
    thread->pc += 2;
    return 1;
}

/* Command 0xA2: func_ov000_021fbd14 with two operands. */
s32 func_02090a30(struct ScriptThread *thread) {
    s16 x = (u16) resolveOperand(thread, *thread->pc);
    s16 y = (u16) resolveOperand(thread, thread->pc[1]);
    func_ov000_021fbd14(x, y);
    thread->pc += 2;
    return 1;
}

/* Command 0xA3: func_ov000_021fbcfc with two operands, unless event flag 0x3E9
 * is set. */
s32 func_020909b0(struct ScriptThread *thread) {
    s16 index;
    s16 value;

    if (getGameFlag(0x3E9) == 0) {
        index = (u16) resolveOperand(thread, thread->pc[0]);
        value = (u16) resolveOperand(thread, thread->pc[1]);
        func_ov000_021fbcfc(index, value);
    }
    thread->pc += 2;
    return 1;
}

/* Command 0xC2: adds a Digimon to the party (func_020a10ac), given by its index
 * of addDigimon. */
s32 func_0209097c(struct ScriptThread *thread) {
    struct Digimon *digimon;

    digimon = getDigimonAt(addDigimon((u16) readOperand(thread)));
    func_020a10ac(digimon->id);
    setNameEntryDigimon(digimon->id);
    return 1;
}

/* Command 0xC3: gives one of an item (addItem) and puts its name
 * (func_0209d5f4) in text slot 0. */
s32 func_02090940(struct ScriptThread *thread) {
    u16 item;

    item = readOperand(thread);
    addItem(item, 1);
    setTextArg(0, func_0209d5f4((s16) item));
    return 1;
}

/* Command 0x160: gives a farm item (createFarmGoods) and puts its name
 * (func_0209d378) in text slot 0. */
s32 func_02090904(struct ScriptThread *thread) {
    s16 item;

    item = (u16) readOperand(thread);
    createFarmGoods(item);
    setTextArg(0, func_0209d378(item));
    return 1;
}

/* Command 0x161: calls func_0209fa00. */
s32 func_020908ec(struct ScriptThread *thread) {
    func_0209fa00();
    return 1;
}

/* Command 0x168: for a first operand of 0, calls clearGamePad and
 * clearTouch; the second operand is not used. */
s32 func_020907c4(struct ScriptThread *thread) {
    s16 mode;

    mode = readOperand(thread);
    readOperand(thread);
    if (mode == 0) {
        clearGamePad();
        clearTouch();
    }
    return 1;
}
