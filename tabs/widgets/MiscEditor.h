#pragma once

#include <QSpinBox>

#include "../../include/quest/SerializeData.h"

namespace PQH::UI {
    class MiscEditor: public QWidget {
    private:
        QSpinBox *pokemonBoxCapacity = nullptr;
        QSpinBox *potentialStorageCapacity = nullptr;
        QSpinBox *tickets = nullptr;
        QSpinBox *battery = nullptr;
        std::shared_ptr<CharacterStorage> characterStorage;
        std::shared_ptr<PotentialStorage> potentialStorage;
        std::shared_ptr<Misc> miscData;

    public:
        MiscEditor();

        void setData(const std::shared_ptr<SerializeData> &serializeData);
        void apply() const;
    };
}
