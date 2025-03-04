#pragma once

#include <types.h>

namespace NPpu {

class CEnvironemnt {
public:
    s32 sizeUnkBuffer;
    void *unkBuffer;
    s32 len_functable;
    void *functable;

    virtual void CEnvironment_vfunc_80170420();
};
static_assert(sizeof(CEnvironemnt) == 0x14);

} // namespace NPpu
