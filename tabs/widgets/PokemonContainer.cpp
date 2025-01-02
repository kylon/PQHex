#include "PokemonContainer.h"
#include "../include/Utils.h"

namespace PQH::UI {
    PokemonContainer::PokemonContainer(): GridWidget(5) {
        gridLyt->setContentsMargins(0, 0, 0, 0);
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
            for (PokemonWidget *pw: pokemonMap)
                delete pw;

            pokemonMap.clear();
            partyList.clear();
            resetSlot();
        }

        for (const auto &[dictKey, manageData]: characterStorage->characterDataDictionary) {
            const bool shiny = isShiny(*manageData->data->id, *manageData->data->rareRandom);
            PokemonWidget *pkm = new PokemonWidget(dictKey, shiny, *manageData->data->monsterNo);

            if (isInParty(formationData, dictKey)) {
                pkm->setInParty(true);
                partyList.append(pkm);
            }

            setNextSlot();
            gridLyt->addWidget(pkm, row, column);
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
