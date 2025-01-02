#pragma once

#include "SaveCharacterPoteintialData.h"

namespace PQH {
    struct SaveCharacterData {
        u32 *exp;
        u16 *monsterNo; // dex entry
        u8 *form;
        u16 *level;
        i32 *hp;
        i32 *attak;
        char16_t *name;
        int nameLen;
        u8 *nature;
        u32 *id;
        u32 *rareRandom;
        std::shared_ptr<SaveCharacterPoteintialData> potential;
        i32 *trainingSkillCount;
        bool *isEvolve;
    };
}
