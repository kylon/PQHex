#include <QLabel>

#include "PotentialSkillDataEditor.h"

namespace PQH::UI {
    PotentialSkillDataEditor::PotentialSkillDataEditor() {
        QVBoxLayout *lyt = new QVBoxLayout();

        skillsLyt = new QVBoxLayout();
        moveFilter = new QCheckBox("Only valid moves");

        lyt->setContentsMargins(0, 0, 0, 0);
        lyt->addItem(new QSpacerItem(1, 8, QSizePolicy::Expanding, QSizePolicy::Fixed));
        lyt->addWidget(new QLabel("Potential skill"));
        lyt->addItem(new QSpacerItem(1, 4, QSizePolicy::Expanding, QSizePolicy::Fixed));
        lyt->addWidget(moveFilter);
        lyt->addItem(new QSpacerItem(1, 4, QSizePolicy::Expanding, QSizePolicy::Fixed));
        lyt->addLayout(skillsLyt);

        setLayout(lyt);

        QObject::connect(moveFilter, &QCheckBox::checkStateChanged, this, &PotentialSkillDataEditor::onMoveFilterChanged);
    }

    void PotentialSkillDataEditor::addSkillItem(QComboBox *combo, const PQH::UI::PotentialSkillDataEditor::Move_t &move) const {
        QString lbl;

        if (move.damage == -1)
            lbl = move.name.data();
        else
            lbl = QString("%1 [%2:%3]").arg(move.name.data()).arg(move.damage).arg(move.wait);

        combo->addItem(QIcon(QString(":/%1").arg(move.icon.data())), lbl, move.id);
    }

    void PotentialSkillDataEditor::setSkillCombos(const bool filter) const {
        int psid = 0;

        for (QComboBox *combo: skillIDList)
            combo->setEnabled(false);

        for (QComboBox *combo: skillIDList) {
            int comboIdx;

            combo->clear();
            combo->addItem(QIcon(":/question"), "Unset", UINT16_MAX);

            if (filter) {
                const MoveSet_t set = movesDB[monsterNo - 1];

                for (int i=0; i<set.setLimit; ++i)
                    addSkillItem(combo, MovesData[static_cast<int>(moveSets[set.setIdx][i])]);

            } else {
                for (const Move_t &move: MovesData)
                    addSkillItem(combo, move);
            }

            comboIdx = combo->findData(*(potentialData->potentialSkill[psid++]->skillID));
            combo->setCurrentIndex(comboIdx == -1 ? 0:comboIdx);
        }

        for (QComboBox *combo: skillIDList)
            combo->setEnabled(true);
    }

    void PotentialSkillDataEditor::setData(const std::shared_ptr<SaveCharacterPoteintialData> &data, const int dexNo) {
        potentialData = data;
        monsterNo = dexNo;

        if (potentialData->potentialSkill.size() == slotIndexList.size()) {
            if (moveFilter->isChecked()) {
                const QSignalBlocker sblock {moveFilter};

                moveFilter->setChecked(false);
                setSkillCombos(false);
            }

            return;
        }

        while (true) {
            QLayoutItem *itm = skillsLyt->takeAt(0);

            if (itm == nullptr)
                break;

            delete itm->widget();
            delete itm;
        }

        slotIndexList.clear();
        skillIDList.clear();

        for (const std::shared_ptr<SavePotentialSkillData> &sd: potentialData->potentialSkill) {
            QSpinBox *slotIdx = new QSpinBox();
            QComboBox *skillID = new QComboBox();
            QFont skillIDFont = skillID->font();

            slotIdx->setRange(-1, 8);
            skillID->setIconSize(QSize(42, 42));
            skillIDFont.setPointSize(11);
            skillID->setFont(skillIDFont);

            skillsLyt->addWidget(new QLabel("Slot index"));
            skillsLyt->addWidget(slotIdx);
            skillsLyt->addWidget(new QLabel("Skill ID"));
            skillsLyt->addWidget(skillID);
            slotIndexList.append(slotIdx);
            skillIDList.append(skillID);
        }

        setSkillCombos(false);
    }

    void PotentialSkillDataEditor::updateMonsterNo(const int dexNo) {
        monsterNo = dexNo;

        if (moveFilter->isChecked())
            setSkillCombos(true);
    }

    void PotentialSkillDataEditor::refresh() const {
        for (int i=0,l=slotIndexList.size(); i<l; ++i) {
            const int idx = skillIDList[i]->findData(*(potentialData->potentialSkill[i]->skillID));

            slotIndexList[i]->setValue(*(potentialData->potentialSkill[i]->slotIndex));
            skillIDList[i]->setCurrentIndex(idx == -1 ? 0:idx);
        }
    }

    void PotentialSkillDataEditor::apply() const {
        for (int i=0,l=slotIndexList.size(); i<l; ++i) {
            *(potentialData->potentialSkill[i]->slotIndex) = slotIndexList[i]->value();
            *(potentialData->potentialSkill[i]->skillID) = skillIDList[i]->currentData().toUInt();
        }
    }

    void PotentialSkillDataEditor::onMoveFilterChanged(const Qt::CheckState state) const {
        moveFilter->setEnabled(false);
        setSkillCombos(state == Qt::Checked);
        moveFilter->setEnabled(true);
    }
}
