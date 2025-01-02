#pragma once

#include <QComboBox>
#include <QVBoxLayout>

#include "../../../../../include/quest/SaveCharacterPoteintialData.h"

namespace PQH::UI {
    class SlotPropertyTypesEditor: public QWidget {
        Q_OBJECT

    private:
        QVBoxLayout *slotsLyt = nullptr;
        QList<QComboBox *> slotPropertyTypesList;
        std::shared_ptr<SaveCharacterPoteintialData> potentialData;

    public:
        SlotPropertyTypesEditor();

        void setData(const std::shared_ptr<SaveCharacterPoteintialData> &data);
        void refresh() const;
        void apply() const;

    private slots:
        void onSlotTypeChanged(int idx);

    signals:
        void slotTypeChanged(int slotIdx, int type);
    };
}
