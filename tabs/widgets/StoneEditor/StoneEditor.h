#pragma once

#include <QPushButton>

#include "../../include/MainSubWidget.h"
#include "StoneData/StoneDataEditor.h"
#include "StoneData/StoneBonusEditor.h"

namespace PQH::UI {
    class StoneEditor: public MainSubWidget {
        Q_OBJECT

    private:
        StoneDataEditor *stoneDataEditor = nullptr;
        StoneBonusEditor *stoneBonusEditor = nullptr;
        QPushButton *saveBtn = nullptr;
        mutable int skey;

    public:
        StoneEditor();

        void setStone(const std::shared_ptr<PowerStone> &powerStone, int key) const;

    private slots:
        void onSaveBtnClicked();

    signals:
        void stoneEdited(int key);
    };
}
