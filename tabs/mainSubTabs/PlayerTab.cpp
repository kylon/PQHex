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

#include "PlayerTab.h"

namespace PQH::UI {
    PlayerTab::PlayerTab() {
        playerName = new QLineEdit();
        saveBtn = new QPushButton("Apply");

        playerName->setMaxLength(25); // not sure
        saveBtn->setEnabled(false);

        scrollLyt->addWidget(new QLabel("Player name"));
        scrollLyt->addWidget(playerName);
        scrollLyt->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
        lyt->addWidget(saveBtn);

        QObject::connect(saveBtn, &QPushButton::clicked, this, &PlayerTab::onSaveBtnClicked);
    }

    void PlayerTab::setData(const std::shared_ptr<PlayerData> &data) {
        playerName->setText(QString::fromUtf8(data->name, data->nameLen));
        saveBtn->setEnabled(true);
    }

    void PlayerTab::onSaveBtnClicked() {
        saveBtn->setEnabled(false);
        emit playerNameChanged(playerName->text());
    }
}
