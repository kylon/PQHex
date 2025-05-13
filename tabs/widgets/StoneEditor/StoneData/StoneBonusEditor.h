#pragma once

#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>

#include "../../../../include/quest/PowerStone.h"

namespace PQH::UI {
    class StoneBonusEditor final: public QWidget {
        Q_OBJECT

    private:
        static constexpr std::array<std::pair<std::string_view, int>, 18> bonusTypeList {{
            {"Natural Healing (%)", 14}, {"Movement Speed (%)", 23}, {"Critical Hit Rate (%)", 26},
            {"Critical Hit Damage (%)", 27}, {"Time to Recover (%)", 28}, {"HP upon Recovery (%)", 29},
            {"Hit Healing (%)", 40}, {"Healing from K.O. (%)", 41}, {"Resistant to ↓ Effects (%)", 48},
            {"Resistant to Status Conditions (%)", 49},

            // skill bonus types
            {"Number of move repetitions", 6}, {"Move wait time (%)", 5}, {"Move's number of shots", 12},
            {"Move's ATK (%)", 11}, {"Effect ↑ duration (%)", 33}, {"Effect ↓ duration (%)", 35},
            {"↑ Effects for buddies (%)", 39}, {"Attack width", 9}
        }};
        QCheckBox *typeFilter = nullptr;
        QList<std::pair<QComboBox *, QLineEdit *>> bonusInptList;
        std::shared_ptr<PowerStone> powerStone;

        void setBonusTypeCombos(bool filter) const;
        [[nodiscard]] std::shared_ptr<PowerStoneBonus> makeStoneBonus(int type, float val) const;

    public:
        StoneBonusEditor();

        void setData(const std::shared_ptr<PowerStone> &stone);
        void apply() const;

    private slots:
        void onFilterChanged(Qt::CheckState state) const;
    };
}
