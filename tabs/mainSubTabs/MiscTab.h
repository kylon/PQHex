#pragma once

#include <QPushButton>

#include "../include/MainSubWidget.h"
#include "../widgets/MiscEditor.h"
#include "../widgets/ConfigDataEditor.h"

namespace PQH::UI {
    class MiscTab: public MainSubWidget {
        Q_OBJECT

    private:
        MiscEditor *miscEditor = nullptr;
        ConfigDataEditor *configDataEditor = nullptr;
        QPushButton *saveBtn = nullptr;

    public:
        MiscTab();

        void setData(const std::shared_ptr<SerializeData> &serializeData) const;

    private slots:
        void onSaveBtnClicked() const;
    };
}
