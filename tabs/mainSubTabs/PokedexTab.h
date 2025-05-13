#pragma once

#include <QSpinBox>
#include <QPushButton>

#include "../include/MainSubWidget.h"
#include "../../include/quest/PokemonMemory.h"

namespace PQH::UI {
    class PokedexTab final: public MainSubWidget {
        Q_OBJECT

    private:
        QPushButton *saveBtn = nullptr;
        QList<QSpinBox *> scoutCounts;
        std::shared_ptr<PokemonMemory> pokemonMemory;

    public:
        PokedexTab();

        void setData(const std::shared_ptr<PokemonMemory> &data);
        void updateEncounters(int dexNo) const;
        void refresh() const;

    private slots:
        void onSaveBtnClicked() const;
    };
}
