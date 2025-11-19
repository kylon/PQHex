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

#include "LogTab.h"

namespace PQH::UI {
    LogTab::LogTab() {
        QVBoxLayout *lyt = new QVBoxLayout();
        QHBoxLayout *btnLyt = new QHBoxLayout();

        container = new QTextEdit();
        clearBtn = new QPushButton("Clear");

        container->setReadOnly(true);
        btnLyt->addWidget(clearBtn);
        btnLyt->setAlignment(Qt::AlignRight);
        lyt->addWidget(container);
        lyt->addLayout(btnLyt);

        setLayout(lyt);

        QObject::connect(clearBtn, &QPushButton::clicked, this, &LogTab::onClearBtnClicked);
    }

    void LogTab::write(const QString &msg) const {
        container->append(msg);
    }

    void LogTab::onClearBtnClicked() const {
        container->clear();
    }
}
