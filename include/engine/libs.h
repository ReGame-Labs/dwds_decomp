#ifndef ENGINE_LIBS_H
#define ENGINE_LIBS_H

#include "types.h"

/* NitroSystem's expanded heap (NNS_FndExpHeap), which the game's two heaps are */
struct NNSiFndHeapHead;
/* NNS_FndCreateExpHeapEx(void *start, u32 size, u16 flags), its parameters
 * left open while its caller holds the arena block as a u32 */
struct NNSiFndHeapHead *func_020b9068();
/* NNS_FndAllocFromExpHeapEx: a negative alignment takes the block from the
 * heap's end */
void *func_020b9018(struct NNSiFndHeapHead *heap, u32 size, s32 alignment);
/* NNS_FndFreeToExpHeap(heap, void *block), its parameters left open while
 * some callers hold their blocks as an s32 */
void func_020b8fd8();
/* NNS_FndGetTotalFreeSizeForExpHeap */
u32 func_020b8fb0(struct NNSiFndHeapHead *heap);

s32 func_0202ec98();
s32 func_020b9cc0();
s32 func_020b9d30();
s32 func_020b9d80();
s32 func_020bc2b8();
s32 func_020bc2ec();
s32 func_020bdb90();
s32 func_020bdcdc();
s32 func_020bddc8();
s32 func_020bdf6c();
s32 func_020bea58();
s32 func_020bea90();
s32 func_020bedc8();
s32 func_020c0020();
s32 func_020d8ef8();
s32 func_020d906c();
s32 func_020d93bc();
s32 func_020da29c();
s32 func_020da454();
s32 func_020da47c();
s32 func_020da4a4();
s32 func_020da4b8();
s32 func_020da4cc();
s32 func_020da4e0();
s32 func_020da4f4();
s32 func_020da508();
s32 func_020da52c();
s32 func_020da550();
s32 func_020da564();
s32 func_020da7f0();
s32 func_020db8cc();
s32 func_020dc1c8();
s32 func_020dc230();
s32 func_020dc298();
s32 func_020dc300();
s32 func_020dc368();
s32 func_020dc3d0();
s32 func_020dc438();
s32 func_020dc4a0();
s32 func_020dc820();
s32 func_020e22dc();
s32 func_020e233c();
s32 func_020e23c0();
s32 func_020e2454();
s32 func_020e2d7c();
s32 func_020e2dd4();
s32 func_020e4f58();
s32 func_020e5e04(void);
void func_020e5e18(s32 state);
s32 func_020e5e9c();
s32 func_020e6250();
s32 func_020e966c();
s32 func_020ebbd4();
s32 func_020ebc34();
s32 func_020ec1a0();
s32 func_020ec2f4();
s32 func_020edfb4();
s32 func_020ee0f4();
s32 func_020f9424();
s32 func_020f9b1c();
s32 func_020fedb8();
s32 func_020fee20();
s32 func_020fee60();
s32 func_020fefac();
s32 func_020fefd0();
s32 func_020ff038();
s32 func_020ff0e4();
s32 func_020ff12c();
s32 func_020ff4ec();
s32 func_020bcc74();
s32 func_020ee16c();
s32 func_020ee3f0();
s32 func_020f9384();
s32 func_020f93a4();
s32 func_020f9b00();
s32 func_020e5000();
s32 func_020e52cc();
s32 func_020e52e0();
void func_020d9e60(vu16 *reg, s32 brightness);
s16 func_020e9340();
s32 func_0202de00();
float func_0202d600(float x);
s32 func_020e70a8();
s32 func_020e7610();
s32 func_020e7668();
s32 func_020e7708();
s32 func_020e7850();
s32 func_020e78fc();
void func_020e22f4();
void func_020e2324();
s32 func_020fec48();
s32 func_020ff144();
s32 func_020db3f8();
s32 func_020e3a68();
void func_020ebbe4();
s32 func_020ec31c();
void func_020ec330();
void func_020f0d60();

/* The SDK's wireless library (0x020b6bd8-0x020b8a80) */
/* shuts the local wireless link down */
s32 func_020b6c30();
void func_020b6d70(void);
/* the bitmap of the DS connected */
u16 func_020b7604(void);

/* MSL, the Metrowerks C library */
s32 func_02030108();
void func_02030238(s32 arg0);
void func_02030288(void);
void func_02030628(void);
s32 func_020306ac(s32 arg0);
void func_020306b8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_02030788(void *arg0);
void func_020307bc();
s32 func_02030a8c();
double func_02030ca4(double value, s32 shift);
void func_02030dec(s32 arg0, s32 arg1);
s32 func_02030e10(s8 *arg0, s8 arg1);
s32 func_02030e24(s16 *arg0, u8 *arg1, s32 arg2);
s32 func_02030e80(u8 *a, u8 *b, s32 count);
void *func_02030f18(void *dst, s32 value, u32 size);
void *func_02030f78(void *dst, const void *src, u32 size);
void func_02030f98(void *dst, s32 value, u32 size);
void func_02031044();
s32 func_02031048(char *buffer, const char *fmt, ...);
s32 func_0203107c(char *buffer, s32 size, const char *fmt, ...);
s32 func_020310ac();
s32 func_02031114();
s32 func_02031228(void *arg0, const void *arg1, s32 arg2);
s32 func_02031274(s32 arg0, s32 arg1, s32 arg2);
void func_02033304(s32 arg0);
s32 func_02033314(void);
s32 func_02033348(const u8 *str, const char *fmt, ...);
s32 func_02033378(const u8 *str, const char *fmt, char *args);
s32 func_020333d0(void *stream, s32 ch, s32 op);
s32 func_02033448();
s32 func_02034454();
s32 func_02034648(u8 *s1, u8 *s2, s32 n);
u8 *func_02034788(u8 *dst, const u8 *src);
s32 func_020347b8();
s32 func_0203481c();
s32 func_020348e4(u8 *arg0);
void func_02034900(s32 arg0);
s32 func_02034910();
void func_02035d44(s32 arg0);
s32 func_02035d58();
s32 func_020366d8(void *arg0, s32 arg1);
u16 *func_0203674c(u16 *buffer, s32 value, s32 count);
void *func_02036774(u16 *dst, const u16 *src, s32 count);
void func_02036784();
void func_020367e8(s32 arg0, s32 arg1, s32 format, ...);
void *func_02036818(void *stream, const u16 *src, s32 count);
u16 *func_02038228(u16 *dst, u16 *src);
s32 func_02038248(u16 *str);
s32 func_02038264();
s32 func_0203864c();
double func_02039e6c(double x);
double func_02039e90();
double func_02039f50();
double func_0203a234(double y, double x);
void func_0203a240(void);
s32 func_020db56c();
s64 func_020fef34();
s32 func_020ff5cc();
s32 func_020da1e4();
s32 func_020da1f4();
s32 func_020da204();
s32 func_020da214();
void func_020db8e8();
void func_020db99c();
void func_020db9e8();
void func_020dba5c();
void func_020dba80();
void func_020dbacc();
void func_020dbb40();
void func_020dbb64();
void func_020dbbbc();
void func_020dbc30();
void func_020dbca0();
void func_020dbd04();
void func_020dbd84();
void func_020dc68c();
void func_020dc6f4();
void func_020dc75c();
void func_020dc7c4();

#endif /* ENGINE_LIBS_H */
