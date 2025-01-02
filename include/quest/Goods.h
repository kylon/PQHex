#pragma once

#include <unordered_map>
#include <memory>

#include "GoodsManageData.h"
#include "PlacementData.h"

namespace PQH {
    struct Goods {
        std::unordered_map<int, std::shared_ptr<GoodsManageData>> hasDatas;
        std::unordered_map<int, std::shared_ptr<PlacementData>> placementDatas;
    };
}
