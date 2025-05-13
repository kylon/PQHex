#pragma once

#include <vector>
#include <memory>

#include "Core.h"

namespace PQH {
    struct ItemStorage final {
        std::vector<std::shared_ptr<Core>> datas;
    };
}
