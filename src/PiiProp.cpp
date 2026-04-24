#include <PiiDex.hpp>
#include <PiiProp.hpp>

bool isMonsNoValid(u16 monsNo) { return 1 <= monsNo && monsNo <= 495; }

bool isFormValidForMon(u16 monsNo, u16 formNo) {
    if (!isMonsNoValid(monsNo)) { return false; }

    // clang-format off
    if (monsNo == UNOWN)     { return 0 <= formNo && formNo <= 27; }
    if (monsNo == CASTFORM)  { return 0 <= formNo && formNo <= 3;  }
    if (monsNo == DEOXYS)    { return 0 <= formNo && formNo <= 3;  }
    if (monsNo == BURMY)     { return 0 <= formNo && formNo <= 2;  }
    if (monsNo == WORMADAM)  { return 0 <= formNo && formNo <= 2;  }
    if (monsNo == CHERRIM)   { return 0 <= formNo && formNo <= 1;  }
    if (monsNo == SHELLOS)   { return 0 <= formNo && formNo <= 1;  }
    if (monsNo == GASTRODON) { return 0 <= formNo && formNo <= 1;  }
    if (monsNo == SHAYMIN)   { return 0 <= formNo && formNo <= 1;  }
    if (monsNo == ROTOM)     { return 0 <= formNo && formNo <= 5;  }
    if (monsNo == GIRATINA)  { return 0 <= formNo && formNo <= 1;  }
    if (monsNo == ARCEUS)    { return 0 <= formNo && formNo <= 17; }
    if (monsNo == EGG)       { return 0 <= formNo && formNo <= 1;  }
    // clang-format on

    return formNo == 0;
}

u16 getPiiPropNumberByDexNumber(u16 dex_number) {
    return PiiProp::pprNo[dex_number];
}

const PiiProp *PiiProp::get(u16 dex_number, s32 form_number) {
    s32 idx = getPiiPropNumberByDexNumber(dex_number) + form_number;
    return &allPiiProperties[idx];
}

u16 PiiProp::monsNo() const { return m_bitf.monsNo; }
u8 PiiProp::formNo() const { return m_bitf.formNo; }
u8 PiiProp::boneType() const { return m_bitf.boneType; }
u8 PiiProp::flyHeight() const { return m_bitf.flyHeight; }
u8 PiiProp::ASize() const { return m_bitf.ASize; }
f64 PiiProp::unk1() const {
    return m_bitf.unk1 == 100 ? 1.0f : m_bitf.unk1 * 0.01f;
}
f64 PiiProp::unk2() const { return m_bitf.unk2 * 0.01f; }
u8 PiiProp::type1() const { return m_bitf.type1; }
u8 PiiProp::type2() const { return m_bitf.type2; }
u8 PiiProp::sexVector() const { return m_bitf.sexVector; }
u8 PiiProp::unk3() const { return m_bitf.unk3; }
u8 PiiProp::unk4() const {
    switch (m_bitf.sexVector) {
    case PiiProp::Sex::MaleOnly:
        return 0;
    case PiiProp::Sex::FemaleOnly:
        return 1;
    case PiiProp::Sex::Unknown:
        return 2;
    default:
        return m_bitf.unk4 ^ 1;
    }
}
const char *PiiProp::modelName(u16 sex) const { return m_modelName[sex & 1]; }
f32 PiiProp::walkSpeedCoeff() const { return m_walkSpeedCoeff; }
f32 PiiProp::walkAnmRate() const { return m_walkAnmRate; }

// static const u8 unknownTable[6][5] = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
//                                       {0, 0, 1, 2, 3}, {0, 0, 2, 3, 4},
//                                       {0, 0, 3, 4, 5}, {0, 0, 0, 0, 0}};

s32 getTypeOnTypeEfficacy(s32 attackType, s32 defenderType);
u8 unknownTable[6][5];
s8 PiiProp::attackEfficacy(s32 attackType) const {
    s32 efficacy1 = m_bitf.type1 == m_bitf.type2
                        ? 3
                        : getTypeOnTypeEfficacy(attackType, m_bitf.type2);
    s32 efficacy2 = getTypeOnTypeEfficacy(attackType, m_bitf.type1);
    return unknownTable[efficacy1][efficacy2];
}

#include <PiiPropAll.cpp>
const u16 PiiProp::pprNo[507] = {
#include <pprNo.csv>
};
