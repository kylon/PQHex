#include <QFile>
#include <openssl/evp.h>
#include <openssl/hmac.h>

#include "Save.h"
#include "classes/Patcher/ItemStoragePatcher.h"
#include "classes/Patcher/PlayerNamePatcher.h"
#include "classes/Patcher/StonePatcher.h"
#include "classes/Patcher/GoodsPatcher.h"

namespace PQH {
    QByteArray Save::readFile(const QString &path) const {
        QFile save {path};

        if (!save.open(QFile::ReadOnly))
            return {};

        return save.readAll();
    }

    Error Save::parseSavedata() {
        std::unique_ptr<uchar[]> checksum;
        Parser parser {savedata};

        checksum = makeChecksum();
        checkData = parser.parseCheckData();

        if (checksum == nullptr)
            return Error::CALC_CHECKSUM;
        else if (std::memcmp(checksum.get(), checkData->hashBytes, *checkData->checksumSize) != 0)
            return Error::CHECKSUM_MISMATCH;

        serializeData = parser.parseSerializeData();

        return Error::NONE;
    }

    void Save::parsePatchedSavedata(const int patchedSize) {
        Parser parser {savedata};

        checkData.reset();
        serializeData.reset();

        savedataSz = patchedSize;
        checkData = parser.parseCheckData();
        serializeData = parser.parseSerializeData();
    }

    Error Save::read(const QString &path) {
        const QByteArray file = readFile(path);
        const uchar *bytes = reinterpret_cast<const uchar *>(file.data());
        std::unique_ptr<uchar[]> decBodySz;
        int decHeadLen;
        int decBodyLen;

        if (file.isEmpty())
            return Error::SAVE_FILE_READ;

        decBodySz = decrypt(bytes, encHeadSz, decHeadLen);
        if (decBodySz == nullptr)
            return Error::DEC_HEAD;

        decBodyLen = *reinterpret_cast<int *>(decBodySz.get());
        savedata = decrypt(bytes + encHeadSz, decBodyLen, savedataSz);

        return savedata == nullptr ? Error::DEC_BODY : parseSavedata();
    }

    Error Save::readDecrypted(const QString &path) {
        const QByteArray file = readFile(path);

        if (file.isEmpty())
            return Error::SAVE_FILE_READ;

        savedata = std::make_shared<uchar[]>(file.size());
        savedataSz = file.size();

        std::memcpy(savedata.get(), file.data(), file.size());
        return parseSavedata();
    }

    Error Save::write(const QString &path) const {
        const std::unique_ptr<uchar[]> saveFile = std::make_unique<uchar[]>(encSavedataSz);
        const std::unique_ptr<uchar[]> checksum = makeChecksum();
        const u32 encSaveSz = savedataSz + encHeadSz & ~0xf;
        QFile save {path};
        std::unique_ptr<uchar[]> head, body;
        int encHeadLen, encBodyLen;

        if (checksum == nullptr)
            return Error::CALC_CHECKSUM;
        else if (!save.open(QFile::ReadWrite))
            return Error::WRITE_FILE_OPEN;

        std::memcpy(checkData->hashBytes, checksum.get(), *checkData->checksumSize);

        head = encrypt(reinterpret_cast<const uchar *>(&encSaveSz), 4, encHeadLen);
        if (head == nullptr || encHeadLen != encHeadSz)
            return Error::ENC_HEAD;

        body = encrypt(savedata.get(), savedataSz, encBodyLen);
        if (body == nullptr)
            return Error::ENC_BODY;

        std::memcpy(saveFile.get(), head.get(), encHeadLen);
        std::memcpy(saveFile.get() + encHeadLen, body.get(), encBodyLen);
        save.seek(0);
        save.write(reinterpret_cast<const char *>(saveFile.get()), encSavedataSz);

        return Error::NONE;
    }

    Error Save::writeDecrypted(const QString &path) const {
        const std::unique_ptr<uchar[]> checksum = makeChecksum();
        QFile saveDec {path};

        if (checksum == nullptr)
            return Error::CALC_CHECKSUM;
        else if (!saveDec.open(QFile::WriteOnly))
            return Error::WRITE_FILE_OPEN;

        std::memcpy(checkData->hashBytes, checksum.get(), *checkData->checksumSize);
        saveDec.write(reinterpret_cast<const char *>(savedata.get()), savedataSz);

        return Error::NONE;
    }

    std::unique_ptr<uchar[]> Save::decrypt(const uchar *data, const int len, int &decLen) const {
        auto evp_free = [](EVP_CIPHER_CTX *p)->void { EVP_CIPHER_CTX_free(p); };
        std::unique_ptr<EVP_CIPHER_CTX, decltype(evp_free)> ctx(EVP_CIPHER_CTX_new(), evp_free);
        std::unique_ptr<uchar[]> buf = std::make_unique<uchar[]>(len);
        int outUpLen = 0;
        int outFLen = 0;

        if (ctx == nullptr ||
            EVP_DecryptInit_ex(ctx.get(), EVP_aes_128_cbc(), nullptr, key, iv) != 1 ||
            EVP_DecryptUpdate(ctx.get(), buf.get(), &outUpLen, data, len) != 1 ||
            EVP_DecryptFinal_ex(ctx.get(), buf.get() + outUpLen, &outFLen) != 1
        )
            return nullptr;

        decLen = outUpLen + outFLen;
        return buf;
    }

    std::unique_ptr<uchar[]> Save::encrypt(const uchar *data, const int len, int &encLen) const {
        auto evp_free = [](EVP_CIPHER_CTX *p)->void { EVP_CIPHER_CTX_free(p); };
        std::unique_ptr<EVP_CIPHER_CTX, decltype(evp_free)> ctx(EVP_CIPHER_CTX_new(), evp_free);
        std::unique_ptr<uchar[]> buf = std::make_unique<uchar[]>(encSavedataSz);
        int outUpLen = 0;
        int outFLen = 0;

        if (ctx == nullptr ||
            EVP_EncryptInit_ex(ctx.get(), EVP_aes_128_cbc(), nullptr, key, iv) != 1 ||
            EVP_EncryptUpdate(ctx.get(), buf.get(), &outUpLen, data, len) != 1 ||
            EVP_EncryptFinal_ex(ctx.get(), buf.get() + outUpLen, &outFLen) != 1
        )
            return nullptr;

        encLen = outUpLen + outFLen;
        return buf;
    }

    std::unique_ptr<uchar[]> Save::makeChecksum() const {
        uchar buf[EVP_MAX_MD_SIZE] = {0};
        unsigned sumLen = 0;
        uchar *hmac = HMAC(EVP_sha256(), hmac256Key, hmac256KeySz, savedata.get() + 0x38, savedataSz - 0x38, buf, &sumLen);
        std::unique_ptr<uchar[]> ret;

        if (hmac == nullptr)
            return nullptr;

        ret = std::make_unique<uchar[]>(sumLen);

        std::memcpy(ret.get(), buf, sumLen);
        return ret;
    }

    void Save::patchIngridients(const QList<int> &counts) {
        const ItemStoragePatcher itemStoragePatcher(savedata, savedataSz);
        int patchedSaveSz;

        savedata = std::move(itemStoragePatcher.patchItemStorage(counts, patchedSaveSz));
        parsePatchedSavedata(patchedSaveSz);
    }

    void Save::patchPlayerName(const QString &name) {
        const PlayerNamePatcher playerNamePatcher(savedata, savedataSz);
        int patchedSaveSz;

        savedata = std::move(playerNamePatcher.patchPlayerName(name, patchedSaveSz));
        parsePatchedSavedata(patchedSaveSz);
    }

    void Save::patchStone(const int stoneKey) {
        const StonePatcher stonePatcher(savedata, savedataSz);
        int patchedSaveSz;

        savedata = std::move(stonePatcher.patchStone(serializeData->potentialStorage->potentialDatas[stoneKey], patchedSaveSz));
        parsePatchedSavedata(patchedSaveSz);
    }

    void Save::patchGoods() {
        const GoodsPatcher goodsPatcher(savedata, savedataSz);
        int patchedSaveSz;

        savedata = std::move(goodsPatcher.patchGoods(serializeData->goods, patchedSaveSz));
        parsePatchedSavedata(patchedSaveSz);
    }
}
