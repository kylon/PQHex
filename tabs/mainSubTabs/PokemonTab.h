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

#include "../include/MainSubWidget.h"
#include "../widgets/PokemonContainer.h"

namespace PQH::UI {
    class PokemonTab final: public MainSubWidget {
        Q_OBJECT

    private:
        PokemonContainer *pkmContainer = nullptr;
        QPushButton *editBtn = nullptr;
        int selected = -1;

    public:
        PokemonTab();

        void setData(const std::shared_ptr<CharacterStorage> &characterStorage, const std::shared_ptr<FormationData> &formationData) const;
        void updateSelectedPokemonWidget(int dexNo, bool shiny) const;
        void unselectSelectedPokemon();
        void updatePartyPokemons(const QList<int> &party) const;

    private slots:
        void onPokemonSelected(int key, bool shiny, bool inParty);
        void onPokemonEditClicked();

    signals:
        void pokemonSelected(int key, bool shiny, bool inParty);
        void editPokemon(int key);
    };
}
