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
#include <QDataStream>
#include <QIODevice>

#include "ItemStoragePatcher.h"

namespace PQH {
    QByteArray ItemStoragePatcher::getPatchedItemStorage(const QList<int> &counts) const {
        QByteArray patchedBytes;
        QDataStream ds(&patchedBytes, QIODevice::WriteOnly);

        ds.setByteOrder(QDataStream::LittleEndian);

        // prepare patched itemStorage obj
        ds << static_cast<quint32>(330) << // itemStorage size
           static_cast<quint32>(0) << // last index
           static_cast<quint32>(0x0c) << // datas offset
           static_cast<quint32>(318) << // datas obj size
           static_cast<quint32>(10); // datas items count

        // datas items offsets, start 8(datas size + offsets count) + 10(items) * 4 bytes
        for (u32 i=0,offt=48,l=counts.size(); i<l; ++i,offt+=27)
            ds << static_cast<quint32>(offt);

        // ingridients
        for (int i=0,l=counts.size(); i<l; ++i) {
            ds << static_cast<quint32>(27) << // core obj size
               static_cast<quint32>(2) << // last index
               static_cast<quint32>(0x14) << // id offset
               static_cast<quint32>(0x18) << // num offset
               static_cast<quint32>(0x1a) << // isNew offset
               static_cast<qint32>(i+1) << // id
               static_cast<qint16>(counts[i]) << // num
               static_cast<qint8>(1); // isNew
        }

        return patchedBytes;
    }

    std::unique_ptr<uchar[]> ItemStoragePatcher::patchItemStorage(const QList<int> &counts, int &newSaveSize) const {
        const u32 serializeDataOffset = *pointer<u32>(0);
        const u32 itemStorageSerializeDataOffset = serializeDataOffset + 8 + (5 * 4);
        const u32 itemStorageOffset = *pointer<u32>(itemStorageSerializeDataOffset) + serializeDataOffset;
        const u32 itemStorageSize = *pointer<u32>(itemStorageOffset);
        const u32 secondHalfSaveOffset = itemStorageOffset + itemStorageSize;
        const QByteArray patchedBytes = getPatchedItemStorage(counts);
        const int bytesToAdd = patchedBytes.size() - itemStorageSize;
        const int patchedSz = dataSz + bytesToAdd;
        std::unique_ptr<uchar[]> patched = std::make_unique<uchar[]>(patchedSz);
        uchar *patchedItemStorageHandle = patched.get() + itemStorageOffset;
        uchar *patchedSecondHalfHandle = patchedItemStorageHandle + patchedBytes.size();

        std::memcpy(patched.get(), data.get(), itemStorageOffset); // copy from 0 to itemstorage offset
        adjustObjOffsetList(serializeDataOffset, itemStorageSerializeDataOffset, bytesToAdd, patched.get());
        std::memcpy(patchedItemStorageHandle, patchedBytes.constData(), patchedBytes.size());
        std::memcpy(patchedSecondHalfHandle, data.get() + secondHalfSaveOffset, dataSz - secondHalfSaveOffset);

        newSaveSize = patchedSz;

        return patched;
    }
}
