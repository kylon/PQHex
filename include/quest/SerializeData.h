/*
 * This file is part of PQHex.
 * Copyright (C) 2025 kylon
 *
 * PQHex is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PQHex is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "CharacterStorage.h"
#include "BattleData.h"
#include "PotentialStorage.h"
#include "ConfigData.h"
#include "ItemStorage.h"
#include "PokemonMemory.h"
#include "Misc.h"
#include "PlayerData.h"
#include "Goods.h"

namespace PQH {
    struct SerializeData final {
        std::shared_ptr<CharacterStorage> characterStorage;
        std::shared_ptr<BattleData> battleData;
        std::shared_ptr<PotentialStorage> potentialStorage;
        std::shared_ptr<ConfigData> configData;
        std::shared_ptr<ItemStorage> itemStorage;
        std::shared_ptr<PokemonMemory> pokemonMemory;
        std::shared_ptr<Misc> misc;
        std::shared_ptr<PlayerData> playerData;
        std::shared_ptr<Goods> goods;
    };
}
