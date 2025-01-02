#pragma once

#include <QScrollArea>
#include <QRect>

#include "../../include/TypeAliases.h"

namespace PQH::UI {
    [[nodiscard]] QScrollArea *createScrollArea();
    [[nodiscard]] bool isShiny(u32 pkmID, u32 pkmRareRandom);
    [[nodiscard]] QPixmap getStoneIcon(int type, int rarity, int value);
}
