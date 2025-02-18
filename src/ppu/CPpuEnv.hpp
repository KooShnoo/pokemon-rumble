#pragma once

class CPpuCode;
#include <MSL_Common/detail/msl_smart_pointers.hpp>
#include <ppu/CEnvironment.hpp>

class CPpuEnv : public std::tr1::enable_shared_from_this<CPpuEnv>,
                NPpu::CEnvironemnt {
  public:
    u8 _pad[0x24];

    // std::tr1::shared_ptr<CPpuCode> make_ppuCode(const char *pkcName,
    //                                             int param_4);
};
static_assert(sizeof(CPpuEnv) == 0x3c);
