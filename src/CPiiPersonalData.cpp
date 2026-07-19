#include <CPiiPersonalData.hpp>
#include <MSL_Common/detail/msl_smart_pointers.hpp>
#include <revolution/OS/OSTime.h>
void fn_801119B0(std::tr1::shared_ptr<s32> &);
u32 rand_fn_8019DFC0();
extern s32 gMinHP;
extern u16 lbl_804B5C48;
u16* getLocalizedName(u32 nameId, u16* param_2);

s32 calculateSexForSpecies(PiiProp &ppr, s32 sex) {
    if (ppr.isMaleOnly()) { return PiiSex::Male; }
    if (ppr.isFemaleOnly()) { return PiiSex::Female; }
    if (ppr.isUnknown()) { return PiiSex::Unknown; }

    // haha, "bang bang sex" funny
    return !!sex;
}

CPiiPersonalData::CPiiPersonalData(u32 counter, u32 trainerId, PiiProp &ppr,
                                   s32 sex) {
    m_flags = 0;
    m_unkownCounter = counter;
    m_piiProp = &ppr;
    m_sex = calculateSexForSpecies(ppr, sex);
    m_level = 0;
    m_bonusMaxHP = 0;
    m_bonusAttackPower = 0;
    m_bonusDefencePower = 0;
    m_bonusSpeed = 0;
    m_trait = 0;
    randomizeId();
    m_time = OSGetTime();
    m_trainerId = trainerId;
    fn_801119B0(m_unknown);
    m_maxHP = 1;
    m_attackPower = 1;
    m_defencePower = 1;
    m_speed = 1;
    m_battlePower = 1;
    m_cappedLevel = 0;
    m_hp = 1;
    m_damage = 0;
    m_heal = 0;
    m_price = 0;
    m_groupNo = 0;
    setNonShiny();
    m_moveIds[0] = 0;
    m_moveIds[1] = 0;
}

void CPiiPersonalData::setTrainerId(u32 trainerId) { m_trainerId = trainerId; }

u32 CPiiPersonalData::getPiiStatus() {
    if (m_hp <= 0) {
        return 1;
    }
    if (isShiny()) {
        return 3;
    }
    u32 result = 0;

    if (m_trait != 0) {
        result = 2;
    }
    return result;
}

void CPiiPersonalData::setId(u32 piiId) { m_piiId = piiId; }

void CPiiPersonalData::randomizeId() { m_piiId = rand_fn_8019DFC0(); }

bool CPiiPersonalData::isShiny() {
    u16 trainerId_high = (m_trainerId >> 16);
    u16 trainerId_low = m_trainerId & 0xFFFF;

    u16 piiId_high = (m_piiId >> 16);
    u16 piiId_low = m_piiId & 0xFFFF;

    u32 xor_result = trainerId_high ^ trainerId_low ^ piiId_high ^ piiId_low;

    return xor_result < 8;
}

void CPiiPersonalData::setShiny() {
    m_piiId = m_trainerId << 0x10 | m_trainerId >> 0x10;
}

void CPiiPersonalData::setNonShiny() {
    while (isShiny()) {
        randomizeId();
    }
}

void CPiiPersonalData::setTime(u32 time) { m_time = time; }

void CPiiPersonalData::setMoveId(u32 moveNo, u32 moveId) {
    m_moveIds[moveNo] = moveId;
}

u32 CPiiPersonalData::getMoveId(u32 moveNo) { return m_moveIds[moveNo]; }

void CPiiPersonalData::setHP(s32 new_hp) {
    if (new_hp < m_hp) {
        m_damage += new_hp - m_hp;
    } else if (m_hp < new_hp) {
        m_heal += new_hp - m_hp;
    }

    s32* hp = (m_maxHP < new_hp) ? &m_maxHP : &new_hp;
    
    hp = (gMinHP < *hp) ? hp : &gMinHP;
    
    m_hp = *hp;
}

f32 CPiiPersonalData::getHpPercent() {
    f32 hpPercent;
    
    if (m_hp == m_maxHP) {
        hpPercent = 1.0f;
    } else if (m_hp == 0) {
        hpPercent = 0.0f;
    } else {
        hpPercent = ((f32)m_hp) / ((f32)m_maxHP);
    }
    
    return hpPercent;
}

void CPiiPersonalData::resetDamage() { m_damage = 0; }

void CPiiPersonalData::resetHeal() { m_heal = 0; }

void CPiiPersonalData::fillUpHP() {
    m_hp = m_maxHP;
    resetDamage();
    resetHeal();
}

void CPiiPersonalData::setMaxHP(s32 maxHP) {
    m_maxHP = maxHP;
    resetDamage();
    resetHeal();
    // if (m_hp > maxHP) hp = maxHP;
    s32* hpResult = m_maxHP < m_hp ? &m_maxHP : &m_hp;
    m_hp = *hpResult;
}

void CPiiPersonalData::setBonusMaxHP(u32 bonusMaxHP) {
    m_bonusMaxHP = bonusMaxHP;
}

void CPiiPersonalData::setLevel(u32 level) { 
    m_level = level;
    m_cappedLevel = level;
}

void CPiiPersonalData::setCappedLevel(u32 cappedLevel) {
    m_cappedLevel = cappedLevel;
}

void CPiiPersonalData::setAttackPower(u32 attackPower) {
    m_attackPower = attackPower;
}

void CPiiPersonalData::setBonusAttackPower(u32 bonusAttackPower) {
    m_bonusAttackPower = bonusAttackPower;
}

void CPiiPersonalData::setDefencePower(u32 defencePower) {
    m_defencePower = defencePower;
}

void CPiiPersonalData::setBonusDefencePower(u32 bonusDefencePower) {
    m_bonusDefencePower = bonusDefencePower;
}

void CPiiPersonalData::setSpeed(u32 speed) { m_speed = speed; }

void CPiiPersonalData::setBonusSpeed(u32 bonusSpeed) {
    m_bonusSpeed = bonusSpeed;
}

void CPiiPersonalData::setBattlePower(u32 battlePower) { 
    m_battlePower = battlePower;
}

void CPiiPersonalData::setGroupNo(u32 groupNo) { m_groupNo = groupNo; }

void CPiiPersonalData::setTrait(u32 trait) { m_trait = trait; }

u16* CPiiPersonalData::getTraitName() {
    return getLocalizedName(m_trait + 0x6001D, &lbl_804B5C48);
}

void CPiiPersonalData::setBossFlag(bool enable) {
    if (enable) {
        BITFLAG_SET(m_flags, BOSS_FLAG);
    } else {
        BITFLAG_CLEAR(m_flags, BOSS_FLAG);
    }
}

void CPiiPersonalData::setFavoriteFlag(bool enable) {
    if (enable) {
        BITFLAG_SET(m_flags, FAVORITE_FLAG);
    } else {
        BITFLAG_CLEAR(m_flags, FAVORITE_FLAG);
    }
}

void CPiiPersonalData::setReleaseFlag(bool enable) {
    if (enable) {
        BITFLAG_SET(m_flags, RELEASE_FLAG);
    } else {
        BITFLAG_CLEAR(m_flags, RELEASE_FLAG);
    }
}

void CPiiPersonalData::setPrice(u32 price) { m_price = price; }
