#include <types.h>
#include <vector>

class CPiiCollectionBox {
public:
    struct PiiCollectionEntries {
        s32 m_collectionType;
        s32 m_normalRank;
        s32 m_advancedRank;
        s32 m_exRank;
        s32 m_defeatCount;
        s32 m_collectedNormal;
        s32 m_collectedShiny;
    };
    static_assert(sizeof(PiiCollectionEntries) == 0x1C);

public:
    std::vector<PiiCollectionEntries> m_entries;

    void setCollectionType(u32 dexNo, u32 formNo, s32 param_4, bool isShiny);
    s32 getCollectionType(u32 dexNo);
    PiiCollectionEntries* getPiiCollectionEntries(u32 dexNo);
    s32 getCollectedNormal(u32 dexNo);
    s32 getCollectedShiny(u32 dexNo);
    void setCollectionBRR(u32 dexNo, s32 mode, s32 brRank);
    s32 getCollectionBRR(u32 dexNo, s32 mode);
    s32 getDefeatCount(u32 dexNo);
};