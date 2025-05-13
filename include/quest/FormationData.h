#pragma once

#include <vector>
#include <memory>

#include "MemberData.h"

namespace PQH {
    struct FormationData final {
        std::vector<std::shared_ptr<MemberData>> memberDatas;
    };
}
