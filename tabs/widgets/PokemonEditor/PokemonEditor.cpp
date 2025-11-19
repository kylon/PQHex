/*
 * This file is part of PQHex.
 * Copyright (C) 2025 kylon
 *
 * PQHex is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PQHex is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "PokemonEditor.h"

namespace PQH::UI {
    PokemonEditor::PokemonEditor() {
        baseDataEditor = new PokemonBaseDataEditor();
        characterPotentialEditor = new PokemonCharacterPotentialEditor();
        saveBtn = new QPushButton("Apply");

        scrollLyt->addWidget(baseDataEditor);
        scrollLyt->addWidget(characterPotentialEditor);
        lyt->addWidget(saveBtn);

        QObject::connect(saveBtn, &QPushButton::clicked, this, &PokemonEditor::onSaveBtnClicked);
        QObject::connect(baseDataEditor, &PokemonBaseDataEditor::pokemonChanged, this, &PokemonEditor::onPokemonChanged);
        QObject::connect(baseDataEditor, &PokemonBaseDataEditor::coreDataChanged, this, &PokemonEditor::onCoreDataChanged);
        QObject::connect(baseDataEditor, &PokemonBaseDataEditor::pokemonMaxLevel, this, &PokemonEditor::onPokemonMaxLevel);
        QObject::connect(baseDataEditor, &PokemonBaseDataEditor::updatePokedex, this, &PokemonEditor::onPokedexUpdate);
        QObject::connect(characterPotentialEditor, &PokemonCharacterPotentialEditor::stoneAssigned, this, &PokemonEditor::onStoneAssigned);
        QObject::connect(characterPotentialEditor, &PokemonCharacterPotentialEditor::skillStoneAssigned, this, &PokemonEditor::onSkillStoneAssigned);
    }

    void PokemonEditor::refreshEditor() const {
        resetScroolbar();
        baseDataEditor->refresh();
        characterPotentialEditor->refresh();
    }

    void PokemonEditor::setPokemon(const std::shared_ptr<CharacterStorage> &characterStorage, const std::shared_ptr<PotentialStorage> &potentialStorage, const int key) const {
        baseDataEditor->setPokemon(characterStorage->characterDataDictionary[key]->data, key);
        characterPotentialEditor->setPotential(potentialStorage, characterStorage, key);
        refreshEditor();
    }

    void PokemonEditor::onSaveBtnClicked() {
        saveBtn->setEnabled(false);
        baseDataEditor->apply();
        characterPotentialEditor->apply();
        emit pokemonEdited(baseDataEditor->getMonsterNo(), baseDataEditor->getShinyStatus());
        refreshEditor();
        saveBtn->setEnabled(true);
    }

    void PokemonEditor::onCoreDataChanged(const int key) {
        emit coreDataChanged(key);
    }

    void PokemonEditor::onPokemonChanged(const int dexNo) const {
        characterPotentialEditor->setPokemon(dexNo);
    }

    void PokemonEditor::onPokemonMaxLevel() const {
        characterPotentialEditor->resetSlotProgress();
    }

    void PokemonEditor::onPokedexUpdate(const int dexNo) {
        emit updatePokedex(dexNo);
    }

    void PokemonEditor::onStoneAssigned(const int stoneKey, const int pkmKey) {
        emit stoneAssigned(stoneKey, pkmKey);
    }

    void PokemonEditor::onSkillStoneAssigned(int stoneKey, int pkmKey) {
        emit skillStoneAssigned(stoneKey, pkmKey);
    }
}
