#include "types.h"
#include <MSL_Common/detail/msl_smart_pointers.hpp>
#include <memory>

namespace NPpu {

class CCode {
  public:
    char *scriptFileName;
    u32 unk0;
    u32 unk1;
    u32 unk2;
    u32 unk3;
    void *scriptBuffer;
    u32 unk4;
    u32 unk5;
};

} // namespace NPpu

class CPpuCode : public std::tr1::enable_shared_from_this<CPpuCode>,
                 public NPpu::CCode {
  public:
    virtual void CPpuCode_vfunc_80105250();
};
