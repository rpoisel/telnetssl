#ifndef TELNETSSL_H
#define TELNETSSL_H

#include <QMainWindow>

namespace Ui {
class TelnetSSL;
}

class TelnetSSL : public QMainWindow
{
    Q_OBJECT

public:
    explicit TelnetSSL(QWidget *parent = 0);
    ~TelnetSSL();

private:
    Ui::TelnetSSL *ui;
};

#endif // TELNETSSL_H
