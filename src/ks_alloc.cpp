// #include <revolution/types.h>
#include <types.h>
#include <stdlib.h>

void* (*callback)(void) = 0;

// ty chippy
void *ks_malloc(size_t size) throw() {
    if (size == 0) {
        size = 4;
    }

    while (true) {
        void *buf = malloc(size);
        if (buf != 0) {
            return buf;
        } else if (callback) {
            callback();
        } else {
            return 0;
        }
    }
    
    return 0;
}
