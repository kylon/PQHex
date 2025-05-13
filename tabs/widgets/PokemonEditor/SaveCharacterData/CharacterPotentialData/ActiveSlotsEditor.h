#pragma once

#include <QCheckBox>

#include "../../../../include/GridWidget.h"
#include "../../../../../include/TypeAliases.h"

namespace PQH::UI {
    class ActiveSlotsEditor final: public GridWidget {
    private:
        QList<QCheckBox *> slotsList;

    public:
        ActiveSlotsEditor();

        void setData(u16 activeSlotsFlag) const;
        [[nodiscard]] u16 getActiveSlots() const;
    };
}
