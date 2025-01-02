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
