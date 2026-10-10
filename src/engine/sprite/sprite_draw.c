#include "engine/sprite/sprite_draw.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "nitro/fs.h"

/* Sets the BG priority of every main screen sprite in use. */
void setMainSpritesBgPriority(u8 priority) {
    s32 i;

    for (i = 0; i < SPRITE_COUNT; i++) {
        setMainSpriteBgPriority(i, priority);
    }
}

/* Sets the BG priority of every sub screen sprite in use. */
void setSubSpritesBgPriority(u8 priority) {
    s32 i;

    for (i = 0; i < SPRITE_COUNT; i++) {
        setSubSpriteBgPriority(i, priority);
    }
}

/* Whether a main screen sprite's animation is done: true too for no sprite and
 * for a sprite not in use. */
s32 isMainSpriteAnimDone(u32 index) {
    if (index >= SPRITE_COUNT) {
        return TRUE;
    }
    if (!(MAIN_SPRITES[index].flags & SPRITE_IN_USE)) {
        return TRUE;
    }
    if (MAIN_SPRITES[index].animLoops != -1 && MAIN_SPRITES[index].animLoopsDone >= MAIN_SPRITES[index].animLoops) {
        return TRUE;
    }
    return FALSE;
}

/* Reads a file of the movie whole into dest. FALSE if it could not all be
 * read; a file that does not open counts as read. */
s32 readMovieFile(void *dest, const char *path) {
    s32 length;

    func_020d93bc(&MOVIE_FILE);
    if (func_020d906c(&MOVIE_FILE, path) != 0) {
        length = FS_GetLength(&MOVIE_FILE);
        if (length != func_020d8ef8(&MOVIE_FILE, dest, length)) {
            return FALSE;
        }
    }
    return TRUE;
}
