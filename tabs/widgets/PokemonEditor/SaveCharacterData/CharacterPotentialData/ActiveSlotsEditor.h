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

#include <QCheckBox>

#include "../../../../include/GridWidget.h"
#include "../../../../../include/TypeAliases.h"

namespace PQH::UI {
    class ActiveSlotsEditor final: public GridWidget {
    private:
        QList<QCheckBox *> slotsList;

    public:
        ActiveSlotsEditor();

        void setData(u16 activeSlotsFlag) const;
        [[nodiscard]] u16 getActiveSlots() const;
    };
}
