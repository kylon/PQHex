#pragma once

#include "../include/quest/CheckData.h"
#include "../include/quest/SerializeData.h"

namespace PQH {
    class Parser final {
    private:
        std::shared_ptr<uchar[]> data;
        mutable unsigned fileOffset = 0;

        template<typename T>
        [[nodiscard]] T *pointer(const unsigned offset) const { return reinterpret_cast<T *>(data.get() + offset); }
        [[nodiscard]] unsigned incOffset(const unsigned size) const { return (fileOffset += size); }

        [[nodiscard]] std::shared_ptr<CharacterStorage> parseCharacterStorage(unsigned offset) const;
        [[nodiscard]] std::shared_ptr<ManageData> parseManageData(unsigned offset) const;
        [[nodiscard]] std::shared_ptr<SaveCharacterData> parseSaveCharacterData(unsigned offset) const;
        [[nodiscard]] std::shared_ptr<SaveCharacterPoteintialData> parseSaveCharacterPoteintialData(unsigned offset) const;
        [[nodiscard]] std::shared_ptr<SavePotentialSkillData> parseSavePotentialSkillData(unsigned offset) const;
        [[nodiscard]] std::shared_ptr<BattleData> parseBattleData(unsigned offset) const;
        [[nodiscard]] std::shared_ptr<FormationData> parseFormationData(unsigned offset) const;
        [[nodiscard]] std::shared_ptr<MemberData> parseMemberData(unsigned offset) const;
        [[nodiscard]] std::shared_ptr<PotentialStorage> parsePotentialStorage(unsigned offset) const;
        [[nodiscard]] std::shared_ptr<StoneData> parseStoneData(unsigned offset) const;
        [[nodiscard]] std::shared_ptr<PowerStone> parsePowerStone(unsigned offset, int stoneIntCount) const;
        [[nodiscard]] std::shared_ptr<PowerStoneBonus> parsePowerStoneBonus(unsigned offset) const;
        [[nodiscard]] std::shared_ptr<ConfigData> parseConfigData(unsigned offset) const;
        [[nodiscard]] std::shared_ptr<ItemStorage> parseItemStorage(unsigned offset) const;
        [[nodiscard]] std::shared_ptr<Core> parseCore(unsigned offset) const;
        [[nodiscard]] std::shared_ptr<Misc> parseMisc(unsigned offset) const;
        [[nodiscard]] std::shared_ptr<PlayerData> parsePlayerData(unsigned offset) const;
        [[nodiscard]] std::shared_ptr<Goods> parseGoods(unsigned offset) const;
        [[nodiscard]] std::shared_ptr<GoodsManageData> parseGoodsManageData(unsigned offset) const;
        [[nodiscard]] std::shared_ptr<PlacementData> parsePlacementData(unsigned offset) const;
        [[nodiscard]] std::shared_ptr<PokemonMemory> parsePokemonMemory(unsigned offset) const;

    public:
        explicit Parser(const std::shared_ptr<uchar[]> &savedata) { data = savedata; }

        [[nodiscard]] std::shared_ptr<CheckData> parseCheckData() const;
        [[nodiscard]] std::shared_ptr<SerializeData> parseSerializeData() const;
    };
}
