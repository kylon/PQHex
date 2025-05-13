#pragma once

#include <vector>

#include "../TypeAliases.h"

namespace PQH {
    struct PokemonMemory final {
        std::vector<u16 *> scoutCounts;
    };
}
