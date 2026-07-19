#include <CPiiCollectionBox.hpp>
extern s32 gMaxDefeated;

void CPiiCollectionBox::setCollectionType(u32 dexNo, u32 formNo, s32 collectionState, bool isShiny) {
    PiiCollectionEntries* entry = &m_entries[dexNo];

    if (entry->m_collectionType < collectionState) {
        entry->m_collectionType = collectionState;
    }

    if (collectionState == 3) {
        if (isShiny) {
            entry->m_collectedShiny |= 1 << (formNo >> 0x1f) - (formNo << 27);
        } else {
            entry->m_collectedNormal |= 1 << (formNo >> 0x1f) - (formNo << 27);
        }
    }
    if (collectionState == 2) {
        s32 newDefeatCount = entry->m_defeatCount + 1;
        s32* tmp = &newDefeatCount;
        
        if (9999999 < newDefeatCount) {
            tmp = &gMaxDefeated;
        }

        entry->m_defeatCount = *tmp;
    }
}

s32 CPiiCollectionBox::getCollectionType(u32 dexNo) {
    return m_entries[dexNo].m_collectionType;
}

CPiiCollectionBox::PiiCollectionEntries* CPiiCollectionBox::getPiiCollectionEntries(u32 dexNo) {
    return &m_entries[dexNo];
}

s32 CPiiCollectionBox::getCollectedNormal(u32 dexNo) {
    return m_entries[dexNo].m_collectedNormal;
}

s32 CPiiCollectionBox::getCollectedShiny(u32 dexNo) {
    return m_entries[dexNo].m_collectedShiny;
}

void CPiiCollectionBox::setCollectionBRR(u32 dexNo, s32 mode, s32 brRank) {
    s32* rank = &m_entries[dexNo].m_normalRank + mode;

    if (*rank >= brRank) {
        return;
    }

    *rank = brRank;
}

s32 CPiiCollectionBox::getCollectionBRR(u32 dexNo, s32 mode) {
    s32* rank = &m_entries[dexNo].m_normalRank + mode;
    return *rank;
}

s32 CPiiCollectionBox::getDefeatCount(u32 dexNo) {
    return m_entries[dexNo].m_defeatCount;
}