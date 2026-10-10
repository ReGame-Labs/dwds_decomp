#ifndef BATTLE_BATTLE_STATE_H
#define BATTLE_BATTLE_STATE_H

#include "types.h"

/* The battle's state: its flags and the values the field gives it, and the
 * link partner's equipment. */

/* getBattleFlags's flag of a link battle. */
#define BATTLE_FLAG_LINK 0x40

u8 getAbilityEffect(u8 id);
u8 func_02080de8(u32 id);
s32 *func_02080e58(void);
void func_02080e64(s32 value0, s32 value1, s32 value2, s32 value3, s32 value4);
s16 func_02080e94(void);
void func_02080ea4(s16 value);
u8 func_02080eb4(void);
void func_02080ec4(u8 value);
u8 getBattleFlags(void);
void addBattleFlags(s32 flags);
void setBattleFlags(u8 flags);
u8 func_02080f0c(void);
void func_02080f1c(s8 value);
void func_02080fe4(void);
void func_02081004(s32 index, u8 value);
u8 func_02081014(s32 index);
s32 addLinkPartyItem2(s32 id, u16 item);
u16 getLinkPartyItem2(s32 id);
s32 addLinkPartyItem1(s32 id, u16 item);
u16 getLinkPartyItem1(s32 id);
s32 func_02080e00(void);

/* The callers test the flag as a value, which an inline function explains. */
static inline BOOL isLinkBattle(void) {
    if (getBattleFlags() & BATTLE_FLAG_LINK) {
        return TRUE;
    }
    return FALSE;
}

static inline BOOL isLocalBattle(void) {
    if (!(getBattleFlags() & BATTLE_FLAG_LINK)) {
        return TRUE;
    }
    return FALSE;
}

#endif /* BATTLE_BATTLE_STATE_H */
