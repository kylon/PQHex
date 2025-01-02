#pragma once

#include <QTabWidget>

#include "mainSubTabs/PokemonTab.h"
#include "mainSubTabs/PartyTab.h"
#include "mainSubTabs/StoneTab.h"
#include "mainSubTabs/IngridientsTab.h"
#include "mainSubTabs/GoodsTab.h"
#include "mainSubTabs/PokedexTab.h"
#include "mainSubTabs/MiscTab.h"
#include "mainSubTabs/PlayerTab.h"
#include "mainSubTabs/InfoTab.h"
#include "widgets/PokemonEditor/PokemonEditor.h"
#include "widgets/StoneEditor/StoneEditor.h"

namespace PQH::UI {
    class MainTab: public QWidget {
        Q_OBJECT

    private:
        QLabel *pkmImg = nullptr;
        QLabel *statsLbl = nullptr;
        QLabel *shinySymbol = nullptr;
        QLabel *partyLbl = nullptr;
        PokemonTab *pokemonTab = nullptr;
        PartyTab *partyTab = nullptr;
        StoneTab *stoneTab = nullptr;
        IngridientsTab *ingridientsTab = nullptr;
        GoodsTab *goodsTab = nullptr;
        PokedexTab *pokedexTab = nullptr;
        MiscTab *miscTab = nullptr;
        PlayerTab *playerTab = nullptr;
        InfoTab *infoTab = nullptr;
        PokemonEditor *pokemonEditor = nullptr;
        StoneEditor *stoneEditor = nullptr;
        std::shared_ptr<CharacterStorage> characterStorage;
        std::shared_ptr<PotentialStorage> potentialStorage;
        int prevTab = 0;

        void resetLeftPane() const;

    public:
        MainTab();

        void setData(const std::shared_ptr<CheckData> &checkData, const std::shared_ptr<SerializeData> &data);

    private slots:
        void onTabChanged(int idx);
        void onPokemonSelected(int key, bool shiny, bool inParty) const;
        void onPokemonEdit(int key) const;
        void onPokemonEdited(int dexNo, bool shiny) const;
        void onPokemonCoreDataChanged(int key) const;
        void onPokedexUpdate(int dexNo) const;
        void onStoneAssigned(int stoneKey, int pkmKey) const;
        void onPartyChanged(const QList<int> &party) const;
        void onStoneSelected() const;
        void onStoneEdit(int key) const;
        void onIngridientsSaved(const QList<int> &counts);
        void onPlayerNameChanged(const QString &name);
        void onStoneEdited(int key);
        void onGoodsSaved();

    signals:
        void ingridientsSaved(const QList<int> &counts);
        void playerNameChanged(const QString &name);
        void stoneEdited(int key);
        void goodsSaved();
    };
}
