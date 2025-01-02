#include <QVBoxLayout>
#include <QLabel>

#include "PokemonCharacterPotentialEditor.h"

namespace PQH::UI {
    PokemonCharacterPotentialEditor::PokemonCharacterPotentialEditor() {
        QVBoxLayout *lyt = new QVBoxLayout();
        nextActivateSlotIndex = new QSpinBox();
        nextSlotProgress = new QDoubleSpinBox();
        bingoPropertyIndices = new QSpinBox();
        activeSlotsEditor = new ActiveSlotsEditor();
        attachStoneStorageIdEditor = new AttachStoneStorageIDEditor();
        attachSkillStoneStorageIdEditor = new AttachSkillStoneStorageIDEditor();
        slotPropertyTypesEditor = new SlotPropertyTypesEditor();
        potentialSkillDataEditor = new PotentialSkillDataEditor();

        nextActivateSlotIndex->setRange(-1, 8);
        nextSlotProgress->setRange(0, 1);
        nextSlotProgress->setSingleStep(0.1f);
        bingoPropertyIndices->setRange(0, INT32_MAX);
        lyt->setContentsMargins(0, 0, 0, 0);
        lyt->addItem(new QSpacerItem(1, 8, QSizePolicy::Expanding, QSizePolicy::Fixed));
        lyt->addWidget(new QLabel("Active slots"));
        lyt->addWidget(activeSlotsEditor);
        lyt->addWidget(new QLabel("Next active slot index"));
        lyt->addWidget(nextActivateSlotIndex);
        lyt->addWidget(new QLabel("Next slot progress"));
        lyt->addWidget(nextSlotProgress);
        lyt->addWidget(new QLabel("Bingo property indices"));
        lyt->addWidget(bingoPropertyIndices);
        lyt->addWidget(attachStoneStorageIdEditor);
        lyt->addWidget(attachSkillStoneStorageIdEditor);
        lyt->addWidget(slotPropertyTypesEditor);
        lyt->addWidget(potentialSkillDataEditor);

        setLayout(lyt);

        QObject::connect(attachStoneStorageIdEditor, &AttachStoneStorageIDEditor::stoneAssigned, this, &PokemonCharacterPotentialEditor::onStoneAssigned);
        QObject::connect(attachSkillStoneStorageIdEditor, &AttachSkillStoneStorageIDEditor::skillStoneAssigned, this, &PokemonCharacterPotentialEditor::onSkillStoneAssigned);
        QObject::connect(slotPropertyTypesEditor, &SlotPropertyTypesEditor::slotTypeChanged, this, &PokemonCharacterPotentialEditor::onSlotTypeChanged);
    }

    void PokemonCharacterPotentialEditor::setPotential(const std::shared_ptr<PotentialStorage> &potentialStorage, const std::shared_ptr<CharacterStorage> &characterStorage, const int key) {
        const std::shared_ptr<SaveCharacterData> pkm = characterStorage->characterDataDictionary[key]->data;

        potentialData = pkm->potential;

        activeSlotsEditor->setData(*potentialData->activeSlots);
        attachStoneStorageIdEditor->setData(characterStorage, potentialStorage, key);
        attachSkillStoneStorageIdEditor->setData(characterStorage, potentialStorage, key);
        slotPropertyTypesEditor->setData(potentialData);
        potentialSkillDataEditor->setData(potentialData, *pkm->monsterNo);
        refresh();
    }

    void PokemonCharacterPotentialEditor::resetSlotProgress() const {
        nextActivateSlotIndex->setValue(-1);
        nextSlotProgress->setValue(0);
    }

    void PokemonCharacterPotentialEditor::setPokemon(const int dexNo) const {
        potentialSkillDataEditor->updateMonsterNo(dexNo);
    }

    void PokemonCharacterPotentialEditor::refresh() const {
        activeSlotsEditor->setData(*potentialData->activeSlots);
        nextActivateSlotIndex->setValue(*potentialData->nextActivateSlotIndex);
        nextSlotProgress->setValue(*potentialData->nextSlotProgress);
        bingoPropertyIndices->setValue(*potentialData->bingoPropertyIndices);
        attachStoneStorageIdEditor->refresh();
        attachSkillStoneStorageIdEditor->refresh();
        slotPropertyTypesEditor->refresh();
        potentialSkillDataEditor->refresh();
    }

    void PokemonCharacterPotentialEditor::apply() const {
        *potentialData->activeSlots = activeSlotsEditor->getActiveSlots();
        *potentialData->nextActivateSlotIndex = nextActivateSlotIndex->value();
        *potentialData->nextSlotProgress = nextSlotProgress->value();
        *potentialData->bingoPropertyIndices = bingoPropertyIndices->value();

        attachStoneStorageIdEditor->apply();
        attachSkillStoneStorageIdEditor->apply();
        slotPropertyTypesEditor->apply();
        potentialSkillDataEditor->apply();
    }

    void PokemonCharacterPotentialEditor::onSlotTypeChanged(const int slotIdx, const int type) const {
        attachStoneStorageIdEditor->updateComboStones(slotIdx, type);
        attachStoneStorageIdEditor->refresh();
    }

    void PokemonCharacterPotentialEditor::onStoneAssigned(const int stoneKey, const int pkmKey) {
        emit stoneAssigned(stoneKey, pkmKey);
    }

    void PokemonCharacterPotentialEditor::onSkillStoneAssigned(const int stoneKey, const int pkmKey) {
        emit skillStoneAssigned(stoneKey, pkmKey);
    }
}
