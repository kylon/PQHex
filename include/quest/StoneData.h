#pragma once

#include "PowerStone.h"

namespace PQH {
    struct StoneData {
        unsigned offset;
        i32 dictKey;
        std::shared_ptr<PowerStone> stoneData;
        i32 *characterStorageIndex;
        bool *isNew;
        u64 *timeTicks;
    };
}
