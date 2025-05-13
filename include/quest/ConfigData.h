#pragma once

#include "../TypeAliases.h"

namespace PQH {
    struct ConfigData final {
        u32 *playerSex;
        u32 *language;
        bool *bgmMute;
        bool *seMute;
        bool *PushNotice;
    };
}
