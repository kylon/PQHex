#pragma once

#include "../TypeAliases.h"

namespace PQH {
    struct PowerStoneBonus {
        u32 unk0;
        u32 unk1;
        u32 type;
        u32 unk2;
        u32 unk3;
        u32 unk4;
        u32 unk5;
        union {
            float floatV;
            u32 intV;
        } value;
        u32 unk6;
    };
}
