#include <QVBoxLayout>
#include <QLabel>
#include <QRandomGenerator>

#include "StoneBonusEditor.h"

namespace PQH::UI {
    StoneBonusEditor::StoneBonusEditor() {
        QVBoxLayout *lyt = new QVBoxLayout();

        bonusInptList.append({new QComboBox, new QLineEdit});
        bonusInptList.append({new QComboBox, new QLineEdit});
        bonusInptList.append({new QComboBox, new QLineEdit});
        typeFilter = new QCheckBox("Only valid bonuses");

        setBonusTypeCombos(false);

        lyt->addWidget(typeFilter);
        lyt->addItem(new QSpacerItem(1, 6, QSizePolicy::Expanding, QSizePolicy::Fixed));

        for (int i=0; i<3; ++i) {
            lyt->addWidget(new QLabel(QString("Bonus %1").arg(i+1)));
            lyt->addWidget(bonusInptList[i].first);
            lyt->addWidget(bonusInptList[i].second);
        }

        setLayout(lyt);

        QObject::connect(typeFilter, &QCheckBox::checkStateChanged, this, &StoneBonusEditor::onFilterChanged);
    }

    void StoneBonusEditor::setBonusTypeCombos(const bool filter) const {
        const bool isSkill = powerStone != nullptr && powerStone->type > 1;
        const int l = filter ? (isSkill ? bonusTypeList.size() : 10) : bonusTypeList.size();

        for (const auto &inpt: bonusInptList) {
            inpt.first->clear();
            inpt.first->addItem("");
        }

        for (int i=(filter ? (isSkill ? 10:0) : 0); i<l; ++i) {
            bonusInptList[0].first->addItem(bonusTypeList[i].first.data(), bonusTypeList[i].second);
            bonusInptList[1].first->addItem(bonusTypeList[i].first.data(), bonusTypeList[i].second);
            bonusInptList[2].first->addItem(bonusTypeList[i].first.data(), bonusTypeList[i].second);
        }
    }

    void StoneBonusEditor::setData(const std::shared_ptr<PowerStone> &stone) {
        powerStone = stone;

        if (typeFilter->isChecked()) {
            const QSignalBlocker sblock {typeFilter};

            typeFilter->setChecked(false);
            setBonusTypeCombos(false);
        }

        for (const auto &inpt: bonusInptList) {
            inpt.first->setCurrentIndex(0);
            inpt.second->setText(QString::number(0));
        }

        for (int i=0,l=stone->bonuses.size(); i<l; ++i) {
            const int type = stone->bonuses[i]->type;
            const int idx = bonusInptList[i].first->findData(type);

            bonusInptList[i].first->setCurrentIndex(idx == -1 ? 0:idx);

            if (type == 6 || type == 9 || type == 12)
                bonusInptList[i].second->setText(QString::number(stone->bonuses[i]->value.intV));
            else
                bonusInptList[i].second->setText(QString::number(stone->bonuses[i]->value.floatV * 100));
        }
    }

    std::shared_ptr<PowerStoneBonus> StoneBonusEditor::makeStoneBonus(const int type, const float val) const {
        std::shared_ptr<PowerStoneBonus> bonus = std::make_shared<PowerStoneBonus>();

        bonus->unk0 = 32;
        bonus->unk1 = 32;
        bonus->type = type;
        bonus->unk2 = 24;
        bonus->unk3 = 1;
        bonus->unk4 = 16;
        bonus->unk5 = 20;
        bonus->unk6 = 1;

        if (type != 6 && type != 9 && type != 12)
            bonus->value.floatV = val / 100;
        else
            bonus->value.intV = val;

        if (powerStone->type == 0 || powerStone->type == 1) { // generate a random valid value, don't know whats this
            const int unk = QRandomGenerator::global()->bounded(1, 20);

            bonus->unk6 = 5 * unk;
        }

        return bonus;
    }

    void StoneBonusEditor::apply() const {
        powerStone->bonuses.clear();

        for (const auto &bonus: bonusInptList) {
            if (bonus.first->currentIndex() <= 0)
                continue;

            bool res;
            const float val = bonus.second->text().toFloat(&res);

            if (res)
                powerStone->bonuses.push_back(makeStoneBonus(bonus.first->currentData().toInt(), val));
        }
    }

    void StoneBonusEditor::onFilterChanged(const Qt::CheckState state) const {
        const int old1 = bonusInptList[0].first->currentData().toInt();
        const int old2 = bonusInptList[1].first->currentData().toInt();
        const int old3 = bonusInptList[2].first->currentData().toInt();
        int nidx1, nidx2, nidx3;

        setBonusTypeCombos(state == Qt::Checked);

        nidx1 = bonusInptList[0].first->findData(old1);
        nidx2 = bonusInptList[1].first->findData(old2);
        nidx3 = bonusInptList[2].first->findData(old3);

        bonusInptList[0].first->setCurrentIndex(nidx1 == -1 ? 0:nidx1);
        bonusInptList[1].first->setCurrentIndex(nidx2 == -1 ? 0:nidx2);
        bonusInptList[2].first->setCurrentIndex(nidx3 == -1 ? 0:nidx3);
    }
}
