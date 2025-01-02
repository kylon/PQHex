#include <QRandomGenerator>
#include <QVBoxLayout>
#include <QLabel>

#include "PokemonBaseDataEditor.h"

namespace PQH::UI {
    PokemonBaseDataEditor::PokemonBaseDataEditor() {
        const QList<QString> natureList {
                "Hardy", "Lonely", "Brave", "Adamant", "Naughty", "Bold", "Docile", "Relaxed",
                "Impish", "Lax", "Timid", "Hasty", "Serious", "Jolly", "Naive", "Modest",
                "Mild", "Quiet", "Bashful", "Rash", "Calm", "Gentle", "Sassy", "Careful", "Quirky"
        };
        const QList<QString> pokemonList = {
                "Bulbasaur", "Ivysaur", "Venusaur", "Charmander", "Charmeleon", "Charizard", "Squirtle",
                "Wartortle", "Blastoise", "Caterpie", "Metapod", "Butterfree", "Weedle", "Kakuna", "Beedrill",
                "Pidgey", "Pidgeotto", "Pidgeot", "Rattata", "Raticate", "Spearow", "Fearow", "Ekans",
                "Arbok", "Pikachu", "Raichu", "Sandshrew", "Sandslash", "Nidoran (Female)", "Nidorina",
                "Nidoqueen", "Nidoran (Male)", "Nidorino", "Nidoking", "Clefairy", "Clefable", "Vulpix",
                "Ninetales", "Jigglypuff", "Wigglytuff", "Zubat", "Golbat", "Oddish", "Gloom","Vileplume",
                "Paras", "Parasect", "Venonat", "Venomoth", "Diglett", "Dugtrio", "Meowth", "Persian",
                "Psyduck", "Golduck", "Mankey", "Primeape", "Growlithe", "Arcanine", "Poliwag", "Poliwhirl",
                "Poliwrath", "Abra", "Kadabra", "Alakazam", "Machop", "Machoke", "Machamp", "Bellsprout",
                "Weepinbell", "Victreebel", "Tentacool", "Tentacruel", "Geodude", "Graveler", "Golem", "Ponyta",
                "Rapidash", "Slowpoke", "Slowbro", "Magnemite", "Magneton", "Farfetch'd", "Doduo", "Dodrio", "Seel",
                "Dewgong", "Grimer", "Muk", "Shellder", "Cloyster", "Gastly", "Haunter", "Gengar", "Onix", "Drowzee",
                "Hypno", "Krabby", "Kingler", "Voltorb", "Electrode", "Exeggcute", "Exeggutor", "Cubone", "Marowak",
                "Hitmonlee", "Hitmonchan", "Lickitung", "Koffing", "Weezing", "Rhyhorn", "Rhydon", "Chansey", "Tangela",
                "Kangaskhan", "Horsea", "Seadra", "Goldeen", "Seaking", "Staryu", "Starmie", "Mr. Mime", "Scyther",
                "Jynx", "Electabuzz", "Magmar", "Pinsir", "Tauros", "Magikarp", "Gyarados", "Lapras", "Ditto", "Eevee",
                "Vaporeon", "Jolteon", "Flareon", "Porygon", "Omanyte", "Omastar", "Kabuto", "Kabutops", "Aerodactyl",
                "Snorlax", "Articuno", "Zapdos", "Moltres", "Dratini", "Dragonair", "Dragonite", "Mewtwo", "Mew"
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
        isEvolve = new QCheckBox("Evolved");
        shiny = new QCheckBox("Shiny");

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
        lyt->addWidget(new QLabel("Experience"));
        lyt->addWidget(exp);
        lyt->addWidget(new QLabel("Level"));
        lyt->addWidget(level);
        lyt->addWidget(new QLabel("HP"));
        lyt->addWidget(hp);
        lyt->addWidget(new QLabel("Attack"));
        lyt->addWidget(attack);
        lyt->addWidget(new QLabel("Name"));
        lyt->addWidget(name);
        lyt->addWidget(new QLabel("Nature"));
        lyt->addWidget(nature);
        lyt->addWidget(new QLabel("ID"));
        lyt->addWidget(id);
        lyt->addWidget(new QLabel("Rare random"));
        lyt->addWidget(rareRandom);
        lyt->addWidget(new QLabel("Training skill count"));
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
