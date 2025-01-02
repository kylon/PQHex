#include "InfoTab.h"

namespace PQH::UI {
    InfoTab::InfoTab() {
        checksum = new QLabel("-");
        checksumSize = new QLabel("-");
        version = new QLabel("-");

        checksum->setWordWrap(true);
        scrollLyt->addWidget(new QLabel("Checksum"));
        scrollLyt->addWidget(checksum);
        scrollLyt->addItem(new QSpacerItem(1, 6, QSizePolicy::Expanding, QSizePolicy::Fixed));
        scrollLyt->addWidget(new QLabel("Checksum size"));
        scrollLyt->addWidget(checksumSize);
        scrollLyt->addItem(new QSpacerItem(1, 6, QSizePolicy::Expanding, QSizePolicy::Fixed));
        scrollLyt->addWidget(new QLabel("Game internal version"));
        scrollLyt->addWidget(version);
        scrollLyt->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    }

    void InfoTab::setData(const std::shared_ptr<CheckData> &checkData) const {
        const QByteArray hash = QByteArray(checkData->hashBytes);

        checksum->setText(hash.toHex(' ').toUpper());
        checksumSize->setNum(*checkData->checksumSize);
        version->setNum(*checkData->version);
    }
}
