#pragma once

#include <unordered_map>

#include "StoneData.h"

namespace PQH {
    struct PotentialStorage final {
        std::unordered_map<int, std::shared_ptr<StoneData>> potentialDatas;
        i32 *dataCapacity;
    };
}
