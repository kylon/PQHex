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
#include "PokemonContainer.h"
#include "../include/Utils.h"

namespace PQH::UI {
    PokemonContainer::PokemonContainer() {
        lyt = new FlowLayout();

        setLayout(lyt);
    }

    bool PokemonContainer::isInParty(const std::shared_ptr<FormationData> &formationData, const int key) const {
        for (const std::shared_ptr<MemberData> &member: formationData->memberDatas) {
            if (*member->storageIndex == key)
                return true;
        }

        return false;
    }

    void PokemonContainer::setData(const std::shared_ptr<CharacterStorage> &characterStorage, const std::shared_ptr<FormationData> &formationData) {
        prevSelected = -1;

        if (!pokemonMap.isEmpty()) {
            while (true) {
                if (lyt->itemAt(0) == nullptr)
                    break;

                const QLayoutItem *itm = lyt->takeAt(0);

                delete itm->widget();
                delete itm;
            }

            pokemonMap.clear();
            partyList.clear();
        }

        for (const auto &[dictKey, manageData]: characterStorage->characterDataDictionary) {
            const bool shiny = isShiny(*manageData->data->id, *manageData->data->rareRandom);
            PokemonWidget *pkm = new PokemonWidget(dictKey, shiny, *manageData->data->monsterNo);

            if (isInParty(formationData, dictKey)) {
                pkm->setInParty(true);
                partyList.append(pkm);
            }

            lyt->addWidget(pkm);
            pokemonMap.insert(dictKey, pkm);

            QObject::connect(pkm, &PokemonWidget::clicked, this, &PokemonContainer::onPokemonSelected);
        }
    }

    void PokemonContainer::updatePokemonWidget(const int key, const int dexNo, const bool shiny) const {
        pokemonMap.value(key)->updateWidget(shiny, dexNo);
    }

    void PokemonContainer::unselectPokemon(const int key) const {
        pokemonMap.value(key)->setUnselected();
    }

    void PokemonContainer::updatePartyPokemons(const QList<int> &party) const {
        for (const PokemonWidget *pkm: partyList)
            pkm->setInParty(false);

        partyList.clear();

        for (const int pkmKey: party) {
            PokemonWidget *pkm = pokemonMap.value(pkmKey);

            pkm->setInParty(true);
            partyList.append(pkm);
        }
    }

    void PokemonContainer::onPokemonSelected(const int key, const bool shiny, const bool inParty) {
        if (prevSelected != -1)
            pokemonMap.value(prevSelected)->setUnselected();

        pokemonMap.value(key)->setSelected();

        prevSelected = key;
        emit pokemonSelected(key, shiny, inParty);
    }
}
