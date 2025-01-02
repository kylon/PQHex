#include <QDataStream>
#include <QIODevice>

#include "StonePatcher.h"

namespace PQH {
    QByteArray StonePatcher::getPatchedStone(const std::shared_ptr<StoneData> &stone) const {
        QByteArray stoneBytes;
        QDataStream ds(&stoneBytes, QIODevice::WriteOnly);

        ds.setByteOrder(QDataStream::LittleEndian);

        ds << stone->stoneData->unk0 <<
            stone->stoneData->unk1 <<
            stone->stoneData->unk2 <<
            stone->stoneData->unk3 <<
            stone->stoneData->unk4 <<
            stone->stoneData->unk5 <<
            stone->stoneData->unk6 <<
            stone->stoneData->unk7 <<
            stone->stoneData->unk8 <<
            stone->stoneData->unk9 <<
            stone->stoneData->unkValueRange <<
            stone->stoneData->type <<
            stone->stoneData->unk11 <<
            stone->stoneData->unk12 <<
            stone->stoneData->rarity <<
            stone->stoneData->internalRarity;

        if (stone->stoneData->type == 0 || stone->stoneData->type == 1) {
            ds << stone->stoneData->unk14 <<
                stone->stoneData->unk15 <<
                stone->stoneData->powerStoneBonusType <<
                stone->stoneData->unk17 <<
                stone->stoneData->unk18 <<
                stone->stoneData->unk19 <<
                stone->stoneData->unk20 <<
                stone->stoneData->value <<
                stone->stoneData->unkValueRange1;
        }

        for (const std::shared_ptr<PowerStoneBonus> &bonus: stone->stoneData->bonuses) {
            ds << bonus->unk0 <<
                bonus->unk1 <<
                bonus->type <<
                bonus->unk2 <<
                bonus->unk3 <<
                bonus->unk4 <<
                bonus->unk5 <<
                bonus->value.intV <<
                bonus->unk6;
        }

        return stoneBytes;
    }

    QByteArray StonePatcher::getPatchedStoneData(const std::shared_ptr<StoneData> &stone) const {
        const QByteArray stoneBytes = getPatchedStone(stone);
        const u32 stoneDataOffset = 0x18;
        const u32 characterStorageIdxOffset = stoneDataOffset + stoneBytes.size() + 4;
        const u32 isNewOffset = characterStorageIdxOffset + 4;
        const u32 timeTicksOffset = isNewOffset + 1;
        QByteArray patchedBytes;
        QDataStream ds(&patchedBytes, QIODevice::WriteOnly);

        ds.setByteOrder(QDataStream::LittleEndian);

        ds << stone->dictKey << // dict key hash, no hash for int keys
            static_cast<qint32>(-1) << // dict next
            stone->dictKey << // dict key
            static_cast<quint32>(41 + stoneBytes.size()) << // total obj size
            static_cast<quint32>(3) << // last index
            stoneDataOffset <<
            characterStorageIdxOffset <<
            isNewOffset <<
            timeTicksOffset <<
            static_cast<quint32>(stoneBytes.size()); // stone bytes count

        for (const char byte: stoneBytes) // avoid qt serialization
            ds << byte;

        ds << *stone->characterStorageIndex <<
            static_cast<quint8>(*stone->isNew) <<
            static_cast<quint64>(*stone->timeTicks);

        return patchedBytes;
    }

    std::unique_ptr<uchar[]> StonePatcher::patchStone(const std::shared_ptr<StoneData> &stone, int &newSaveSize) const {
        const u32 serializeDataOffset = *pointer<u32>(0);
        const u32 potentialStorageSerializeDataOffset = serializeDataOffset + 8 + (2 * 4);
        const u32 potentialStorageOffset = *pointer<u32>(potentialStorageSerializeDataOffset) + serializeDataOffset;
        const u32 potentialDataPotentialStorageOffset = potentialStorageOffset + 8;
        const u32 potentialDataOffset = *pointer<u32>(potentialDataPotentialStorageOffset) + potentialStorageOffset;
        const u32 potentialDataSize = *pointer<u32>(potentialDataOffset);
        const u32 bucketsCount = *pointer<u32>(potentialDataOffset + 8);
        const u32 offsetListOffset = potentialDataOffset + 12 + (bucketsCount * 4);
        const u32 stoneOffset = *pointer<u32>(stone->offset) + offsetListOffset;
        const u32 stoneSize = *pointer<u32>(stoneOffset + 12) + 12;
        const u32 secondHalfSaveOffset = stoneOffset + stoneSize;
        const QByteArray patchedBytes = getPatchedStoneData(stone);
        const int bytesToAdd = patchedBytes.size() - stoneSize;
        const u32 potentialDataPatchedSize = potentialDataSize + bytesToAdd;
        const int patchedSz = dataSz + bytesToAdd;
        std::unique_ptr<uchar[]> patched = std::make_unique<uchar[]>(patchedSz);
        uchar *patchedStoneDataHandle = patched.get() + stoneOffset;
        uchar *patchedSecondHalfHandle = patchedStoneDataHandle + patchedBytes.size();

        std::memcpy(patched.get(), data.get(), stoneOffset);
        std::memcpy(patched.get() + potentialDataOffset, &potentialDataPatchedSize, 4);
        adjustObjOffsetList(serializeDataOffset, potentialStorageSerializeDataOffset, bytesToAdd, patched.get());
        adjustObjOffsetList(potentialStorageOffset, potentialDataPotentialStorageOffset, bytesToAdd, patched.get());
        adjustObjOffsetList(offsetListOffset, stone->offset, bytesToAdd, patched.get(), true);
        std::memcpy(patchedStoneDataHandle, patchedBytes.constData(), patchedBytes.size());
        std::memcpy(patchedSecondHalfHandle, data.get() + secondHalfSaveOffset, dataSz - secondHalfSaveOffset);

        newSaveSize = patchedSz;

        return patched;
    }
}
