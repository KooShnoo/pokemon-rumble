#include <BWorldObj.hpp>
std::tr1::shared_ptr<s32>& fn_801119B0(std::tr1::shared_ptr<s32>&);

BWorldObj::BWorldObj(u32 group) {
    const u32 grp = group | 1;
    m_group = grp;
    m_world = 0;
    m_field0x18 = 0;
    m_objectActiveFlag = 4;
    m_parentObj.swap(m_parentObj);
    fn_801119B0(m_unknown);
    m_angle = 0.f;
    m_position.x = 0.f;
    m_position.y = 0.f;
    m_position.z = 0.f;
    m_scale.x = 1.f;
    m_scale.y = 1.f;
    m_scale.z = 1.f;
}

void BWorldObj::setPosition(const nw4r::math::VEC3& pos) {
    m_position = pos;
}

void BWorldObj::setScale(const nw4r::math::VEC3& scale) {
    m_scale = scale;
}

void BWorldObj::setAngle(f32 angle) {
    m_angle = angle;
}

void BWorldObj::setParentObj(std::tr1::weak_ptr<BWorldObj>& parentObj) {
    m_parentObj = parentObj;
}