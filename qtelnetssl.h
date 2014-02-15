#ifndef QTELNETSSL_H
#define QTELNETSSL_H

#include <QMainWindow>

namespace Ui
{
    class QTelnetSSL;
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
    Ui::QTelnetSSL *ui;
};

#endif // QTELNETSSL_H
