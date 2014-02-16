#ifndef SSLCOMM_H
#define SSLCOMM_H

#include <QWidget>
#include <QtNetwork/QSslSocket>

namespace Ui {
class SslComm;
}

class SslComm : public QWidget
{
    Q_OBJECT

public:
    explicit SslComm(QWidget *parent = 0);
    ~SslComm();

public slots:
    void changeConnectionState();

private:
    Ui::SslComm *ui;
    QSslSocket* socket;
};

#endif // SSLCOMM_H
