#pragma once

#include <QFrame>
#include <QLabel>

namespace PQH::UI {
    class StoneWidget: public QFrame {
        Q_OBJECT

    private:
        QLabel *iconLbl = nullptr;
        QLabel *pkmLbl = nullptr;
        QLabel *valueLbl = nullptr;
        int key;

        [[nodiscard]] int getValueLblPosX(int value) const;

    protected:
        void mouseReleaseEvent(QMouseEvent *e) override;

    public:
        StoneWidget(int skey, int type, int rarity, int value, int assignedToPkmNo);

        void setSelected() { setLineWidth(2); }
        void setUnselected() { setLineWidth(1); }

        void updateAssignedPkm(int assignedToPkmNo) const;

    signals:
        void clicked(int key);
    };
}
