#pragma once

#include <vector>
#include <memory>

#include "Core.h"

namespace PQH {
    struct ItemStorage {
        std::vector<std::shared_ptr<Core>> datas;
    };
}
