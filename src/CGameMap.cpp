#include <CGameMap.hpp>
// extern std::tr1::shared_ptr<IDlg> FUN_800AA730(std::tr1::weak_ptr<IDlg>* arg);

//CGameMap::CGameMap(const SomeStageResource& arg) : m_mapDesc(arg.mapDesc), m_ppuEnv(arg.ppuEnv) {
//    // WIP
//}

MapDesc* CGameMap::getMapDesc() {
    return m_mapDesc;
}

BWorld* getWorld(std::tr1::shared_ptr<BWorld> world) {
    return world.get();
}

std::tr1::shared_ptr<CDividedGround> getSharedDividedGround(const std::tr1::shared_ptr<CDividedGround>* dividedGround) {
    return *dividedGround;
}

CShadowCamera* getShadowCamera(std::tr1::shared_ptr<CShadowCamera> shadowCamera) {
    return shadowCamera.get();
}

CDividedGround* getDividedGround(std::tr1::shared_ptr<CDividedGround> dividedGround) {
    return dividedGround.get();
}

bool CGameMap::tryOpenDlg(std::tr1::shared_ptr<IDlg>* sharedPtr) {
    if (!*sharedPtr) {
        return false;
    }
    std::tr1::shared_ptr<IDlg> current = m_currentDlg.lock();
    if (current == *sharedPtr) {
        return true;
    }
    if ((current) && (!current->vfunc18())) {
        return false;
    }

    current.reset();
    
    m_currentDlg = *sharedPtr;
    return true;
}

void CGameMap::resetCurrentDlg(std::tr1::shared_ptr<IDlg>* sharedPtr) {
    std::tr1::shared_ptr<IDlg> current = m_currentDlg.lock();
    if (current && current == *sharedPtr) {
        m_currentDlg.reset();
    }
}

s32 CGameMap::getBattleRoyalTimer() {
    return m_battleRoyalTimer;
}

bool CGameMap::isTimerSpeedActive() {
    return m_battleRoyalTimerSpeed;
}

void CGameMap::resetBattleRoyalTimerSpeed() {
    m_battleRoyalTimerSpeed = 0;
}

void CGameMap::addBattleRoyalTimer(s32 deltaFrames) {
    m_battleRoyalTimer += deltaFrames;

    if (deltaFrames <= 0) {
        return;
    }

    m_battleRoyalDisplay->notifyTimeAdded();
}

void CGameMap::setBattleRoyalTimer(s32 battleRoyalTimer, s32 battleRoyalTimerSpeed) {
    m_battleRoyalTimer = battleRoyalTimer;
    m_battleRoyalTimerSpeed = battleRoyalTimerSpeed;
}

void CGameMap::setMovementLockTimer(s32 lockTimer) {
    s32 *result = lockTimer < m_movementLockTimer ? &m_movementLockTimer : &lockTimer;

    m_movementLockTimer = *result;
}

void CGameMap::setHideUiFlag(bool shouldHideUI) {
    m_shouldHideUI = shouldHideUI;
}

IDlg* CGameMap::getCurrentDlg() {
    std::tr1::shared_ptr<IDlg> current(m_currentDlg.lock());
    return current.get();
}

CPostEffect* CGameMap::getPostEffect() {
    return m_postEffect.get();
}

CNumericInput* CGameMap::getNumericInput() {
    return m_numericInput.get();
}

CEnemyInfo* CGameMap::getEnemyInfo() {
    return m_enemyInfo.get();
}

CMsgBalloon* CGameMap::getMsgBalloon() {
    return m_msgBalloon.get();
}

CTutorialMsg* CGameMap::getTutorialMsg() {
    return m_tutorialMsg.get();
}

CPauseMenu* CGameMap::getPauseMenu() {
    return m_pauseMenu.get();
}

CLayoutManager* CGameMap::getLayoutManager() {
    return m_layoutManager.get();
}

CComboDisplay* CGameMap::getComboDisplay() {
    return m_comboDisplay.get();
}

CBattleRoyalDisplay* CGameMap::getBattleRoyalDisplay() {
    return m_battleRoyalDisplay.get();
}

CMoneyLifeDisplay* CGameMap::getMoneyLifeDisplay() {
    return m_moneyLifeDisplay.get();
}

CNoticeDisplay* CGameMap::getNoticeDisplay() {
    return m_noticeDisplay.get();
}

CDlgMsgWin* CGameMap::getDlgMsgWin() {
    return m_dlgMsgWin.get();
}

CDlgInfo* CGameMap::getDlgInfo() {
    return m_dlgInfo.get();
}

CDlgCollection* CGameMap::getDlgCollection() {
    return m_dlgCollection.get();
}

CDlgPiiList* CGameMap::getDlgPiiList() {
    return m_dlgPiiList.get();
}

CDlgPiiSelector* CGameMap::getDlgPiiSelector() {
    return m_dlgPiiSelector.get();
}

CMiniMap* CGameMap::getMiniMap() {
    return m_miniMap.get();
}

CWorldObjStatDisplay* CGameMap::getWorldStatDisplay() {
    return m_worldObjStatDisplay.get();
}

BWorld* CGameMap::getWorld() {
    return m_bWorld.get();
}
