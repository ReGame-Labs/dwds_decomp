#ifndef ENGINE_PALETTE_PALETTE_UPLOAD_H
#define ENGINE_PALETTE_PALETTE_UPLOAD_H

#include "engine/data.h"
#include "types.h"

/* The task that steps the palette effects (runPaletteEffects). */
struct PaletteTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 running;
    /* 0x20 */ s16 unk20;
};

void markSubStandardPalettesDirty(void);
void clearSubPalettesDirty(void);
void clearMainPalettesDirty(void);
void markSubPalettesDirty(void);
void markMainPalettesDirty(void);
void unlockSubPalettes(void);
void unlockMainPalettes(void);
void lockSubPalettes(void);
void lockMainPalettes(void);
void clearSubPalettes(void);
void clearMainPalettes(void);
s32 stepPaletteFade(struct PaletteSet *palettes, struct PaletteEffect *effect);
void stepPaletteEffects(struct PaletteSet *palettes, struct PaletteEffect *effects);
void runPaletteEffects(void);
s32 initPalettes(void);
void uploadPalettes(void);

#endif /* ENGINE_PALETTE_PALETTE_UPLOAD_H */
