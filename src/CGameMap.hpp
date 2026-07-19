#include <MSL_Common/detail/msl_smart_pointers.hpp>
#include <types.h>
#include <ppu/CPpuEnv.hpp>
#include <BWorld.hpp>
class CShadowCamera;
class CDividedGround;
class CPostEffect;
class CWorldObjStatDisplay;
class CMiniMap;
class CDlgPiiSelector;
class CDlgPiiList;
class CDlgCollection;
class CDlgInfo;
class CMoneyLifeDisplay;
class CBattleRoyalDisplay {
public:
    virtual void notifyTimeAdded(); 

    // std::tr1::shared_ptr<CLayout::CMotionProgram> layout; // 0x100
    // std::tr1::shared_ptr<CLayout::CMotionProgram> layout; // 0x11C
    bool m_isTimeAdded;
};
class CComboDisplay;
class CNoticeDisplay;
class CLayoutManager;
class CDlgMsgWin;
class CPauseMenu;
class CTutorialMsg;
class CMsgBalloon;
class CEnemyInfo;
class CNumericInput;
class IDlg {
public:
    virtual u32 vfunc0();
    virtual u32 vfunc4();
    virtual u32 vfunc8();
    virtual u32 vfuncC();       
    virtual u32 vfunc10();
    virtual u32 vfunc14();
    virtual bool vfunc18();
};

struct MapDesc {
    u32 stageId; //0x0
    // shared ptr to NPpu::Slice
    // vector?
};

struct SomeStageResource {
    MapDesc* mapDesc;
    std::tr1::shared_ptr<CPpuEnv> ppuEnv;
};

class CGameMap : std::tr1::enable_shared_from_this<CGameMap> {
public:
    virtual u8 FUN_800a7f70();
    virtual MapDesc* getMapDesc();
    virtual bool tryOpenDlg(std::tr1::shared_ptr<IDlg>* sharedPtr);
    virtual void resetCurrentDlg(std::tr1::shared_ptr<IDlg>* sharedPtr);
    virtual s32 getBattleRoyalTimer();
    virtual bool isTimerSpeedActive();
    virtual void resetBattleRoyalTimerSpeed();
    virtual void addBattleRoyalTimer(s32 deltaFrames);
    virtual void setBattleRoyalTimer(s32 battleRoyalTimer, s32 battleRoyalTimerSpeed);
    virtual void setMovementLockTimer(s32 lockTimer);
    virtual void setHideUiFlag(bool shouldHideUI);
    virtual IDlg* getCurrentDlg();
    virtual CPostEffect* getPostEffect();
    virtual CNumericInput* getNumericInput();
    virtual CEnemyInfo* getEnemyInfo();
    virtual CMsgBalloon* getMsgBalloon();
    virtual CTutorialMsg* getTutorialMsg();
    virtual CPauseMenu* getPauseMenu();
    virtual CLayoutManager* getLayoutManager();
    virtual CComboDisplay* getComboDisplay();
    virtual CBattleRoyalDisplay* getBattleRoyalDisplay();
    virtual CMoneyLifeDisplay* getMoneyLifeDisplay();
    virtual CNoticeDisplay* getNoticeDisplay();
    virtual CDlgMsgWin* getDlgMsgWin();
    virtual CDlgInfo* getDlgInfo();
    virtual CDlgCollection* getDlgCollection(); 
    virtual CDlgPiiList* getDlgPiiList();
    virtual CDlgPiiSelector* getDlgPiiSelector();
    virtual CMiniMap* getMiniMap();
    virtual CWorldObjStatDisplay* getWorldStatDisplay();
    virtual BWorld* getWorld();

    CGameMap(const SomeStageResource& arg);

    MapDesc* m_mapDesc; // 0xC
    std::tr1::shared_ptr<CPpuEnv> m_ppuEnv; // 0x10
    bool m_shouldHideUI; // ? 0x18
    std::tr1::weak_ptr<IDlg> m_currentDlg; // 0x1C
    s32 m_battleRoyalTimer; // 0x24
    s32 m_battleRoyalTimerSpeed; // 0x28
    s32 m_movementLockTimer; // ? 0x2C
    char pad0x40[0x10];
    std::tr1::shared_ptr<BWorld> m_bWorld; // 0x40
    std::tr1::shared_ptr<CPostEffect> m_postEffect; // 0x48
    std::tr1::shared_ptr<CWorldObjStatDisplay> m_worldObjStatDisplay; // 0x50
    std::tr1::shared_ptr<CMiniMap> m_miniMap; // 0x58
    std::tr1::shared_ptr<CDlgPiiSelector> m_dlgPiiSelector; // 0x60
    std::tr1::shared_ptr<CDlgPiiList> m_dlgPiiList; // 0x68
    std::tr1::shared_ptr<CDlgCollection> m_dlgCollection; // 0x70
    std::tr1::shared_ptr<CDlgInfo> m_dlgInfo; // 0x78
    std::tr1::shared_ptr<CMoneyLifeDisplay> m_moneyLifeDisplay; // 0x80
    std::tr1::shared_ptr<CBattleRoyalDisplay> m_battleRoyalDisplay; // 0x88
    std::tr1::shared_ptr<CComboDisplay> m_comboDisplay; // 0x90
    std::tr1::shared_ptr<CNoticeDisplay> m_noticeDisplay; // 0x98
    std::tr1::shared_ptr<CLayoutManager> m_layoutManager; // 0xA0
    std::tr1::shared_ptr<CDlgMsgWin> m_dlgMsgWin; // 0xA8
    std::tr1::shared_ptr<CPauseMenu> m_pauseMenu; // 0xB0
    std::tr1::shared_ptr<CTutorialMsg> m_tutorialMsg; // 0xB8
    std::tr1::shared_ptr<CMsgBalloon> m_msgBalloon; // 0xC0
    std::tr1::shared_ptr<CEnemyInfo> m_enemyInfo; // 0xC8
    std::tr1::shared_ptr<CNumericInput> m_numericInput; // 0xD0
}; static_assert(sizeof(CGameMap) == 0xD4);

BWorld* getWorld(std::tr1::shared_ptr<BWorld> world);
CShadowCamera* getShadowCamera(std::tr1::shared_ptr<CShadowCamera> shadowCamera);
CDividedGround* getDividedGround(std::tr1::shared_ptr<CDividedGround> dividedGround);
