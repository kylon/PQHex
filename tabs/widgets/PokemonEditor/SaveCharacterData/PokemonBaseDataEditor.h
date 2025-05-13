#pragma once

#include <QSpinBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>

#include "../../../../include/quest/SaveCharacterData.h"
#include "../../../include/Utils.h"

namespace PQH::UI {
    class PokemonBaseDataEditor final: public QWidget {
        Q_OBJECT

    private:
        QComboBox *pokemon = nullptr;
        QLineEdit *exp = nullptr;
        QSpinBox *level = nullptr;
        QSpinBox *hp = nullptr;
        QSpinBox *attack = nullptr;
        QLineEdit *name = nullptr;
        QComboBox *nature = nullptr;
        QLineEdit *id = nullptr;
        QLineEdit *rareRandom = nullptr;
        QSpinBox *trainingSkillCount = nullptr;
        QCheckBox *isEvolve = nullptr;
        QCheckBox *shiny = nullptr;
        std::shared_ptr<SaveCharacterData> pokemonData;
        int maxNature = 0;
        int prevLevel;
        int pkey;

        void setShinyStatus(bool makeShiny) const;
        [[nodiscard]] bool isCoreDataModified() const;

    public:
        PokemonBaseDataEditor();

        [[nodiscard]] int getMonsterNo() const { return *pokemonData->monsterNo; }
        [[nodiscard]] bool getShinyStatus() const { return isShiny(*pokemonData->id, *pokemonData->rareRandom); }

        void setPokemon(const std::shared_ptr<SaveCharacterData> &data, int key);
        void refresh() const;
        void apply();

    private slots:
        void onPokemonChanged(int idx);
        void onLevelChanged(int v);
        void onIDChanged(const QString &tx) const;
        void onRareChanged(const QString &tx) const;

    signals:
        void pokemonChanged(int dexNo);
        void coreDataChanged(int key);
        void pokemonMaxLevel();
        void updatePokedex(int dexNo);
    };
}
