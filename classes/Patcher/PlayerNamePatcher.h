/*
 * This file is part of PQHex.
 * Copyright (C) 2025 kylon
 *
 * PQHex is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PQHex is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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
