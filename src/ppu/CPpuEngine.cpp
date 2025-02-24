#include <MSL_Common/detail/msl_smart_pointers.hpp>
#include <ppu/CPpuEngine.hpp>

// CPpuEngine::CPpuEngine() {
//     // todo
// }

static std::tr1::weak_ptr<CPpuEnv> gPpuEnv;

void fn_801738C0(u32);
void fn_8019E770();

void fn_8005F450() throw();

static u32 ks_g_ppu_smth = 0;
static u8 lbl_804B9060 = 0;

std::tr1::shared_ptr<CPpuCode> make_ppuCode(CPpuEnv &ppuEnv,
                                            const char *pkcName, int param_4);

bool CPpuEngine::prepareScript(const char *pkcName, s32 one,
                               std::tr1::shared_ptr<CPpuEnv> *pPpuEnv) {
    std::tr1::shared_ptr<CPpuEnv> ppuEnv = *pPpuEnv ? *pPpuEnv : gPpuEnv.lock();

    if (!ppuEnv) {
        return false;
    }

    // make_ppuCode might be a member of CPpuEnv, but this matches better.
    std::tr1::shared_ptr<CPpuCode> ppuCode =
        make_ppuCode(*ppuEnv, pkcName, one);
    // pPpuEnv->get()->make_ppuCode(pkcName, one);

    if (!ppuCode) {
        return false;
    }

    this->_90 = ks_g_ppu_smth;
    this->setupMemory(*ppuCode, *ppuEnv, 0x40, 0x20, 0x8);

    return true;
}

bool CPpuEngine::execScript(const char *pkcName, s32 one,
                            std::tr1::shared_ptr<CPpuEnv> *env) {
    if (lbl_804B9060 == 0) {
        lbl_804B9060 = 1;
        fn_801738C0(1000000000);
    }

    if (!this->prepareScript(pkcName, one, env)) {
        return false;
    }

    while (true) {
        this->runScript();
        s32 nextState = this->exec_pkc_return_value;
        switch (nextState) {
        case 0:
        case 1:
        case 4:
            return false;
        case 2:
            if (one == 1) {
                fn_8019E770();
            }
            break;
        case 3:
            return true;
        }
    }

    return true;
}

void CPpuEngine::runScript() throw() {
    if (this->exec_pkc_return_value == 0) {
        return;
    }

    while (1) {
        u32 tickRetVal = this->tickOnce();
        if (tickRetVal == 0 || tickRetVal == 1 || tickRetVal == 3 ||
            tickRetVal == 4) {
            continue;
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

u32 ks_doPKC_fun1(std::basic_string<char> &pkcName, s32 one,
                  std::tr1::shared_ptr<CPpuEnv> *env) {
    std::tr1::shared_ptr<CPpuEngine> engine(new CPpuEngine());

    // CPpuEngine *pEngine = new CPpuEngine();
    // std::detail::default_delete<CPpuEngine> dtr;
    // std::tr1::shared_ptr<CPpuEngine> engine(pEngine, dtr);
    // std::tr1::shared_ptr<CPpuEngine> engine(pEngine, std::move(dtr));
    // std::tr1::shared_ptr<CPpuEngine> engine(pEngine,
    // rvalue_ref<std::detail::default_delete<CPpuEngine> >(dtr));
    // engine.get_deleter<std::tr1::detail::shared_ptr_deleter<CPpuEngine>
    // >()->dispose(); CPpuEngine *pEngine = new CPpuEngine();
    // std::tr1::detail::shared_ptr_deleter<CPpuEngine> dtr =
    // std::tr1::detail::shared_ptr_deleter<CPpuEngine>(pEngine);
    // engine.get_deleter<std::tr1::detail::shared_ptr_deleter<CPpuEngine>
    // >()->dispose(); pEngine->shared_from_this()
    // std::tr1::shared_ptr<CPpuEngine> engine = pEngine->shared_from_this();
    // Metrowerks::move_ptr<CPpuEngine> doo(pEngine);
    // std::tr1::shared_ptr<CPpuEngine> engine(pEngine, doo);
    // std::tr1::shared_ptr<CPpuEngine> engine(pEngine,
    // std::tr1::detail::shared_ptr_deleter<CPpuEngine> (pEngine));
    // std::tr1::shared_ptr<CPpuEngine> engine(pEngine, std::move(
    //     std::tr1::detail::shared_ptr_deleter<CPpuEngine>(pEngine)
    // ));
    // std::tr1::shared_ptr<CPpuEngine> engine(pEngine);
    // std::tr1::shared_ptr<CPpuEngine> engine = (new
    // CPpuEngine())->shared_from_this(); auto f
    // =dynamic_cast<std::detail::default_delete<CPpuEngine>*>(engine.get_deleter<std::detail::default_delete<CPpuEngine>
    // >()); f->del std::tr1::shared_ptr<CPpuEngine> engine(new CPpuEngine(),
    // std::detail::default_delete<CPpuEngine>());
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
