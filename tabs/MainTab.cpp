#include "MainTab.h"

namespace PQH::UI {
    MainTab::MainTab() {
        QHBoxLayout *lyt = new QHBoxLayout();
        QTabWidget *tab = new QTabWidget();
        QFont inPartyFont;
        QFont statsFont;
        QPalette inPartyPal;

        pkmImg = new QLabel();
        statsLbl = new QLabel(pkmImg);
        statsFont = statsLbl->font();
        shinySymbol = new QLabel(pkmImg);
        partyLbl = new QLabel("In party", pkmImg);
        inPartyFont = partyLbl->font();
        inPartyPal = partyLbl->palette();
        pokemonTab = new PokemonTab();
        partyTab = new PartyTab();
        stoneTab = new StoneTab();
        ingridientsTab = new IngridientsTab();
        goodsTab = new GoodsTab();
        pokedexTab = new PokedexTab();
        miscTab = new MiscTab();
        playerTab = new PlayerTab();
        infoTab = new InfoTab();
        pokemonEditor = new PokemonEditor();
        stoneEditor = new StoneEditor();

        pkmImg->setFixedWidth(350);
        pkmImg->setAlignment(Qt::AlignCenter);
        statsFont.setBold(true);
        statsFont.setPointSize(11);
        statsLbl->setFont(statsFont);
        statsLbl->setMaximumWidth(350);
        statsLbl->move(0, 90);
        statsLbl->setVisible(false);
        shinySymbol->setAlignment(Qt::AlignCenter);
        shinySymbol->setPixmap(QPixmap(":/starnb.png"));
        shinySymbol->move(260, 120);
        shinySymbol->setVisible(false);
        inPartyFont.setItalic(true);
        inPartyFont.setBold(true);
        inPartyPal.setColor(QPalette::WindowText, Qt::red);
        partyLbl->setFont(inPartyFont);
        partyLbl->setPalette(inPartyPal);
        partyLbl->move(150, 380);
        partyLbl->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        partyLbl->setVisible(false);
        pokemonEditor->setFixedWidth(350);
        pokemonEditor->setVisible(false);
        stoneEditor->setFixedWidth(350);
        stoneEditor->setVisible(false);

        tab->addTab(pokemonTab, "Pokemon");
        tab->addTab(partyTab, "Party");
        tab->addTab(stoneTab, "Stones");
        tab->addTab(ingridientsTab, "Ingridients");
        tab->addTab(goodsTab, "Decorations");
        tab->addTab(pokedexTab, "Pokedex");
        tab->addTab(miscTab, "Misc");
        tab->addTab(playerTab, "Player");
        tab->addTab(infoTab, "Info");

        lyt->addWidget(pkmImg);
        lyt->addWidget(pokemonEditor);
        lyt->addWidget(stoneEditor);
        lyt->addWidget(tab);

        setLayout(lyt);

        QObject::connect(tab, &QTabWidget::currentChanged, this, &MainTab::onTabChanged);
        QObject::connect(pokemonTab, &PokemonTab::pokemonSelected, this, &MainTab::onPokemonSelected);
        QObject::connect(pokemonTab, &PokemonTab::editPokemon, this, &MainTab::onPokemonEdit);
        QObject::connect(pokemonEditor, &PokemonEditor::pokemonEdited, this, &MainTab::onPokemonEdited);
        QObject::connect(pokemonEditor, &PokemonEditor::coreDataChanged, this, &MainTab::onPokemonCoreDataChanged);
        QObject::connect(pokemonEditor, &PokemonEditor::updatePokedex, this, &MainTab::onPokedexUpdate);
        QObject::connect(pokemonEditor, &PokemonEditor::stoneAssigned, this, &MainTab::onStoneAssigned);
        QObject::connect(pokemonEditor, &PokemonEditor::skillStoneAssigned, this, &MainTab::onStoneAssigned);
        QObject::connect(partyTab, &PartyTab::partyChanged, this, &MainTab::onPartyChanged);
        QObject::connect(stoneTab, &StoneTab::stoneSelected, this, &MainTab::onStoneSelected);
        QObject::connect(stoneTab, &StoneTab::editStone, this, &MainTab::onStoneEdit);
        QObject::connect(ingridientsTab, &IngridientsTab::ingridientsSaved, this, &MainTab::onIngridientsSaved);
        QObject::connect(goodsTab, &GoodsTab::goodsSaved, this, &MainTab::onGoodsSaved);
        QObject::connect(playerTab, &PlayerTab::playerNameChanged, this, &MainTab::onPlayerNameChanged);
        QObject::connect(stoneEditor, &StoneEditor::stoneEdited, this, &MainTab::onStoneEdited);
    }

    void MainTab::setData(const std::shared_ptr<CheckData> &checkData, const std::shared_ptr<SerializeData> &data) {
        characterStorage = data->characterStorage;
        potentialStorage = data->potentialStorage;

        resetLeftPane();
        pokemonTab->setData(characterStorage, data->battleData->formationDatas[0]);
        partyTab->setData(data->battleData, characterStorage);
        stoneTab->setData(data->potentialStorage, characterStorage);
        ingridientsTab->setData(data->itemStorage);
        goodsTab->setData(data->goods);
        pokedexTab->setData(data->pokemonMemory);
        miscTab->setData(data);
        playerTab->setData(data->playerData);
        infoTab->setData(checkData);
    }

    void MainTab::resetLeftPane() const {
        pokemonEditor->setVisible(false);
        stoneEditor->setVisible(false);
        statsLbl->setVisible(false);
        shinySymbol->setVisible(false);
        partyLbl->setVisible(false);
        pkmImg->setPixmap(QPixmap());
        pkmImg->setVisible(true);
    }

    void MainTab::onTabChanged(const int idx) {
        const int p = prevTab;

        prevTab = idx;

        if (p != 0 && p != 2)
            return;

        resetLeftPane();

        switch (p) {
            case 0:
                pokemonTab->unselectSelectedPokemon();
                break;
            case 2:
                stoneTab->unselectSelectedStone();
                break;
            default:
                break;
        }
    }

    void MainTab::onPokemonSelected(const int key, const bool shiny, const bool inParty) const {
        const std::shared_ptr<SaveCharacterData> pkm = characterStorage->characterDataDictionary[key]->data;
        const int hp = *pkm->hp + *pkm->level;
        const int atk = *pkm->attak + *pkm->level;
        const QString stats = QString("L.%1 [HP: %2 ATK: %3]").arg(*pkm->level).arg(hp).arg(atk);

        pokemonEditor->setVisible(false);
        pkmImg->setPixmap(QPixmap(QString(":/pk%1").arg(*pkm->monsterNo)));
        pkmImg->setVisible(true);
        statsLbl->setText(stats);
        statsLbl->adjustSize();
        statsLbl->setVisible(true);
        shinySymbol->setVisible(shiny);
        partyLbl->setVisible(inParty);
    }

    void MainTab::onPokemonEdit(const int key) const {
        pkmImg->setVisible(false);
        shinySymbol->setVisible(false);
        pokemonEditor->setVisible(true);
        pokemonEditor->setPokemon(characterStorage, potentialStorage, key);
    }

    void MainTab::onPokemonEdited(const int dexNo, const bool shiny) const {
        pokemonTab->updateSelectedPokemonWidget(dexNo, shiny);
    }

    void MainTab::onPokemonCoreDataChanged(const int key) const {
        partyTab->updatePokemonData(key);
    }

    void MainTab::onPokedexUpdate(const int dexNo) const {
        pokedexTab->updateEncounters(dexNo);
    }

    void MainTab::onStoneAssigned(const int stoneKey, const int pkmKey) const {
        const int dexNo = pkmKey == -1 ? -1 : *(characterStorage->characterDataDictionary[pkmKey]->data->monsterNo);

        stoneTab->updateStoneWidgetAssignedPkm(stoneKey, dexNo);
    }

    void MainTab::onPartyChanged(const QList<int> &party) const {
        pokemonTab->updatePartyPokemons(party);
    }

    void MainTab::onStoneSelected() const {
        stoneEditor->setVisible(false);
        pkmImg->setVisible(true);
    }

    void MainTab::onStoneEdit(const int key) const {
        pkmImg->setVisible(false);
        stoneEditor->setVisible(true);
        stoneEditor->setStone(potentialStorage->potentialDatas[key]->stoneData, key);
    }

    void MainTab::onIngridientsSaved(const QList<int> &counts) {
        emit ingridientsSaved(counts);
    }

    void MainTab::onPlayerNameChanged(const QString &name) {
        emit playerNameChanged(name);
    }

    void MainTab::onStoneEdited(const int key) {
        emit stoneEdited(key);
    }

    void MainTab::onGoodsSaved() {
        emit goodsSaved();
    }
}
