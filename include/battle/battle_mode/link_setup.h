#ifndef BATTLE_BATTLE_MODE_LINK_SETUP_H
#define BATTLE_BATTLE_MODE_LINK_SETUP_H

/* The link battle's preparation: the party screen and the options screen, each
 * DS sending the other its state, party and option. */

#include "types.h"

struct LinkSetupTask;
struct TextWindow;
struct WindowLayout;

BOOL readFileAsync(void *dest, const char *path);
void func_ov002_02251e18(struct LinkSetupTask *task);
void func_ov002_0225209c(struct LinkSetupTask *task);
void func_ov002_02252b44(struct LinkSetupTask *task);
void func_ov002_02252cf4(struct LinkSetupTask *task);
void func_ov002_02252f00(void);
void func_ov002_02253624(struct LinkSetupTask *task);
void copyLinkWindowLayout(struct WindowLayout *layout, struct TextWindow *window);
void tickLinkSetupTask(void);
void func_ov002_02251910(struct LinkSetupTask *task);
void func_ov002_02251b2c(struct LinkSetupTask *task);
void func_ov002_022521bc(struct LinkSetupTask *task);
void func_ov002_02252808(struct LinkSetupTask *task);
void func_ov002_02252d48(struct LinkSetupTask *task);
void func_ov002_02253204(struct LinkSetupTask *task);
void func_ov002_02253068(struct LinkSetupTask *task);
void func_ov002_02252f44(u8 slot);
void func_ov002_02253754(struct LinkSetupTask *task);
u8 func_ov002_02253fec(struct LinkSetupTask *task);
void func_ov002_02251ec8(struct LinkSetupTask *task);
void func_ov002_02251d7c(struct LinkSetupTask *task);
void func_ov002_02252aa8(struct LinkSetupTask *task);
void func_ov002_02252bf4(struct LinkSetupTask *task);
void func_ov002_02253f0c(struct LinkSetupTask *task);

#endif /* BATTLE_BATTLE_MODE_LINK_SETUP_H */
