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

#include "GoodsPatcher.h"

namespace PQH {
    QByteArray GoodsPatcher::getPatchedHasDatasOffsets(const std::shared_ptr<Goods> &goodsData) const {
        QByteArray patchedBytes;
        QDataStream ds(&patchedBytes, QIODevice::WriteOnly);
        const unsigned startOffset = (goodsData->hasDatas.size() * 4) + 8; // no. of elements + 4(tot size) + 4(count)

        ds.setByteOrder(QDataStream::LittleEndian);

        ds << static_cast<quint32>(goodsData->hasDatas.size()); // number of manageData elements

        for (unsigned i=0,off=startOffset,l=goodsData->hasDatas.size(); i<l; ++i,off+=21)
            ds << static_cast<quint32>(off); // i manageData offset

        return patchedBytes;
    }

    QByteArray GoodsPatcher::getPatchedManageDataObjects(const std::shared_ptr<Goods> &goodsData) const {
        QByteArray patchedBytes;
        QDataStream ds(&patchedBytes, QIODevice::WriteOnly);

        ds.setByteOrder(QDataStream::LittleEndian);

        for (const auto &[key, good]: goodsData->hasDatas) {
            ds << static_cast<quint32>(21) << // manageData size
               static_cast<quint32>(1) << // last idx
               static_cast<quint32>(0x10) << // id offset
               static_cast<quint32>(0x14) << // isNew offset
               good->id <<
               good->isNew;
        }

        return patchedBytes;
    }

    QByteArray GoodsPatcher::getPatchedHasDatas(const std::shared_ptr<Goods> &goodsData) const {
        const QByteArray offsetListBytes = getPatchedHasDatasOffsets(goodsData);
        const QByteArray manageDataObjectsBytes = getPatchedManageDataObjects(goodsData);
        QByteArray patchedBytes;
        QDataStream ds(&patchedBytes, QIODevice::WriteOnly);

        ds.setByteOrder(QDataStream::LittleEndian);

        ds << static_cast<quint32>(offsetListBytes.size() + manageDataObjectsBytes.size() + 4); // hasDatas size

        for (const char byte: offsetListBytes)
            ds << byte;

        for (const char byte: manageDataObjectsBytes)
            ds << byte;

        return patchedBytes;
    }

    QByteArray GoodsPatcher::getPatchedPlacementDatasOffsets(const std::shared_ptr<Goods> &goodsData) const {
        QByteArray patchedBytes;
        QDataStream ds(&patchedBytes, QIODevice::WriteOnly);
        const unsigned startOffset = (goodsData->placementDatas.size() * 4) + 8; // no. of elements + 4(tot size) + 4(count)

        ds.setByteOrder(QDataStream::LittleEndian);

        ds << static_cast<quint32>(goodsData->placementDatas.size()); // number of placementData elements

        for (unsigned i=0,off=startOffset,l=goodsData->placementDatas.size(); i<l; ++i,off+=29)
            ds << static_cast<quint32>(off); // i placementData offset

        return patchedBytes;
    }

    QByteArray GoodsPatcher::getPatchedPlacementDatasObjects(const std::shared_ptr<Goods> &goodsData) const {
        QByteArray patchedBytes;
        QDataStream ds(&patchedBytes, QIODevice::WriteOnly);

        ds.setByteOrder(QDataStream::LittleEndian);

        for (const auto &[key, placement]: goodsData->placementDatas) {
            ds << static_cast<quint32>(29) << // placementData size
               static_cast<quint32>(2) << // last idx
               static_cast<quint32>(0x14) << // id offset
               static_cast<quint32>(0x18) << // goodsID offset
               static_cast<quint32>(0x1c) << // direction offset
               placement->id <<
               placement->goodsID <<
               placement->direction;
        }

        return patchedBytes;
    }

    QByteArray GoodsPatcher::getPatchedPlacementDatas(const std::shared_ptr<Goods> &goodsData) const {
        const QByteArray patchedOffsetList = getPatchedPlacementDatasOffsets(goodsData);
        const QByteArray patchedPlacementData = getPatchedPlacementDatasObjects(goodsData);
        QByteArray patchedBytes;
        QDataStream ds(&patchedBytes, QIODevice::WriteOnly);

        ds.setByteOrder(QDataStream::LittleEndian);

        ds << static_cast<quint32>(patchedOffsetList.size() + patchedPlacementData.size() + 4); // placementDatas size

        for (const char byte: patchedOffsetList)
            ds << byte;

        for (const char byte: patchedPlacementData)
            ds << byte;

        return patchedBytes;
    }

    QByteArray GoodsPatcher::getPatchedGoods(const std::shared_ptr<Goods> &goodsData) const {
        const QByteArray patchedHasDatas = getPatchedHasDatas(goodsData);
        const QByteArray patchedPlacementData = getPatchedPlacementDatas(goodsData);
        QByteArray patchedBytes;
        QDataStream ds(&patchedBytes, QIODevice::WriteOnly);

        ds.setByteOrder(QDataStream::LittleEndian);

        ds << static_cast<quint32>(patchedHasDatas.size() + patchedPlacementData.size() + 16) << // goods size
            static_cast<quint32>(1) << // last idx
            static_cast<quint32>(0x10) << // hasDatas offset
            static_cast<quint32>(0x10 + patchedHasDatas.size()); // placementDatas offset

        for (const char byte: patchedHasDatas)
            ds << byte;

        for (const char byte: patchedPlacementData)
            ds << byte;

        return patchedBytes;
    }

    std::unique_ptr<uchar[]> GoodsPatcher::patchGoods(const std::shared_ptr<Goods> &goodsData, int &newSaveSize) const {
        const u32 serializeDataOffset = *pointer<u32>(0);
        const u32 goodsSerializeDataOffset = serializeDataOffset + 8 + (11 * 4);
        const u32 goodsOffset = *pointer<u32>(goodsSerializeDataOffset) + serializeDataOffset;
        const u32 goodsSize = *pointer<u32>(goodsOffset);
        const u32 secondHalfSaveOffset = goodsOffset + goodsSize;
        const QByteArray patchedBytes = getPatchedGoods(goodsData);
        const int bytesToAdd = patchedBytes.size() - goodsSize;
        const int patchedSz = dataSz + bytesToAdd;
        std::unique_ptr<uchar[]> patched = std::make_unique<uchar[]>(patchedSz);
        uchar *patchedGoodsHandle = patched.get() + goodsOffset;
        uchar *patchedSecondHalfHandle = patchedGoodsHandle + patchedBytes.size();

        std::memcpy(patched.get(), data.get(), goodsOffset); // copy from 0 to goods offset
        adjustObjOffsetList(serializeDataOffset, goodsSerializeDataOffset, bytesToAdd, patched.get());
        std::memcpy(patchedGoodsHandle, patchedBytes.constData(), patchedBytes.size());
        std::memcpy(patchedSecondHalfHandle, data.get() + secondHalfSaveOffset, dataSz - secondHalfSaveOffset);

        newSaveSize = patchedSz;

        return patched;
    }
}
