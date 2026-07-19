#include <types.h>
#include <MSL_Common/detail/msl_smart_pointers.hpp>

class BSoundSource {
public:
    u32 m_field0x0;
    u32 m_field0x4;
    u32 m_field0x8;
    char pad0xC[0xC];

    virtual ~BSoundSource();

    BSoundSource();
};

/*
BSoundSource::BSoundSource() {
    m_field0x0 = 0;
    m_field0x4 = 0;
    m_field0x8 = 0;
}
*/