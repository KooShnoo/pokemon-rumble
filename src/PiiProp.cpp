#include <PiiProp.hpp>

u16 getPiiPropNumberByDexNumber(u16 dex_number) {
    return PiiProp::pprNo[dex_number];
}

const PiiProp *PiiProp::get(u16 dex_number, s32 form_number) {
    s32 idx = getPiiPropNumberByDexNumber(dex_number) + form_number;
    return &allPiiProperties[idx];
}

u16 PiiProp::monsNo() { return m_bitf.monsNo; }
u8 PiiProp::formNo() { return m_bitf.formNo; }
u8 PiiProp::boneType() { return m_bitf.boneType; }
u8 PiiProp::flyHeight() { return m_bitf.flyHeight; }
u8 PiiProp::ASize() { return m_bitf.ASize; }
f64 PiiProp::unk1() { return m_bitf.unk1 == 100 ? 1.0f : m_bitf.unk1 * 0.01f; }
f64 PiiProp::unk2() { return m_bitf.unk2 * 0.01f; }
u8 PiiProp::type1() { return m_bitf.type1; }
u8 PiiProp::type2() { return m_bitf.type2; }
u8 PiiProp::sexVector() { return m_bitf.sexVector; }
u8 PiiProp::unk3() { return m_bitf.unk3; }
u8 PiiProp::unk4() {
    switch (m_bitf.sexVector) {
    case 0:
        return 0;
    case static_cast<u8>(-2):
        return 1;
    case static_cast<u8>(-1):
        return 2;
    default:
        return m_bitf.unk4 ^ 1;
    }
}
const char *PiiProp::modelName(u16 sex) { return m_modelName[sex & 1]; }
f32 PiiProp::walkSpeedCoeff() { return m_walkSpeedCoeff; }
f32 PiiProp::walkAnmRate() { return m_walkAnmRate; }

// static const u8 unknownTable[6][5] = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
//                                       {0, 0, 1, 2, 3}, {0, 0, 2, 3, 4},
//                                       {0, 0, 3, 4, 5}, {0, 0, 0, 0, 0}};

s32 getTypeOnTypeEfficacy(s32 attackType, s32 defenderType);
u8 unknownTable[6][5];
s8 PiiProp::attackEfficacy(s32 attackType) {
    s32 efficacy1 = m_bitf.type1 == m_bitf.type2
                        ? 3
                        : getTypeOnTypeEfficacy(attackType, m_bitf.type2);
    s32 efficacy2 = getTypeOnTypeEfficacy(attackType, m_bitf.type1);
    return unknownTable[efficacy1][efficacy2];
}

// TODO(KooShnoo): Dump this table from ROM into human-readable JSON. Then,
// create a build step which uses the JSON to generate a cpp header declaring
// this table.
const PiiProp PiiProp::allPiiProperties[560] = {{}};

const u16 PiiProp::pprNo[507] = {
#ifndef DECOMP_IDE_FLAG
#include <pokemon_index_array.csv>
#endif
};
