#include <CPii.hpp>

CPii::CPii(std::tr1::shared_ptr<CPiiPersonalData>& ppd, u32 group) : BModelObj(group | 0x20) {
    m_ppd = ppd;
}
