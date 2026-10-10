#include "link/wifi_friend_roster_data.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/system/system.h"
#include "link/wifi_friend_roster.h"

/* What the friend roster's list has come to: 1 a friend picked, -1 still
 * open, -2 and -3 its other two ends, -10 no list. */
s32 getFriendRosterListResult(void) {
    s16 result;

    if (FRIEND_ROSTER_LIST == NULL) {
        return -10;
    }
    result = ((struct FriendRosterList *) findTask(FRIEND_ROSTER_LIST_TASK_ID))->result;
    if (result == 0) {
        return -1;
    }
    if (result == 1) {
        return 1;
    }
    if (result == -1) {
        return -2;
    }
    if (result == -2) {
        return -3;
    }
    return -10;
}

/* The friend roster list's top row. */
s16 getFriendRosterListTop(void) {
    if (FRIEND_ROSTER_LIST == NULL) {
        return -1;
    }
    return ((struct FriendRosterList *) findTask(FRIEND_ROSTER_LIST_TASK_ID))->top;
}

/* The friend roster list's cursor, from its top row. */
s16 getFriendRosterListCursor(void) {
    if (FRIEND_ROSTER_LIST == NULL) {
        return -1;
    }
    return ((struct FriendRosterList *) findTask(FRIEND_ROSTER_LIST_TASK_ID))->cursor;
}

/* The 64-bit key of the friend under the cursor, or 0. */
s64 getPickedFriendKey(void) {
    struct WifiData *wifi = (struct WifiData *) data_021db618;
    struct FriendRosterList *list;
    s64 key;
    void *friendData;

    if (FRIEND_ROSTER_LIST == NULL) {
        return 0;
    }
    list       = findTask(FRIEND_ROSTER_LIST_TASK_ID);
    key        = 0;
    friendData = wifi->friends[(s16) (list->top + list->cursor)];
    if (func_020ff144(friendData) != 0) {
        key = func_020fef34(friendData);
    }
    return key;
}

/* The row of data_021db718 of the friend under the cursor, or NULL. */
void *getPickedFriendRow(void) {
    struct WifiData *wifi = (struct WifiData *) data_021db618;
    struct FriendRosterList *list;
    s32 offset;
    u8 *row;

    if (FRIEND_ROSTER_LIST == NULL) {
        return NULL;
    }
    list   = findTask(FRIEND_ROSTER_LIST_TASK_ID);
    offset = (s16) (list->top + list->cursor) * (s32) sizeof(wifi->friends[0]);
    row    = NULL;
    if (func_020ff144((u8 *) wifi->friends + offset) != 0) {
        row                  = (u8 *) data_021db718 + offset;
        *(u16 *) (row + 0xA) = 0xFFFF; /* the row's last halfword */
    }
    return row;
}

/* func_020ff5cc of the friend under the cursor. */
s32 func_02073c0c(void) {
    struct WifiData *wifi = (struct WifiData *) data_021db618;
    struct FriendRosterList *list;

    if (FRIEND_ROSTER_LIST == NULL) {
        return 0;
    }
    list = findTask(FRIEND_ROSTER_LIST_TASK_ID);
    return func_020ff5cc(wifi->friends[(s16) (list->top + list->cursor)]);
}
