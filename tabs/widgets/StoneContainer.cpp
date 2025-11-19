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
#include "StoneContainer.h"

namespace PQH::UI {
    StoneContainer::StoneContainer() {
        lyt = new FlowLayout();

        setLayout(lyt);
    }

    void StoneContainer::setData(const std::shared_ptr<PotentialStorage> &potentialStorage, const std::shared_ptr<CharacterStorage> &characterStorage) {
        prevSelected = -1;

        if (!stoneMap.isEmpty()) {
            while (true) {
                if (lyt->itemAt(0) == nullptr)
                    break;

                const QLayoutItem *itm = lyt->takeAt(0);

                delete itm->widget();
                delete itm;
            }

            stoneMap.clear();
        }

        for (const auto &[dictKey, stoneData]: potentialStorage->potentialDatas) {
            const int pkmNo = *stoneData->characterStorageIndex != -1 ? *(characterStorage->characterDataDictionary[*stoneData->characterStorageIndex]->data->monsterNo) : -1;
            StoneWidget *stone = new StoneWidget(dictKey, stoneData->stoneData->type, stoneData->stoneData->rarity, stoneData->stoneData->value, pkmNo);

            lyt->addWidget(stone);
            stoneMap.insert(dictKey, stone);

            QObject::connect(stone, &StoneWidget::clicked, this, &StoneContainer::onStoneSelected);
        }
    }

    void StoneContainer::updateStoneWidgetAssignedPkm(const int key, const int dexNo) const {
        stoneMap.value(key)->updateAssignedPkm(dexNo);
    }

    void StoneContainer::unselectStone(const int key) const {
        stoneMap.value(key)->setUnselected();
    }

    void StoneContainer::onStoneSelected(const int key) {
        if (prevSelected != -1)
            stoneMap.value(prevSelected)->setUnselected();

        stoneMap.value(key)->setSelected();

        prevSelected = key;
        emit stoneSelected(key);
    }
}
