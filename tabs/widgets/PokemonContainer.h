#pragma once

#include "../include/GridWidget.h"
#include "../widgets/PokemonWidget.h"
#include "../../include/quest/CharacterStorage.h"
#include "../../include/quest/FormationData.h"

namespace PQH::UI {
    class PokemonContainer: public GridWidget {
        Q_OBJECT

    private:
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
