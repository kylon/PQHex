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
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>

#include "NatureTab.h"

namespace PQH::UI {
    using namespace Qt::StringLiterals;

    NatureTab::NatureTab() {
        const QList<QList<QString>> data {
                {u"Hardy"_s, u"Ganbariya"_s, u"—"_s, u"—"_s},
                {u"Lonely"_s, u"Samishigari"_s, u"Attack"_s, u"Defense"_s},
                {u"Brave"_s, u"Yuukan"_s, u"Attack"_s, u"Speed"_s},
                {u"Adamant"_s, u"Ijippari"_s, u"Attack"_s, u"Special Attack"_s},
                {u"Naughty"_s, u"Yancha"_s, u"Attack"_s, u"Special Defense"_s},
                {u"Bold"_s, u"Zubutoi"_s, u"Defense"_s, u"Attack"_s},
                {u"Docile"_s, u"Sunao"_s, u"—"_s, u"—"_s},
                {u"Relaxed"_s, u"Nonki"_s, u"Defense"_s, u"Speed"_s},
                {u"Impish"_s, u"Wanpaku"_s, u"Defense"_s, u"Special Attack"_s},
                {u"Lax"_s, u"Noutenki"_s, u"Defense"_s, u"Special Defense"_s},
                {u"Timid"_s, u"Okubyou"_s, u"Speed"_s, u"Attack"_s},
                {u"Hasty"_s, u"Sekkachi"_s, u"Speed"_s, u"Defense"_s},
                {u"Serious"_s, u"Majime"_s, u"—"_s, u"—"_s},
                {u"Jolly"_s, u"Youki"_s, u"Speed"_s, u"Special Attack"_s},
                {u"Naive"_s, u"Mujaki"_s, u"Speed"_s, u"Special Defense"_s},
                {u"Modest"_s, u"Hikaeme"_s, u"Special Attack"_s, u"Attack"_s},
                {u"Mild"_s, u"Ottori"_s, u"Special Attack"_s, u"Defense"_s},
                {u"Quiet"_s, u"Reisei"_s, u"Special Attack"_s, u"Speed"_s},
                {u"Bashful"_s, u"Dereya"_s, u"—"_s, u"—"_s},
                {u"Rash"_s, u"Ukkariya"_s, u"Special Attack"_s, u"Special Defense"_s},
                {u"Calm"_s, u"Odayaka"_s, u"Special Defense"_s, u"Attack"_s},
                {u"Gentle"_s, u"Otonashii"_s, u"Special Defense"_s, u"Defense"_s},
                {u"Sassy"_s, u"Namaiki"_s, u"Special Defense"_s, u"Speed"_s},
                {u"Careful"_s, u"Shinchou"_s, u"Special Defense"_s, u"Special Attack"_s},
                {u"Quirky"_s, u"Kimagure"_s, u"—"_s, u"—"_s}
        };
        QVBoxLayout *lyt = new QVBoxLayout();
        QTableWidget *table = new QTableWidget(25, 4);
        int row = 0;

        table->setHorizontalHeaderLabels({u"Nature"_s, u"Nature Romaji"_s, u"Increased"_s, u"Decreased"_s});
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        lyt->addWidget(table);

        for (const QList<QString> &tableData: data) {
            int col = 0;

            for (const QString &item: tableData) {
                QTableWidgetItem *titem = new QTableWidgetItem(item);

                titem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                table->setItem(row, col++, titem);
            }

            ++row;
        }

        setLayout(lyt);
    }
}
