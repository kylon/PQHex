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

#include <QPushButton>

#include "../../include/MainSubWidget.h"
#include "SaveCharacterData/PokemonBaseDataEditor.h"
#include "SaveCharacterData/CharacterPotentialData/PokemonCharacterPotentialEditor.h"

namespace PQH::UI {
    class PokemonEditor final: public MainSubWidget {
        Q_OBJECT

    private:
        PokemonBaseDataEditor *baseDataEditor = nullptr;
        PokemonCharacterPotentialEditor *characterPotentialEditor = nullptr;
        QPushButton *saveBtn = nullptr;

        void refreshEditor() const;

    public:
        PokemonEditor();

        void setPokemon(const std::shared_ptr<CharacterStorage> &characterStorage, const std::shared_ptr<PotentialStorage> &potentialStorage, int key) const;

    private slots:
        void onSaveBtnClicked();
        void onCoreDataChanged(int key);
        void onPokemonChanged(int dexNo) const;
        void onPokemonMaxLevel() const;
        void onPokedexUpdate(int dexNo);
        void onStoneAssigned(int stoneKey, int pkmKey);
        void onSkillStoneAssigned(int stoneKey, int pkmKey);

    signals:
        void pokemonEdited(int dexNo, bool shiny);
        void coreDataChanged(int key);
        void updatePokedex(int dexNo);
        void stoneAssigned(int stoneKey, int pkmKey);
        void skillStoneAssigned(int stoneKey, int pkmKey);
    };
}
