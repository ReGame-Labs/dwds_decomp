#include "menus/digimon/digivolve_preview.h"
#include "engine/data.h"
#include "engine/sprite/sprite.h"
#include "engine/window/window.h"
#include "field/actors/actor_files.h"
#include "menus/digimon/data.h"

/* Keeps the sprites and the actors of the status windows on the windows. */
void func_ov006_02292be4(struct DigivolveScreen *screen) {
    struct Window *status;
    struct Window *preview;
    struct Sprite *sprite;
    struct Actor *actor;

    if (screen->statusWindow == 0xFF || screen->previewWindow == 0xFF) {
        return;
    }
    status  = getWindow(screen->statusWindow);
    preview = getWindow(screen->previewWindow);

    sprite = getSubSprite(screen->work->unk13C);
    if (sprite != NULL) {
        sprite->x = (status->x + 5) * 8;
        sprite->y = (status->y + 1) * 8;
    }
    actor = getSubActor(screen->work->actor);
    if (actor != NULL) {
        actor->x     = (status->x + 3) * 8;
        actor->y     = (status->y + 3) * 8;
        actor->unk80 = 1;
    }

    sprite = getSubSprite(screen->work->unk140);
    if (sprite != NULL) {
        sprite->x = (preview->x + 1) * 8;
        sprite->y = (preview->y + 1) * 8;
    }
    sprite = getSubSprite(screen->work->unk144);
    if (sprite != NULL) {
        sprite->x = (preview->x + 1) * 8;
        sprite->y = (preview->y + 1) * 8;
    }
    sprite = getSubSprite(screen->work->unk148);
    if (sprite != NULL) {
        sprite->x = (preview->x + 1) * 8;
        sprite->y = (preview->y + 7) * 8;
    }
    actor = getSubActor(screen->work->targetActor);
    if (actor != NULL) {
        actor->x     = (preview->x + 12) * 8;
        actor->y     = (preview->y + 3) * 8;
        actor->unk80 = 1;
    }
    sprite = getSubSprite(screen->work->unk154);
    if (sprite != NULL) {
        sprite->x = (preview->x + 10) * 8;
        sprite->y = (preview->y + 7) * 8;
    }
    sprite = getSubSprite(screen->work->unk158);
    if (sprite != NULL) {
        sprite->x = (preview->x + 10) * 8;
        sprite->y = (preview->y + 7) * 8;
    }
}
