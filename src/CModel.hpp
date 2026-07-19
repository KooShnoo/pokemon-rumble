#include <types.h>
#include <MSL_Common/detail/msl_smart_pointers.hpp>

class CModel {
public:
    virtual ~CModel();

    std::tr1::shared_ptr<s32> m_scnMdl;
};