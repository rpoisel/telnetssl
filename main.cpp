#include "qtelnetssl.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTelnetSSL w;
    w.show();

    return a.exec();
}
