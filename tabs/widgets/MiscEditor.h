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

#include <QSpinBox>

#include "../../include/quest/SerializeData.h"

namespace PQH::UI {
    class MiscEditor final: public QWidget {
    private:
        QSpinBox *pokemonBoxCapacity = nullptr;
        QSpinBox *potentialStorageCapacity = nullptr;
        QSpinBox *tickets = nullptr;
        QSpinBox *battery = nullptr;
        std::shared_ptr<CharacterStorage> characterStorage;
        std::shared_ptr<PotentialStorage> potentialStorage;
        std::shared_ptr<Misc> miscData;

    public:
        MiscEditor();

        void setData(const std::shared_ptr<SerializeData> &serializeData);
        void apply() const;
    };
}
