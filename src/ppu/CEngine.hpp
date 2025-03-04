#pragma once

#include <ppu/CPpuCode.hpp>
#include <ppu/CPpuEnv.hpp>

namespace NPpu {

struct StackValue {
    enum EType {
        PTR = 0,
        DOUBLE = 1,
        C_STRING = 3,
        WCHAR_STR_CONST = 6,
        WCHAR_STR = 7
    };
    EType type;
    void *data;
};

class CEngine {
protected:
    s32 engineId;
    CPpuCode *ppuCode;
    CPpuEnv *ppuEnv;
    u32 size1;
    u32 size2;
    u32 size3;
    void *unknown_pointer1;
    u32 exec_pkc_return_value;
    s32 program_counter;
    s32 stack_pointer;
    StackValue *stack_base;
    u32 unknown_counter1;
    void *unknown_pointer2;
    u32 unknown_counter2;
    void *unknown_pointer3;
    void *unknown_pointer4;
    u32 unknown_counter3;
    void *unknown_pointer5;
    UNKOWN_DATA(0x44, 0x64, u32);

    static s32 engine_id_counter;

public:
    CEngine();
    void setupMemory(CPpuCode &ppuCode, CPpuEnv &ppuEnv, s32 size1, s32 size2,
                     s32 size3);

    static void setEngineId(s32 id);
};
static_assert(sizeof(CEngine) == 0x64)

} // namespace NPpu
