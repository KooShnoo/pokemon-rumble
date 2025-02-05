
#include "MSL_Common/detail/msl_smart_pointers.hpp"
#include <ppu/CPpuEngine.hpp>

// CPpuEngine::CPpuEngine() {
//     // todo
// }

void fn_8005F450() throw();

static u32 lbl_804B9060 = 0;

void CPpuEngine::runScript() throw() {
    if (this->exec_pkc_return_value == 0) {
        return;
    }

    while (1) {
        u32 tickRetVal = this->tickOnce();
        // wtf???
        if ((tickRetVal < 2) && (tickRetVal - 3 < 2)) {
            break;
        }
        if (this->_74 == 0) {
            return;
        }

        this->fn_800951D0(this->_74);
        std::tr1::shared_ptr<u32> foo(&this->_74);
        s32 iVar2 = this->_74 + 0x14;
        if (iVar2 != 0) {
            fn_8005F450();
        }
    }

    return;
}

void fn_801738C0(u32);
void fn_8019E770();

s32 ks_doPKC_fun1(std::basic_string<char> &pkcName, s32 one,
                  std::tr1::shared_ptr<CPpuEnv> env) {

    std::tr1::shared_ptr<CPpuEngine> engine(new CPpuEngine());
    engine->shared = engine.get();
    if (lbl_804B9060 == 0) {
        lbl_804B9060 = 1;
        fn_801738C0(1000000000);
    }

    engine->prepareScript(&pkcName, 0, env);

    s32 ret = 1;

    if (!engine) {
        return 0;
    }

    while (true) {
        engine->runScript();
        u32 nextEngineCmd = engine->exec_pkc_return_value;

        if (nextEngineCmd == 0 || nextEngineCmd == 1 || nextEngineCmd == 4) {
            ret = 0;
            break;
        }

        if (nextEngineCmd != 2) {
            break;
        }

        if (one == 1) {
            fn_8019E770();
        }
    }

    return ret;
}
