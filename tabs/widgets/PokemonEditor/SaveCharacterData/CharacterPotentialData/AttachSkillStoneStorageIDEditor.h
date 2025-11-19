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

#include <QComboBox>
#include <QVBoxLayout>

#include "../../../../../include/quest/CharacterStorage.h"
#include "../../../../../include/quest/SaveCharacterPoteintialData.h"
#include "../../../../../include/quest/PotentialStorage.h"

namespace PQH::UI {
    class AttachSkillStoneStorageIDEditor final: public QWidget {
        Q_OBJECT

    private:
        QVBoxLayout *skillStoneLyt = nullptr;
        QList<QComboBox *> attachSkillStoneStorageIDList;
        std::shared_ptr<SaveCharacterPoteintialData> potentialData;
        std::shared_ptr<PotentialStorage> potentialStorage;
        std::shared_ptr<CharacterStorage> characterStorage;
        int pkmKey;

        void updateStoneCombos() const;
        [[nodiscard]] QString getStoneName(int type) const;
        [[nodiscard]] QString getStoneLabel(const std::shared_ptr<StoneData> &stone) const;
        void updateStoneLabel(int key) const;
        void removeStoneFromSlot(int pkey, int stoneKey) const;

    public:
        AttachSkillStoneStorageIDEditor();

        void setData(const std::shared_ptr<CharacterStorage> &characterStorageData, const std::shared_ptr<PotentialStorage> &potentialStorageData, int pkey);
        void refresh() const;
        void apply();

    signals:
        void skillStoneAssigned(int stoneKey, int pkmKey);
    };
}
