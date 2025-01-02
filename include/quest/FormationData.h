#pragma once

#include <vector>
#include <memory>

#include "MemberData.h"

namespace PQH {
    struct FormationData {
        std::vector<std::shared_ptr<MemberData>> memberDatas;
    };
}
