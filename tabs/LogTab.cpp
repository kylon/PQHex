#include <QVBoxLayout>

#include "LogTab.h"

namespace PQH::UI {
    LogTab::LogTab() {
        QVBoxLayout *lyt = new QVBoxLayout();
        QHBoxLayout *btnLyt = new QHBoxLayout();

        container = new QTextEdit();
        clearBtn = new QPushButton("Clear");

        container->setReadOnly(true);
        btnLyt->addWidget(clearBtn);
        btnLyt->setAlignment(Qt::AlignRight);
        lyt->addWidget(container);
        lyt->addLayout(btnLyt);

        setLayout(lyt);

        QObject::connect(clearBtn, &QPushButton::clicked, this, &LogTab::onClearBtnClicked);
    }

    void LogTab::write(const QString &msg) const {
        container->append(msg);
    }

    void LogTab::onClearBtnClicked() const {
        container->clear();
    }
}
