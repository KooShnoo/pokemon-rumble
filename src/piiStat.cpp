#include <revolution/types.h>

#ifdef __clang__
#pragma clang diagnostic ignored "-Wc11-extensions"
#pragma clang diagnostic ignored "-Wc++17-extensions"
#define CHECK_SIZEOF(cls, size) _Static_assert(sizeof(cls) == size);
#else
#define CHECK_SIZEOF(cls, size)
#endif

struct Pokemon {
    u8 _unk_data[12];
    const char *name_male;
    const char *name_female;
    f32 stat1;
    f32 stat2;
};
CHECK_SIZEOF(Pokemon, 28)

const Pokemon pokemon_array[560] = {{
    /* ._unk_data = */ {
        0x00,
        0x80,
        0x50,
        0x00,
        0x19,
        0x00,
        0xc8,
        0x60,
        0x18,
        0x1f,
        0x40,
        0x00,
    },
    /* .name_male = */ "HUSIGIDANE",
    /* .name_female = */ "HUSIGIDANE",
    /* .stat1 = */ 1.0,
    /* .stat2 = */ 106.0,
}};

const u16 pokemon_index_array[507] = {
#include <pokemon_index_array.csv>
};


const Pokemon *ks_getPiiStats(u16 param_1, s32 param_2) {
    s32 idx = param_2 + pokemon_index_array[param_1];
    return &pokemon_array[idx];
}
