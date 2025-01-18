#ifndef _TYPES_H
#define _TYPES_H

#ifndef __cplusplus
#include <stdarg.h>
#include <stddef.h>
#else
#include <cstdarg>
#include <cstddef>
#include <new>
#endif

// #include "decomp.h"
// #include "macros.h"

typedef unsigned long long u64;
typedef signed long long s64;

typedef unsigned long u32;
typedef signed long s32;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned char u8;
typedef signed char s8;

typedef float f32;
typedef double f64;

typedef unsigned int uint;

typedef int UNKWORD;
typedef void UNKTYPE;

#define FALSE 0
#define TRUE 1
typedef int BOOL;

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#define CLAMP(low, high, x)                                                    \
    ((x) > (high) ? (high) : ((x) < (low) ? (low) : (x)))

#define ROUND_UP(x, align) (((x) + (align)-1) & (-(align)))
#define ROUND_UP_PTR(x, align)                                                 \
    ((void*)((((u32)(x)) + (align)-1) & (~((align)-1))))

#define ROUND_DOWN(x, align) ((x) & (-(align)))
#define ROUND_DOWN_PTR(x, align) ((void*)(((u32)(x)) & (~((align)-1))))

#define LENGTHOF(x) (sizeof((x)) / sizeof((x)[0]))

#define MEMCLR(x) __memclr((x), sizeof(*(x)))

#define ALIGN(x) __attribute__((aligned(x)))

#define DECL_SECTION(x) __declspec(section x)
#define DECL_WEAK __declspec(weak)

#define DECLTYPE(x) __decltype__(x)

//Make VSCode shut up
#ifdef __MWERKS__
#define AT_ADDRESS(xyz) : (xyz)
#else
typedef int __vec2x32float__;
#define AT_ADDRESS(xyz)
#endif

#endif
