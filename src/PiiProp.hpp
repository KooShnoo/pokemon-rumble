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
        u32 data[3];
        struct {
            // clang-format off
            u16 monsNo    : 9  ;
            u8  formNo    : 5  ;
            u8  boneType  : 4  ;
            u8  flyHeight : 2  ;
            u8  ASize     : 3  ;
            u16 unk1      : 10 ;
            u8  unk2      : 7  ;
            u8  type1     : 5  ;
            u8  type2     : 5  ;
            u8  sexVector : 8  ;
            u8  unk3      : 1  ;
            u8  unk4      : 1  ;
            // clang-format on
        };
    } m_bitf;
    const char *m_modelName[2];
    f32 m_walkSpeedCoeff;
    f32 m_walkAnmRate;

    /// gives the appropriate index into @ref PiiProp::allPiiProperties by
    /// pokedex number
    static const u16 pprNo[507];
    static const PiiProp allPiiProperties[560];

public:
    u16 monsNo();
    u8 formNo();
    u8 boneType();
    u8 flyHeight();
    u8 ASize();
    f64 unk1();
    f64 unk2();
    u8 type1();
    u8 type2();
    u8 sexVector();

    bool isMaleOnly() { return sexVector() == PiiProp::Sex::MaleOnly; }
    bool isFemaleOnly() { return sexVector() == PiiProp::Sex::FemaleOnly; }
    bool isUnknown() { return sexVector() == PiiProp::Sex::Unknown; }

    u8 unk3();
    u8 unk4();
    const char *modelName(u16 sex);
    const char *name_male();
    const char *name_female();
    f32 walkSpeedCoeff();
    f32 walkAnmRate();

    s8 attackEfficacy(s32 attackType);

    static const PiiProp *get(u16 param_1, s32 param_2);
};
static_assert(sizeof(PiiProp) == 0x1c);
