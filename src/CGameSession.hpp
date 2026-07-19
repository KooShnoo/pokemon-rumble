#include <types.h>
#include <ppu/CPpuEnv.hpp>
#include <CGameStage.hpp>
#include <CPlayer.hpp>
#include <CPiiBox.hpp>
#include <CPiiCollectionBox.hpp>
#include <CPiiPersonalData.hpp>

class CRemoteMemory; 
class CBattleRoyalBox;
class CStatistic;

struct ScreenColor {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
};

struct PlayerSlot {
    std::tr1::shared_ptr<CPlayer> player;
};

struct RemoteSlot {
    std::tr1::shared_ptr<CRemoteMemory> remoteMemory;
};
    
class CGameSessionSub28 {
public:
    u32* m_unk_0x28;   // vector 
    s32 size;
    s32 capacity;
    s32 unkCounter;
    s32 trainerId;
};

class CGameSession {
public:
    virtual void vfunc_800B26B0();
    virtual void vfunc_800B9C00();
    virtual void vfunc_800BA880();
    virtual void vfunc_800BA8B0();
    virtual void vfunc_800BA8E0();
    virtual void vfunc_800B7AA0();
    virtual void vfunc_800B81E0();
    virtual void vfunc_800B81F0();
    virtual void vfunc_800B8200();
    virtual void vfunc_800B8230();
    virtual void vfunc_800B8210();
    virtual void vfunc_800B8220();
    virtual void vfunc_800B8390();
    virtual void vfunc_800B84C0();
    virtual void vfunc_800B8500();
    virtual void vfunc_800B8570();
    virtual void vfunc_800B8D80();
    virtual u32 getMoney();
    virtual void setMoney(s32 amount);
    virtual void addMoney(s32 amount);
    virtual CGameStage* getGameStage();
    virtual bool isPiiBoxFull();
    virtual CPiiBox* getPiiBox();
    virtual CPlayer* getPlayer(u32 index);
    virtual CRemoteMemory* getRemoteMemory(u32 index);
    virtual CGameSessionSub28* getGameSessSub28();
    virtual std::tr1::shared_ptr<CPpuEnv> getPpuEnv();
    virtual void setScreenColor(s32 colorMode, s32 duration);
    virtual u32 getFadeTimer();
    virtual void updatePiiCollectionBox();
    void updateScreenColor();
    virtual void vfunc_800B9B30(u32 *stageId, u32 param_3, u32 warpMode);

    char pad_0x00[0x1C];
    s32 m_money;                                        // 0x20
    s32 smthSavedMoney;                                 // 0x24
    CGameSessionSub28 m_sub28;                          // 0x28 -> 0x3C 
    std::tr1::shared_ptr<CPiiBox> m_piiBox;             // 0x3C
    PlayerSlot m_players[4];                            // 0x44 -> 0x60 
    RemoteSlot m_remoteMemory[4];                        // 0x64 -> 0x80
    std::tr1::shared_ptr<CPpuEnv> m_ppuEnv;             // 0x84     
    char pad_0x40[0x64];                                // 0x84 -> 0xF0
    std::tr1::shared_ptr<CPiiCollectionBox> m_piiCollectionBox;     // 0xF0
    std::tr1::shared_ptr<CBattleRoyalBox> m_battleRoyalBox;          // 0xF8
    std::tr1::shared_ptr<CStatistic> m_statistic;       // 0x100
    char pad_0x104[0xB40];                              // 0x104 -> 0xC48
    u32 m_returnStageId;                                // 0xC48 not sure if it is for return but found no other use
    std::tr1::shared_ptr<CGameStage> m_gameStage;       // 0xC4C
    u32 m_field_0xC54;                                    // 0xC54
    u32 m_field_0xC58;                                    // 0xC58
    ScreenColor m_screenColor;                          // 0xC5C
    ScreenColor m_screenColorTarget;                    // 0xC60
    u32 m_fadeTimer;                                    // 0xC64
};