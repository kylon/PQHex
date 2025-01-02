#pragma once

#include <QByteArray>

#include "include/Patcher.h"
#include "../../include/quest/StoneData.h"

namespace PQH {
    class StonePatcher: public Patcher {
    private:
        [[nodiscard]] QByteArray getPatchedStone(const std::shared_ptr<StoneData> &stone) const;
        [[nodiscard]] QByteArray getPatchedStoneData(const std::shared_ptr<StoneData> &stone) const;

    public:
        StonePatcher(const std::shared_ptr<uchar[]> &savedata, const int saveSize): Patcher(savedata, saveSize) {}

        [[nodiscard]] std::unique_ptr<uchar[]> patchStone(const std::shared_ptr<StoneData> &stone, int &newSaveSize) const;
    };
}
