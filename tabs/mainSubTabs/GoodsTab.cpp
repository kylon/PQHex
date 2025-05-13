#include <QLabel>

#include "GoodsTab.h"

namespace PQH::UI {
    GoodsTab::GoodsTab() {
        for (const std::pair<std::string_view, int> &good: goodsData) {
            QHBoxLayout *goodLyt = new QHBoxLayout();
            QCheckBox *goodck = new QCheckBox();
            QLabel *icon = new QLabel();
            QLabel *lbl = new QLabel();
            QFont lblFont = lbl->font();

            goodLyt->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            goodck->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
            icon->setPixmap(QPixmap(QString(":/%1").arg(good.second)));
            icon->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
            lbl->setText(good.first.data());
            lbl->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
            lblFont.setPointSize(12);
            lbl->setFont(lblFont);

            goodLyt->addWidget(goodck);
            goodLyt->addWidget(icon);
            goodLyt->addWidget(lbl);
            scrollLyt->addLayout(goodLyt);
            goods.append(goodck);
        }

        ownAll = new QPushButton("Own all");
        saveBtn = new QPushButton("Apply");

        ownAll->setEnabled(false);
        saveBtn->setEnabled(false);

        lyt->addWidget(ownAll);
        lyt->addWidget(saveBtn);

        QObject::connect(ownAll, &QPushButton::clicked, this, &GoodsTab::onOwnAllClicked);
        QObject::connect(saveBtn, &QPushButton::clicked, this, &GoodsTab::onSaveBtnClicked);
    }

    void GoodsTab::setData(const std::shared_ptr<Goods> &goodsObj) {
        decorationsData = goodsObj;

        for (int i=0,l=goodsData.size(); i<l; ++i)
            goods[i]->setChecked(decorationsData->hasDatas.contains(goodsData[i].second));

        ownAll->setEnabled(true);
        saveBtn->setEnabled(true);
    }

    void GoodsTab::onOwnAllClicked() const {
        for (QCheckBox *good: goods)
            good->setChecked(true);
    }

    void GoodsTab::onSaveBtnClicked() {
        ownAll->setEnabled(false);
        saveBtn->setEnabled(false);

        for (int i=0,l=goodsData.size(); i<l; ++i) {
            if (!goods[i]->isChecked()) {
                decorationsData->hasDatas.erase(goodsData[i].second);
                decorationsData->placementDatas.erase(goodsData[i].second);

            } else if (!decorationsData->hasDatas.contains(goodsData[i].second)) {
                std::shared_ptr<GoodsManageData> goodsManageData = std::make_shared<GoodsManageData>();

                goodsManageData->id = goodsData[i].second;
                goodsManageData->isNew = true;

                decorationsData->hasDatas.insert({goodsData[i].second, goodsManageData});
            }
        }

        emit goodsSaved();
    }
}
