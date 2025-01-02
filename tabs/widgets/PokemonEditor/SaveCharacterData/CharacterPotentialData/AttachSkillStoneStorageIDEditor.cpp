#include <QLabel>

#include "AttachSkillStoneStorageIDEditor.h"
#include "../../../../include/Utils.h"

namespace PQH::UI {
    AttachSkillStoneStorageIDEditor::AttachSkillStoneStorageIDEditor() {
        QVBoxLayout *lyt = new QVBoxLayout();

        skillStoneLyt = new QVBoxLayout();

        lyt->setContentsMargins(0, 0, 0, 0);
        lyt->addItem(new QSpacerItem(1, 8, QSizePolicy::Expanding, QSizePolicy::Fixed));
        lyt->addWidget(new QLabel("Attach skill stone storage ID"));
        lyt->addLayout(skillStoneLyt);

        setLayout(lyt);
    }

    void AttachSkillStoneStorageIDEditor::setData(const std::shared_ptr<CharacterStorage> &characterStorageData, const std::shared_ptr<PotentialStorage> &potentialStorageData, int pkey) {
        potentialData = characterStorageData->characterDataDictionary[pkey]->data->potential;
        potentialStorage = potentialStorageData;
        characterStorage = characterStorageData;
        pkmKey = pkey;

        if (potentialData->attachSkillStoneStorageID.size() == attachSkillStoneStorageIDList.size()) {
            updateStoneCombos();
            return;
        }

        while (true) {
            QLayoutItem *itm = skillStoneLyt->takeAt(0);

            if (itm == nullptr)
                break;

            delete itm->widget();
            delete itm;
        }

        attachSkillStoneStorageIDList.clear();

        for (const i16 *sssi: potentialData->attachSkillStoneStorageID) {
            QComboBox *combo = new QComboBox();
            QFont comboFont = combo->font();

            combo->setIconSize(QSize(42, 42));
            comboFont.setPointSize(11);
            combo->setFont(comboFont);
            skillStoneLyt->addWidget(combo);
            attachSkillStoneStorageIDList.append(combo);
        }

        updateStoneCombos();
    }

    QString AttachSkillStoneStorageIDEditor::getStoneName(const int type) const {
        switch (type) {
            case 2: return "Wait Less";
            case 3: return "Whack Whack";
            case 4: return "Broadburst";
            case 5: return "Scattershot";
            case 6: return "Sharing";
            case 7: return "Stay strong";
            default: return "Invalid";
        }
    }

    QString AttachSkillStoneStorageIDEditor::getStoneLabel(const std::shared_ptr<StoneData> &stone) const {
        const int assignedPkm = *stone->characterStorageIndex;
        const std::shared_ptr<ManageData> pkm = assignedPkm != -1 ? characterStorage->characterDataDictionary[assignedPkm] : nullptr;

        return QString("%1 (+%2) %3").arg(getStoneName(stone->stoneData->type))
                .arg(stone->stoneData->bonuses.size())
                .arg(pkm != nullptr ? QString("[%1]").arg(QString::fromUtf16(pkm->data->name, pkm->data->nameLen).remove(u'\0')) : "");
    }

    void AttachSkillStoneStorageIDEditor::updateStoneLabel(const int key) const {
        const int itmIdx = attachSkillStoneStorageIDList[0]->findData(key);
        const QString lbl = getStoneLabel(potentialStorage->potentialDatas[key]);

        if (itmIdx == -1)
            return;

        for (QComboBox *combo: attachSkillStoneStorageIDList)
            combo->setItemText(itmIdx, lbl);
    }

    void AttachSkillStoneStorageIDEditor::removeStoneFromSlot(const int pkey, const int stoneKey) const {
        for (i16 *storageID: characterStorage->characterDataDictionary[pkey]->data->potential->attachSkillStoneStorageID) {
            if (*storageID != stoneKey)
                continue;

            *storageID = -1;
            break;
        }
    }

    void AttachSkillStoneStorageIDEditor::updateStoneCombos() const {
        for (QComboBox *combo: attachSkillStoneStorageIDList) {
            combo->clear();
            combo->addItem("", -1);

            for (const auto &[key, stone]: potentialStorage->potentialDatas) {
                if (stone->stoneData->type <= 1)
                    continue;

                combo->addItem(getStoneIcon(stone->stoneData->type, stone->stoneData->rarity, stone->stoneData->value), getStoneLabel(stone), stone->dictKey);
            }
        }
    }

    void AttachSkillStoneStorageIDEditor::refresh() const {
        for (int i=0,l=attachSkillStoneStorageIDList.size(); i < l; ++i) {
            QComboBox *combo = attachSkillStoneStorageIDList[i];
            const int idx = combo->findData(*(potentialData->attachSkillStoneStorageID[i]));

            attachSkillStoneStorageIDList[i]->setCurrentIndex(idx == -1 ? 0:idx);
        }
    }

    void AttachSkillStoneStorageIDEditor::apply() {
        for (int i=0,l=attachSkillStoneStorageIDList.size(); i < l; ++i) {
            const int id = attachSkillStoneStorageIDList[i]->currentData().toInt();
            const int old = *(potentialData->attachSkillStoneStorageID[i]);
            int oldOwner;

            if (old == id)
                continue;

            if (old != -1) { // unassign removed stone
                *(potentialStorage->potentialDatas[old]->characterStorageIndex) = -1;
                removeStoneFromSlot(pkmKey, old);
                updateStoneLabel(old);
                emit skillStoneAssigned(old, -1);
            }

            if (id == -1) // removed from slot, no more actions needed
                continue;

            oldOwner = *(potentialStorage->potentialDatas[id]->characterStorageIndex);
            if (oldOwner != -1) // remove new stone from previous owner
                removeStoneFromSlot(oldOwner, id);

            *(potentialData->attachSkillStoneStorageID[i]) = id; // set stone to current pkm or unset
            *(potentialStorage->potentialDatas[id]->characterStorageIndex) = pkmKey; // assign stone to current pokemon

            updateStoneLabel(id);
            emit skillStoneAssigned(id, pkmKey);
        }
    }
}
