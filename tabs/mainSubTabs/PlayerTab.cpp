#include <QVBoxLayout>
#include <QLabel>

#include "PlayerTab.h"

namespace PQH::UI {
    PlayerTab::PlayerTab() {
        playerName = new QLineEdit();
        saveBtn = new QPushButton("Apply");

        playerName->setMaxLength(25); // not sure
        saveBtn->setEnabled(false);

        scrollLyt->addWidget(new QLabel("Player name"));
        scrollLyt->addWidget(playerName);
        scrollLyt->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
        lyt->addWidget(saveBtn);

        QObject::connect(saveBtn, &QPushButton::clicked, this, &PlayerTab::onSaveBtnClicked);
    }

    void PlayerTab::setData(const std::shared_ptr<PlayerData> &data) {
        playerName->setText(QString::fromUtf8(data->name, data->nameLen));
        saveBtn->setEnabled(true);
    }

    void PlayerTab::onSaveBtnClicked() {
        saveBtn->setEnabled(false);
        emit playerNameChanged(playerName->text());
    }
}
