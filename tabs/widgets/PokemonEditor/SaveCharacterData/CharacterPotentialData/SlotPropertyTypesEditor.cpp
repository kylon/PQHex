#include <QLabel>

#include "SlotPropertyTypesEditor.h"

namespace PQH::UI {
    SlotPropertyTypesEditor::SlotPropertyTypesEditor() {
        QVBoxLayout *lyt = new QVBoxLayout();

        slotsLyt = new QVBoxLayout();

        lyt->setContentsMargins(0, 0, 0, 0);
        lyt->addItem(new QSpacerItem(1, 8, QSizePolicy::Expanding, QSizePolicy::Fixed));
        lyt->addWidget(new QLabel("Slot property types"));
        lyt->addLayout(slotsLyt);

        setLayout(lyt);
    }

    void SlotPropertyTypesEditor::setData(const std::shared_ptr<SaveCharacterPoteintialData> &data) {
        potentialData = data;

        if (potentialData->slotPropertyTypes.size() == slotPropertyTypesList.size())
            return;

        while (true) {
            QLayoutItem *itm = slotsLyt->takeAt(0);

            if (itm == nullptr)
                break;

            delete itm->widget();
            delete itm;
        }

        slotPropertyTypesList.clear();

        for (const i8 *st: data->slotPropertyTypes) {
            QComboBox *combo = new QComboBox();
            QFont comboFont = combo->font();

            combo->setIconSize(QSize(42, 42));
            comboFont.setPointSize(11);
            combo->setFont(comboFont);
            combo->addItem(QIcon(":/atk"), "Attack");
            combo->addItem(QIcon(":/hp"), "HP");
            combo->addItem(QIcon(":/multi"), "Multi");

            slotsLyt->addWidget(combo);
            slotPropertyTypesList.append(combo);
            QObject::connect(combo, &QComboBox::currentIndexChanged, this, &SlotPropertyTypesEditor::onSlotTypeChanged);
        }
    }

    void SlotPropertyTypesEditor::refresh() const {
        for (int i=0,l=slotPropertyTypesList.size(); i < l; ++i) {
            const QSignalBlocker sblock {slotPropertyTypesList[i]};

            slotPropertyTypesList[i]->setCurrentIndex(*(potentialData->slotPropertyTypes[i]));
        }
    }

    void SlotPropertyTypesEditor::apply() const {
        for (int i=0,l=slotPropertyTypesList.size(); i < l; ++i)
            *(potentialData->slotPropertyTypes[i]) = slotPropertyTypesList[i]->currentIndex();
    }

    void SlotPropertyTypesEditor::onSlotTypeChanged(const int idx) {
        QComboBox *combo = qobject_cast<QComboBox *>(QObject::sender());

        if (combo == nullptr)
            return;

        emit slotTypeChanged(slotPropertyTypesList.indexOf(combo), idx);
    }
}
