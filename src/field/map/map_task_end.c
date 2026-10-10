#include "field/map/map_task_end.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "field/actors/actor_create.h"
#include "field/map/data.h"
#include "field/map/map.h"
#include "field/map/map_files.h"
#include "field/map/map_sprite.h"
#include "field/map/ov000_021fbb2c.h"
#include "field/map/ov000_021ff94c.h"
#include "field/map/ov000_022001c4.h"
#include "nitro/g2.h"

/* Called when the main screen's map task ends: frees the map's files and its
 * sprites and clears its state. */
void freeMainMap(void) {
    void *screen;
    void *map;

    func_ov000_021fbec0();
    screen = data_ov000_0220d8d0.screen;
    if (screen != NULL) {
        heapFree(screen);
        data_ov000_0220d8d0.screen = NULL;
    }
    screen = data_ov000_0220d8f4.screen;
    if (screen != NULL) {
        heapFree(screen);
        data_ov000_0220d8f4.screen = NULL;
    }
    screen = data_ov000_0220d8b8.screen;
    if (screen != NULL) {
        heapFree(screen);
        data_ov000_0220d8b8.screen = NULL;
    }
    map = data_021ab7b0;
    if (map != NULL) {
        heapFree(map);
        data_021ab7b0 = NULL;
    }
    G2_BlendNone();
    func_ov000_02200838();
    func_ov000_02201f00();
    deleteMainActors();
    endAllMainMapSprites();
    freeMainSprites();
    clearMainScreenAndBlending();
    clearMainMapState();
}

/* The same for the sub screen's map task. */
void freeSubMap(void) {
    void *screen;
    void *map;

    func_ov000_021fbe88();
    screen = data_ov000_0220d8e8.screen;
    if (screen != NULL) {
        heapFree(screen);
        data_ov000_0220d8e8.screen = NULL;
    }
    screen = data_ov000_0220d8dc.screen;
    if (screen != NULL) {
        heapFree(screen);
        data_ov000_0220d8dc.screen = NULL;
    }
    screen = data_ov000_0220d8c4.screen;
    if (screen != NULL) {
        heapFree(screen);
        data_ov000_0220d8c4.screen = NULL;
    }
    map = data_021ab7a8;
    if (map != NULL) {
        heapFree(map);
        data_021ab7a8 = NULL;
    }
    G2S_BlendNone();
    func_ov000_022007a8();
    func_ov000_02201e40();
    deleteSubActors();
    endAllSubMapSprites();
    freeSubSprites();
    clearSubScreenAndBlending();
    clearSubMapState();
}
