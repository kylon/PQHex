#pragma once

#include <QLabel>

#include "../include/MainSubWidget.h"
#include "../../include/quest/CheckData.h"

namespace PQH::UI {
    class InfoTab final: public MainSubWidget {
    private:
        QLabel *checksum = nullptr;
        QLabel *checksumSize = nullptr;
        QLabel *version = nullptr;

    public:
        InfoTab();

        void setData(const std::shared_ptr<CheckData> &checkData) const;
    };
}
