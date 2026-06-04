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

#include "IngridientsTab.h"

namespace PQH::UI {
    using namespace Qt::StringLiterals;

    IngridientsTab::IngridientsTab() {
        const QList<QString> icons = {
            u":/tinymushroom"_s, u":/bigroot"_s, u":/blukberry"_s, u":/icyrock"_s,
            u":/apricorn"_s, u":/honey"_s, u":/fossil"_s, u":/balmmushroom"_s,
            u":/rainbowmatter"_s, u":/mysticalshell"_s
        };
        const QList<QString> names = {
            u"Tiny mushroom"_s, u"Big root"_s, u"Bluk berry"_s, u"Icy rock"_s, u"Apricorn"_s,
            u"Honey"_s, u"Fossil"_s, u"Balm mushroom"_s, u"Rainbow matter"_s, u"Mystical shell"_s
        };

        for (int i=0; i<10; ++i) {
            QHBoxLayout *ingrientLyt = new QHBoxLayout();
            QLabel *ingridientIcon = new QLabel();
            QSpinBox *ingridient = new QSpinBox();

            ingridient->setRange(0, 999);
            ingridientIcon->setPixmap(QPixmap(icons[i]));
            ingridientIcon->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
            ingrientLyt->addWidget(ingridientIcon);
            ingrientLyt->addWidget(new QLabel(names[i]));
            ingrientLyt->addWidget(ingridient);
            scrollLyt->addLayout(ingrientLyt);
            ingridients.append(ingridient);
        }

        maxAll = new QPushButton(u"Max all"_s);
        saveBtn = new QPushButton(u"Apply"_s);

        maxAll->setEnabled(false);
        saveBtn->setEnabled(false);

        lyt->addWidget(maxAll);
        lyt->addWidget(saveBtn);

        QObject::connect(maxAll, &QPushButton::clicked, this, &IngridientsTab::onMaxAllClicked);
        QObject::connect(saveBtn, &QPushButton::clicked, this, &IngridientsTab::onSaveBtnClicked);
    }

    int IngridientsTab::getIngridientCount(const std::shared_ptr<ItemStorage> &itemStorage, const int id) const {
        for (const std::shared_ptr<Core> &ing: itemStorage->datas) {
            if (*ing->id == id)
                return *ing->num;
        }

        return 0;
    }

    void IngridientsTab::setData(const std::shared_ptr<ItemStorage> &itemStorage) const {
        for (int i=0,l=ingridients.size(); i<l; ++i)
            ingridients[i]->setValue(getIngridientCount(itemStorage, i+1));

        maxAll->setEnabled(true);
        saveBtn->setEnabled(true);
    }

    void IngridientsTab::onSaveBtnClicked() {
        maxAll->setEnabled(false);
        saveBtn->setEnabled(false);

        QList<int> counts;

        for (const QSpinBox *ing: ingridients)
            counts.append(ing->value());

        emit ingridientsSaved(counts);
    }

    void IngridientsTab::onMaxAllClicked() const {
        for (QSpinBox *ing: ingridients)
            ing->setValue(ing->maximum());
    }
}
