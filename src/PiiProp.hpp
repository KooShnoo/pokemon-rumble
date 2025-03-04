#include <types.h>

class PiiProp {
public:
    // clang-format off
    u16 m_monsNo    : 9;
    u8  m_formNo    : 5;
    u8  m_boneType  : 4;
    u8  m_flyHeight : 2;
    u8  m_ASize     : 3;
    u16 m_unk0      : 10;
    u8  m_unk       : 7;
    u8  m_type1     : 5;
    u8  m_type2     : 5;
    u8 m_sexVector;
    u8 m_unk2       : 1;
    u8 m_unk3       : 1;
    // clang-format on
    const char *m_name[2];
    f32 m_walkSpeedCoeff;
    f32 m_walkAnmRate;

    static const u16 lookupTable[507];
    static const PiiProp allPii[560];

public:
    u16 monsNo();
    u8 formNo();
    u8 boneType();
    u8 flyHeight();
    u8 ASize();
    f64 unk0();
    f64 unk();
    u8 type1();
    u8 type2();
    u8 sexVector();
    u8 unk2();
    u8 unk3_();
    const char *name(u16 sex);
    const char *name_male();
    const char *name_female();
    f32 walkSpeedCoeff();
    f32 walkAnmRate();

    s8 attackEfficacy(s32 attackType);

    static const PiiProp *get(u16 param_1, s32 param_2);
};
static_assert(sizeof(PiiProp) == 28);
