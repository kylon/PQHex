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
#include <QLabel>

#include "PartyTab.h"

namespace PQH::UI {
    PartyTab::PartyTab() {
        const QColor colorRoles[] = {Qt::darkRed, Qt::darkGreen, Qt::darkBlue};
        QFont comboFont;
        int i = 0;

        members = {new QComboBox, new QComboBox, new QComboBox};
        comboFont = members[0]->font();
        saveBtn = new QPushButton("Apply");

        comboFont.setPointSize(12);
        saveBtn->setEnabled(false);

        for (QComboBox *combo: members) {
            QHBoxLayout *partyMemberLyt = new QHBoxLayout();
            QLabel *role = new QLabel();
            QPalette rolePal = role->palette();

            rolePal.setColor(QPalette::Window, colorRoles[i++]);
            role->setPalette(rolePal);
            role->setMaximumWidth(6);
            role->setAutoFillBackground(true);
            combo->setIconSize(QSize(42, 42));
            combo->setFont(comboFont);
            combo->setMinimumHeight(50);
            partyMemberLyt->addWidget(role);
            partyMemberLyt->addWidget(combo);
            scrollLyt->addLayout(partyMemberLyt);

            QObject::connect(combo, &QComboBox::currentIndexChanged, this, &PartyTab::onPartyPkmChanged);
        }

        scrollLyt->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
        lyt->addWidget(saveBtn);

        QObject::connect(saveBtn, &QPushButton::clicked, this, &PartyTab::onSaveBtnClicked);
    }

    QString PartyTab::makePokemonLbl(const int key) const {
        const std::shared_ptr<SaveCharacterData> pkm = characterStorageData->characterDataDictionary[key]->data;
        const QString name = QString::fromUtf16(pkm->name, pkm->nameLen).remove(u'\0');
        const int hp = *pkm->hp + *pkm->level;
        const int atk = *pkm->attak + *pkm->level;

        return QString("%1 L.%2 [HP:%3 ATK:%4]").arg(name).arg(*pkm->level).arg(hp).arg(atk);
    }

    void PartyTab::setData(const std::shared_ptr<BattleData> &battleData, const std::shared_ptr<CharacterStorage> &characterStorage) {
        int membersIdx[3] = {0};
        int i = 1;

        formationData = battleData->formationDatas[0];
        characterStorageData = characterStorage;

        for (QComboBox *combo: members) {
            const QSignalBlocker sblock {combo};

            combo->clear();
            combo->addItem("", -1);
        }

        for (const auto &[dictKey, manageData]: characterStorage->characterDataDictionary) {
            const QPixmap icon = QPixmap(QString(":/pk%1").arg(*manageData->data->monsterNo));

            for (QComboBox *combo: members) {
                const QSignalBlocker sblock {combo};

                combo->addItem(icon, makePokemonLbl(dictKey), dictKey);
            }

            for (int j=0; j<3; ++j) {
                if (dictKey == *(formationData->memberDatas[j]->storageIndex))
                    membersIdx[j] = i;
            }

            ++i;
        }

        for (int m=0; m<3; ++m)
            members[m]->setCurrentIndex(membersIdx[m]);

        saveBtn->setEnabled(true);
    }

    void PartyTab::updatePokemonData(const int key) const {
        const QString lbl = makePokemonLbl(key);

        for (QComboBox *combo: members) {
            const int idx = combo->findData(key);

            if (idx == -1)
                continue;

            combo->setItemText(idx, lbl);
            combo->setItemIcon(idx, QPixmap(QString(":/pk%1").arg(*characterStorageData->characterDataDictionary[key]->data->monsterNo)));
        }
    }

    void PartyTab::onPartyPkmChanged(const int idx) const {
        QComboBox *combo = qobject_cast<QComboBox *>(QObject::sender());

        if (combo == nullptr)
            return;

        for (QComboBox *pkm: members) {
            if (pkm == combo || pkm->currentData().toInt() != combo->currentData().toInt())
                continue;

            const QSignalBlocker sblock {combo};

            combo->setCurrentIndex(0);
        }
    }

    void PartyTab::onSaveBtnClicked() {
        saveBtn->setEnabled(false);

        QList<int> party;

        for (int i=0,l=members.size(); i<l; ++i) {
            const int pkm = members[i]->currentData().toInt();

            *(formationData->memberDatas[i]->storageIndex) = pkm;

            if (pkm != -1)
                party.append(pkm);
        }

        emit partyChanged(party);
        saveBtn->setEnabled(true);
    }
}
