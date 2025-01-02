#include "StoneContainer.h"

namespace PQH::UI {
    StoneContainer::StoneContainer(): GridWidget(5) {
        gridLyt->setContentsMargins(0, 0, 0, 0);
    }

    void StoneContainer::setData(const std::shared_ptr<PotentialStorage> &potentialStorage, const std::shared_ptr<CharacterStorage> &characterStorage) {
        prevSelected = -1;

        if (!stoneMap.isEmpty()) {
            for (StoneWidget *sw: stoneMap)
                sw->deleteLater();

            stoneMap.clear();
            resetSlot();
        }

        for (const auto &[dictKey, stoneData]: potentialStorage->potentialDatas) {
            const int pkmNo = *stoneData->characterStorageIndex != -1 ? *(characterStorage->characterDataDictionary[*stoneData->characterStorageIndex]->data->monsterNo) : -1;
            StoneWidget *stone = new StoneWidget(dictKey, stoneData->stoneData->type, stoneData->stoneData->rarity, stoneData->stoneData->value, pkmNo);

            setNextSlot();
            gridLyt->addWidget(stone, row, column);
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
