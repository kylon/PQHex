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
#include "MiscTab.h"

namespace PQH::UI {
    MiscTab::MiscTab() {
        miscEditor = new MiscEditor();
        configDataEditor = new ConfigDataEditor();
        saveBtn = new QPushButton("Apply");

        saveBtn->setEnabled(false);

        scrollLyt->addWidget(miscEditor);
        scrollLyt->addWidget(configDataEditor);
        scrollLyt->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
        lyt->addWidget(saveBtn);

        QObject::connect(saveBtn, &QPushButton::clicked, this, &MiscTab::onSaveBtnClicked);
    }

    void MiscTab::setData(const std::shared_ptr<SerializeData> &serializeData) const {
        miscEditor->setData(serializeData);
        configDataEditor->setData(serializeData->configData);
        saveBtn->setEnabled(true);
    }

    void MiscTab::onSaveBtnClicked() const {
        saveBtn->setEnabled(false);
        miscEditor->apply();
        configDataEditor->apply();
        saveBtn->setEnabled(true);
    }
}
