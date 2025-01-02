#include "StoneTab.h"

namespace PQH::UI {
    StoneTab::StoneTab() {
        stoneContainer = new StoneContainer();
        editBtn = new QPushButton("Edit");

        editBtn->setEnabled(false);

        scrollLyt->addWidget(stoneContainer);
        lyt->addWidget(editBtn);

        QObject::connect(stoneContainer, &StoneContainer::stoneSelected, this, &StoneTab::onStoneSelected);
        QObject::connect(editBtn, &QPushButton::clicked, this, &StoneTab::onStoneEditClicked);
    }

    void StoneTab::setData(const std::shared_ptr<PotentialStorage> &potentialStorage, const std::shared_ptr<CharacterStorage> &characterStorage) const {
        resetScroolbar();
        stoneContainer->setData(potentialStorage, characterStorage);
        editBtn->setEnabled(false);
    }

    void StoneTab::updateStoneWidgetAssignedPkm(const int key, const int dexNo) const {
        stoneContainer->updateStoneWidgetAssignedPkm(key, dexNo);
    }

    void StoneTab::unselectSelectedStone() {
        if (selected == -1)
            return;

        stoneContainer->unselectStone(selected);
        editBtn->setEnabled(false);
        selected = -1;
    }

    void StoneTab::onStoneSelected(const int key) {
        selected = key;

        editBtn->setEnabled(true);
        emit stoneSelected();
    }

    void StoneTab::onStoneEditClicked() {
        if (selected == -1)
            return;

        emit editStone(selected);
    }
}
