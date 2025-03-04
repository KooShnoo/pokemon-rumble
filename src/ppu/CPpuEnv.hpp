#pragma once

#include <MSL_Common/detail/msl_smart_pointers.hpp>
#include <ppu/CEnvironment.hpp>

class CPpuEnv : public std::tr1::enable_shared_from_this<CPpuEnv>,
                NPpu::CEnvironemnt {
public:
    UNKOWN_DATA(0x0, 0x20, u8);
    virtual void CPpuEnv_vfunc_shared_ptr_801054D0();
};
static_assert(sizeof(CPpuEnv) == 0x3c);
