#ifndef QTELNETSSL_H
#define QTELNETSSL_H

#include <QMainWindow>

#include "sslcomm.h"

namespace Ui
{
    class TelnetSSL;
}

class QTelnetSSL: public QMainWindow
{
    Q_OBJECT

public:
    explicit QTelnetSSL(QWidget *parent = 0);
    ~QTelnetSSL();

public slots:
    void printInfo();

private:
    Ui::TelnetSSL *ui;
    SslComm *mainForm;
};

#endif // QTELNETSSL_H
