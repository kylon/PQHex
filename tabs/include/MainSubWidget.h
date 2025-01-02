#pragma once

#include <QScrollBar>
#include <QVBoxLayout>

#include "Utils.h"

namespace PQH::UI {
    class MainSubWidget: public QWidget {
    private:
        QScrollArea *scrollArea = nullptr;

    protected:
        QVBoxLayout *scrollLyt = nullptr;
        QVBoxLayout *lyt = nullptr;

        void resetScroolbar() const { scrollArea->verticalScrollBar()->setValue(0); }

    public:
        MainSubWidget() {
            scrollArea = createScrollArea();
            scrollLyt = new QVBoxLayout();
            lyt = new QVBoxLayout();

            scrollArea->widget()->setLayout(scrollLyt);
            lyt->addWidget(scrollArea);

            setLayout(lyt);
        }
    };
}
