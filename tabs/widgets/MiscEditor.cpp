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
#include <QVBoxLayout>
#include <QLabel>

#include "MiscEditor.h"

namespace PQH::UI {
    MiscEditor::MiscEditor() {
        QVBoxLayout *lyt = new QVBoxLayout();

        pokemonBoxCapacity = new QSpinBox();
        potentialStorageCapacity = new QSpinBox();
        tickets = new QSpinBox();
        battery = new QSpinBox();

        pokemonBoxCapacity->setRange(100, 400);
        potentialStorageCapacity->setRange(100, 400);
        tickets->setRange(0, 99999);
        battery->setRange(0, 99);

        lyt->setContentsMargins(0, 0, 0, 0);
        lyt->addWidget(new QLabel("Pokemon box capacity"));
        lyt->addWidget(pokemonBoxCapacity);
        lyt->addWidget(new QLabel("Stone box capacity"));
        lyt->addWidget(potentialStorageCapacity);
        lyt->addWidget(new QLabel("Tickets"));
        lyt->addWidget(tickets);
        lyt->addWidget(new QLabel("Battery"));
        lyt->addWidget(battery);

        setLayout(lyt);
    }

    void MiscEditor::setData(const std::shared_ptr<SerializeData> &serializeData) {
        characterStorage = serializeData->characterStorage;
        potentialStorage = serializeData->potentialStorage;
        miscData = serializeData->misc;

        pokemonBoxCapacity->setValue(*characterStorage->dataCapacity);
        potentialStorageCapacity->setValue(*potentialStorage->dataCapacity);
        tickets->setValue(*miscData->fsGiftTicketNum);
        battery->setValue(*miscData->battery);
    }

    void MiscEditor::apply() const {
        *characterStorage->dataCapacity = pokemonBoxCapacity->value();
        *potentialStorage->dataCapacity = potentialStorageCapacity->value();
        *miscData->fsGiftTicketNum = tickets->value();
        *miscData->battery = battery->value();
    }
}
