#include "MSL_Common/detail/msl_smart_pointers.hpp"
#include <ppu/CPpuEngine.hpp>

// CPpuEngine::CPpuEngine() {
//     // todo
// }

void fn_8005F450() throw();

static u8 lbl_804B9060 = 0;

void CPpuEngine::runScript() throw() {
    if (this->exec_pkc_return_value == 0) {
        return;
    }

    while (1) {
        u32 tickRetVal = this->tickOnce();
        // todo: this is a compiler optimization
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

u32 CPpuEngine::execScript(const char *pkcName, s32 one,
                           std::tr1::shared_ptr<CPpuEnv> *env) {

    if (lbl_804B9060 == 0) {
        lbl_804B9060 = 1;
        fn_801738C0(1000000000);
    }

    if (this->prepareScript(pkcName, one, env) == 0) {
        return 0;
    }

    while (true) {
        this->runScript();
        s32 nextState = this->exec_pkc_return_value;
        switch (nextState) {
        case 0:
        case 1:
        case 4:
            return 0;
        case 2:
            if (one == 1) {
                fn_8019E770();
            }
            break;
        case 3:
            return 1;
        }
    }

    return 1;
}

u32 ks_doPKC_fun1(std::basic_string<char> &pkcName, s32 one,
                  std::tr1::shared_ptr<CPpuEnv> *env) {

    // CPpuEngine *engine = new CPpuEngine();
    // std::tr1::shared_ptr<CPpuEngine> pEngine(engine);
    std::tr1::shared_ptr<CPpuEngine> engine(new CPpuEngine());
    // std::tr1::shared_ptr<CPpuEngine> pEngine = engine->shared_from_this();
    // pEngine->shared = pEngine->shared_from_this();
    // engine->shared =
    // std::tr1::shared_ptr<CPpuEngine>(std::tr1::weak_ptr<CPpuEngine>(engine));
    // engine->shared =
    // std::tr1::shared_ptr<CPpuEngine>(std::tr1::weak_ptr<CPpuEngine>(engine));

    // engine->shared =
    // std::tr1::shared_ptr<CPpuEngine>(std::tr1::weak_ptr<CPpuEngine>(engine));

    return engine->execScript(pkcName.c_str(), one, env);
}
