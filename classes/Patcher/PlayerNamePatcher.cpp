#include <QDataStream>
#include <QIODevice>

#include "PlayerNamePatcher.h"

namespace PQH {
    QByteArray PlayerNamePatcher::getPatchedPlayerName(const QString &name) const {
        QByteArray patchedBytes;
        QDataStream ds(&patchedBytes, QIODevice::WriteOnly);

        ds.setByteOrder(QDataStream::LittleEndian);

        ds << static_cast<quint32>(name.size());

        for (const char c: name.toStdString()) // avoid qt serialization
            ds << c;

        return patchedBytes;
    }

    std::unique_ptr<uchar[]> PlayerNamePatcher::patchPlayerName(const QString &name, int &newSaveSize) const {
        const u32 serializeDataOffset = *pointer<u32>(0);
        const u32 playerDataSerializeDataOffset = serializeDataOffset + 8 + (9 * 4);
        const u32 playerDataOffset = *pointer<u32>(playerDataSerializeDataOffset) + serializeDataOffset;
        const u32 playerNamePlayerDataOffset = playerDataOffset + 8;
        const u32 playerNameOffset = *pointer<u32>(playerNamePlayerDataOffset) + playerDataOffset;
        const u32 playerNameLen = *pointer<u32>(playerNameOffset);
        const u32 secondHalfSaveOffset = playerNameOffset + 4 + playerNameLen;
        const QByteArray patchedBytes = getPatchedPlayerName(name);
        const int bytesToAdd = name.size() - playerNameLen;
        const int patchedSz = dataSz + bytesToAdd;
        std::unique_ptr<uchar[]> patched = std::make_unique<uchar[]>(patchedSz);
        uchar *patchedPlayerNameHandle = patched.get() + playerNameOffset;
        uchar *patchedSecondHalfHandle = patchedPlayerNameHandle + patchedBytes.size();

        std::memcpy(patched.get(), data.get(), playerNameOffset);
        adjustObjOffsetList(serializeDataOffset, playerDataSerializeDataOffset, bytesToAdd, patched.get());
        adjustObjOffsetList(playerDataOffset, playerNamePlayerDataOffset, bytesToAdd, patched.get());
        std::memcpy(patchedPlayerNameHandle, patchedBytes.constData(), patchedBytes.size());
        std::memcpy(patchedSecondHalfHandle, data.get() + secondHalfSaveOffset, dataSz - secondHalfSaveOffset);

        newSaveSize = patchedSz;

        return patched;
    }
}
