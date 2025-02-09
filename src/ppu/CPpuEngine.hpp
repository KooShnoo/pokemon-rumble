#include "MSL_Common/detail/msl_smart_pointers.hpp"
#include <string>
#include <types.h>

class CPpuCode;
class CPpuEnv;

class ICalc {
    virtual void Calc();
};

class CEngine {
  public:
    CPpuCode *ppuCode;
    CPpuEnv *ppuEnv;
    u8 _pad0[8];
    u32 exec_pkc_return_value;
    int param_0x40;
    int param_0x20;
    int param_0x8;
    // u8 _pad0[4];
  public:
    CEngine();
    // virtual u32 tickOnce();
    virtual void runScript() throw();
};

class CPpuEngine : public std::tr1::enable_shared_from_this<CPpuEngine>,
                   ICalc,
                   CEngine {
  public: // TODO(KooShnoo): remove
    // u8 _03[4];
    u32 ks_PC;
    std::tr1::shared_ptr<CPpuEngine> shared;
    u32 _74;
    u8 _pad1[127];

  public:
    CPpuEngine();

    void runScript() throw();
    u32 execScript(const char *pkcName, s32 one,
                   std::tr1::shared_ptr<CPpuEnv> *env);
    u32 tickOnce();
    void fn_800951D0(u32 unk);
    s32 prepareScript(const char *str, s32,
                      std::tr1::shared_ptr<CPpuEnv> *ppuEnv);
};
// static_assert(sizeof(CPpuEngine) == 0xc4)

u32 ks_doPKC_fun1(std::basic_string<char> &pkcName, s32 one,
                  std::tr1::shared_ptr<CPpuEnv> *env);
