#pragma once

#include <vector>

#include "../TypeAliases.h"

namespace PQH {
    struct PokemonMemory {
        std::vector<u16 *> scoutCounts;
    };
}
