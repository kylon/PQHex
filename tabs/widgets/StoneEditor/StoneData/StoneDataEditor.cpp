#include <QVBoxLayout>

#include "StoneDataEditor.h"

namespace PQH::UI {
    StoneDataEditor::StoneDataEditor() {
        QVBoxLayout *lyt = new QVBoxLayout();
        QFont typeFont, rarityFont;

        rarityLbl = new QLabel("Rarity");
        valueLbl = new QLabel("Value");
        typeCombo = new QComboBox();
        rarityCombo = new QComboBox();
        value = new QSpinBox();
        typeFont = typeCombo->font();
        rarityFont = rarityCombo->font();

        typeCombo->setMinimumSize(50, 50);
        rarityCombo->setMinimumSize(50, 50);
        typeCombo->setIconSize(QSize(42, 42));
        rarityCombo->setIconSize(QSize(42, 42));
        value->setRange(1, 999);
        typeFont.setPointSize(11);
        rarityFont.setPointSize(11);
        typeCombo->setFont(typeFont);
        rarityCombo->setFont(rarityFont);

        lyt->addWidget(new QLabel("Type"));
        lyt->addWidget(typeCombo);
        lyt->addWidget(rarityLbl);
        lyt->addWidget(rarityCombo);
        lyt->addWidget(valueLbl);
        lyt->addWidget(value);

        setLayout(lyt);

        QObject::connect(typeCombo, &QComboBox::currentIndexChanged, this, &StoneDataEditor::onStoneTypeChanged);
    }

    void StoneDataEditor::setStone(const std::shared_ptr<PowerStone> &stone) {
        const QSignalBlocker sblock {typeCombo};
        const bool isSkillStone = stone->type > 1;
        int typeIdx;

        powerStone = stone;
        prevVal = stone->value;

        rarityLbl->setVisible(!isSkillStone);
        rarityCombo->setVisible(!isSkillStone);
        valueLbl->setVisible(!isSkillStone);
        value->setVisible(!isSkillStone);
        setTypeCombo(powerStone->type);

        if (!isSkillStone) {
            setRarityCombo(powerStone->type);

            const int rarityIdx = rarityCombo->findData(powerStone->rarity);

            rarityCombo->setCurrentIndex(rarityIdx == -1 ? 0:rarityIdx);
            value->setValue(powerStone->value);
        }

        typeIdx = typeCombo->findData(stone->type);
        prevType = powerStone->type;

        typeCombo->setCurrentIndex(typeIdx == -1 ? 0:typeIdx);
    }

    void StoneDataEditor::setTypeCombo(const int type) const {
        if ((type >= 2 && type <= 7 && prevType >= 2 && prevType <= 7) || (type >= 0 && type <= 1 && prevType >= 0 && prevType <= 1))
            return;

        const QSignalBlocker sblock {typeCombo};

        typeCombo->clear();

        if (type > 1) {
            typeCombo->addItem(QIcon(":/waitless"), "Wait less", 2);
            typeCombo->addItem(QIcon(":/whackwhack"), "Whack Whack", 3);
            typeCombo->addItem(QIcon(":/broadburst"), "Broadburst", 4);
            typeCombo->addItem(QIcon(":/scattershot"), "Scattershot", 5);
            typeCombo->addItem(QIcon(":/sharing"), "Sharing", 6);
            typeCombo->addItem(QIcon(":/staystrong"), "Stay strong", 7);

        } else {
            typeCombo->addItem(QIcon(":/atk50"), "Attack", 0);
            typeCombo->addItem(QIcon(":/hp50"), "Defense", 1);
        }
    }

    void StoneDataEditor::setRarityCombo(const int type) const {
        rarityCombo->clear();

        if (type == 0) {
            rarityCombo->addItem(QIcon(":/atk50"), "Basic", 0);
            rarityCombo->addItem(QIcon(":/atkb50"), "Bronze", 10);
            rarityCombo->addItem(QIcon(":/atks50"), "Silver", 20);
            rarityCombo->addItem(QIcon(":/atkg50"), "Gold", 30);

        } else {
            rarityCombo->addItem(QIcon(":/hp50"), "Basic", 0);
            rarityCombo->addItem(QIcon(":/hpb50"), "Bronze", 10);
            rarityCombo->addItem(QIcon(":/hps50"), "Silver", 20);
            rarityCombo->addItem(QIcon(":/hpg50"), "Gold", 30);
        }
    }

    std::shared_ptr<PowerStoneBonus> StoneDataEditor::makeSkillStoneBonus(const int type, const float val) const {
        std::shared_ptr<PowerStoneBonus> bonus = std::make_shared<PowerStoneBonus>();

        bonus->unk0 = 32;
        bonus->unk1 = 32;
        bonus->type = type;
        bonus->unk2 = 24;
        bonus->unk3 = 1;
        bonus->unk4 = 16;
        bonus->unk5 = 20;
        bonus->value.floatV = val;
        bonus->unk6 = 1;

        if (type != 6 && type != 9 && type != 12)
            bonus->value.floatV /= 100;

        return bonus;
    }

    void StoneDataEditor::apply() const {
        const int oldType = powerStone->type;

        powerStone->type = typeCombo->currentData().toInt();

        if (powerStone->type == 0 || powerStone->type == 1) {
            powerStone->rarity = rarityCombo->currentData().toInt();
            powerStone->internalRarity = rarityCombo->currentIndex() + 1;

            if (value->value() != prevVal) {
                const int v = value->value();

                // not correct but close, some stones may have slightly higher range than their actual range
                // don't know what it is used for and what would cause this but better than completely wrong values
                const int vRange = static_cast<float>(v - 1) / 998.f * 100;
                const int rangeRound = qMax(1, vRange - (vRange % 5));

                powerStone->unkValueRange = rangeRound;
                powerStone->value = v;
                powerStone->unkValueRange1 = rangeRound;
            }
        }

        if (oldType == powerStone->type)
            return;

        switch (powerStone->type) {
            case 0: { // attack
                powerStone->powerStoneBonusType = 0;
            }
                break;
            case 1: { // hp
                powerStone->powerStoneBonusType = 2;
            }
                break;
            case 2: { // wait less
                powerStone->unkValueRange = 1;
                powerStone->unk12 = 1;
                powerStone->internalRarity = 1;

                powerStone->bonuses.clear();
                powerStone->bonuses.push_back(makeSkillStoneBonus(5, -0.05f));
            }
                break;
            case 3: { // whack whack
                powerStone->unkValueRange = 15;
                powerStone->unk12 = 15;
                powerStone->internalRarity = 2;

                powerStone->bonuses.clear();
                powerStone->bonuses.push_back(makeSkillStoneBonus(6, 1.f));
                powerStone->bonuses.push_back(makeSkillStoneBonus(5, 0.5f));
            }
                break;
            case 4: { // broadburst
                powerStone->unkValueRange = 5;
                powerStone->unk12 = 5;
                powerStone->internalRarity = 1;

                powerStone->bonuses.clear();
                powerStone->bonuses.push_back(makeSkillStoneBonus(9, 1.f));
            }
                break;
            case 5: { // scattershot
                powerStone->unkValueRange = 5;
                powerStone->unk12 = 5;
                powerStone->internalRarity = 2;

                powerStone->bonuses.clear();
                powerStone->bonuses.push_back(makeSkillStoneBonus(12, 1.f));
                powerStone->bonuses.push_back(makeSkillStoneBonus(11, -0.15f));
            }
                break;
            case 6: { // sharing
                powerStone->unkValueRange = 5;
                powerStone->unk12 = 5;
                powerStone->internalRarity = 1;

                powerStone->bonuses.clear();
                powerStone->bonuses.push_back(makeSkillStoneBonus(39, 0.25f));
            }
                break;
            case 7: { // stay strong
                powerStone->unkValueRange = 15;
                powerStone->unk12 = 15;
                powerStone->internalRarity = 2;

                powerStone->bonuses.clear();
                powerStone->bonuses.push_back(makeSkillStoneBonus(33, 0.25f));
                powerStone->bonuses.push_back(makeSkillStoneBonus(35, 0.25f));
            }
                break;
            default:
                break;
        }
    }

    void StoneDataEditor::onStoneTypeChanged(const int idx) {
        if (!rarityLbl->isVisible())
            return;

        QComboBox *combo = qobject_cast<QComboBox *>(QObject::sender());
        int rarityIdx;

        if (combo == nullptr)
            return;

        setRarityCombo(combo->currentData().toInt());

        rarityIdx = rarityCombo->findData(powerStone->rarity);
        rarityCombo->setCurrentIndex(rarityIdx == -1 ? 0:rarityIdx);
    }
}
