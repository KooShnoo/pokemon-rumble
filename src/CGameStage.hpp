#include <MSL_Common/detail/msl_smart_pointers.hpp>
#include <types.h>
#include <CGameMap.hpp>

enum WarpModes {
    WARP_MODE_NORMAL = 1,
    WARP_MODE_RESULT_2 = 2,
    WARP_MODE_RESULT_3 = 3,
    WARP_MODE_RESULT_4 = 4,
    WARP_MODE_RESULT_5 = 5,
    WARP_MODE_RESULT_6 = 6,
    WARP_MODE_RESULT_7 = 7,
};

class CGameStage : std::tr1::enable_shared_from_this<CGameStage> {
public:
    virtual void vfunc_800BDB40();
    virtual void vfunc_800BD350();
    virtual void vfunc_800BD380();
    virtual void vfunc_800BD3B0();
    virtual void vfunc_800BD3E0();
    virtual void vfunc_800BDC50();
    virtual CGameMap* getGameMap();
    virtual u32 getLives();
    virtual void setLives(s32 lives);
    virtual void setNextStage(u32* stageIdPtr);
    virtual void setWarpMode(s32 transitionState);
    virtual void vfunc_800BD2E0();
    virtual void vfunc_800BD340();

    char pad[0x0C];
    u32 m_stageId;
    s32 m_lives;
    std::tr1::shared_ptr<CGameMap> m_gameMap;
    u32 m_warpMode;
};