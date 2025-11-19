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
#pragma once

#include <QMainWindow>

#include "Save.h"
#include "tabs/LogTab.h"
#include "tabs/MainTab.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class PQHex;
}
QT_END_NAMESPACE

class PQHex final: public QMainWindow {
    Q_OBJECT

private:
    Ui::PQHex *ui;
    QPushButton *loadBtn = nullptr;
    QPushButton *loadDecryptedBtn = nullptr;
    QPushButton *saveBtn = nullptr;
    QPushButton *saveDecryptedBtn = nullptr;
    QTabWidget *tabWidget = nullptr;
    PQH::UI::LogTab *logTab = nullptr;
    PQH::UI::MainTab *mainTab = nullptr;
    std::unique_ptr<PQH::Save> pqsave;
    int unreadLogs = 0;
    int logTabIdx;

    void load(bool encrypted);
    void writeLog(const QString &msg);
    [[nodiscard]] QString getErrorString(PQH::Error e) const;

public:
    explicit PQHex(QWidget *parent = nullptr);
    ~PQHex() override;

private slots:
    void onLoadBtnClicked();
    void onLoadDecryptedBtnClicked();
    void onSaveBtnClicked();
    void onSaveDecryptedBtnClicked();
    void onTabChanged(int idx);
    void onIngridientsSaved(const QList<int> &counts) const;
    void onPlayerNameChanged(const QString &name) const;
    void onStoneEdited(int key) const;
    void onGoodsSaved() const;
};
