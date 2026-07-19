#include <BModelObj.hpp>

BModelObj::BModelObj(u32 group) : BWorldObj(group | 0x20), BSoundSource() {
    m_unknownStruct.m_field112_0x64 = &m_unknownStruct;
    m_unknownStruct.m_field112_0x68 = &m_unknownStruct;
    m_field112_0x6C = 0;
    m_updateFlag = 0;
    m_model = 0;
    m_field112_0x78 = 0;
    m_collisionScale.x = 1.f;
    m_collisionScale.y = 1.f;
    m_collisionScale.z = 1.f;
    m_hitBoxScale.x = 0.f;
    m_hitBoxScale.y = 0.f;
    m_hitBoxScale.z = 0.f;
    m_hitBoxPos.x = 0.f;
    m_hitBoxPos.y = 0.f;
    m_hitBoxPos.z = 0.f;
    m_field112_0xE8 = 1;
    m_field112_0xEC = 0;
    m_field112_0xF0 = 0;
    m_field112_0xF4 = &m_field112_0xF0;
}

nw4r::math::VEC3 BModelObj::getHitboxScale() {
    return m_hitBoxScale;
}

u32* BModelObj::get0xEC() {
    return &m_field112_0xEC;
}

// placed here because its a vfunc from BWorldObj in the range of BModelObj?
void BWorldObj::vfunc_80057CC0() {}

void BWorldObj::vfunc_80057CD0() {}

u32 BWorldObj::vfunc_80057CE0() {return 0;}

u32 BWorldObj::vfunc_80057CF0() {return 0;}

nw4r::math::VEC3 BWorldObj::getPosition() {
    return m_position;
}

void BModelObj::setAngle(f32 angle) {
    m_angle = angle;
    m_updateFlag = m_updateFlag | 1;
}
