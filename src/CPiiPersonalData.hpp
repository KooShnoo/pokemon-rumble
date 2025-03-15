#include <MSL_Common/detail/msl_smart_pointers.hpp>
#include <PiiProp.hpp>

namespace PiiSex {
enum {
    Male = 0,
    Female = 1,
    Unknown = 2,
};
}

class CPiiPersonalData : std::tr1::enable_shared_from_this<CPiiPersonalData> {
    u32 m_flags;
    u32 m_unkownCounter;
    PiiProp *m_piiProp;
    u32 m_sex;
    /// in the code these are called `waza`
    s32 m_moveIds[2];
    u32 m_level;
    u32 m_bonusMaxHP;
    u32 m_bonusAttackPower;
    u32 m_bonusDefencePower;
    u32 m_bonusSpeed;
    /// in the code this is called a `prefix`
    u32 m_trait;
    /// in the code this is called `rand` (because it is randomly generated)
    u32 m_piiId;
    u32 m_field14_0x3c;
    u64 m_time;
    /// in the code this is called the `oyaID`
    u32 m_trainerId;
    std::tr1::shared_ptr<s32> m_unknown;
    u32 m_maxHP;
    u32 m_attackPower;
    u32 m_defencePower;
    u32 m_speed;
    u32 m_BP;
    u32 m_cappedLevel;
    s32 m_hp;
    u32 m_damage;
    u32 m_heal;
    u32 m_price;
    u32 m_groupNo;

    CPiiPersonalData(u32 counter, u32 trainerId, PiiProp &ppr, s32 sex);
    void setTrainerId(u32 trainerId);
    void setId(u32 piiId);
    void randomizeId();
    bool isShiny();
    void setShiny();
    void setNonShiny();
    void setTime(u32 time);
    void setMoveId(u32 moveNo, u32 moveId);
    u32 getMoveId(u32 moveNo);
    void setHP(u32 hp);
    // hpbar_fill_pct
    void resetDamage();
    void resetHeal();
    void fillUpHP();
    void setMaxHP(u32 maxHP);
    void setBonusMaxHP(u32 bonusMaxHP);
    void setLevel(u32 level);
    void setCappedLevel(u32 cappedLevel);
    void setAttackPower(u32 attackPower);
    void setBonusAttackPower(u32 bonusAttackPower);
    void setDefencePower(u32 defencePower);
    void setBonusDefencePower(u32 bonusDefencePower);
    void setSpeed(u32 speed);
    void setBonusSpeed(u32 bonusSpeed);
    void setBP(u32 BP);
    void setGroupNo(u32 groupNo);
    void setTrait(u32 trait);
    void setBossFlag(bool enable);
    void setPrice(u32 price);
};
static_assert(sizeof(CPiiPersonalData) == 0x80);
