#include "telnetssl.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TelnetSSL w;
    w.show();

    return a.exec();
}
