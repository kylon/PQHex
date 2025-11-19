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

#include <QWidget>
#include <QGridLayout>

namespace PQH::UI {
    class GridWidget: public QWidget {
    private:
        int itemsPerRow;

    protected:
        QGridLayout *gridLyt = nullptr;
        int column = -1;
        int row = 0;

        void setNextSlot() {
            if (++column < itemsPerRow)
                return;

            column = 0;
            ++row;
        }

        void resetSlot() {
            column = -1;
            row = 0;
        }

    public:
        explicit GridWidget(const int itemsPerRow) {
            this->itemsPerRow = itemsPerRow;
            gridLyt = new QGridLayout();

            gridLyt->setAlignment(Qt::AlignLeft | Qt::AlignTop);
            setLayout(gridLyt);
        }
    };
}
