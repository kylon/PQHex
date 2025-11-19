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
#include "ActiveSlotsEditor.h"

namespace PQH::UI {
    ActiveSlotsEditor::ActiveSlotsEditor(): GridWidget(3) {
        for (int i=0; i<9; ++i) {
            QCheckBox *slot = new QCheckBox(QString::number(i));

            setNextSlot();
            gridLyt->addWidget(slot, row, column, Qt::AlignCenter);
            gridLyt->setColumnStretch(column, 1);
            slotsList.append(slot);
        }
    }

    void ActiveSlotsEditor::setData(const u16 activeSlotsFlag) const {
        for (int i=0; i<9; ++i)
            slotsList[i]->setChecked(activeSlotsFlag & (1 << i));
    }

    u16 ActiveSlotsEditor::getActiveSlots() const {
        u16 activeSlots = 0;

        for (int i=0; i<9; ++i) {
            if (slotsList[i]->isChecked())
                activeSlots += (1 << i);
        }

        return activeSlots;
    }
}
