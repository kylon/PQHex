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
#include "InfoTab.h"

namespace PQH::UI {
    using namespace Qt::StringLiterals;

    InfoTab::InfoTab() {
        checksum = new QLabel(u"-"_s);
        checksumSize = new QLabel(u"-"_s);
        version = new QLabel(u"-"_s);

        checksum->setWordWrap(true);
        scrollLyt->addWidget(new QLabel(u"Checksum"_s));
        scrollLyt->addWidget(checksum);
        scrollLyt->addItem(new QSpacerItem(1, 6, QSizePolicy::Expanding, QSizePolicy::Fixed));
        scrollLyt->addWidget(new QLabel(u"Checksum size"_s));
        scrollLyt->addWidget(checksumSize);
        scrollLyt->addItem(new QSpacerItem(1, 6, QSizePolicy::Expanding, QSizePolicy::Fixed));
        scrollLyt->addWidget(new QLabel(u"Game internal version"_s));
        scrollLyt->addWidget(version);
        scrollLyt->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    }

    void InfoTab::setData(const std::shared_ptr<CheckData> &checkData) const {
        const QByteArray hash = QByteArray(checkData->hashBytes);

        checksum->setText(hash.toHex(' ').toUpper());
        checksumSize->setNum(*checkData->checksumSize);
        version->setNum(*checkData->version);
    }
}
