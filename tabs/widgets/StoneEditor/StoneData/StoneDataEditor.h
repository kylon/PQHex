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
