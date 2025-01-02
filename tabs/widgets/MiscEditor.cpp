#include <QVBoxLayout>
#include <QLabel>

#include "MiscEditor.h"

namespace PQH::UI {
    MiscEditor::MiscEditor() {
        QVBoxLayout *lyt = new QVBoxLayout();

        pokemonBoxCapacity = new QSpinBox();
        potentialStorageCapacity = new QSpinBox();
        tickets = new QSpinBox();
        battery = new QSpinBox();

        pokemonBoxCapacity->setRange(100, 400);
        potentialStorageCapacity->setRange(100, 400);
        tickets->setRange(0, 99999);
        battery->setRange(0, 99);

        lyt->setContentsMargins(0, 0, 0, 0);
        lyt->addWidget(new QLabel("Pokemon box capacity"));
        lyt->addWidget(pokemonBoxCapacity);
        lyt->addWidget(new QLabel("Stone box capacity"));
        lyt->addWidget(potentialStorageCapacity);
        lyt->addWidget(new QLabel("Tickets"));
        lyt->addWidget(tickets);
        lyt->addWidget(new QLabel("Battery"));
        lyt->addWidget(battery);

        setLayout(lyt);
    }

    void MiscEditor::setData(const std::shared_ptr<SerializeData> &serializeData) {
        characterStorage = serializeData->characterStorage;
        potentialStorage = serializeData->potentialStorage;
        miscData = serializeData->misc;

        pokemonBoxCapacity->setValue(*characterStorage->dataCapacity);
        potentialStorageCapacity->setValue(*potentialStorage->dataCapacity);
        tickets->setValue(*miscData->fsGiftTicketNum);
        battery->setValue(*miscData->battery);
    }

    void MiscEditor::apply() const {
        *characterStorage->dataCapacity = pokemonBoxCapacity->value();
        *potentialStorage->dataCapacity = potentialStorageCapacity->value();
        *miscData->fsGiftTicketNum = tickets->value();
        *miscData->battery = battery->value();
    }
}
