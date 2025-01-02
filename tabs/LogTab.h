#pragma once

#include <QTextEdit>
#include <QPushButton>

namespace PQH::UI {
    class LogTab: public QWidget {
        Q_OBJECT

    private:
        QTextEdit *container = nullptr;
        QPushButton *clearBtn = nullptr;

    public:
        LogTab();

        void write(const QString &msg) const;

    private slots:
        void onClearBtnClicked() const;
    };
}
