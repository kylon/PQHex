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
