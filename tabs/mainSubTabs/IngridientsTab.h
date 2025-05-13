#pragma once

#include <QPushButton>
#include <QSpinBox>

#include "../include/MainSubWidget.h"
#include "../../include/quest/ItemStorage.h"

namespace PQH::UI {
    class IngridientsTab final: public MainSubWidget {
        Q_OBJECT

    private:
        QPushButton *maxAll = nullptr;
        QPushButton *saveBtn = nullptr;
        QList<QSpinBox *> ingridients;

        [[nodiscard]] int getIngridientCount(const std::shared_ptr<ItemStorage> &itemStorage, int id) const;

    public:
        IngridientsTab();

        void setData(const std::shared_ptr<ItemStorage> &itemStorage) const;

    private slots:
        void onMaxAllClicked() const;
        void onSaveBtnClicked();

    signals:
        void ingridientsSaved(const QList<int> &list);
    };
}
