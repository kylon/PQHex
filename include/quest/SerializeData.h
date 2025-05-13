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
