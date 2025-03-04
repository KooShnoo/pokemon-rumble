#include <PiiProp.hpp>

const PiiProp *PiiProp::get(u16 param_1, s32 param_2) {
    s32 idx = lookupTable[param_1] + param_2;
    return &allPii[idx];
}

u16 PiiProp::monsNo() { return m_monsNo; }
u8 PiiProp::formNo() { return m_formNo; }
u8 PiiProp::boneType() { return m_boneType; }
u8 PiiProp::flyHeight() { return m_flyHeight; }
u8 PiiProp::ASize() { return m_ASize; }
f64 PiiProp::unk0() { return m_unk0 == 100 ? 1.0f : m_unk0 * 0.01f; }
f64 PiiProp::unk() { return m_unk * 0.01f; }
u8 PiiProp::type1() { return m_type1; }
u8 PiiProp::type2() { return m_type2; }
u8 PiiProp::sexVector() { return m_sexVector; }
u8 PiiProp::unk2() { return m_unk2; }
u8 PiiProp::unk3_() {
    switch (m_sexVector) {
    case 0:
        return 0;
    case static_cast<u8>(-2):
        return 1;
    case static_cast<u8>(-1):
        return 2;
    default:
        return m_unk3 ^ 1;
    }
}
const char *PiiProp::name(u16 sex) { return m_name[sex]; }
f32 PiiProp::walkSpeedCoeff() { return m_walkSpeedCoeff; }
f32 PiiProp::walkAnmRate() { return m_walkAnmRate; }

static const u8 unknownTable[6][5] = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
                                      {0, 0, 1, 2, 3}, {0, 0, 2, 3, 4},
                                      {0, 0, 3, 4, 5}, {0, 0, 0, 0, 0}};

s32 getTypeOnTypeEfficacy(s32 attackType, s32 defenderType);
union fake {
    u8 u;
    s8 s;
};
s8 PiiProp::attackEfficacy(s32 attackType) {
    // fake t1_;
    // t1_.s = type1();
    // s8 t1 = t1_.s;
    // fake t2_;
    // t2_.s = type2();
    // s8 t2 = t2_.s;

    // u8 t1_ = m_type1;
    // s8 t1 = *(s8 *)(&t1);
    // u8 t2_ = m_type2;
    // s8 t2 = *(s8 *)(&t2);

    // s32 efficacy1;
    // if (t1 == t2) {
    //     efficacy1 = 3;
    // } else {
    //     efficacy1 = getTypeOnTypeEfficacy(attackType, t2);
    // }
    // s32 efficacy1 = t1 == t2 ? 3 : getTypeOnTypeEfficacy(attackType, t2);
    // s32 efficacy2 = getTypeOnTypeEfficacy(attackType, t1);

    s32 efficacy1 =
        m_type1 == m_type2 ? 3 : getTypeOnTypeEfficacy(attackType, m_type2);
    s32 efficacy2 = getTypeOnTypeEfficacy(attackType, m_type1);
    return unknownTable[efficacy1][efficacy2];
}

// const PiiProp PiiProp::allPii[560] = {{}};

// const u16 PiiProp::lookupTable[507] = {
// #include <pokemon_index_array.csv>
// };
