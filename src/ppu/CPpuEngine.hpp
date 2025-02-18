#pragma once

#include <MSL_Common/detail/msl_smart_pointers.hpp>
#include <ppu/CEngine.hpp>
#include <string>

class ICalc {
    virtual void Calc();
};

class CPpuEngine : public std::tr1::enable_shared_from_this<CPpuEngine>,
                   ICalc,
                   NPpu::CEngine {
  public: // TODO(KooShnoo): remove
    u32 ks_PC;
    std::tr1::shared_ptr<CPpuEngine> shared;
    u32 _74;
    u32 _90;
    u8 _pad1[75];

  public:
    CPpuEngine();

    void runScript() throw();
    bool execScript(const char *pkcName, s32 one,
                    std::tr1::shared_ptr<CPpuEnv> *env);
    u32 tickOnce();
    void fn_800951D0(u32 unk);
    bool prepareScript(const char *pkcName, s32 one,
                       std::tr1::shared_ptr<CPpuEnv> *ppuEnv);
};
// static_assert(sizeof(CPpuEngine) == 0xc4)

u32 ks_doPKC_fun1(std::basic_string<char> &pkcName, s32 one,
                  std::tr1::shared_ptr<CPpuEnv> *env);
