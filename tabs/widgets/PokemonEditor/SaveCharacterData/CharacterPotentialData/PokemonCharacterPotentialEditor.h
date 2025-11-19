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

#include <QDoubleSpinBox>

#include "ActiveSlotsEditor.h"
#include "AttachStoneStorageIDEditor.h"
#include "AttachSkillStoneStorageIDEditor.h"
#include "SlotPropertyTypesEditor.h"
#include "PotentialSkillDataEditor.h"

namespace PQH::UI {
    class PokemonCharacterPotentialEditor final: public QWidget {
        Q_OBJECT

    private:
        QSpinBox *nextActivateSlotIndex = nullptr;
        QDoubleSpinBox *nextSlotProgress = nullptr;
        QSpinBox *bingoPropertyIndices = nullptr;
        ActiveSlotsEditor *activeSlotsEditor = nullptr;
        AttachStoneStorageIDEditor *attachStoneStorageIdEditor = nullptr;
        AttachSkillStoneStorageIDEditor *attachSkillStoneStorageIdEditor = nullptr;
        SlotPropertyTypesEditor *slotPropertyTypesEditor = nullptr;
        PotentialSkillDataEditor *potentialSkillDataEditor = nullptr;
        std::shared_ptr<SaveCharacterPoteintialData> potentialData;

    public:
        PokemonCharacterPotentialEditor();

        void setPotential(const std::shared_ptr<PotentialStorage> &potentialStorage, const std::shared_ptr<CharacterStorage> &characterStorage, int key);
        void resetSlotProgress() const;
        void setPokemon(int dexNo) const;
        void refresh() const;
        void apply() const;

    private slots:
        void onSlotTypeChanged(int slotIdx, int type) const;
        void onStoneAssigned(int stoneKey, int pkmKey);
        void onSkillStoneAssigned(int stoneKey, int pkmKey);

    signals:
        void stoneAssigned(int stoneKey, int pkmKey);
        void skillStoneAssigned(int stoneKey, int pkmKey);
    };
}
