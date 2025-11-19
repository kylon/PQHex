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
#include <QMouseEvent>

#include "PokemonWidget.h"

namespace PQH::UI {
    PokemonWidget::PokemonWidget(const int pkey, const bool shiny, const int dexNo) {
        QVBoxLayout *lyt = new QVBoxLayout();
        QPalette pal = palette();

        iconLbl = new QLabel();
        shinySymbol = new QLabel(iconLbl);
        partySymbol = new QLabel(iconLbl);
        key = pkey;

        pal.setColor(QPalette::WindowText, Qt::darkBlue);
        setFrameShape(QFrame::Box);
        setPalette(pal);
        setCursor(Qt::PointingHandCursor);
        setMaximumSize(64, 64);
        iconLbl->setAlignment(Qt::AlignCenter);
        iconLbl->setPixmap(QPixmap(QString(":/pq%1").arg(dexNo)).scaled(64, 64));
        shinySymbol->setAlignment(Qt::AlignCenter);
        shinySymbol->setPixmap(QPixmap(":/star.png"));
        shinySymbol->move(48, 3);
        shinySymbol->setVisible(shiny);
        partySymbol->setAlignment(Qt::AlignCenter);
        partySymbol->setPixmap(QPixmap(":/diamond.png"));
        partySymbol->move(51, 51);
        partySymbol->setVisible(false);

        lyt->setContentsMargins(0, 0, 0, 0);
        lyt->addWidget(iconLbl);

        setLayout(lyt);
    }

    void PokemonWidget::updateWidget(const bool shiny, const int dexNo) {
        iconLbl->setPixmap(QPixmap(QString(":/pq%1").arg(dexNo)).scaled(64, 64));
        shinySymbol->setVisible(shiny);
    }

    void PokemonWidget::mouseReleaseEvent(QMouseEvent *e) {
        if (e->button() == Qt::LeftButton)
            emit clicked(key, shinySymbol->isVisible(), partySymbol->isVisible());
    }
}
