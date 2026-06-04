/*
 * This file is part of PQHex.
 * Copyright (C) 2025 kylon
 *
 * PQHex is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PQHex is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <QRandomGenerator>
#include <QVBoxLayout>
#include <QLabel>

#include "PokemonBaseDataEditor.h"

namespace PQH::UI {
    using namespace Qt::StringLiterals;

    PokemonBaseDataEditor::PokemonBaseDataEditor() {
        const QList<QString> natureList {
                u"Hardy"_s, u"Lonely"_s, u"Brave"_s, u"Adamant"_s, u"Naughty"_s, u"Bold"_s, u"Docile"_s, u"Relaxed"_s,
                u"Impish"_s, u"Lax"_s, u"Timid"_s, u"Hasty"_s, u"Serious"_s, u"Jolly"_s, u"Naive"_s, u"Modest"_s,
                u"Mild"_s, u"Quiet"_s, u"Bashful"_s, u"Rash"_s, u"Calm"_s, u"Gentle"_s, u"Sassy"_s, u"Careful"_s, u"Quirky"_s
        };
        const QList<QString> pokemonList = {
                u"Bulbasaur"_s, u"Ivysaur"_s, u"Venusaur"_s, u"Charmander"_s, u"Charmeleon"_s, u"Charizard"_s, u"Squirtle"_s,
                u"Wartortle"_s, u"Blastoise"_s, u"Caterpie"_s, u"Metapod"_s, u"Butterfree"_s, u"Weedle"_s, u"Kakuna"_s, u"Beedrill"_s,
                u"Pidgey"_s, u"Pidgeotto"_s, u"Pidgeot"_s, u"Rattata"_s, u"Raticate"_s, u"Spearow"_s, u"Fearow"_s, u"Ekans"_s,
                u"Arbok"_s, u"Pikachu"_s, u"Raichu"_s, u"Sandshrew"_s, u"Sandslash"_s, "Nidoran (Female)", u"Nidorina"_s,
                u"Nidoqueen"_s, "Nidoran (Male)", u"Nidorino"_s, u"Nidoking"_s, u"Clefairy"_s, u"Clefable"_s, u"Vulpix"_s,
                u"Ninetales"_s, u"Jigglypuff"_s, u"Wigglytuff"_s, u"Zubat"_s, u"Golbat"_s, u"Oddish"_s, u"Gloom"_s,u"Vileplume"_s,
                u"Paras"_s, u"Parasect"_s, u"Venonat"_s, u"Venomoth"_s, u"Diglett"_s, u"Dugtrio"_s, u"Meowth"_s, u"Persian"_s,
                u"Psyduck"_s, u"Golduck"_s, u"Mankey"_s, u"Primeape"_s, u"Growlithe"_s, u"Arcanine"_s, u"Poliwag"_s, u"Poliwhirl"_s,
                u"Poliwrath"_s, u"Abra"_s, u"Kadabra"_s, u"Alakazam"_s, u"Machop"_s, u"Machoke"_s, u"Machamp"_s, u"Bellsprout"_s,
                u"Weepinbell"_s, u"Victreebel"_s, u"Tentacool"_s, u"Tentacruel"_s, u"Geodude"_s, u"Graveler"_s, u"Golem"_s, u"Ponyta"_s,
                u"Rapidash"_s, u"Slowpoke"_s, u"Slowbro"_s, u"Magnemite"_s, u"Magneton"_s, "Farfetch'd", u"Doduo"_s, u"Dodrio"_s, u"Seel"_s,
                u"Dewgong"_s, u"Grimer"_s, u"Muk"_s, u"Shellder"_s, u"Cloyster"_s, u"Gastly"_s, u"Haunter"_s, u"Gengar"_s, u"Onix"_s, u"Drowzee"_s,
                u"Hypno"_s, u"Krabby"_s, u"Kingler"_s, u"Voltorb"_s, u"Electrode"_s, u"Exeggcute"_s, u"Exeggutor"_s, u"Cubone"_s, u"Marowak"_s,
                u"Hitmonlee"_s, u"Hitmonchan"_s, u"Lickitung"_s, u"Koffing"_s, u"Weezing"_s, u"Rhyhorn"_s, u"Rhydon"_s, u"Chansey"_s, u"Tangela"_s,
                u"Kangaskhan"_s, u"Horsea"_s, u"Seadra"_s, u"Goldeen"_s, u"Seaking"_s, u"Staryu"_s, u"Starmie"_s, u"Mr. Mime"_s, u"Scyther"_s,
                u"Jynx"_s, u"Electabuzz"_s, u"Magmar"_s, u"Pinsir"_s, u"Tauros"_s, u"Magikarp"_s, u"Gyarados"_s, u"Lapras"_s, u"Ditto"_s, u"Eevee"_s,
                u"Vaporeon"_s, u"Jolteon"_s, u"Flareon"_s, u"Porygon"_s, u"Omanyte"_s, u"Omastar"_s, u"Kabuto"_s, u"Kabutops"_s, u"Aerodactyl"_s,
                u"Snorlax"_s, u"Articuno"_s, u"Zapdos"_s, u"Moltres"_s, u"Dratini"_s, u"Dragonair"_s, u"Dragonite"_s, u"Mewtwo"_s, u"Mew"_s
        };
        QVBoxLayout *lyt = new QVBoxLayout();
        QFont pokemonComboFont;

        maxNature = natureList.size();
        pokemon = new QComboBox();
        pokemonComboFont = pokemon->font();
        exp = new QLineEdit();
        level = new QSpinBox();
        hp = new QSpinBox();
        attack = new QSpinBox();
        name = new QLineEdit();
        nature = new QComboBox();
        id = new QLineEdit();
        rareRandom = new QLineEdit();
        trainingSkillCount = new QSpinBox();
        isEvolve = new QCheckBox(u"Evolved"_s);
        shiny = new QCheckBox(u"Shiny"_s);

        for (int i=0,j=1,l=pokemonList.size(); i<l; ++i,++j) {
            const QString lbl = QString("%1 #%2").arg(pokemonList[i], QString::number(j).rightJustified(3, '0'));

            pokemon->addItem(QIcon(QString(":/pk%1").arg(j)), lbl);
        }

        pokemonComboFont.setPointSize(12);
        pokemon->setIconSize(QSize(42, 42));
        pokemon->setFont(pokemonComboFont);
        level->setRange(1, 100);
        hp->setRange(25, 9999);
        attack->setRange(25, 9999);
        trainingSkillCount->setRange(0, INT32_MAX);
        nature->addItem("");
        nature->addItems(natureList);

        lyt->setContentsMargins(0, 0, 0, 0);
        lyt->addItem(new QSpacerItem(1, 6, QSizePolicy::Expanding, QSizePolicy::Fixed));
        lyt->addWidget(pokemon);
        lyt->addItem(new QSpacerItem(1, 10, QSizePolicy::Expanding, QSizePolicy::Fixed));
        lyt->addWidget(new QLabel(u"Experience"_s));
        lyt->addWidget(exp);
        lyt->addWidget(new QLabel(u"Level"_s));
        lyt->addWidget(level);
        lyt->addWidget(new QLabel(u"HP"_s));
        lyt->addWidget(hp);
        lyt->addWidget(new QLabel(u"Attack"_s));
        lyt->addWidget(attack);
        lyt->addWidget(new QLabel(u"Name"_s));
        lyt->addWidget(name);
        lyt->addWidget(new QLabel(u"Nature"_s));
        lyt->addWidget(nature);
        lyt->addWidget(new QLabel(u"ID"_s));
        lyt->addWidget(id);
        lyt->addWidget(new QLabel(u"Rare random"_s));
        lyt->addWidget(rareRandom);
        lyt->addWidget(new QLabel(u"Training skill count"_s));
        lyt->addWidget(trainingSkillCount);
        lyt->addItem(new QSpacerItem(1, 4, QSizePolicy::Expanding, QSizePolicy::Fixed));
        lyt->addWidget(isEvolve);
        lyt->addWidget(shiny);

        setLayout(lyt);

        QObject::connect(pokemon, &QComboBox::currentIndexChanged, this, &PokemonBaseDataEditor::onPokemonChanged);
        QObject::connect(level, &QSpinBox::valueChanged, this, &PokemonBaseDataEditor::onLevelChanged);
        QObject::connect(id, &QLineEdit::textChanged, this, &PokemonBaseDataEditor::onIDChanged);
        QObject::connect(rareRandom, &QLineEdit::textChanged, this, &PokemonBaseDataEditor::onRareChanged);
    }

    void PokemonBaseDataEditor::refresh() const {
        const QSignalBlocker pkblock {pokemon};
        const QSignalBlocker lblock {level};
        const QSignalBlocker idblock {id};
        const QSignalBlocker rrblock {rareRandom};
        const int pkmNature = *pokemonData->nature;

        pokemon->setCurrentIndex(*pokemonData->monsterNo - 1);
        exp->setText(QString::number(*pokemonData->exp));
        level->setValue(*pokemonData->level);
        hp->setValue(*pokemonData->hp + *pokemonData->level);
        attack->setValue(*pokemonData->attak + *pokemonData->level);
        name->setText(QString::fromUtf16(pokemonData->name, pokemonData->nameLen).remove(u'\0'));
        nature->setCurrentIndex(pkmNature >= 0 && pkmNature < maxNature ? (pkmNature + 1) : 0);
        id->setText(QString::number(*pokemonData->id));
        rareRandom->setText(QString::number(*pokemonData->rareRandom));
        trainingSkillCount->setValue(*pokemonData->trainingSkillCount);
        isEvolve->setChecked(*pokemonData->isEvolve);
        shiny->setChecked(isShiny(*pokemonData->id, *pokemonData->rareRandom));
    }

    void PokemonBaseDataEditor::setPokemon(const std::shared_ptr<SaveCharacterData> &data, const int key) {
        prevLevel = *data->level;
        pokemonData = data;
        pkey = key;

        name->setMaxLength(data->nameLen);
        refresh();
    }

    void PokemonBaseDataEditor::setShinyStatus(const bool makeShiny) const {
        QRandomGenerator *globalRandGen = QRandomGenerator::global();
        quint32 _id, _rare;
        bool shinyPkm;

        while (true) {
            _id = globalRandGen->bounded(0U, UINT32_MAX);
            _rare = globalRandGen->bounded(0U, UINT32_MAX);
            shinyPkm = isShiny(_id, _rare);

            if ((makeShiny && shinyPkm) || (!makeShiny && !shinyPkm))
                break;
        }

        *pokemonData->id = _id;
        *pokemonData->rareRandom = _rare;
    }

    bool PokemonBaseDataEditor::isCoreDataModified() const {
        const std::u16string pname = name->text().toStdU16String();
        const int plevel = level->value();
        const int php = hp->value() - plevel;
        const int patk = attack->value() - plevel;

        return (*pokemonData->level != plevel ||
                *pokemonData->monsterNo != (pokemon->currentIndex() + 1) ||
                *pokemonData->hp != php ||
                *pokemonData->attak != patk ||
                std::memcmp(pname.data(), pokemonData->name, pokemonData->nameLen * 2) != 0);
    }

    void PokemonBaseDataEditor::apply() {
        QRandomGenerator *globalRandGen = QRandomGenerator::global();
        bool expRes, idRes, rareRes, shinyPkm;
        const bool updateExternalPkmLists = isCoreDataModified();
        const int monNo = pokemon->currentIndex() + 1;
        const int expI = exp->text().toUInt(&expRes);
        const int idI = id->text().toUInt(&idRes);
        const int rareI = rareRandom->text().toUInt(&rareRes);
        const QString pname = name->text();
        const int plevel = level->value();
        const int pnature = nature->currentIndex();
        const bool isNewEncounter = *pokemonData->monsterNo != monNo;

        if (expRes)
            *pokemonData->exp = expI;

        if (idRes)
            *pokemonData->id = idI;

        if (rareRes)
            *pokemonData->rareRandom = rareI;

        if (pname.size() <= pokemonData->nameLen) {
            const std::u16string name16 = pname.toStdU16String();

            std::memset(pokemonData->name, 0, pokemonData->nameLen * 2);
            std::memcpy(pokemonData->name, name16.c_str(), name16.size() * 2);
        }

        *pokemonData->monsterNo = monNo;
        *pokemonData->level = plevel;
        *pokemonData->hp = hp->value() - plevel;
        *pokemonData->attak = attack->value() - plevel;
        *pokemonData->nature = pnature == 0 ? globalRandGen->bounded(0, maxNature - 1) : (pnature - 1);
        *pokemonData->trainingSkillCount = trainingSkillCount->value();
        *pokemonData->isEvolve = isEvolve->isChecked();
        shinyPkm = isShiny(*pokemonData->id, *pokemonData->rareRandom);

        if (shiny->isChecked() && !shinyPkm)
            setShinyStatus(true);
        else if (!shiny->isChecked() && shinyPkm)
            setShinyStatus(false);

        if (updateExternalPkmLists)
            emit coreDataChanged(pkey);

        if (isNewEncounter)
            emit updatePokedex(monNo);
    }

    void PokemonBaseDataEditor::onPokemonChanged(const int idx) {
        name->setText(pokemon->itemText(idx).split('#').first().trimmed());
        emit pokemonChanged(idx + 1);
    }

    void PokemonBaseDataEditor::onLevelChanged(const int v) {
        hp->setValue(hp->value() - prevLevel + v);
        attack->setValue(attack->value() - prevLevel + v);
        prevLevel = v;

        if (v == 100) {
            exp->setText(QString::number(0));
            emit pokemonMaxLevel();
        }
    }

    void PokemonBaseDataEditor::onIDChanged(const QString &tx) const {
        bool idRes, rareRes;
        const int idI = tx.toUInt(&idRes);
        const int rareI = rareRandom->text().toUInt(&rareRes);

        if (idRes && rareRes)
            shiny->setChecked(isShiny(idI, rareI));
    }

    void PokemonBaseDataEditor::onRareChanged(const QString &tx) const {
        bool idRes, rareRes;
        const int idI = id->text().toUInt(&idRes);
        const int rareI = tx.toUInt(&rareRes);

        if (idRes && rareRes)
            shiny->setChecked(isShiny(idI, rareI));
    }
}
