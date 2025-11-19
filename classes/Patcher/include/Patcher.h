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

#include <memory>

#include "../../../include/TypeAliases.h"

namespace PQH {
    class Patcher {
    protected:
        std::shared_ptr<uchar[]> data;
        int dataSz;

    protected:
        template<typename T>
        [[nodiscard]] T *pointer(const unsigned offset) const { return reinterpret_cast<T *>(data.get() + offset); }

        void adjustObjOffsetList(const u32 objOffset, const u32 patchedOffsetOffset, const int bytesToAdd, uchar *patchedData, const bool isDictionary = false) const {
            const u32 objSize = *pointer<u32>(objOffset);
            const u32 objItemCount = *pointer<u32>(objOffset + 4) + (isDictionary ? 0:1);
            const u32 patchedObjSz = objSize + bytesToAdd;
            const u32 start = objOffset + 8;

            std::memcpy(patchedData + objOffset, &patchedObjSz, 4);

            for (u32 i=0,offt=start; i<objItemCount; ++i,offt+=4) {
                if (patchedOffsetOffset >= offt)
                    continue;

                const u32 adjusted = *pointer<u32>(offt) + bytesToAdd;

                std::memcpy(patchedData + offt, &adjusted, 4);
            }
        }

    public:
        Patcher(const std::shared_ptr<uchar[]> &savedata, const int saveSize) {
            data = savedata;
            dataSz = saveSize;
        }
    };
}
