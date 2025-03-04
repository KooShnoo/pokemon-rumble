#pragma once

#include <MSL_Common/detail/msl_smart_pointers.hpp>
#include <ppu/CEngine.hpp>

class ICalc {
    virtual void Calc();
};

class CPpuEngine : NPpu::CEngine,
                   public std::tr1::enable_shared_from_this<CPpuEngine>,
                   ICalc {
    // u32 override_vtable; // TODO: get this to generate
    u32 _70;
    u32 _74;
    UNKOWN_DATA(0x74, 0x90, u32);
    u32 _90;
    UNKOWN_DATA(0x90, 0xc0, u32);

public:
    virtual void vfunc_thunk_801035C0();
    virtual void vfunc_thunk_801035b0() {};
    virtual ~CPpuEngine();
    virtual void runScript() throw();

    CPpuEngine();

    bool execScript(const char *pkcName, s32 one,
                    std::tr1::shared_ptr<CPpuEnv> *env);
    u32 tickOnce();
    void fn_800951D0(u32 unk);
    bool prepareScript(const char *pkcName, s32 one,
                       std::tr1::shared_ptr<CPpuEnv> *ppuEnv);
};
// This should actually be 0xc4, but we need to get the vtables to generate
// correctly first.
static_assert(sizeof(CPpuEngine) == 0xc0);
// static_assert(sizeof(CPpuEngine) == 0xc4);

u32 ks_doPKC_fun1(char *pkcName, s32 one, std::tr1::shared_ptr<CPpuEnv> *env);
