#include "MiscTab.h"

namespace PQH::UI {
    MiscTab::MiscTab() {
        miscEditor = new MiscEditor();
        configDataEditor = new ConfigDataEditor();
        saveBtn = new QPushButton("Apply");

        saveBtn->setEnabled(false);

        scrollLyt->addWidget(miscEditor);
        scrollLyt->addWidget(configDataEditor);
        scrollLyt->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
        lyt->addWidget(saveBtn);

        QObject::connect(saveBtn, &QPushButton::clicked, this, &MiscTab::onSaveBtnClicked);
    }

    void MiscTab::setData(const std::shared_ptr<SerializeData> &serializeData) const {
        miscEditor->setData(serializeData);
        configDataEditor->setData(serializeData->configData);
        saveBtn->setEnabled(true);
    }

    void MiscTab::onSaveBtnClicked() const {
        saveBtn->setEnabled(false);
        miscEditor->apply();
        configDataEditor->apply();
        saveBtn->setEnabled(true);
    }
}
