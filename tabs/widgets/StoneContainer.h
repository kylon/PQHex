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

#include "../include/FlowLayout.h"
#include "StoneWidget.h"
#include "../../include/quest/PotentialStorage.h"
#include "../../include/quest/CharacterStorage.h"

namespace PQH::UI {
    class StoneContainer final: public QWidget {
        Q_OBJECT

    private:
        FlowLayout *lyt = nullptr;
        QMap<int, StoneWidget *> stoneMap;
        int prevSelected = -1;

    public:
        StoneContainer();

        void setData(const std::shared_ptr<PotentialStorage> &potentialStorage, const std::shared_ptr<CharacterStorage> &characterStorage);
        void updateStoneWidgetAssignedPkm(int key, int dexNo) const;
        void unselectStone(int key) const;

    private slots:
        void onStoneSelected(int key);

    signals:
        void stoneSelected(int key);
    };
}
