#include "battle/sprite_slots.h"
#include "engine/bg/bg_screen.h"
#include "engine/data.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_create.h"
#include "engine/sprite/sprite_draw.h"

/* Forwards each sprite's changes to its pool sprite, and moves it. */
void updateSpriteSlots(void) {
    s32 i;
    s32 stopped;
    struct SpriteSlot *slot;

    slot = SPRITE_SLOTS;
    for (i = 0; i < SPRITE_SLOT_COUNT; i++) {
        if (slot->flags & SPRITE_SLOT_USED) {
            stopped = 0;
            if (slot->flags & SPRITE_SLOT_MOVING) {
                if (slot->moveDelay != 0) {
                    slot->moveDelay--;
                } else {
                    slot->x.value += slot->dx.value;
                    slot->y.value += slot->dy.value;
                    if (slot->flags & SPRITE_SLOT_MOVE_TIMED) {
                        slot->moveFrames--;
                        if (slot->moveFrames == 0) {
                            stopped = 1;
                            slot->flags &= ~SPRITE_SLOT_MOVE_TIMED;
                            if (slot->flags & SPRITE_SLOT_RELEASE_AFTER_MOVE) {
                                releaseSlotSprite(slot->handle);
                                slot->flags &= ~SPRITE_SLOT_RELEASE_AFTER_MOVE;
                            }
                        }
                    }
                    slot->flags |= SPRITE_SLOT_MOVED;
                }
            }
            if (slot->flags & SPRITE_SLOT_CREATE) {
                slot->flags &= ~SPRITE_SLOT_CREATE;
                createSlotPoolSprite(slot);
            }
            if (slot->flags & SPRITE_SLOT_CREATE_NEXT) {
                slot->flags &= ~SPRITE_SLOT_CREATE_NEXT;
                slot->flags |= SPRITE_SLOT_CREATE;
            } else {
                if (slot->flags & SPRITE_SLOT_MOVED) {
                    if (slot->flags & SPRITE_SLOT_SUB_SCREEN) {
                        setSubSpritePos(slot->handle - SUB_SPRITE_HANDLE, slot->x.part.whole, slot->y.part.whole);
                    } else {
                        setMainSpritePos(slot->handle, slot->x.part.whole, slot->y.part.whole);
                    }
                    slot->flags &= ~SPRITE_SLOT_MOVED;
                }
                if (slot->flags & SPRITE_SLOT_PALETTE_CHANGED) {
                    applySlotSpritePalette(slot);
                    slot->flags &= ~SPRITE_SLOT_PALETTE_CHANGED;
                }
                if (slot->flags & SPRITE_SLOT_PRIORITY_CHANGED) {
                    applySlotSpritePriority(slot);
                    slot->flags &= ~SPRITE_SLOT_PRIORITY_CHANGED;
                }
                if (slot->flags & SPRITE_SLOT_UNK29_CHANGED) {
                    func_0207c664(slot);
                    slot->flags &= ~SPRITE_SLOT_UNK29_CHANGED;
                }
                if (slot->flags & SPRITE_SLOT_ANIMATION_CHANGED) {
                    applySlotSpriteAnimation(slot);
                    slot->flags &= ~SPRITE_SLOT_ANIMATION_CHANGED;
                }
                if (slot->flags & SPRITE_SLOT_SHOW) {
                    if (slot->flags & SPRITE_SLOT_SUB_SCREEN) {
                        clearSubSpriteFlags(slot->handle - SUB_SPRITE_HANDLE, SPRITE_HIDDEN);
                    } else {
                        clearMainSpriteFlags(slot->handle, SPRITE_HIDDEN);
                    }
                    slot->flags &= ~SPRITE_SLOT_SHOW;
                    slot->flags |= SPRITE_SLOT_SHOWN;
                }
                if (slot->flags & SPRITE_SLOT_HIDE) {
                    if (slot->flags & SPRITE_SLOT_SUB_SCREEN) {
                        setSubSpriteFlags(slot->handle - SUB_SPRITE_HANDLE, SPRITE_HIDDEN);
                    } else {
                        setMainSpriteFlags(slot->handle, SPRITE_HIDDEN);
                    }
                    slot->flags &= ~SPRITE_SLOT_HIDE;
                    slot->flags &= ~SPRITE_SLOT_SHOWN;
                }
            }
            if (stopped == 1) {
                slot->flags &= ~SPRITE_SLOT_MOVING;
            }
        }
        slot++;
    }
}

/* Empties the sprite table. */
s32 initSpriteSlots(void) {
    s32 i;
    struct SpriteSlot *slot;

    slot = SPRITE_SLOTS;
    for (i = 0; i < SPRITE_SLOT_COUNT; i++) {
        slot->flags = 0;
        slot->index = i;
        slot++;
    }
    return 0;
}

/* Takes a free slot for a sprite that is created in the pool two frames later,
 * hidden; returns the slot's index. A handle that already has a slot keeps it
 * and is returned instead. */
s32 queueSlotSprite(s16 spriteId, s16 x, s16 y, s16 palette, u16 unk12, s32 handle) {
    struct SpriteSlot *slot;
    s32 inUse;
    s32 i;

    if (handle != -1 && handle != -2 && findSpriteSlot(handle) != NULL) {
        return handle;
    }
    slot = SPRITE_SLOTS;
    for (i = 0; i < SPRITE_SLOT_COUNT; i++) {
        if (slot->flags & SPRITE_SLOT_USED) {
            inUse = 1;
        } else {
            inUse = 0;
        }
        if (inUse == 0) {
            slot->flags = 0;
            slot->flags |= SPRITE_SLOT_USED;
            slot->spriteId     = spriteId;
            slot->x.part.whole = x;
            /* The original clears the y fraction twice and never the x one. */
            slot->y.part.frac  = 0;
            slot->y.part.whole = y;
            slot->y.part.frac  = 0;
            slot->palette      = palette;
            slot->unk12        = unk12;
            slot->priority     = 0;
            slot->unk29        = 0;
            slot->animation    = 0;
            slot->handle       = handle;
            slot->flags |= SPRITE_SLOT_CREATE_NEXT;
            slot->flags |= SPRITE_SLOT_HIDE;
            return i;
        }
        slot++;
    }
    return -1;
}

/* Takes a free slot and creates its sprite in the pool at once, hidden: in the
 * given pool slot, or in a free one for -1 (main screen) or -2 (sub screen).
 * Returns the sprite's handle. */
u32 createSlotSprite(u16 spriteId, s16 x, s16 y, u16 palette, u16 unk12, u32 handle) {
    struct SpriteSlot *slot;
    s32 inUse;
    s32 i;

    slot = SPRITE_SLOTS;
    for (i = 0; i < SPRITE_SLOT_COUNT; i++) {
        if (slot->flags & SPRITE_SLOT_USED) {
            inUse = 1;
        } else {
            inUse = 0;
        }
        if (inUse == 0) {
            slot->flags = 0;
            slot->flags |= SPRITE_SLOT_USED;
            slot->spriteId     = spriteId;
            slot->x.part.whole = x;
            slot->y.part.frac  = 0;
            slot->y.part.whole = y;
            slot->y.part.frac  = 0;
            slot->palette      = palette;
            slot->unk12        = unk12;
            slot->priority     = 0;
            slot->unk29        = 0;
            slot->animation    = 0;
            slot->handle       = handle;
            if (handle < SUB_SPRITE_HANDLE || handle == -1) {
                if (slot->handle != -1) {
                    createMainSpriteAt(slot->spriteId, slot->x.part.whole, slot->y.part.whole, slot->palette, slot->unk12,
                                       slot->handle);
                } else {
                    slot->handle =
                        createMainSprite(slot->spriteId, slot->x.part.whole, slot->y.part.whole, slot->palette, slot->unk12);
                }
            } else {
                if (slot->handle != -2) {
                    createSubSpriteAt(slot->spriteId, slot->x.part.whole, slot->y.part.whole, slot->palette, slot->unk12,
                                      slot->handle - SUB_SPRITE_HANDLE);
                } else {
                    slot->handle =
                        createSubSprite(slot->spriteId, slot->x.part.whole, slot->y.part.whole, slot->palette, slot->unk12);
                    slot->handle += SUB_SPRITE_HANDLE;
                }
                slot->flags |= SPRITE_SLOT_SUB_SCREEN;
            }
            slot->flags |= SPRITE_SLOT_HIDE;
            return slot->handle;
        }
        slot++;
    }
    return -1;
}

/* Releases the sprite and its pool sprite. */
s32 releaseSlotSprite(s32 handle) {
    struct SpriteSlot *slot;

    slot = findSpriteSlot(handle);
    if (slot != NULL) {
        if (slot->flags & SPRITE_SLOT_SUB_SCREEN) {
            freeSubSprite(slot->handle - SUB_SPRITE_HANDLE);
            slot->flags &= ~SPRITE_SLOT_USED;
            return 1;
        }
        freeMainSprite(slot->handle);
        slot->flags &= ~SPRITE_SLOT_USED;
        return 1;
    }
    return 0;
}

/* Whether the sprite exists in its pool: not still waiting to be created. */
s32 isSlotSpriteCreated(s32 handle) {
    struct SpriteSlot *slot;
    u32 flags;

    slot = findSpriteSlot(handle);
    if (slot != NULL) {
        flags = slot->flags;
        if ((flags & SPRITE_SLOT_CREATE_NEXT) || (flags & SPRITE_SLOT_CREATE)) {
            return 0;
        }
        return 1;
    }
    return 0;
}

/* The slot in use whose sprite has the handle, or NULL. */
struct SpriteSlot *findSpriteSlot(s32 handle) {
    s32 i;
    struct SpriteSlot *slot;

    slot = SPRITE_SLOTS;
    for (i = 0; i < SPRITE_SLOT_COUNT; i++) {
        if ((slot->flags & SPRITE_SLOT_USED) && slot->handle == handle) {
            return slot;
        }
        slot++;
    }
    return NULL;
}

/* The slot with the index. */
struct SpriteSlot *getSpriteSlot(s32 index) {
    return &SPRITE_SLOTS[index];
}

/* Shows the sprite next frame, dropping a pending hide. */
void showSlotSprite(s32 handle) {
    struct SpriteSlot *slot;

    slot = findSpriteSlot(handle);
    if (slot != NULL) {
        slot->flags |= SPRITE_SLOT_SHOW;
        if (slot->flags & SPRITE_SLOT_HIDE) {
            slot->flags &= ~SPRITE_SLOT_HIDE;
        }
    }
}

/* Shows the sprite of the slot with the index next frame, dropping a pending
 * hide. */
void showSlotSpriteByIndex(s32 index) {
    struct SpriteSlot *slot = &SPRITE_SLOTS[index];

    slot->flags |= SPRITE_SLOT_SHOW;
    if (slot->flags & SPRITE_SLOT_HIDE) {
        slot->flags &= ~SPRITE_SLOT_HIDE;
    }
}

/* Hides the sprite next frame, dropping a pending show. */
void hideSlotSprite(s32 handle) {
    struct SpriteSlot *slot;

    slot = findSpriteSlot(handle);
    if (slot != NULL) {
        slot->flags |= SPRITE_SLOT_HIDE;
        if (slot->flags & SPRITE_SLOT_SHOW) {
            slot->flags &= ~SPRITE_SLOT_SHOW;
        }
    }
}

/* Moves the sprite to (x, y). */
void setSlotSpritePosition(s32 handle, s16 x, s16 y) {
    struct SpriteSlot *slot;

    slot = findSpriteSlot(handle);
    if (slot != NULL) {
        slot->x.part.whole = x;
        slot->x.part.frac  = 0;
        slot->y.part.whole = y;
        slot->y.part.frac  = 0;
        slot->flags |= SPRITE_SLOT_MOVED;
    }
}

/* Moves the sprite by (dx, dy) a frame after delay frames: for frames frames,
 * or for good with 0xFFFF; released at the end if release is 1. */
void moveSlotSprite(s32 release, s32 handle, union Fixed16 dx, union Fixed16 dy, u16 frames, u16 delay) {
    struct SpriteSlot *slot;

    slot = findSpriteSlot(handle);
    if (slot == NULL) {
        return;
    }
    slot->dx         = dx;
    slot->dy         = dy;
    slot->moveFrames = frames;
    slot->moveDelay  = delay;
    slot->flags |= SPRITE_SLOT_MOVING;
    if (frames < 0xFFFF) {
        slot->flags |= SPRITE_SLOT_MOVE_TIMED;
    }
    if (release == 1) {
        slot->flags |= SPRITE_SLOT_RELEASE_AFTER_MOVE;
    }
}

/* Sets the sprite's palette and unk12. */
void setSlotSpritePalette(s32 handle, u16 palette, u16 unk12) {
    struct SpriteSlot *slot;

    slot          = findSpriteSlot(handle);
    slot->palette = palette;
    slot->unk12   = unk12;
    slot->flags |= SPRITE_SLOT_PALETTE_CHANGED;
}

/* Sets the sprite's OAM priority. */
void setSlotSpritePriority(s32 handle, u8 priority) {
    struct SpriteSlot *slot;

    slot = findSpriteSlot(handle);
    if (slot != NULL) {
        slot->priority = priority;
        slot->flags |= SPRITE_SLOT_PRIORITY_CHANGED;
    }
}

/* Sets the OAM priority of the slot with the index. */
void setSlotSpritePriorityByIndex(u16 index, u8 priority) {
    struct SpriteSlot *slot = &SPRITE_SLOTS[index];

    slot->priority = priority;
    slot->flags |= SPRITE_SLOT_PRIORITY_CHANGED;
}

/* Sets the sprite's unk29, which goes to its pool sprite's unk1D. */
void func_0207c8b8(s32 handle, u8 unk29) {
    struct SpriteSlot *slot;

    slot        = findSpriteSlot(handle);
    slot->unk29 = unk29;
    slot->flags |= SPRITE_SLOT_UNK29_CHANGED;
}

/* Sets unk29 of the slot with the index. */
void func_0207c890(s32 index, u8 unk29) {
    struct SpriteSlot *slot = &SPRITE_SLOTS[index];

    slot->unk29 = unk29;
    slot->flags |= SPRITE_SLOT_UNK29_CHANGED;
}

/* The sprite's animation. */
u16 getSlotSpriteAnimation(s32 handle) {
    return findSpriteSlot(handle)->animation;
}

/* Sets the sprite's animation. */
void setSlotSpriteAnimation(s32 handle, u16 animation) {
    struct SpriteSlot *slot;

    slot            = findSpriteSlot(handle);
    slot->animation = animation;
    slot->flags |= SPRITE_SLOT_ANIMATION_CHANGED;
}

/* Sets the animation of the slot with the index. */
void setSlotSpriteAnimationByIndex(u16 index, u16 animation) {
    struct SpriteSlot *slot = &SPRITE_SLOTS[index];

    slot->animation = animation;
    slot->flags |= SPRITE_SLOT_ANIMATION_CHANGED;
}

/* The sprite's pool sprite. */
struct Sprite *getSlotPoolSprite(u32 handle) {
    struct SpriteSlot *slot;

    slot = findSpriteSlot(handle);
    if (slot == NULL) {
        return NULL;
    }
    if (handle < SUB_SPRITE_HANDLE) {
        return getMainSprite(slot->handle);
    }
    return getSubSprite(slot->handle - SUB_SPRITE_HANDLE);
}

/* Creates the slot's sprite in its pool, hidden: in its pool slot, or in a free
 * one for -1 (main screen) or -2 (sub screen). */
void createSlotPoolSprite(struct SpriteSlot *slot) {
    u32 handle;

    handle = slot->handle;
    if (handle < SUB_SPRITE_HANDLE || handle == -1) {
        if (handle != -1) {
            createMainSpriteAt(slot->spriteId, slot->x.part.whole, slot->y.part.whole, slot->palette, slot->unk12, handle);
        } else {
            slot->handle =
                createMainSprite(slot->spriteId, slot->x.part.whole, slot->y.part.whole, slot->palette, slot->unk12);
        }
        setMainSpriteFlags(slot->handle, SPRITE_HIDDEN);
    } else {
        if (handle != -2) {
            createSubSpriteAt(slot->spriteId, slot->x.part.whole, slot->y.part.whole, slot->palette, slot->unk12,
                              handle - SUB_SPRITE_HANDLE);
        } else {
            slot->handle = createSubSprite(slot->spriteId, slot->x.part.whole, slot->y.part.whole, slot->palette, slot->unk12);
            slot->handle += SUB_SPRITE_HANDLE;
        }
        slot->flags |= SPRITE_SLOT_SUB_SCREEN;
        setSubSpriteFlags(slot->handle - SUB_SPRITE_HANDLE, SPRITE_HIDDEN);
    }
    slot->flags &= ~SPRITE_SLOT_SHOWN;
}

/* Passes the palette and unk12 on to the pool sprite, which keeps them a byte
 * each. */
void applySlotSpritePalette(struct SpriteSlot *slot) {
    struct Sprite *sprite;

    sprite          = getSlotPoolSprite(slot->handle);
    sprite->palette = slot->palette;
    sprite->unk29   = slot->unk12;
}

/* Passes the OAM priority on to the pool sprite. */
void applySlotSpritePriority(struct SpriteSlot *slot) {
    u32 handle;

    handle = slot->handle;
    if (handle < SUB_SPRITE_HANDLE) {
        setMainSpriteBgPriority(handle, slot->priority);
        return;
    }
    setSubSpriteBgPriority(handle - SUB_SPRITE_HANDLE, slot->priority);
}

/* Passes unk29 on to the pool sprite. */
void func_0207c664(struct SpriteSlot *slot) {
    getSlotPoolSprite(slot->handle)->unk1D = slot->unk29;
}

/* Passes the animation on to the pool sprite. */
void applySlotSpriteAnimation(struct SpriteSlot *slot) {
    getSlotPoolSprite(slot->handle)->anim = slot->animation;
}
