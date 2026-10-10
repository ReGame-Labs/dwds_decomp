#include "field/map/map_sprite.h"
#include "engine/data.h"
#include "engine/gfx/gfx_files.h"
#include "engine/libs.h"
#include "field/map/data.h"
#include "field/map/map_sprite_draw.h"

/* Ends all the main screen's map sprites. */
void endAllMainMapSprites(void) {
    s32 i;

    for (i = 0; i < MAP_SPRITE_COUNT; i++) {
        endMainMapSprite(i);
    }
}

/* Ends all the sub screen's map sprites. */
void endAllSubMapSprites(void) {
    s32 i;

    for (i = 0; i < MAP_SPRITE_COUNT; i++) {
        endSubMapSprite(i);
    }
}

/* Ends a main screen map sprite: its character's files lose a user, and the
 * graphics' VRAM is freed once no sprite uses them. */
void endMainMapSprite(u32 index) {
    struct MapSprite *sprite;
    u16 graphics;

    if (index >= MAP_SPRITE_COUNT) {
        return;
    }
    sprite = &MAIN_MAP_SPRITES[index];
    if (!(sprite->flags & MAP_SPRITE_IN_USE)) {
        return;
    }
    func_ov000_021fa444(sprite->character);
    graphics = data_02107f34[sprite->character].graphics;
    if (data_021ea308[graphics] == 0 && MAIN_MAP_CHARACTER_VRAM[graphics] != 0xFFFF) {
        freeMainMapSpriteVram(MAIN_MAP_CHARACTER_VRAM[graphics]);
        MAIN_MAP_CHARACTER_VRAM[data_02107f34[sprite->character].graphics] = 0xFFFF;
    }
    func_02030f18(sprite, 0, sizeof(struct MapSprite));
}

/* Ends a main screen map sprite at the end of its task's frame. */
void requestEndMainMapSprite(u32 index) {
    struct MapSprite *sprite;

    if (index >= MAP_SPRITE_COUNT) {
        return;
    }
    sprite = &MAIN_MAP_SPRITES[index];
    if (sprite->flags & MAP_SPRITE_IN_USE) {
        MAIN_MAP_SPRITES_ENDING[index] = 1;
    }
}

/* The same for the sub screen. */
void endSubMapSprite(u32 index) {
    struct MapSprite *sprite;
    u16 graphics;

    if (index >= MAP_SPRITE_COUNT) {
        return;
    }
    sprite = &SUB_MAP_SPRITES[index];
    if (!(sprite->flags & MAP_SPRITE_IN_USE)) {
        return;
    }
    func_ov000_021fa444(sprite->character);
    graphics = data_02107f34[sprite->character].graphics;
    if (data_021ea308[graphics] == 0 && SUB_MAP_CHARACTER_VRAM[graphics] != 0xFFFF) {
        freeSubMapSpriteVram(SUB_MAP_CHARACTER_VRAM[graphics]);
        SUB_MAP_CHARACTER_VRAM[data_02107f34[sprite->character].graphics] = 0xFFFF;
    }
    func_02030f18(sprite, 0, sizeof(struct MapSprite));
}

/* Ends a sub screen map sprite at the end of its task's frame. */
void requestEndSubMapSprite(u32 index) {
    struct MapSprite *sprite;

    if (index >= MAP_SPRITE_COUNT) {
        return;
    }
    sprite = &SUB_MAP_SPRITES[index];
    if (sprite->flags & MAP_SPRITE_IN_USE) {
        SUB_MAP_SPRITES_ENDING[index] = 1;
    }
}

/* Loads a map character's animation file, unless it is loaded, and counts a
 * user more. */
void loadMapCharacterAnim(s32 character) {
    char name[6];
    char path[26];
    u16 anim;

    anim = data_02107f36[character][0];
    if (data_021eb4bc[anim] == NULL && data_021e9e38[anim] == 0) {
        func_020e3a68(name, data_ov000_02206790, anim);
        joinPath(path, data_ov000_02206794, name);
        func_02043fc4(&data_021eb4bc[anim], path);
    }
    data_021e9e38[anim]++;
}

/* Returns a main screen map sprite, NULL past the last. */
struct MapSprite *getMainMapSprite(u32 index) {
    if (index >= MAP_SPRITE_COUNT) {
        return NULL;
    }
    return &MAIN_MAP_SPRITES[index];
}

/* Returns a sub screen map sprite, NULL past the last. */
struct MapSprite *getSubMapSprite(u32 index) {
    if (index >= MAP_SPRITE_COUNT) {
        return NULL;
    }
    return &SUB_MAP_SPRITES[index];
}
