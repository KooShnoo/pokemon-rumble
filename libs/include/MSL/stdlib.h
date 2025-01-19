#ifndef MSL_STDLIB_H
#define MSL_STDLIB_H
#include <arith.h>
#include <internal/mbstring.h>
#include <internal/rand.h>
#include <internal/strtold.h>

void *malloc(size_t size) __attribute__((nothrow));

#endif
