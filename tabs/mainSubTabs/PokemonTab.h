#pragma once

#include <QPushButton>

#include "../include/MainSubWidget.h"
#include "../widgets/PokemonContainer.h"

namespace PQH::UI {
    class PokemonTab: public MainSubWidget {
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
