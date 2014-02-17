#ifndef SSLCOMM_H
#define SSLCOMM_H

#include <qabstractsocket.h>
#include <qlist.h>
#include <qobjectdefs.h>
#include <qsslerror.h>
#include <qstring.h>

class QLabel;

class QStatusBar;

class QSslSocket;

namespace Ui {
class SslComm;
}

class SslComm : public QWidget
{
    Q_OBJECT

public:
    explicit SslComm(QWidget *parent = 0);
    ~SslComm();
    void setLabelStatus(QLabel* labelStatus);

public slots:
    void changeConnectionState();
    void socketStateChanged(QAbstractSocket::SocketState state);
    void socketEncrypted();
    void socketError(QAbstractSocket::SocketError socketError);
    void sslErrors(QList<QSslError> errors);
    void socketReadyRead();
    void sendData();

private:
    Ui::SslComm *ui;
    QLabel* labelStatus;
    QSslSocket* socket;

    void setStatus(QString status);
};

#endif // SSLCOMM_H
