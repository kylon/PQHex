#pragma once

#include <QDoubleSpinBox>

#include "ActiveSlotsEditor.h"
#include "AttachStoneStorageIDEditor.h"
#include "AttachSkillStoneStorageIDEditor.h"
#include "SlotPropertyTypesEditor.h"
#include "PotentialSkillDataEditor.h"

namespace PQH::UI {
    class PokemonCharacterPotentialEditor: public QWidget {
        Q_OBJECT

    private:
        QSpinBox *nextActivateSlotIndex = nullptr;
        QDoubleSpinBox *nextSlotProgress = nullptr;
        QSpinBox *bingoPropertyIndices = nullptr;
        ActiveSlotsEditor *activeSlotsEditor = nullptr;
        AttachStoneStorageIDEditor *attachStoneStorageIdEditor = nullptr;
        AttachSkillStoneStorageIDEditor *attachSkillStoneStorageIdEditor = nullptr;
        SlotPropertyTypesEditor *slotPropertyTypesEditor = nullptr;
        PotentialSkillDataEditor *potentialSkillDataEditor = nullptr;
        std::shared_ptr<SaveCharacterPoteintialData> potentialData;

    public:
        PokemonCharacterPotentialEditor();

        void setPotential(const std::shared_ptr<PotentialStorage> &potentialStorage, const std::shared_ptr<CharacterStorage> &characterStorage, int key);
        void resetSlotProgress() const;
        void setPokemon(int dexNo) const;
        void refresh() const;
        void apply() const;

    private slots:
        void onSlotTypeChanged(int slotIdx, int type) const;
        void onStoneAssigned(int stoneKey, int pkmKey);
        void onSkillStoneAssigned(int stoneKey, int pkmKey);

    signals:
        void stoneAssigned(int stoneKey, int pkmKey);
        void skillStoneAssigned(int stoneKey, int pkmKey);
    };
}
