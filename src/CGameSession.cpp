#include "CGameSession.hpp"
#include <MSL_Common/detail/msl_smart_pointers.hpp>
extern s32 maxMoney;
extern const double lbl_804B9EE0;
void fn_80113760(void* field_0x100, s32 arg1, s32 arg2);

void CGameSession::updatePiiCollectionBox() {
    CPiiBox* piiBox = m_piiBox.get();
    CPiiBox::PiiBoxNode* tail = (CPiiBox::PiiBoxNode*)&piiBox->m_piiBoxTail;

    for (CPiiBox::PiiBoxNode* i = piiBox->m_piiBoxHead; i != tail; i = i->next) {
        u16 dexno = i->ppd->m_piiProp->monsNo();
        u8 formno = i->ppd->m_piiProp->formNo();
        CPiiCollectionBox* piiCollectionBox = m_piiCollectionBox.get();
        bool isShiny = i->ppd->isShiny();
        piiCollectionBox->setCollectionType(dexno, formno, 3, isShiny);
    }
}

u32 CGameSession::getMoney() {
    return m_money;
}

void CGameSession::setMoney(s32 amount) {
    s32 *m_value = &amount;

    if (maxMoney < amount) {
        m_value = &maxMoney;
    }
    m_money = *m_value;
}

void CGameSession::addMoney(s32 amount) {
    s32 maxInt = 0x7fffffff;
    s32 newMoney = maxInt;
    s32 currentMoney = m_money;

    if (amount > 0) {
        s32 sum = currentMoney + amount;
      
        if (currentMoney < sum) {
            newMoney = maxInt;
        } else {
            newMoney = sum;
        }
    } else if (amount < 0) {
        s32 sum = currentMoney + amount;

        if (currentMoney > sum) {
            s32* result = &newMoney;
          
            if (sum < maxInt) {
                result = &newMoney + 1;
            }

            newMoney = *result;
        }
        else {
            newMoney = 9999999;
        }
    } else {
        newMoney = currentMoney;
    }

    setMoney(newMoney);
    if (amount > 0) {
        fn_80113760(m_statistic.get(), -0x62, amount);
    }
}

bool CGameSession::isPiiBoxFull() {
    u32 total = m_piiBox->m_size;

    for (s32 i = 0; i < 4; i++) {
        CPlayer* player = getPlayer(i);

        if (player->m_activeFlag != 0) { 
            total += player->m_collectedPiiCount;
        }
    }

    return total >= m_piiBox->m_limit;
}

CGameStage* CGameSession::getGameStage() { 
    return m_gameStage.get(); 
}

CPiiBox* CGameSession::getPiiBox() { 
    return m_piiBox.get(); 
}

CPlayer* CGameSession::getPlayer(u32 index) { 
    return m_players[index].player.get(); 
}

CRemoteMemory* CGameSession::getRemoteMemory(u32 index) { 
    return m_remoteMemory[index].remoteMemory.get(); 
}

CGameSessionSub28* CGameSession::getGameSessSub28() {
    return &m_sub28;
}

std::tr1::shared_ptr<CPpuEnv> CGameSession::getPpuEnv() {
    return m_ppuEnv;
}

void CGameSession::setScreenColor(s32 colorMode,s32 duration) {
    if (duration < 0) {
        m_fadeTimer = 0xf;
    } else {
        m_fadeTimer = duration;
    }
  
    switch (colorMode) {
        default:
            m_screenColorTarget.r = 0x0;
            m_screenColorTarget.g = 0x0;
            m_screenColorTarget.b = 0x0;
            m_screenColorTarget.a = 0x0;
            break;
        case 1:
            m_screenColorTarget.r = 0xff;
            m_screenColorTarget.g = 0xff;
            m_screenColorTarget.b = 0xff;
            m_screenColorTarget.a = 0xff;
            break;
        case 2:
            m_screenColorTarget.r = 0xff;
            m_screenColorTarget.g = 0xff;
            m_screenColorTarget.b = 0xff;
            m_screenColorTarget.a = 0xff;
            break;
    }

    if (m_fadeTimer == 0) {
        m_screenColor = m_screenColorTarget;
    } else if (m_screenColor.a == 0) {
        m_screenColor.r = m_screenColorTarget.r;
        m_screenColor.g = m_screenColorTarget.g;
        m_screenColor.b = m_screenColorTarget.b;
    }
}

u32 CGameSession::getFadeTimer() {
    return m_fadeTimer;
}
