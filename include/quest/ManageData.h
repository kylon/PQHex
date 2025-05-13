#pragma once

#include "SaveCharacterData.h"

namespace PQH {
    struct ManageData final {
        i32 dictKey;
        std::shared_ptr<SaveCharacterData> data;
        bool *isNew;
    };
}
