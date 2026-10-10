#include "engine/text/text_args.h"
#include "engine/data.h"
#include "engine/system/system.h"
#include "engine/text/expand_text.h"
#include "engine/text/text_banks.h"
#include "link/exchange_data.h"

#define STAGE_COUNT 6
#define EXP_CURVE_COUNT 3
#define TAMER_RANK_COUNT 6

/* Prints a text into a window picture (func_0209caf0) with flag 0x10000. */
void func_0209d080(void *text, void *picture) {
    func_0209caf0(text, picture, 0x10000);
}

/* Copies a text, as func_0209e344 gives it, into one of the 8 text arguments
 * (TEXT_ARGS), and returns that argument. */
void *setTextArg(s16 index, void *text) {
    void *entry;

    entry = getTextArg(index);
    func_0209d2d0(func_0209e344(text), entry);
    return entry;
}

/* Sets a text argument to a number (func_0209cf94). */
void *func_0209cfc4(s16 index, s32 value, s32 digits) {
    return func_0209cf94(index, value, digits, 0);
}

/* Sets a text argument to a number, written by formatNumber. */
void *func_0209cf94(s16 index, s32 value, s32 digits, s32 flags) {
    u16 buffer[32];

    formatNumber(value, digits, buffer, flags);
    return setTextArg(index, buffer);
}

/* Returns one of the 8 text arguments. */
void *getTextArg(s16 index) {
    return TEXT_ARGS[index];
}

/* Returns the name of a stage, In-Training to Armor (texts 32 to 37 of
 * data_0210b7f0), or NULL. */
void *getStageName(u32 index) {
    s32 *archive             = data_0210b7f0;
    s16 entries[STAGE_COUNT] = {32, 33, 34, 35, 36, 37};

    if (index >= STAGE_COUNT) {
        return NULL;
    }
    return (u8 *) archive + archive[entries[index]];
}

/* Returns the name of an exp curve, Early, Normal or Late (texts 53 to 55),
 * or NULL. */
void *getExpCurveName(u32 index) {
    s32 *archive                 = data_0210b7f0;
    s16 entries[EXP_CURVE_COUNT] = {53, 54, 55};

    if (index >= EXP_CURVE_COUNT) {
        return NULL;
    }
    return (u8 *) archive + archive[entries[index]];
}

/* Returns the name of a tamer rank, Normal Tamer to Tamer King (texts 56
 * to 61), or NULL. */
void *getTamerRankName(u32 index) {
    s32 *archive                  = data_0210b7f0;
    s16 entries[TAMER_RANK_COUNT] = {56, 57, 58, 59, 60, 61};

    if (index >= TAMER_RANK_COUNT) {
        return NULL;
    }
    return (u8 *) archive + archive[entries[index]];
}

/* Returns the name of an area (data_0210b014). */
void *getAreaName(s32 index) {
    return func_0209d470(data_0210b014, index);
}

/* Returns one of the texts of data_0210e960. */
void *func_0209cd08(s32 index) {
    return (u8 *) data_0210e960 + data_0210e960[index];
}

/* Starts the link exchange of the farms' visit through the link of
 * func_02079354 (func_0209c438). */
void func_0209cab0(void) {
    struct ExchangeTask *task;

    task          = createTask(&func_0209c438, 0x113);
    task->state   = 0;
    task->wait    = 0;
    data_021da414 = getTaskId(task);
}

/* The same through the link of func_02071acc (func_0209c738). */
void func_0209ca70(void) {
    struct ExchangeTask *task;

    task          = createTask(&func_0209c738, 0x113);
    task->state   = 0;
    task->wait    = 0;
    data_021da414 = getTaskId(task);
}
