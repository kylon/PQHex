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

#include <vector>
#include <memory>

#include "PowerStoneBonus.h"

namespace PQH {
    struct PowerStone final {
        u32 unk0;
        u32 unk1;
        u32 unk2;
        u32 unk3;
        u32 unk4;
        u32 unk5;
        u32 unk6;
        u32 unk7;
        u32 unk8;
        u32 unk9;
        u32 unkValueRange;
        u32 type;
        u32 unk11;
        u32 unk12;
        u32 rarity;
        u32 internalRarity; // skill stone ends here, 16 ints + bonuses
        u32 unk14;
        u32 unk15;
        u32 powerStoneBonusType; // attack or hp value type
        u32 unk17;
        u32 unk18;
        u32 unk19;
        u32 unk20;
        u32 value;
        u32 unkValueRange1; // same value of unkValueRange
        std::vector<std::shared_ptr<PowerStoneBonus>> bonuses;
    };
}
