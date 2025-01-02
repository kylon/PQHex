#pragma once

#include <QWidget>
#include <QGridLayout>

namespace PQH::UI {
    class GridWidget: public QWidget {
    private:
        int itemsPerRow;

    protected:
        QGridLayout *gridLyt = nullptr;
        int column = -1;
        int row = 0;

        void setNextSlot() {
            if (++column < itemsPerRow)
                return;

            column = 0;
            ++row;
        }

        void resetSlot() {
            column = -1;
            row = 0;
        }

    public:
        explicit GridWidget(const int itemsPerRow) {
            this->itemsPerRow = itemsPerRow;
            gridLyt = new QGridLayout();

            gridLyt->setAlignment(Qt::AlignLeft | Qt::AlignTop);
            setLayout(gridLyt);
        }
    };
}
