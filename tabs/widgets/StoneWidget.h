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

#include <QFrame>
#include <QLabel>

namespace PQH::UI {
    class StoneWidget final: public QFrame {
        Q_OBJECT

    private:
        QLabel *iconLbl = nullptr;
        QLabel *pkmLbl = nullptr;
        QLabel *valueLbl = nullptr;
        int key;

        [[nodiscard]] int getValueLblPosX(int value) const;

    protected:
        void mouseReleaseEvent(QMouseEvent *e) override;

    public:
        StoneWidget(int skey, int type, int rarity, int value, int assignedToPkmNo);

        void setSelected() { setLineWidth(2); }
        void setUnselected() { setLineWidth(1); }

        void updateAssignedPkm(int assignedToPkmNo) const;

    signals:
        void clicked(int key);
    };
}
