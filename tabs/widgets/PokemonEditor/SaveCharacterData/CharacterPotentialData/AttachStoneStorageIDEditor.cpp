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
#include <QLabel>

#include "AttachStoneStorageIDEditor.h"
#include "../../../../include/Utils.h"

namespace PQH::UI {
    AttachStoneStorageIDEditor::AttachStoneStorageIDEditor() {
        QVBoxLayout *lyt = new QVBoxLayout();

        stoneStoreIDLyt = new QVBoxLayout();

        lyt->setContentsMargins(0, 0, 0, 0);
        lyt->addItem(new QSpacerItem(1, 8, QSizePolicy::Expanding, QSizePolicy::Fixed));
        lyt->addWidget(new QLabel("Attach stone storage ID"));
        lyt->addLayout(stoneStoreIDLyt);

        setLayout(lyt);
    }

    void AttachStoneStorageIDEditor::setData(const std::shared_ptr<CharacterStorage> &characterStorageData, const std::shared_ptr<PotentialStorage> &potentialStorageData, const int pkey) {
        potentialData = characterStorageData->characterDataDictionary[pkey]->data->potential;
        potentialStorage = potentialStorageData;
        characterStorage = characterStorageData;
        pkmKey = pkey;

        if (potentialData->attachStoneStorageID.size() == attachStoneStorageIDList.size()) {
            updateStoneCombos();
            return;
        }

        while (true) {
            QLayoutItem *itm = stoneStoreIDLyt->takeAt(0);

            if (itm == nullptr)
                break;

            delete itm->widget();
            delete itm;
        }

        attachStoneStorageIDList.clear();

        for (const i16 *ssi: potentialData->attachStoneStorageID) {
            QComboBox *combo = new QComboBox();
            QFont comboFont = combo->font();

            combo->setIconSize(QSize(42, 42));
            comboFont.setPointSize(11);
            combo->setFont(comboFont);
            stoneStoreIDLyt->addWidget(combo);
            attachStoneStorageIDList.append(combo);
        }

        updateStoneCombos();
    }

    void AttachStoneStorageIDEditor::updateStoneCombos() const {
        const std::vector<i8 *> slotTypes = characterStorage->characterDataDictionary[pkmKey]->data->potential->slotPropertyTypes;

        for (int i=0,l=attachStoneStorageIDList.size(); i<l; ++i)
            updateComboStones(i, *(slotTypes[i]));
    }

    QString AttachStoneStorageIDEditor::getStoneLabel(const std::shared_ptr<StoneData> &stone) const {
        const int assignedPkm = *stone->characterStorageIndex;
        const std::shared_ptr<ManageData> pkm = assignedPkm != -1 ? characterStorage->characterDataDictionary[assignedPkm] : nullptr;

        return QString("%1 %2 (+%3) %4").arg(stone->stoneData->value)
                .arg(stone->stoneData->type == 0 ? "ATK":"HP")
                .arg(stone->stoneData->bonuses.size())
                .arg(pkm != nullptr ? QString("[%1]").arg(QString::fromUtf16(pkm->data->name, pkm->data->nameLen).remove(u'\0')) : "");
    }

    void AttachStoneStorageIDEditor::updateStoneLabel(const int key) const {
        const QString lbl = getStoneLabel(potentialStorage->potentialDatas[key]);

        for (QComboBox *combo: attachStoneStorageIDList) {
            const int itmIdx = combo->findData(key);

            if (itmIdx != -1)
                combo->setItemText(itmIdx, lbl);
        }
    }

    void AttachStoneStorageIDEditor::removeStoneFromSlot(const int pkey, const int stoneKey) const {
        for (i16 *storageID: characterStorage->characterDataDictionary[pkey]->data->potential->attachStoneStorageID) {
            if (*storageID != stoneKey)
                continue;

            *storageID = -1;
            break;
        }
    }

    void AttachStoneStorageIDEditor::updateComboStones(const int comboIdx, const int slotType) const {
        QComboBox *combo = attachStoneStorageIDList[comboIdx];

        combo->clear();
        combo->addItem("", -1);

        for (const auto &[key, stone]: potentialStorage->potentialDatas) {
            if (stone->stoneData->type > 1 || (stone->stoneData->type == 1 && slotType == 0) || (stone->stoneData->type == 0 && slotType == 1))
                continue;

            combo->addItem(getStoneIcon(stone->stoneData->type, stone->stoneData->rarity, stone->stoneData->value), getStoneLabel(stone), stone->dictKey);
        }
    }

    void AttachStoneStorageIDEditor::refresh() const {
        for (int i=0,l=attachStoneStorageIDList.size(); i<l; ++i) {
            QComboBox *combo = attachStoneStorageIDList[i];
            const int idx = combo->findData(*(potentialData->attachStoneStorageID[i]));

            combo->setCurrentIndex(idx == -1 ? 0:idx);
        }
    }

    void AttachStoneStorageIDEditor::apply() {
        for (int i=0,l=attachStoneStorageIDList.size(); i<l; ++i) {
            const int id = attachStoneStorageIDList[i]->currentData().toInt();
            const int old = *(potentialData->attachStoneStorageID[i]);
            int oldOwner;

            if (old == id)
                continue;

            if (old != -1) { // unassign removed stone
                *(potentialStorage->potentialDatas[old]->characterStorageIndex) = -1;
                removeStoneFromSlot(pkmKey, old);
                updateStoneLabel(old);
                emit stoneAssigned(old, -1);
            }

            if (id == -1) // removed from slot, no more actions needed
                continue;

            oldOwner = *(potentialStorage->potentialDatas[id]->characterStorageIndex);
            if (oldOwner != -1) // remove new stone from previous owner
                removeStoneFromSlot(oldOwner, id);

            *(potentialData->attachStoneStorageID[i]) = id; // set stone to current pkm or unset
            *(potentialStorage->potentialDatas[id]->characterStorageIndex) = pkmKey; // assign stone to current pokemon

            updateStoneLabel(id);
            emit stoneAssigned(id, pkmKey);
        }
    }
}
