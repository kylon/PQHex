#pragma once

#include <QPushButton>
#include <QComboBox>

#include "../include/MainSubWidget.h"
#include "../../include/quest/BattleData.h"
#include "../../include/quest/CharacterStorage.h"

namespace PQH::UI {
    class PartyTab final: public MainSubWidget {
        Q_OBJECT

    private:
        QPushButton *saveBtn = nullptr;
        QList<QComboBox *> members;
        std::shared_ptr<CharacterStorage> characterStorageData;
        std::shared_ptr<FormationData> formationData;

        [[nodiscard]] QString makePokemonLbl(int key) const;

    public:
        PartyTab();

        void setData(const std::shared_ptr<BattleData> &battleData, const std::shared_ptr<CharacterStorage> &characterStorage);
        void updatePokemonData(int key) const;

    private slots:
        void onPartyPkmChanged(int idx) const;
        void onSaveBtnClicked();

    signals:
        void partyChanged(const QList<int> &party);
    };
}
