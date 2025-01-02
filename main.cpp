#include <QApplication>

#include "PQHex.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    PQHex w;
    w.show();
    return a.exec();
}
