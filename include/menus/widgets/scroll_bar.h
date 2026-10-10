#ifndef MENUS_WIDGETS_SCROLL_BAR_H
#define MENUS_WIDGETS_SCROLL_BAR_H

#include "engine/data.h"
#include "types.h"

/* The opening of the field menu, and the scroll bars (8 slots of tasks). */

#define FIELD_MENU_TASK_PRIORITY 0x11A
#define FIELD_MENU_UNK20_SIZE 0xE

#define SCROLL_BAR_COUNT 8

/* A scroll bar's states. */
#define SCROLL_BAR_ACTIVE 0
#define SCROLL_BAR_PAUSED 1
#define SCROLL_BAR_RESUMED 2 /* active from its next frame */

/* A scroll bar's task (tickScrollBar), created by createScrollBar. */
struct ScrollBarTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 id;
    /* 0x20 */ u16 state;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 position;
    /* 0x28 */ s16 unk28[7];
    /* 0x36 */ u8 unk36;
    /* 0x37 */ u8 unk37;
    /* 0x38 */ struct Sprite *sprite;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 unk3E;
    /* 0x40 */ void (*callback)(struct ScrollBarTask *task);
    /* 0x44 */ u8 unk44;
};

s32 isFieldMenuOpen(void);
void openFieldMenu(void);
s16 getScrollBarPos(s32 id);
void resumeScrollBar(s32 id);
void pauseScrollBar(s32 id);
void reopenFieldMenu(void);
void setScrollBarPos(s32 id, s16 position);
void updateScrollBar();
void tickScrollBar(void);
s32 createScrollBar();
void initScrollBars(void);
struct ScrollBarTask *findScrollBar(s32 id);
void closeScrollBar(s32 id);
void startFieldMenuTask(void);
void *func_0204bef8();

#endif /* MENUS_WIDGETS_SCROLL_BAR_H */
