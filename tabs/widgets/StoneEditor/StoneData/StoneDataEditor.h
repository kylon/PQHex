#pragma once

#include <QComboBox>
#include <QSpinBox>
#include <QLabel>

#include "../../../../include/quest/PowerStone.h"

namespace PQH::UI {
    class StoneDataEditor final: public QWidget {
        Q_OBJECT

    private:
        QComboBox *typeCombo = nullptr;
        QLabel *rarityLbl = nullptr;
        QComboBox *rarityCombo = nullptr;
        QLabel *valueLbl = nullptr;
        QSpinBox *value = nullptr;
        std::shared_ptr<PowerStone> powerStone;
        int prevType = -1;
        int prevVal = 0;

        void setTypeCombo(int type) const;
        void setRarityCombo(int type) const;
        [[nodiscard]] std::shared_ptr<PowerStoneBonus> makeSkillStoneBonus(int type, float val) const;

    public:
        StoneDataEditor();

        void setStone(const std::shared_ptr<PowerStone> &stone);
        void apply() const;

    private slots:
        void onStoneTypeChanged(int idx);
    };
}
