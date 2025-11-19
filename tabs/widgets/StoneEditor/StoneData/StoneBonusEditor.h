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
#include <QLineEdit>
#include <QCheckBox>

#include "../../../../include/quest/PowerStone.h"

namespace PQH::UI {
    class StoneBonusEditor final: public QWidget {
        Q_OBJECT

    private:
        static constexpr std::array<std::pair<std::string_view, int>, 18> bonusTypeList {{
            {"Natural Healing (%)", 14}, {"Movement Speed (%)", 23}, {"Critical Hit Rate (%)", 26},
            {"Critical Hit Damage (%)", 27}, {"Time to Recover (%)", 28}, {"HP upon Recovery (%)", 29},
            {"Hit Healing (%)", 40}, {"Healing from K.O. (%)", 41}, {"Resistant to ↓ Effects (%)", 48},
            {"Resistant to Status Conditions (%)", 49},

            // skill bonus types
            {"Number of move repetitions", 6}, {"Move wait time (%)", 5}, {"Move's number of shots", 12},
            {"Move's ATK (%)", 11}, {"Effect ↑ duration (%)", 33}, {"Effect ↓ duration (%)", 35},
            {"↑ Effects for buddies (%)", 39}, {"Attack width", 9}
        }};
        QCheckBox *typeFilter = nullptr;
        QList<std::pair<QComboBox *, QLineEdit *>> bonusInptList;
        std::shared_ptr<PowerStone> powerStone;

        void setBonusTypeCombos(bool filter) const;
        [[nodiscard]] std::shared_ptr<PowerStoneBonus> makeStoneBonus(int type, float val) const;

    public:
        StoneBonusEditor();

        void setData(const std::shared_ptr<PowerStone> &stone);
        void apply() const;

    private slots:
        void onFilterChanged(Qt::CheckState state) const;
    };
}
