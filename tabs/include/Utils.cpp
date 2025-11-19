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
#include "Utils.h"

namespace PQH::UI {
    QScrollArea *createScrollArea() {
        QScrollArea *scrollArea = new QScrollArea();

        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollArea->setWidget(new QWidget);

        return scrollArea;
    }

    bool isShiny(const u32 pkmID, const u32 pkmRareRandom) {
        const u16 r1 = (pkmID >> 16) ^ (pkmID & 0x0000ffff);
        const u16 r2 = r1 ^ (pkmRareRandom >> 16);
        const u16 r3 = r2 ^ (pkmRareRandom & 0x0000ffff);

        return r3 < 16;
    }

    QPixmap getStoneIcon(const int type, const int rarity, const int value) {
        QString icon {":/"};

        switch (type) {
            case 0:
                icon.append("atk");
                break;
            case 1:
                icon.append("hp");
                break;
            case 2:
                icon.append("waitless");
                break;
            case 3:
                icon.append("whackwhack");
                break;
            case 4:
                icon.append("broadburst");
                break;
            case 5:
                icon.append("scattershot");
                break;
            case 6:
                icon.append("sharing");
                break;
            case 7:
                icon.append("staystrong");
                break;
            default:
                break;
        }

        if (type == 0 || type == 1) {
            switch (rarity) {
                case 10:
                    icon.append('b');
                    break;
                case 20:
                    icon.append('s');
                    break;
                case 30:
                    icon.append('g');
                    break;
                default:
                    break;
            }

            if (value <= 100)
                icon.append("50");
            else if (value <= 170)
                icon.append("80");
            else if (value <= 310)
                icon.append("160");
            else if (value <= 500)
                icon.append("210");
            else if (value <= 660)
                icon.append("360");
            else
                icon.append("max");
        }

        return QPixmap(icon).scaled(64, 64);
    }
}
