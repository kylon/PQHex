#pragma once

#include <QPushButton>

#include "../include/MainSubWidget.h"
#include "../widgets/StoneContainer.h"

namespace PQH::UI {
    class StoneTab final: public MainSubWidget {
        Q_OBJECT

    private:
        StoneContainer *stoneContainer = nullptr;
        QPushButton *editBtn = nullptr;
        int selected = -1;

    public:
        StoneTab();

        void setData(const std::shared_ptr<PotentialStorage> &potentialStorage, const std::shared_ptr<CharacterStorage> &characterStorage) const;
        void updateStoneWidgetAssignedPkm(int key, int dexNo) const;
        void unselectSelectedStone();

    private slots:
        void onStoneSelected(int key);
        void onStoneEditClicked();

    signals:
        void stoneSelected();
        void editStone(int key);
    };
}
