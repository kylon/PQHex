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

#include <QFrame>
#include <QLabel>

namespace PQH::UI {
    class PokemonWidget final: public QFrame {
        Q_OBJECT

    private:
        QLabel *shinySymbol = nullptr;
        QLabel *partySymbol = nullptr;
        QLabel *iconLbl = nullptr;
        int key;

    protected:
        void mouseReleaseEvent(QMouseEvent *e) override;

    public:
        PokemonWidget(int pkey, bool shiny, int dexNo);

        void setSelected() { setLineWidth(2); }
        void setUnselected() { setLineWidth(1); }
        void setInParty(const bool inParty) const { partySymbol->setVisible(inParty); }

        void updateWidget(bool shiny, int dexNo);

    signals:
        void clicked(int key, bool shiny, bool inParty);
    };
}
