#include <types.h>
#include <BSoundSource.hpp>
#include <BWorldObj.hpp>
#include <CModel.hpp>

class BModelObj : public BWorldObj, public BSoundSource {
public:
    virtual ~BModelObj();
    virtual void vfunc_80053840();
    virtual void vfunc_80053a20();
    virtual void vfunc_800541b0();
    virtual void vfunc_800549c0();
    virtual void vfunc_80055140();
    virtual void vfunc_80055200();
    virtual void vfunc_80055980();
    virtual void vfunc_800570d0();
    virtual void vfunc_80057160();
    virtual void vfunc_80057960();
    virtual void vfunc_800579f0();
    virtual void vfunc_80057A60();
    virtual void vfunc_80057D20();
    virtual void setAngle(f32 angle);
    virtual nw4r::math::VEC3 getHitboxScale();
    virtual u32* get0xEC();

    BModelObj(u32 group);

    struct unknownStruct {
        unknownStruct* m_field112_0x64;
        unknownStruct* m_field112_0x68;
    };

    unknownStruct m_unknownStruct; // 0x64
    u32 m_field112_0x6C;
    u32 m_updateFlag; // 0x70
    CModel* m_model; // 0x74
    u32 m_field112_0x78; // 0x78
    nw4r::math::VEC3 m_collisionScale; // 0x7C
    nw4r::math::VEC3 m_hitBoxScale; // 0x88
    char pad0xAC[0x18];
    nw4r::math::VEC3 m_hitBoxPos; // 0x94
    char pad0xE8[0x30];
    u32 m_field112_0xE8; // 0xE8
    u32 m_field112_0xEC; // 0xEC
    u32 m_field112_0xF0; // 0xF0
    u32* m_field112_0xF4; // 0xF4
};
