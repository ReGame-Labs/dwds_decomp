#include "battle/battle_state.h"
#include "battle/ability_bonus.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"

/* The item the link partner's Digimon with the id equips in its second slot,
 * or NO_ITEM. */
u16 getLinkPartyItem1(s32 id) {
    s32 i;
    struct LinkPartyItem *slot = LINK_PARTY_ITEMS1;

    for (i = 0; i < LINK_PARTY_DIGIMON_COUNT; i++, slot++) {
        if (slot->id == id) {
            return slot->item;
        }
    }
    return NO_ITEM;
}

/* Records the item the link partner's Digimon with the id equips in its second
 * slot, in a free entry; FALSE when there is none. */
s32 addLinkPartyItem1(s32 id, u16 item) {
    s32 i;
    struct LinkPartyItem *slot = LINK_PARTY_ITEMS1;

    for (i = 0; i < LINK_PARTY_DIGIMON_COUNT; i++, slot++) {
        if (slot->id == 0) {
            slot->id   = id;
            slot->item = item;
            return TRUE;
        }
    }
    return FALSE;
}

/* The item the link partner's Digimon with the id equips in its third slot. */
u16 getLinkPartyItem2(s32 id) {
    s32 i;
    struct LinkPartyItem *slot = LINK_PARTY_ITEMS2;

    for (i = 0; i < LINK_PARTY_DIGIMON_COUNT; i++, slot++) {
        if (slot->id == id) {
            return slot->item;
        }
    }
    return NO_ITEM;
}

/* Records the item the link partner's Digimon with the id equips in its third
 * slot. */
s32 addLinkPartyItem2(s32 id, u16 item) {
    s32 i;
    struct LinkPartyItem *slot = LINK_PARTY_ITEMS2;

    for (i = 0; i < LINK_PARTY_DIGIMON_COUNT; i++, slot++) {
        if (slot->id == 0) {
            slot->id   = id;
            slot->item = item;
            return TRUE;
        }
    }
    return FALSE;
}

/* The byte with the index of a table that the link battle's setup fills. */
u8 func_02081014(s32 index) {
    return data_021bc1b4[index];
}

void func_02081004(s32 index, u8 value) {
    data_021bc1b4[index] = value;
}

/* Clears func_02080f1c's value and func_02080e00's counter. */
void func_02080fe4(void) {
    data_021bb8b4 = 0;
    data_021bb8b8 = 0;
}

void func_02080f1c(s8 value) {
    data_021bb8b4 = value;
}

u8 func_02080f0c(void) {
    return data_021bb8b4;
}

/* Sets the battle's flags (BATTLE_FLAG_*). */
void setBattleFlags(u8 flags) {
    BATTLE_FLAGS = flags;
}

/* Adds to the battle's flags. */
void addBattleFlags(s32 flags) {
    BATTLE_FLAGS |= flags;
}

/* The battle's flags. */
u8 getBattleFlags(void) {
    return BATTLE_FLAGS;
}

void func_02080ec4(u8 value) {
    data_021bb8a8 = value;
}

u8 func_02080eb4(void) {
    return data_021bb8a8;
}

void func_02080ea4(s16 value) {
    data_021bb8bc = value;
}

s16 func_02080e94(void) {
    return data_021bb8bc;
}

/* Sets the five values that a script command (func_0208c864) gives the next
 * battle. */
void func_02080e64(s32 value0, s32 value1, s32 value2, s32 value3, s32 value4) {
    data_021bb8c0[0] = value0;
    data_021bb8c0[1] = value1;
    data_021bb8c0[2] = value2;
    data_021bb8c0[3] = value3;
    data_021bb8c0[4] = value4;
}

s32 *func_02080e58(void) {
    return data_021bb8c0;
}

/* TRUE every third call. */
s32 func_02080e00(void) {
    data_021bb8b8++;
    if (data_021bb8b8 % 3 == 0) {
        data_021bb8b8 = 0;
        return TRUE;
    }
    return FALSE;
}

/* The skill's kind (enum SkillKind). */
u8 func_02080de8(u32 id) {
    struct SkillData *skill = func_020a1268(id);

    return skill->kind;
}

/* What the ability does (enum AbilityEffect). */
u8 getAbilityEffect(u8 id) {
    struct Ability *ability = func_020a1250(id);

    return ability->effect;
}
