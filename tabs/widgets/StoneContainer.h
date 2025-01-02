#pragma once

#include "../include/GridWidget.h"
#include "StoneWidget.h"
#include "../../include/quest/PotentialStorage.h"
#include "../../include/quest/CharacterStorage.h"

namespace PQH::UI {
    class StoneContainer: public GridWidget {
        Q_OBJECT

    private:
        QMap<int, StoneWidget *> stoneMap;
        int prevSelected = -1;

    public:
        StoneContainer();

        void setData(const std::shared_ptr<PotentialStorage> &potentialStorage, const std::shared_ptr<CharacterStorage> &characterStorage);
        void updateStoneWidgetAssignedPkm(int key, int dexNo) const;
        void unselectStone(int key) const;

    private slots:
        void onStoneSelected(int key);

    signals:
        void stoneSelected(int key);
    };
}
