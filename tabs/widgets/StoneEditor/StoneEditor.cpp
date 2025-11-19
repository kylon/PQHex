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
#include "StoneEditor.h"

namespace PQH::UI {
    StoneEditor::StoneEditor() {
        stoneDataEditor = new StoneDataEditor();
        stoneBonusEditor = new StoneBonusEditor();
        saveBtn = new QPushButton("Apply");

        saveBtn->setEnabled(false);

        scrollLyt->addWidget(stoneDataEditor);
        scrollLyt->addWidget(stoneBonusEditor);
        scrollLyt->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
        lyt->addWidget(saveBtn);

        QObject::connect(saveBtn, &QPushButton::clicked, this, &StoneEditor::onSaveBtnClicked);
    }

    void StoneEditor::setStone(const std::shared_ptr<PowerStone> &powerStone, const int key) const {
        skey = key;
        stoneDataEditor->setStone(powerStone);
        stoneBonusEditor->setData(powerStone);
        resetScroolbar();
        saveBtn->setEnabled(true);
    }

    void StoneEditor::onSaveBtnClicked() {
        saveBtn->setEnabled(false);
        stoneDataEditor->apply();
        stoneBonusEditor->apply();
        emit stoneEdited(skey);
    }
}
