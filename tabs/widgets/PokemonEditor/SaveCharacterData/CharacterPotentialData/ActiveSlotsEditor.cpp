#include "ActiveSlotsEditor.h"

namespace PQH::UI {
    ActiveSlotsEditor::ActiveSlotsEditor(): GridWidget(3) {
        for (int i=0; i<9; ++i) {
            QCheckBox *slot = new QCheckBox(QString::number(i));

            setNextSlot();
            gridLyt->addWidget(slot, row, column, Qt::AlignCenter);
            gridLyt->setColumnStretch(column, 1);
            slotsList.append(slot);
        }
    }

    void ActiveSlotsEditor::setData(const u16 activeSlotsFlag) const {
        for (int i=0; i<9; ++i)
            slotsList[i]->setChecked(activeSlotsFlag & (1 << i));
    }

    u16 ActiveSlotsEditor::getActiveSlots() const {
        u16 activeSlots = 0;

        for (int i=0; i<9; ++i) {
            if (slotsList[i]->isChecked())
                activeSlots += (1 << i);
        }

        return activeSlots;
    }
}
