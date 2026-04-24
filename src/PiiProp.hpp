#pragma once

#include <types.h>

class PiiProp {
public:
    struct Sex {
        enum {
            MaleOnly = 0,
            FemaleOnly = static_cast<u8>(-2),
            Unknown = static_cast<u8>(-1),
        };
    };

    /// some data is stored in bitfields for compact storage. c/cpp bitfields
    /// are convenient, but they are mostly implementation-defined. so, we allow
    /// access as 3 uints for more reliabile, consistent behavior.
    union {
        struct {
            // clang-format off
            u16 monsNo    : 9  ;
            u8  formNo    : 5  ;
            /// What type of movement animation
            u8  boneType  : 4  ;
            u8  flyHeight : 2  ;
            /// Evolution stage
            u8  ASize     : 3  ;
            u16 unk1      : 10 ;
            u8  unk2      : 7  ;
            u8  type1     : 5  ;
            u8  type2     : 5  ;
            /// Distribution M/F
            u8  sexVector : 8  ;
            u8  unk3      : 1  ;
            u8  unk4      : 1  ;
            // clang-format on
        };
        u32 data[3];
    } m_bitf;
    const char *m_modelName[2];
    f32 m_walkSpeedCoeff;
    f32 m_walkAnmRate;

    /// gives the appropriate index into @ref PiiProp::allPiiProperties by
    /// pokedex number
    static const u16 pprNo[507];
    static const PiiProp allPiiProperties[560];

public:
    u16 monsNo() const;
    u8 formNo() const;
    u8 boneType() const;
    u8 flyHeight() const;
    u8 ASize() const;
    f64 unk1() const;
    f64 unk2() const;
    u8 type1() const;
    u8 type2() const;
    u8 sexVector() const;

    bool isMaleOnly() const { return sexVector() == PiiProp::Sex::MaleOnly; }
    bool isFemaleOnly() const {
        return sexVector() == PiiProp::Sex::FemaleOnly;
    }
    bool isUnknown() const { return sexVector() == PiiProp::Sex::Unknown; }

    u8 unk3() const;
    u8 unk4() const;
    const char *modelName(u16 sex) const;
    // const char *name_male() const;
    // const char *name_female() const;
    f32 walkSpeedCoeff() const;
    f32 walkAnmRate() const;

    s8 attackEfficacy(s32 attackType) const;

    static const PiiProp *get(u16 dex_number, s32 form_number);
};
static_assert(sizeof(PiiProp) == 0x1c);

bool isMonsNoValid(u16 monsNo);
bool isFormValidForMon(u16 monsNo, u16 formNo);
