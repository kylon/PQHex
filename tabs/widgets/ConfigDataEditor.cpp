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
#include <QVBoxLayout>
#include <QLabel>

#include "ConfigDataEditor.h"

namespace PQH::UI {
    using namespace Qt::StringLiterals;

    ConfigDataEditor::ConfigDataEditor() {
        QVBoxLayout *lyt = new QVBoxLayout();

        playerSex = new QComboBox();
        language = new QComboBox();
        bgmMute = new QCheckBox(u"Disable music"_s);
        seMute = new QCheckBox(u"Disable sound effects"_s);
        pushNotice = new QCheckBox(u"Push notifications"_s);

        playerSex->addItems({u"Male"_s, u"Female"_s, u"Other"_s});
        language->addItems({"", u"Japanese"_s, u"English"_s, u"French"_s, u"Italian"_s, u"German"_s, u"Spanish"_s, u"Korean"_s, u"ChineseSimplified"_s, u"ChineseTraditional"_s});

        lyt->setContentsMargins(0, 0, 0, 0);
        lyt->addWidget(new QLabel(u"Player sex"_s));
        lyt->addWidget(playerSex);
        lyt->addWidget(new QLabel(u"Language"_s));
        lyt->addWidget(language);
        lyt->addWidget(bgmMute);
        lyt->addWidget(seMute);
        lyt->addWidget(pushNotice);

        setLayout(lyt);
    }

    void ConfigDataEditor::setData(const std::shared_ptr<ConfigData> &data) {
        configData = data;

        playerSex->setCurrentIndex(*configData->playerSex);
        language->setCurrentIndex(*configData->language);
        bgmMute->setChecked(*configData->bgmMute);
        seMute->setChecked(*configData->seMute);
        pushNotice->setChecked(*configData->PushNotice);
    }

    void ConfigDataEditor::apply() const {
        *configData->playerSex = playerSex->currentIndex();
        *configData->language = language->currentIndex();
        *configData->bgmMute = bgmMute->isChecked();
        *configData->seMute = seMute->isChecked();
        *configData->PushNotice = pushNotice->isChecked();
    }
}
