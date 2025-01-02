#pragma once

#include <QFrame>
#include <QLabel>

namespace PQH::UI {
    class PokemonWidget: public QFrame {
        Q_OBJECT

    private:
        QLabel *shinySymbol = nullptr;
        QLabel *partySymbol = nullptr;
        QLabel *iconLbl = nullptr;
        int key;

    protected:
        void mouseReleaseEvent(QMouseEvent *e) override;

    public:
        PokemonWidget(int pkey, bool shiny, int dexNo);

        void setSelected() { setLineWidth(2); }
        void setUnselected() { setLineWidth(1); }
        void setInParty(const bool inParty) const { partySymbol->setVisible(inParty); }

        void updateWidget(bool shiny, int dexNo);

    signals:
        void clicked(int key, bool shiny, bool inParty);
    };
}
