#include <MSL_Common/detail/msl_smart_pointers.hpp>
#include <types.h>
#include <CPiiPersonalData.hpp>

class CPlayer {
public:
    char pad_0x04[0x08];
    u32 m_playerSlot;
    char pad_0x4[0x04];
    u8 m_activeFlag;
    char pad_0xC[0x08];
    u32 m_collectedPiiCount;
    char pad3[0x08];
    std::tr1::shared_ptr<CPiiPersonalData> m_playerPii;
    std::tr1::shared_ptr<CPiiPersonalData> m_incomingPlayerPii;
};