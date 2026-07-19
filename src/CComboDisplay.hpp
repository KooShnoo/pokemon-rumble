#include <types.h>

class CComboDisplay {
public:
    void setComboCount(u32 count);
    u32 getComboCount();
    void setComboTimer(u32 timer);
    u32 getComboTimer();

    char pad_0xF8[0xF8];
    u32 m_comboCount;
    u32 m_comboTimer;
};