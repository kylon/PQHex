#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>

#include "NatureTab.h"

namespace PQH::UI {
    NatureTab::NatureTab() {
        const QList<QList<QString>> data {
                {"Hardy", "Ganbariya", "—", "—"},
                {"Lonely", "Samishigari", "Attack", "Defense"},
                {"Brave", "Yuukan", "Attack", "Speed"},
                {"Adamant", "Ijippari", "Attack", "Special Attack"},
                {"Naughty", "Yancha", "Attack", "Special Defense"},
                {"Bold", "Zubutoi", "Defense", "Attack"},
                {"Docile", "Sunao", "—", "—"},
                {"Relaxed", "Nonki", "Defense", "Speed"},
                {"Impish", "Wanpaku", "Defense", "Special Attack"},
                {"Lax", "Noutenki", "Defense", "Special Defense"},
                {"Timid", "Okubyou", "Speed", "Attack"},
                {"Hasty", "Sekkachi", "Speed", "Defense"},
                {"Serious", "Majime", "—", "—"},
                {"Jolly", "Youki", "Speed", "Special Attack"},
                {"Naive", "Mujaki", "Speed", "Special Defense"},
                {"Modest", "Hikaeme", "Special Attack", "Attack"},
                {"Mild", "Ottori", "Special Attack", "Defense"},
                {"Quiet", "Reisei", "Special Attack", "Speed"},
                {"Bashful", "Dereya", "—", "—"},
                {"Rash", "Ukkariya", "Special Attack", "Special Defense"},
                {"Calm", "Odayaka", "Special Defense", "Attack"},
                {"Gentle", "Otonashii", "Special Defense", "Defense"},
                {"Sassy", "Namaiki", "Special Defense", "Speed"},
                {"Careful", "Shinchou", "Special Defense", "Special Attack"},
                {"Quirky", "Kimagure", "—", "—"}
        };
        QVBoxLayout *lyt = new QVBoxLayout();
        QTableWidget *table = new QTableWidget(25, 4);
        int row = 0;

        table->setHorizontalHeaderLabels({"Nature", "Nature Romaji", "Increased", "Decreased"});
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
