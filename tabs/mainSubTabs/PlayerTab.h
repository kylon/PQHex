#pragma once

#include <QLineEdit>
#include <QPushButton>

#include "../include/MainSubWidget.h"
#include "../../include/quest/PlayerData.h"

namespace PQH::UI {
    class PlayerTab: public MainSubWidget {
        Q_OBJECT

    private:
        QLineEdit *playerName = nullptr;
        QPushButton *saveBtn = nullptr;

    public:
        PlayerTab();

        void setData(const std::shared_ptr<PlayerData> &data);

    private slots:
        void onSaveBtnClicked();

    signals:
        void playerNameChanged(const QString &name);
    };
}
