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

#include "include/Error.h"
#include "classes/Parser.h"

namespace PQH {
    class Save final {
    private:
        static constexpr uchar key[] {"C7PxX4jPfPQ2SmzB"};
        static constexpr uchar iv[] {"nSdhdc3ecDDEM7fA"};
        static constexpr char hmac256Key[] {"chikuwa-hanpen"};
        static constexpr int hmac256KeySz = static_cast<int>(std::string_view(hmac256Key).size());
        static constexpr int encSavedataSz = 1024 * 512;
        const int encHeadSz = 16;
        int savedataSz = 0;
        std::shared_ptr<uchar[]> savedata;
        std::shared_ptr<CheckData> checkData;
        std::shared_ptr<SerializeData> serializeData;

        [[nodiscard]] QByteArray readFile(const QString &path) const;
        [[nodiscard]] std::unique_ptr<uchar[]> decrypt(const uchar *data, int len, int &decLen) const;
        [[nodiscard]] std::unique_ptr<uchar[]> encrypt(const uchar *data, int len, int &encLen) const;
        [[nodiscard]] std::unique_ptr<uchar[]> makeChecksum() const;
        [[nodiscard]] Error parseSavedata();
        void parsePatchedSavedata(int patchedSize);

    public:
        [[nodiscard]] std::shared_ptr<CheckData> getCheckData() const { return checkData; }
        [[nodiscard]] std::shared_ptr<SerializeData> getSerializeData() const { return serializeData; }

        [[nodiscard]] Error read(const QString &path);
        [[nodiscard]] Error readDecrypted(const QString &path);
        [[nodiscard]] Error write(const QString &path) const;
        [[nodiscard]] Error writeDecrypted(const QString &path) const;
        void patchIngridients(const QList<int> &counts);
        void patchPlayerName(const QString &name);
        void patchStone(int stoneKey);
        void patchGoods();
    };
}
