#pragma once

#include <QList>
#include <QByteArray>

#include "include/Patcher.h"

namespace PQH {
    class ItemStoragePatcher: public Patcher {
    private:
        [[nodiscard]] QByteArray getPatchedItemStorage(const QList<int> &counts) const;

    public:
        ItemStoragePatcher(const std::shared_ptr<uchar[]> &savedata, const int saveSize): Patcher(savedata, saveSize) {}

        [[nodiscard]] std::unique_ptr<uchar[]> patchItemStorage(const QList<int> &counts, int &newSaveSize) const;
    };
}
