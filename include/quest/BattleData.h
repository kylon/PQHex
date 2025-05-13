#pragma once

#include "FormationData.h"

namespace PQH {
    struct BattleData final {
        std::vector<std::shared_ptr<FormationData>> formationDatas;
    };
}
