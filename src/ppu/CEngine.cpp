#include <MSL_Common/null_def.h>
#include <cstdlib>
#include <cstring>
#include <map>
#include <ppu/CEngine.hpp>
#include <utility>

static std::map<s32, CPpuCode *> *g_UnkMap1 = nullptr;
static std::map<s32, CPpuCode *> *g_UnkMap2 = nullptr;
static std::map<s32, CPpuCode *> *g_UnkMap3 = nullptr;

// TODO: figure out what these structs are
// I think one of these is a "stack value"
#define SIZEOF_STRUCT_1 8
#define SIZEOF_STRUCT_2 16
#define SIZEOF_STRUCT_3 4
namespace NPpu {

s32 CEngine::engine_id_counter = 1;

void CEngine::setupMemory(CPpuCode &ppuCode, CPpuEnv &ppuEnv, s32 size1,
                          s32 size2, s32 size3) {
    if (!g_UnkMap1) { g_UnkMap1 = new std::map<s32, CPpuCode *>; }
    if (!g_UnkMap2) { g_UnkMap2 = new std::map<s32, CPpuCode *>; }
    if (!g_UnkMap3) { g_UnkMap3 = new std::map<s32, CPpuCode *>; }

    g_UnkMap3->insert(std::make_pair(this->engineId, this->ppuCode));

    this->ppuCode->CPpuCode_vfunc_80105250();
    this->ppuCode = &ppuCode;
    this->ppuEnv = &ppuEnv;
    this->ppuEnv->CPpuEnv_vfunc_shared_ptr_801054D0();
    this->size1 = size1;
    this->size2 = size2;
    this->size3 = size3;

    // my guess is that the sizeX vars give a count of structure instances, and
    // these constants come from sizeof.
    /* clang-format off */
    void *memory = malloc(
            SIZEOF_STRUCT_1 * this->ppuCode->unk0
             + SIZEOF_STRUCT_2 * size1
             + SIZEOF_STRUCT_3 * size2
             + SIZEOF_STRUCT_3 * size3 * 3
    );
    /* clang-format on */

    // u32 *pMem = static_cast<u32 *>(memory);
    void *pMem = (memory);
    this->unknown_pointer1 = pMem;
    this->unknown_pointer5 = pMem;
    pMem = static_cast<u32 *>(pMem) + size3 * 3;
    this->unknown_pointer4 = pMem;
    pMem = static_cast<u32 *>(pMem) + size2;
    this->unknown_pointer3 = pMem;
    pMem = static_cast<u32 *>(pMem) + size1;
    this->unknown_pointer2 = pMem;
    pMem = static_cast<u32 *>(pMem) + size1 * 3;
    this->stack_base = static_cast<StackValue *>(pMem);

    this->exec_pkc_return_value = 1;
    this->program_counter = 0;
    this->stack_pointer = 0;

    memset(this->stack_base, 0, this->ppuCode->unk0 << 3);
    this->unknown_counter1 = 0;
    this->unknown_counter2 = 0;
    memset(this->unknown_pointer3, 0, this->size1 << 2);
    memset(this->unknown_pointer4, 0, this->size2 << 2);
    this->unknown_counter3 = 0;
    // this->_58 = 0;
}

void CEngine::setEngineId(s32 id) { engine_id_counter = id; }

} // namespace NPpu
