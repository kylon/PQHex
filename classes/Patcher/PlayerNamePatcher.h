#pragma once

#include <QByteArray>

#include "include/Patcher.h"

namespace PQH {
    class PlayerNamePatcher final: public Patcher {
    private:
        [[nodiscard]] QByteArray getPatchedPlayerName(const QString &name) const;

    public:
        PlayerNamePatcher(const std::shared_ptr<uchar[]> &savedata, const int saveSize): Patcher(savedata, saveSize) {}

        [[nodiscard]] std::unique_ptr<uchar[]> patchPlayerName(const QString &name, int &newSaveSize) const;
    };
}
