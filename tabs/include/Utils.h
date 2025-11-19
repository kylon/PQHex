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

#include <QScrollArea>
#include <QRect>

#include "../../include/TypeAliases.h"

namespace PQH::UI {
    [[nodiscard]] QScrollArea *createScrollArea();
    [[nodiscard]] bool isShiny(u32 pkmID, u32 pkmRareRandom);
    [[nodiscard]] QPixmap getStoneIcon(int type, int rarity, int value);
}
