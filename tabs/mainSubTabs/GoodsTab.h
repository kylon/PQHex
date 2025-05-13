#pragma once

#include <QCheckBox>
#include <QPushButton>

#include "../include/MainSubWidget.h"
#include "../../include/quest/Goods.h"

namespace PQH::UI {
    class GoodsTab final: public MainSubWidget {
        Q_OBJECT

    private:
        static constexpr std::array<std::pair<std::string_view, int>, 39> goodsData {{
            {"Pikachu Arch", 100}, {"Mewtwo Arch", 101}, {"Eevee Arch", 102},
            {"Perfect Pair Statue", 103}, {"Charizard Torch", 200}, {"Lapras Pool", 201},
            {"Venusaur Planter", 202}, {"Dodrio Tent", 203}, {"Blastoise Fountain", 204},
            {"Mechanical Tauros", 205}, {"Snorlax Lounger", 206}, {"Kangaskhan Swing Chair", 207},
            {"Pikachu Surfboard", 300}, {"Victreebel Golf Bag", 301}, {"Fearow Weathervane", 302},
            {"Meowth Balloon", 303}, {"Ditto Balloon", 304}, {"Gengar Balloon", 305},
            {"Bulbasaur Flag", 306}, {"Charmander Flag", 307}, {"Squirtle Flag", 308},
            {"Flareon Cusheon", 309}, {"Vaporeon Cusheon", 310}, {"Jolteon Cusheon", 311},
            {"Prolific Statue", 312}, {"Spring Showers Statue", 313}, {"Flourishing Statue", 314},
            {"Tranquility Statue", 315}, {"Gentle Breeze Statue", 316}, {"Abundance Statue", 317},
            {"Purification Statue", 318}, {"Burning Mane Statue", 319}, {"Longevity Statue", 320},
            {"Reverent Statue", 321}, {"Poké Ball Model", 400}, {"Great Ball Model", 401},
            {"Ultra Ball Model", 402}, {"Premier Ball Model", 403}, {"Master Ball Model", 404}
        }};
        QList<QCheckBox *> goods;
        QPushButton *ownAll = nullptr;
        QPushButton *saveBtn = nullptr;
        std::shared_ptr<Goods> decorationsData;

    public:
        GoodsTab();

        void setData(const std::shared_ptr<Goods> &goodsObj);

    private slots:
        void onOwnAllClicked() const;
        void onSaveBtnClicked();

    signals:
        void goodsSaved();
    };
}
