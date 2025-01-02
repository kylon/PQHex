#include <QVBoxLayout>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>

#include "StoneWidget.h"
#include "../include/Utils.h"

namespace PQH::UI {
    StoneWidget::StoneWidget(const int skey, const int type, const int rarity, const int value, const int assignedToPkmNo) {
        QVBoxLayout *lyt = new QVBoxLayout();
        QPalette pal = palette();

        iconLbl = new QLabel();
        pkmLbl = new QLabel(iconLbl);
        key = skey;

        pal.setColor(QPalette::WindowText, Qt::darkBlue);
        setFrameShape(QFrame::Box);
        setPalette(pal);
        setCursor(Qt::PointingHandCursor);
        setMaximumSize(64, 64);
        iconLbl->setAlignment(Qt::AlignCenter);
        iconLbl->setPixmap(getStoneIcon(type, rarity, value));
        pkmLbl->setAlignment(Qt::AlignCenter);
        pkmLbl->setFixedSize(20, 20);
        pkmLbl->move(38, 2);
        pkmLbl->setFrameShape(QFrame::Box);
        updateAssignedPkm(assignedToPkmNo);

        if (type <= 1) {
            QGraphicsDropShadowEffect *lshadow = new QGraphicsDropShadowEffect();
            QFont valueFont;
            QPalette valuePal;

            valueLbl = new QLabel(iconLbl);
            valueFont = valueLbl->font();
            valuePal = valueLbl->palette();

            lshadow->setParent(valueLbl);
            lshadow->setOffset(1, 1);
            lshadow->setBlurRadius(1);
            valueLbl->setAlignment(Qt::AlignCenter);
            valueLbl->setNum(value);
            valueLbl->move(getValueLblPosX(value), 40);
            valueFont.setBold(true);
            valueFont.setPointSize(10);
            valuePal.setColor(QPalette::WindowText, Qt::white);
            valueLbl->setFont(valueFont);
            valueLbl->setPalette(valuePal);
            valueLbl->setGraphicsEffect(lshadow);
        }

        lyt->setContentsMargins(0, 0, 0, 0);
        lyt->addWidget(iconLbl);

        setLayout(lyt);
    }

    int StoneWidget::getValueLblPosX(const int value) const {
        if (value < 100)
            return 23;
        else if ( value < 1000)
            return 20;
        else
            return 17;
    }

    void StoneWidget::mouseReleaseEvent(QMouseEvent *e) {
        if (e->button() == Qt::LeftButton)
            emit clicked(key);
    }

    void StoneWidget::updateAssignedPkm(const int assignedToPkmNo) const {
        pkmLbl->setVisible(assignedToPkmNo != -1);

        if (assignedToPkmNo != -1)
            pkmLbl->setPixmap(QPixmap(QString(":/pq%1").arg(assignedToPkmNo)).scaled(20, 20));
    }
}
