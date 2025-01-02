#pragma once

#include "FormationData.h"

namespace PQH {
    struct BattleData {
        std::vector<std::shared_ptr<FormationData>> formationDatas;
    };
}
