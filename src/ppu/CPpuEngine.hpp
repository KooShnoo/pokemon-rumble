#include <types.h>
#include <string>
#include "MSL_Common/detail/msl_smart_pointers.hpp"

class ICalc{
    virtual void Calc();
};

class CEngine{
public:
    CEngine();
    // virtual u32 tickOnce();
};

class CPpuCode;
class CPpuEnv;

class CPpuEngine: public std::tr1::enable_shared_from_this<CPpuEngine>, ICalc, CEngine {
public: // TODO(KooShnoo): remove
    // u8 _03[4];
    CPpuCode *ppuCode;
    CPpuEnv *ppuEnv;
    int param_0x40;
    int param_0x20;
    int param_0x8;
    u32 exec_pkc_return_value;
    u8 _1f[4];
    u32 ks_PC;
    CPpuEngine *shared;
    u8 _83[66];
    u32 _74;
    u8 _78[76];

public:
    CPpuEngine();

    void runScript() throw();
    u32 tickOnce();
    void fn_800951D0(u32 unk);
    void prepareScript(std::basic_string<char> *str, s32, std::tr1::shared_ptr<CPpuEnv> ppuEnv);
};
// static_assert(sizeof(CPpuEngine) == 0xc4)
