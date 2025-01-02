#pragma once

#include <QComboBox>
#include <QVBoxLayout>

#include "../../../../../include/quest/CharacterStorage.h"
#include "../../../../../include/quest/SaveCharacterPoteintialData.h"
#include "../../../../../include/quest/PotentialStorage.h"

namespace PQH::UI {
    class AttachStoneStorageIDEditor: public QWidget {
        Q_OBJECT

    private:
        QVBoxLayout *stoneStoreIDLyt = nullptr;
        QList<QComboBox *> attachStoneStorageIDList;
        std::shared_ptr<SaveCharacterPoteintialData> potentialData;
        std::shared_ptr<PotentialStorage> potentialStorage;
        std::shared_ptr<CharacterStorage> characterStorage;
        int pkmKey;

        void updateStoneCombos() const;
        [[nodiscard]] QString getStoneLabel(const std::shared_ptr<StoneData> &stone) const;
        void updateStoneLabel(int key) const;
        void removeStoneFromSlot(int pkey, int stoneKey) const;

    public:
        AttachStoneStorageIDEditor();

        void setData(const std::shared_ptr<CharacterStorage> &characterStorageData, const std::shared_ptr<PotentialStorage> &potentialStorageData, int pkey);
        void updateComboStones(int comboIdx, int slotType) const;
        void refresh() const;
        void apply();

    signals:
        void stoneAssigned(int stoneKey, int pkmKey);
    };
}
