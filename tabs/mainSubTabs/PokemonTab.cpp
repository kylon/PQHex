#include "PokemonTab.h"

namespace PQH::UI {
    PokemonTab::PokemonTab() {
        pkmContainer = new PokemonContainer();
        editBtn = new QPushButton("Edit");

        editBtn->setEnabled(false);

        scrollLyt->addWidget(pkmContainer);
        lyt->addWidget(editBtn);

        QObject::connect(pkmContainer, &PokemonContainer::pokemonSelected, this, &PokemonTab::onPokemonSelected);
        QObject::connect(editBtn, &QPushButton::clicked, this, &PokemonTab::onPokemonEditClicked);
    }

    void PokemonTab::setData(const std::shared_ptr<CharacterStorage> &characterStorage, const std::shared_ptr<FormationData> &formationData) const {
        resetScroolbar();
        pkmContainer->setData(characterStorage, formationData);
        editBtn->setEnabled(false);
    }

    void PokemonTab::updateSelectedPokemonWidget(const int dexNo, const bool shiny) const {
        pkmContainer->updatePokemonWidget(selected, dexNo, shiny);
    }

    void PokemonTab::unselectSelectedPokemon() {
        if (selected == -1)
            return;

        pkmContainer->unselectPokemon(selected);
        editBtn->setEnabled(false);
        selected = -1;
    }

    void PokemonTab::updatePartyPokemons(const QList<int> &party) const {
        pkmContainer->updatePartyPokemons(party);
    }

    void PokemonTab::onPokemonSelected(const int key, const bool shiny, const bool inParty) {
        selected = key;

        editBtn->setEnabled(true);
        emit pokemonSelected(key, shiny, inParty);
    }

    void PokemonTab::onPokemonEditClicked() {
        if (selected == -1)
            return;

        emit editPokemon(selected);
    }
}
