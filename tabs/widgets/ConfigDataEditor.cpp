#include <QVBoxLayout>
#include <QLabel>

#include "ConfigDataEditor.h"

namespace PQH::UI {
    ConfigDataEditor::ConfigDataEditor() {
        QVBoxLayout *lyt = new QVBoxLayout();

        playerSex = new QComboBox();
        language = new QComboBox();
        bgmMute = new QCheckBox("Disable music");
        seMute = new QCheckBox("Disable sound effects");
        pushNotice = new QCheckBox("Push notifications");

        playerSex->addItems({"Male", "Female", "Other"});
        language->addItems({"", "Japanese", "English", "French", "Italian", "German", "Spanish", "Korean", "ChineseSimplified", "ChineseTraditional"});

        lyt->setContentsMargins(0, 0, 0, 0);
        lyt->addWidget(new QLabel("Player sex"));
        lyt->addWidget(playerSex);
        lyt->addWidget(new QLabel("Language"));
        lyt->addWidget(language);
        lyt->addWidget(bgmMute);
        lyt->addWidget(seMute);
        lyt->addWidget(pushNotice);

        setLayout(lyt);
    }

    void ConfigDataEditor::setData(const std::shared_ptr<ConfigData> &data) {
        configData = data;

        playerSex->setCurrentIndex(*configData->playerSex);
        language->setCurrentIndex(*configData->language);
        bgmMute->setChecked(*configData->bgmMute);
        seMute->setChecked(*configData->seMute);
        pushNotice->setChecked(*configData->PushNotice);
    }

    void ConfigDataEditor::apply() const {
        *configData->playerSex = playerSex->currentIndex();
        *configData->language = language->currentIndex();
        *configData->bgmMute = bgmMute->isChecked();
        *configData->seMute = seMute->isChecked();
        *configData->PushNotice = pushNotice->isChecked();
    }
}
