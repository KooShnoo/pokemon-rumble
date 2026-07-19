#include <types.h>
#include <MSL_Common/detail/msl_smart_pointers.hpp>
#include <CPiiPersonalData.hpp>

class CPiiBox {
public:
    // dont know for sure yet, but there is definitely different kinds of boxes.
    enum BoxType {
        Unk = 0,
        PiiBox = 1,
        TeamBox = 2,
    };
    struct PiiBoxNode {
        PiiBoxNode* prev;
        PiiBoxNode* next;
        std::tr1::shared_ptr<CPiiPersonalData> ppd;
    };
public:
    BoxType m_boxType;
    u32 m_limit;
    u32 m_size;
    PiiBoxNode* m_piiBoxTail;
    PiiBoxNode* m_piiBoxHead;

    bool removePpd(std::tr1::shared_ptr<CPiiPersonalData>& ppd);
    u32 fn_800E0310(std::tr1::shared_ptr<CPiiPersonalData>& ppd);
    void healAll();
    void clearNewFlag();
};