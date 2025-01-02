#include <QLabel>

#include "IngridientsTab.h"

namespace PQH::UI {
    IngridientsTab::IngridientsTab() {
        const QString icons[] = {
            ":/tinymushroom", ":/bigroot", ":/blukberry", ":/icyrock",
            ":/apricorn", ":/honey", ":/fossil", ":/balmmushroom",
            ":/rainbowmatter", ":/mysticalshell"
        };
        const QString names[] = {
            "Tiny mushroom", "Big root", "Bluk berry", "Icy rock", "Apricorn",
            "Honey", "Fossil", "Balm mushroom", "Rainbow matter", "Mystical shell"
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

        maxAll = new QPushButton("Max all");
        saveBtn = new QPushButton("Apply");

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
