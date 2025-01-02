#include <QFileDialog>

#include "PQHex.h"
#include "./ui_pqhex.h"
#include "tabs/NatureTab.h"

PQHex::PQHex(QWidget *parent): QMainWindow(parent), ui(new Ui::PQHex) {
    ui->setupUi(this);

    QVBoxLayout *lyt = new QVBoxLayout();
    QHBoxLayout *actionsLyt = new QHBoxLayout();
    PQH::UI::NatureTab *natureTab = new PQH::UI::NatureTab();

    tabWidget = new QTabWidget();
    mainTab = new PQH::UI::MainTab();
    logTab = new PQH::UI::LogTab();
    loadBtn = new QPushButton("Load");
    loadDecryptedBtn = new QPushButton("Load decrypted");
    saveBtn = new QPushButton("Save");
    saveDecryptedBtn = new QPushButton("Save decrypted");

    tabWidget->addTab(mainTab, "Main");
    tabWidget->addTab(natureTab, "Nature Table");
    tabWidget->addTab(logTab, "Logs");
    saveBtn->setEnabled(false);
    saveDecryptedBtn->setEnabled(false);

    logTabIdx = tabWidget->indexOf(logTab);

    actionsLyt->addWidget(loadBtn);
    actionsLyt->addWidget(loadDecryptedBtn);
    actionsLyt->addWidget(saveBtn);
    actionsLyt->addWidget(saveDecryptedBtn);
    lyt->addWidget(tabWidget);
    lyt->addLayout(actionsLyt);
    setWindowTitle("PQHex");
    setFixedSize(800, 600);
    ui->centralwidget->setLayout(lyt);

    QObject::connect(loadBtn, &QPushButton::clicked, this, &PQHex::onLoadBtnClicked);
    QObject::connect(loadDecryptedBtn, &QPushButton::clicked, this, &PQHex::onLoadDecryptedBtnClicked);
    QObject::connect(saveBtn, &QPushButton::clicked, this, &PQHex::onSaveBtnClicked);
    QObject::connect(saveDecryptedBtn, &QPushButton::clicked, this, &PQHex::onSaveDecryptedBtnClicked);
    QObject::connect(tabWidget, &QTabWidget::currentChanged, this, &PQHex::onTabChanged);
    QObject::connect(mainTab, &PQH::UI::MainTab::ingridientsSaved, this, &PQHex::onIngridientsSaved);
    QObject::connect(mainTab, &PQH::UI::MainTab::playerNameChanged, this, &PQHex::onPlayerNameChanged);
    QObject::connect(mainTab, &PQH::UI::MainTab::stoneEdited, this, &PQHex::onStoneEdited);
    QObject::connect(mainTab, &PQH::UI::MainTab::goodsSaved, this, &PQHex::onGoodsSaved);
}

PQHex::~PQHex() {
    delete ui;
}

void PQHex::load(const bool encrypted) {
    const QString fsave = QFileDialog::getOpenFileName(this, "Load savedata");
    PQH::Error ret;

    if (fsave.isEmpty())
        return;

    pqsave = std::make_unique<PQH::Save>();
    ret = encrypted ? pqsave->read(fsave) : pqsave->readDecrypted(fsave);

    if (ret != PQH::Error::NONE) {
        writeLog(getErrorString(ret));

    } else {
        mainTab->setData(pqsave->getCheckData(), pqsave->getSerializeData());
        saveDecryptedBtn->setEnabled(true);
        saveBtn->setEnabled(true);
    }
}

void PQHex::writeLog(const QString &msg) {
    logTab->write(msg);

    if (tabWidget->currentIndex() == logTabIdx)
        return;

    ++unreadLogs;
    tabWidget->setTabText(logTabIdx, QString("Logs (%1)").arg(unreadLogs));
}

QString PQHex::getErrorString(const PQH::Error e) const {
    switch (e) {
        case PQH::Error::SAVE_FILE_READ:
            return "Failed to read save file";
        case PQH::Error::WRITE_FILE_OPEN:
            return "Cannot write to file";
        case PQH::Error::DEC_HEAD:
            return "Failed to decrypt head";
        case PQH::Error::ENC_HEAD:
            return "Failed to encrypt head";
        case PQH::Error::DEC_BODY:
            return "Failed to decrypt body";
        case PQH::Error::ENC_BODY:
            return "Failed to encrypt body";
        case PQH::Error::CALC_CHECKSUM:
            return "Failed to calculate checksum";
        case PQH::Error::CHECKSUM_MISMATCH:
            return "Checksum error, file may be corrupt";
        case PQH::Error::NONE:
            return "Success";
        default:
            return "Unknown error";
    }
}

void PQHex::onLoadBtnClicked() {
    load(true);
}

void PQHex::onLoadDecryptedBtnClicked() {
    load(false);
}

void PQHex::onSaveBtnClicked() {
    const QString savef = QFileDialog::getSaveFileName(this, "Encrypted savedata", "user");
    PQH::Error ret;

    if (savef.isEmpty())
        return;

    ret = pqsave->write(savef);

    if (ret != PQH::Error::NONE)
        writeLog(getErrorString(ret));
    else
        writeLog("Save: success");
}

void PQHex::onSaveDecryptedBtnClicked() {
    const QString savef = QFileDialog::getSaveFileName(this, "Decrypted savedata", "user_dec");
    PQH::Error ret;

    if (savef.isEmpty())
        return;

    ret = pqsave->writeDecrypted(savef);

    if (ret != PQH::Error::NONE)
        writeLog(getErrorString(ret));
    else
        writeLog("Save decrypted: success");
}

void PQHex::onTabChanged(const int idx) {
    if (idx == logTabIdx && unreadLogs) {
        tabWidget->setTabText(logTabIdx, "Logs");
        unreadLogs = 0;
    }
}

void PQHex::onIngridientsSaved(const QList<int> &counts) const {
    pqsave->patchIngridients(counts);
    mainTab->setData(pqsave->getCheckData(), pqsave->getSerializeData());
}

void PQHex::onPlayerNameChanged(const QString &name) const {
    pqsave->patchPlayerName(name);
    mainTab->setData(pqsave->getCheckData(), pqsave->getSerializeData());
}

void PQHex::onStoneEdited(const int key) const {
    pqsave->patchStone(key);
    mainTab->setData(pqsave->getCheckData(), pqsave->getSerializeData());
}

void PQHex::onGoodsSaved() const {
    pqsave->patchGoods();
    mainTab->setData(pqsave->getCheckData(), pqsave->getSerializeData());
}
