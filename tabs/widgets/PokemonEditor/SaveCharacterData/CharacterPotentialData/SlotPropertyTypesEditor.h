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
#include <QVBoxLayout>

#include "../../../../../include/quest/SaveCharacterPoteintialData.h"

namespace PQH::UI {
    class SlotPropertyTypesEditor final: public QWidget {
        Q_OBJECT

    private:
        QVBoxLayout *slotsLyt = nullptr;
        QList<QComboBox *> slotPropertyTypesList;
        std::shared_ptr<SaveCharacterPoteintialData> potentialData;

    public:
        SlotPropertyTypesEditor();

        void setData(const std::shared_ptr<SaveCharacterPoteintialData> &data);
        void refresh() const;
        void apply() const;

    private slots:
        void onSlotTypeChanged(int idx);

    signals:
        void slotTypeChanged(int slotIdx, int type);
    };
}
