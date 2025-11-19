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
#include <QLabel>

#include "PokedexTab.h"

namespace PQH::UI {
    PokedexTab::PokedexTab() {
        for (int i=0; i<151; ++i) {
            QHBoxLayout *dexLyt = new QHBoxLayout();
            QSpinBox *count = new QSpinBox();
            QLabel *icon = new QLabel();

            dexLyt->setAlignment(Qt::AlignCenter);
            icon->setPixmap(QPixmap(QString(":/pk%1").arg(i+1)).scaled(120, 120));
            count->setRange(0, 999);
            count->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

            dexLyt->addWidget(icon);
            dexLyt->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred));
            dexLyt->addWidget(count);
            dexLyt->addWidget(new QLabel("befriended"));
            scrollLyt->addLayout(dexLyt);
            scoutCounts.append(count);
        }

        saveBtn = new QPushButton("Apply");

        saveBtn->setEnabled(false);
        lyt->addWidget(saveBtn);

        QObject::connect(saveBtn, &QPushButton::clicked, this, &PokedexTab::onSaveBtnClicked);
    }

    void PokedexTab::setData(const std::shared_ptr<PokemonMemory> &data) {
        pokemonMemory = data;

        saveBtn->setEnabled(true);
        refresh();
    }

    void PokedexTab::updateEncounters(const int dexNo) const {
        const int idx = dexNo - 1;

        *(pokemonMemory->scoutCounts[idx]) += 1;
        scoutCounts[idx]->setValue(*(pokemonMemory->scoutCounts[idx]));
    }

    void PokedexTab::refresh() const {
        for (int i=0,l=scoutCounts.size(); i<l; ++i)
            scoutCounts[i]->setValue(*pokemonMemory->scoutCounts[i]);
    }

    void PokedexTab::onSaveBtnClicked() const {
        saveBtn->setEnabled(false);

        for (int i=0,l=scoutCounts.size(); i<l; ++i)
            *(pokemonMemory->scoutCounts[i]) = scoutCounts[i]->value();

        refresh();
        saveBtn->setEnabled(true);
    }
}
