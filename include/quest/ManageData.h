#pragma once

#include "SaveCharacterData.h"

namespace PQH {
    struct ManageData {
        i32 dictKey;
        std::shared_ptr<SaveCharacterData> data;
        bool *isNew;
    };
}
