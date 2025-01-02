#pragma once

#include "../TypeAliases.h"

namespace PQH {
    struct CheckData {
        i32 *checksumSize;
        uchar *hashBytes;
        i32 *version;
    };
}
