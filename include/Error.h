#pragma once

namespace PQH {
    enum class Error {
        NONE,
        SAVE_FILE_READ,
        WRITE_FILE_OPEN,
        DEC_HEAD,
        ENC_HEAD,
        DEC_BODY,
        ENC_BODY,
        CALC_CHECKSUM,
        CHECKSUM_MISMATCH
    };
}
