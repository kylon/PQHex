#pragma once

#include <QComboBox>
#include <QCheckBox>

#include "../../include/quest/ConfigData.h"

namespace PQH::UI {
    class ConfigDataEditor final: public QWidget {
    private:
        QComboBox *playerSex = nullptr;
        QComboBox *language = nullptr;
        QCheckBox *bgmMute = nullptr;
        QCheckBox *seMute = nullptr;
        QCheckBox *pushNotice = nullptr;
        std::shared_ptr<ConfigData> configData;

    public:
        ConfigDataEditor();

        void setData(const std::shared_ptr<ConfigData> &data);
        void apply() const;
    };
}
