#ifndef TYPES_H
#define TYPES_H

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;

typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;

typedef int BOOL;
#define TRUE 1
#define FALSE 0

#ifndef NULL
    #define NULL ((void *) 0)
#endif

/* Zero-fills size bytes at ptr in place, without a call: the stm loop mwcc
 * emits for a "= {0}" initialiser. The game clears its structs and buffers
 * this way where no plain C statement makes mwcc emit it, so the compiler's
 * intrinsic is named here. */
#define CLEAR(ptr, size) __builtin__clear((ptr), (size))

#endif /* TYPES_H */
