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

#include "../include/FlowLayout.h"
#include "../widgets/PokemonWidget.h"
#include "../../include/quest/CharacterStorage.h"
#include "../../include/quest/FormationData.h"

namespace PQH::UI {
    class PokemonContainer final: public QWidget {
        Q_OBJECT

    private:
        FlowLayout *lyt = nullptr;
        QMap<int, PokemonWidget *> pokemonMap;
        mutable QList<PokemonWidget *> partyList;
        int prevSelected = -1;

        [[nodiscard]] bool isInParty(const std::shared_ptr<FormationData> &formationData, int key) const;

    public:
        PokemonContainer();

        void setData(const std::shared_ptr<CharacterStorage> &characterStorage, const std::shared_ptr<FormationData> &formationData);
        void updatePokemonWidget(int key, int dexNo, bool shiny) const;
        void unselectPokemon(int key) const;
        void updatePartyPokemons(const QList<int> &party) const;

    private slots:
        void onPokemonSelected(int key, bool shiny, bool inParty);

    signals:
        void pokemonSelected(int key, bool shiny, bool inParty);
    };
}
