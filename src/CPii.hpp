#include <types.h>
#include <BModelObj.hpp>
#include <MSL_Common/detail/msl_smart_pointers.hpp>
#include <CHPBar.hpp>
#include <CPiiPersonalData.hpp>
#include <CStageCamera.hpp>

class CPii : public BModelObj {
public:
    CPii(std::tr1::shared_ptr<CPiiPersonalData>& ppd, u32 group);
    
    std::tr1::shared_ptr<CPiiPersonalData> m_ppd; // 0xFC
    std::tr1::shared_ptr<CHPBar> m_HPBar; // 0x11C
    std::tr1::shared_ptr<CStageCamera> m_stageCamera; // 0x124
};

class CPlayerPii : public CPii {
public:
    CPlayerPii();

    u32* m_player; // 0x14C
};