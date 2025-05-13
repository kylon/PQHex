#pragma once

#include <vector>
#include <memory>

#include "SavePotentialSkillData.h"

namespace PQH {
    struct SaveCharacterPoteintialData final {
        u16 *activeSlots;
        std::vector<i16 *> attachStoneStorageID;
        std::vector<i16 *> attachSkillStoneStorageID;
        i8 *nextActivateSlotIndex;
        float *nextSlotProgress;
        u32 *bingoPropertyIndices;
        std::vector<i8 *> slotPropertyTypes;
        std::vector<std::shared_ptr<SavePotentialSkillData>> potentialSkill;
    };
}
