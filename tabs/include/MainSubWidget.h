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

#include <QScrollBar>
#include <QVBoxLayout>

#include "Utils.h"

namespace PQH::UI {
    class MainSubWidget: public QWidget {
    private:
        QScrollArea *scrollArea = nullptr;

    protected:
        QVBoxLayout *scrollLyt = nullptr;
        QVBoxLayout *lyt = nullptr;

        void resetScroolbar() const { scrollArea->verticalScrollBar()->setValue(0); }

    public:
        MainSubWidget() {
            scrollArea = createScrollArea();
            scrollLyt = new QVBoxLayout();
            lyt = new QVBoxLayout();

            scrollArea->widget()->setLayout(scrollLyt);
            lyt->addWidget(scrollArea);

            setLayout(lyt);
        }
    };
}
