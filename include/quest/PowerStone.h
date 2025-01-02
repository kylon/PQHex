#pragma once

#include <vector>
#include <memory>

#include "PowerStoneBonus.h"

namespace PQH {
    struct PowerStone {
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
