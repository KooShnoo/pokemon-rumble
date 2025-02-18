#pragma once

#include <ppu/CPpuEnv.hpp>

class CPpuCode;

namespace NPpu {

class CEngine {
  public:
    CPpuCode *ppuCode;
    CPpuEnv *ppuEnv;
    u8 _pad0[8];
    u32 exec_pkc_return_value;
    int param_0x40;
    int param_0x20;
    int param_0x8;
    u8 _pad1[52];

  public:
    CEngine();
    // virtual u32 tickOnce();
    virtual void runScript() throw();
    void setupMemory(CPpuCode *ppuCode, CPpuEnv *ppuEnv, s32 size1, s32 size2,
                     s32 size3);
};
static_assert(sizeof(CEngine) == 0x58)

} // namespace NPpu
