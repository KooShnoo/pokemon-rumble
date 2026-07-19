#include <types.h>
#include <nw4r/math.h>
#include <MSL_Common/detail/msl_smart_pointers.hpp>
#include <BWorld.hpp>

class BWorldObj : std::tr1::enable_shared_from_this<BWorldObj> {
public:
    virtual ~BWorldObj();
    virtual void setPosition(const nw4r::math::VEC3& pos);
    virtual void setScale(const nw4r::math::VEC3& scale);
    virtual void setAngle(f32 angle);
    virtual nw4r::math::VEC3 getPosition();
    virtual u32 vfunc_80057CF0();
    virtual u32 vfunc_80057CE0();
    virtual void vfunc_80057CD0();
    virtual void vfunc_80057CC0();
    
    BWorldObj(u32 group);

    u32 m_objectActiveFlag; // 0x0C
    u32 m_group; // 0x10
    BWorld* m_world; // 0x14 BWorld pointer
    u32 m_field0x18; // 0x18
    std::tr1::weak_ptr<BWorldObj> m_parentObj; // 0x1C
    std::tr1::shared_ptr<s32> m_unknown; // 0x24
    f32 m_angle; // 0x2C
    nw4r::math::VEC3 m_position; // 0x30
    nw4r::math::VEC3 m_scale; // 0x3C

    void setParentObj(std::tr1::weak_ptr<BWorldObj>& parentObj);
};