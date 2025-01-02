#pragma once

#include <unordered_map>

#include "ManageData.h"

namespace PQH {
    struct CharacterStorage {
        std::unordered_map<int, std::shared_ptr<ManageData>> characterDataDictionary;
        i32 *dataCapacity;
    };
}
