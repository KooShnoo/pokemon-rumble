#include "CGameStage.hpp"

CGameMap* CGameStage::getGameMap() {
    return m_gameMap.get();
}

u32 CGameStage::getLives() {
    return m_lives;
}

void CGameStage::setLives(s32 lives) {
    s32 values[3];
    values[0] = 3;
    values[1] = 0;
    values[2] = lives;

    s32* result = &values[1]; 
    if (lives > 0) {
        result = &values[2];
    }
    if (*result > 3) {
        result = &values[0];
    }
  
    m_lives = *result;
}

void CGameStage::setNextStage(u32* stageIdPtr) {
    m_warpMode = WARP_MODE_NORMAL;
    m_stageId = *stageIdPtr;
}

void CGameStage::setWarpMode(s32 warpMode) {
    switch (warpMode) {
        default:
        m_warpMode = 3;
        break;
      case 1:
          m_warpMode = 5;
          break;
      case 2:
          m_warpMode = 6;
          break;
      case 3:
          m_warpMode = 7;
          break;
      case 4: 
          m_warpMode = 4;
          break;
    }
}