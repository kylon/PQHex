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

#include "SaveCharacterPoteintialData.h"

namespace PQH {
    struct SaveCharacterData final {
        u32 *exp;
        u16 *monsterNo; // dex entry
        u8 *form;
        u16 *level;
        i32 *hp;
        i32 *attak;
        char16_t *name;
        int nameLen;
        u8 *nature;
        u32 *id;
        u32 *rareRandom;
        std::shared_ptr<SaveCharacterPoteintialData> potential;
        i32 *trainingSkillCount;
        bool *isEvolve;
    };
}
