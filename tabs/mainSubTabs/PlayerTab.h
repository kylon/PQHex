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

#include <QLineEdit>
#include <QPushButton>

#include "../include/MainSubWidget.h"
#include "../../include/quest/PlayerData.h"

namespace PQH::UI {
    class PlayerTab final: public MainSubWidget {
        Q_OBJECT

    private:
        QLineEdit *playerName = nullptr;
        QPushButton *saveBtn = nullptr;

    public:
        PlayerTab();

        void setData(const std::shared_ptr<PlayerData> &data);

    private slots:
        void onSaveBtnClicked();

    signals:
        void playerNameChanged(const QString &name);
    };
}
