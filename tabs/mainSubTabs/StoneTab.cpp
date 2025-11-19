/*
 * This file is part of PQHex.
 * Copyright (C) 2025 kylon
 *
 * PQHex is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PQHex is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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
