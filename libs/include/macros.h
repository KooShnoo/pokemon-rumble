#ifndef MACROS_H
#define MACROS_H

#ifdef __clang__
#pragma clang diagnostic ignored "-Wc11-extensions"
#pragma clang diagnostic ignored "-Wc++17-extensions"
#define static_assert(cls, size) _Static_assert(sizeof(cls) == size);
#else
#define static_assert(cls, size)
#endif

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#define CLAMP(low, high, x)                                                    \
    ((x) > (high) ? (high) : ((x) < (low) ? (low) : (x)))

#define ROUND_UP(x, align) (((x) + (align) - 1) & (-(align)))
#define ROUND_UP_PTR(x, align)                                                 \
    ((void*)((((u32)(x)) + (align) - 1) & (~((align) - 1))))

#define ROUND_DOWN(x, align) ((x) & (-(align)))
#define ROUND_DOWN_PTR(x, align) ((void*)(((u32)(x)) & (~((align) - 1))))

#define LENGTHOF(x) (sizeof((x)) / sizeof((x)[0]))

#define MEMCLR(x) __memclr((x), sizeof(*(x)))

#define ALIGN(x) __attribute__((aligned(x)))

#define DECL_SECTION(x) __declspec(section x)
#define DECL_WEAK __declspec(weak)

#define DECLTYPE(x) __decltype__(x)

// For VSCode
#ifdef __INTELLISENSE__
typedef int __vec2x32float__;
#define AT_ADDRESS(xyz)
#define ARR_AT_ADDRESS(xyz) = {}
#define asm
#define __attribute__(x)
#define __declspec(x)
#else
#define ARR_AT_ADDRESS(xyz) AT_ADDRESS(xyz)
#define AT_ADDRESS(xyz) : (xyz)
#endif

#endif
